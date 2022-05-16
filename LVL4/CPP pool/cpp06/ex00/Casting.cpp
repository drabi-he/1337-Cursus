/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Casting.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:38:26 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/11 15:26:42 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Casting.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Casting::Casting(){
	this->type = NOTYPE;
}

Casting::Casting( const Casting & C ){
	*this = C;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Casting::~Casting()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Casting &				Casting::operator=( Casting const & C )
{
	if ( this != &C )
	{
		this->type = C.type;
		this->charValue = C.charValue;
		this->intValue = C.intValue;
		this->floatValue = C.floatValue;
		this->doubleValue = C.doubleValue;
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void Casting::detectType(char *str)
{
	if (str == nullptr)
		throw Casting::EmptyException();
	this->type = -1;
	this->type = detectPseudo(str);
	if (this->type != NOTYPE)
		return;
	this->type = detectFD(str);
	if (this->type != NOTYPE)
		return ;
	this->type = detectI(str);
	if (this->type != NOTYPE)
		return ;
	if (strlen(str) == 1)
		this->type = CHAR;
}

int detectPseudo(char *str){
	std::string D[4] = {
		"nan",
		"inf",
		"+inf",
		"-inf",
	};
	std::string F[4] = {
		"nanf",
		"inff",
		"+inff",
		"-inff",
	};
	for (int i = 0; i < 4; i++){
		if (D[i] == str)
			return DOUBLE;
		else if (F[i] == str)
			return FLOAT;
	}
	return NOTYPE;
}

int detectFD(char *str){
	int i = 0;
	int cp = 0;
	
	if (str[i] == '-')
		i++;
	for (; str[i] != 0 ; i++)
		if (!std::isdigit(str[i]))
			break ;
			
	if (str[i] != '.')
		return NOTYPE ;
		
	i++;
	
	for (; str[i] != 0; i++)
	{
		if (!std::isdigit(str[i]))
			break ;
		cp++;
	}
	if ((str[i] != 0 && str[i] != 'f') || cp == 0 )
		return NOTYPE ;
	if (str[i] == 'f')
		return FLOAT;
	return DOUBLE;
}

int detectI(char *str){
	int i = 0;

	if (str[0] == '-')
		i++;
	for (; str[i] != 0; i++)
		if (!std::isdigit(str[i]))
			return NOTYPE ;
	return INT;
}


void Casting::printResult(char *str){
	this->convertResult(str);
	
	if (this->doubleValue < CHAR_MIN || this->doubleValue > CHAR_MAX || this->doubleValue != this->doubleValue)
		std::cout << "char Value : " << "can't be measured" << std::endl;
	else if (!std::isprint(this->charValue))
		std::cout << "char Value : " << "non printable" << std::endl;
	else
		std::cout << "char Value : " << this->charValue << std::endl;
		
	if (this->doubleValue < INT_MIN || this->doubleValue > INT_MAX || this->doubleValue != this->doubleValue)
		std::cout << "int Value : " << "can't be measured" << std::endl;
	else
		std::cout << "int Value : " << this->intValue << std::endl;
		
	if (this->type == 1 || this->type == 2 || this->floatValue == (int)this->floatValue)
		std::cout << "float Value : "  << this->floatValue << ".0f" << std::endl;
	else 
		std::cout << "float Value : "  << this->floatValue << "f" << std::endl;
		
	if (this->type == 1 || this->type == 2 || this->floatValue == (int)this->floatValue)
		std::cout << "double Value : " << this->doubleValue << ".0" << std::endl;
	else 
		std::cout << "double Value : " << this->doubleValue << std::endl;
}

void Casting::convertResult(char *str){
	(void)str;
	if (this->type == -1)
		throw Casting::WrongInput();
	switch (this->type)
	{
	case 1 :
		this->charValue = str[0];
		charToOther();
		break;
		
	case 2 :
		this->intValue = std::stoi(str);
		intToOther();
		break;
		
	case 3 :
		this->floatValue = std::stof(str);
		floatToOther();
		break;
		
	default:
		this->doubleValue = std::stod(str);
		doubleToOther();
		break;
	}
}

void Casting::charToOther(){
	this->intValue = static_cast<int>(this->charValue);
	this->floatValue = static_cast<float>(this->charValue);
	this->doubleValue = static_cast<double>(this->charValue);
}

void Casting::intToOther()
{
	this->charValue = static_cast<char>(this->intValue);
	this->floatValue = static_cast<float>(this->intValue);
	this->doubleValue = static_cast<double>(this->intValue);
}

void Casting::floatToOther(){
	this->intValue = static_cast<int>(this->floatValue);
	this->charValue = static_cast<char>(this->floatValue);
	this->doubleValue = static_cast<double>(this->floatValue);
}

void Casting::doubleToOther(){
	this->intValue = static_cast<int>(this->doubleValue);
	this->floatValue = static_cast<float>(this->doubleValue);
	this->charValue = static_cast<char>(this->doubleValue);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/



/* ************************************************************************** */