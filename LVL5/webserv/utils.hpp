/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:59:17 by hdrabi            #+#    #+#             */
/*   Updated: 2022/09/26 17:46:31 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>
#include <map>

extern std::vector<std::string> _directives;

std::string trim(std::string& str, std::string delimiter = " \t\n");
bool check_brackets(std::string& str);
std::string get_value(std::string str, std::string key, int dup, int k = 0);
std::string decipherMethods(std::vector<std::string> methods);
void check_line(std::string line);

#endif