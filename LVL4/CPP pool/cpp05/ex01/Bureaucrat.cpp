/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:10:44 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/18 11:27:34 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(){
    std::cout << "Default contructor for Bureaucrat" << std::endl;
}

Bureaucrat::Bureaucrat(const std::string &name, const int &grade): name(name){
    std::cout << "Initialise contructor for Bureaucrat" << std::endl;
    if (grade < 1)
        throw Bureaucrat::GradeTooHighException();
    if (grade > 150)
        throw Bureaucrat::GradeTooLowException();
    this->grade = grade;
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
int Bureaucrat::getGrade() const{
    return this->grade;
}

void    Bureaucrat::signForm(Form &F){
    if (this->grade <= F.getSignGrade() && !F.getSigned())
        std::cout << this->name + " signed " + F.getName() << std::endl;
    else {
        if (this->grade > F.getSignGrade())
            std::cout << this->name + " couldn’t sign " + F.getName() + " because his grade is low" << std::endl;
        if (F.getSigned())
            std::cout << this->name + " couldn’t sign " + F.getName() + " because it's already Signed" << std::endl;
    }
}

void    Bureaucrat::promotion(){
    if (this->grade == 1)
        throw Bureaucrat::GradeTooHighException();
    this->grade--;
}
void    Bureaucrat::demotion(){
    if (this->grade == 150)
        throw Bureaucrat::GradeTooLowException();
    this->grade++;
}

std::ostream & operator << (std::ostream &out, const Bureaucrat &B)
{
    out <<  B.getName() + ", bureaucrat grade " + std::to_string(B.getGrade());
    return out;
}