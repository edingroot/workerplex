#include "PingPong.hpp"

const string PingPong::IDENTIFIER = "ping";

string PingPong::getIdentifier() {
    return IDENTIFIER;
}

void PingPong::run() {
    cout << "pong" << endl;
}
