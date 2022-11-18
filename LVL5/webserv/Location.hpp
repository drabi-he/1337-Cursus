/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:28:19 by hdrabi            #+#    #+#             */
/*   Updated: 2022/10/04 15:36:31 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <unistd.h>
#include "utils.hpp"
#include "utils2.hpp"

#define GET 0
#define POST 1
#define PUT 2
#define DELETE 3

class Location
{
	public:
		std::string _path;
		std::string _root;
		std::vector<std::string> _index;
		std::string _autoIndex;
		std::string _uploadPath;
		std::map<int, std::string> _errorPages;
		std::map<int, int> _errorCodes;
		std::string _methods;
		std::pair<int, std::string> _return;

	public:
		Location(std::string& location);
		~Location();
		void display() const;
};

#endif