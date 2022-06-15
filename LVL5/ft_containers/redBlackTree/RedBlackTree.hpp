/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 10:38:28 by hdrabi            #+#    #+#             */
/*   Updated: 2022/06/15 11:15:38 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../xtra/pair.hpp"

namespace ft {
    
    template <class T>
    struct Node {
        T value;
        bool isBlack;
        bool isLeftChild;
        Node *parent;
        Node *left;
        Node *right;
        
        Node () {
            value = T();
            isBlack = false;
            parent = nullptr;
            left = nullptr;
            right = nullptr;
            isLeftChild = false;
        }
    };
    
    template <class Key, class Value, class Alloc = std::allocator< Node< ft::pair< Key, Value > > > >
    class RedBlackTree
    {
        typedef std::size_t size_type;
        typedef Key key_type;
        typedef Value mapped_type;
        typedef Alloc allocator_type;
        typedef ft::pair< key_type, mapped_type> value_type;
        typedef Node<value_type> Node;
        typedef Node* nodePtr;
        typedef Node& nodeRef;
        
        public:
            nodePtr _root;
            nodePtr _null_node;
            size_type _size;
            allocator_type _alloc;
            
            nodePtr newNode(Key key, Value value) {
                nodePtr _new = _alloc.allocate(1);
                _new->value->first = key;
                _new->value->second = value;
            }
            
            // void add (nodePtr parent, nodePtr newNode) {};
            
        public:
            RedBlackTree() : _root(nullptr), _size(0) {
                _null_node = _alloc.allocate(1);
                _null_node->isBlack = true;
            };
            
            ~RedBlackTree() {
                _alloc.deallocate(_null_node, 1);
            };
            
            void add (Key key, Value value) {
                nodePtr _new = newNode(key, value);

                if (_root == nullptr) {
                    _root = _new;
                    _root->isBlack = true;
                    _size++;
                    return ;
                }
                // add (_root, newNode);
                _size++;
            }
    };
    
}