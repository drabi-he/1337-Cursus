/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 10:38:28 by hdrabi            #+#    #+#             */
/*   Updated: 2022/07/08 11:47:43 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP

#include <iostream>
#include "../xtra/pair.hpp"

namespace ft {
    
    template <class T>
    struct Node
    {
        T data;
        bool isBlack;
        bool isLeftChild;
        Node<T> *left;
        Node<T> *right;
        Node<T> *parent;
        
        Node(T data) : data(data), isBlack(false), isLeftChild(false),
                left(nullptr), right(nullptr), parent(nullptr) {}
        
    };

    template <class Key, class Value, class Alloc = std::allocator< Node < ft::pair < const Key, Value> > > >
    class RedBlackTree
    {
        public:
            typedef std::size_t size_type;
            typedef Key key_type;
            typedef Value mapped_type;
            typedef ft::pair<const key_type , mapped_type> value_type;
            typedef Node<value_type> node_type;
            typedef node_type* node_pointer;
            typedef node_type& node_reference;
            typedef Alloc allocator_type;
            

        private:
            node_pointer _root;
            node_pointer _null;
            size_type _size;
            allocator_type _alloc;

            void fixColor(node_pointer node) {
                node_pointer tmp;
                
                while (!node->parent->isBlack) {
                    
                }
            }
            
        public:
            RedBlackTree(/* args */) {
                value_type new_value(0, 0);
                _null = _alloc.allocate(1);
                _alloc.construct(_null, Node<value_type>(new_value));
                _null->isBlack = true;
                _root = _null;
                _size = 0;
            };

            void add(key_type key, mapped_type value) {
                value_type new_value(key, value);
                node_pointer new_node = _alloc.allocate(1);
                _alloc.construct(new_node, Node<value_type>(new_value));
                new_node->left = _null;
                new_node->right = _null;

                node_pointer current = _root;
                node_pointer parent = nullptr;
                
                while (current != _null) {
                    parent = current;
                    if (new_node->data < current->data) {
                        current = current->left;
                    } else {
                        current = current->right;
                    }
                }

                new_node->parent = parent;
                if (parent == nullptr) {
                    _root = new_node;
                } else if (new_node->data < parent->data) {
                    parent->left = new_node;
                } else {
                    parent->right = new_node;
                }

                if (new_node.parent == nullptr) {
                    new_node->isBlack = true;
                    _size++;
                    return ;
                }
                
                if (new_node->parent->parent == nullptr) {
                    _size++;
                    return ;
                }

                fixColor(new_node);
            }
            
            ~RedBlackTree() {};
            

            // void printTree(int count, node_pointer root = nullptr, int space = 0){
            //     if (root == _null)
            //         return ;
            //     if (_root == nullptr)
            //         return;
            //     if (root == nullptr) {
            //         if (space == 0)
            //             root = _root;
            //         else
            //             return;
            //     }
            //     space += count;
            //     printTree(count ,root->right, space);
            //     for (int i = count; i < space; i++)
            //         std::cout << "\t";
            //     std::cout << "[ " << root->data.first << " , " << root->data.second << " ]" << " (" << (root->isBlack ? "BLACK" : "RED") << ")" << "\n";
            //     printTree(count ,root->left, space);
            // }
    };
    
    
    
}

#endif // RED_BLACK_TREE_HPP_INCLUDED