#ifndef ITERATORS_HPP
# define ITERATORS_HPP

# include <iterator>
# include <cstddef>
# include "type_traits.hpp"

namespace ft {

template <class Iter>
struct iterator_traits
{
    typedef typename Iter::difference_type   difference_type;
    typedef typename Iter::value_type        value_type;
    typedef typename Iter::pointer           pointer;
    typedef typename Iter::reference         reference;
    typedef typename Iter::iterator_category iterator_category;
};

template <class T>
struct iterator_traits<T*>
{
    typedef std::ptrdiff_t                  difference_type;
    typedef T                               value_type;
    typedef const T*                        pointer;
    typedef const T&                        reference;
    typedef std::random_access_iterator_tag iterator_category;
};

template < class InputIt >
typename iterator_traits<InputIt>::difference_type  diff(InputIt first, InputIt last)
{
    typename iterator_traits<InputIt>::difference_type n = 0;

    while (first != last)
    {
        n++;
        first++;
    }
    return (n);
}

template <class Iter>
class reverse_iterator
{
    protected:
        Iter current;

    public:

        typedef          Iter                                           iterator_type;
        typedef typename ft::iterator_traits<Iter>::difference_type     difference_type;
        typedef typename ft::iterator_traits<Iter>::value_type          value_type;
        typedef typename ft::iterator_traits<Iter>::iterator_category   iterator_category;
        typedef typename ft::iterator_traits<Iter>::pointer             pointer;
        typedef typename ft::iterator_traits<Iter>::reference           reference;

    public:
        reverse_iterator() {}
        explicit reverse_iterator(iterator_type x) : current(x) {}
        template <class U>
        reverse_iterator( const reverse_iterator<U> & other) : current(other.base()) {}

        template <class U>
        reverse_iterator & operator=(const reverse_iterator<U> & other)
        {
            current = other.base();
            return ( *this );
        }

        iterator_type   base(void) const { return (current); }

        value_type&   operator*() const
        {
            Iter    tmp = current;
            
            return ( *--tmp );
        }

        pointer     operator->() const
        {
            return ( &operator*() );
        }

        reference   operator[](difference_type n) const
        {
            return (base()[-n-1]); //?
        }

        reverse_iterator &  operator++()
        {
            --current;
            return ( *this );
        }

        reverse_iterator &  operator--()
        {
            ++current;
            return ( *this );
        }

        reverse_iterator    operator++(int)
        {
            Iter    tmp = current;

            --current;
            return ( reverse_iterator(tmp) );
        }

        reverse_iterator    operator--(int)
        {
            Iter    tmp = current;

            ++current;
            return ( reverse_iterator(tmp) );
        }

        reverse_iterator    operator+(difference_type n) const { return ( reverse_iterator(base() - n) ); }

        reverse_iterator    operator-(difference_type n) const { return ( reverse_iterator(base() + n) ); }

        reverse_iterator    operator+=(difference_type n)
        {
            return ( reverse_iterator( current -= n ) );
        }

        reverse_iterator    operator-=(difference_type n)
        {
            return ( reverse_iterator( current += n ));
        }
};

template <class Iterator1, class Iterator2>
bool    operator==(const ft::reverse_iterator<Iterator1>& lhs, 
                    const ft::reverse_iterator<Iterator2>& rhs)
{
    return ( lhs.base() == rhs.base() );
}

template <class Iterator1, class Iterator2>
bool    operator!=(const ft::reverse_iterator<Iterator1>& lhs, 
                    const ft::reverse_iterator<Iterator2>& rhs)
{
    return ( lhs.base() != rhs.base() );
}

template <class Iterator1, class Iterator2>
bool    operator<(const ft::reverse_iterator<Iterator1>& lhs, 
                    const ft::reverse_iterator<Iterator2>& rhs)
{
    return ( lhs.base() > rhs.base() );
}

template <class Iterator1, class Iterator2>
bool    operator<=(const ft::reverse_iterator<Iterator1>& lhs, 
                    const ft::reverse_iterator<Iterator2>& rhs)
{
    return ( lhs.base() >= rhs.base() );
}

template <class Iterator1, class Iterator2>
bool    operator>(const ft::reverse_iterator<Iterator1>& lhs, 
                    const ft::reverse_iterator<Iterator2>& rhs)
{
    return ( lhs.base() < rhs.base() );
}

template <class Iterator1, class Iterator2>
bool    operator>=(const ft::reverse_iterator<Iterator1>& lhs, 
                    const ft::reverse_iterator<Iterator2>& rhs)
{
    return ( lhs.base() <= rhs.base() );
}

template <class Iter>
ft::reverse_iterator<Iter>  operator+(typename ft::reverse_iterator<Iter>::difference_type n, 
                                        const ft::reverse_iterator<Iter>& it)
{
    return ( ft::reverse_iterator<Iter>(it.base() - n) );
}

template <class Iterator>
typename ft::reverse_iterator<Iterator>::difference_type    
            operator-(  const ft::reverse_iterator<Iterator>& lhs, 
                        const ft::reverse_iterator<Iterator>& rhs)
{
    return ( rhs.base() - lhs.base() );
}

template <typename Iterator1, typename Iterator2>
typename ft::reverse_iterator<Iterator1>::difference_type    
            operator-(  const ft::reverse_iterator<Iterator1>& lhs, 
                        const ft::reverse_iterator<Iterator2>& rhs)
{
    return ( rhs.base() - lhs.base() );
}

}

#endif
