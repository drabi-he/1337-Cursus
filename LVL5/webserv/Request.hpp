/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouf <izouf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:35:28 by hdrabi            #+#    #+#             */
/*   Updated: 2023/01/23 14:33:12 by izouf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP




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
#include "Client.hpp"
#include "Response.hpp"
#include "Socket.hpp"
#include "utils.hpp"

class WebServ;
class Server;
class Location;
class Client;
class Response;
class Socket;

class Request
{
	public:
		bool _isReady;
		std::string _rawRequest;
		std::map<std::string, std::string> _headers;
		std::string _method;
		std::string _uri;
		std::string _version;
		std::string _body;
		std::string _root;
		std::pair<bool, std::string> _isDirectory;
		std::pair<bool, std::string> _index;
		int _status;
		std::string _cgiport;
		std::string _query;
		std::string _reminder;
		Location *_location;
		int _chunked;
		std::string _remotAddr;
		std::string _path_o;

	public:
		Request();
		~Request();
		void parseRequest(std::string request, Client *client, Server *server);
		void headers_init();
		void checkHeaders();
		void reset();
		int check_headers(std::string line, Server *server, Client *client);
		void display();
};

#endif