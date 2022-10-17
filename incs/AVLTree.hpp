#ifndef AVLTREE2_HPP
# define AVLTREE2_HPP

# include <stdexcept>
# include <iostream>
# include <bits/stdc++.h>
# include <iterator>
# include "Colors.hpp"
# include "Iterators.hpp"
# include "pair.hpp"
# include "lexicographical_compare.hpp"

# define COUNT 10

template < typename T, typename Compare, typename Allocator >
class AVLTree {

    typedef T           value_type;
    typedef T&          reference;
    typedef T*          pointer;
    typedef const T&    const_reference;
    typedef size_t      size_type;

    private:
        struct TreeNode
        {
            public:
                T               value;
                TreeNode        *parent;
                TreeNode        *left;
                TreeNode        *right;
                unsigned        height;

                TreeNode( const T& v, TreeNode* parent, TreeNode* left = NULL, TreeNode* right = NULL, unsigned height = 1 ) 
                    : value(v), parent(parent), left(left), right(right), height(height) {}
                TreeNode( const TreeNode& other) :  value(other.value), 
                                                    parent(other.parent), 
                                                    left(other.left), 
                                                    right(other.right),  
                                                    height(other.height) {}
                ~TreeNode( void ) {}

                TreeNode& operator=( const TreeNode& rhs)
                {
                    if (this != &rhs)
                    {
                        value = rhs.value;
                        parent = rhs.parent;
                        left = rhs.left;
                        right = rhs.right;
                        height = rhs.height;
                    }

                    return (*this);
                }

                bool    isLeaf( void ) const { return ( !right && !left ); }

                void    swap(TreeNode& rhs)
                {
                    TreeNode    *leftTmp = left;
                    TreeNode    *rightTmp = right;

                    left = rhs.left == this ? &rhs : rhs.left;
                    right = rhs.right == this ? &rhs : rhs.right;

                    if (left)
                        left->parent = this;
                    if (right)
                        right->parent = this;

                    rhs.left = leftTmp == &rhs ? this : leftTmp;
                    rhs.right = rightTmp == &rhs ? this : rightTmp;
                    
                    if (leftTmp)
                        leftTmp->parent = &rhs;

                    if (rightTmp)
                        rightTmp->parent = &rhs;

                    TreeNode    *parentTmp = parent;

                    parent = rhs.parent == this ? &rhs : rhs.parent;
                    
                    if (parent)
                    {
                        if (parent->left == &rhs)
                            parent->left = this;
                        else if (parent->right == &rhs)
                            parent->right = this;
                    }

                    rhs.parent = parentTmp;

                    if (rhs.parent)
                    {
                        if (rhs.parent->left == this)
                            rhs.parent->left = &rhs;
                        else if (parent->right == this)
                            rhs.parent->right = &rhs;
                    }

                    std::swap(height, rhs.height);
                    std::swap(value, rhs.value);
                }
        };
    
        typedef typename Allocator::template rebind<TreeNode>::other    NodeAlloc;

        TreeNode*   _allocateNode(   NodeAlloc& alloc, 
                                    const_reference value, 
                                    TreeNode* parent, 
                                    TreeNode* left = NULL, 
                                    TreeNode* right = NULL,
                                    unsigned height = 1) const
        {
            TreeNode*   Node = alloc.allocate(1);
            alloc.construct( Node, TreeNode(value, parent, left, right, height) );

            return (Node);
        }

        void        _deallocateNode(TreeNode *p)
        {
            _allocate.destroy(p);
            _allocate.deallocate(p, 1);
        }

    private:
        NodeAlloc   _allocate;
        TreeNode*   _root;
        TreeNode*   _begin;
        TreeNode*   _end;
        size_t      _size;
        Compare     _compare;

    public:
        AVLTree(void) : _allocate(), _size(0)
        {
            _begin = _allocateNode(_allocate, T(), 0);
            _end = _allocateNode(_allocate, T(), _begin);
            _begin->height = 0;
            _end->height = 0;
            _begin->right = _end;
            _root = _begin;
        }

