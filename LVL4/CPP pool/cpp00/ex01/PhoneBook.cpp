/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:27:57 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/29 22:54:03 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

int PhoneBook::cp = 0;

PhoneBook::PhoneBook(){}

void  PhoneBook::addContact(int index, Contact contact){
    if (this->cp < 8)
        this->cp++;
	this->phoneBook[index] = contact;
    std::cout << "\033[1m\033[32m" << "Contact Added" << "\033[0m" << std::endl;
}

void PhoneBook::showAll(){
    std::cout << "|" << std::setw(10) << "index" << "|" << std::setw(10) << "First Name" << "|" \
    << std::setw(10) << "Last Name" << "|" << std::setw(10) << "NickName" << "|" << std::endl;
    
    for (int i = 0; i < this->cp ; i++)
        this->phoneBook[i].displayAll();
}

void PhoneBook::search(int index){
    if (index < 0 || index >= this->cp)
        std::cout << "\033[1m\033[31m" << "Contact Not Found" << "\033[0m" << std::endl;
    else
        this->phoneBook[index].display();
}