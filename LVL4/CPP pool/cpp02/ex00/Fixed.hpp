/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:58:55 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/29 14:46:57 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FIXED_
#define _FIXED_

#include <iostream>

class Fixed
{
    private:
        int n;
        static const int fb = 8;
    public:
        Fixed();
        Fixed(const Fixed &F);
        Fixed &operator = (const Fixed &F);
        ~Fixed();
        int getRawBits() const;
        void setRawBits(int const raw);
};



#endif 
