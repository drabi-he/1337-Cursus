/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:12:21 by hdrabi            #+#    #+#             */
/*   Updated: 2022/07/16 13:23:01 by hdrabi           ###   ########.fr       */
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
                RedBlackTree<value_type> _tree;
                allocator_type _alloc;
                key_compare _comp;

            public :

            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {
                _comp = comp;
                _alloc = alloc;
            }

            template <class InputIterator>
            map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()){
                _comp = comp;
                _alloc = alloc;
                for (; first != last; ++first)
                    _tree.add(*first);
            }

            map (const map& x) {
                *this = x;
            }

            map& operator= (const map& x) {
                if (this != &x) {
                    _comp = x._comp;
                    _alloc = x._alloc;
                    _tree = x._tree;
                }
                return *this;
            }

            ~map () {}

            iterator begin() {
                return _tree.begin();
            }
            
            const_iterator begin() const {
                return _tree.begin();
            }

            iterator end() {
                return nullptr;
            }
            
            const_iterator end() const {
                return nullptr;
            }

            reverse_iterator rbegin() {
                return _tree.end();
            }
            
            const_reverse_iterator rbegin() const {
                return _tree.end();
            }

            reverse_iterator rend() {
                return nullptr;
            }
            
            const_reverse_iterator rend() const {
                return nullptr;
            }

            bool empty() const {
                return _tree.size() == 0;
            }

            size_type size() const {
                return _tree.size();
            }

            size_type max_size() const {
                return _tree.max_size();
            }

            mapped_type& operator[] (const key_type& k) {
                // _tree.printTree(3);
                value_type v(k, mapped_type());
                typename RedBlackTree<value_type>::node_pointer node = _tree.find(v);

                std::cout << "node: " << node << std::endl;
                
                if (!node) {
                    std::cout << "add" << std::endl;
                    _tree.add(v);
                    node = _tree.find(v);
                }
                return node->data.second;
            }
    };
}




#endif