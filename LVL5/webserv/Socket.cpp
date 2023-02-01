/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:31:41 by hdrabi            #+#    #+#             */
/*   Updated: 2022/10/27 16:41:59 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

Socket::Socket(int port, std::string host) {
	int opt = 1;

	_port = port;
	_host = host;



	if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw std::runtime_error("Error: Socket creation failed");

	fcntl(_socket, F_SETFL, O_NONBLOCK);

	if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		throw std::runtime_error("Error: Socket setsockopt failed");


	if (host == "0.0.0.0")
		_address.sin_addr.s_addr = INADDR_ANY;
	else if (host == "127.0.0.1" || host == "localhost")
		_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	else
		_address.sin_addr.s_addr = inet_addr(_host.c_str());
	_address.sin_family = AF_INET;
	_address.sin_port = htons(_port);

	if (bind(_socket, (struct sockaddr *)&_address, sizeof(_address)) == -1)
		throw std::runtime_error("Error: Socket bind failed");

	if (listen(_socket, SOMAXCONN) == -1)
		throw std::runtime_error("Error: Socket listen failed");

	std::cout << "listening on 0.0.0.0:" << port << std::endl;
}

Socket::~Socket()
{
}