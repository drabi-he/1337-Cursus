/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:33:17 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/06 17:42:34 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(): Form("RobotomyRequestForm", false, 72, 45){
    std::cout << "Default constructor for RobotomyRequestForm" << std::endl;
    this->target = "default";
}

RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
: Form("RobotomyRequestForm", false, 72, 45){
    std::cout << "Default constructor for RobotomyRequestForm" << std::endl;
    this->target = target;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &RRF){
    std::cout << "Copy constructor for RobotomyRequestForm" << std::endl;
    *this = RRF;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &RRF){
    std::cout << "Copy Assignment constructor for RobotomyRequestForm" << std::endl;
    (void)RRF;
    return *this;
}

RobotomyRequestForm::~RobotomyRequestForm(){
    std::cout << "Destructor for RobotomyRequestForm" << std::endl;
}

void RobotomyRequestForm::execute(Bureaucrat const &B) const{
    Form::execute(B);
}

void RobotomyRequestForm::valid(Bureaucrat const &B) const{
    (void)B;
    srand( time(NULL) );
    	std::cout << "* Vrrrrrrrrr Vrrrrrrrrr Vrrrrrrrrr *" << std::endl;
	if (std::rand() % 2)
		std::cout << "Subject  " << this->target << " has been successfull"
			        << "y robotomized, Prepare for World Domination" << std::endl;
	else
		std::cout << "The robotomization on " << this->target << " has Failed "
			        << "please Upgrade the Tools." << std::endl;
}