        ~AVLTree(void)
        {
            _destroy(_root);
            _deallocateNode(_begin);
            _deallocateNode(_end);
        }
        
        template < typename It, bool isConst = false >
        class TreeIt
        {
            public:
                TreeNode*   current;

            public:
                typedef std::bidirectional_iterator_tag iterator_category;
                typedef It                              value_type;
                typedef It*                             pointer;
                typedef It&                             reference;
                typedef std::ptrdiff_t                  difference_type;
        
                TreeIt(void) : current(NULL) {}
                TreeIt(TreeNode *n) : current(n) {}
                TreeIt(const TreeIt<value_type>& other) { *this = other; }
                ~TreeIt(void) {}

                void*    getCurrentNode(void) const { return ( current ); }

                operator    TreeIt<const It, true>() const
                {
                    return ( TreeIt<const It, true>(current) );
                }

                TreeIt&     operator=(const TreeIt& rhs)
                {
                    if (this != &rhs)
                        current = rhs.current;
                    return ( *this );
                }

                reference       operator*(void) { return ( current->value ); }
                const_reference operator*(void) const { return ( current->value ); }

                pointer         operator->(void) { return ( &current->value ); }
                const T*        operator->(void) const { return ( &current->value ); }

                TreeIt&         operator++(void)
                {
                    if (!current->right)
                    {
                        TreeNode* prev = 0;
                        do {
                            prev = current;
                            current = current->parent;
                        } while (current && current->right && current->right == prev);
                    }
                    else
                        current = _findInOrderSuccessor(current->right);
                    
                    return ( *this );
                }

                TreeIt         operator++(int)
                {
                    TreeIt      tmp(*this);

                    operator++();
                    return ( tmp );
                }

                TreeIt&         operator--()
                {
                    if (current->left)
                        current = _findInOrderPredecessor(current->left);
                    else
                    {
                        TreeNode* prev = NULL;
                        do {
                            prev = current;
                            current = current->parent;
                        } while (current && current->left && current->left == prev);
                    }

                    return ( *this );
                }

                TreeIt     operator--(int)
                {
                    TreeIt  tmp(*this);

                    operator--();
                    return ( tmp );
                }

                bool    operator==(TreeIt<It, false> rhs) const { return getCurrentNode() == rhs.getCurrentNode(); }
                bool    operator!=(TreeIt<It, false> rhs) const { return getCurrentNode() != rhs.getCurrentNode(); }
                bool    operator==(TreeIt<const It, true> rhs) const { return getCurrentNode() == rhs.getCurrentNode(); }
                bool    operator!=(TreeIt<const It, true> rhs) const { return getCurrentNode() != rhs.getCurrentNode(); }
        };
        
        typedef TreeIt<T, false>                        iterator;
        typedef TreeIt<const T, true>                   const_iterator;
        typedef ft::reverse_iterator<iterator>          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

    private:

        static TreeNode*    _findInOrderSuccessor(TreeNode *p)
        {
            while (p && p->left)
                p = p->left;
            
            return (p);
        }

        static TreeNode*    _findInOrderPredecessor(TreeNode *p)
        {
            while (p && p->right)
                p = p->right;
            
            return (p);
        }

        bool                _hasLeft(TreeNode* p) const { return ( p->left && p != _begin ); }

        bool                _hasRight(TreeNode* p) const { return ( p->right && p != _end ); }

        unsigned            _updateHeight(TreeNode *r) const
        {
            unsigned    lheight;
            unsigned    rheight;

            lheight = r->left ? r->left->height : 0;
            rheight = r->right ? r->right->height : 0;

            if ( lheight >= rheight )
                return ( lheight + 1 );
            else
                return ( rheight + 1 );
        }

        int         _getBalanceFactor(TreeNode *n)
        {            
            unsigned lheight;
            unsigned rheight;

            lheight = n->left ? n->left->height : 0;
            rheight = n->right ? n->right->height : 0;

            return ( lheight - rheight );
        }

