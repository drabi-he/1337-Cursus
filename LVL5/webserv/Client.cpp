/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:17:17 by hdrabi            #+#    #+#             */
/*   Updated: 2022/10/06 12:24:17 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"


Client::Client(int socket, struct sockaddr_in address) : _request(new Request()) {
	_socket = socket;
	_address = address;
}

Client::~Client()
{
}