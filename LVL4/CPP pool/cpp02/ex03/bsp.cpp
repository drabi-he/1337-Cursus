/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:43:54 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/30 01:05:07 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include "Point.hpp"

float get_sign(Point p1, Point p2, Point p3)
{
    return (((p1.getX() - p3.getX()) * (p2.getY() - p3.getY())) - ((p2.getX() - p3.getX()) * (p1.getY() - p3.getY())));
}

bool bsp( Point const a, Point const b, Point const c, Point const point){
    float d1, d2, d3;
    bool n, p;

    d1 = get_sign(point, a, b);
    d2 = get_sign(point, b, c);
    d3 = get_sign(point, c, a);

    // TODO: re-check the values
    std::cout << d1 << d2 << d3 << std::endl;
    if (d1 == 0 || d2 == 0 || d3 == 0)
        return (false);
    n = (d1 < 0 || d2 < 0 || d3 < 0);
    p = (d1 > 0 || d2 > 0 || d3 > 0);
    return !(n && p);
}