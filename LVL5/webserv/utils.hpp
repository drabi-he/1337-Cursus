/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:59:17 by hdrabi            #+#    #+#             */
/*   Updated: 2022/09/21 14:09:39 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>

std::string trim(std::string& str, std::string delimiter = " \t\n");
bool check_brackets(std::string& str);
std::string get_value(std::string str, std::string key , int k = 0);
std::string decipherMethods(std::string methods);

#endif