#include "subset.h"

#include "randomized_queue.h"

#include <string>

void subset(unsigned long k, std::istream & in, std::ostream & out)
{
    std::string line;
    randomized_queue<std::string> random_queue;
    while (std::getline(in, line)) {
        random_queue.enqueue(line);
    }
    for (auto i = k; i > 0 && !random_queue.empty(); --i) {
        out << random_queue.dequeue() << "\n";
    }
}
