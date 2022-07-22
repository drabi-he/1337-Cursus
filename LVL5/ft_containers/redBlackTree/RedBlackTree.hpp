/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 10:38:28 by hdrabi            #+#    #+#             */
/*   Updated: 2022/07/22 19:49:46 by hdrabi           ###   ########.fr       */
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

        bool isBlack;
        T* data;
        Node *parent;
        Node *left;
        Node *right;

        explicit Node() : isBlack(false), data(nullptr), parent(nullptr), left(nullptr), right(nullptr) {}

        explicit Node(T* v) : isBlack(false), data(v), parent(nullptr), left(nullptr), right(nullptr) {}

        Node(const Node &other)
        {
            *this = other;
        }

        Node &operator=(const Node &N)
        {
            if (this != &N)
            {
                isBlack = N.isBlack;
                data = N.data;
                parent = N.parent;
                left = N.left;
                right = N.right;
            }
            return *this;
        }

        ~Node() {}
    };

    template <class T>
    class TreeIterator;

    template <class Iterator>
    class TreeReverseIterator;

    template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
    class RedBlackTree
    {
        public:
            typedef std::size_t size_type;
            typedef T value_type;
            typedef Alloc allocator_type;
            typedef Compare key_compare;
            typedef Node<value_type> node_type;
            typedef std::allocator<node_type> allocator_type_2;
            typedef node_type* node_pointer;
            typedef TreeIterator<value_type> iterator;
            typedef TreeIterator<value_type> const_iterator;
            typedef TreeReverseIterator<iterator> reverse_iterator;
            typedef TreeReverseIterator<const_iterator> const_reverse_iterator;


        private :
            node_pointer _root;
            node_pointer _null;
            size_type _size;
            allocator_type _alloc;
            allocator_type_2 _alloc_node;
            key_compare _comp;

            void rotateLeft(node_pointer node) {
                node_pointer tmp = node->right;

                node->right = tmp->left;
                if (tmp->left != _null)
                    tmp->left->parent = node;

                tmp->parent = node->parent;
                if (node->parent == nullptr)
                    _root = tmp;
                else if (node == node->parent->left)
                    node->parent->left = tmp;
                else
                    node->parent->right = tmp;

                tmp->left = node;
                node->parent = tmp;
            }

            void rotateRight(node_pointer node) {
                node_pointer tmp = node->left;

                node->left = tmp->right;           
                if (tmp->right != _null)
                    tmp->right->parent = node;

                tmp->parent = node->parent;
                if (node->parent == nullptr)
                    _root = tmp;
                else if (node == node->parent->right)
                    node->parent->right = tmp;
                else
                    node->parent->left = tmp;

                tmp->right = node;
                node->parent = tmp;
            }

            void transplant(node_pointer old, node_pointer _new) {
                if (old->parent == nullptr)
                    _root = _new;
                else if (old == old->parent->left)
                    old->parent->left = _new;
                else
                    old->parent->right = _new;

                // if (_new->parent)
                    _new->parent = old->parent;
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
            
            void colorFix(node_pointer node) {
                node_pointer tmp;

                if (node->parent == nullptr) {
                    node->isBlack = true;
                    return;
                }
                
                if (node->parent->parent == nullptr)
                    return;

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

                while (node != _root && node->isBlack)
                {
                    if (node == node->parent->left) {
                        tmp = node->parent->right;

                        if (!tmp->isBlack)
                        {
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
        
        
        public :
            explicit RedBlackTree(
                const key_compare &comp = key_compare(),
                const allocator_type &alloc = allocator_type()) : _alloc(alloc), _comp(comp) {
                    value_type *data = _alloc.allocate(1);
                    _alloc.construct(data, value_type());
                    _null = _alloc_node.allocate(1);
                    _alloc_node.construct(_null, node_type(data));
                    _null->isBlack = true;
                    _root = _null;
                    _size = 0;
                }

            RedBlackTree(const RedBlackTree &other) : _null(nullptr), _root(nullptr) {
                *this = other;
            }
            
            RedBlackTree &operator=(const RedBlackTree &rhs) {
                if (this != &rhs) {
                    _alloc = rhs._alloc;
                    _comp = rhs._comp;
                    _size = rhs._size;
                    _alloc_node = rhs._alloc_node;
                    _root = copy(rhs._root, rhs._null);
                }
                return (*this);
            }

            node_pointer copy(node_pointer node, node_pointer null) {
                if (node == null)
                    return _null;
                    
                value_type *data = _alloc.allocate(1);
                _alloc.construct(data, *node->data);
                node_pointer new_node = _alloc_node.allocate(1);
                _alloc_node.construct(new_node, node_type(data));

                new_node->isBlack = node->isBlack;
                new_node->left = copy(node->left, null);
                new_node->right = copy(node->right, null);
                new_node->parent = nullptr;
                if (new_node->left != _null)
                    new_node->left->parent = new_node;
                if (new_node->right != _null)
                    new_node->right->parent = new_node;
                return new_node;
            }

            ~RedBlackTree() {
                clear();
                _alloc_node.destroy(_null);
                _alloc_node.deallocate(_null, 1);
            }

            node_pointer getRoot() const {
                return _root;
            }

            node_pointer getNull() const {
                return _null;
            }

            static node_pointer min(node_pointer node)
            {
                if (!node || !node->left)
                    return nullptr;

                while (node->left->parent){
                    
                // std::cout << "1 - node : " << *node->data << " | left : " << *node->left->data << " | parent : " << *node->left->parent->data << std::endl;
                    node = node->left;
                // std::cout << "2 - node : " << (node ? *node->data : -1)  << " | left : " << (node->left ? *node->left->data : -1) << " | parent : " << (node->left->parent ? *node->left->parent->data : -1) << std::endl;
                }

                return node;
            }

            static node_pointer max(node_pointer node)
            {
                if (!node || !node->right)
                    return nullptr;

                while (node->right->parent)
                    node = node->right;

                return node;
            }

            static node_pointer successor(node_pointer node)
            {
                if (node->right && node->right->parent)
                    return min(node->right);

                node_pointer tmp = node->parent;
                while (tmp && node == tmp->right) {
                    node = tmp;
                    tmp = tmp->parent;
                }

                return tmp;
            }

            static node_pointer predecessor(node_pointer node)
            {
                if (node->left && node->left->parent) 
                    return max(node->left);

                node_pointer tmp = node->parent;
                while (tmp && node == tmp->left) {
                    node = tmp;
                    tmp = tmp->parent;
                }

                return tmp;
            }

            node_pointer find(const value_type &key) const
            {
                node_pointer current = _root;
                node_pointer tmp = nullptr;

                while (current != _null)
                {
                    if (!(_comp(*current->data, key) || _comp(key, *current->data)))
                        tmp = current;
                    if (_comp(*current->data, key))
                        current = current->right;
                    else
                        current = current->left;
                }
                return (tmp);
            }

            node_pointer begin() const
            {
                return min(_root);
            }

            node_pointer end() const
            {
                return max(_root);
            }

            void add(const value_type &key)
            {
                value_type *data = _alloc.allocate(1);
                _alloc.construct(data, key);
                node_pointer new_node = _alloc_node.allocate(1);
                _alloc_node.construct(new_node, node_type(data));
                new_node->parent = nullptr;
                new_node->left = _null;
                new_node->right = _null;

                node_pointer parent = nullptr;
                node_pointer current = _root;

                while (current != _null)
                {
                    parent = current;
                    if (_comp(*(new_node->data), *(current->data)))
                        current = current->left;
                    else
                        current = current->right;
                }

                new_node->parent = parent;
                if (parent == nullptr)
                    _root = new_node;
                else if (_comp(*(new_node->data), *(parent->data)))
                    parent->left = new_node;
                else
                    parent->right = new_node;
                colorFix(new_node);
                blacks(_root);
                _size++;
            }


            void erase(const value_type &key)
            {
                node_pointer node = find(key);
                node_pointer tmp1, tmp2;
                
                if (!node)
                    return ;
                tmp2 = node;
                bool isBlack = node->isBlack;

                if (node->left == _null) {
                    tmp1 = node->right;
                    transplant(node, node->right);
                } else if (node->right == _null) {
                    tmp1 = node->left;
                    transplant(node, node->left);
                } else {
                    tmp2 = min(node->right);
                    isBlack = tmp2->isBlack;
                    tmp1 = tmp2->right;
                    if (tmp2->parent == node && tmp1 != _null)
                        tmp1->parent = tmp2;
                    else
                    {
                        transplant(tmp2, tmp2->right);
                        tmp2->right = node->right;
                        if (tmp2->right != _null)
                            tmp2->right->parent = tmp2;
                    }
                    transplant(node, tmp2);
                    tmp2->left = node->left;
                    if (tmp2->left != _null)
                        tmp2->left->parent = tmp2;
                    tmp2->isBlack = node->isBlack;
                }
                freeNode(node);
                if (isBlack)
                    fixDelete(tmp1);
                blacks(_root);
                _null->parent = nullptr;
                _size--;
            }

            // ****************************** map ************************************ //
            
            size_type size() const {
                return _size;
            }

            size_type max_size() const {
                return _alloc_node.max_size();
            }

            void freeNode(node_pointer node) {
                if (node == _null)
                    return;
                _alloc.destroy(node->data);
                _alloc.deallocate(node->data, 1);
                _alloc_node.destroy(node);
                _alloc_node.deallocate(node, 1);
            }

            void freeAll(node_pointer node) {
                if (node == _null)
                    return;
                freeAll(node->left);
                freeAll(node->right);
                freeNode(node);
            }

            void clear() {
                if (_root == _null)
                    return;
                freeAll(_root);
                _root = _null;
                _size = 0;
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
                std::cout << "[ " << *root->data << "," << *root->data << " ]" << " (" << (root->isBlack ? "BLACK" : "RED") << ")" << "( " << (root->parent ? *root->parent->data : - 1) << " ) \n";
                printTree(count ,root->left, space);
            }
    };

    template <class T>
    class TreeIterator
    {
        public:
            typedef std::size_t size_type;
            typedef T value_type;
            typedef value_type& reference;
            typedef value_type* pointer;
            typedef std::ptrdiff_t difference_type;
            typedef std::bidirectional_iterator_tag iterator_category;
            typedef Node<value_type>* node_pointer;

        
        private:
            node_pointer _node;

        public:
            TreeIterator(node_pointer node = nullptr) : _node(node) {}

            TreeIterator(const TreeIterator &other) {
                *this = other;
            }

            TreeIterator &operator=(const TreeIterator &other) {
                if (this != &other)
                    _node = other._node;

                return *this;
            }

            ~TreeIterator() {}

            reference operator*() const {
                return *(_node->data);
            }

            pointer operator->() const {
                return (_node->data);
            }

            TreeIterator &operator++() {
                _node = RedBlackTree<value_type>::successor(_node);
                return (*this);
            }

            TreeIterator operator++(int) {
                TreeIterator old = *this;
                ++*this;
                return (old);
            }

            TreeIterator &operator--() {
                _node = RedBlackTree<value_type>::predecessor(_node);
                return (*this);
            }

            TreeIterator operator--(int) {
                TreeIterator old = *this;
                operator--();
                return (old);
            }

            node_pointer base() const {
                return _node;
            }

            bool operator==(const TreeIterator &rhs) const {
                return (_node == rhs._node);
            }

            bool operator!=(const TreeIterator &rhs) const {
                return _node != rhs._node;
            }
    };

    template <class Iterator>
    class TreeReverseIterator
    {

        public:
            typedef Iterator iterator_type;
            typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
            typedef typename iterator_traits<Iterator>::value_type value_type;
            typedef typename iterator_traits<Iterator>::difference_type difference_type;
            typedef typename iterator_traits<Iterator>::pointer pointer;
            typedef typename iterator_traits<Iterator>::reference reference;


        private:
            iterator_type _base;

        public:
            TreeReverseIterator() {}

            explicit TreeReverseIterator(iterator_type it) : _base(it) {}

            template <class Iter>
            TreeReverseIterator(const TreeReverseIterator<Iter> &rev_it) : _base(rev_it._base) {}

            iterator_type base() const {
                return _base;
            }

            reference operator*() const {
                return *(_base);
            }

            pointer operator->() const {
                return &(operator*());
            }

            TreeReverseIterator &operator++() {
                --_base;
                return *this;
            }

            TreeReverseIterator operator++(int) {
                TreeReverseIterator tmp(*this);
                ++*this;
                return (tmp);
            }

            TreeReverseIterator &operator--()
            {
                ++_base;
                return (*this);
            }

            TreeReverseIterator operator--(int) {
                TreeReverseIterator tmp(*this);
                --*this;
                return (tmp);
            }

            bool operator==(const TreeReverseIterator &rhs) const
            {
                return (_base == rhs._base);
            }

            bool operator!=(const TreeReverseIterator &rhs) const
            {
                return _base != rhs._base;
            }
        
    };

}

#endif // RED_BLACK_TREE_HPP_INCLUDED