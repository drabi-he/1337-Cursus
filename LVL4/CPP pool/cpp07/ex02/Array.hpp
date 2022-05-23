/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:32:39 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/23 12:13:52 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ARRAY_
# define _ARRAY_

# include <iostream>
# include <exception>

template <typename T>
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
		const T &	operator[]( int index ) const;	
		T &	operator[]( int index );	
		unsigned int size() const;
	
	class ArrayException : public std::exception {
		public:
			const char *what() const throw(){
				return "index out of bound";
			}
	};
};

template <typename T>
Array<T>::Array()
{
	this->array = nullptr;
	this->len = 0;
}

template <typename T>
Array<T>::Array(unsigned int size)
{
	if (size > 0)
		this->array = new T[size];
	else
		this->array = nullptr;
	this->len = size;
}

template <typename T>
Array<T>::Array( const Array<T> & src )
{
	this->len = 0;
	*this = src;
}

template <typename T>
Array<T> &	Array<T>::operator=( Array<T> const & src )
{
	if (this != &src)
	{
		if (this->len > 0)
			delete [] this->array;
		this->len = src.len;
		if (this->len > 0){
			this->array = new T[src.len];
			for (int i = 0; i < (int)this->len; i++)
			{
				this->array[i] = src.array[i];
			}
		} else 
			this->array = nullptr;
	}
	return *this;
}

template <typename T>
const T& Array<T>::operator[](int index) const
{
    if (index < 0 || index >= (int)this->len)
        throw Array<T>::ArrayException();
    return this->array[index];
}

template <typename T>
T& Array<T>::operator[](int index)
{
    if (index < 0 || index >= (int)this->len)
        throw Array<T>::ArrayException();
    return this->array[index];
}


template <typename T>
unsigned int Array<T>::size() const{
	return this->len;
}


template <typename T>
Array<T>::~Array()
{
	if (this->len > 0)
		delete [] this->array;
}


#endif /* *********************************************************** ARRAY_H */