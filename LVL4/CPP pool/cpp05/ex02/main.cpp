/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 12:12:12 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/18 12:32:00 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

int main()
{
    
    std::cout << "< ----------------------------------------------------------- >" << std::endl;
    {
        ShrubberyCreationForm SCF("home");
        Bureaucrat M("momayaz", 146);
        Bureaucrat I("izouf", 137);
        (void)M;
        (void)I;
        (void)SCF;
        
        try
        {
            std::cout << M << std::endl;
            std::cout << I << std::endl;
            std::cout << SCF << std::endl;

            M.promotion();
            std::cout << M << std::endl;
            SCF.beSigned(M);
            std::cout << SCF << std::endl;
            SCF.execute(I);
            SCF.execute(M);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    std::cout << "< ----------------------------------------------------------- >" << std::endl;
    {
        RobotomyRequestForm RRF("home");
        Bureaucrat M("momayaz", 45);
        Bureaucrat I("izouf", 45);
        (void)M;
        (void)I;
        (void)RRF;
        
        try
        {
            std::cout << M << std::endl;
            std::cout << I << std::endl;
            std::cout << RRF << std::endl;

            M.promotion();
            std::cout << M << std::endl;
            RRF.beSigned(M);
            std::cout << RRF << std::endl;
            RRF.execute(M);
            RRF.execute(I);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    std::cout << "< ----------------------------------------------------------- >" << std::endl;
    {
        PresidentialPardonForm PPF("home");
        Bureaucrat M("momayaz", 5);
        Bureaucrat I("izouf", 26);
        (void)M;
        (void)I;
        (void)PPF;
        
        try
        {
            std::cout << M << std::endl;
            std::cout << I << std::endl;
            std::cout << PPF << std::endl;

            I.promotion();
            std::cout << I << std::endl;
            PPF.beSigned(M);
            std::cout << PPF << std::endl;
            PPF.execute(M);
            M.demotion();
            std::cout << M << std::endl;
            PPF.execute(M);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}