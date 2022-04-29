/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:51:50 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/29 15:41:26 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed(){
	std::cout << "Default constructor called" << std::endl;
	this->n = 0;
}

Fixed::Fixed(const int nb){
	std::cout << "Int constructor called" << std::endl;
	this->n = nb * (1 << this->fb);
}

Fixed::Fixed(const float nb){
	std::cout << "Float constructor called" << std::endl;
	this->n = (int)(roundf(nb * (1 << this->fb)));
}

Fixed::Fixed(const Fixed &F){
	std::cout << "Copy constructor called" << std::endl;
	*this = F;
}

Fixed & Fixed::operator = (const Fixed &F){
	if (this != &F)
	{
		std::cout << "Copy assignment constructor called" << std::endl;
		this->n = F.getRawBits();
	}
	return *this;
}

Fixed::~Fixed(){
	std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits() const {
	return this->n;
}

void Fixed::setRawBits(int const raw){
	this->n = raw;
}

float Fixed::toFloat( void ) const {
	return ((double)this->n / (double)(1 << this->fb));
}

int Fixed::toInt( void ) const {
	return (this->n / (1 << this->fb));
}

std::ostream & operator<<(std::ostream &out, const Fixed &F){
	out << F.toFloat();
	return out;
}