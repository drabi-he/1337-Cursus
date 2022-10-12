/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:36:01 by hdrabi            #+#    #+#             */
/*   Updated: 2022/10/12 11:12:05 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServ.hpp"

WebServ::WebServ(std::string& configFile)
{
	std::ifstream config;
	std::string config_str = "";
	std::string line;

	config.open(configFile);
	if (!config.is_open())
		throw std::runtime_error("file not found or corrupted");
	while(std::getline(config, line)) {
		line = trim(line);

		check_line(line);

		if (!line.empty())
			config_str += line + "\n";
	}
	if (!check_brackets(config_str))
		throw std::logic_error("configFile, brackets error");
	config_str.erase(config_str.size() - 1, 1);
	init_servers(config_str);
}

WebServ::~WebServ()
{
}

void WebServ::init_servers(std::string& str) {
	size_t i = 0;
	std::string rst;

	while (1) {
		i = str.find("SERVER", i) < str.find("server" , i) ? str.find("SERVER" , i) : str.find("server" , i);
		if (i == std::string::npos)
			break;
		if (str[i + 6] != '\n' && str[i + 6] != ' ') {
            i++;
            continue;
        }

		rst = str.substr(0, i);
		str.erase(0, i + 6);
		rst = trim(rst);
		if (!rst.empty()) {
			if (rst[0] != '{' || rst[rst.length() - 1] != '}')
				throw std::logic_error("configFile error, open/close of brackets");
			_servers.push_back(new Server(rst));
		}
		i = 0;
	}
	str = trim(str);
	if(str[0] != '{' || str[str.length() - 1] != '}')
		throw std::logic_error("configFile error, open/close of brackets");
	_servers.push_back(new Server(str));
}

void WebServ::display() const {
	for (size_t i = 0; i < _servers.size(); i++) {
		std::cout << "************************ Server " << i + 1 << " ************************" << std::endl;
		_servers[i]->display();
	}
}

void WebServ::setup() {
	std::vector<Server *>::const_iterator it = _servers.begin();
	for (it =  _servers.begin(); it <  _servers.end(); it++) {
		// std::map<int, std::string>::const_iterator m_it = (*it)->getListen().begin() //segfault
		std::map<int, std::string> m = (*it)->getListen();
		std::map<int, std::string>::const_iterator m_it;
		for (m_it = m.begin(); m_it != m.end(); m_it++)
			(*it)->_sockets.push_back(new Socket(m_it->first, m_it->second));
	}
}

void WebServ::run() {
	fd_set read_fds;
	fd_set write_fds;
	int nfds;

	while (1) {
		nfds = prepare_sets(&read_fds, &write_fds);

		if ((select(nfds, &read_fds, &write_fds, NULL, NULL)) == -1)
			throw std::runtime_error("Selection Failed");

		prepare_clients(&read_fds, &write_fds);

		for (size_t i = 0; i < _servers.size(); i++) {
			for (size_t j = 0; j < _servers[i]->_clients.size(); j++) {
				if (FD_ISSET(_servers[i]->_clients[j]->_socket, &read_fds))
					Reading_Request(i, j, &read_fds);
				else if (FD_ISSET(_servers[i]->_clients[j]->_socket, &write_fds))
					Sending_Response(i, j);
			}
		}
	}
}

int WebServ::prepare_sets(fd_set *read, fd_set *write) {
	int cp = -1;

	FD_ZERO(read);
	FD_ZERO(write);

	for (size_t i = 0; i < _servers.size(); i++) {
		for (size_t j = 0; j < _servers[i]->_sockets.size(); j++) {
			FD_SET(_servers[i]->_sockets[j]->_socket, read);
			// FD_SET(_servers[i]->_sockets[j]->_socket, write);
			if (_servers[i]->_sockets[j]->_socket > cp)
				cp = _servers[i]->_sockets[j]->_socket;
		}
	}
	for (size_t i = 0; i < _servers.size(); i++) {
		for (size_t j = 0; j < _servers[i]->_clients.size(); j++) {
			FD_SET(_servers[i]->_clients[j]->_socket, read);
			FD_SET(_servers[i]->_clients[j]->_socket, write);
			if (_servers[i]->_clients[j]->_socket > cp)
				cp = _servers[i]->_clients[j]->_socket;
		}
	}
	return cp + 1;
}

void WebServ::prepare_clients(fd_set *read, fd_set *write) {
	int newSocket;
	struct sockaddr_in newAddress;
	int len = sizeof(newAddress);

	for (size_t i = 0; i < _servers.size(); i++) {
		for (size_t j = 0; j < _servers[i]->_sockets.size(); j++) {
			if (FD_ISSET(_servers[i]->_sockets[j]->_socket, read)) {
				if ((newSocket = accept(_servers[i]->_sockets[j]->_socket, (struct sockaddr *)&newAddress, (socklen_t *)&len)) == -1)
					throw std::runtime_error("Connection Refused");
				fcntl(newSocket, F_SETFL, O_NONBLOCK);
				_servers[i]->_clients.push_back(new Client(newSocket, newAddress));
				//std::cout << "[CLIENT] ==> " << inet_ntoa(newAddress.sin_addr) << ":" << ntohs(newAddress.sin_port) << " [PORT] ==> " << _sockets[i]->_port << std::endl;
			}
		}
	}

}

void WebServ::Reading_Request(int i, int j, fd_set *read) {
	int val;
	char buff[30000];

	if ((val = recv(_servers[i]->_clients[j]->_socket, buff, 30000, 0)) > 0) {
		buff[val] = 0;
		_servers[i]->_clients[j]->_request->parse(buff);
		_servers[i]->_clients[j]->_request->display();
	}
}

void WebServ::Sending_Response(int i, int j) {
	if (send(_servers[i]->_clients[j]->_socket, "HTTP/1.1 200 OK\r, Content-Type: text/html\r\n\r Hello World\r\n", 50, 0) == -1)
		throw std::runtime_error("Send Failed");
}