        TreeNode*   _insertNode(TreeNode* r, const_reference value, TreeNode*& ret, TreeNode* parent = 0)
        {
            //spot is "available" ie no interaction with _begin or _end, allocate right there
            if (!r)
            {
                _size++;
                return ( ret = _allocateNode(_allocate, value, parent) );
            }

            //value is highest so far in the tree so it interacts with _end, need to update
            //accordingly
            if ( r == _end )
            {
                r = ret = _allocateNode(_allocate, value, parent, 0, r, 1);
                _end->parent = r;
                _size++;
                return (r);
            }

            //value is lowest so far in the tree so it interacts with _begin, need to update
            //accordingly
            if ( r == _begin )
            {
                TreeNode* p;

                p = ret = _allocateNode(_allocate, value, parent, _begin, _begin->right);
                _begin->parent = p;

                //First element inserted so _begin->right == _end, need to update _end
                if ( _begin->right == _end )
                {
                    _end->parent = p;
                    _begin->right = 0;
                }
                _size++;
                return (p);
            }

            if ( _compare( value, r->value) )
                r->left = _insertNode(r->left, value, ret, r);
            else if ( _compare(r->value, value) )
                r->right = _insertNode(r->right, value, ret, r);
            else
            {
                ret = r;
                throw std::runtime_error("No duplicates allowed");
            }

            r->height = _updateHeight(r);

            int bf = _getBalanceFactor(r);
            int bf2 = 0;

            //bf == 2 : LST imbalance | bf == -2 : RST imbalance
            if (bf == 2)
            {
                bf2 = _getBalanceFactor(r->left);
                if (bf2 == 1) {
                    return ( _LL_Rotate(r) );
                }
                else if (bf2 == -1) {
                    return ( _LR_Rotate(r) );
                }
            }
            else if (bf == -2)
            {
                bf2 = _getBalanceFactor(r->right);
                if (bf2 == 1) {
                    return ( _RL_Rotate(r) );
                }
                if (bf2 == -1) {
                    return ( _RR_Rotate(r) );
                }
            }

            return (r);
        }

