/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:58:55 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/29 16:56:26 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FIXED_
#define _FIXED_

#include <iostream>
#include <fstream>
#include <cmath>

class Fixed
{
    private:
        int n;
        static const int fb = 8;
    public:
        Fixed();
        Fixed(const int nb);
        Fixed(const float nb);
        Fixed(const Fixed &F);
        Fixed &operator = (const Fixed &F);
        ~Fixed();
        int getRawBits() const;
        void setRawBits(int const raw);
        float toFloat( void ) const;
        int toInt( void ) const;
        Fixed operator + (const Fixed &F) const; 
        Fixed operator - (const Fixed &F) const; 
        Fixed operator / (const Fixed &F) const; 
        Fixed operator * (const Fixed &F) const; 
        bool operator < (const Fixed &F); 
        bool operator > (const Fixed &F); 
        bool operator <= (const Fixed &F); 
        bool operator >= (const Fixed &F); 
        bool operator == (const Fixed &F); 
        bool operator != (const Fixed &F);
        Fixed operator++(); 
        Fixed operator++(int); 
        Fixed operator--(); 
        Fixed operator--(int);
        static Fixed max(Fixed &x1, Fixed &x2);
        static const Fixed max(const Fixed &x1, const Fixed &x2);
        static Fixed min(Fixed &x1, Fixed &x2);
        static const Fixed min(const Fixed &x1, const Fixed &x2);

};

std::ostream & operator<<(std::ostream &out, const Fixed &F);

#endif 
