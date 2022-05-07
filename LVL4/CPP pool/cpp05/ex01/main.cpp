/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 12:12:12 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/06 15:22:31 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main()
{
    {
        std::cout << "< ---------------- 1st Bureaucrat Scoop --------------- >" << std::endl;
        try {
            Bureaucrat B("test", -1);
            std::cout << B << std::endl; 
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
    {
        std::cout << "< ---------------- 1st Form Scoop --------------- >" << std::endl;
        {
            try {
                Form F("test", 0, -1, 5);
                std::cout << F << std::endl; 
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }
        {
            try {
                Form F("test", 0, 5, -1);
                std::cout << F << std::endl; 
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }

    }
    {
        std::cout << "< ---------------- 2nd Bureaucrat Scoop --------------- >" << std::endl;
        try {
            Bureaucrat B("test", 155);
            std::cout << B << std::endl; 
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
    {
        std::cout << "< ---------------- 2nd Form Scoop --------------- >" << std::endl;
        {
            try {
                Form F("test", 0, 5, 155);
                std::cout << F << std::endl; 
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }
        {
            try {
                Form F("test", 0, 155, 5);
                std::cout << F << std::endl; 
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }
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
    {
        std::cout << "< ---------------- 5th scoop --------------- >" << std::endl;
        try {
            Bureaucrat B("izouf", 146);
            Form F("Bus", 0, 145, 5);
            F.beSigned(B);
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
    {
        std::cout << "< ---------------- 6th scoop --------------- >" << std::endl;
        try {
            Bureaucrat B("izouf", 146);
            Form F("Bus", 0, 145, 5);
            std::cout << B << std::endl; 
            std::cout << F << std::endl; 
            B.promotion();
            F.beSigned(B);
            std::cout << B << std::endl; 
            std::cout << F << std::endl; 
            F.beSigned(B);
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }

}