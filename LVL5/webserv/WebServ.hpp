/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:35:58 by hdrabi            #+#    #+#             */
/*   Updated: 2022/10/04 13:21:45 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include "Server.hpp"
#include "Socket.hpp"
#include "Client.hpp"

class WebServ
{
	public:
		std::vector<Server *> _servers;
		std::vector<Socket *> _sockets;
		std::vector<Client *> _clients;
		void init_servers(std::string& str);

	public:
		WebServ(std::string& configFile);
		~WebServ();
		void setup();
		void run();
		int prepare_sets(fd_set *read, fd_set *write);
		void prepare_clients(fd_set *read, fd_set *write);
		void display() const;
};

#endif