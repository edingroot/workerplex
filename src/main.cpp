#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "workerplex/Workerplex.hpp"
#include "workerplex/workers/PingPong.hpp"

using namespace std;

int main() {
    Workerplex workerplex;
    workerplex.addWorker(new PingPong());
    workerplex.startPrompt();

    return 0;
}
