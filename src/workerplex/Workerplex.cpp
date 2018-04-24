#include "Workerplex.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>

const string Workerplex::PROMPT = "> ";

bool Workerplex::addWorker(Worker *worker) {
    if (started)
        return false;

    workers[worker->getIdentifier()] = worker;
    return true;
}

void Workerplex::startPrompt() {
    started = true;

    string cmd;
    cout << PROMPT;
    while (cin >> cmd) {
        if (cmd == "quit")
            break;

        if (!runCommand(cmd))
            cout << "Unknown command: " << cmd << endl;

        boost::this_thread::sleep(boost::posix_time::millisec(5));
        cout << PROMPT;
    }
}

/**
 * @return false if command not found
 */
bool Workerplex::runCommand(const string &cmd) {
    started = true;

    if (workers.count(cmd) != 0) {
        startWorker(workers[cmd]);
        return true;
    } else {
        return false;
    }
}

void Workerplex::startWorker(Worker *worker) {
    string cmd = worker->getIdentifier();

    // Check if key not exists
    if (workerThreadSets.count(cmd) == 0) {
        workerThreadSets[cmd] = vector<boost::thread*>();
    }

    boost::thread *workerThread = new boost::thread([&, worker]() {
        worker->run();
    });

    workerThreadSets[cmd].emplace_back(workerThread);
}

int Workerplex::getRunningCount(const string &cmd) {
    int count = 0;

    if (workerThreadSets.count(cmd) != 0) {
        auto i = workerThreadSets[cmd].begin();
        while (i != workerThreadSets[cmd].end()) {
            auto workerThread = *i;

            // Check if workerThread exists and is running
            if (workerThread != nullptr && workerThread->timed_join(boost::posix_time::millisec(0))) {
                count++;
            } else {
                // Remove thread* entry if it has finished
                delete workerThread;
                workerThread = nullptr;
                workerThreadSets[cmd].erase(i);
                i++;
            }
        }
    }

    return count;
}

Workerplex::~Workerplex() {
    for (auto &workerPair : workers) {
        Worker *worker = workerPair.second;
        if (worker) {
            delete worker;
            worker = nullptr;
        }
    }

    for (auto &workerIdThread : workerThreadSets) {
        for (auto &thread : workerIdThread.second) {
            if (thread) {
                delete thread;
                thread = nullptr;
            }
        }
    }
}
