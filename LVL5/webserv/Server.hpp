/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:17:44 by hdrabi            #+#    #+#             */
/*   Updated: 2022/09/21 13:30:29 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <vector>
#include <map>
#include "Location.hpp"
#include "utils.hpp"

class Server
{
	private:
		std::string _host;
		std::string _port;
		std::string _serverName;
		std::string _autoIndex;
		std::string _index;
		std::string _root;
		std::string _uploadPath;
		std::string _clientBodySizeLimit;
		std::map<int, std::string> _errorPages;
		std::string _methods;
		std::vector<Location *> _locations;
		std::string init_locations(std::string str);

	public:
		Server();
		Server(std::string& config);
		Server(const Server& other);
		Server &operator=(const Server& other);
		~Server();
		void display() const;
};

#endif