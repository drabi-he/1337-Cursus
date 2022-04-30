/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:51:50 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/30 00:48:26 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed(){
	std::cout << "\033[1m\033[32m" << "Default constructor called" << "\033[0m" << std::endl;
	this->n = 0;
}

Fixed::Fixed(const Fixed &F){
	std::cout << "\033[1m\033[32m" << "Copy constructor called" << "\033[0m" << std::endl;
	*this = F;
}

Fixed & Fixed::operator = (const Fixed &F){
	if (this != &F)
	{
		std::cout << "\033[1m\033[32m" << "Copy assignment constructor called" << "\033[0m" << std::endl;
		this->n = F.getRawBits();
	}
	return *this;
}

Fixed::~Fixed(){
	std::cout << "\033[1m\033[31m" << "Destructor called" << "\033[0m" << std::endl;
}

int Fixed::getRawBits() const {
	std::cout << "\033[1m\033[33m" << "getRawBits member function called" << "\033[0m" << std::endl;
	return this->n;
}

void Fixed::setRawBits(int const raw){
	this->n = raw;
}