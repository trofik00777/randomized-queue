#include "randomized_queue.h"
#include "subset.h"

#include <cstdlib>
#include <iostream>

int main()
{
    randomized_queue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    queue.enqueue(5);
    auto w = queue.end();
    auto s = *w;
    s++;
    for (const auto & x : queue) {
        std::cout << x << " ";
    }
    std::cout << "\n";
    for (const auto & x : queue) {
        std::cout << x << " ";
    }

    //    if (argc != 2) {
    //        std::cerr << "Usage: " << argv[0] << " <number of random strings printed>" << std::endl;
    //        return -1;
    //    }
    //    char * end;
    //    unsigned long k = std::strtoul(argv[1], &end, 10);
    //    if (*end != '\0') {
    //        std::cerr << "Incorrect number of strings to be printed\nUsage: " << argv[0] << " <number of random strings printed>" << std::endl;
    //        return -1;
    //    }
    //    subset(k, std::cin, std::cout);
}
