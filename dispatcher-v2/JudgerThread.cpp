/* 
 * File:   JudgerThread.cpp
 * Author: 51isoft
 * 
 * Created on 2014年1月13日, 下午10:10
 */

#include "JudgerThread.h"

/**
 * Initialize a judger handler
 * @param _socket       The client sockfd
 * @param oj            OJ name
 */
JudgerThread::JudgerThread(SocketHandler * _socket, string _oj) {
    db = new DatabaseHandler();
    oj = _oj;
    socket = _socket;
    current_submit = NULL;
}

JudgerThread::~JudgerThread() {
    delete db;
    delete socket;
    if (current_submit) delete current_submit;
}

void JudgerThread::run() {
    while (true) {
        usleep(50000); // sleep 50ms
        if (current_submit) {
            
        }
    }
}
