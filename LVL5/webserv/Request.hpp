/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:30:04 by hdrabi            #+#    #+#             */
/*   Updated: 2022/10/06 17:26:01 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <sstream>
#include <map>

class Request
{
	public:
		std::map<std::string, std::string> _headers;
		std::string _type;
		std::string _path;
		std::string _body;
	public:
		Request(/* args */);
		void parse(std::string req);
		void display();
		~Request();
};



#endif