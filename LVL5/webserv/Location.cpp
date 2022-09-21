/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:30:57 by hdrabi            #+#    #+#             */
/*   Updated: 2022/09/21 15:31:30 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"

Location::Location(/* args */) {

}

Location::Location(std::string& location) {
	_path = get_value(location, "location ");
	_path = _path.substr(0, _path.find('\n'));
	_root = get_value(location, "\nroot ");
	_index = get_value(location, "\nindex ");
	_autoIndex = get_value(location, "\nautoindex ");
	_uploadPath = get_value(location, "\nupload_path ");
	int i = 0;
	while ((i = location.find("\nerror_page ", i)) != std::string::npos) {
		std::string _error = get_value(location, "\nerror_page ", i);
		_error = trim(_error);
		int code = std::stoi(_error.substr(0, _error.find(' ')));
		std::string path = _error.substr(_error.find(' ') + 1, _error.length());
		if (_errorPages.find(code) != _errorPages.end())
			throw std::logic_error("duplicate error code");
		_errorPages[code] = path;
		i++;
	}
	_methods = decipherMethods(get_value(location, "\nmethods "));
	std::string tmp = get_value(location, "\nredirection ");
	if (!tmp.empty()) {
		_redirection.first = tmp.substr(0, tmp.find(' '));
		_redirection.second = std::stoi(tmp.substr(tmp.find(' '), tmp.length() - 1));
	}
}

Location::Location(const Location& other) {

}

Location &Location::operator=(const Location& other) {

	return *this;
}

Location::~Location() {

}

void Location::display() const {
	_path != "" && std::cout << "\tPath: " << _path << std::endl;
	_root != "" && std::cout << "\troot: " << _root << std::endl;
	_index != "" && std::cout << "\tindex: " << _index << std::endl;
	_autoIndex != "" && std::cout << "\tautoindex: " << _autoIndex << std::endl;
	_uploadPath != "" && std::cout << "\tupload_path: " << _uploadPath << std::endl;
	_errorPages.size() != 0 && std::cout << "\tErrorPages: " << std::endl;
	std::map<int, std::string>::const_iterator it ;
    for (it = _errorPages.begin(); it != _errorPages.end(); it++)
		it->second != "" && std::cout << "\t\t" << it->first << " " << it->second << std::endl;
	_methods != "" && std::cout << "\tmethods: " << _methods << std::endl;
	_redirection.first != "" && std::cout << "\tredirection: " << _redirection.first << " " << _redirection.second << std::endl;
}
