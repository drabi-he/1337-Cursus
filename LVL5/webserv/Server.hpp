/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:49:43 by hdrabi            #+#    #+#             */
/*   Updated: 2022/10/27 15:50:12 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "WebServ.hpp"
#include "Location.hpp"
#include "Client.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Socket.hpp"
#include "utils.hpp"

class WebServ;
class Location;
class Client;
class Request;
class Response;
class Socket;

class Server
{
	public:
		std::map<int , std::string> _listen;
		std::vector<std::string> _serverName;
		std::string _root;
		std::vector<std::string> _index;
		std::string _autoIndex;
		std::string _uploadPath;
		std::vector< std::pair <std::string, std::string> > _cgi;
		std::string _cgiBin;
		std::map<int , std::string> _errorPages;
		std::map<int , int> _errorCodes;
		std::string _clientMaxBodySize;
		std::string _methods;
		std::pair<int, std::string> _return;
		std::vector<Location *> _locations;
		std::vector<Socket *> _sockets;
		std::vector<Client *> _clients;
		std::string init_locations(std::string config);

	public:
		Server(std::string config);
		~Server();
		void display() const;
};

#endif