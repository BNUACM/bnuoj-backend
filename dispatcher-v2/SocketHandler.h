/* 
 * File:   SocketHandler.h
 * Author: 51isoft
 *
 * Created on 2014年1月13日, 下午10:06
 */

#ifndef SOCKETHANDLER_H
#define	SOCKETHANDLER_H

#include "dispatcher.h"

class SocketHandler {
public:
    SocketHandler(int _sockfd) : sockfd(_sockfd) {}
    string getConnectionMessage();
    virtual ~SocketHandler();
private:
    int sockfd;
};

#endif	/* SOCKETHANDLER_H */

