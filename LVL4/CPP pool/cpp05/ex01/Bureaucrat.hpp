/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:10:52 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/06 15:21:39 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BUREAUCRAT_
#define _BUREAUCRAT_

#include "Form.hpp"
#include <iostream>
#include <exception>

class Form;

class Bureaucrat
{
    private:
        const std::string name;
        int grade;
    public:
        Bureaucrat();
        Bureaucrat(const std::string &name, const int &grade);
        Bureaucrat(const Bureaucrat &B);
        Bureaucrat &operator=(const Bureaucrat &B);
        ~Bureaucrat();

        std::string getName() const;
        int getGrade() const;
        void    signForm(Form &F);

        void    promotion();
        void    demotion();
        
        class GradeTooHighException : public std::exception{
            public:
                virtual const char* what() const throw() {
                    return "Bureaucrat Exception : the highest grade possible is 1" ;
                }
        };
        
        class GradeTooLowException : public std::exception{
            public:
                virtual const char* what() const throw() {
                    return "Bureaucrat Exception : the lowest grade possible is 150" ;
                }
        };
    
};

std::ostream & operator << (std::ostream &out, const Bureaucrat &B);

#endif