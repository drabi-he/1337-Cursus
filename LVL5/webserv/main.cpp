/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:48:32 by hdrabi            #+#    #+#             */
/*   Updated: 2022/09/21 11:59:59 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

int main(int ac, char *av[]) {

	try
	{
		if (ac != 2)
			throw std::runtime_error("./WebServ *.conf");
		std::string configFile = av[1];
		if (configFile.find(".conf", configFile.length() - 5) == std::string::npos)
			throw std::runtime_error("config file extension error");
		WebServ server = WebServ(configFile);
		server.display();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}


}