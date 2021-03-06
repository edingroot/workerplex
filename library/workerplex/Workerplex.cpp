#include "Workerplex.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <sstream>
#include "Exceptions.hpp"

const string Workerplex::PROMPT = "> ";

bool Workerplex::addWorker(Worker *worker) {
    if (started)
        return false;

    workers[worker->getIdentifier()] = worker;
    return true;
}

void Workerplex::startPrompt(bool async) {
    started = true;

    string line;
    cout << PROMPT;
    while (getline(std::cin, line)) {
        string cmd, token;
        vector<string> tokens, args;
        istringstream iss(line);

        while (iss >> quoted(token)) {
            tokens.emplace_back(token);
        }

        cmd = tokens[0];
        if (tokens.size() > 1) {
            args = vector<string>(tokens.begin() + 1, tokens.end());
        }

        if (cmd == "quit") {
            break;

        } else if (cmd == "_help") {
            cout << "Configured commands: ";
            for (auto &command : getCommands())
                cout << command << " ";
            cout << endl;

        } else if (cmd == "_active" && args.size() == 1) {
            cout << "getActiveCount("<< args[0] << "): "
                 << getActiveCount(args[0]) << endl;

        } else {
            try {
                if (async) {
                    runCommand(cmd, args);
                } else {
                    string response = runCommandSync(cmd, args);
                    cout << "--------------- cmd sync response ---------------" << endl;
                    cout << response;
                    cout << "-------------------------------------------------" << endl;
                }
            } catch (command_not_found &e) {
                cout << e.what() << endl;
            }
        }

        boost::this_thread::sleep(boost::posix_time::millisec(5));
        cout << PROMPT;
    }
}

void Workerplex::runCommand(const string &cmd, const vector<string> &args) {
    started = true;

    if (workers.count(cmd) == 0)
        throw command_not_found("Unknown command: " + cmd);

    startWorkerAsync(workers[cmd], args);
}

string Workerplex::runCommandSync(const string &cmd, const vector<string> &args) {
    started = true;

    if (workers.count(cmd) == 0)
        throw command_not_found("Unknown command: " + cmd);

    return workers[cmd]->run(args);
}

void Workerplex::startWorkerAsync(Worker *worker, const vector<string> &args) {
    string cmd = worker->getIdentifier();

    // Check if key not exists
    if (workerThreadSets.count(cmd) == 0) {
        workerThreadSets[cmd] = vector<boost::thread*>();
    }

    boost::thread *workerThread = new boost::thread([&, worker, args]() {
        worker->run(args);
    });

    workerThreadSets[cmd].emplace_back(workerThread);
}

vector<string> Workerplex::getCommands() const {
    vector<string> commands;

    for (auto &workerPair : workers) {
        commands.emplace_back(workerPair.first);
    }

    return commands;
}

int Workerplex::getActiveCount(const string &cmd) {
    int count = 0;

    if (workerThreadSets.count(cmd) != 0) {
        auto i = workerThreadSets[cmd].begin();

        while (i != workerThreadSets[cmd].end()) {
            auto workerThread = *i;

            // Check if workerThread exists and is active,
            // remove thread* entry if it has finished
            if (workerThread) {
                if (!workerThread->timed_join(boost::posix_time::millisec(0))) {
                    count++;
                    i++;
                } else {
                    delete workerThread;
                    workerThreadSets[cmd].erase(i);
                }
            } else {
                workerThreadSets[cmd].erase(i);
            }
        }
    }

    return count;
}

Workerplex::~Workerplex() {
    for (auto &workerPair : workers) {
        Worker *worker = workerPair.second;
        delete worker;
    }

    for (auto &workerIdThread : workerThreadSets) {
        for (auto &thread : workerIdThread.second) {
            if (thread) {
                thread->join();
                delete thread;
            }
        }
    }
}
