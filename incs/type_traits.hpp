#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft {

const class nullptr_t
{
    public:

        template < typename T >
        operator T*() const { return (0); }

        template < typename T, typename U >
        operator T U::*() const { return (0); }

        operator void*() const { return (0); }

    private:

        void    operator&() const;
} c_nullptr = {};


template < bool B, class T = void >
struct enable_if {};

template < class T >
struct enable_if < true, T > { typedef T type; };

template < class T, T v >
struct integral_constant
{
    static const T  value = v;
    
    typedef T                       value_type;
    typedef integral_constant<T, v> type;

    operator value_type() const { return value; };
};

typedef integral_constant< bool, true >     true_type;
typedef integral_constant< bool, false >    false_type;

template < class T >
struct is_integral : public false_type {};

template < class T >
struct is_integral<const T> : public false_type {};

template <>
struct is_integral<bool> : public true_type {};

template <>
struct is_integral<char> : public true_type {};

template <>
struct is_integral<wchar_t> : public true_type {};

template <>
struct is_integral<short> : public true_type {};

template <>
struct is_integral<int> : public true_type {};

template <>
struct is_integral<long int> : public true_type {};

template <>
struct is_integral<long long int> : public true_type {};

template <>
struct is_integral<unsigned char> : public true_type {};

template <>
struct is_integral<unsigned short> : public true_type {};

template <>
struct is_integral<unsigned int> : public true_type {};

template <>
struct is_integral<unsigned long int> : public true_type {};

template <>
struct is_integral<unsigned long long int> : public true_type {};

}

#endif