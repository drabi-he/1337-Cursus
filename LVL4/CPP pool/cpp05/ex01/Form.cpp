/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:51:53 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/18 11:32:24 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form(): name("Form") ,signGrade(150) , execGrade(150){
    std::cout << "Default constructor for Form" << std::endl;
    this->_signed = false;
}

Form::Form(const std::string &name, const bool &_signed, const int &sg, const int &eg)
: name(name), _signed(_signed) , signGrade(sg) , execGrade(eg) {
    std::cout << "Initialise constructor for Form" << std::endl;
    if (this->signGrade < 1 || this->execGrade < 1)
        throw GradeTooHighException();
    if (this->signGrade > 150 || this->execGrade > 150)
        throw GradeTooLowException();
}

Form::Form(const Form &F): signGrade(150) , execGrade(150){
    std::cout << "Copy constructor for Form" << std::endl;
    *this = F;
}

Form &Form::operator=(const Form &F){
    std::cout << "Copy Assignment constructor for Form" << std::endl;
    if (this != &F)
    {
        this->_signed = F._signed;
    }
    return *this;
}

Form::~Form(){
    std::cout << "Deconstructor for Form" << std::endl;
}

std::string Form::getName() const{
    return this->name;
}
bool Form::getSigned() const{
    return this->_signed;
}
int Form::getSignGrade() const{
    return this->signGrade;
}
int Form::getExecGrade() const{
    return this->execGrade;
}

void Form::beSigned(Bureaucrat &B){
    B.signForm(*this);
    if (B.getGrade() > this->signGrade)
        throw Form::GradeTooLowException();
    this->_signed = true;
}


std::ostream &operator << (std::ostream &out, const Form &F){
    out << "Form " + F.getName() + " is " + (F.getSigned() ? "Signed" : "not Signed")
            << " it require " + std::to_string(F.getSignGrade()) + " Grade to sign"
            << " and " + std::to_string(F.getExecGrade()) + " Grade to execute";
    return out;
}