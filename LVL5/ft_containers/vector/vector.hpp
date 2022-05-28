/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:56:36 by hdrabi            #+#    #+#             */
/*   Updated: 2022/05/28 17:57:18 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <string>
# include <stdexcept>

// # include <memory>

namespace ft {
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		
		public:
		
			typedef T* iterator;
			typedef const T* c_iterator;
			typedef T* r_iterator;
			typedef const T* c_r_iterator;
			
			// * Constructors
			vector(){
				_size = 0;
				_capacity = 0;
				_data = nullptr;
				std::cout << "\e[0;33mDefault Constructor called of vector\e[0m" << std::endl;
			}
			
			vector(const vector &copy){
				std::cout << "\e[0;33mCopy Constructor called of vector\e[0m" << std::endl;
				*this = copy;
			}
			
			vector(std::size_t size){
				_size = size;
				_capacity = _size;
				_data = alloc.allocate(size);
				for (std::size_t i = 0; i < this->_size ; i++)
					*(this->_data + i) = 0;
				std::cout << "\e[0;33mFields Constructor called of vector\e[0m" << std::endl;
			}
			
			// ! Destructor
			~vector(){
				std::cout << "\e[0;31mDestructor called of vector\e[0m" << std::endl;
				this->alloc.deallocate(this->_data, this->_size);
			}
			
			// Operators
			vector & operator=(const vector &assign){
				_size = assign._size;
				_capacity = assign._capacity;
				_data = assign._data;
				return *this;
			}

			// ? iterators
			iterator begin(){
				return this->_data;
			}

			iterator end(){
				return this->_data + this->_size;
			}

			c_iterator cbegin() const{
				return this->_data;
			}

			c_iterator cend() const{
				return this->_data + this->_size;
			}
			
			r_iterator rbegin(){
				return this->end() - 1;
			}

			r_iterator rend(){
				return this->begin() - 1;
			}

			c_r_iterator crbegin() const{
				return this->cend() - 1;
			}

			c_r_iterator crend() const{
				return this->cbegin() - 1;
			}

			// ? Capacity
			std::size_t size(){
				return this->_size;
			}
			
			std::size_t max_size(){
				return this->alloc.max_size();
			}

			void resize(size_t n, T val = static_cast<T>(0)){
				T *tmp;
				if (n == this->_size)
					return ;
				else if (n < this->_size)
					this->_size = n;
				else {
					if (this->_capacity * 2 <= n)
						this->_capacity = n;
					else if (this->_capacity < n && this->_capacity * 2 > n)
						this->_capacity *= 2;
					tmp = this->_data;
					this->_data = alloc.allocate(this->_capacity);
					for (std::size_t i = 0; i < this->_size ; i++)
						*(this->_data + i) = *(tmp + i);
					for (std::size_t i = this->_size ; i < n ; i++)
						*(this->_data + i) = val;
					this->alloc.deallocate(tmp, this->_size);
					this->_size = n;
				}
			}

			std::size_t capacity(){
				return this->_capacity;
			}

			bool empty() const {
				if (this->_size == 0)
					return (true);
				return (false);
			}
			
			void reserve(size_t n){
				if (n <= this->_capacity)
					return ;
					
				T *tmp;
				this->_capacity = n;
				tmp = this->_data;
				this->_data = this->alloc.allocate(this->_capacity);
				for (std::size_t i = 0; i < this->_size ; i++)
					*(this->_data + i) = *(tmp + i);
				this->alloc.deallocate(tmp, this->_size);
			}

			void shrink_to_fit(){
				if (this->_size == this->_capacity)
					return ;
				T *tmp;
				this->_capacity = this->_size;
				tmp = this->_data;
				this->_data = this->alloc.allocate(this->_capacity);
				for (std::size_t i = 0; i < this->_size ; i++)
					*(this->_data + i) = *(tmp + i);
				this->alloc.deallocate(tmp, this->_size);
			}
			
			// ? Element access
			T& operator[](int index) {
				// if (index < 0 || index >= (int)this->_size)
        		// 	throw std::logic_error("out of bound");
				return this->_data[index];
			}
			
			const T& operator[](int index) const {
				// if (index < 0 || index >= (int)this->_size)
        		// 	throw std::logic_error("out of bound");
				return this->_data[index];
			}
			
			T& at(int index) {
				if (index < 0 || index >= (int)this->_size)
        			throw std::logic_error("vector");
				return *(this->_data + index);
			}
			
			const T& at(int index) const {
				if (index < 0 || index >= (int)this->_size)
        			throw std::logic_error("vector");
				return *(this->_data + index);
			}
			
			T& front() {
				// if (this->_data == nullptr)
        		// 	throw std::logic_error("vector not allocated");
				return *(this->_data);
			}
			
			const T& front() const {
				// if (this->_data == nullptr)
        		// 	throw std::logic_error("vector not allocated");
				return *(this->_data);
			}

			T& back() {
				// if (this->_data == nullptr)
        		// 	throw std::logic_error("vector not allocated");
				return *(this->_data + this->_size - 1);
			}
			
			const T& back() const {
				// if (this->_data == nullptr)
        		// 	throw std::logic_error("vector not allocated");
				return *(this->_data + this->_size - 1);
			}

			T* data() {
				if (this->_data == nullptr)
        			throw std::logic_error("vector not allocated");
				return this->_data;
			}
			
			const T* data() const {
				if (this->_data == nullptr)
        			throw std::logic_error("vector not allocated");
				return this->_data;
			}
			
			// ? Modifiers

			void assign(std::size_t n, const std::size_t &val){
				if (this->_capacity >= n){
					for (std::size_t i = 0 ; i < n ; i++)
						*(this->_data + i) = val;
				} else {
					this->_capacity = n;
					this->alloc.deallocate(this->_data, this->_size);
					this->_data = this->alloc.allocate(this->_capacity);
					for (std::size_t i = 0; i < n ; i++)
						*(this->_data + i) = val;
				}
				this->_size = n;
			}
			
			void assign(iterator first, iterator last){
				int j = 0;
				if (this->_capacity >= (std::size_t)(last - first)){
					for (iterator i = first ; i < last ; i++){
						*(this->_data + j) = *i;
						j++;
					}
				} else {
					this->_capacity = last - first;
					this->alloc.deallocate(this->_data, this->_size);
					this->_data = this->alloc.allocate(this->_capacity);
					for (iterator i = first ; i < last ; i++){
						*(this->_data + j) = *i;
						j++;
					}
				}
				this->_size = last - first;
			}
			
			void push_back(const T &val){
				if (this->_size < this->_capacity){
					*(this->_data + this->_size) = val;
					this->_size++;	
				} else {
					T *tmp;
					if (this->_capacity == 0)
						this->_capacity++;
					else
						this->_capacity *= 2;
					tmp = this->_data;
					this->_data = this->alloc.allocate(this->_capacity);
					for (std::size_t i = 0; i < this->_size ; i++)
						*(this->_data + i) = *(tmp + i);
					*(this->_data + this->_size) = val;
					this->alloc.deallocate(tmp, this->_size);
					this->_size++;
				}
			}
			
			void pop_back(){
				if (this->_size == 0)
					return ;
				this->_size--;
			}
		private:
			std::size_t _size;
			std::size_t _capacity;
			T* _data;
			Alloc alloc;
			
	};
}

#endif