/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 23:47:57 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/28 16:52:13 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <iostream>
#include <ctime>
#include <iomanip>

// * recreate a issing file depending on existing ones

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

Account::Account(){
    this->_displayTimestamp();
    this->_accountIndex = _nbAccounts;
    this->_amount = 0;
    this->_nbDeposits = 0;
    this->_nbWithdrawals = 0;
    _nbAccounts++;
    std::cout << "index:" << this->_accountIndex << ";amount:" << this->_amount << ";created" << std::endl;
}
Account::Account(int initial_deposit){
    this->_displayTimestamp();
    this->_accountIndex = _nbAccounts;
    this->_amount = initial_deposit;
    this->_nbDeposits = 0;
    this->_nbWithdrawals = 0;
    _nbAccounts++;
    _totalAmount += initial_deposit;
    std::cout << "index:" << this->_accountIndex << ";amount:" << this->_amount << ";created" << std::endl;
}
Account::~Account(){
    this->_displayTimestamp();
    this->_nbAccounts--;
    std::cout << "index:" << this->_accountIndex << ";amount:" << this->_amount << ";closed" << std::endl;
}

int Account::getNbAccounts(){
    return _nbAccounts;
}
int Account::getTotalAmount(){
    return _totalAmount;
}
int Account::getNbDeposits(){
    return _totalNbDeposits;
}
int Account::getNbWithdrawals(){
    return _totalNbWithdrawals;
}
void Account::displayAccountsInfos(){
    _displayTimestamp();
    std::cout << "accounts:" << _nbAccounts
                << ";total:" << _totalAmount
                << ";deposits:" << _totalNbDeposits
                << ";withdrawals:" << _totalNbWithdrawals << std::endl;
}

void Account::makeDeposit(int deposit){
    int p;

    this->_displayTimestamp();
    p = this->_amount;
    this->_amount += deposit;
    this->_nbDeposits++;
    _totalAmount += deposit;
    _totalNbDeposits++;
    std::cout << "index:" << this->_accountIndex << ";p_amount:" << p \
    << ";deposit:" << deposit << ";amount:" << this->_amount \
    << ";nb_deposits:" << this->_nbDeposits << std::endl;
}
bool Account::makeWithdrawal(int withdrawal){
    int p;

    this->_displayTimestamp();
    if (withdrawal > this->_amount){
        std::cout << "index:" << this->_accountIndex << ";p_amount:" << this->_amount \
        << ";withdrawal:refused" << std::endl;
         return false;   
    }
    p = this->_amount;
    this->_amount -= withdrawal;
    this->_nbWithdrawals++;
    _totalAmount -= withdrawal;
    _totalNbWithdrawals++;
    std::cout << "index:" << this->_accountIndex << ";p_amount:" << p \
    << ";withdrawal:" << withdrawal << ";amount:" << this->_amount \
    << ";nb_withdrawals:" << this->_nbWithdrawals << std::endl;
    return true;
}
int Account::checkAmount() const {
    return this->_amount;
}
void Account::displayStatus() const {
    this->_displayTimestamp();
    std::cout << "index:" << this->_accountIndex
                << ";amount:" << this->_amount
                << ";deposits:" << this->_nbDeposits
                << ";withdrawals:" << this->_nbWithdrawals << std::endl;
}

void Account::_displayTimestamp(){
    std::time_t result = std::time(nullptr);

    std::cout << std::setfill('0') <<"[" << 1900 + std::localtime(&result)->tm_year
                << std::setw(2) << 1 + std::localtime(&result)->tm_mon
                <<  std::setw(2) << std::localtime(&result)->tm_mday
                <<  "_"
                <<  std::setw(2) << std::localtime(&result)->tm_hour
                <<  std::setw(2) << std::localtime(&result)->tm_min
                <<  std::setw(2) << std::localtime(&result)->tm_sec << "] ";
}
