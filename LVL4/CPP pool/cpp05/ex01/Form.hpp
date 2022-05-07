/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:04:00 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/06 15:12:28 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FORM_
#define _FORM_

#include "Bureaucrat.hpp"
#include <iostream>
#include <exception>

class Bureaucrat;

class Form
{
    private:
        const std::string   name;
        bool    _signed;
        const int   signGrade;
        const int   execGrade;
    public:
        Form();
        Form(const std::string &name, const bool &_signed, const int &sg, const int &eg);
        Form(const Form &F);
        Form &operator=(const Form &F);
        ~Form();
        
        std::string getName() const;
        bool getSigned() const;
        int getSignGrade() const;
        int getExecGrade() const;
        void beSigned(Bureaucrat &B);

        class GradeTooHighException: public std::exception {
            public:
                const char *what() const throw() {
                    return "Form Exception : the highest grade possible is 1";
                }
        };

        class GradeTooLowException: public std::exception {
            public:
                const char *what() const throw() {
                    return "Form Exception : the lowest grade possible is 150";
                }
        };
};

std::ostream &operator << (std::ostream &out, const Form &F);




#endif /* _FORM_ */
