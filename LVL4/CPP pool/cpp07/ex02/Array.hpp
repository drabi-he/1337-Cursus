/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:32:39 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/10 17:24:58 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ARRAY_
# define _ARRAY_

# include <iostream>
# include <exception>

template <class T>
class Array
{
	private:
		T *array;
		unsigned int len;
	public:

		Array();
		Array(unsigned int size);
		Array(const Array<T> & src );
		~Array();
		Array &	operator=( Array const & src );	
		T &	operator[]( int index );	
		unsigned int size() const;
	
	class ArrayException : public std::exception {
		public:
			const char *what() const throw(){
				return "index out of bound";
			}
	};
};

template <class T>
Array<T>::Array() : array(NULL), len(0)
{
}

template <class T>
Array<T>::Array(unsigned int size)
{
	this->array = new T[size];
	this->len = size;
}

template <class T>
Array<T>::Array( const Array<T> & src )
{
	*this = src;
}

template <class T>
Array<T> &	Array<T>::operator=( Array<T> const & src )
{
	if (this != &src)
	{
		if (this->len > 0)
			delete [] this->array;
		this->len = src.len;
		this->array = new T[src.len];
		for (int i = 0; i < (int)this->len; i++)
			this->array[i] = src.array[i];
	}
	return *this;
}

template <class T>
T& Array<T>::operator[](int index)
{
    if (index < 0 || index >= (int)this->len)
        throw Array<T>::ArrayException();
    return this->array[index];
}


template <class T>
unsigned int Array<T>::size() const{
	return this->len;
}


template <class T>
Array<T>::~Array()
{
	if (this->len > 0)
		delete [] this->array;
}


#endif /* *********************************************************** ARRAY_H */