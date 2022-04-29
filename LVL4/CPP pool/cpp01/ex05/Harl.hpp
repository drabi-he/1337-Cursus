/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 00:07:45 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/29 00:12:27 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _HARL_
#define _HARL_

#include "iostream"

class Harl
{
    private:
        void debug();
        void info();
        void warning();
        void error();
    public:
        Harl(/* args */);
        ~Harl();
        void complain( std::string level );
};

#endif