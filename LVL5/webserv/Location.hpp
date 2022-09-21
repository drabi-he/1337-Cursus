/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:28:19 by hdrabi            #+#    #+#             */
/*   Updated: 2022/09/21 14:52:11 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <map>
#include "utils.hpp"

#define GET 0
#define POST 1
#define PUT 2
#define DELETE 3

class Location
{
	private:
		std::string _path;
		std::string _root;
		std::string _index;
		std::string _autoIndex;
		std::string _uploadPath;
		std::map<int, std::string> _errorPages;
		std::pair<std::string, int> _redirection;
		std::string _methods;

	public:
		Location();
		Location(std::string& location);
		Location(const Location& other);
		Location &operator=(const Location& other);
		~Location();
		void display() const;
};

#endif