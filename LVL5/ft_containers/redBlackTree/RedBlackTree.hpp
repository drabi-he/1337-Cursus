/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 10:38:28 by hdrabi            #+#    #+#             */
/*   Updated: 2022/07/16 13:12:42 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP

#include <iostream>
#include <functional>
#include "../xtra/pair.hpp"

namespace ft {
    
    template <class T>
    struct Node
    {
        T data;
        bool isBlack;
        Node<T> *left;
        Node<T> *right;
        Node<T> *parent;
        
        Node(T data) : data(data), isBlack(false),
                left(nullptr), right(nullptr), parent(nullptr) {}
        
    };

    template <class T>
    class TreeIterator;

    template <class Iterator>
    class TreeReverseIterator;

    template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
    class RedBlackTree
    {
        public:
            typedef std::size_t size_type;
            typedef T value_type;
            typedef Node<value_type> node_type;
            typedef node_type* node_pointer;
            typedef node_type& node_reference;
            typedef Alloc allocator_type;
            typedef std::allocator<node_type> node_allocator_type;
            typedef TreeIterator<value_type> iterator;
            typedef TreeIterator<value_type> const_iterator;
            typedef TreeReverseIterator<iterator> reverse_iterator;
            typedef TreeReverseIterator<const_iterator> const_reverse_iterator;
            

        private:
            node_pointer _root;
            node_pointer _null;
            size_type _size;
            allocator_type _alloc;
            node_allocator_type _node_alloc;
            Compare _comp;

            void rotateLeft(node_pointer node) {
                node_pointer tmp = node->right;
                
                node->right = tmp->left;
                if (tmp->left != _null) {
                    tmp->left->parent = node;
                }
                tmp->parent = node->parent;
                if (node->parent == nullptr) {
                    _root = tmp;
                } else if (node == node->parent->left) {
                    node->parent->left = tmp;
                } else {
                    node->parent->right = tmp;
                }
                tmp->left = node;
                node->parent = tmp;
            }

            void rotateRight(node_pointer node) {
                node_pointer tmp = node->left;
                
                node->left = tmp->right;
                if (tmp->right != _null) {
                    tmp->right->parent = node;
                }
                tmp->parent = node->parent;
                if (node->parent == nullptr) {
                    _root = tmp;
                } else if (node == node->parent->right) {
                    node->parent->right = tmp;
                } else {
                    node->parent->left = tmp;
                }
                tmp->right = node;
                node->parent = tmp;
            }

            void transplant(node_pointer old, node_pointer newNode) {
                if (old->parent == nullptr) {
                    _root = newNode;
                } else if (old == old->parent->left) {
                    old->parent->left = newNode;
                } else {
                    old->parent->right = newNode;
                }
                newNode->parent = old->parent;
            }

            int blacks(node_pointer node) {
                if (node == _null)
                    return 1 ;

                int right = blacks(node->right);
                int left = blacks(node->left);

                if (right != left)
                    throw std::logic_error("Tree Is Not Balanced");
                if (node->isBlack)
                    left++;
                return left;
            }

            void fixColor(node_pointer node) {
                node_pointer tmp;
                
                while (!node->parent->isBlack) {
                    if (node->parent == node->parent->parent->right) {
                        tmp = node->parent->parent->left;
                        if (!tmp->isBlack) {
                            tmp->isBlack = true;
                            node->parent->isBlack = true;
                            node->parent->parent->isBlack = false;
                            node = node->parent->parent;
                        } else {
                            if (node == node->parent->left) {
                                node = node->parent;
                                rotateRight(node);
                            }
                            node->parent->isBlack = true;
                            node->parent->parent->isBlack = false;
                            rotateLeft(node->parent->parent);
                        }
                    } else {
                        tmp = node->parent->parent->right;
                        if (!tmp->isBlack) {
                            tmp->isBlack = true;
                            node->parent->isBlack = true;
                            node->parent->parent->isBlack = false;
                            node = node->parent->parent;
                        } else {
                            if (node == node->parent->right) {
                                node = node->parent;
                                rotateLeft(node);
                            }
                            node->parent->isBlack = true;
                            node->parent->parent->isBlack = false;
                            rotateRight(node->parent->parent);
                        }
                    }
                    if (node == _root)
                        break;
                }
                _root->isBlack = true;
            }
            
            void fixDelete(node_pointer node) {
                node_pointer tmp;

                while (node != _root && node->isBlack) {
                    if (node == node->parent->left) {
                        tmp = node->parent->right;
                        if (!tmp->isBlack) {
                            tmp->isBlack = true;
                            node->parent->isBlack = false;
                            rotateLeft(node->parent);
                            tmp = node->parent->right;
                        }
                        
                        if (tmp->left->isBlack && tmp->right->isBlack) {
                            tmp->isBlack = false;
                            node = node->parent;
                        } else {
                            if (tmp->right->isBlack) {
                                tmp->left->isBlack = true;
                                tmp->isBlack = false;
                                rotateRight(tmp);
                                tmp = node->parent->right;
                            }
                            
                            tmp->isBlack = node->parent->isBlack;
                            node->parent->isBlack = true;
                            tmp->right->isBlack = true;
                            rotateLeft(node->parent);
                            node = _root;
                        }
                    } else {
                        tmp = node->parent->left;
                        if (!tmp->isBlack) {
                            tmp->isBlack = true;
                            node->parent->isBlack = false;
                            rotateRight(node->parent);
                            tmp = node->parent->left;
                        }
                        if (tmp->left->isBlack && tmp->right->isBlack) {
                            tmp->isBlack = false;
                            node = node->parent;
                        } else {
                            if (tmp->left->isBlack) {
                                tmp->right->isBlack = true;
                                tmp->isBlack = false;
                                rotateLeft(tmp);
                                tmp = node->parent->left;
                            }
                            tmp->isBlack = node->parent->isBlack;
                            node->parent->isBlack = true;
                            tmp->left->isBlack = true;
                            rotateRight(node->parent);
                            node = _root;
                        }
                    }
                }
                node->isBlack = true;
            }
            
        public:
            RedBlackTree(/* args */) {
                _null = _node_alloc.allocate(1);
                _node_alloc.construct(_null, Node<value_type>(value_type()));
                _null->isBlack = true;
                _root = _null;
                _size = 0;
            };

            RedBlackTree &operator=(const RedBlackTree &other) {
                if (this != &other) {
                    _size = other._size;
                    _root = copy(other._root, other._null);
                }
                return *this;
            }

            node_pointer copy(node_pointer node, node_pointer null) {
                if (node == null)
                    return _null;
                node_pointer newNode = _node_alloc.allocate(1);
                _node_alloc.construct(newNode, Node<value_type>(node->data));
                newNode->isBlack = node->isBlack;
                newNode->left = copy(node->left, null);
                newNode->right = copy(node->right, null);
                newNode->parent = _null;
                if (newNode->left != _null)
                    newNode->left->parent = newNode;
                if (newNode->right != _null)
                    newNode->right->parent = newNode;
                return newNode;
            }

            ~RedBlackTree() {};

            static node_pointer min(node_pointer node) {
                if (!node || !node->left)
                    return nullptr;
                while (node->left->parent) {
                    node = node->left;
                }
                return node;
            }

            static node_pointer max(node_pointer node) {
                if (!node || !node->right)
                    return nullptr;
                while (node->right->parent) {
                    node = node->right;
                }
                return node;
            }

            static node_pointer successor(node_pointer node) {
                if (node->right && node->right->parent) {
                    return min(node->right);
                }
                node_pointer tmp = node->parent;
                while (tmp && node == tmp->right) {
                    node = tmp;
                    tmp = tmp->parent;
                }
                return tmp;
            }

            static node_pointer predecessor(node_pointer node) {
                if (node->left && node->left->parent) {
                    return max(node->left);
                }
                node_pointer tmp = node->parent;
                while (tmp && node == tmp->left) {
                    node = tmp;
                    tmp = tmp->parent;
                }
                return tmp;
            }

            node_pointer find(const value_type &value) {
                node_pointer node = _root;
                std::cout << "find: " << node->data.first << " | " <<  node->data.second << std::endl;
                while (node != _null) {
                    if (!(_comp(node->data, value) || _comp(value, node->data))){
                        return node;
                    }
                    if (_comp(value, node->data))
                        node = node->left;
                    else
                        node = node->right;
                }
                // std::cout << "not found"<< std::endl;
                return nullptr;
            }

            node_pointer begin() {
                return min(_root);
            }

            node_pointer end() {
                return max(_root);
            }

            size_type size() const{
                return _size;
            }

            size_type max_size() const {
                return _node_alloc.max_size();
            }

            void add(value_type value) {
                node_pointer new_node = _node_alloc.allocate(1);
                _node_alloc.construct(new_node, Node<value_type>(value));
                new_node->left = _null;
                new_node->right = _null;

                node_pointer current = _root;
                node_pointer parent = nullptr;
                
                while (current != _null) {
                    parent = current;
                    if (_comp(new_node->data, current->data)) {
                        current = current->left;
                    } else {
                        current = current->right;
                    }
                }

                new_node->parent = parent;
                if (parent == nullptr) {
                    _root = new_node;
                } else if (_comp(new_node->data, parent->data)) {
                    parent->left = new_node;
                } else {
                    parent->right = new_node;
                }

                if (new_node->parent == nullptr) {
                    new_node->isBlack = true;
                    _size++;
                    return ;
                }
                
                if (new_node->parent->parent == nullptr) {
                    _size++;
                    return ;
                }

                fixColor(new_node);
                blacks(_root);
            }
            
            void deleteNode(value_type key) {
                node_pointer current = _root;
                node_pointer tmp1, tmp2;
                
                while (current != _null) {
                    if (!(_comp(current->data, key) || _comp(key, current->data))) {
                        break;
                    }
                    if (_comp(key, current->data)) {
                        current = current->left;
                    } else {
                        current = current->right;
                    }
                }
                
                if (current == _null) {
                    std::cout << "Key not found" << std::endl;
                    return ;
                }
                
                tmp2 = current;
                bool isBlack = current->isBlack;
                if (current->left == _null) {
                    tmp1 = current->right;
                    transplant(current, current->right);
                } else if (current->right == _null) {
                    tmp1 = current->left;
                    transplant(current, current->left);
                } else {
                    tmp2 = min(current->right);
                    isBlack = tmp2->isBlack;
                    tmp1 = tmp2->right;
                    if (tmp2->parent == current) {
                        tmp1->parent = tmp2;
                    } else {
                        transplant(tmp2, tmp2->right);
                        tmp2->right = current->right;
                        tmp2->right->parent = tmp2;
                    }
                    
                    transplant(current, tmp2);
                    tmp2->left = current->left;
                    tmp2->left->parent = tmp2;
                    tmp2->isBlack = current->isBlack;
                }
                
                _node_alloc.destroy(current);
                _node_alloc.deallocate(current, 1);
                
                if (isBlack) {
                    fixDelete(tmp1);
                }
                _size--;
                blacks(_root);
            }

            void printTree(int count, node_pointer root = nullptr, int space = 0){
                if (root == _null)
                    return ;
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
                std::cout << "[ " << root->data.first << "," << root->data.second << " ]" << " (" << (root->isBlack ? "BLACK" : "RED") << ")" << "\n";
                printTree(count ,root->left, space);
            }
    };
    

    template < class T>
    class TreeIterator {
        
        public:
			typedef std::size_t size_type;
            typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef value_type* pointer;
			typedef value_type& reference;
			typedef std::bidirectional_iterator_tag iterator_category;
            typedef Node<value_type>* node_pointer;

            private :
                node_pointer _node;

            public :
                TreeIterator(node_pointer node = nullptr) : _node(node) {}

                TreeIterator(const TreeIterator& other) {
                    *this = other;
                }

                TreeIterator& operator=(const TreeIterator& other) {
                    if (this != &other)
                        this->_node = other._node;
                    return *this;
                }

                ~TreeIterator() {}

                reference operator*() {
                    std::cout << "operator*" << std::endl;
                    return (_node->data);
                }

                pointer operator->() {
                    return &(_node->data);
                }
                
                TreeIterator& operator++() {
                    _node = RedBlackTree<value_type>::successor(_node);
                    return *this;
                }

                TreeIterator operator++(int) {
                    TreeIterator tmp(*this);
                    ++*this;
                    return tmp;
                }

                TreeIterator& operator--() {
                    _node = RedBlackTree<value_type>::predecessor(_node);
                    return *this;
                }

                TreeIterator operator--(int) {
                    TreeIterator tmp(*this);
                    --*this;
                    return tmp;
                }

                node_pointer base() const {
                    return _node;
                }
                
                bool operator==(const TreeIterator& other) {
                    return (_node == other._node);
                }

                bool operator!=(const TreeIterator& other) {
                    return (_node != other._node);
                }
    };

    template <class Iterator>
    class TreeReverseIterator {
        
        public :
            typedef Iterator iterator_type;
            typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
            typedef typename iterator_traits<iterator_type>::value_type value_type;
            typedef typename iterator_traits<iterator_type>::difference_type difference_type;
            typedef typename iterator_traits<iterator_type>::pointer pointer;
            typedef typename iterator_traits<iterator_type>::reference reference;

            private :
                iterator_type _it;
                
            public :
            
                TreeReverseIterator() {}

                TreeReverseIterator(iterator_type it) : _it(it) {}

                TreeReverseIterator(const TreeReverseIterator& other) {
                    *this = other;
                }

                TreeReverseIterator& operator=(const TreeReverseIterator& other) {
                    if (this != &other)
                        this->_it = other._it;
                    return *this;
                }

                ~TreeReverseIterator() {}

                iterator_type base() const {
                    return _it;
                }

                reference operator*() {
                    return *(_it);
                }

                pointer operator->() {
                    return &(operator*());
                }

                TreeReverseIterator& operator++() {
                    --_it;
                    return *this;
                }

                TreeReverseIterator operator++(int) {
                    TreeReverseIterator tmp(*this);
                    ++*this;
                    return tmp;
                }

                TreeReverseIterator& operator--() {
                    ++_it;
                    return *this;
                }

                TreeReverseIterator operator--(int) {
                    TreeReverseIterator tmp(*this);
                    --*this;
                    return tmp;
                }

                bool operator==(const TreeReverseIterator& other) {
                    return (_it == other._it);
                }

                bool operator!=(const TreeReverseIterator& other) {
                    return (_it != other._it);
                }
    };
}

#endif // RED_BLACK_TREE_HPP_INCLUDED