/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:12:21 by hdrabi            #+#    #+#             */
/*   Updated: 2022/06/28 16:27:28 by hdrabi           ###   ########.fr       */
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
    
    template < class Key, class T, class Compare = std::less<Key>,  class Alloc = std::allocator<ft::pair<const Key,T> > >
    class map {
        
        public:
            typedef ft::pair<const Key, T> value_type;
            typedef Key key_type;
            typedef T mapped_type;
            typedef Compare key_compare;
            typedef Alloc allocator_type;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename std::size_t size_type;
            typedef typename std::ptrdiff_t difference_type;

            
        public:
            map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {
                _comp = comp;
                _alloc = alloc;
            }

            template <class InputIterator>
            map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type()) {
                _comp = comp;
                _alloc = alloc;
            }

            map (const map& x) {
                *this = x;
            }

            ~map() {
                _rbTree.~RedBlackTree();
            }

            map& operator= (const map& x) {
                if (this != &x) {
                    _comp = x._comp;
                    _alloc = x._alloc;
                    _rbTree = x._rbTree;
                }
                return *this;
            }

        private:
            RedBlackTree<value_type, key_compare, allocator_type> _rbTree;
            allocator_type _alloc;
            key_compare _comp;
            
    };
}




#endif