/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 00:07:56 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/29 01:31:26 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl(/* args */){}

Harl::~Harl(){}

void Harl::debug(){
    std::cout <<"[ DEBUG ]" << std::endl;
    std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!" << std::endl << std::endl ;
    this->info();
}
void Harl::info(){
    std::cout << "[ INFO ]" << std::endl;
    std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put "\
    "enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl << std::endl;
    this->warning();
}
void Harl::warning(){
    std::cout << "[ WARNING ]" << std::endl;
    std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for "\
    "years whereas you started working here since last month." << std::endl << std::endl;
    this->error();
}
void Harl::error(){
    std::cout << "[ ERROR ]" << std::endl;
    std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl << std::endl;
}
void Harl::complain(std::string level){

    int i;
    
    std::string choice[4] = {
        "DEBUG",
        "INFO",
        "WARNING",
        "ERROR"
    };
    i = -1;
    while (++i < 4)
        if(level == choice[i])
            break ;
    this->filter(i);
}

void Harl::filter(int i){
    switch (i)
    {
        case 0 :
            this->debug();
            break;
        case 1 :
            this->info();
            break;
        case 2 :
            this->warning();
            break;
        case 3 :
            this->error();
            break;
        default:
            std::cout << "[  Probably complaining about insignificant problems ]" << std::endl;
            break;
    }
}