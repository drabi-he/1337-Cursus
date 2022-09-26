/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:59:51 by hdrabi            #+#    #+#             */
/*   Updated: 2022/09/26 18:11:12 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

std::string trim(std::string& str, std::string delimiter) {
	// remove comments
	int k = str.find("#");
	if (k != std::string::npos)
		str.erase(k, str.length());
	// trim spaces and tabs
	int i = 0;
	int j = str.length() - 1;
	while (delimiter.find(str[i]) != std::string::npos)
		i++;
	while (delimiter.find(str[j]) != std::string::npos){
		j--;
	}
	str.erase(j + 1, str.length());
	str.erase(0, i);
	return str;
}

bool check_brackets(std::string& str) {
	int i = 0;
	int cp = 0;

	while (str[i]) {
		if (str[i] == '{') {

			cp++;
		}
		if (str[i] == '}') {

			cp--;
		}
		if (cp < 0)
			return false;
		i++;
	}
	if (cp != 0)
		return false;
	return true;
}

std::string get_value(std::string str, std::string key, int dup, int k)
{
    int i = str.find(key , k);

    if (i == std::string::npos)
        return "";

    int j = str.find(';', i);

    std::string value = str.substr(i + key.size(), j - i - key.size());
    i = str.find(key , j);
    if (i != std::string::npos && !dup)
        throw std::runtime_error("configFile error, {duplicate directive : " + key.substr(1, key.length() - 2) + "}");
	value = trim(value);
	if (value.empty())
		throw std::runtime_error("configFile error, missing arguments for directive '" + key.substr(1, key.length() - 2) + "'");
    return value;
}

std::string decipherMethods(std::vector<std::string> methods)
{
	std::string result = "0000";
	std::string tmp[4] = {"GET", "POST", "PUT", "DELETE"};

	for (std::vector<std::string>::iterator it = methods.begin() ; it < methods.end() ; it++)
	{
		int i = 0;
		for (i = 0; i < 4; i++) {
			if (*it == tmp[i]) {
				result[i] = '1';
				break;
			}
		}
		if (i == 4) {
			throw std::runtime_error("configFile error, unknown method found");
		}
	}
	return result;
}

void check_line(std::string line) {
	int i;
	std::string rst;

	if (line.empty())
		return ;
	if (line[0] == '{' || line[0] == '}') {
		if (line.length() == 1)
			return ;
		else
			throw std::runtime_error("configFile error, near '" + line + "'");
	}
	i = line.find(' ');
	if (i == std::string::npos) {
		if (line != "SERVER" && line != "server" && line.length() != 1)
			throw std::runtime_error("configFile error, near 'server' directive");
	} else {
		rst = line.substr(0, i);
		std::vector<std::string>::iterator it;
		it = std::find(_directives.begin(), _directives.end(), rst);
		if (it == _directives.end())
			throw std::runtime_error("configFile error, directive '" + rst + "' doesn't exist");
		if (line.back() != ';') {
			if (rst != "location" && rst != "server" && rst != "SERVER")
				throw std::runtime_error("configFile error, missing ';' near directive '" + rst + "'");
		} else {
			if (rst == "location" || rst == "server" || rst == "SERVER")
				throw std::runtime_error("configFile error, ';' near directive '" + rst + "'");
		}
	}
}