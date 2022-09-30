/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 10:49:53 by hdrabi            #+#    #+#             */
/*   Updated: 2022/09/30 14:15:59 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

Socket::Socket(int port, std::string host) {
	int op = 1;
	_address.sin_family = AF_INET;
	_address.sin_port = htons(port);
	// _address.sin_addr.s_addr = htonl(inet_addr(host == "localhost" ? "127.0.0.1" : host.c_str()));
	_address.sin_addr.s_addr = htonl(INADDR_ANY);

	if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw std::runtime_error("Socket Creation Failed");

	if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &op, sizeof(int)) == -1)
		throw std::runtime_error("Option Set Failed");

	if (bind(_socket, (struct sockaddr *)&_address, sizeof(_address)) == -1)
		throw std::runtime_error("Socket Binding Failed");

	if (listen(_socket, SOMAXCONN) == -1)
		throw std::runtime_error("Listening Failed");

	fcntl(_socket, F_SETFL, O_NONBLOCK);

	std::cout << "listening on 127.0.0.1:" << port << std::endl;
}

Socket::~Socket() {
}