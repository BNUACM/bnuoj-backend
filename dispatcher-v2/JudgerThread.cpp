/* 
 * File:   JudgerThread.cpp
 * Author: 51isoft
 * 
 * Created on 2014年1月13日, 下午10:10
 */

#include "JudgerThread.h"
#include "Bott.h"

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

/**
 * Load infos for a regular run, and store it to a bott file
 * @param bott  The bott file we store infos to
 * @param runid Regular runid
 */
void JudgerThread::prepareBottForRun(Bott * bott, string runid) {
    // load basic info from status table
    map<string, string> info = db->Getall_results("\
            SELECT status.source AS source, \
                   status.runid AS runid, \
                   status.language AS language, \
                   status.pid AS pid, \
                   problem.ignore_noc AS ignore_noc \
            FROM status, problem \
            WHERE status.pid = problem.pid AND runid = '" + runid + "' \
    ")[0];

    bott->Setsrc(info["source"]);
    bott->Setrunid(info["runid"]);
    bott->Setlanguage(info["language"]);
    bott->Setpid(info["pid"]);
    
    // DO_TESTALL will ignore time_limit and just use case_limit
    // NEED_JUDGE will set the time_limit together with case_limit
    // a little bit hacky though
    if (info["ignore_noc"] == "1") {
        bott->Settype(DO_TESTALL);
    } else {
        bott->Settype(NEED_JUDGE);
    }
    
    // load additional info from problem table
    info = db->Getall_results("\
            SELECT number_of_testcase, time_limit, case_time_limit, memory_limit, special_judge_status, vname, vid \
            FROM   problem \
            WHERE  pid = '" + info["pid"] + "' \
    ")[0];
    
    bott->Setnumber_of_testcases(info["number_of_testcase"]);
    bott->Settime_limit(info["time_limit"]);
    bott->Setcase_limit(info["case_time_limit"]);
    bott->Setmemory_limit(info["memory_limit"]);
    bott->Setspj(info["special_judge_status"]);
    bott->Setvname(info["vname"]);
    bott->Setvid(info["vid"]);
    
    bott->save();
}

/**
 * Main loop of the judger handler
 */
void JudgerThread::run() {
    while (true) {
        usleep(50000); // sleep 50ms
        if (current_submit) {
            // got a new judge task
            if ( current_submit->Gettype() == NEED_JUDGE ||
                 current_submit->Gettype() == DO_PRETEST ||
                 current_submit->Gettype() == DO_TESTALL ) {
                // A regular run
                LOG("Load infos of Runid: " + current_submit->Getid());
                string filename = Bott::RAW_FILES_DIRECTORY + current_submit->Getid() + Bott::EXTENTION;
                Bott * bott = new Bott(filename);
                prepareBottForRun(bott, current_submit->Getid());
                
            }
            else if ( current_submit->Gettype() == DO_CHALLENGE ) {
                // A challenge
            }
        }
    }
}
