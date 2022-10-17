#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "Iterators.hpp"
# include "lexicographical_compare.hpp"
# include "type_traits.hpp"
# include <iostream>
# include <cstddef>
# include <tgmath.h>
# include <algorithm>

namespace ft {

template < class T, class Allocator = std::allocator<T> >
class vector
{
    public:
        typedef T                                   value_type;
        typedef Allocator                           allocator_type;
        typedef std::size_t                         size_type;
        typedef T&                                  reference;
        typedef T const &                           const_reference;
        typedef typename Allocator::pointer         pointer;
        typedef typename Allocator::const_pointer   const_pointer;
        typedef std::ptrdiff_t                      difference_type;

        template < typename It, bool isConst = false >
        class VectorIt
        {
            It*  _p;

            public:
                typedef It                              value_type;
                typedef std::ptrdiff_t                  difference_type;
                typedef It*                             pointer;
                typedef It&                             reference;
                typedef std::random_access_iterator_tag iterator_category;

                VectorIt(void) : _p() {}
                VectorIt(pointer value) : _p(value) {}
                VectorIt(const VectorIt & src) : _p(src._p) {}
                
                VectorIt & operator=(const VectorIt & rhs)
                {
                    this->_p = rhs._p;
                    return (*this);
                }

                operator VectorIt<const It, true>() const
                {
                    return VectorIt<const It, true>(_p);
                }

                VectorIt &  operator++()
                {
                    ++this->_p;
                    return (*this);
                }

                VectorIt    operator++(int)
                {
                    VectorIt    tmp(*this);

                    ++(*this);
                    return (tmp);
                }

                VectorIt &  operator--()
                {
                    --this->_p;
                    return (*this);
                }

                VectorIt    operator--(int)
                {
                    VectorIt    tmp(*this);

                    --(*this);
                    return (tmp);
                }
                
                reference    operator*( void ) const { return (*_p); }

                VectorIt &  operator+=(difference_type n)
                {
                    this->_p += n;

                    return (*this);
                }

                VectorIt &  operator-=(difference_type n)
                {
                    this->_p -= n;

                    return (*this);
                }

                VectorIt    operator+(difference_type n) const
                {
                    return ( VectorIt( _p + n ) );
                }

                VectorIt    operator-(difference_type n)
                {
                    VectorIt    result;

                    result._p = this->_p - n;
                    return (result);
                }

                difference_type operator-(const VectorIt<It, false> & rhs) const
                {
                    return ( _p - &(*rhs) );
                }

                difference_type operator-(const VectorIt<const It, true> & rhs) const
                {
                    return ( _p - &(*rhs) );
                }

                bool        operator==(const VectorIt<It, false> & rhs) const { return ( this->_p == &(*rhs) ); }

                bool        operator!=(const VectorIt<It, false> & rhs) const { return ( this->_p != &(*rhs) ); }

                bool        operator<(const VectorIt<It, false> & rhs) const { return ( this->_p < &(*rhs) ); }

                bool        operator>(const VectorIt<It, false> & rhs) const { return ( this->_p > &(*rhs) ); }

                bool        operator<=(const VectorIt<It, false> & rhs) const { return ( this->_p <= &(*rhs) ); }

                bool        operator>=(const VectorIt<It, false> & rhs) const { return ( this->_p >= &(*rhs) ); }
                
                bool        operator==(const VectorIt<const It, true> & rhs) const { return ( this->_p == &(*rhs) ); }

                bool        operator!=(const VectorIt<const It, true> & rhs) const { return ( this->_p != &(*rhs) ); }

                bool        operator<(const VectorIt<const It, true> & rhs) const { return ( this->_p < &(*rhs) ); }

                bool        operator>(const VectorIt<const It, true> & rhs) const { return ( this->_p > &(*rhs) ); }

                bool        operator<=(const VectorIt<const It, true> & rhs) const { return ( this->_p <= &(*rhs) ); }

                bool        operator>=(const VectorIt<const It, true> & rhs) const { return ( this->_p >= &(*rhs) ); }

