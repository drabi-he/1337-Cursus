/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:49:31 by hdrabi            #+#    #+#             */
/*   Updated: 2022/10/29 15:16:52 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(std::string config) {
	size_t i;
	if (config.empty())
		throw std::runtime_error("Error: Invalid config file: empty server block");
	config.insert(0, "\n");
	config = init_locations(config);

	i = 0;
	while ((i = config.find("listen ", i)) != std::string::npos) {
		std::string listen = get_value(&config, "listen ", 1, i);
		listen = trim(listen);
		if (listen.find(' ') != std::string::npos)
			throw std::runtime_error("Error: wrong number of arguments for directive 'listen'");
		int port = get_port(listen);
		std::string host = get_host(listen);
		if (_listen.find(port) != _listen.end())
			throw std::logic_error("Error: duplicate port value");
		_listen[port] = host;
		i = 0;
	}

	i = 0;
	while ((i = config.find("\nserver_name ", i)) != std::string::npos) {
		std::string server_name = get_value(&config, "\nserver_name ", 1, i);
		server_name = trim(server_name);
		std::vector<std::string> tmp = split_vec(server_name);
		_serverName.insert(_serverName.end(), tmp.begin(), tmp.end());
		i = 0;
	}

	_root = get_value(&config, "\nroot ", 0);
	if (_root.find(' ') != std::string::npos)
		throw std::runtime_error("Error: wrong number of arguments for directive 'root'");

	i = 0;
	while ((i = config.find("\nindex ", i)) != std::string::npos) {
		std::string index = get_value(&config, "\nindex ", 1, i);
		index = trim(index);
		std::vector<std::string> tmp = split_vec(index);
		_index.insert(_index.end(), tmp.begin(), tmp.end());
		i = 0;
	}
	if (_index.size() == 0)
		_index.push_back("index.html");

	_autoIndex = get_value(&config, "\nautoindex ", 0);
	if (_autoIndex == "")
		_autoIndex = "off";
	else
		if (_autoIndex != "on" && _autoIndex != "off")
			throw std::runtime_error("Error: undefined autoindex value");

	_uploadPath = get_value(&config, "\nupload_path " , 0);
	if (_uploadPath.find(' ') != std::string::npos)
		throw std::runtime_error("Error: wrong number of arguments for directive 'upload_path'");


	_clientMaxBodySize = get_value(&config, "\nclient_max_body_size ", 0);
	if (_clientMaxBodySize.find(' ') != std::string::npos)
		throw std::runtime_error("configFile error, wrong number of arguments for directive 'client_max_body_size'");
	if (_clientMaxBodySize.empty())
		_clientMaxBodySize = std::to_string(ULLONG_MAX);
	if (std::atol(_clientMaxBodySize.c_str()) < 0 )
		throw std::runtime_error("configFile error, client_max_body_size value is out of range");

	i = 0;
	while ((i = config.find("\nerror_page ", i)) != std::string::npos) {
		std::string _error = get_value(&config, "\nerror_page ", 1, i);
		_error = trim(_error);
		std::vector<std::string> codes = split_vec(_error.substr(0, _error.find_last_of(' ')));
		std::string path = _error.substr(_error.find_last_of(' ') + 1, _error.length());
		int newCode = -1;
		for (std::vector<std::string>::const_iterator it = codes.begin() ; it != codes.end(); it++) {
			for (size_t j = 0; j < (*it).length(); j++) {
				if (!std::isdigit((*it)[j])) {
					if (j != 0 || (*it)[j] != '=' || (it != (codes.end() - 1))){
						throw std::runtime_error("configFile error, wrong format for directive 'error_page'");
					}
				}
			}
			if ((*it)[0] == '=') {
				newCode = std::stoi((*it).substr(1, (*it).length()));
				codes.erase(it);
				break ;
			}
		}
		for (std::vector<std::string>::const_iterator it = codes.begin() ; it != codes.end(); it++) {
			if (_errorPages.find(std::stoi(*it)) == _errorPages.end()) {
				int code = std::stoi(*it);
				if (code < 300 || code > 599)
					throw std::runtime_error("configFile error, error_page value is out of range");
				_errorPages[code] = path;
				_errorCodes[code] = newCode;
			}
		}
		i = 0;
	}

	i = 0;
	while ((i = config.find("\ncgi ", i)) != std::string::npos) {
		std::string cgi = get_value(&config, "\ncgi ", 1, i);
		cgi = trim(cgi);
		if (cgi.find(' ') == std::string::npos)
			throw std::runtime_error("configFile error, wrong number of arguments for directive 'cgi'");
		_cgi.push_back(std::make_pair(cgi.substr(0, cgi.find(' ')), cgi.substr(cgi.find_last_of(' ') + 1, cgi.length())));
		i = 0;
	}
	for (size_t k = 0; k < _cgi.size(); k++) {
		if (_cgi[k].first.find('.') != std::string::npos)
			throw std::runtime_error("configFile error, wrong format for directive 'cgi'");
	}

	_cgiBin = get_value(&config, "\ncgi_bin ", 0);
	if (_cgiBin.find(' ') != std::string::npos)
		throw std::runtime_error("Error: wrong number of arguments for directive '_cgiBin'");

	_methods = get_value(&config, "\nmethods ", 0);
	if (_methods == "")
		_methods = "GET POST DELETE";
	_methods = decipherMethods(split_vec(_methods));

	std::string tmp = get_value(&config, "\nreturn ", 0);
	if (!tmp.empty()) {
		_return.second = tmp.substr(tmp.find(' '), tmp.length() - 1);
		std::string code = tmp.substr(0, tmp.find(' '));
		for (size_t j = 0; j < code.length(); j++)
			if (!std::isdigit(code[j]))
				throw std::runtime_error("configFile error, return value should be a status code");
		_return.first = std::stoi(code);
	}

	i = 0;
	for (i = 0; i < _locations.size(); i++) {
		if (_locations[i]->_path == "/")
			break ;
	}
	if (i == _locations.size()) {
		_locations.push_back(new Location());
	}
	if (_locations[i]->_path == "")
		_locations[i]->_path = "/";
	if (_locations[i]->_root == "")
		_locations[i]->_root = _root;
	if (_locations[i]->_index.size() == 0)
		_locations[i]->_index = _index;
	if (_locations[i]->_autoIndex == "")
		_locations[i]->_autoIndex = _autoIndex;
	if (_locations[i]->_errorPages.size() == 0)
		_locations[i]->_errorPages = _errorPages;
	if (_locations[i]->_errorCodes.size() == 0)
		_locations[i]->_errorCodes = _errorCodes;
	if (_locations[i]->_methods == "")
		_locations[i]->_methods = _methods;
	if (_locations[i]->_return.first == 0)
		_locations[i]->_return = _return;

	i = 0;
	for (i = 0; i < _locations.size(); i++) {
		_locations[i]->_cgi = _cgi;
		_locations[i]->_cgiBin = _cgiBin;
		_locations[i]->_uploadPath = _uploadPath;
		if (_locations[i]->_root == "")
			_locations[i]->_root = _root;
	}

	config = trim(config);
	if (!config.empty())
		throw std::runtime_error("Error: invalid directive(s) for server block");
}

Server::~Server()
{
}

std::string Server::init_locations(std::string config) {
	size_t i = 0;
	size_t j = 0;
	std::string rst;

	while (1) {
		i = config.find("\nlocation ");
		if (i == std::string::npos)
			break ;
		j = config.find("}", i);
		rst = config.substr(i, j - i + 1);
		config.erase(i, j - i + 1);
		_locations.push_back(new Location(rst));
	}
	return config;
}

void Server::display() const {

	_listen.size() != 0 && std::cout << "listen: " << std::endl;
	std::map<int, std::string>::const_iterator it ;
    for (it = _listen.begin(); it != _listen.end(); it++)
		it->second != "" && std::cout << "\t" << it->first << " " << it->second << std::endl;

	_serverName.size() != 0 && std::cout << "server_name: " << std::endl;
    for (std::vector<std::string>::const_iterator it = _serverName.begin() ; it != _serverName.end(); it++)
		std::cout << "\t" << *it << std::endl;


	_root != "" && std::cout << "root: " << _root << std::endl;

	_index.size() != 0 && std::cout << "index: " << std::endl;
    for (std::vector<std::string>::const_iterator it = _index.begin() ; it != _index.end(); it++)
		std::cout << "\t" << *it << std::endl;

	_autoIndex != "" && std::cout << "auto_index: " << _autoIndex << std::endl;

	_uploadPath != "" && std::cout << "upload_path: " << _uploadPath << std::endl;

	_clientMaxBodySize != "" && std::cout << "client_max_body_size: " << _clientMaxBodySize << std::endl;

	_cgiBin != "" && std::cout << "cgi_bin: " << _cgiBin << std::endl;

	_cgi.size() != 0 && std::cout << "CGI: " << std::endl;
    for (std::vector< std::pair <std::string , std::string> >::const_iterator it = _cgi.begin() ; it != _cgi.end(); it++)
		std::cout << "\t" << it->first << "\t" << it->second << std::endl;

	_errorPages.size() != 0 && std::cout << "ErrorPages: " << std::endl;
    for (it = _errorPages.begin(); it != _errorPages.end(); it++)
		it->second != "" && std::cout << "\t" << it->first << " " << it->second << "\t=" << _errorCodes.find(it->first)->second <<  std::endl;

	_methods != "" && std::cout << "methods: " << _methods << std::endl;

	_return.first != 0 && std::cout << "return: " << _return.first << " " << _return.second << std::endl;

	for (size_t i = 0; i < _locations.size(); i++) {
		std::cout << "-------- location " << i + 1 << " --------" << std::endl;
		_locations[i]->display();
	}
}