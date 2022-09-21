/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:59:51 by hdrabi            #+#    #+#             */
/*   Updated: 2022/09/21 14:39:55 by hdrabi           ###   ########.fr       */
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

std::string get_value(std::string str, std::string key , int k)
{
    int i = str.find(key , k);

    if (i == std::string::npos)
        return "";

    int j = str.find(';', i);

    std::string value = str.substr(i + key.size(), j - i - key.size());
    i = str.find(key , j);
    if (i != std::string::npos && key != "\nerror_page ")
        throw std::runtime_error("Syntax error in config file {duplicate key : " + key + "}");
    return trim(value);
}

std::string decipherMethods(std::string methods)
{
    std::string result = "";
	int i = 0;
    if ((i = methods.find("GET")) != std::string::npos) {
		methods.erase(i, 3);
        result += "1";
	}
    else
        result += "0";
    if ((i = methods.find("POST")) != std::string::npos) {
		methods.erase(i, 4);
        result += "1";
	}
    else
        result += "0";
    if ((i = methods.find("PUT")) != std::string::npos) {
		methods.erase(i, 3);
        result += "1";
	}
    else
        result += "0";
    if ((i = methods.find("DELETE")) != std::string::npos) {
		methods.erase(i, 6);
        result += "1";
	}
    else
        result += "0";
	methods = trim(methods);
	if (!methods.empty())
		throw std::logic_error("methods format error");
    return result;
}