#include "Config.h"

Config* Config::instance = new Config;

Config * Config::Getinstance() {
   return instance;
}

Config::Config() {
    FILE * fin=fopen("config.ini", "r");
    
    if (fin == NULL) {
        perror("config.ini not found, exiting...\n");
        exit(1);
    }

    char ts1[1000],ts2[1000];
    config.clear();
    while (fscanf(fin,"%s = %s",ts1,ts2)!=EOF) {
        config[ts1]=ts2;
    }
    
    database_ip = config["database_ip"];
    database_port = atoi(config["database_port"].c_str());
    database_user = config["database_user"];
    database_password = config["database_password"];
    database_table = config["database_table"];
    judger_string = config["judge_connect_string"];
    submit_string = config["submit_string"];
    rejudge_string = config["rejudge_string"];
    error_rejudge_string = config["error_rejudge_string"];
    challenge_string = config["challenge_string"];
    pretest_string = config["pretest_string"];
    testall_string = config["test_all_string"];
    log_file_prefix = config["log_file_prefix"];
    port_listen = atoi(config["port_listen"].c_str());

    fclose(fin);
    //ctor
}

Config::~Config() {
    //dtor
}
