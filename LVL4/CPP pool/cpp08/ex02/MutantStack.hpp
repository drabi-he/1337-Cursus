/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:57:45 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/19 15:20:35 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <iostream>
# include <string>
#include <stack>

template <typename T>
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
		typedef typename std::stack<T>::container_type::const_iterator c_iterator;
		typedef typename std::stack<T>::container_type::reverse_iterator r_iterator;
		typedef typename std::stack<T>::container_type::const_reverse_iterator c_r_iterator;

		iterator begin();
		iterator end();
		c_iterator begin() const;
		c_iterator end() const;
		r_iterator rbegin();
		r_iterator rend();
		c_r_iterator rbegin() const;
		c_r_iterator rend() const;
	private:
		
};

template <typename T>
MutantStack<T>::MutantStack()
{
	std::cout << "\e[0;33mDefault Constructor called of MutantStack\e[0m" << std::endl;
}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack &copy)
{
	*this = copy;
	std::cout << "\e[0;33mCopy Constructor called of MutantStack\e[0m" << std::endl;
}

template <typename T>
MutantStack<T>::~MutantStack()
{
	std::cout << "\e[0;31mDestructor called of MutantStack\e[0m" << std::endl;
}


template <typename T>
MutantStack<T> & MutantStack<T>::operator=(const MutantStack<T> &assign)
{
	(void) assign;
	return *this;
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin(){
	return this->c.begin();
}
template <typename T>
typename MutantStack<T>::c_iterator MutantStack<T>::begin() const{
	return this->c.begin();
}
template <typename T>
typename MutantStack<T>::r_iterator MutantStack<T>::rbegin(){
	return this->c.rbegin();
}
template <typename T>
typename MutantStack<T>::c_r_iterator MutantStack<T>::rbegin() const{
	return this->c.rbegin();
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::end(){
	return this->c.end();
}
template <typename T>
typename MutantStack<T>::c_iterator MutantStack<T>::end() const{
	return this->c.end();
}
template <typename T>
typename MutantStack<T>::r_iterator MutantStack<T>::rend(){
	return this->c.rend();
}
template <typename T>
typename MutantStack<T>::c_r_iterator MutantStack<T>::rend() const{
	return this->c.rend();
}


#endif