        TreeNode*   _deleteNode(TreeNode *r, const_reference value)
        {
            if (!r)
                return (0);
            
            //Found node with value we want to delete
            if ( _equal(value, r->value) )
            {
                if ( r == _end || r == _begin )
                    return (r);
                
                //Last element in tree is deleted, need to wire _begin and _end like they were at the start
                if ( r->left == _begin && r->right == _end )
                {
                    _deallocateNode(r);
                    _begin->right = _end;
                    _end->parent = _begin;
                    _begin->parent = 0;
                    _size--;

                    return ( _begin );
                }

                //Case: leaf node => a "leaf node" can either be a node with no right && left ; a node with no right
                //and _begin in left (lowest key in tree); a node with no left and _end in right (highest key in tree)
                if ( r->isLeaf() || (!r->left && r->right == _end ) || (!r->right && r->left == _begin) )
                {
                    //Lowest key in tree: we update _begin's wiring before deleting
                    if ( r->left == _begin )
                    {
                        _begin->parent = r->parent;
                        r->parent->left = _begin;
                    }

                    //Highest key in tree: we update _end's wiring before deleting
                    else if ( r->right == _end )
                    {
                        _end->parent = r->parent;
                        r->parent->right = _end;
                    }

                    //Leaf node that is not the lowest or the highest, we update parent's wiring to cut off leaf
                    //before deleting
                    else
                    {
                        if ( r->parent )
                        {
                            if ( r->parent->left == r )
                                r->parent->left = 0;
                            else
                                r->parent->right = 0;
                        }
                    }

                    TreeNode*   ret;

                    //Middle leaf node: we return 0 to prior recursive call
                    if ( r->isLeaf() )
                        ret = 0;
                    else
                    {
                        //Lowest leaf: we return _begin to prior recursive call
                        if ( r->left )
                            ret = _begin;
                        //Highest leaf: we return _end to prior recursive call
                        else
                            ret = _end;
                    }

                    _deallocateNode(r);
                    _size--;

                    return (ret);
                }

                //Case: Not a leaf node, basically
                bool    leftSide;

                //We check if the tree has a left subtree or not, in case it has both we will work with the tallest subtree
                if ( _hasLeft(r) && _hasRight(r) )
                    leftSide = r->left->height >= r->right->height;
                else
                    leftSide = _hasLeft(r);

                TreeNode    *tmp;

                //It it has a left side: tmp is the in-order predecessor, if it doesn't it is the in-order successor
                if ( leftSide )
                    tmp = _findInOrderPredecessor( r->left );
                else
                    tmp = _findInOrderSuccessor( r->right );
                
                //We use our node's swap function so everything points to the right parents and left/right trees
                r->swap(*tmp);
                
                //We use std::swap to swap pointers, and then we switch the value back to what we want to keep
                std::swap(r, tmp);
                r->value = tmp->value;

                //We recurse until value goes down to a leaf node, so we can delete it
                if ( leftSide )
                    r->left = _deleteNode(r->left, tmp->value);
                else
                    r->right = _deleteNode(r->right, tmp->value);
            }

            //Value of current node is different of the value we want, we continue searching via recursion
            else
            {
                if ( _compare(value, r->value) )
                    r->left = _deleteNode(r->left, value);
                else
                    r->right = _deleteNode(r->right, value);
            }

            //Rebalancing operations
            r->height = _updateHeight(r);
            int bf = _getBalanceFactor(r);
            int bf2 = 0;

            if (bf == 2)
            {
                bf2 = _getBalanceFactor(r->left);

                if (bf2 == 1)
                    return ( _LL_Rotate(r) );
                else if (bf2 == -1)
                    return ( _LR_Rotate(r) );
                else if (bf2 == 0)
                    return ( _LL_Rotate(r) );
            }

            else if (bf == -2)
            {
                bf2 = _getBalanceFactor(r->right);

                if (bf2 == 1)
                    return ( _RL_Rotate(r) );
                else if (bf2 == -1)
                    return ( _RR_Rotate(r) );
                else if (bf2 == 0)
                    return ( _RR_Rotate(r) );
            }

            return (r);
        }

        //ROTATIONS
        TreeNode*   _RR_Rotate(TreeNode* y)
        {
            TreeNode *x = y->right;
            TreeNode *T2 = x->left;

            x->left = y;
            y->right = T2;
            if (T2)
                T2->parent = y;

            x->parent = y->parent;
            y->parent = x;
            y->height = _updateHeight(y);
            x->height = _updateHeight(x);

            if (_root == y)
                _root = x;

            return (x);
        }

        TreeNode*   _LL_Rotate(TreeNode* x)
        {
            TreeNode *y = x->left;
            TreeNode *T2 = y->right;

            y->right = x;
            x->left = T2;
            if (T2)
                T2->parent = x;
            
            y->parent = x->parent;
            x->parent = y;
            x->height = _updateHeight(x);
            y->height = _updateHeight(y);

            if (_root == x)
                _root = y;

            return (y);
        }

        TreeNode*   _LR_Rotate(TreeNode* x)
        {
            TreeNode*   y = x->left;
            TreeNode*   T2 = y->right;
            
            y->right = T2->left;
            if (T2->left)
                T2->left->parent = y;

            x->left = T2->right;
            if (T2->right)
                T2->right->parent = x;

            T2->right = x;
            T2->parent = x->parent;
            x->parent = T2;
            T2->left = y;
            y->parent = T2;

            y->height = _updateHeight(y);
            x->height = _updateHeight(x);
            T2->height = _updateHeight(T2);

            if (_root == x)
                _root = T2;
            
            return (T2);
        }

