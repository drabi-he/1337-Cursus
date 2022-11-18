/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:36:59 by hdrabi            #+#    #+#             */
/*   Updated: 2022/11/14 15:51:26 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <string>
# include "stdexcept"

#include "../iterators/iterator.hpp"
#include "../xtra/enable_if.hpp"
#include "../xtra/is_integral.hpp"
#include "../xtra/equal.hpp"
#include "../xtra/lexicographical_compare.hpp"

namespace ft {

	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:

			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;

			typedef iterators<pointer> iterator;
			typedef iterators<const_pointer> const_iterator;
			typedef reverse_iterator<const_iterator> const_reverse_iterator;
			typedef reverse_iterator<iterator> reverse_iterator;
			typedef std::ptrdiff_t difference_type;
			typedef std::size_t size_type;

            // *************************************** Constructors *************************************** //
			explicit vector (const allocator_type& alloc = allocator_type())
			{
				_data = nullptr;
				_size = 0;
				_capacity = 0;
				_alloc = alloc;
				// std::cout << "\e[0;33mDefault Constructor called of vector\e[0m" << std::endl;
			}

			vector(const vector &x)
			{
				// std::cout << "\e[0;33mCopy Constructor called of vector\e[0m" << std::endl;
				_capacity = 0;
				*this = x;
			}

			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			{
				// std::cout << "\e[0;33mFields Constructor called of vector\e[0m" << std::endl;
				_size = n;
				_capacity = n;
				_alloc = alloc;
				_data = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _capacity ; i++)
					_data[i] = val;
			}

			template <class InputIterator>
			vector (InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value , InputIterator>::type last,
					const allocator_type& alloc = allocator_type())
			{
				// std::cout << "\e[0;33mRange Constructor called of vector\e[0m" << std::endl;
				_size = last - first;
				_capacity = last - first;
				_alloc = alloc;
				_data = _alloc.allocate(_capacity);
				int i = 0;
				for (InputIterator it = first ; it != last ; it++)
					_data[i++] = *it;
			}

            // *************************************** Destructor *************************************** //
			~vector()
			{
				// std::cout << "\e[0;31mDestructor called of vector\e[0m" << std::endl;
				if (_capacity > 0)
					_alloc.deallocate(_data, _capacity);
				_capacity.~size_type();
				_size.~size_type();
				_alloc.~allocator_type();
			}


            // *************************************** Assign *************************************** //
			vector & operator=(const vector &x)
			{
				if (this != &x){
					if (_capacity < x._capacity)
					{
						if (_capacity > 0)
							_alloc.deallocate(_data, _capacity);
						_alloc = x._alloc;
						_data = _alloc.allocate(x._size);
						_capacity = x._size;
					}
					_size = x._size;
					for (size_type i = 0; i < _size ;  i++)
						_data[i] = x._data[i];
				}
				return *this;
			}


            // *************************************** Iterators *************************************** //
			iterator begin(){
				return _data;
			}

			const_iterator begin() const {
				return _data;
			}

			iterator end(){
				return _data + _size;
			}

			const_iterator end() const {
				return _data + _size;
			}

			reverse_iterator rbegin(){
				return reverse_iterator(end());
			}

			const_reverse_iterator rbegin() const {
				return const_reverse_iterator(end());
			}

			reverse_iterator rend(){
				return reverse_iterator(begin());
			}

			const_reverse_iterator rend() const {
				return const_reverse_iterator(begin());
			}


			// *************************************** Capacity *************************************** //
			size_type size() const {
				return _size;
			}

			size_type max_size() const {
				return _alloc.max_size();
			}

			void resize (size_type n, value_type val = value_type()) {
				if (_size == n)
					return ;
				else if (n < _size) {
					for (size_type i = n ; i < _size ; i++)
						_data[i].~value_type();
					_size = n;
				} else {
					if (this->_capacity * 2 <= n)
						this->_capacity = n;
					else if (this->_capacity < n && this->_capacity * 2 > n)
						this->_capacity *= 2;
					copy(n, val);
				}
			}

			size_type capacity() const {
				return _capacity;
			}

			bool empty() const {
				return _size == 0 ;
			}

			void reserve (size_type n) {
				if (n <= _capacity)
					return ;
				_capacity = n;
				copy(_size);
			}


			// *************************************** Element access *************************************** //
			reference operator[] (size_type n){
				// if (n < 0 || n >= _size)
				// 	throw std::range_error("Index out of bound");
				return _data[n];
			}

			const_reference operator[] (size_type n) const {
				// if (n < 0 || n >= _size)
				// 	throw std::range_error("Index out of bound");
				return _data[n];
			}

			reference at (size_type n){
				if (n < 0 || n >= _size)
					throw std::out_of_range("vector");
				return _data[n];
			}

			const_reference at (size_type n) const {
				if (n < 0 || n >= _size)
					throw std::range_error("vector");
				return _data[n];
			}

			reference front() {
				// if (_data == nullptr)
				// 	throw std::range_error("Index out of bound");
				return _data[0];
			}

			const_reference front() const {
				// if (_data == nullptr)
				// 	throw std::range_error("Index out of bound");
				return _data[0];
			}

			reference back() {
				// if (_data == nullptr)
				// 	throw std::range_error("Index out of bound");
				return _data[_size - 1];
			}

			const_reference back() const {
				// if (_data == nullptr)
				// 	throw std::range_error("Index out of bound");
				return _data[_size - 1];
			}


			// *************************************** Modifiers *************************************** //
			template <class InputIterator>
			void assign (InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value , InputIterator>::type last) {
				int j = 0;
				if ((long long)_capacity >= last - first){
					for (InputIterator it = first ; it < last ; it++)
						_data[j++] = *it;
				} else {
					_capacity = last - first;
					_alloc.deallocate(_data, _size);
					_data = _alloc.allocate(_capacity);
					for (InputIterator it = first ; it < last ; it++)
						_data[j++] = *it;
				}
				_size = last - first;
			}

			void assign (size_type n, const value_type& val) {
				if (_capacity >= n) {
					for (size_type i = 0 ; i < n ; i++)
						_data[i] = val;
				} else {
					_capacity = n;
					_alloc.deallocate(_data, _size);
					_data = _alloc.allocate(_capacity);
					for (size_type i = 0; i < n ; i++)
						_data[i] = val;
				}
				_size = n;
			}

			void push_back (const value_type& val){
				if (_size < _capacity)
					_data[_size++] = val;
				else {
					if (_capacity == 0)
						_capacity++;
					else
						_capacity *= 2;
					copy(_size + 1, val);
				}
			}

			void pop_back() {
				_data[_size].~value_type();
				_size--;
			}

			iterator insert (iterator position, const value_type& val){
				size_type pos;
				if (_size < _capacity) {
					pos = _size - 1;
					for (iterator it = end() - 1 ; it > position ; it--) {
						_data[pos + 1] = _data[pos];
						pos--;
					}
					_data[pos] = val;
				} else {
					value_type* tmp;
					pos = 0;
					if (_capacity == 0)
						_capacity++;
					else
						_capacity *= 2;
					tmp = _alloc.allocate(_capacity);
					for (iterator it = begin() ; it < position ; it++) {
						tmp[pos] = _data[pos];
						pos++;
					}
					tmp[pos] = val;
					size_type i = pos + 1;
					for (iterator it = position + 1 ; it <= end() ; it++) {
						tmp[i] = _data[i - 1];
						i++;
					}
					_alloc.deallocate(_data, _size);
					_data = tmp;
				}
				_size++;
				return begin() + pos;
			}

			void insert (iterator position, size_type n, const value_type& val) {
				size_type pos;
				if (_size + n < _capacity) {
					pos = _size - 1;
					for (iterator it = end() - 1 ; it > position ; it--) {
						_data[pos + n] = _data[pos];
						pos--;
					}
					for (size_type i = 0 ; i < n ; i++)
						_data[pos + i] = val;
				} else {
					value_type* tmp;
					pos = 0;
					if (_size + n <= _capacity * 2)
						_capacity *= 2;
					else
						_capacity = _size + n;
					tmp = _alloc.allocate(_capacity);
					for (iterator it = begin() ; it < position ; it++) {
						tmp[pos] = _data[pos];
						pos++;
					}
					for (size_type i = 0 ; i < n ; i++)
						tmp[pos + i] = val;
					size_type i = pos + n;
					for (iterator it = position + 1 ; it <= end() ; it++) {
						tmp[i] = _data[i - n];
						i++;
					}
					_alloc.deallocate(_data, _size);
					_data = tmp;
				}
				_size += n;
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value , InputIterator>::type last)
			{
				size_type pos;
				size_type n = (last - first);
				if (last - first < 0)
					return ;
				if (_size + n < _capacity) {
					pos = _size - 1;
					for (iterator it = end() - 1 ; it >= position ; it--) {
						_data[pos + n] = *(it);
						if (pos)
							pos--;
					}
					iterator it = first;
					for (size_type i = 0 ; i < n ; i++)
						_data[pos + i] = *(it++);
				} else {
					value_type* tmp;
					pos = 0;
					if (_size + n <= _capacity * 2)
						_capacity *= 2;
					else
						_capacity = _size + n;
					tmp = _alloc.allocate(_capacity);
					for (iterator it = begin() ; it < position ; it++) {
						tmp[pos] = _data[pos];
						pos++;
					}
					iterator it = first;
					for (size_type i = 0 ; i < n ; i++)
						tmp[pos + i] = *(it++);
					size_type i = pos + n;
					for (iterator it = position + 1 ; it <= end() ; it++) {
						tmp[i] = _data[i - n];
						i++;
					}
					_alloc.deallocate(_data, _size);
					_data = tmp;
				}
				_size += n;
			}

			iterator erase (iterator position) {
				for (iterator it = position ; it < end() - 1 ; it++) {
					*it = *(it + 1);
				}
				_size--;
				return position;
			}

			iterator erase (iterator first, iterator last) {
				size_type n = last - first;
				for (iterator it = first ; it < last ; it++) {
					if (it + n >= end())
						break ;
					*(it) = *(it + n);
				}
				if (n > 0)
					_size -= n;
				for (iterator it = last ; it < end() ; it++) {
					*(it) = *(it + n);
				}
				return first;
			}

			void swap (vector& x) {
				value_type* tmp_data = x._data;
				allocator_type tmp_alloc = x._alloc;
				size_type tmp_size = x._size;
				size_type tmp_capacity = x._capacity;

				x._data = this->_data;
				x._alloc = this->_alloc;
				x._capacity = this->_capacity;
				x._size = this->_size;

				this->_data = tmp_data;
				this->_alloc = tmp_alloc;
				this->_size = tmp_size;
				this->_capacity = tmp_capacity;
			}

			void clear() {
				for (size_type i = 0 ; i < _size ; i++)
					_data[i].~value_type();
				_size = 0;
			}


			// *************************************** Allocator *************************************** //
			allocator_type get_allocator() const {
				return _alloc;
			}

		private:
			value_type* _data;
			size_type _size;
			size_type _capacity;
			Alloc _alloc;

			void	copy(size_type n, const value_type& val = value_type()) {
				value_type* tmp;

				tmp = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size ; i++)
					tmp[i] = _data[i];
				for (size_type i = _size; i < n ; i++)
					tmp[i] = val;
				if (_size >= 0)
					_alloc.deallocate(_data, _size);
				_size = n;
				_data = tmp;
			}

	};

	template <class T, class Alloc>
	bool operator== (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
			if (lhs.size() != rhs.size() || !ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
				return false;
			return true;
		}

	template <class T, class Alloc>
	bool operator!= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator< (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

	template <class T, class Alloc>
	bool operator> (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
			return rhs < lhs;
		}

	template <class T, class Alloc>
	bool operator<= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
			return !(rhs < lhs);
		}

	template <class T, class Alloc>
	bool operator>= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
			return !(lhs < rhs);
		}

	template <class T, class Alloc>
	void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y) {
		x.swap(y);
	}

}


#endif