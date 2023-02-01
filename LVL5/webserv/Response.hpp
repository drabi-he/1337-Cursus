/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouf <izouf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:36:24 by hdrabi            #+#    #+#             */
/*   Updated: 2023/01/23 14:29:34 by izouf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

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
# include "WebServ.hpp"
# include "Server.hpp"
# include "Location.hpp"
# include "Client.hpp"
# include "Request.hpp"
#include "Socket.hpp"
# include "Cgi.hpp"
# include "utils.hpp"

class WebServ;
class Server;
class Location;
class Client;
class Request;
class Socket;
class Cgi;

class Response
{
	public:
		std::string _content;
		std::string _response;
		Location* _location;
		std::string _content_type;
		bool isSend;
		std::string _cookie;



	public:
		Response();
		void handelError(Client *client, Server *server);
		void handelRequest(Client *client);
		void defineContentType(Client *client);
		void reset();
		std::string createErrorPage2(Client *client);
		void parse_cgi(Client *client, std::string body);
		~Response();
};

#endif