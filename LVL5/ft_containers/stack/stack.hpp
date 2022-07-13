/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:21:01 by hdrabi            #+#    #+#             */
/*   Updated: 2022/07/09 16:08:40 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <iostream>
# include <string>
# include "../vector/vector.hpp"

namespace ft {
	
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef T value_type;
			typedef Container container_type;
			typedef std::size_t size_type;

			template <class U, class V>
			friend bool operator== (const stack<U,V>& lhs, const stack<U,V>& rhs);
			template <class U, class V>
			friend bool operator!= (const stack<U,V>& lhs, const stack<U,V>& rhs);
			template <class U, class V>
			friend bool operator< (const stack<U,V>& lhs, const stack<U,V>& rhs);
			template <class U, class V>
			friend bool operator<= (const stack<U,V>& lhs, const stack<U,V>& rhs);
			template <class U, class V>
			friend bool operator> (const stack<U,V>& lhs, const stack<U,V>& rhs);
			template <class U, class V>
			friend bool operator>= (const stack<U,V>& lhs, const stack<U,V>& rhs);
			
			
			// Constructors
			explicit stack (const container_type& ctnr = container_type())
			{
				std::cout << "\e[0;33mDefault Constructor called of stack\e[0m" << std::endl;
				_c = ctnr;
			}

			bool empty() const {
				return _c.empty();
			}

			size_type size() const {
				return _c.size();
			}

			value_type& top() {
				return _c.back();
			}
			const value_type& top() const {
				return _c.back();
			}

			void push (const value_type& val) {
				_c.push_back(val);
			}

			void pop() {
				_c.pop_back();
			}
			
		private:
			container_type _c;
	};

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs._c == rhs._c;
	}

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs._c != rhs._c;
	}

	template <class T, class Container>
	bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs._c < rhs._c;
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs._c <= rhs._c;
	}

	template <class T, class Container>
	bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs._c > rhs._c;
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs._c >= rhs._c;
	}
}


#endif