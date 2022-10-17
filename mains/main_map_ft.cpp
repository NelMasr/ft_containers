#include "../incs/AVLTree.hpp"
#include "../incs/map.hpp"
#include "../incs/pair.hpp"
#include "../incs/Colors.hpp"
#include <list>
#include <memory>
#include <string>
#include <iomanip>

int main(void)
{
    std::cout << "O========================================O" << std::endl;
    std::cout << "|               CONSTRUCTORS             |" << std::endl;
    std::cout << "O========================================O" << std::endl;
    
    std::cout << std::endl;
    
    ft::map<std::string, std::string>   ft1;
    ft1.insert( ft::make_pair("Baie de Goji", "Rouge") );
    ft1.insert( ft::make_pair("Baie de Goji", "Rouge") );
    ft1["Banane"] = "Orange";
    ft1["Banane"] = "Jaune";
    
    std::cout << colors::bold << colors::bright_blue << "[ ft1 ]" << std::endl << colors::reset << "Map contents: " << std::endl;
    for (ft::map<std::string, std::string>::iterator it = ft1.begin(); it != ft1.end(); it++) {
        std::cout << std::setw(14);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Searching for key 'Banane': ";
    ft::map<std::string, std::string>::iterator it = ft1.find("Banane");
    it != ft1.end() ? std::cout << it->first << " -> " << it->second << std::endl : std::cout << "No match found" << std::endl;
    std::cout << "Searching for key 'Peche': ";
    it = ft1.find("Peche");
    it != ft1.end() ? std::cout << it->first << " -> " << it->second << std::endl : std::cout << "No match found" << std::endl;
    std::cout << std::endl;

    ft::map<std::string, std::string>   ft2( ft1.begin(), ft1.end() );
    std::cout << colors::bold << colors::bright_blue << "[ ft2 - ctor(it1, it2) test ]" << std::endl << colors::reset << "Map contents: " << std::endl;    
    for (ft::map<std::string, std::string>::iterator it = ft2.begin(); it != ft2.end(); it++) {
        std::cout << std::setw(15);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }
    ft2.insert( ft::make_pair("Ananas", "Jaune") );
    std::cout << std::endl;

    ft::map<std::string, std::string>   ft3( ft2 );
    std::cout << colors::bold << colors::bright_blue << "[ ft3 - ctor( map ) test ]" << std::endl << colors::reset << "Map contents: " << std::endl;    
    for (ft::map<std::string, std::string>::iterator it = ft3.begin(); it != ft3.end(); it++) {
        std::cout << std::setw(15);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }
    ft3["Bergamote"] = "Vert";
    std::cout << std::endl;

    ft::map<std::string, std::string>   ft4 = ft3;
    std::cout << colors::bold << colors::bright_blue << "[ ft4 - ctor( operator= ) test ]" << std::endl << colors::reset << "Map contents: " << std::endl;
    for (ft::map<std::string, std::string>::iterator it = ft4.begin(); it != ft4.end(); it++) {
        std::cout << std::setw(15);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }

    std::cout << std::endl;

    std::cout << "O========================================O" << std::endl;
    std::cout << "|             ELEMENT ACCESS             |" << std::endl;
    std::cout << "O========================================O" << std::endl;

    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ at() ]" << colors::reset << std::endl;
    std::cout << "Printing at('Banane'): " << ft4.at("Banane") << std::endl;
    try {
    std::cout << "Printing at('Peche'): " << ft4.at("Peche") << std::endl;
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }
    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ operator[] ]" << colors::reset << std::endl;
    std::cout << "Returning Baie de Goji's value via operator[] (existing key): ft4['Baie de Goji'] -> " << ft4["Baie de Goji"] << std::endl;
    ft4["Avocat"] = "Violet";
    std::cout << "Added Avocat key via operator[]: ft4['Avocat'] -> " << ft4["Avocat"] << std::endl;
    ft4["Avocat"] = "Vert";
    std::cout << "Changed Avocat key's value via operator[]: ft4['Avocat'] -> " << ft4["Avocat"] << std::endl;

    std::cout << std::endl;

    std::cout << "O========================================O" << std::endl;
    std::cout << "|               ITERATORS                |" << std::endl;
    std::cout << "O========================================O" << std::endl << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ begin() | end() ]" << colors::reset << std::endl;
    std::cout << "Printing all nodes using iterators ( [KEY] -> [VALUE] ) : " << std::endl << std::endl;
    for (ft::map<std::string, std::string>::iterator it = ft4.begin(); it != ft4.end(); it++) {
        std::cout << std::setw(15);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }
    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ const begin() | const end() ]" << colors::reset << std::endl;
    std::cout << "Printing all nodes using iterators ( [KEY] -> [VALUE] ) : " << std::endl << std::endl;
    for (ft::map<std::string, std::string>::const_iterator it = ft4.begin(); it != ft4.end(); it++) {
        std::cout << std::setw(15);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }
    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ rbegin() | rend() ]" << colors::reset << std::endl;
    std::cout << "Printing all nodes using iterators ( [KEY] -> [VALUE] ) : " << std::endl << std::endl;
    for (ft::map<std::string, std::string>::reverse_iterator it = ft4.rbegin(); it != ft4.rend(); it++) {
        std::cout << std::setw(15);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }
    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ const rbegin() | const rend() ]" << colors::reset << std::endl;
    std::cout << "Printing all nodes using iterators ( [KEY] -> [VALUE] ) : " << std::endl << std::endl;
    for (ft::map<std::string, std::string>::const_reverse_iterator it = ft4.rbegin(); it != ft4.rend(); it++) {
        std::cout << std::setw(15);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }
    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ begin() | end() ]" << colors::reset << std::endl;
    std::cout << colors::bold << colors::bright_yellow << "Testing on empty container ft5 (should return nothing and not segfault)" << colors::reset << std::endl;
    ft::map<std::string, std::string>   ft5;
        for (ft::map<std::string, std::string>::iterator it = ft5.begin(); it != ft5.end(); it++) {
        std::cout << std::setw(15);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }
    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ rbegin() | rend() ]" << colors::reset << std::endl;
    std::cout << colors::bold << colors::bright_yellow << "Testing on empty container ft5 (should return nothing and not segfault)" << colors::reset << std::endl;
        for (ft::map<std::string, std::string>::iterator it = ft5.begin(); it != ft5.end(); it++) {
        std::cout << std::setw(15);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }
    std::cout << std::endl;

    std::cout << "O========================================O" << std::endl;
    std::cout << "|                CAPACITY                |" << std::endl;
    std::cout << "O========================================O" << std::endl << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ empty() ]" << colors::reset << std::endl;
    std::cout << "Is ft4 container empty (should be no)  -> ";
    ft4.empty() ? std::cout << "Yes" : std::cout << "No";
    std::cout << std::endl;
    std::cout << "Is ft5 container empty (should be yes) -> ";
    ft5.empty() ? std::cout << "Yes" : std::cout << "No";
    std::cout << std::endl << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ size() ]" << colors::reset << std::endl;
    std::cout << "ft4 size: " << ft4.size() << std::endl;
    std::cout << "ft5 size: " << ft5.size() << std::endl;

    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ max_size() ]" << colors::reset << std::endl;
    std::cout << "ft4 max_size: " << ft4.max_size() << std::endl;
    std::cout << "ft5 max_size: " << ft5.max_size() << std::endl;

    std::cout << std::endl;

    std::cout << "O========================================O" << std::endl;
    std::cout << "|               MODIFIERS                |" << std::endl;
    std::cout << "O========================================O" << std::endl << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ clear() ]" << colors::reset << std::endl;
    std::cout << "ft1 - Map contents pre-clear: " << std::endl;
    for (ft::map<std::string, std::string>::iterator it = ft1.begin(); it != ft1.end(); it++) {
        std::cout << std::setw(14);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Using clear()";
    ft1.clear();
    std::cout << " -> done" << std::endl;
    std::cout << "ft1 - Map contents post-clear (nothing should be between the 2 lines): " << std::endl;
    std::cout << "_______________________________________________________________________" << std::endl;
    for (ft::map<std::string, std::string>::iterator it = ft1.begin(); it != ft1.end(); it++) {
        std::cout << std::setw(14);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }
    std::cout << "_______________________________________________________________________" << std::endl;

    std::cout << std::endl;

    std::cout << "Using clear() on empty container";
    ft1.clear();
    std::cout << " -> done" << std::endl;

    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ insert() ]" << colors::reset << std::endl;
    std::cout << colors::bold << colors::bright_yellow << "insert(const value_type& value)" << colors::reset << std::endl;
    ft4.insert( ft::make_pair("Myrtille", "Bleu") );
    ft4.insert( ft::make_pair("Prune", "Violet") );
    ft4.insert( ft::make_pair("Papaye", "Orange") );
    std::cout << "Inserted 3 new keys, printing ft4 map contents:" << std::endl;
    for (ft::map<std::string, std::string>::iterator it = ft4.begin(); it != ft4.end(); it++) {
        std::cout << std::setw(14);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }

    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_yellow << "insert(InputIt first, InputIt last)" << colors::reset << std::endl;
    std::cout << "Creating new container ft6 with exclusive contents" << std::endl;
    ft::map<std::string, std::string>   ft6;
    ft6["Nefle"] = "Marron";
    ft6["Palmier peche"] = "Rouge";
    ft6["Pasteque"] = "Rouge";
    std::cout << "Printing ft6 contents:" << std::endl;
    for (ft::map<std::string, std::string>::iterator it = ft6.begin(); it != ft6.end(); it++) {
        std::cout << std::setw(14);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Adding all ft4 keys in ft6 using ft4.begin() and ft4.end() parameters for insert()" << std::endl;
    ft6.insert( ft4.begin(), ft4.end() );
    std::cout << "Printing new ft6 contents" << std::endl;
    for (ft::map<std::string, std::string>::iterator it = ft6.begin(); it != ft6.end(); it++) {
        std::cout << std::setw(14);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }

    std::cout << std::endl;
    
    std::cout << colors::bold << colors::bright_yellow << "insert(iterator hint, const value_type& value)" << colors::reset << std::endl;
    std::cout << "Adding 'Nefle' key to ft4 container using hint" << std::endl;
    ft::map<std::string, std::string>::iterator hint = ft6.begin();
    for (int i = 0; i < 5; i++)
        hint++;
    std::cout << "hint: " << hint->first << " -> " << hint->second << std::endl;
    ft::map<std::string, std::string>::iterator it_nefle = ft4.insert(hint, ft::make_pair("Nefle", "Marron"));
    std::cout << "Return value of insert(hint, make_pair(Nefle, Marron): " << it_nefle->first << " -> " << it_nefle->second << std::endl;
    std::cout << std::endl;
    std::cout << "Printing ft4 map contents:" << std::endl;
    for (ft::map<std::string, std::string>::iterator it = ft4.begin(); it != ft4.end(); it++) {
        std::cout << std::setw(14);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }
    //SHOW_TREE
    //ft4._data.print2D();

    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ erase() ]" << colors::reset << std::endl;
    std::cout << colors::bold << colors::bright_yellow << "erase(const Key& key)" << colors::reset << std::endl;
    std::cout << "Erasing Baie de Goji key (delete node with 2 children)" << std::endl;
    ft4.erase("Baie de Goji");
    std::cout << "Printing ft4 map contents:" << std::endl;
    for (ft::map<std::string, std::string>::iterator it = ft4.begin(); it != ft4.end(); it++) {
        std::cout << std::setw(14);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }
    //SHOW_TREE
    //ft4._data.print2D();
    
    std::cout << std::endl;
    std::cout << "Erasing Avocat key (delete node with 1 child - left)" << std::endl;
    ft4.erase("Avocat");
    std::cout << "Printing ft4 map contents:" << std::endl;
    for (ft::map<std::string, std::string>::iterator it = ft4.begin(); it != ft4.end(); it++) {
        std::cout << std::setw(14);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }
    //SHOW_TREE
    //ft4._data.print2D();


    std::cout << std::endl;
    std::cout << "Erasing Ananas (delete node with no child)" << std::endl;
    ft4.erase("Ananas");
    std::cout << "Printing ft4 map contents:" << std::endl;
    for (ft::map<std::string, std::string>::iterator it = ft4.begin(); it != ft4.end(); it++) {
        std::cout << std::setw(14);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }
    //SHOW_TREE
    //ft4._data.print2D();
    
    std::cout << std::endl;
    std::cout << "Erasing Bergamote (delete node with 1 child - right)" << std::endl;
    ft4.erase("Bergamote");
    std::cout << "Printing ft4 map contents:" << std::endl;
    for (ft::map<std::string, std::string>::iterator it = ft4.begin(); it != ft4.end(); it++) {
        std::cout << std::setw(14);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }
    //SHOW_TREE 
    //ft4._data.print2D();
    
    std::cout << std::endl;
    std::cout << "Erasing Peche (nonexistant)" << std::endl;
    ft4.erase("Peche");
    std::cout << "Printing ft4 map contents:" << std::endl;
    for (ft::map<std::string, std::string>::iterator it = ft4.begin(); it != ft4.end(); it++) {
        std::cout << std::setw(14);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }
    //SHOW_TREE 
    //ft4._data.print2D();
    
    std::cout << std::endl;
    std::cout << colors::bold << colors::bright_yellow << "erase(iterator pos)" << colors::reset << std::endl;
    ft::map<std::string, std::string>::iterator erase_it = ft4.begin();
    for (int i = 0; i < 3; i++)
        erase_it++;    
    std::cout << "Erasing Papaye key via iterator" << std::endl;
    std::cout << "Printing ft4 map contents:" << std::endl;
    ft4.erase(erase_it);
    for (ft::map<std::string, std::string>::iterator it = ft4.begin(); it != ft4.end(); it++) {
        std::cout << std::setw(14);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }
    //SHOW_TREE 
    //ft4._data.print2D();

    std::cout << std::endl;
    std::cout << colors::bold << colors::bright_yellow << "erase(iterator first, iterator second)" << colors::reset << std::endl;
    ft::map<char, int>              ft7;
    ft::map<char, int>::iterator    it_erase;
    ft::map<char, int>::iterator    it_erase2;

    ft7['a'] = 10;
    ft7['b'] = 20;
    ft7['c'] = 30;
    ft7['d'] = 40;
    ft7['e'] = 50;
    ft7['f'] = 60;

    std::cout << "Created a map ft7 with following contents:" << std::endl;
    for (ft::map<char, int>::iterator it = ft7.begin(); it != ft7.end(); it++) {
        std::cout << std::setw(14);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Erasing keys b to e using iterators" << std::endl;
    it_erase = ft7.find('b');
    it_erase2 = ft7.find('e');
    
    ft7.erase( it_erase, it_erase2 );
    std::cout << "New content:" << std::endl;
    for (ft::map<char, int>::iterator it = ft7.begin(); it != ft7.end(); it++) {
        std::cout << std::setw(14);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }
    std::cout << "Size after erasing: " << ft7.size() << std::endl;

    std::cout << std::endl;
    std::cout << "Erasing everything left with begin() and end()" << std::endl;
    ft7.erase( ft7.begin(), ft7.end() );
    std::cout << "New content:" << std::endl;
    for (ft::map<char, int>::iterator it = ft7.begin(); it != ft7.end(); it++) {
        std::cout << std::setw(14);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }
    !ft7.size() ? std::cout << "(empty)" << std::endl : std::cout << "(not empty)" << std::endl;
    
    std::cout << std::endl;
    
    std::cout << colors::bold << colors::bright_blue << "[ swap() ]" << colors::reset << std::endl;

    std::cout << "Creating 2 containers with different contents" << std::endl;
    ft::map<std::string, std::string>   fbPlayerHeights;
    ft::map<std::string, std::string>   fbPlayerWeights;
    fbPlayerHeights.insert( ft::make_pair("Van Dijk", "1m93") );
    fbPlayerHeights.insert( ft::make_pair("Salah", "1m75") );
    fbPlayerHeights.insert( ft::make_pair("Mane", "1m75") );
    fbPlayerHeights.insert( ft::make_pair("Firmino", "1m80") );

    fbPlayerWeights.insert( ft::make_pair("Nunez", "78 kg") );
    fbPlayerWeights.insert( ft::make_pair("Keita", "63 kg") );
    fbPlayerWeights.insert( ft::make_pair("Robertson", "63 kg") );
    fbPlayerWeights.insert( ft::make_pair("Alisson", "91 kg") );

    std::cout << "fbPlayerHeights: " << std::endl;
    for (ft::map<std::string, std::string>::iterator it = fbPlayerHeights.begin(); it != fbPlayerHeights.end(); it++) {
        std::cout << std::setw(14);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }

    std::cout << std::endl;

    std::cout << "fbPlayerWeights: " << std::endl;
    for (ft::map<std::string, std::string>::iterator it = fbPlayerWeights.begin(); it != fbPlayerWeights.end(); it++) {
        std::cout << std::setw(14);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Using swap()" << std::endl;
    fbPlayerHeights.swap(fbPlayerWeights);
    std::cout << "Done" << std::endl << std::endl;

    std::cout << "fbPlayerHeights: " << std::endl;
    for (ft::map<std::string, std::string>::iterator it = fbPlayerHeights.begin(); it != fbPlayerHeights.end(); it++) {
        std::cout << std::setw(14);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }
    
    std::cout << std::endl;

    std::cout << "fbPlayerWeights: " << std::endl;
    for (ft::map<std::string, std::string>::iterator it = fbPlayerWeights.begin(); it != fbPlayerWeights.end(); it++) {
        std::cout << std::setw(14);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }

    std::cout << std::endl;

    std::cout << "O========================================O" << std::endl;
    std::cout << "|                 LOOKUP                 |" << std::endl;
    std::cout << "O========================================O" << std::endl << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ count() ]" << colors::reset << std::endl;
    std::cout << "Counting nb of 'Peche' key in ft4 container: " << ft4.count("Peche") << std::endl;
    std::cout << "Counting nb of 'Banane' key in ft4 container: " << ft4.count("Banane") << std::endl;
    std::cout << "Calling count on empty container ft7: " << ft7.count('a') << std::endl;

    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ find() ]" << colors::reset << std::endl;
    std::cout << colors::bold << colors::bright_yellow << "find(const Key& key)" << colors::reset << std::endl;
    ft::map<std::string, std::string>::iterator f1 = ft4.find("Peche");
    ft::map<std::string, std::string>::iterator f2 = ft4.find("Banane");
    ft::map<char, int>::iterator                f3 = ft7.find('a');

    std::cout << "Searching for 'Peche' key in ft4: ";
    f1 != ft4.end() ? std::cout << f1->first << " -> " << f1->second << std::endl : std::cout << "No match found" << std::endl;
    std::cout << "Searching for 'Banane' key in ft4: ";
    f2 != ft4.end() ? std::cout << f2->first << " -> " << f2->second << std::endl : std::cout << "No match found" << std::endl;
    std::cout << "Searching for 'a' key in empty container ft7: ";
    f3 != ft7.end() ? std::cout << f3->first << " -> " << f3->second << std::endl : std::cout << "No match found" << std::endl;

    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_yellow << "find(const Key& key) const" << colors::reset << std::endl;
    ft::map<std::string, std::string>::const_iterator f5 = ft4.find("Peche");
    ft::map<std::string, std::string>::const_iterator f6 = ft4.find("Banane");
    ft::map<char, int>::const_iterator                f7 = ft7.find('a');

    std::cout << "Searching for 'Peche' key in ft4: ";
    f5 != ft4.end() ? std::cout << f5->first << " -> " << f5->second << std::endl : std::cout << "No match found" << std::endl;
    std::cout << "Searching for 'Banane' key in ft4: ";
    f6 != ft4.end() ? std::cout << f6->first << " -> " << f6->second << std::endl : std::cout << "No match found" << std::endl;
    std::cout << "Searching for 'a' key in empty container ft7: ";
    f7 != ft7.end() ? std::cout << f7->first << " -> " << f7->second << std::endl : std::cout << "No match found" << std::endl;

    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ equal_range() ]" << colors::reset << std::endl;
    std::cout << colors::bold << colors::bright_yellow << "equal_range(const Key& key)" << colors::reset << std::endl;
    ft::map<char, int>  eqrange;
    eqrange['a'] = 10;
    eqrange['b'] = 20;
    eqrange['c'] = 30;

    ft::pair< ft::map<char, int>::iterator, ft::map<char, int>::iterator >  ret;
    ret = eqrange.equal_range('b');

    std::cout << "lower bound points to: ";
    std::cout << ret.first->first << " -> " << ret.first->second << std::endl;

    std::cout << "upper bound points to: ";
    std::cout << ret.second->first << " -> " << ret.second->second << std::endl;

    std::cout << std::endl;
    std::cout << colors::bold << colors::bright_yellow << "equal_range(const Key& key) const" << colors::reset << std::endl;
    ft::pair< ft::map<char, int>::const_iterator, ft::map<char, int>::const_iterator >  ret2;
    ret2 = eqrange.equal_range('b');
    std::cout << "lower bound points to: ";
    std::cout << ret2.first->first << " -> " << ret2.first->second << std::endl;

    std::cout << "upper bound points to: ";
    std::cout << ret2.second->first << " -> " << ret2.second->second << std::endl;

    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_blue << "[ lower_bound() | upper_bound() ]" << colors::reset << std::endl;
    std::cout << colors::bold << colors::bright_yellow << "lower_bound(const Key& key) | upper_bound(const Key& key)" << colors::reset << std::endl;
    eqrange['d'] = 40;
    eqrange['e'] = 50;

    std::cout << "Printing eqrange content: " << std::endl;
    for (ft::map<char, int>::iterator it = eqrange.begin(); it != eqrange.end(); it++) {
        std::cout << std::setw(14);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Erasing all elements in range: lower_bound('b') (points to 'b' key) to upper_bound('d') (points to 'e' key)" << std::endl;
    ft::map<char, int>::iterator    itlow, itup;
    itlow = eqrange.lower_bound('b');
    itup = eqrange.upper_bound('d');
    eqrange.erase(itlow, itup);
    std::cout << "Printing eqrange content: " << std::endl;
    for (ft::map<char, int>::iterator it = eqrange.begin(); it != eqrange.end(); it++) {
        std::cout << std::setw(14);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }

    std::cout << std::endl;

    std::cout << colors::bold << colors::bright_yellow << "lower_bound(const Key& key) const | upper_bound(const Key& key) const" << colors::reset << std::endl;
    ft::map<char, int>  eqrange2;
    eqrange2['a'] = 10;
    eqrange2['b'] = 20;
    eqrange2['c'] = 30;
    eqrange2['d'] = 40;
    eqrange2['e'] = 50;
    std::cout << "Printing eqrange2 content: " << std::endl;
    for (ft::map<char, int>::iterator it = eqrange2.begin(); it != eqrange2.end(); it++) {
        std::cout << std::setw(14);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }
    std::cout << std::endl;
    ft::map<char, int>::const_iterator    itlow2, itup2;
    itlow2 = eqrange2.lower_bound('b');
    itup2 = eqrange2.upper_bound('d');
    std::cout << "Printing only elements between lower_bound and upper_bound (can't erase since no suitable overload): " << std::endl;
    for (ft::map<char, int>::const_iterator it = itlow2; it != itup2; it++) {
        std::cout << std::setw(14);
        std::cout << it->first;
        std::cout << " -> " << it->second << std::endl;
    }

    std::cout << std::endl;
    
    std::cout << "O========================================O" << std::endl;
    std::cout << "|            PERFORMANCE TESTS           |" << std::endl;
    std::cout << "O========================================O" << std::endl << std::endl;

    ft::map<int, int>  perf;

    std::cout << "For performance we will add 1M elements to container, search for highest and lowest value";
    std::cout << " then deleting these 1M elements" << std::endl;
    std::cout << std::endl;
    std::cout << "1/ Adding 1M elements" << std::endl;
    for (int i = 0; i < 1000000; i++)
        perf.insert( ft::make_pair(i, i) );
    std::cout << "2/ Searching for lowest value (0): ";
    ft::map<int, int>::iterator    itp = perf.find(0);
    itp != perf.end() ? std::cout << "Found" << std::endl : std::cout << "Not found" << std::endl;
    std::cout << "3/ Searching for highest value (999999): ";
    itp = perf.find(999999);
    itp != perf.end() ? std::cout << "Found" << std::endl : std::cout << "Not found" << std::endl;
    std::cout << "4/ Deleting all 1M elements" << std::endl;
    for (int i = 0; i < 1000000; i++)
        perf.erase(i);
    
    std::cout << std::endl;

    std::cout << colors::bright_green << "END OF TESTS :)" << colors::reset << std::endl;

}