                reference   operator[](difference_type n) const { return ( this->_p[n] ); }

                pointer     operator->(void) { return ( _p ); }
        };

        template < typename It, bool IsConst >
        friend VectorIt<It, IsConst>    operator+( 
                            typename VectorIt<It, IsConst>::difference_type lhs, 
                            const VectorIt<It, IsConst>& rhs )
        {
            return ( VectorIt<It, IsConst>(rhs + lhs) );
        }

        typedef VectorIt<T, false>                      iterator;
        typedef VectorIt<const T, true>                 const_iterator;
        typedef ft::reverse_iterator<iterator>          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

    private:
        Allocator   _allocator;
        size_type   _capacity;
        T*          _data;
        size_type   _size;

        static  size_type newVectorSize(size_type size)
        {
            static  size_type coeff = 2;
            
            if (size)
                return (size * coeff);
            return (1);
        }

    public:

        /* ====================== MEMBER FUNCTIONS ====================== */

                        /*      CONSTRUCTORS      */

        // (1)
        vector( void ) :    
            _allocator(Allocator()), 
            _capacity(newVectorSize(0)), 
            _data(_allocator.allocate(_capacity)), 
            _size(0)
        {}

        // (2)
        explicit vector( const Allocator & alloc ) :    
            _allocator(alloc), 
            _capacity (newVectorSize(0)), 
            _data(_allocator.allocate(_capacity)), 
            _size(0)
        {}

        // (3)
        explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator() ) : 
            _allocator(alloc), 
            _capacity(newVectorSize(count)), 
            _data(_allocator.allocate(_capacity)), 
            _size(count)
        {
            for (size_type i = 0; i < _size; i++)
                _allocator.construct(_data + i, value);
        }

        // (4)
        template < class InputIt >
        vector( InputIt first,
                typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last,
                const Allocator & alloc = Allocator() ) : 
            _allocator(alloc), 
            _capacity( newVectorSize(ft::diff(first, last)) ),
            _data(_allocator.allocate(_capacity)),
            _size(ft::diff(first, last))
        {
            for (size_type i = 0; i < _size; i++, first++)
                _allocator.construct(_data + i, *first);
        }

        // (5)
        vector( const vector & other ) :    
            _allocator(Allocator()), 
            _capacity(newVectorSize(other.size())), 
            _data(_allocator.allocate(_capacity)), //inception test
            _size(other.size())
        {
            for (size_type i = 0; i != size(); i++)
            {
                _allocator.construct(_data + i, other._data[i]);
            }
        }

                    /*      DESTRUCTOR      */

        ~vector()
        {
            clear();
            _allocator.deallocate(_data, _capacity);
        }

                    /*      OPERATOR=      */

        vector<T>&    operator=(vector<T> const & rhs)
        {
            if ( this != &rhs )
            {
                _allocator = rhs._allocator;
                assign( rhs.begin(), rhs.end() );
            }
            return *this;
        }


                    /*      ASSIGN      */
        // (1)
        void        assign(size_type count, const T& value)
        {
            if (count > _capacity)
                reserve(count);
            for (size_type i = 0; i < count; i++)
            {
                if (i < _size)
                    _data[i] = value;
                else
                    _allocator.construct(_data + i, value);
            }

            _size = count;
        }

        // (2)
        template < class InputIt >
        void        assign( InputIt first,
                            typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last )
        {
            size_type   count = ft::diff(first, last);
            
            if (count > _capacity)
                reserve( newVectorSize(count) );

            for (size_type i = 0; i < count; i++, first++)
            {
                if (i < _size)
                    _data[i] = *first;
                else
                    _allocator.construct(_data + i, *first);
            }

            for (size_type i = count; i < (size()); ++i)
            {
                _allocator.destroy(_data + i);
            }

            _size = count;
        }

                    /*      GET ALLOCATOR      */

        allocator_type  get_allocator( void ) const { return ( _allocator ); }

        /* ====================== CAPACITY ====================== */

        bool        empty( void ) const
        {
            return ( begin() == end() );
        }

