/* 
 * File:   JudgerThread.h
 * Author: 51isoft
 *
 * Created on 2014年1月13日, 下午10:10
 */

#ifndef JUDGERTHREAD_H
#define	JUDGERTHREAD_H

#include "dispatcher.h"
#include "SocketHandler.h"
#include "DatabaseHandler.h"
#include "Submit.h"
#include "Bott.h"

class JudgerThread {
public:
    JudgerThread(SocketHandler *, string);
    virtual ~JudgerThread();
    void run();

    Submit* Getcurrent_submit() const {
        return current_submit;
    }

    void Setcurrent_submit(Submit* current_submit) {
        this->current_submit = current_submit;
    }

    string Getoj() const {
        return oj;
    }

    void Setoj(string oj) {
        this->oj = oj;
    }

private:
    DatabaseHandler * db;
    SocketHandler * socket;
    string oj;
    Submit * current_submit;
    
    void prepareBottForRun(Bott *, string);
    void prepareBottForChallenge(Bott *, string);
    void updateRunResult(string, string);
    void updateRunStatus(Bott *);
    void updateStatistics(string, string);
    void updateChallengeResult(string, string);
    void updateChallengeStatus(Bott *);
};

#endif	/* JUDGERTHREAD_H */

