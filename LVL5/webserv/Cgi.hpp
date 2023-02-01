/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouf <izouf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:50:16 by izouf             #+#    #+#             */
/*   Updated: 2023/01/31 16:39:29 by izouf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <stdlib.h>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#include "WebServ.hpp"
#include "Server.hpp"
#include "Location.hpp"
#include "Client.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Socket.hpp"
# define BUFFER_SIZE	4096

class WebServ;
class Server;
class Location;
class Client;
class Request;
class Response;
class Socket;

class Cgi
{
	public:

		Cgi(Request *request, std::string path);
		Cgi(Cgi const &src);
		virtual ~Cgi();

		Cgi	&operator=(const Cgi &copy);

		std::string	execute(std::string path);

	private:

		std::map<std::string, std::string>					_env;
		std::string											_path;
		std::string											_body;
		std::vector<std::pair<std::string, std::string> >	_exec;
		std::string											_cgi;
		char												*_args[3];
		void		initCgi(Request *request);
		char		**maptotab();
};