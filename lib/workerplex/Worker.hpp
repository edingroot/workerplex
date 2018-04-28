#ifndef WORKERPLEX_WORKER_HPP
#define WORKERPLEX_WORKER_HPP

#include <string>

using namespace std;

class Worker {
public:
    virtual string getIdentifier() = 0;

    virtual string run(const vector<string> &args) = 0;

    // Required to allow inheritance
    virtual ~Worker() = default;

};

#endif //WORKERPLEX_WORKER_HPP
