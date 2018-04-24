#ifndef HANDRECOGNIZER_WORKERPLEX_H
#define HANDRECOGNIZER_WORKERPLEX_H

#include <iostream>
#include <vector>
#include <map>
#include <boost/thread/thread.hpp>
#include "workers/Worker.hpp"

using namespace std;

class Workerplex {
public:
    bool addWorker(Worker *worker);

    void startPrompt();

    bool runCommand(const string &cmd);

    int getRunningCount(const string &cmd);

    virtual ~Workerplex();

private:
    static const string PROMPT;

    bool started = false;
    map<string, Worker*> workers;
    map<string, vector<boost::thread*>> workerThreadSets; // <cmd, vector<thread*>>

    void startWorker(Worker *worker);

};


#endif //HANDRECOGNIZER_WORKERPLEX_H
