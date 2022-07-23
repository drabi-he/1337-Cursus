/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:21:01 by hdrabi            #+#    #+#             */
/*   Updated: 2022/07/23 18:47:33 by hdrabi           ###   ########.fr       */
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
			
			
            // *************************************** Constructors *************************************** //
			explicit stack (const container_type& ctnr = container_type())
			{
				// std::cout << "\e[0;33mDefault Constructor called of stack\e[0m" << std::endl;
				c = ctnr;
			}

            // *************************************** OTHERS *************************************** //
			bool empty() const {
				return c.empty();
			}

			size_type size() const {
				return c.size();
			}

			value_type& top() {
				return c.back();
			}

			const value_type& top() const {
				return c.back();
			}

			void push (const value_type& val) {
				c.push_back(val);
			}

			void pop() {
				c.pop_back();
			}

		protected:
			container_type c;
	};

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.c == rhs.c;
	}

	template <class T, class Container>
	bool operator!= (const ft::stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.c != rhs.c;
	}

	template <class T, class Container>
	bool operator< (const ft::stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.c < rhs.c;
	}

	template <class T, class Container>
	bool operator<= (const ft::stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.c <= rhs.c;
	}

	template <class T, class Container>
	bool operator> (const ft::stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.c > rhs.c;
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.c >= rhs.c;
	}
}


#endif