/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:26:59 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/29 22:56:05 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact(){}

Contact::Contact(int index, std::string firstName, std::string lastName, \
        std::string nickName, std::string phoneNumber, std::string darkSecret){
    this->index = index;
    this->firstName = firstName;
    this->lastName=lastName;  
    this->nickName = nickName;
    this->phoneNumber = phoneNumber;
    this->darkSecret = darkSecret;
}

void Contact::display(){
    std::cout << "index : " << this->index + 1 << std::endl;
    std::cout << "First Name : " << this->firstName << std::endl;
    std::cout << "Last Name : " << this->lastName << std::endl;
    std::cout << "NickName : " << this->nickName << std::endl;
    std::cout << "Phone Number : " << this->phoneNumber << std::endl;
    std::cout << "Dark Secret : " << this->darkSecret << std::endl;
}

void Contact::displayAll()
{
    std::cout << (this->index % 2 ? "\033[35m" : "\033[36m") 
                << "|" << std::setw(10) << this->index + 1
                << "|" << std::setw(10) << (this->firstName.length() > 10 ? this->firstName.substr(0, 9) + "." : this->firstName) 
                << "|" << std::setw(10) << (this->lastName.length() > 10 ? this->lastName.substr(0, 9) + "." : this->lastName) 
                << "|" << std::setw(10) << (this->nickName.length() > 10 ? this->nickName.substr(0, 9) + "." : this->nickName) 
                << "|" << "\033[0m" << std::endl ;
}