        size_type   size( void )  const { return ( _size ); }

        size_type   max_size( void ) const { return ( _allocator.max_size() ); }

        void        reserve( size_type new_cap )
        {
            if ( new_cap <= _capacity )
                return ;
            if ( new_cap > max_size() )
                throw std::length_error("ft_vector::reserve: New cap is greater than the max size allowed.");

            T*      result;

            result = _allocator.allocate(new_cap);

            for (size_type i = 0; i < size(); i++)
            {
                _allocator.construct(result + i, _data[i]);
                _allocator.destroy(_data + i);
            }
            _allocator.deallocate(_data, _capacity);

            _data = result;
            _capacity = new_cap;
        }

        size_type   capacity( void ) const { return ( _capacity ); }

        /* ====================== ITERATORS ====================== */

        iterator                begin( void )
        {
            iterator    tmp( _data );

            return ( tmp );
        }

        const_iterator          begin( void ) const
        {
            const_iterator  tmp( _data );

            return ( tmp );
        }

        iterator                end( void )
        {
            iterator    tmp( _data + size() );

            return ( tmp );
        }

        const_iterator          end( void ) const
        {
            const_iterator  tmp( _data + size() );

            return ( tmp );
        }

        reverse_iterator        rbegin( void )
        { 
            return ( reverse_iterator(end()) ); 
        }

        const_reverse_iterator  rbegin( void ) const
        {
            return ( const_reverse_iterator(end()) );
        }

        reverse_iterator        rend( void )
        {
            return ( reverse_iterator(begin()) );
        }

        const_reverse_iterator  rend( void ) const
        {
            return (const_reverse_iterator(begin()) );
        }

        /* ====================== ACCESS ====================== */
        
        value_type&             operator[]( size_type pos ) { return ( _data[pos] ); }

        value_type&             operator[]( size_type pos ) const { return ( _data[pos] ); }

        value_type&             at( size_type pos )
        {
            if ( !(pos < size() ) )
                throw(std::out_of_range("ft_vector::at: Requested pos is out of range."));
            
            return ( operator[](pos) );
        }

        const value_type&       at( size_type pos ) const
        {
            if (!(pos < size() ) )
                throw(std::out_of_range("Requested pos is out of range."));
            
            return ( operator[](pos) );
        }

        reference               front( void ) { return ( *begin() ); }

        const_reference         front( void ) const { return ( *begin() ); }

        reference               back( void ) { return ( *(end() - 1) ); }

        const_reference         back( void ) const { return ( *(end() - 1) ); }

        T*                      data( void ) { return ( _data ); }

        const T*                data( void ) const { return ( _data ); }

        /* ====================== MODIFIERS ====================== */

        void    clear( void )
        {
            for (size_type i = 0; i != size(); i++)
            {
                _allocator.destroy(_data + i);
            }

            _size = 0;
        }
        
        void    push_back( const T& value )
        {
            if ( size() == capacity() )
                reserve( newVectorSize( capacity() ) );
            
            _allocator.construct(_data + _size, value);
            _size++;
        }
        
        iterator    insert( iterator pos, const T& value)
        {
            size_type   stop = pos - begin();

            push_back(value);
            for (size_type i = end() - begin() - 1; i > stop; i--)
            {
                _data[i] = _data[i - 1];
            }

            _data[stop] = value;
            return ( iterator( _data + stop ) );
        }

        void        insert( iterator pos, size_type count, const T& value )
        {
            if (count == 0)
                return ;

            size_type   stop = pos - begin();

            if (capacity() < size() + count)
            {
                reserve( newVectorSize( size() + count ) );
            }

            if ( size() > 0 && stop != size() )
            {
                for (size_type i = size() - 1; i >= stop;)
                {
                    if ( (i + count) >= size() )
                        _allocator.construct(_data + i + count, _data[i]);
                    else
                        _data[i + count] = _data[i];
                    if (i-- == stop)
                        break ;
                }
            }

            for (size_type i = stop; i < (stop + count); i++)
            {
                if ( i >= size() )
                    _allocator.construct(_data + i, value);
                else
                    _data[i] = value;
            }

            _size += count;
        }

