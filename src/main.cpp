// std
#include <iostream>
#include <list>

// extern
#include "caractere.hpp"
#include "phrase.hpp"

int main()
{
    Phrase p = Phrase({new A});

    std::cout << p << std::endl;

    int n = 3;

    for(int i = 0; i < n; i++)
    {
        p.phrase() = p.iteration();
    }

    std::cout << p << std::endl;

    return 0;
}