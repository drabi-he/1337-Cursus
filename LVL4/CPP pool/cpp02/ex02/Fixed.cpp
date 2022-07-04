/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:51:50 by hdrabi            #+#    #+#             */
/*   Updated: 2022/06/18 10:59:21 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed(){
	this->n = 0;
}

Fixed::Fixed(const int nb){
	this->n = nb * (1 << this->fb);
}

Fixed::Fixed(const float nb){
	this->n = (int)(roundf(nb * (1 << this->fb)));
}

Fixed::Fixed(const Fixed &F){
	*this = F;
}

Fixed & Fixed::operator = (const Fixed &F){
	if (this != &F)
	{
		this->n = F.getRawBits();
	}
	return *this;
}

Fixed::~Fixed(){
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

//* ********************** overloads ************************* */

// ? -------------- operators --------------
Fixed Fixed::operator+(const Fixed &F) const{
	Fixed rst;

	rst.n = n + F.n;
	return rst;
}

Fixed Fixed::operator-(const Fixed &F) const{
	Fixed rst;

	rst.n = n - F.n;
	return rst;
}

Fixed Fixed::operator*(const Fixed &F) const{
	Fixed rst(this->toFloat() * F.toFloat());

	return rst;
}

Fixed Fixed::operator/(const Fixed &F) const{
	Fixed rst(this->toFloat() / F.toFloat());

	return rst;
}

// ? -------------- comparison --------------
bool Fixed::operator<(const Fixed &F){
	return n < F.n;
}

bool Fixed::operator>(const Fixed &F){
	return n > F.n;
}

bool Fixed::operator<=(const Fixed &F){
	return n <= F.n;
}

bool Fixed::operator>=(const Fixed &F){
	return n >= F.n;
}

bool Fixed::operator==(const Fixed &F){
	return n == F.n;
}

bool Fixed::operator!=(const Fixed &F){
	return n != F.n;
}

// ? -------------- increment/decrement --------------
Fixed Fixed::operator++(){
	n++;
	return *this;
} 
Fixed Fixed::operator++(int){
	Fixed rst = *this;
	++n;
	return rst;
}
Fixed Fixed::operator--(){
	n--;
	return *this;
}
Fixed Fixed::operator--(int){
	Fixed rst = *this;
	--n;
	return rst;
}


// ? -------------- functions --------------
Fixed Fixed::max(Fixed &x1, Fixed &x2){
	if (x1 < x2)
		return x2;
	return x1;
}

Fixed const Fixed::max(const Fixed &x1, const Fixed &x2){
	if ((Fixed)x1 < (Fixed)x2)
		return x2;
	return x1;
}

Fixed Fixed::min(Fixed &x1, Fixed &x2){
	if (x1 < x2)
		return x1;
	return x2;
}

Fixed const Fixed::min(const Fixed &x1, const Fixed &x2){
	if ((Fixed)x1 < (Fixed)x2)
		return x1;
	return x2;
}


std::ostream & operator<<(std::ostream &out, const Fixed &F){
	out << F.toFloat();
	return out;
}