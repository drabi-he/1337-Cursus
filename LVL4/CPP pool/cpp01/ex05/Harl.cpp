/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 00:07:56 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/29 23:44:33 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl(/* args */){}

Harl::~Harl(){}

void Harl::debug(){
    std::cout << "\033[1m\033[32m" << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup "\
    "burger. I really do!" << "\033[0m" << std::endl;
}
void Harl::info(){
    std::cout << "\033[1m\033[36m" << "I cannot believe adding extra bacon costs more money. "\
    "You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << "\033[0m" << std::endl;
}
void Harl::warning(){
    std::cout << "\033[1m\033[33m" << "I think I deserve to have some extra bacon for free. I’ve been coming for "\
    "years whereas you started working here since last month." << "\033[0m" << std::endl;
}
void Harl::error(){
    std::cout << "\033[1m\033[31m" << "This is unacceptable! I want to speak to the manager now." << "\033[0m" << std::endl;
}
void Harl::complain(std::string level){
    void (Harl::*choose[4])(void) = {
        &Harl::debug,
        &Harl::info,
        &Harl::warning,
        &Harl::error
    };
    
    std::string choice[4] = {
        "DEBUG",
        "INFO",
        "WARNING",
        "ERROR"
    };
    
    for (int i = 0; i < 4; i++)
        if(level == choice[i])
            (this->*choose[i])();
}