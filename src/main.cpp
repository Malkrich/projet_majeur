// std
#include <iostream>
#include <list>

// extern
#include "caractere.hpp"
#include "phrase.hpp"

int main()
{
    Phrase p = Phrase({new A, new CrochetClose, new F});

    /* test iterations fonctionnel*/
    std::cout << p << std::endl;

    int n = 3;

    for(int i = 1; i < n; i++)
    {
        p.phrase() = p.iteration();
        std::cout << p << std::endl;
    }

    std::cout << "size phrase : " << p.size_phrase() << std::endl;

    return 0;
}