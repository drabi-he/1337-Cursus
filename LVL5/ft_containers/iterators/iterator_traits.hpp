/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:48:19 by hdrabi            #+#    #+#             */
/*   Updated: 2022/11/07 14:35:45 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include <iostream>
# include <string>

namespace ft {

	template <class Category, class T, class Distance = std::ptrdiff_t,
			class Pointer = T*, class Reference = T&>
	struct iterator {
		public:
			typedef T         value_type;
			typedef Distance  difference_type;
			typedef Pointer   pointer;
			typedef Reference reference;
			typedef Category  iterator_category;
	};

	template <class Iterator>
	class iterator_traits{
		public :
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::difference_type  difference_type;
		typedef typename Iterator::pointer   pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category  iterator_category;
	};

	template <class T>
	class iterator_traits<T*>{
		public:
		typedef T         value_type;
		typedef std::ptrdiff_t  difference_type;
		typedef T*   pointer;
		typedef T& reference;
		typedef std::random_access_iterator_tag  iterator_category;
	};

	template <class T>
	class iterator_traits<const T*>{
		public :
		typedef T         value_type;
		typedef std::ptrdiff_t  difference_type;
		typedef const T*   pointer;
		typedef const T& reference;
		typedef std::random_access_iterator_tag  iterator_category;
	};

}

#endif