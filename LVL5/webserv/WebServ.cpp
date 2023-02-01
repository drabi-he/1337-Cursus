/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouf <izouf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:48:40 by hdrabi            #+#    #+#             */
/*   Updated: 2023/01/31 13:06:33 by izouf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServ.hpp"

WebServ::WebServ(std::string configFile) {
	std::ifstream config;
	std::string config_str;
	std::string line;
	int line_num = 0;

	config.open(configFile);
	if (!config.is_open())
		throw std::runtime_error("Error: Can't open config file");

	while (std::getline(config, line)) {
		line = trim(line);
		line_num++;

		check_line(line, line_num);

		if (!line.empty())
			config_str += line + "\n";
	}
	check_brackets(config_str);
	config_str = trim(config_str);
	init_servers(config_str);
}

WebServ::~WebServ() {
}

void WebServ::init_servers(std::string config) {
	size_t i = 0;
	std::string server_str;

	while (1) {
		i = config.find("server", i);
		if (i == std::string::npos)
			break;
		if (config[i + 6] != '{' && config[i + 6] != ' ' && config[i + 6] != '\n') {
			i++;
			continue;
		}

		server_str = config.substr(0, i);
		config.erase(0, i + 6);
		server_str = trim(server_str);
		if (!server_str.empty()) {
			if (server_str[0] != '{' || server_str[server_str.length() - 1] != '}')
				throw std::runtime_error("Error: Invalid config file: missing '{' or '}'");
			server_str.erase(0, 1);
			server_str.erase(server_str.length() - 1, server_str.length());
			server_str = trim(server_str);
			_servers.push_back(new Server(server_str));
		}
		i = 0;
	}
	config = trim(config);
	if (config[0] != '{' || config[config.length() - 1] != '}')
		throw std::runtime_error("Error: Invalid config file: missing '{' or '}'");
	config.erase(0, 1);
	config.erase(config.length() - 1, config.length());
	config = trim(config);
	_servers.push_back(new Server(config));
}

int WebServ::prepare_sets(fd_set *read_set, fd_set *write_set){
	int max = 0;

	FD_ZERO(read_set);
	FD_ZERO(write_set);

	for (size_t i = 0; i < _servers.size(); i++) {
		for (size_t j = 0; j < _servers[i]->_sockets.size(); j++) {
			FD_SET(_servers[i]->_sockets[j]->_socket, read_set);
			if (_servers[i]->_sockets[j]->_socket > max)
				max = _servers[i]->_sockets[j]->_socket;
		}
	}

	for (size_t i = 0; i < _servers.size(); i++) {
		for (size_t j = 0; j < _servers[i]->_clients.size(); j++) {
			FD_SET(_servers[i]->_clients[j]->_socket, read_set);
			FD_SET(_servers[i]->_clients[j]->_socket, write_set);
			if (_servers[i]->_clients[j]->_socket > max)
				max = _servers[i]->_clients[j]->_socket;
		}
	}

	return (max);
}

void WebServ::clients_setup(fd_set *read_set) {
	int client_socket;
	struct sockaddr_in client_addr;
	socklen_t client_addr_size = sizeof(client_addr);

	for (size_t i = 0; i < _servers.size(); i++) {
		for (size_t j = 0; j < _servers[i]->_sockets.size(); j++) {
			if (FD_ISSET(_servers[i]->_sockets[j]->_socket, read_set)) {
				if ((client_socket = accept(_servers[i]->_sockets[j]->_socket, (struct sockaddr *)&client_addr, &client_addr_size)) == -1)
					throw std::runtime_error("Error: Accept failed");
				fcntl(client_socket, F_SETFL, O_NONBLOCK);
				_servers[i]->_clients.push_back(new Client(client_socket, client_addr));
			}
		}
	}
}

void WebServ::verifyRequest(Client* client, int i) {
	Request *request = client->_request;
	Server *server = _servers[i];
	size_t k, cp = 0;
	size_t match = 0;
	int keep = -1;

	if (request->_status != 0)
		return;
	if (request->_version != "HTTP/1.1" && request->_version != "HTTP/1.0") {
		request->_status = 505;
		return;
	}

	for (k = 0; k < server->_locations.size(); k++) {
		if (request->_uri == server->_locations[k]->_path) {
			request->_location = server->_locations[k];
			cp++;
			break;
		} else if (request->_uri.find(server->_locations[k]->_path) == 0) {
			if (match < server->_locations[k]->_path.length()) {
				match = server->_locations[k]->_path.length();
				keep = k;
			}
			request->_location = server->_locations[k];
			cp++;
		}
	}
	if (keep != -1)
		request->_location = server->_locations[keep];

	if (request->_location->_return.second != "") {
		request->_status = request->_location->_return.first;
		request->_headers["Location"] = request->_location->_return.second;
		return;
	}


	request->_isDirectory = ft_isDirectory(server->_root, request->_location, request->_uri);

	if (!cp || request->_isDirectory.second == "") {
		request->_status = 404;
		return;
	}

	if (request->_isDirectory.first) {
		for (size_t i = 0; i < request->_location->_index.size(); i++) {
			request->_index = ft_isDirectory(request->_isDirectory.second, NULL, request->_location->_index[i]);
			if (request->_index.second != "")
				break;
		}
		if (request->_location->_autoIndex == "off" && request->_index.second == "") {
			request->_status = 404;
			return;
		} else
			request->_status = 200;
	}


	if ((request->_method == "GET" && request->_location->_methods[GET] == '0') || (request->_method == "POST" && request->_location->_methods[POST] == '0') || (request->_method == "DELETE" && request->_location->_methods[DELETE] == '0'))
	{
		request->_status = 405;
		return;
	}

	if (request->_method != "GET" && request->_method != "POST" && request->_method != "DELETE") {
		request->_status = 405;
		return;
	}

	if (request->_headers["Content-Length"] != "") {
		if (std::atol(request->_headers["Content-Length"].c_str()) > std::atol(server->_clientMaxBodySize.c_str())) {
			request->_status = 413;
			return;
		}
	}

	if (request->_headers["Host"] == "") {
		request->_status = 400;
		return;
	} else {
		std::string host = request->_headers["Host"];
		host = trim(host);
		if (host.find(" ") != std::string::npos) {
			request->_status = 400;
			return;
		}
	}


	if (request->_method != "POST") {
		request->_status = 200;
		return;
	} else {
		if (request->_headers["Content-Length"] == "") {
			request->_status = 411;
			return;
		}
		if (request->_headers["Content-Length"].find_first_not_of("0123456789") != std::string::npos) {
			request->_status = 400;
			return;
		}
		if (request->_body.length() > (size_t)atoi(request->_headers["Content-Length"].c_str())) {
			request->_body.erase(atoi(request->_headers["Content-Length"].c_str()));
			request->_status = 200;
			return;
		}
	}


}

void WebServ::parsUpload(Client* client, std::string body){
	if (body == "")
		return;

	body = body.substr(0, body.length() - 2);
	std::vector<std::string> content = split(body, "\r");
	if (content.size() <= 3){
		return;
	}

	std::string fileName = content[0].substr(content[0].find("filename=") + 9);
	fileName = trim(fileName, "\"\r\n");
	if (fileName.size() == 0)
		return;
	std::string filePath = client->_request->_location->_uploadPath + "/" + fileName;
	std::string filetoupload = body.substr(body.find("\r\n\r\n") + 4);
	std::ofstream file;
	file.open(filePath, std::ios::binary);
	if (!file.is_open())
		return;
	file << filetoupload;
	file.close();
	content.clear();
}

void WebServ::prepareResponse(Client* client, int i, int j) {
	if (client->_request->_status >= 400) {
		client->_response->handelError(client, _servers[i]);
	} else {
		if (client->_request->_method == "POST" && client->_request->_headers["Content-Type"].find("multipart/form-data") != std::string::npos && client->_request->_body != "")
		{
			std::string _boundary = "--";
			_boundary += _servers[i]->_clients[j]->_request->_headers["Content-Type"].substr(_servers[i]->_clients[j]->_request->_headers["Content-Type"].find("boundary=") + 9);
			std::vector<std::string> _body = split(_servers[i]->_clients[j]->_request->_body, _boundary);
			for (size_t i = 0; i < _body.size(); i++)
			{
				parsUpload(client, _body[i]);
			}
		}
		client->_response->handelRequest(client);
	}


}

void WebServ::print(std::string str) {
    int i = -1;

    while (str[++i]) {
        if (std::isprint(str[i]) && str[i] != '\n')
            std::cout << str[i];
        else
            std::cout << "|" << (int)str[i];
				if (str[i] == '\n')
					std::cout << std::endl;
    }
    std::cout << std::endl;
}

void WebServ::read_request(Client* client, int i, int j, Server* server) {
	int bytes_read;
	char buf[8000000];


	if ((bytes_read = read(client->_socket, buf, 8000000)) < 0) {
		close(client->_socket);
		delete _servers[i]->_clients[j];
		_servers[i]->_clients.erase(_servers[i]->_clients.begin() + j);
	}
	else if(bytes_read == 0){
		close(client->_socket);
		delete _servers[i]->_clients[j];
		_servers[i]->_clients.erase(_servers[i]->_clients.begin() + j);
	} else {
		buf[bytes_read] = '\0';
		client->_request->parseRequest(std::string(buf, bytes_read), client, server);
		if (parse_mime_types() == 0)
			getContentTypeFromMap(client);
		else
			client->_response->defineContentType(client);
		verifyRequest(client, i);
		if (client->_request->_status >= 400 || client->_request->_method == "GET" || client->_request->_method == "DELETE")
			client->_request->_isReady = true;
		if (client->_request->_method == "POST" && client->_request->_body.length() >= (size_t)atoi(client->_request->_headers["Content-Length"].c_str()))
			client->_request->_isReady = true;
		if (client->_request->_isReady)
			prepareResponse(client, i, j);
	}
}

std::string WebServ::create_response(Client* client) {
	std::string rst = "";
	std::string path = "";

	if (client->_request->_isDirectory.first) {
    if (client->_request->_index.second != "")
      path = client->_request->_index.second;
  } else {
    path = client->_request->_isDirectory.second;
  }

	rst += "HTTP/1.1 " + std::to_string(client->_request->_status) + " " + _statusCodes[client->_request->_status] + "\r\n";
	rst += "Server: WebServ\r\n";
	rst += "Date: " + getDate() + "\r\n";
	if (client->_request->_headers["Connection"] == "")
		rst += "Connection: keep-alive\r\n";
	else
		rst += "Connection: close\r\n";
	if (client->_request->_status == 301 || client->_request->_status == 302) {
		rst += "Location: " + client->_request->_headers["Location"] + "\r\n\r\n";
		rst += client->_request->_headers["Location"];
		return rst;
	}
	rst += client->_response->_cookie;
	rst += "Content-Type: " + client->_response->_content_type +"\r\n";
	rst += "Content-Length: " + std::to_string(client->_response->_content.length()) + "\r\n";
	rst += "\r\n";

	rst += client->_response->_content;
	return rst;
}

void WebServ::write_response(Client* client, int i, int j) {
	int ret;
	if (!client->_response->isSend){
		client->_response->_response = create_response(client);
		client->_response->isSend = true;
	}

	if (client->_response->_response.length() <= BUFF_SIZE)
		ret = send(client->_socket, client->_response->_response.c_str(), client->_response->_response.length(), 0);
	else
		ret = send(client->_socket, client->_response->_response.c_str(), BUFF_SIZE, 0);

	if (ret < 0) {
		close(client->_socket);
		delete client;
		_servers[i]->_clients.erase(_servers[i]->_clients.begin() + j);
		return ;
	}
	else if (ret == 0 | ret == (int)client->_response->_response.length()) {
		client->_response->_response = "";
		client->_response->isSend = false;
	}
	else
		client->_response->_response = client->_response->_response.substr(ret);

	if (!client->_response->isSend && (client->_request->_headers["Connection"] == "close" || client->_request->_status >= 400)) {
		close(client->_socket);
		delete client;
		_servers[i]->_clients.erase(_servers[i]->_clients.begin() + j);
	} else if (!client->_response->isSend) {
		client->_request->reset();
		client->_response->reset();
	}
}

void WebServ::run() {
	Client *client;
	fd_set read_set;
	fd_set write_set;
	std::map<int, std::string> ports;
	int nfds;

	for (size_t i = 0; i < _servers.size(); i++) {
		std::map<int, std::string>::const_iterator it = _servers[i]->_listen.begin();
		while (it != _servers[i]->_listen.end()) {
			if (ports.find(it->first) != ports.end()) {
				it++;
				continue;
			}
			_servers[i]->_sockets.push_back(new Socket(it->first, it->second));
			ports[it->first] = it->second;
			it++;
		}
	}

	while (1) {
		nfds = prepare_sets(&read_set, &write_set);

		if (select(nfds + 1, &read_set, &write_set, NULL, NULL) == -1)
			throw std::runtime_error("Error: Select failed");

		clients_setup(&read_set);

		for (size_t i = 0; i < _servers.size(); i++) {
			for (size_t j = 0; j < _servers[i]->_clients.size(); j++) {
				client = _servers[i]->_clients[j];

				if (!client->_request->_isReady && FD_ISSET(client->_socket, &read_set)) {
					read_request(client, i, j, _servers[i]);
				} else if (client->_request->_isReady && FD_ISSET(client->_socket, &write_set)) {
					write_response(client, i, j);
				}
			}
		}

	}
}


void WebServ::display() const {
	for (size_t i = 0; i < _servers.size(); i++) {
		std::cout << "************************ Server " << i + 1 << " ************************" << std::endl;
		_servers[i]->display();
	}
}