/* 
 * File:   DatabaseHandler.cpp
 * Author: 51isoft
 * 
 * Created on 2014年1月12日, 下午11:21
 */

#include "DatabaseHandler.h"

DatabaseHandler::DatabaseHandler() {
    mysql = new MYSQL;
    mysql_init(mysql);
    mysql_options(mysql, MYSQL_SET_CHARSET_NAME, "utf8");
    if (!mysql_real_connect(mysql,
            CONFIG->Getdatabase_ip().c_str(),
            CONFIG->Getdatabase_user().c_str(),
            CONFIG->Getdatabase_password().c_str(),
            CONFIG->Getdatabase_table().c_str(),
            CONFIG->Getdatabase_port(),
            NULL,
            0)) {
        throw Exception("Cannot connect to DB");
    }
}

DatabaseHandler::~DatabaseHandler() {
    mysql_close(mysql);
    delete mysql;
}

/**
 * Get all results of a query, formatted in both numeric (using string) and key
 * @param query The SQL to be executed
 * @return      The results
 */
vector <map<string, string> > DatabaseHandler::Getall_results(string query) {
    mysql_ping(mysql);
    mysql_query(mysql, query.c_str());
    MYSQL_RES * res = mysql_use_result(mysql);
    
    // init field names
    MYSQL_FIELD *field;
    vector <string> fields;
    while((field = mysql_fetch_field(res))) {
        fields.push_back(field->name);
    }
    
    // fetch all rows
    MYSQL_ROW row;
    vector <map<string, string> > result;
    while ((row = mysql_fetch_row(res))) {
        map<string, string> tmp;
        tmp.clear();
        for (int i = 0; i < fields.size(); ++i) {
            tmp[fields[i]] = row[i];
            tmp[intToString(i)] = row[i];
        }
        result.push_back(tmp);
    }
    
    mysql_free_result(res);
    
    return result;
}

/**
 * Do a DB query
 * @param query SQL query string
 */
void DatabaseHandler::query(string query) {
    mysql_ping(mysql);
    mysql_query(mysql, query.c_str());
}

/**
 * Do mysql_real_escape on the string
 * @param str   Original string
 * @return Escaped string
 */
string DatabaseHandler::escape(string str) {
    char * res = new char[str.length() * 2 + 1];
    mysql_real_escape_string(mysql, res, str.c_str(), str.length());
    return res;
}