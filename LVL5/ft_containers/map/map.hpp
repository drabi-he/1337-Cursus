/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:12:21 by hdrabi            #+#    #+#             */
/*   Updated: 2022/11/12 11:56:48 by hdrabi           ###   ########.fr       */
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
            class value_compare;
            typedef Key key_type;
            typedef T mapped_type;
            typedef ft::pair<const key_type, mapped_type> value_type;
            typedef Compare key_compare;
            typedef Alloc allocator_type;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename RedBlackTree<value_type, key_compare, allocator_type>::iterator iterator;
            typedef typename RedBlackTree<value_type, key_compare, allocator_type>::const_iterator const_iterator;
            typedef typename RedBlackTree<value_type, key_compare, allocator_type>::reverse_iterator reverse_iterator;
            typedef typename RedBlackTree<value_type, key_compare, allocator_type>::const_reverse_iterator const_reverse_iterator;
            typedef std::ptrdiff_t difference_type;
            typedef std::size_t size_type;

        private :
            typedef RedBlackTree<value_type, value_compare, allocator_type> RBT;
            RBT _tree;
            allocator_type _alloc;
            key_compare _comp;

        public :

            // *************************************** Iterators *************************************** //
            explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(value_compare(comp), alloc), _alloc(alloc), _comp(comp) {}

            template <class InputIterator>
            map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(value_compare(comp), alloc), _alloc(alloc), _comp(comp)
            {
                for (; first != last; first++)
                    _tree.add(*first);
            }

            map(const map& x) {
                *this = x;
            }


            // *************************************** Iterators *************************************** //
            map& operator=(const map& x) {
                if (this != & x){
                    _tree = x._tree;
                    _alloc = x._alloc;
                    _comp = x._comp;
                }
                return *this;
            }


            // *************************************** Destructor *************************************** //
            ~map() {
            }

            class value_compare : std::binary_function<value_type, value_type, bool>
            {
                protected:
                    key_compare comp;

                public:
                    typedef bool result_type;
                    typedef value_type first_argument_type;
                    typedef value_type second_argument_type;
                    bool operator()(const value_type &x, const value_type &y) const
                    {
                        return comp(x.first, y.first);
                    }
                    value_compare(const key_compare &c = key_compare()) : comp(c) {}
            };


            // *************************************** Iterators *************************************** //
            iterator begin() {
                return iterator(_tree.begin());
            }

            const_iterator begin() const {
                return const_iterator(_tree.begin());
            }

            iterator end() {
                return iterator(_tree.end());
            }

            const_iterator end() const {
                return const_iterator(_tree.end());
            }

            reverse_iterator rbegin() {
                return reverse_iterator(_tree.rbegin());
            }

            const_reverse_iterator rbegin() const {
                return const_reverse_iterator(_tree.rbegin());
            }

            reverse_iterator rend() {
                return reverse_iterator(_tree.rend());
            }

            const_reverse_iterator rend() const {
                return const_reverse_iterator(_tree.rend());
            }


            // *************************************** Capacity *************************************** //
            bool empty() const {
                return _tree.size() == 0;
            }

            size_type size() const {
                return _tree.size();
            }

            size_type max_size() const {
                return _tree.max_size();
            }


            // *************************************** Element access *************************************** //
            mapped_type& operator[] (const key_type& k) {
                value_type v(k, mapped_type());
                typename RBT::node_pointer node = _tree.find(v);

                if (!node) {
                    _tree.add(v);
                    node = _tree.find(v);
                }
                return node->data.second;
            }


            // *************************************** Modifiers *************************************** //
            ft::pair<iterator,bool> insert (const value_type& val) {
                typename RBT::node_pointer node = _tree.find(val);

                bool added = false;
                if (!node) {
                    _tree.add(val);
                    added = true;
                    node = _tree.find(val);
                }
                return ft::pair<iterator,bool>(iterator(node), added);
            }

            iterator insert (iterator position, const value_type& val) {
                (void)position;
                typename RBT::node_pointer node = _tree.find(val);

                if (!node) {
                    _tree.add(val);
                    node = _tree.find(val);
                }
                return iterator(node);
            }

            template <class InputIterator>
            void insert (InputIterator first, InputIterator last) {

                typename RBT::node_pointer node;

                for (; first != last; first++) {
                    node = _tree.find(*first);
                    if (!node)
                        _tree.add(*first);
                }
            }

            void erase (iterator position) {
                _tree.erase(*position);
            }

            size_type erase (const key_type& k) {
                value_type v(k, mapped_type());
                typename RBT::node_pointer node = _tree.find(v);
                if (node) {
                    _tree.erase(v);
                    return 1;
                }
                return 0;
            }

            void erase (iterator first, iterator last) {
                while (first != last) {
                    erase(first++);
                }
            }

            void swap (map& x) {
                map tmp = x;
                x = *this;
                *this = tmp;
            }

            void clear() {
                _tree.clear();
            }


            // *************************************** Observers *************************************** //
            value_compare value_comp() const {
                return value_compare(_comp);
            }

            key_compare key_comp() const {
                return _comp;
            }


            // *************************************** Operations *************************************** //
            iterator find (const key_type& k) {
                value_type v(k, mapped_type());
                typename RBT::node_pointer node = _tree.find(v);
                return iterator(node);
            }

            const_iterator find (const key_type& k) const {
                value_type v(k, mapped_type());
                typename RBT::node_pointer node = _tree.find(v);
                return const_iterator(node);
            }

            size_type count (const key_type& k) const {
                value_type v(k, mapped_type());
                typename RBT::node_pointer node = _tree.find(v);
                return node ? 1 : 0;
            }

            iterator lower_bound (const key_type& k) {
                typename RBT::node_pointer tmp = _tree.getRoot();
                typename RBT::node_pointer node = NULL;

                while (tmp != _tree.getNull()) {
                    if (_comp(tmp->data.first, k))
                        tmp = tmp->right;
                    else
                    {
                        node = tmp;
                        tmp = tmp->left;
                    }
                }
                return iterator(node);
            }

            const_iterator lower_bound (const key_type& k) const {
                typename RBT::node_pointer tmp = _tree.getRoot();
                typename RBT::node_pointer node = NULL;

                while (tmp != _tree.getNull()) {
                    if (_comp(tmp->data.first, k))
                        tmp = tmp->right;
                    else
                    {
                        node = tmp;
                        tmp = tmp->left;
                    }
                }
                return const_iterator(node);
            }

            iterator upper_bound (const key_type& k) {
                typename RBT::node_pointer tmp = _tree.getRoot();
                typename RBT::node_pointer node = NULL;

                while (tmp != _tree.getNull()) {
                    if (_comp(k, tmp->data.first)) {
                        node = tmp;
                        tmp = tmp->left;
                    }
                    else
                    {
                        tmp = tmp->right;
                    }
                }
                return iterator(node);
            }

            const_iterator upper_bound (const key_type& k) const {
                typename RBT::node_pointer tmp = _tree.getRoot();
                typename RBT::node_pointer node = NULL;

                while (tmp != _tree.getNull()) {
                    if (_comp(k, tmp->data.first)) {
                        node = tmp;
                        tmp = tmp->left;
                    }
                    else
                    {
                        tmp = tmp->right;
                    }
                }
                return const_iterator(node);
            }

            ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
                return ft::pair<const_iterator,const_iterator>(lower_bound(k), upper_bound(k));
            }

            ft::pair<iterator,iterator> equal_range (const key_type& k) {
                return ft::pair<iterator,iterator>(lower_bound(k), upper_bound(k));
            }

            // *************************************** Allocator *************************************** //
            allocator_type get_allocator() const {
                return _alloc;
            }
    };
}

#endif