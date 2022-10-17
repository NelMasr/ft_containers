#include <vector>
#include "../incs/Colors.hpp"
#include <iomanip>

int main(void)
{
    std::cout << "O========================================O" << std::endl;
    std::cout << "|               CONSTRUCTORS             |" << std::endl;
    std::cout << "O========================================O" << std::endl;
    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ ft1(void) ]" << colors::reset << std::endl;
    
    std::vector<int> ft1;

    ft1.assign(5, 42);
    std::cout << "Printing ft1 contents" << std::endl;
    for (std::vector<int>::iterator it = ft1.begin(); it != ft1.end(); it++)
    {
        std::cout << std::setw(5);
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << colors::bold << colors::bright_blue << "[ ft2(count, value) ]" << colors::reset << std::endl;
    std::cout << "ft2 is initialized using constructor #3" << std::endl;
    
    std::vector<int> ft2(7, 100);
    
    std::cout << "Printing ft2 contents" << std::endl;
    for (std::vector<int>::iterator it = ft2.begin(); it != ft2.end(); it++)
    {
        std::cout << std::setw(5);
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    ft2.push_back(200);
    ft2.push_back(300);
    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ ft3(begin, end) ]" << colors::reset << std::endl;
    std::cout << "ft3 is initialized using iterators: ft2.begin() and ft2.end() (to which we added some other values in the meantime)" << std::endl;
    
    std::vector<int> ft3( ft2.begin(), ft2.end() );
    
    std::cout << "Printing ft3 contents" << std::endl;
    for (std::vector<int>::iterator it = ft3.begin(); it != ft3.end(); it++)
    {
        std::cout << std::setw(5);
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    ft3.push_back(400);
    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ ft4(ctor) ]" << colors::reset << std::endl;
    std::cout << "ft4 is initialized using copy constructor" << std::endl;

    std::vector<int> ft4(ft3);

    std::cout << "Printing ft4 contents" << std::endl;
    for (std::vector<int>::iterator it = ft4.begin(); it != ft4.end(); it++)
    {
        std::cout << std::setw(5);
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    ft4.push_back(500);
    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ ft5(operator=) ]" << colors::reset << std::endl;
    std::cout << "ft5 = ft4" << std::endl;

    std::vector<int> ft5;
    ft5.push_back(-4);
    ft5 = ft4;

    std::cout << "Printing ft5 contents" << std::endl;
    for (std::vector<int>::iterator it = ft5.begin(); it != ft5.end(); it++)
    {
        std::cout << std::setw(5);
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << std::endl;

    std::cout << "O========================================O" << std::endl;
    std::cout << "|                 CAPACITY               |" << std::endl;
    std::cout << "O========================================O" << std::endl;
    std::cout << std::endl;

    std::vector<int> ft6;
    std::cout << colors::bold << colors::bright_blue << "[ empty() ]" << colors::reset << std::endl;
    std::cout << "Is ft6 container empty: ";
    ft6.empty() ? std::cout << "Yes" << std::endl : std::cout << "No" << std::endl;
    std::cout << "Is ft4 container empty: ";
    ft4.empty() ? std::cout << "Yes" << std::endl : std::cout << "No" << std::endl;

    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ size() | max_size() ]" << colors::reset << std::endl;
    std::cout << "ft6.size(): " << ft6.size() << std::endl;
    std::cout << "ft5.size(): " << ft5.size() << std::endl;
    std::cout << "Adding 1 value to ft6 and removing 3 values from ft5" << std::endl;
    ft6.push_back(78);
    std::vector<int>::iterator   size_it = ft5.begin() + 5;
    std::vector<int>::iterator   size_itt = ft5.end() - 3;
    ft5.erase(size_it, size_itt);
    std::cout << "ft6.size(): " << ft6.size() << std::endl;
    std::cout << "ft5.size(): " << ft5.size() << std::endl;
    std::cout << std::endl;
    std::cout << "ft6.max_size(): " << ft6.max_size() << std::endl;
    std::cout << "ft5.max_size(): " << ft5.max_size() << std::endl;

    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ reserve() | capacity() ]" << colors::reset << std::endl;
    std::cout << colors::bright_magenta << "cplusplus.com test" << colors::reset << std::endl;
    std::vector<int>::size_type sz;
    std::vector<int> foo;
  
    sz = foo.capacity();
    std::cout << "making foo grow:\n";
    for (int i=0; i<100; ++i) {
    foo.push_back(i);
    if (sz!=foo.capacity()) {
      sz = foo.capacity();
      std::cout << "capacity changed: " << sz << '\n';
        }
    }

    std::vector<int> bar;
    sz = bar.capacity();
    bar.reserve(100);   // this is the only difference with foo above
    std::cout << "making bar grow:\n";
    for (int i=0; i<100; ++i) {
    bar.push_back(i);
    if (sz!=bar.capacity()) {
      sz = bar.capacity();
      std::cout << "capacity changed: " << sz << '\n';
        }
    }

    std::cout << std::endl;

    std::cout << "O========================================O" << std::endl;
    std::cout << "|                ITERATORS               |" << std::endl;
    std::cout << "O========================================O" << std::endl;
    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ begin() | end() ]" << colors::reset << std::endl;
    std::cout << colors::bright_magenta << "cplusplus.com test" << colors::reset << std::endl;
    {
        std::vector<int> myvector;
        
        for (int i=1; i<=5; i++) myvector.push_back(i);

        std::cout << "myvector contains:";
        for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }
    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ rbegin() | rend() ]" << colors::reset << std::endl;
    std::cout << colors::bright_magenta << "cplusplus.com test" << colors::reset << std::endl;
    {
        std::vector<int> myvector (5);  // 5 default-constructed ints

        int i = 0;

        std::vector<int>::reverse_iterator rit = myvector.rbegin();
        for (; rit!= myvector.rend(); ++rit)
            *rit = ++i;

        std::cout << "myvector contains:";
        for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }
    std::cout << std::endl;

    std::cout << "O========================================O" << std::endl;
    std::cout << "|              ELEMENT ACCESS            |" << std::endl;
    std::cout << "O========================================O" << std::endl;
    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ operator[] ]" << colors::reset << std::endl;
    std::vector<std::string> ft7(4);

    std::string s[] = { "Ceci", "est", "un", "test" };
    int size = 4;
    for (int i = 0; i != size; i++)
        ft7[i] = s[i];
    std::cout << "Initialized char* vector ft7 via operator[]. Printing contents:" << std::endl;
    for (std::vector<std::string>::iterator it = ft7.begin(); it != ft7.end(); it++)
    {
        std::cout << std::setw(5);
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ at() ]" << colors::reset << std::endl;
    std::cout << colors::bright_magenta << "cplusplus.com test" << colors::reset << std::endl;
    {
        std::vector<int> myvector (10);

        for (unsigned i=0; i<myvector.size(); i++)
            myvector.at(i)=i;

        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); i++)
            std::cout << ' ' << myvector.at(i);
        std::cout << '\n';
    }
    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ front() | back() ]" << colors::reset << std::endl;
    std::vector<std::string> f8;

    f8.push_back("Ceci est le front");
    f8.push_back("Ceci est le back");

    std::cout << "front: " << f8.front() << std::endl;
    std::cout << "back: " << f8.back() << std::endl;
    std::cout << std::endl;

    std::cout << "O========================================O" << std::endl;
    std::cout << "|                MODIFIERS               |" << std::endl;
    std::cout << "O========================================O" << std::endl;
    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ assign() ]" << colors::reset << std::endl;
    std::cout << colors::bright_magenta << "cplusplus.com test" << colors::reset << std::endl;
    {
        std::vector<int> first;
        std::vector<int> second;
        std::vector<int> third;

        first.assign (7,100);

        std::vector<int>::iterator it;
        it=first.begin()+1;

        second.assign (it,first.end()-1);

        int myints[] = {1776,7,4};
        third.assign (myints,myints+3);

        std::cout << "Size of first: " << int (first.size()) << '\n';
        std::cout << "Size of second: " << int (second.size()) << '\n';
        std::cout << "Size of third: " << int (third.size()) << '\n';
    }
    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ insert() ]" << colors::reset << std::endl;
    std::cout << colors::bright_magenta << "cplusplus.com test" << colors::reset << std::endl;
    {
        std::vector<int> myvector (3,100);
        std::vector<int>::iterator it;

        it = myvector.begin();
        it = myvector.insert ( it , 200 );

        myvector.insert (it,2,300);

        // "it" no longer valid, get a new one:
        it = myvector.begin();

        std::vector<int> anothervector (2,400);
        myvector.insert (it+2,anothervector.begin(),anothervector.end());

        int myarray [] = { 501,502,503 };
        myvector.insert (myvector.begin(), myarray, myarray+3);

        std::cout << "myvector contains:";
        for (it=myvector.begin(); it<myvector.end(); it++)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }
    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ erase() ]" << colors::reset << std::endl;
    std::cout << colors::bright_magenta << "cplusplus.com test" << colors::reset << std::endl;
    {
        std::vector<int> myvector;

        // set some values (from 1 to 10)
        for (int i=1; i<=10; i++) myvector.push_back(i);

        // erase the 6th element
        myvector.erase (myvector.begin()+5);

        // erase the first 3 elements:
        myvector.erase (myvector.begin(),myvector.begin()+3);

        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); ++i)
            std::cout << ' ' << myvector[i];
        std::cout << '\n';
    }
    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ push_back() | pop_back() ]" << colors::reset << std::endl;
    
    std::vector<std::string> ft8;
    ft8.push_back("Flemme");
    ft8.push_back("de");
    ft8.push_back("faire");
    ft8.push_back("des");
    ft8.push_back("tests");
    std::cout << "ft8 contents:";
    for (unsigned i=0; i<ft8.size(); ++i)
        std::cout << ' ' << ft8[i];
    std::cout << '\n';

    std::cout << "Popping." << std::endl;
    ft8.pop_back();
    std::cout << "ft8 contents:";
    for (unsigned i=0; i<ft8.size(); ++i)
        std::cout << ' ' << ft8[i];
    std::cout << '\n' << '\n';

    std::cout << colors::bold << colors::bright_blue << "[ swap() ]" << colors::reset << std::endl;
    {
        std::vector<int> foo (3,100);   // three ints with a value of 100
        std::vector<int> bar (5,200);   // five ints with a value of 200
        std::cout << "Before swap:" << std::endl;
        std::cout << "foo contains:";
        for (unsigned i=0; i<foo.size(); i++)
            std::cout << ' ' << foo[i];
        std::cout << '\n';

        std::cout << "bar contains:";
        for (unsigned i=0; i<bar.size(); i++)
            std::cout << ' ' << bar[i];
        std::cout << '\n';

        foo.swap(bar);
        std::cout << std::endl;
        std::cout << "After swap:" << std::endl;
        std::cout << "foo contains:";
        for (unsigned i=0; i<foo.size(); i++)
            std::cout << ' ' << foo[i];
        std::cout << '\n';

        std::cout << "bar contains:";
        for (unsigned i=0; i<bar.size(); i++)
            std::cout << ' ' << bar[i];
        std::cout << '\n';
    }
    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ clear() ]" << colors::reset << std::endl;
    std::cout << colors::bright_magenta << "cplusplus.com test" << colors::reset << std::endl;
    {
        std::vector<int> myvector;
        myvector.push_back (100);
        myvector.push_back (200);
        myvector.push_back (300);

        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); i++)
        std::cout << ' ' << myvector[i];
        std::cout << '\n';

        myvector.clear();
        myvector.push_back (1101);
        myvector.push_back (2202);

        std::cout << "myvector contains:";
        for (unsigned i=0; i<myvector.size(); i++)
        std::cout << ' ' << myvector[i];
        std::cout << '\n';
    }
    std::cout << std::endl;

    std::cout << "O========================================O" << std::endl;
    std::cout << "|            PERFORMANCE TESTS           |" << std::endl;
    std::cout << "O========================================O" << std::endl << std::endl;

    std::vector<int>  perf;

    std::cout << "For performance we will add 1M elements to container, then delete these 1M elements" << std::endl;
    std::cout << std::endl;
    std::cout << "1/ Adding 1M elements" << std::endl;
    for (int i = 0; i < 1000000; i++)
        perf.push_back(i);
    std::cout << "Calling size() on ft4: " << perf.size() << std::endl;
    std::cout << "2/ Deleting 1M elements" << std::endl;
    for (int i = 0; i < 1000000; i++)
        perf.pop_back();

    std::cout << std::endl;

    std::cout << colors::bright_green << "END OF TESTS :)" << colors::reset << std::endl;
}