        TreeNode*   _RL_Rotate(TreeNode* y)
        {
            TreeNode*   x = y->right;
            TreeNode*   T2 = x->left;

            x->left = T2->right;
            if (T2->right)
                T2->right->parent = x;

            y->right = T2->left;
            if (T2->left)
                T2->left->parent = y;

            T2->left = y;
            T2->parent = y->parent;
            y->parent = T2;
            T2->right = x;
            x->parent = T2;

            x->height = _updateHeight(x);
            y->height = _updateHeight(y);
            T2->height = _updateHeight(T2);

            if (_root == y)
                _root = T2;
            
            return (T2);
        }
        
        //FIND
        TreeNode*   _findNode(TreeNode* r, const T& value) const
        {
            if (!r || r == _begin || r == _end)
                return (0);
            
            if ( _compare(value, r->value) )
                return ( _findNode(r->left, value) );
            else if ( _compare(r->value, value) )
                return ( _findNode(r->right, value) );
            else
                return (r);
        }

        TreeNode*   _findLowerBound(TreeNode* r, const T& value, TreeNode* ret = 0) const
        {
            if (!r || r == _begin || r == _end)
                return (ret);
            
            if ( _compare(r->value, value) )
                return ( _findLowerBound(r->right, value, ret) );
            else
                return ( _findLowerBound(r->left, value, r) );
        }

        TreeNode*   _findUpperBound(TreeNode* r, const T& value, TreeNode* ret = 0) const
        {
            if (!r || r == _begin || r == _end)
                return (ret);
            
            if ( _compare(r->value, value) || _equal(r->value, value) )
                return ( _findUpperBound(r->right, value, ret) );
            else
                return ( _findUpperBound(r->left, value, r) );
        }

        //DESTROY
        void    _destroy(TreeNode* r)
        {
            if (r->left)
                _destroy(r->left);
            if (r->right)
                _destroy(r->right);
            if ( r != _begin && r != _end )
                _deallocateNode(r);
        }

        //HELPERS
        bool    _equal(const T& lhs, const T& rhs) const
        {
            return ( !_compare(lhs, rhs) && !_compare(rhs, lhs) );
        }

    public:
        
        size_type   size(void) const { return ( _size ); };

        size_type   max_size(void) const { return ( _allocate.max_size() ); }

        //INSERT
        ft::pair<iterator, bool>    insert(const T& value)
        {
            TreeNode*   ret = 0;

            try {
                _root = _insertNode(_root, value, ret);
            }   catch (std::runtime_error& e) {
                    return ( ft::make_pair(iterator(ret), false) );
            }
            
            return ( ft::make_pair(iterator(ret), true) );
        }

        iterator                    insert(iterator hint, const T& value)
        {
            (void)hint;
            return ( insert(value).first );
        }

        template  < class InputIt >
        void                        insert(InputIt first, InputIt last)
        {
            while (first != last)
            {
                insert(*first);
                *first++;
            }
        }

        //ERASE
        size_type                   erase(const T& value)
        {
            size_type   og = size();

            _root = _deleteNode(_root, value);

            return ( size() != og ? 1 : 0 );
        }

        void        erase(iterator pos) { erase(*pos); }

        void        erase(iterator first, iterator last)
        {
            while (first != last)
                erase(*first++);
        }

        //ITERATORS
        iterator            begin(void)
        {
            if (!_begin->parent)
                return ( end() );
            
            return ( iterator(_begin->parent) );
        }
        
        const_iterator      begin(void) const
        {           
            if (!_begin->parent)
                return ( end() );
            
            return ( const_iterator(_begin->parent) );
        }

        iterator            end(void)
        {
            return ( iterator(_end) );
        }

        const_iterator      end(void) const
        {
            return ( const_iterator(_end) );
        }

        reverse_iterator    rbegin(void)
        {
            return ( reverse_iterator( end() ) );
        }

        const_reverse_iterator  rbegin(void) const
        {
            return ( const_reverse_iterator( end() ) );
        }

        reverse_iterator        rend(void)
        {
            return ( reverse_iterator( begin() ) );
        }

        const_reverse_iterator  rend(void) const
        {
            return ( const_reverse_iterator( begin() ) );
        }

