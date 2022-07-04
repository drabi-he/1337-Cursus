/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 10:38:28 by hdrabi            #+#    #+#             */
/*   Updated: 2022/07/04 13:56:47 by hdrabi           ###   ########.fr       */
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
            size_type _size;
            allocator_type _alloc;

            int height () {
                if (_root == nullptr)
                    return 0;
                return height(_root) - 1;
            }

            int height (node_pointer node) {
                if (node == nullptr)
                    return 0;
                int left = height(node->left) + 1;
                int right = height(node->right) + 1;
                return (left > right ? left : right);
            }

            int blackHeight (node_pointer node) {
                if (node == nullptr)
                    return 1;
                int left = blackHeight(node->left);
                int right = blackHeight(node->right);
                if (left != right)
                    throw std::logic_error("Tree is not balanced");
                if (node->isBlack)
                    left++;
                return left;
            }
            
            void rotateLeft(node_pointer node) {
                node_pointer tmp = node->right;
                node->right = tmp->left;
                if (node->right != nullptr) {
                    node->right->parent = node;
                    node->right->isLeftChild = false;
                }
                tmp->parent = node->parent;
                if (node->parent == nullptr) {
                    _root = tmp;
                } else {
                    if (node->isLeftChild) {
                        tmp->isLeftChild = true;
                        node->parent->left = tmp;
                    } else {
                        tmp->isLeftChild = false;
                        node->parent->right = tmp;
                    }
                }
                tmp->left = node;
                node->isLeftChild = true;
                node->parent = tmp;
            }

            void rotateRight(node_pointer node) {
                node_pointer tmp = node->left;
                node->left = tmp->right;
                if (node->left != nullptr) {
                    node->left->parent = node;
                    node->left->isLeftChild = true;
                }
                tmp->parent = node->parent;
                if (node->parent == nullptr) {
                    _root = tmp;
                } else {
                    if (node->isLeftChild) {
                        tmp->isLeftChild = true;
                        node->parent->left = tmp;
                    } else {
                        tmp->isLeftChild = false;
                        node->parent->right = tmp;
                    }
                }
                tmp->right = node;
                node->isLeftChild = false;
                node->parent = tmp;
            }

            void rotateLeftRight(node_pointer node) {
                rotateLeft(node->left);
                rotateRight(node);
            }
            
            void rotateRightLeft(node_pointer node) {
                rotateRight(node->right);
                rotateLeft(node);
            }

            void rotate(node_pointer node) {
                if (node->isLeftChild) {
                    if (node->parent->isLeftChild){
                        rotateRight(node->parent->parent);
                        node->isBlack = false;
                        node->parent->isBlack = true;
                        if (node->parent->right != nullptr)
                            node->parent->right->isBlack = false;
                    }
                    else {
                        rotateRightLeft(node->parent->parent);
                        node->isBlack = true;
                        node->right->isBlack = false;
                        node->left->isBlack = false;
                    }
                } else {
                    if (!node->parent->isLeftChild){
                        rotateLeft(node->parent->parent);
                        node->isBlack = false;
                        node->parent->isBlack = true;
                        if (node->parent->left != nullptr)
                            node->parent->left->isBlack = false;
                    }
                    else {
                        rotateLeftRight(node->parent->parent);
                        node->isBlack = true;
                        node->left->isBlack = false;
                        node->right->isBlack = false;
                    }
                }
            }

            void correctTree(node_pointer node){
                if (node->parent->isLeftChild){
                    if (node->parent->parent->right == nullptr || node->parent->parent->right->isBlack)
                        rotate(node);
                    else {
                        if (node->parent->parent->right != nullptr)
                            node->parent->parent->right->isBlack = true;
                        if (node->parent->parent != _root)
                            node->parent->parent->isBlack = false;
                        node->parent->isBlack = true;
                    }
                } else {
                    if (node->parent->parent->left == nullptr || node->parent->parent->left->isBlack)
                        rotate(node);
                    else {
                        if (node->parent->parent->left != nullptr)
                            node->parent->parent->left->isBlack = true;
                        if (node->parent->parent != _root)
                            node->parent->parent->isBlack = false;
                        node->parent->isBlack = true;
                    }
                }
            }
            
            void checkColor(node_pointer node) {
                if (node == _root)
                    return ;
                if (!node->isBlack && !node->parent->isBlack)
                    correctTree(node);
                checkColor(node->parent);
            }
            
            void add (node_pointer parent, node_pointer new_node) {
                if(new_node->data >= parent->data) {
                    if(parent->right == nullptr) {
                        parent->right = new_node;
                        new_node->parent = parent;
                        new_node->isLeftChild = false;
                    }
                    else { 
                        add(parent->right, new_node);
                    }
                }
                else {
                    if(parent->left == nullptr) {
                        parent->left = new_node;
                        new_node->parent = parent; 
                        new_node->isLeftChild = true;
                    }
                    else {
                        add(parent->left, new_node);
                    }
                }
                checkColor(new_node);
            }

        public:
            RedBlackTree(/* args */) {
                _root = nullptr;
                _size = 0;
            };
            
            ~RedBlackTree() {};
            
            void add(const key_type &key, const mapped_type &value) {
                value_type new_value (key, value);
                node_pointer new_node = _alloc.allocate(1);
                _alloc.construct(new_node, Node<value_type>(new_value));

                if (_root == nullptr) {
                    _root = new_node;
                    _root->isBlack = true;
                    _size++;
                    return;
                }
                add (_root, new_node);
                _size++;
                blackHeight(_root);
            }

            void printTree(int count, node_pointer root = nullptr, int space = 0){
                if (_root == nullptr)
                    return;
                if (root == nullptr) {
                    if (space == 0)
                        root = _root;
                    else
                        return;
                }
                space += count;
                printTree(count ,root->right, space);
                for (int i = count; i < space; i++)
                    std::cout << "\t";
                std::cout << "[ " << root->data.first << " , " << root->data.second << " ]" << " (" << (root->isBlack ? "BLACK" : "RED") << ")" << "\n";
                printTree(count ,root->left, space);
            }
    };
    
    
    
}

#endif // RED_BLACK_TREE_HPP_INCLUDED