/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:36:01 by hdrabi            #+#    #+#             */
/*   Updated: 2022/09/30 14:13:41 by hdrabi           ###   ########.fr       */
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
	std::vector<Server *>::const_iterator it;
	for (it = _servers.begin(); it < _servers.end(); it++) {
		std::map<int, std::string>::const_iterator m_it = (*it)->getListen().begin();
		_sockets.push_back(new Socket(m_it->first, m_it->second));
	}
}