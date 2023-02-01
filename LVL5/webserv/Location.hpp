/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:22:00 by hdrabi            #+#    #+#             */
/*   Updated: 2022/10/27 15:50:24 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
#define LOCATION_HPP

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
#include "Server.hpp"
#include "Client.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Socket.hpp"
#include "utils.hpp"

class WebServ;
class Server;
class Client;
class Request;
class Response;
class Socket;

class Location
{
	public:
		std::string _path;
		std::string _root;
		std::vector<std::string> _index;
		std::string _autoIndex;
		std::string _uploadPath;
		std::map<int , std::string> _errorPages;
		std::map<int , int> _errorCodes;
		std::string _methods;
		std::pair<int, std::string> _return;
		std::vector< std::pair <std::string, std::string> > _cgi;
		std::string _cgiBin;

	public:
		Location();
		Location(std::string config);
		~Location();
		void display() const;
};

#endif