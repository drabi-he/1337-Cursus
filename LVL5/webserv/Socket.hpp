/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:25:33 by hdrabi            #+#    #+#             */
/*   Updated: 2022/10/27 15:32:09 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <vector>
#include <fstream>
#include "WebServ.hpp"
#include "Server.hpp"
#include "Location.hpp"
#include "Client.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "utils.hpp"

class WebServ;
class Server;
class Location;
class Client;
class Request;
class Response;

class Socket
{
	public:
		int _socket;
		int _port;
		std::string _host;
		struct sockaddr_in _address;

	public:
		Socket(int port, std::string host);
		~Socket();
};

#endif

