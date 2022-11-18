/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:17:44 by hdrabi            #+#    #+#             */
/*   Updated: 2022/10/08 11:38:09 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <vector>
#include <map>
#include "Location.hpp"
#include "Socket.hpp"
#include "Client.hpp"

class Server
{
	public:
		std::map<int, std::string> _listen;
		std::vector<std::string> _serverName;
		std::string _root;
		std::vector<std::string> _index;
		std::string _autoIndex;
		std::string _uploadPath;
		std::string _clientMaxBodySize;
		std::map<int, std::string> _errorPages;
		std::map<int, int> _errorCodes;
		std::string _methods;
		std::vector<Location *> _locations;
		std::vector<Socket *> _sockets;
		std::vector<Client *> _clients;
		std::string init_locations(std::string str);

	public:
		Server(std::string& config);
		~Server();
		void display() const;
		int getPort() const;
		std::map<int , std::string> getListen() const;
};

#endif