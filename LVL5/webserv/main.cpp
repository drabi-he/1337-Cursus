/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:47:40 by hdrabi            #+#    #+#             */
/*   Updated: 2022/10/29 15:17:38 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

std::vector<std::string> _directives;
std::map<int, std::string> _statusCodes;
std::map<std::string, std::string> _mimeTypes;

void init_directives() {
	_directives.push_back("server");
	_directives.push_back("listen");
	_directives.push_back("server_name");
	_directives.push_back("root");
	_directives.push_back("index");
	_directives.push_back("autoindex");
	_directives.push_back("client_max_body_size");
	_directives.push_back("error_page");
	_directives.push_back("location");
	_directives.push_back("upload_path");
	_directives.push_back("methods");
	_directives.push_back("return");
	_directives.push_back("cgi");
	_directives.push_back("cgi_bin");
}

void init_status() {
	_statusCodes[200] = "OK";
	_statusCodes[201] = "Created";
	_statusCodes[202] = "Accepted";
	_statusCodes[204] = "No Content";
	_statusCodes[301] = "Moved Permanently";
	_statusCodes[302] = "Found";
	_statusCodes[304] = "Not Modified";
	_statusCodes[400] = "Bad Request";
	_statusCodes[401] = "Unauthorized";
	_statusCodes[403] = "Forbidden";
	_statusCodes[404] = "Not Found";
	_statusCodes[405] = "Method Not Allowed";
	_statusCodes[406] = "Not Acceptable";
	_statusCodes[408] = "Request Timeout";
	_statusCodes[413] = "Payload Too Large";
	_statusCodes[414] = "URI Too Long";
	_statusCodes[415] = "Unsupported Media Type";
	_statusCodes[416] = "Range Not Satisfiable";
	_statusCodes[417] = "Expectation Failed";
	_statusCodes[418] = "I'm a teapot";
	_statusCodes[422] = "Unprocessable Entity";
	_statusCodes[426] = "Upgrade Required";
	_statusCodes[500] = "Internal Server Error";
	_statusCodes[501] = "Not Implemented";
	_statusCodes[502] = "Bad Gateway";
	_statusCodes[503] = "Service Unavailable";
	_statusCodes[504] = "Gateway Timeout";
	_statusCodes[505] = "HTTP Version Not Supported";
}

std::string get_config_file(int ac, char **av) {
	std::string configFile;

	if (ac == 1)
		configFile = "./assets/conf/default.conf";
	else if (ac == 2)
		configFile = av[1];
	else
		throw std::runtime_error("Error: Too many arguments");
	if (access(configFile.c_str(), F_OK) == -1)
		throw std::runtime_error("Error: Config file not found");
	if (access(configFile.c_str(), R_OK) == -1)
		throw std::runtime_error("Error: Config file not readable");
	if (configFile.find(".conf", configFile.length() - 5) == std::string::npos)
		throw std::runtime_error("Error: Invalid config file extension");

	return (configFile);
}

int main(int ac, char **av) {
	std::string configFile;

	try
	{
		configFile = get_config_file(ac, av);
		init_directives();
		init_status();
		WebServ server = WebServ(configFile);
		server.run();

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}