/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:10:52 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/24 13:46:20 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BUREAUCRAT_
#define _BUREAUCRAT_

#include <iostream>
#include <exception>

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
        unsigned int getGrade() const;

        void    promotion();
        void    demotion();
        
        class GradeTooHighException : public std::exception{
            public:
                virtual const char* what() const throw() {
                    return "the highest grade possible is 1" ;
                }
        };
        
        class GradeTooLowException : public std::exception{
            public:
                virtual const char* what() const throw() {
                    return "the lowest grade possible is 150" ;
                }
        };
    
};

std::ostream & operator << (std::ostream &out, const Bureaucrat &B);

#endif