/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:12:21 by hdrabi            #+#    #+#             */
/*   Updated: 2022/07/13 11:56:54 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <string>
# include <map>
# include "stdexcept"

#include "../iterators/iterator.hpp"
#include "../xtra/enable_if.hpp"
#include "../xtra/is_integral.hpp"
#include "../xtra/equal.hpp"
#include "../xtra/lexicographical_compare.hpp"
#include "../xtra/pair.hpp"
#include "../redBlackTree/RedBlackTree.hpp"

namespace ft {
    
    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > > class map
    {
        public :
            typedef Key key_type;
            typedef T mapped_type;
            typedef ft::pair<const Key,T> value_type;
            typedef Compare key_compare;
            typedef Alloc allocator_type;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename RedBlackTree<key_type, mapped_type>::iterator iterator;
            typedef typename RedBlackTree<key_type, mapped_type>::const_iterator const_iterator;
            typedef typename RedBlackTree<key_type, mapped_type>::reverse_iterator reverse_iterator;
            typedef typename RedBlackTree<key_type, mapped_type>::const_reverse_iterator const_reverse_iterator;
            typedef std::ptrdiff_t difference_type;
            typedef std::size_t size_type;

            private :
                RedBlackTree<key_type, mapped_type> _tree;
                allocator_type _alloc;
                key_compare _comp;

            public :

                
    };
}




#endif