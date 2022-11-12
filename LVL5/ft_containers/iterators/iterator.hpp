/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:23:27 by hdrabi            #+#    #+#             */
/*   Updated: 2022/11/08 10:35:52 by hdrabi           ###   ########.fr       */
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
	class iterators : public ft::iterator<std::random_access_iterator_tag,T>
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

			iterators operator+(const difference_type& val){
				iterators tmp = *this;
				tmp._ptr += val;
				return tmp;
			}

			iterators operator+=(const difference_type& val){
				_ptr += val;
				return *this;
			}

			iterators operator-(const difference_type& val){
				iterators tmp = *this;
				tmp._ptr -= val;
				return tmp;
			}

			iterators operator-=(const difference_type& val){
				_ptr -= val;
				return *this;
			}

			reference operator[](size_type index){
				return *(_ptr + index); // TODO check if it's correct
			}

			pointer operator->(){
				return _ptr;
			}

			reference operator*(){
				return *_ptr;
			}

			pointer base() const{
				return _ptr;
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

			difference_type operator-(const iterators &I){
				return (_ptr - I._ptr);
			}

		private:
			pointer _ptr;
	};

	template <class T>
	iterators<T> operator+(const typename iterators<T>::difference_type &val, const iterators<T> &I){
		iterators<T> tmp(I.base() + val) ;
		return tmp;
	}

	template <class Iterator>
	class reverse_iterator
	{
		public:
			typedef std::size_t size_type;
			typedef Iterator iterator_type;
			typedef typename ft::iterator_traits<iterator_type>::difference_type difference_type;
			typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
			typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
			typedef typename ft::iterator_traits<iterator_type>::reference reference;
			typedef typename ft::iterator_traits<iterator_type>::iterator_category iterator_category;

			// * Constructors
			reverse_iterator(){
				// std::cout << "\e[0;33mDefault Constructor called of reverse_iterator\e[0m" << std::endl;
			}

			reverse_iterator (iterator_type it) {
				// std::cout << "\e[0;33mDefault Constructor called of reverse_iterator\e[0m" << std::endl;
				_ptr = it;
			}

			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it) {
				_ptr = rev_it.base();
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

			iterator_type base() const {
				return _ptr.base();
			}

			reverse_iterator operator+ (difference_type n) const {
				return reverse_iterator(_ptr.base() - n);
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

			reverse_iterator& operator+= (difference_type n) {
				_ptr -= n;
				return *this;
			}

			reverse_iterator operator- (difference_type n) const {
				return  reverse_iterator(_ptr.base() + n);
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

			reverse_iterator& operator-= (difference_type n) {
				_ptr += n;
				return *this;
			}

			reference operator[](size_type index){
				return _ptr.base()[-index - 1];
			}

			reference operator*(){
				return *(_ptr.base() - 1);
			}

			pointer operator->(){
				return &(operator*());
			}

		private:
			iterator_type _ptr;
	};

	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() == rhs.base();
	}

	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() != rhs.base();
	}

	template <class Iterator>
	bool operator< (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() > rhs.base();
	}

	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() >= rhs.base();
	}

	template <class Iterator>
	bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() < rhs.base();
	}

	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() <= rhs.base();
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n,
				const reverse_iterator<Iterator>& rev_it) {
		return rev_it  + n;
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs) {
		return lhs.base() - rhs.base();
	}

}

#endif