        //LOOKUP
        iterator    find(const T& value)
        {
            TreeNode* n;

            n = _findNode(_root, value);
            if (n)
                return ( iterator(n) );
            return ( end() );
        }

        const_iterator    find(const T& value) const
        {
            TreeNode* n;

            n = _findNode(_root, value);
            if (n)
                return ( const_iterator(n) );
            return ( end() );
        }

        iterator            lower_bound(const T& value)
        {
            TreeNode* n;

            n = _findLowerBound(_root, value);
            if (n)
                return ( iterator(n) );
            return ( end() );
        }

        const_iterator            lower_bound(const T& value) const
        {
            TreeNode* n;

            n = _findLowerBound(_root, value);
            if (n)
                return ( const_iterator(n) );
            return ( end() );
        }

        iterator            upper_bound(const T& value)
        {
            TreeNode* n;

            n = _findUpperBound(_root, value);
            if (n)
                return ( iterator(n) );
            return ( end() );
        }

        const_iterator            upper_bound(const T& value) const
        {
            TreeNode* n;

            n = _findUpperBound(_root, value);
            if (n)
                return ( const_iterator(n) );
            return ( end() );
        }

        ft::pair<iterator, iterator>    equal_range(const T& value)
        {
            return ( ft::make_pair(lower_bound(value), upper_bound(value)) );
        }

        ft::pair<const_iterator, const_iterator>    equal_range(const T& value) const
        {
            return ( ft::make_pair(lower_bound(value), upper_bound(value)) );
        }

        void    swap(AVLTree& rhs)
        {
            if ( this != &rhs )
            {
                std::swap(_root, rhs._root);
                std::swap(_size, rhs._size);
                std::swap(_allocate, rhs._allocate);
                std::swap(_begin, rhs._begin);
                std::swap(_end, rhs._end);
            }
        }

        void    clear(void)
        {
            _destroy(_root);
            _root = _begin;
            _begin->parent = 0;
            _begin->right = _end;
            _end->parent = _begin;
            _size = 0;
        }

        void    print2DUtil(TreeNode *r, int space)
        {
            if (r == NULL)
                return ;
            
            space += COUNT;
            print2DUtil(r->right, space);
            std::cout << std::endl;
            for (int i = COUNT; i < space; i++)
                std::cout << " ";
            std::cout << r->value.first << std::endl;
            print2DUtil(r->left, space);
        }

        void    print2D(void)
        {
            print2DUtil(_root, 0);
        }


};

template< typename T, typename Compare, typename Alloc >
bool    operator==( const AVLTree<T, Compare, Alloc>& lhs, 
                    const AVLTree<T, Compare, Alloc>& rhs )
{
    if ( lhs.size() != rhs.size() )
        return (false);
    
    return ( ft::equal(lhs.begin(), lhs.end(), rhs.begin()) );
}

template< typename T, typename Compare, typename Alloc >
bool    operator!=( const AVLTree<T, Compare, Alloc>& lhs, 
                    const AVLTree<T, Compare, Alloc>& rhs )
{
    return ( !(lhs == rhs) );
}

template< typename T, typename Compare, typename Alloc >
bool    operator<(  const AVLTree<T, Compare, Alloc>& lhs, 
                    const AVLTree<T, Compare, Alloc>& rhs )
{
    return ( ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) );
}

template< typename T, typename Compare, typename Alloc >
bool    operator>(  const AVLTree<T, Compare, Alloc>& lhs, 
                    const AVLTree<T, Compare, Alloc>& rhs )
{
    return ( rhs < lhs );
}

template< typename T, typename Compare, typename Alloc >
bool    operator<=(  const AVLTree<T, Compare, Alloc>& lhs, 
                    const AVLTree<T, Compare, Alloc>& rhs )
{
    return ( !(lhs > rhs) );
}

template< typename T, typename Compare, typename Alloc >
bool    operator>=(  const AVLTree<T, Compare, Alloc>& lhs, 
                    const AVLTree<T, Compare, Alloc>& rhs )
{
    return ( !(lhs < rhs) );
}

#endif