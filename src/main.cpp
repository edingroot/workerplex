#include <iostream>
#include "workerplex/Workerplex.hpp"
#include "workers/pingpong/PingPong.hpp"
#include "workers/longtask/LongTask.hpp"

using namespace std;

int main() {
    Workerplex workerplex;
    workerplex.addWorker(new PingPong());
    workerplex.addWorker(new LongTask());

    cout << "Starting prompt." << endl;
    workerplex.startPrompt(false);

    return 0;
}
