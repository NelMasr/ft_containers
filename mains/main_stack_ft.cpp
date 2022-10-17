#include "../incs/stack.hpp"
#include "../incs/Colors.hpp"
#include <iomanip>

int main(void)
{
    std::cout << "O========================================O" << std::endl;
    std::cout << "|               CONSTRUCTORS             |" << std::endl;
    std::cout << "O========================================O" << std::endl;

    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ ft1 ]" << colors::reset << std::endl;
    ft::stack<int>  ft1;
    ft1.push(42);
    std::cout << "Printing ft1 contents: " << std::endl;
    std::cout << std::setw(14);
    std::cout << ft1.top() << std::endl;

    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ ft2 - ctor(stack) ]" << colors::reset << std::endl;
    std::cout << "ft2 is initialized using copy constructor" << std::endl;
    ft::stack<int>  ft2(ft1);
    ft2.push(5);
    std::cout << "Printing ft2 contents:" << std::endl;
    while ( !ft2.empty() )
    {
        std::cout << std::setw(14);
        std::cout << ft2.top() << std::endl;
        ft2.pop();
    }
    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ ft3 - operator= ]" << colors::reset << std::endl;
    ft::stack<int>  ft3 = ft1;
    ft3.push(84);
    std::cout << "Printing ft3 contents:" << std::endl;
    while ( !ft3.empty() )
    {
        std::cout << std::setw(14);
        std::cout << ft3.top() << std::endl;
        ft3.pop();
    }
    std::cout << std::endl;
    
    std::cout << "O========================================O" << std::endl;
    std::cout << "|             ELEMENT ACCESS             |" << std::endl;
    std::cout << "O========================================O" << std::endl;

    std::cout << std::endl;
    std::cout << colors::bold << colors::bright_blue << "[ top() ]" << colors::reset << std::endl;
    std::cout << "Calling top() on ft1: " << ft1.top() << std::endl;
    std::cout << "Adding 3 more values to ft1" << std::endl;
    ft1.push(78);
    ft1.push(492);
    ft1.push(8);
    std::cout << "Calling top() on ft1: " << ft1.top() << std::endl;

    std::cout << std::endl;

    std::cout << "O========================================O" << std::endl;
    std::cout << "|             ELEMENT ACCESS             |" << std::endl;
    std::cout << "O========================================O" << std::endl;

    std::cout << std::endl;
    std::cout << colors::bold << colors::bright_blue << "[ empty() ]" << colors::reset << std::endl;
    std::cout << "Is ft1 empty: ";
    ft1.empty() ? std::cout << "true" << std::endl : std::cout << "false" << std::endl;
    std::cout << "Is ft2 empty: ";
    ft2.empty() ? std::cout << "true" << std::endl : std::cout << "false" << std::endl;

    std::cout << std::endl;
    std::cout << colors::bold << colors::bright_blue << "[ size() ]" << colors::reset << std::endl;
    std::cout << "Calling size() on ft1: " << ft1.size() << std::endl;
    std::cout << "Adding 5 more values to ft1" << std::endl;
    ft1.push(12);
    ft1.push(786);
    ft1.push(202);
    ft1.push(65);
    ft1.push(7524);
    std::cout << "Calling size() on ft1: " << ft1.size() << std::endl;
    std::cout << "Popping 2 values" << std::endl;
    ft1.pop();
    ft1.pop();
    std::cout << "Calling size() on ft1: " << ft1.size() << std::endl;
    std::cout << "Calling size() on ft2: " << ft2.size() << std::endl;
    std::cout << std::endl;
    
    std::cout << "O========================================O" << std::endl;
    std::cout << "|            PERFORMANCE TESTS           |" << std::endl;
    std::cout << "O========================================O" << std::endl << std::endl;

    ft::stack<int>  ft4;

    std::cout << "For performance we will add 1M elements to container, then delete these 1M elements" << std::endl;
    std::cout << std::endl;
    std::cout << "1/ Adding 1M elements" << std::endl;
    for (int i = 0; i < 1000000; i++)
        ft4.push(i);
    std::cout << "Calling size() on ft4: " << ft4.size() << std::endl;
    std::cout << "2/ Deleting 1M elements" << std::endl;
    for (int i = 0; i < 1000000; i++)
        ft4.pop();

    std::cout << std::endl;

    std::cout << colors::bright_green << "END OF TESTS :)" << colors::reset << std::endl;
}