/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:17:24 by hdrabi            #+#    #+#             */
/*   Updated: 2022/10/04 15:35:31 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "utils.hpp"
#include "utils2.hpp"

class Client
{
	public:
		int _socket;
		struct sockaddr_in _address;
	public:
		Client(int socket, struct sockaddr_in address);
		~Client();
};


#endif