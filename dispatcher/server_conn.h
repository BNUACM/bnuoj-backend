#ifndef SERVER_CONN_H_INCLUDED
#define SERVER_CONN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <errno.h>
#include <netdb.h>
#include <pthread.h>
#include <mysql/mysql.h>
#include <string>
#include <map>

using namespace std;

#define MAX_JUDGER_NUMBER 255
#define MAX_DATA_SIZE 855350
#define CHECK_STATUS 1
#define NEED_JUDGE 2
#define SEND_DATA 3
#define DO_CHALLENGE 4
#define DO_PRETEST 5
#define DO_TESTALL 6
#define JUDGER_STATUS_REPORT 1
#define NEED_DATA 2
#define RESULT_REPORT 3
#define CHALLENGE_REPORT 4
#define CPPLANG 1
#define CLANG 2
#define JAVALANG 3
#define FPASLANG 4

// char db_ip[50]={0};
// char db_user[50]={0};
// char db_pass[50]={0};
// char db_table[50]={0};
// char judger_string[100]={0};
// char submit_string[100]={0};
// char rejudge_string[100]={0};
// char error_string[100]={0};
// char challenge_string[100]={0};
// char pretest_string[100]={0};
// char testall_string[100]={0};
// char logfile[100]={0};
// int server_port;

map <string, string> config;

#endif // SERVER_CONN_H_INCLUDED
