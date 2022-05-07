/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:43:58 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/07 11:28:08 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point(): x(), y(){}

Point::Point(const Point &P)
{
    *this = P;
}

Point::Point(const Fixed &x, const Fixed &y)
{
    const_cast<Fixed&>(this->x) = x;
    const_cast<Fixed&>(this->y) = y;
}

Point::~Point(){}

Point & Point::operator=(const Point &P){
    if (this != &P)
    {
        const_cast<Fixed&>(this->x) = P.x;
        const_cast<Fixed&>(this->y) = P.y;
    }
    return *this;
}

float Point::getX() const{
    return this->x.toFloat();
}
float Point::getY() const{
    return this->y.toFloat();
}

