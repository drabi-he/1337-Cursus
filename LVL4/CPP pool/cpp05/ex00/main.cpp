/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 12:12:12 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/06 13:57:42 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include <iostream>

int main()
{
    {
        std::cout << "< ---------------- 1st scoop --------------- >" << std::endl;
        try {
            Bureaucrat B("test", -1);
            std::cout << B << std::endl; 
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
    {
        std::cout << "< ---------------- 2nd scoop --------------- >" << std::endl;
        try {
            Bureaucrat B("test", 155);
            std::cout << B << std::endl; 
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
    {
        std::cout << "< ---------------- 3rd scoop --------------- >" << std::endl;
        try {
            Bureaucrat B("momayaz", 5);
            std::cout << B << std::endl; 
            B.promotion();
            std::cout << B << std::endl; 
            B.promotion();
            std::cout << B << std::endl; 
            B.promotion();
            std::cout << B << std::endl; 
            B.promotion();
            std::cout << B << std::endl; 
            B.promotion();
            std::cout << B << std::endl; 
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
    {
        std::cout << "< ---------------- 4th scoop --------------- >" << std::endl;
        try {
            Bureaucrat B("izouf", 146);
            std::cout << B << std::endl; 
            B.demotion();
            std::cout << B << std::endl; 
            B.demotion();
            std::cout << B << std::endl; 
            B.demotion();
            std::cout << B << std::endl; 
            B.demotion();
            std::cout << B << std::endl; 
            B.demotion();
            std::cout << B << std::endl; 
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }

}