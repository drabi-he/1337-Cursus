/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouf <izouf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:48:37 by hdrabi            #+#    #+#             */
/*   Updated: 2023/01/31 12:51:38 by izouf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <vector>
#include <fstream>
#include "Server.hpp"
#include "Location.hpp"
#include "Client.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Socket.hpp"
#include "utils.hpp"

class Server;
class Location;
class Client;
class Request;
class Response;
class Socket;

class WebServ
{
	public:
		std::vector<Server *> _servers;
		void init_servers(std::string config);

	public:
		WebServ(std::string configFile);
		~WebServ();
		int prepare_sets(fd_set *read_set, fd_set *write_set);
		void clients_setup(fd_set *read_set);
		void read_request(Client* client, int i, int j, Server* server);
		void verifyRequest(Client* client, int i);
		void prepareResponse(Client* client, int i, int j);
		void write_response(Client* client, int i, int j);
		std::string create_response(Client* client);
		void parsUpload(Client* client, std::string body);
		void display() const;
		void print(std::string str) ;
		void run();
};

#endif