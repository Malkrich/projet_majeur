// std
#include <iostream>
#include <list>
#include <vector>

// extern
#include "caractere.hpp"
#include "utility.hpp"

int main()
{
    std::list<alphabet*> phrase;
    phrase.assign(3, new A);

    display_string(phrase);

    return 0;
}