/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:32:49 by hdrabi            #+#    #+#             */
/*   Updated: 2022/10/27 16:47:01 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
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
#include "Location.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Socket.hpp"
#include "utils.hpp"

class WebServ;
class Server;
class Location;
class Request;
class Response;
class Socket;

class Client
{
	public:
		Request *_request;
		Response *_response;
		int _socket;
		struct sockaddr_in _addr;

	public:
		Client(int socket, struct sockaddr_in addr);
		~Client();
};

#endif