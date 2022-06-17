/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 10:38:28 by hdrabi            #+#    #+#             */
/*   Updated: 2022/06/17 15:44:59 by hdrabi           ###   ########.fr       */
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
        
        public: // TODO : change to private 
            nodePtr _root;
            nodePtr _null_node;
            size_type _size;
            allocator_type _alloc;
            
            nodePtr newNode(Key key, Value value) {
                nodePtr _new = _alloc.allocate(1);
                _new->value.first = key;
                _new->value.second = value;
                _new->isBlack = false;
                _new->parent = nullptr;
                _new->left = _null_node;
                _new->right = _null_node;
                _new->isLeftChild = false;
                return _new;
            }

            void leftRotate(nodePtr node) {
                nodePtr tmp = node->right;
                node->right = tmp->left;
                if (node->right != _null_node) {
                    node->right->parent = node;
                    node->right->isLeftChild = false;
                }
                tmp->parent = node->parent;
                if (node->parent == nullptr)
                    _root = tmp;
                else {          
                    if (node->isLeftChild) {
                        tmp->isLeftChild = true;
                        node->parent->left = tmp;
                    } else {
                        tmp->isLeftChild = false;
                        node->parent->right = tmp;
                    }
                }
                tmp->left = node;
                node->parent = tmp;
                node->isLeftChild = true; 
            }

            void rightRotate(nodePtr node) {
                nodePtr tmp = node->left;
                node->left = tmp->right;
                if (node->left != _null_node) {
                    node->left->parent = node;
                    node->left->isLeftChild = true;
                }
                tmp->parent = node->parent;
                if (node->parent == nullptr)
                    _root = tmp;
                else {
                    if (node->isLeftChild) {
                        tmp->isLeftChild = true;
                        node->parent->left = tmp;
                    } else {
                        tmp->isLeftChild = false;
                        node->parent->right = tmp;
                    }
                }
                tmp->right = node;
                node->parent = tmp;
                node->isLeftChild = false;
            }

            void leftRightRotate(nodePtr node) {
                leftRotate(node->left);
                rightRotate(node);
            }

            void rightLeftRotate(nodePtr node) {
                rightRotate(node->right);
                leftRotate(node);
            }

            void rotate(nodePtr node) {
                if (node->isLeftChild) {
                    if (node->parent->isLeftChild) {
                        rightRotate(node->parent->parent);
                        node->isBlack = false;
                        node->parent->isBlack = true;
                        if (node->parent->right != _null_node)
                            node->parent->right->isBlack = false;
                    } else {
                        rightLeftRotate(node->parent->parent);
                        node->isBlack = true;
                        node->right->isBlack = false;
                        node->left->isBlack = false;
                    }
                } else {
                    if (!node->parent->isLeftChild) {
                        leftRotate(node->parent->parent);
                        node->isBlack = false;
                        node->parent->isBlack = true;
                        if(node->parent->left != _null_node)
                            node->parent->left->isBlack = false;
                    } else {
                        leftRightRotate(node->parent->parent);
                        node->isBlack = true;
                        node->right->isBlack = false;
                        node->left->isBlack = false;
                    }
                }
            }

            void correctTree(nodePtr node) {
                if (node->parent->isLeftChild) {
                    if (node->parent->parent->right->isBlack)
                        rotate(node);
                    else {
                        if (node->parent->parent->right != _null_node)
                            node->parent->parent->right->isBlack = true;
                        if (_root != node->parent->parent)
                            node->parent->parent->isBlack = false;
                        node->parent->isBlack = true;
                    }
                } else {
                    if (node->parent->parent->left->isBlack)
                        rotate(node);
                    else {
                        if (node->parent->parent->left != _null_node)
                            node->parent->parent->left->isBlack = true;
                        if (_root != node->parent->parent)
                            node->parent->parent->isBlack = false;
                        node->parent->isBlack = true;
                    }
                }
            }

            void checkColor(nodePtr node) {
                if (node == _root)
                    return ;
                if (!node->isBlack && !node->parent->isBlack)
                    correctTree(node);
                checkColor(node->parent);
            }
            
            void add (nodePtr parent, nodePtr newNode) {
                if (newNode->value > parent->value) {
                    if (parent->right == _null_node) {
                        parent->right = newNode;
                        newNode->parent = parent;
                        newNode->isLeftChild = false;
                    } else {
                        add(parent->right, newNode);
                    }
                } else {
                    if (parent->left == _null_node) {
                        parent->left = newNode;
                        newNode->parent = parent;
                        newNode->isLeftChild = true;
                    } else {
                        add(parent->left, newNode);
                    }
                }
                checkColor(newNode);
            };

            int height(){
                if (_root == nullptr)
                    return 0;
                return (height(_root) - 1);
            }

            int height(nodePtr node){
                if (node == nullptr)
                    return 0;
                int left = height(node->left) + 1;
                int right = height(node->right) + 1;
                return (left > right ? left : right);
            }

            int blackNodes(nodePtr node){
                if (node == _null_node)
                    return 1;
                int left = blackNodes(node->left);
                int right = blackNodes(node->right);
                if (left != right)
                    std::cout << "Tree is not balanced" << std::endl;
                if (node->isBlack)
                    left++;
                return (left);
            }
            
        public:
            RedBlackTree() : _root(nullptr), _size(0) {
                _null_node = _alloc.allocate(1);
                _null_node->isBlack = true;
                _null_node->left = nullptr;
                _null_node->right = nullptr;
                _null_node->parent = nullptr;
                _null_node->isLeftChild = false;
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
                add (_root, _new);
                _size++;
                this->blackNodes(_root);
            }

            void printTree(nodePtr root, int space, int count){
                (void)root;
                if (root == _null_node)
                    return;
                space += count;
                printTree(root->right, space, count);
                for (int i = count; i < space; i++)
                    std::cout << "\t";
                std::cout << "[ " << root->value.first << " , " << root->value.second << " ]" << " (" << (root->isBlack ? "BLACK" : "RED") << ")" << "\n";
                printTree(root->left, space, count);
            }
    };
    
}