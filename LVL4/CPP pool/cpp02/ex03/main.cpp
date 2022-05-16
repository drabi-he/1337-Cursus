/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:43:47 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/14 15:06:47 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include "Point.hpp"

int main( void ) {
	Point P(Fixed(6), Fixed(7));
	Point a;
	Point b(Fixed(10), Fixed(10));
	Point c(Fixed(20), Fixed(0));

	std::cout << (bsp(a, b, c, P) ? "P is inside abc" : " P is outside abc") << std::endl;
	return 0;
}