/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:30:57 by hdrabi            #+#    #+#             */
/*   Updated: 2022/09/27 12:09:11 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"

Location::Location(std::string& location) {
	_path = get_value(location, "location ", 0);
	_path = _path.substr(0, _path.find('{'));
	_path = trim(_path);
	if (_path.empty() || _path.find(' ') != std::string::npos)
		throw std::runtime_error("configFile error, wrong number of arguments for directive 'location'");

	_root = get_value(location, "\nroot ", 0);
	if (_root.find(' ') != std::string::npos)
		throw std::runtime_error("configFile error, wrong number of arguments for directive 'root'");

	size_t i = 0;
	while ((i = location.find("\nindex ", i)) != std::string::npos) {
		std::string index = get_value(location, "\nindex ", 1, i);
		index = trim(index);
		std::vector<std::string> tmp = split_vec(index);
		_index.insert(_index.end(), tmp.begin(), tmp.end());
		i++;
	}
	if (_index.size() == 0)
		_index.push_back("index.html");

	_autoIndex = get_value(location, "\nautoindex ", 0);
	if (_autoIndex == "")
		_autoIndex = "off";
	else
		if (_autoIndex != "on" && _autoIndex != "off")
			throw std::runtime_error("configFile error, undefined autoindex value");

	_uploadPath = get_value(location, "\nupload_path " , 0);
	if (_uploadPath.find(' ') != std::string::npos)
		throw std::runtime_error("configFile error, wrong number of arguments for directive 'upload_path'");

	i = 0;
	while ((i = location.find("\nerror_page ", i)) != std::string::npos) {
		std::string _error = get_value(location, "\nerror_page ", 1, i);
		_error = trim(_error);
		std::vector<std::string> codes = split_vec(_error.substr(0, _error.find_last_of(' ')));
		std::string path = _error.substr(_error.find_last_of(' ') + 1, _error.length());
		int newCode = -1;
		for (std::vector<std::string>::const_iterator it = codes.begin() ; it != codes.end(); it++) {
			for (size_t j = 0; j < (*it).length(); j++) {
				if (!std::isdigit((*it)[j])) {
					if (j != 0 || (*it)[j] != '=' || (it != (codes.end() - 1))){
						throw std::runtime_error("configFile error, wrong format for directive 'error_page'");
					}
				}
			}
			if ((*it)[0] == '=') {
				newCode = std::stoi((*it).substr(1, (*it).length()));
				codes.erase(it);
				break ;
			}
		}
		for (std::vector<std::string>::const_iterator it = codes.begin() ; it != codes.end(); it++) {
			if (_errorPages.find(std::stoi(*it)) == _errorPages.end()) {
				int code = std::stoi(*it);
				if (code < 300 || code > 599)
					throw std::runtime_error("configFile error, error_page value is out of range");
				_errorPages[code] = path;
				_errorCodes[code] = newCode;
			}
		}
		i++;
	}

	_methods = get_value(location, "\nmethods ", 0);
	_methods = decipherMethods(split_vec(_methods));
	std::string tmp = get_value(location, "\nreturn ", 0);
	if (!tmp.empty()) {
		_return.second = tmp.substr(tmp.find(' '), tmp.length() - 1);
		std::string code = tmp.substr(0, tmp.find(' '));
		for (size_t j = 0; j < code.length(); j++)
			if (!std::isdigit(code[j]))
				throw std::runtime_error("configFile error, return value should be a status code");
		_return.first = std::stoi(code);
	}
}

Location::~Location() {

}

void Location::display() const {
	_path != "" && std::cout << "\tPath: " << _path << std::endl;

	_root != "" && std::cout << "\troot: " << _root << std::endl;

	_index.size() != 0 && std::cout << "\tindex: " << std::endl;
    for (std::vector<std::string>::const_iterator it = _index.begin() ; it != _index.end(); it++)
		std::cout << "\t\t" << *it << std::endl;

	_autoIndex != "" && std::cout << "\tautoindex: " << _autoIndex << std::endl;
	_uploadPath != "" && std::cout << "\tupload_path: " << _uploadPath << std::endl;
	std::map<int, std::string>::const_iterator it ;
	_errorPages.size() != 0 && std::cout << "\tErrorPages: " << std::endl;
    for (it = _errorPages.begin(); it != _errorPages.end(); it++)
		it->second != "" && std::cout << "\t\t" << it->first << " " << it->second << "\t=" << _errorCodes.find(it->first)->second <<  std::endl;
	_methods != "" && std::cout << "\tmethods: " << _methods << std::endl;
	_return.second != "" && std::cout << "\tredirection: " << _return.first << " " << _return.second << std::endl;
}
