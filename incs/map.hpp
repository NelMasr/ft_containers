#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include <memory>
# include "pair.hpp"
# include "AVLTree.hpp"

namespace ft {

template <  class Key, 
            class T, 
            class Compare = std::less<Key>, 
            class Allocator = std::allocator<ft::pair< const Key, T> >
> class map
{
    private:
        Compare         _compare;
        Allocator       _allocator;

    public:
        typedef             Key                                     key_type;
        typedef             T                                       mapped_type;
        typedef typename    ft::pair<Key, T>                        value_type;
        typedef             std::size_t                             size_type;
        typedef             std::ptrdiff_t                          difference_type;
        typedef             Compare                                 key_compare;
        typedef             Allocator                               allocator_type;
        typedef             value_type&                             reference;
        typedef             const value_type&                       const_reference;
        typedef typename    Allocator::pointer                      pointer;
        typedef typename    Allocator::const_pointer                const_pointer;
    
        class value_compare
        {
            protected:
                Compare comp;

            public:
                value_compare( void ) : comp( Compare() ) {};
                value_compare( Compare c ) : comp(c) {};
            
            public:
                ~value_compare( void ) {};

                bool    operator()( const value_type &lhs, const value_type& rhs) const
                {
                    return ( comp( lhs.first, rhs.first ) );
                }
        };

        /* ====================== OBSERVERS ====================== */

        key_compare     key_comp( void ) const { return (_compare); }
        value_compare   value_comp( void ) const { return ( value_compare(_compare) ); }
    
    private:
        typedef         AVLTree<value_type, value_compare, allocator_type>  InternalTree;

    public:
        typedef typename    InternalTree::iterator                  iterator;
        typedef typename    InternalTree::const_iterator            const_iterator;
        typedef typename    InternalTree::reverse_iterator          reverse_iterator;
        typedef typename    InternalTree::const_reverse_iterator    const_reverse_iterator;
        InternalTree        _data;        


        /* ====================== CONSTRUCTORS ====================== */

        //(1)
        map() : _compare(), _allocator() {}
        
        explicit map(   const Compare& comp,
                        const Allocator& alloc = Allocator() ) : _compare(comp), _allocator(alloc) {}
        
        //(2)
        template< class InputIt >
        map( InputIt first, InputIt last, 
            const Compare& comp = Compare(), 
            const Allocator& alloc = Allocator() )
        {
            while (first != last)
            {
                _data.insert(*first);
                first++;
            }

            _compare = comp;
            _allocator = alloc;
        }

        //(4)
        map(const map& other)
        {
            _compare = other._compare;
            _allocator = other._allocator;
            _data.insert( other.begin(), other.end() );
        }

        ~map() {}

        map&    operator=( const map& other )
        {
            if ( this != &other )
            {
                _data.clear();
                _data.insert( other.begin(), other.end() );
                _compare = other._compare;
                _allocator = other._allocator;
            }

            return (*this);
        }

        allocator_type  get_allocator(void) const { return ( _allocator ); }

        /* ====================== ELEMENT ACCESS ====================== */

        T&  at( const Key& key )
        {
            iterator    it = find(key);

            if ( it == end() )
                throw ( std::out_of_range("No match found") );

            return ( it->second );
        }

        const T&    at( const Key& key ) const
        {
            const_iterator  it = find(key);

            if ( it == end() )
                throw ( std::out_of_range("No match found") );
            
            return ( it->second );
        }

        mapped_type&  operator[]( const Key& key )
        {
            iterator    it = find(key);

            if (it == end())
                it = insert( value_type(key, mapped_type()) ).first;
            return (it->second);
        }

        /* ====================== ITERATORS ====================== */

        iterator                begin() { return ( _data.begin() ); }

        const_iterator          begin() const { return ( _data.begin() ); }

        iterator                end() { return ( _data.end() ); }

        const_iterator          end() const { return ( _data.end() ); }

        reverse_iterator        rbegin() { return ( _data.rbegin() ); }

        const_reverse_iterator  rbegin() const { return ( _data.rbegin() ); }

        reverse_iterator        rend() { return ( _data.rend() ); }

        const_reverse_iterator  rend() const { return ( _data.rend() ); }

        /* ====================== CAPACITY ====================== */

        bool        empty(void) const { return ( size() == 0 ); }

        size_type   size(void) const { return ( _data.size() ); }

        size_type   max_size(void) const { return ( _data.max_size() ); }

        /* ====================== MODIFIERS ====================== */

        void        clear(void) { _data.clear(); }

        ft::pair<iterator, bool>    insert( const value_type& value )
        {
            return ( _data.insert(value) );
        }

        iterator                    insert( iterator hint, const value_type& value )
        {
            return ( _data.insert(hint, value) );
        }

        template< class InputIt >
        void                        insert( InputIt first, InputIt second )
        {
            return ( _data.insert(first, second) );
        }

        void    erase( iterator pos )
        {
            return ( _data.erase(pos) );
        }

        void    erase( iterator first, iterator second )
        {
            return ( _data.erase(first, second) );
        }

        size_type   erase( const Key& key )
        {
            return ( _data.erase( ft::make_pair(key, typename value_type::second_type()) ) );
        }

        void    swap( map& other )
        {
            if ( this != &other )
                _data.swap(other._data);
        }

        /* ====================== LOOKUP ====================== */

        size_type   count( const Key& key ) const
        {
            const_iterator    it = find(key);
            size_type   ret;

            it != end() ? ret = 1 : ret = 0;

            return (ret);
        }

        iterator    find( const Key& key )
        {
            return ( _data.find( ft::make_pair(key, typename value_type::second_type()) ) );
        }

        const_iterator    find( const Key& key ) const
        {
            return ( _data.find( ft::make_pair(key, typename value_type::second_type()) ) );
        }

        ft::pair<iterator, iterator>    equal_range( const Key& key )
        {
            return ( _data.equal_range( ft::make_pair(key, typename value_type::second_type()) ) );
        }

        ft::pair<const_iterator, const_iterator>    equal_range( const Key& key ) const
        {
            return ( _data.equal_range( ft::make_pair(key, typename value_type::second_type()) ) );
        }

        iterator            lower_bound( const Key& key )
        {
            return ( _data.lower_bound( ft::make_pair(key, typename value_type::second_type() ) ) );
        }

        const_iterator      lower_bound( const Key& key ) const
        {
            return ( _data.lower_bound( ft::make_pair(key, typename value_type::second_type() ) ) );
        }

        iterator            upper_bound( const Key& key )
        {
            return ( _data.upper_bound( ft::make_pair(key, typename value_type::second_type() ) ) );
        }

        const_iterator      upper_bound( const Key& key ) const
        {
            return ( _data.upper_bound( ft::make_pair(key, typename value_type::second_type() ) ) );
        }

        /* ====================== OPERATORS ====================== */

        friend  bool operator==(    const ft::map<Key, T, Compare, Allocator>& lhs, 
                                    const ft::map<Key, T, Compare, Allocator>& rhs )
        {
            return (lhs._data == rhs._data);
        }

        friend  bool operator!=(    const ft::map<Key, T, Compare, Allocator>& lhs, 
                                    const ft::map<Key, T, Compare, Allocator>& rhs )
        {
            return (lhs._data != rhs._data);
        }

        friend  bool operator<(    const ft::map<Key, T, Compare, Allocator>& lhs, 
                                    const ft::map<Key, T, Compare, Allocator>& rhs )
        {
            return (lhs._data < rhs._data);
        }

        friend  bool operator>(    const ft::map<Key, T, Compare, Allocator>& lhs, 
                                    const ft::map<Key, T, Compare, Allocator>& rhs )
        {
            return (lhs._data > rhs._data);
        }

        friend  bool operator<=(    const ft::map<Key, T, Compare, Allocator>& lhs, 
                                    const ft::map<Key, T, Compare, Allocator>& rhs )
        {
            return (lhs._data <= rhs._data);
        }

        friend  bool operator>=(    const ft::map<Key, T, Compare, Allocator>& lhs, 
                                    const ft::map<Key, T, Compare, Allocator>& rhs )
        {
            return (lhs._data >= rhs._data);
        }

};

template< class Key, class T, class Compare, class Alloc >
void    swap(   ft::map<Key, T, Compare, Alloc>& lhs, 
                ft::map<Key, T, Compare, Alloc>& rhs )
{
    lhs.swap(rhs);
}

}

#endif