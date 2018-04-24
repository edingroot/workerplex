#ifndef HANDRECOGNIZER_PINGPONG_HPP
#define HANDRECOGNIZER_PINGPONG_HPP

#include <iostream>
#include "Worker.hpp"

using namespace std;

class PingPong : public Worker {
public:
    static const string IDENTIFIER;

    string getIdentifier() override;

    void run() override;

};


#endif //HANDRECOGNIZER_PINGPONG_HPP
