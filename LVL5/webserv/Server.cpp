/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:17:50 by hdrabi            #+#    #+#             */
/*   Updated: 2022/09/21 15:05:12 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


Server::Server(/* args */) {

}

Server::Server(std::string& config) {
	config = init_locations(config);
	std::string listen = get_value(config, "\nlisten ");
	_host = listen.find(':') != std::string::npos ? listen.substr(0, listen.find(':')) : (listen.find('.') != std::string::npos ? listen : "127.0.0.1" );
	_port = listen.find(':') != std::string::npos ? listen.substr(listen.find(':') + 1, listen.length()) : (listen.find('.') != std::string::npos ? "8080" : listen);
	_serverName = get_value(config, "\nserver_name ");
	_autoIndex = get_value(config, "\nautoindex ");
	_index = get_value(config, "\nindex ");
	_root = get_value(config, "\nroot ");
	_uploadPath = get_value(config, "\nupload_path ");
	_clientBodySizeLimit = get_value(config, "\nclient_body_size_limit ");

	int i = 0;
	while ((i = config.find("\nerror_page ", i)) != std::string::npos) {
		std::string _error = get_value(config, "\nerror_page ", i);
		_error = trim(_error);
		int code = std::stoi(_error.substr(0, _error.find(' ')));
		std::string path = _error.substr(_error.find(' ') + 1, _error.length());
		if (_errorPages.find(code) != _errorPages.end())
			throw std::logic_error("duplicate error code");
		_errorPages[code] = path;
		i++;
	}
	_methods = decipherMethods(get_value(config, "\nmethods "));
}

Server::Server(const Server& other) {

}

Server &Server::operator=(const Server& other) {

	return *this;
}

Server::~Server() {

}

std::string Server::init_locations(std::string str) {
	int i = 0;
	int j = 0;
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
	_host != "" && std::cout << "Host: " << _host << std::endl;
	_port != "" && std::cout << "Port: " << _port << std::endl;
	_serverName != "" && std::cout << "server_name: " << _serverName << std::endl;
	_autoIndex != "" && std::cout << "autoindex: " << _autoIndex << std::endl;
	_index != "" && std::cout << "index: " << _index << std::endl;
	_root != "" && std::cout << "root: " << _root << std::endl;
	_uploadPath != "" && std::cout << "index: " << _uploadPath << std::endl;
	_errorPages.size() != 0 && std::cout << "ErrorPages: " << std::endl;
	std::map<int, std::string>::const_iterator it ;
    for (it = _errorPages.begin(); it != _errorPages.end(); it++)
		it->second != "" && std::cout << "\t" << it->first << " " << it->second << std::endl;
	_methods != "" && std::cout << "methods: " << _methods << std::endl;
	for (size_t i = 0; i < _locations.size(); i++) {
		std::cout << "-------- location " << i + 1 << " --------" << std::endl;
		_locations[i]->display();
	}
}
