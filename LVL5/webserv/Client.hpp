/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:17:24 by hdrabi            #+#    #+#             */
/*   Updated: 2022/10/06 12:23:53 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Request.hpp"
#include "utils.hpp"
#include "utils2.hpp"

class Client
{
	public:
		int _socket;
		struct sockaddr_in _address;
		Request *_request;
	public:
		Client(int socket, struct sockaddr_in address);
		~Client();
};


#endif