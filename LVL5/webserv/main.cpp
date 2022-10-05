/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:48:32 by hdrabi            #+#    #+#             */
/*   Updated: 2022/10/03 14:07:44 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

std::vector<std::string> _directives;

void init_directive() {
	_directives.push_back("server");
	_directives.push_back("SERVER");
	_directives.push_back("listen");
	_directives.push_back("server_name");
	_directives.push_back("root");
	_directives.push_back("index");
	_directives.push_back("autoindex");
	_directives.push_back("client_max_body_size");
	_directives.push_back("error_page");
	_directives.push_back("upload_path");
	_directives.push_back("methods");
	_directives.push_back("location");
	_directives.push_back("return");
}

int main(int ac, char *av[]) {

	try
	{
		if (ac != 2)
			throw std::runtime_error("./WebServ *.conf");
		std::string configFile = av[1];
		if (configFile.find(".conf", configFile.length() - 5) == std::string::npos)
			throw std::runtime_error("configFile extension error");
		init_directive();
		WebServ server = WebServ(configFile);
		server.setup();
		server.run();
		// server.display();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}


}