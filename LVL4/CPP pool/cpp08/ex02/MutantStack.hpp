/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:57:45 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/12 17:17:41 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <iostream>
# include <string>
#include <stack>

template <class T>
class MutantStack : public std::stack<T>
{
	public:
		// Constructors
		MutantStack();
		MutantStack(const MutantStack<T> &copy);
		
		// Destructor
		~MutantStack();
		
		// Operators
		MutantStack<T> & operator=(const MutantStack<T> &assign);
		typedef typename std::stack<T>::container_type::iterator iterator;

		iterator begin();
		iterator end();
	private:
		
};

template <class T>
MutantStack<T>::MutantStack()
{
	std::cout << "\e[0;33mDefault Constructor called of MutantStack\e[0m" << std::endl;
}

template <class T>
MutantStack<T>::MutantStack(const MutantStack &copy)
{
	*this = copy;
	std::cout << "\e[0;33mCopy Constructor called of MutantStack\e[0m" << std::endl;
}

template <class T>
MutantStack<T>::~MutantStack()
{
	std::cout << "\e[0;31mDestructor called of MutantStack\e[0m" << std::endl;
}


template <class T>
MutantStack<T> & MutantStack<T>::operator=(const MutantStack<T> &assign)
{
	(void) assign;
	return *this;
}

template <class T>
typename MutantStack<T>::iterator MutantStack<T>::begin(){
	return this->c.begin();
}
template <class T>
typename MutantStack<T>::iterator MutantStack<T>::end(){
	return this->c.end();
}


#endif