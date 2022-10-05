/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:17:50 by hdrabi            #+#    #+#             */
/*   Updated: 2022/10/01 13:58:54 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(std::string& config) {
	config = init_locations(config);
	size_t i = 0;

	// listen
	while ((i = config.find("\nlisten ", i)) != std::string::npos) {
		std::string listen = get_value(config, "\nlisten ", 1, i);
		listen = trim(listen);
		if (listen.find(' ') != std::string::npos)
			throw std::runtime_error("configFile error, wrong number of arguments for directive 'listen'");
		int port = get_port(listen);
		std::string host = get_host(listen);
		if (_listen.find(port) != _listen.end())
			throw std::logic_error("configFile error, duplicate port value");
		_listen[port] = host;
		i++;
	}

	// server_name
	i = 0;
	while ((i = config.find("\nserver_name ", i)) != std::string::npos) {
		std::string server_name = get_value(config, "\nserver_name ", 1, i);
		server_name = trim(server_name);
		std::vector<std::string> tmp = split_vec(server_name);
		_serverName.insert(_serverName.end(), tmp.begin(), tmp.end());
		i++;
	}

	// root
	_root = get_value(config, "\nroot ", 0);
	if (_root.find(' ') != std::string::npos)
		throw std::runtime_error("configFile error, wrong number of arguments for directive 'root'");

	// index ;
	i = 0;
	while ((i = config.find("\nindex ", i)) != std::string::npos) {
		std::string index = get_value(config, "\nindex ", 1, i);
		index = trim(index);
		std::vector<std::string> tmp = split_vec(index);
		_index.insert(_index.end(), tmp.begin(), tmp.end());
		i++;
	}
	if (_index.size() == 0)
		_index.push_back("index.html");

	// auto index
	_autoIndex = get_value(config, "\nautoindex ", 0);
	if (_autoIndex == "")
		_autoIndex = "off";
	else
		if (_autoIndex != "on" && _autoIndex != "off")
			throw std::runtime_error("configFile error, undefined autoindex value");

	// upload_path
	_uploadPath = get_value(config, "\nupload_path " , 0);
	if (_uploadPath.find(' ') != std::string::npos)
		throw std::runtime_error("configFile error, wrong number of arguments for directive 'upload_path'");

	// client_max_body_size
	_clientMaxBodySize = get_value(config, "\nclient_max_body_size ", 0);
	if (_clientMaxBodySize.find(' ') != std::string::npos)
		throw std::runtime_error("configFile error, wrong number of arguments for directive 'client_max_body_size'");
	if (_clientMaxBodySize.empty())
		_clientMaxBodySize = "1m";

	// error_page
	i = 0;
	while ((i = config.find("\nerror_page ", i)) != std::string::npos) {
		std::string _error = get_value(config, "\nerror_page ", 1, i);
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
		i++;
	}

	_methods = get_value(config, "\nmethods ", 0);
	_methods = decipherMethods(split_vec(_methods));
}

Server::~Server() {

}

std::string Server::init_locations(std::string str) {
	size_t i = 0;
	size_t j = 0;
	std::string rst;

	while (1) {
		i = str.find("\nlocation ");
		if (i == std::string::npos)
			break ;
		j = str.find("}", i);
		rst = str.substr(i, j - i + 1);
		str.erase(i, j - i + 1);
		_locations.push_back(new Location(rst));
	}
	return str;
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

	_autoIndex != "" && std::cout << "autoindex: " << _autoIndex << std::endl;

	_clientMaxBodySize != "" && std::cout << "client_max_body_size: " << _clientMaxBodySize << std::endl;

	_errorPages.size() != 0 && std::cout << "ErrorPages: " << std::endl;
    for (it = _errorPages.begin(); it != _errorPages.end(); it++)
		it->second != "" && std::cout << "\t" << it->first << " " << it->second << "\t=" << _errorCodes.find(it->first)->second <<  std::endl;

	_uploadPath != "" && std::cout << "upload_path: " << _uploadPath << std::endl;
	_methods != "" && std::cout << "methods: " << _methods << std::endl;
	for (size_t i = 0; i < _locations.size(); i++) {
		std::cout << "-------- location " << i + 1 << " --------" << std::endl;
		_locations[i]->display();
	}
}

std::map<int , std::string> Server::getListen() const{
	return _listen;
}