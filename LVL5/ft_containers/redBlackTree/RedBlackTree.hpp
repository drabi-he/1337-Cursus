/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 10:38:28 by hdrabi            #+#    #+#             */
/*   Updated: 2022/07/13 12:58:37 by hdrabi           ###   ########.fr       */
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
            typedef TreeIterator<key_type, mapped_type> iterator;
            typedef TreeIterator<key_type, mapped_type> const_iterator;
            typedef TreeReverseIterator<iterator> reverse_iterator;
            typedef TreeReverseIterator<const_iterator> const_reverse_iterator;
            

        private:
            node_pointer _root;
            node_pointer _null;
            size_type _size;
            allocator_type _alloc;

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

            node_pointer min(node_pointer node) {
                while (node->left != _null) {
                    node = node->left;
                }
                return node;
            }

            node_pointer max(node_pointer node) {
                while (node->right != _null) {
                    node = node->right;
                }
                return node;
            }

            node_pointer successor(node_pointer node) {
                if (node->right != _null) {
                    return min(node->right);
                }
                node_pointer tmp = node->parent;
                while (tmp != _null && node == tmp->right) {
                    node = tmp;
                    tmp = tmp->parent;
                }
                return tmp;
            }

            node_pointer predecessor(node_pointer node) {
                if (node->left != _null) {
                    return max(node->left);
                }
                node_pointer tmp = node->parent;
                while (tmp != _null && node == tmp->left) {
                    node = tmp;
                    tmp = tmp->parent;
                }
                return tmp;
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
                value_type new_value(0, 0);
                _null = _alloc.allocate(1);
                _alloc.construct(_null, Node<value_type>(new_value));
                _null->isBlack = true;
                _root = _null;
                _size = 0;
            };

            ~RedBlackTree() {};

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
            
            void deleteNode(key_type key) {
                node_pointer current = _root;
                node_pointer tmp1, tmp2;
                
                while (current != _null) {
                    if (current->data.first == key) {
                        break;
                    }
                    if (key < current->data.first) {
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
                
                _alloc.destroy(current);
                _alloc.deallocate(current, 1);
                
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
                std::cout << "[ " << root->data.first << " , " << root->data.second << " ]" << " (" << (root->isBlack ? "BLACK" : "RED") << ")" << "\n";
                printTree(count ,root->left, space);
            }
    };
    

    template < class Key, class Value>
    class TreeIterator : public ft::iterator <std::bidirectional_iterator_tag, T> {
        
        public:
			typedef std::size_t size_type;
            typedef Key key_type;
            typedef Value mapped_type;
            typedef ft::pair<key_type, mapped_type> value_type;
			typedef typename ft::iterator_traits<value_type>::difference_type difference_type;
			typedef typename ft::iterator_traits<value_type>::value_type value_type;
			typedef typename ft::iterator_traits<value_type>::pointer pointer;
			typedef typename ft::iterator_traits<value_type>::reference reference;
			typedef typename ft::iterator_traits<value_type>::iterator_category iterator_category;
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
                    return (_node->data);
                }

                pointer operator->() {
                    return &(_node->data);
                }
                
                TreeIterator& operator++() {
                    _node = RedBlackTree<key_type, mapped_type>::successor(_node);
                    return *this;
                }

                TreeIterator operator++(int) {
                    TreeIterator tmp(*this);
                    ++*this;
                    return tmp;
                }

                TreeIterator& operator--() {
                    _node = RedBlackTree<key_type, mapped_type>::predecessor(_node);
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
                    return *(_it - 1);
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