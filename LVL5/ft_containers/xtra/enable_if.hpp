/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:12:13 by hdrabi            #+#    #+#             */
/*   Updated: 2022/10/31 16:05:22 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

# include <iostream>
# include <string>

namespace ft{

	template < bool Cond, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if <true, T> {typedef T type; };
}

#endif