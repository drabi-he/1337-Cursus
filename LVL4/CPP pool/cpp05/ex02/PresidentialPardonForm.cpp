/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:33:37 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/06 17:34:14 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(const std::string &target)
: Form("PresidentialPardonForm", false, 25, 5){
    std::cout << "Default constructor for PresidentialPardonForm" << std::endl;
    this->target = target;
}

PresidentialPardonForm::PresidentialPardonForm(): Form("PresidentialPardonForm", false, 25, 5){
    std::cout << "Default constructor for PresidentialPardonForm" << std::endl;
    this->target = "default";
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &PPF){
    std::cout << "Copy constructor for PresidentialPardonForm" << std::endl;
    *this = PPF;
}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &PPF){
    std::cout << "Copy Assignment constructor for PresidentialPardonForm" << std::endl;
    (void)PPF;
    return *this;
}

PresidentialPardonForm::~PresidentialPardonForm(){
    std::cout << "Destructor for PresidentialPardonForm" << std::endl;
}

void PresidentialPardonForm::execute(Bureaucrat const &B) const{
    Form::execute(B);
}

void PresidentialPardonForm::valid(Bureaucrat const &B) const{
    (void)B;
    std::cout << this->target + ". you have been pardoned by Zaphod Beeblebrox" << std::endl;
}