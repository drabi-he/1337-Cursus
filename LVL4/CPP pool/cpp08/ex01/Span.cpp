/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:16:33 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/12 16:30:31 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

// Constructors
Span::Span()
{
	_nb = 0;
	std::cout << "\e[0;33mDefault Constructor called of Span\e[0m" << std::endl;
}

Span::Span(const Span &copy)
{
	*this = copy;
	std::cout << "\e[0;33mCopy Constructor called of Span\e[0m" << std::endl;
}

Span::Span(unsigned int nb)
{
	_nb = nb;
	std::cout << "\e[0;33mFields Constructor called of Span\e[0m" << std::endl;
}


// Destructor
Span::~Span()
{
	std::cout << "\e[0;31mDestructor called of Span\e[0m" << std::endl;
}


// Operators
Span & Span::operator=(const Span &assign)
{
	if (this != &assign)
	{
		_nb = assign.getNb();
		this->array = assign.array;
	}
	return *this;
}


// Getters / Setters
unsigned int Span::getNb() const
{
	return _nb;
}
void Span::setNb(unsigned int nb)
{
	_nb = nb;
}



void Span::addNumber(int n){
	if (this->array.size() == this->_nb)
		throw std::range_error("the span is already filled");
	this->array.push_back(n);
}

int Span::shortestSpan(){
	int rst = -1;
	std::vector<int> tmp = this->array;
	std::vector<int>::iterator i;
	
	if (this->array.size() < 2)
		throw std::range_error("the span has less than 2 elements");
	sort(tmp.begin(), tmp.end());
	for (i = tmp.begin() ; i < tmp.end() - 1; i++)
	{
		if (rst > (*(i + 1) - *i) || rst < 0)
			rst = (*(i + 1) - *i);
	}
	return rst;
}

int Span::longestSpan(){
	if (this->array.size() < 2)
		throw std::range_error("the span has less than 2 elements");
		
	int min = *min_element(this->array.begin(), this->array.end());
	int max = *max_element(this->array.begin(), this->array.end());

	return (max - min);
}

void Span::UIaddNumber(std::vector<int>::iterator f, std::vector<int>::iterator l){
	if ((int)(this->_nb - this->array.size()) < l - f)
		throw std::range_error("the range is bigger than our span");
	copy(f, l, std::back_inserter(this->array));
}
