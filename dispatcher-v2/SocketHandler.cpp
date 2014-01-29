/* 
 * File:   SocketHandler.cpp
 * Author: 51isoft
 * 
 * Created on 2014年1月13日, 下午10:06
 */

#include "SocketHandler.h"

SocketHandler::~SocketHandler() {
    close(sockfd);
}

/**
 * Get connection message to identify the socket
 * @return The connection message, within HANDSHAKE_TIMEOUT
 */
string SocketHandler::getConnectionMessage() {
    
    struct timeval case_startv,case_nowv;
    struct timezone case_startz,case_nowz;
    gettimeofday(&case_startv,&case_startz);
    
    int time_passed;
    char buffer[255];
    while (1) {
        usleep(10000);
        gettimeofday(&case_nowv,&case_nowz);
        time_passed=(case_nowv.tv_sec-case_startv.tv_sec)*1000+(case_nowv.tv_usec-case_startv.tv_usec)/1000;
        if (recv(sockfd, buffer, 255, MSG_DONTWAIT) > 0 || time_passed > HANDSHAKE_TIMEOUT) break;
    }
    
    return buffer;
}