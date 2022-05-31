/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:23:27 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/31 19:38:57 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <iostream>
# include <string>

#include "iterator_traits.hpp"
#include "../xtra/enable_if.hpp"
#include "../xtra/is_integral.hpp"

namespace ft
{
	template <class T>
	class iterators
	{
		public:
			typedef std::size_t size_type;
			typedef typename ft::iterator_traits<T>::difference_type difference_type;
			typedef typename ft::iterator_traits<T>::value_type value_type;
			typedef typename ft::iterator_traits<T>::pointer pointer;
			typedef typename ft::iterator_traits<T>::reference reference;
			typedef typename ft::iterator_traits<T>::iterator_category iterator_category;
			
			// * Constructors
			iterators(){
				// std::cout << "\e[0;33mDefault Constructor called of iterators\e[0m" << std::endl;
			}

			iterators(pointer addr) : _ptr(addr){
				// std::cout << "\e[0;33mDefault Constructor called of iterators\e[0m" << std::endl;
			}

			iterators(const iterators &copy){
				// std::cout << "\e[0;33mCopy Constructor called of iterators\e[0m" << std::endl;
				*this = copy;
			}

			// ! Destructor
			~iterators(){
				// std::cout << "\e[0;31mDestructor called of iterators\e[0m" << std::endl;
			}

			// ? Operators
			iterators & operator=(const iterators &assign){
				if (this != &assign)
					_ptr = assign._ptr;
				return *this;
			}

			iterators & operator++(){
				_ptr++;
				return *this;
			}
			
			iterators operator++(int){
				iterators tmp = *this;
				_ptr++;
				return tmp;
			}
			
			iterators & operator--(){
				_ptr--;
				return *this;
			}
			iterators operator--(int){
				iterators tmp = *this;
				_ptr--;
				return tmp;
			}

			template <class U>
			typename ft::enable_if<ft::is_integral<U>::value , iterators>::type operator+(const U& val){
				iterators tmp = *this;
				tmp._ptr += val;
				return tmp;
			}

			template <class U>
			typename ft::enable_if<ft::is_integral<U>::value , iterators>::type operator-(const U &val){
				iterators tmp = *this;
				tmp._ptr -= val;
				return tmp;
			}

			reference operator[](size_type index){
				return _ptr + index;
			}

			pointer operator->(){
				return _ptr;
			}

			reference operator*(){
				return *_ptr;
			}

			bool operator==(const iterators &I) const {
				return _ptr == I._ptr;
			}

			bool operator!=(const iterators &I) const {
				return _ptr != I._ptr;
			}

			bool operator<(const iterators &I) const {
				return _ptr < I._ptr;
			}

			bool operator<=(const iterators &I) const {
				return _ptr <= I._ptr;
			}

			bool operator>(const iterators &I) const {
				return _ptr > I._ptr;
			}

			bool operator>=(const iterators &I) const {
				return _ptr >= I._ptr;
			}

			long long operator-(const iterators &I){
				return (_ptr - I._ptr);
			}
			
		private:
			pointer _ptr;
	};

	template <class T>
	class reverse_iterator
	{
		public:
			typedef std::size_t size_type;
			typedef typename ft::iterator_traits<T>::difference_type difference_type;
			typedef typename ft::iterator_traits<T>::value_type value_type;
			typedef typename ft::iterator_traits<T>::pointer pointer;
			typedef typename ft::iterator_traits<T>::reference reference;
			typedef typename ft::iterator_traits<T>::iterator_category iterator_category;
			
			// * Constructors
			reverse_iterator(){
				// std::cout << "\e[0;33mDefault Constructor called of reverse_iterator\e[0m" << std::endl;
			}

			reverse_iterator(pointer addr) : _ptr(addr){
				// std::cout << "\e[0;33mDefault Constructor called of reverse_iterator\e[0m" << std::endl;
			}

			reverse_iterator(const reverse_iterator &copy){
				// std::cout << "\e[0;33mCopy Constructor called of reverse_iterator\e[0m" << std::endl;
				*this = copy;
			}

			// ! Destructor
			~reverse_iterator(){
				// std::cout << "\e[0;31mDestructor called of reverse_iterator\e[0m" << std::endl;
			}

			// ? Operators
			reverse_iterator & operator=(const reverse_iterator &assign){
				if (this != &assign)
					_ptr = assign._ptr;
				return *this;
			}

			reverse_iterator & operator++(){
				_ptr--;
				return *this;
			}
			
			reverse_iterator operator++(int){
				reverse_iterator tmp = *this;
				_ptr--;
				return tmp;
			}
			
			reverse_iterator & operator--(){
				_ptr++;
				return *this;
			}
			
			reverse_iterator operator--(int){
				reverse_iterator tmp = *this;
				_ptr++;
				return tmp;
			}

			template <class U>
			typename ft::enable_if<ft::is_integral<U>::value , reverse_iterator>::type operator+(const U& val){
				reverse_iterator tmp = *this;
				tmp._ptr += val;
				return tmp;
			}

			template <class U>
			typename ft::enable_if<ft::is_integral<U>::value , reverse_iterator>::type operator-(const U& val){
				reverse_iterator tmp = *this;
				tmp._ptr -= val;
				return tmp;
			}

			reference operator[](size_type index){
				return _ptr + index;
			}

			pointer operator->(){
				return _ptr;
			}

			reference operator*(){
				return *_ptr;
			}

			bool operator==(const reverse_iterator &I) const {
				return _ptr == I._ptr;
			}

			bool operator!=(const reverse_iterator &I) const {
				return _ptr != I._ptr;
			}
			
			bool operator<(const reverse_iterator &I) const {
				return _ptr < I._ptr;
			}

			bool operator<=(const reverse_iterator &I) const {
				return _ptr <= I._ptr;
			}

			bool operator>(const reverse_iterator &I) const {
				return _ptr > I._ptr;
			}

			bool operator>=(const reverse_iterator &I) const {
				return _ptr >= I._ptr;
			}
			
			long long operator-(const reverse_iterator &I){
				return (_ptr - I._ptr);
			}
			
		private:
			pointer _ptr;
	};
}

#endif
