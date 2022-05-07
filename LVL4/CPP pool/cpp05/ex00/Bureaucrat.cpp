/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:10:44 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/06 13:57:19 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(){
    std::cout << "Default contructor for Bureaucrat" << std::endl;
}

Bureaucrat::Bureaucrat(const std::string &name, const int &grade): name(name) , grade(grade){
    std::cout << "Initialise contructor for Bureaucrat" << std::endl;
    if (this->grade < 1)
        throw Bureaucrat::GradeTooHighException();
    if (this->grade > 150)
        throw Bureaucrat::GradeTooLowException();
}

Bureaucrat::Bureaucrat(const Bureaucrat &B){
    std::cout << "Copy contructor for Bureaucrat" << std::endl;
    *this = B;
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &B){
    std::cout << "Copy Assignment contructor for Bureaucrat" << std::endl;
    if (this != &B)
    {
        this->grade = B.grade;
    }
    return *this;
}

Bureaucrat::~Bureaucrat(){
    std::cout << "Destructor for Bureaucrat" << std::endl;
}

std::string Bureaucrat::getName() const{
    return this->name;
}
unsigned int Bureaucrat::getGrade() const{
    return this->grade;
}

void    Bureaucrat::promotion(){
    this->grade--;
    if (this->grade < 1)
        throw Bureaucrat::GradeTooHighException();
}
void    Bureaucrat::demotion(){
    this->grade++;
    if (this->grade > 150)
        throw Bureaucrat::GradeTooLowException();
}

std::ostream & operator << (std::ostream &out, const Bureaucrat &B)
{
    out <<  B.getName() + ", bureaucrat grade " + std::to_string(B.getGrade());
    return out;
}