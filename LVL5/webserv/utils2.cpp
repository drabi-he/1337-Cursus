/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:48:33 by hdrabi            #+#    #+#             */
/*   Updated: 2022/09/27 12:08:25 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils2.hpp"

int get_port(std::string listen) {
	size_t i = 0;
	std::string rst = listen;

	i = listen.find(':');
	if (i != std::string::npos)
		rst = listen.substr(i + 1, listen.length());
	if (rst.empty())
		throw std::runtime_error("configFile error, please check your port");
	for (size_t j = 0; j < rst.length() ; j++) {
		if (!std::isdigit(rst[j])) {
			if (i != std::string::npos)
				throw std::runtime_error("configFile error, wrong port format");
			else
				return 80;
		}
	}
	i = std::stoi(rst);
	if (i < 1 || i > 65535)
		throw std::runtime_error("configFile error, port value is out of range");
	return i;
}

std::string get_host(std::string listen) {
	size_t i = 0;
	std::string rst = listen;

	i = listen.find(':');
	if (i != std::string::npos)
		rst = listen.substr(0, i);
	for (size_t j = 0; j < rst.length() ; j++) {
		if (!std::isdigit(rst[j])) {
				return rst;
		}
	}

	return "127.0.0.1";
}

std::vector<std::string> split_vec(std::string str) {
	size_t i = 0;
	std::vector<std::string> vec;
	std::string rst;

	while ((i = str.find(' ')) != std::string::npos) {
		rst = str.substr(0, i);
		rst = trim(rst);
		str.erase(0, i);
		str = trim(str);
		if (!rst.empty())
			vec.push_back(rst);
	}
	if (!str.empty())
		vec.push_back(trim(str));

	return vec;
}