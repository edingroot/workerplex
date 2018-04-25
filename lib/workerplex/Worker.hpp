#ifndef HANDRECOGNIZER_WORKER_HPP
#define HANDRECOGNIZER_WORKER_HPP

#include <string>

using namespace std;

class Worker {
public:
    virtual string getIdentifier() = 0;

    virtual void run(const vector<string> &args) = 0;

    // Required to allow inheritance
    virtual ~Worker() = default;

};

#endif //HANDRECOGNIZER_WORKER_HPP
