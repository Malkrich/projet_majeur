#include "utility.hpp"

void display_string(std::list<alphabet*>& l)
{
    for(auto it = l.begin(); it != l.end(); it++)
    {
        std::cout << (*it)->get_char();
    }
    std::cout << std::endl;
}