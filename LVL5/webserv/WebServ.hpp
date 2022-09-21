/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:35:58 by hdrabi            #+#    #+#             */
/*   Updated: 2022/09/21 11:58:36 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include "Server.hpp"
#include "utils.hpp"

class WebServ
{
	private:
		std::vector<Server *> _servers;
		void init_servers(std::string& str);

	public:
		WebServ(/* args */);
		WebServ(std::string& configFile);
		WebServ(const WebServ& other);
		WebServ operator=(const WebServ& other);
		~WebServ();
		void display() const;
};

#endif