/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:32:47 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/18 12:19:17 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(): Form("ShrubberyCreationForm", false, 145, 137){
    std::cout << "Default constructor for ShrubberyCreationForm" << std::endl;
    this->target = "default";
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
: Form("ShrubberyCreationForm", false, 145, 137){
    std::cout << "Default constructor for ShrubberyCreationForm" << std::endl;
    this->target = target;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &SCF){
    std::cout << "Copy constructor for ShrubberyCreationForm" << std::endl;
    *this = SCF;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &SCF){
    std::cout << "Copy Assignment constructor for ShrubberyCreationForm" << std::endl;
    (void)SCF;
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm(){
    std::cout << "Destructor for ShrubberyCreationForm" << std::endl;
}

void ShrubberyCreationForm::execute(Bureaucrat const &B) const{
    Form::execute(B);
}


void ShrubberyCreationForm::valid(Bureaucrat const &B) const{
    (void)B;
    std::ofstream	myfile;
	std::string		fileName = this->target + "_shrubbery";
	myfile.open(fileName.c_str(), std::ios::out);
	myfile << "      ,.," << std::endl;
	myfile << "      MMMM_    ,..," << std::endl;
	myfile << "        \"_ \"__\"MMMMM          ,...,," << std::endl;
	myfile << " ,..., __.\" --\"    ,.,     _-\"MMMMMMM" << std::endl;
	myfile << "MMMMMM\"___ \"_._   MMM\"_.\"\" _ \"\"\"\"\"\"" << std::endl;
	myfile << " \"\"\"\"\"    \"\" , \\_.   \"_. .\"" << std::endl;
	myfile << "        ,., _\"__ \\__./ .\"" << std::endl;
	myfile << "       MMMMM_\"  \"_    ./" << std::endl;
	myfile << "        ''''      (    )" << std::endl;
	myfile << " ._______________.-'____\"---._." << std::endl;
	myfile << "  \\                          /" << std::endl;
	myfile << "   \\________________________/" << std::endl;
	myfile << "   (_)                    (_)" << std::endl;
	myfile.close();
	std::cout << "Tree created in " << this->target << "_shrubbery" << std::endl;
}
