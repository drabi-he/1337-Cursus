/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:48:04 by hdrabi            #+#    #+#             */
/*   Updated: 2022/09/26 14:19:17 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS2_HPP
#define UTILS2_HPP

#include <iostream>
#include <vector>
#include "utils.hpp"

int get_port(std::string listen);
std::string get_host(std::string listen);
std::vector<std::string> split_vec(std::string str);

#endif