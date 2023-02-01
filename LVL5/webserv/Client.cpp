/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:35:05 by hdrabi            #+#    #+#             */
/*   Updated: 2022/10/27 16:53:51 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int socket, struct sockaddr_in addr) : _request(new Request()), _response(new Response()) {
    _socket = socket;
    _addr = addr;
}

Client::~Client()
{
    delete _request;
    delete _response;
}