        template < class InputIt >
        void    insert( iterator pos, 
                        InputIt first,
                        typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last )
        {
            size_type   count = ft::diff(first, last);
            size_type   stop = pos - begin();

            if (capacity() < size() + count)
            {
                reserve( newVectorSize( size() + count ) );
            }

            if (size() > 0)
            {
                for (size_type i = size() - 1; i >= stop;)
                {
                    if ( (i + count) > size() )
                        _allocator.construct(_data + i + count, _data[i]);
                    else
                        _data[i + count] = _data[i];
                    if (i-- == stop)
                        break ;
                }
            }

            for (size_type i = stop; i < (stop + count); i++)
            {
                if (i >= size())
                    _allocator.construct(_data + i, *first);
                else
                    _data[i] = *first;
                first++;
            }

            _size += count;
        }

        iterator    erase( iterator pos )
        {
            _allocator.destroy(&(*pos));

            for (iterator it = pos; it != end() - 1; it++)
            {
                it[0] = it[1];
            }

            _size--;
            return ( pos );
        }

        iterator    erase( iterator first, iterator last )
        {
            difference_type     n = ft::diff(first, last);

            while ( first != end() )
            {
                if (first < end() - n)
                    first[0] = first[n];
                else
                    _allocator.destroy(&(*first));
                first++;
            }

            _size -= n;
            return ( last - n );
        }

        void        pop_back()
        {
            _size--;
            _allocator.destroy(_data + _size);
        }

        void        resize( size_type count, T value = T() )
        {

            if (count > capacity())
                reserve(count);
    
            if (size() < count)
            {
                for (size_type i = size(); i < ( count ); i++)
                {
                    _allocator.construct(_data + i, value);
                }
            }
            else
            {
                for (size_type i = count; i != size(); i++)
                {
                    _allocator.destroy(_data + i);
                }
            }
            _size = count;
        }

        void        swap( vector& other )
        {
            std::swap( _data, other._data );
            std::swap( _allocator, other._allocator );
            std::swap( _capacity, other._capacity );
            std::swap( _size, other._size );
        }
};

template < class T, class Alloc >
bool    operator==( const ft::vector<T, Alloc>& lhs, 
                    const ft::vector<T, Alloc>& rhs)
{
    return ( (lhs.size() == rhs.size()) 
                && ft::equal( lhs.begin(), lhs.end(), rhs.begin() ) );
}

template < class T, class Alloc >
bool    operator!=( const ft::vector<T, Alloc>& lhs, 
                    const ft::vector<T, Alloc>& rhs)
{
    return ( (lhs.size() != rhs.size()) 
                || !ft::equal( lhs.begin(), lhs.end(), rhs.begin() ) );
}

template < class T, class Alloc >
bool    operator<( const ft::vector<T, Alloc>& lhs, 
                    const ft::vector<T, Alloc>& rhs)
{
    return ( ft::lexicographical_compare( lhs.begin(), lhs.end(), rhs.begin(), rhs.end() ) );
}

template < class T, class Alloc >
bool    operator>( const ft::vector<T, Alloc>& lhs, 
                    const ft::vector<T, Alloc>& rhs)
{
    return ( !(operator<(lhs, rhs)) && !(operator==(lhs, rhs)) );
}

template < class T, class Alloc >
bool    operator<=( const ft::vector<T, Alloc>& lhs, 
                    const ft::vector<T, Alloc>& rhs)
{
    return ( !(operator>( lhs, rhs ) ) );
}

template < class T, class Alloc >
bool    operator>=( const ft::vector<T, Alloc>& lhs, 
                    const ft::vector<T, Alloc>& rhs)
{
    return ( !(operator<( lhs, rhs ) ) );
}

template< class T, class Alloc >
void    swap(   ft::vector<T, Alloc>& lhs, 
                ft::vector<T, Alloc>& rhs)
{
    lhs.swap(rhs);
}

}

#endif