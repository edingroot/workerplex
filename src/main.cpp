#include "workerplex/Workerplex.hpp"
#include "workerplex/workers/pingpong/PingPong.hpp"
#include "workerplex/workers/longtask/LongTask.hpp"

using namespace std;

int main() {
    Workerplex workerplex;
    workerplex.addWorker(new PingPong());
    workerplex.addWorker(new LongTask());
    workerplex.startPrompt();

    return 0;
}
