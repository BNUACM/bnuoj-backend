/* 
 * File:   Bott.cpp
 * Author: 51isoft
 * 
 * Created on 2014年1月19日, 上午1:04
 */

#include "Bott.h"

Bott::Bott() {
    //ctor
}

Bott::~Bott() {
    //dtor
}

string Bott::parseUntil(string end) {
    string res = "", tmps;
    getline(fin, tmps);
    getline(fin, tmps);
    while (tmps != end) {
        res += tmps + "\n";
        getline(fin, tmps);
    }
    return res;
}

Bott::Bott(string filename) {
    string name, value;
    infos.clear();
    fin.open(filename.c_str(), fstream::in);
    while (fin >> name) {
        if (name == "__SOURCE-CODE-BEGIN-LABLE__") src = parseUntil("__SOURCE-CODE-END-LABLE__");
        else if (name == "__COMPILE-INFO-BEGIN-LABLE__") ce_info = parseUntil("__COMPILE-INFO-END-LABLE__");
        else if (name == "__DATA-DETAIL-BEGIN-LABLE__") data_detail = parseUntil("__DATA-DETAIL-END-LABLE__");
        else if (name == "__CHALLENGE-DETAIL-BEGIN-LABLE__") cha_detail = parseUntil("__CHALLENGE-DETAIL-END-LABLE__");
        else {
            getline(fin, value);
            infos[name] = value;
        }
    }
    fin.close();
    if (infos.count("<type>")) type = stringToInt(infos["<type>"]);
    if (infos.count("<runid>")) runid = stringToInt(infos["<runid>"]);
    if (infos.count("<cha_id>")) cha_id = stringToInt(infos["<cha_id>"]);
    if (infos.count("<language>")) language = stringToInt(infos["<language>"]);
    if (infos.count("<pid>")) pid = stringToInt(infos["<pid>"]);
    if (infos.count("<testcases>")) number_of_testcases = stringToInt(infos["<testcases>"]);
    if (infos.count("<time_limit>")) time_limit = stringToInt(infos["<time_limit>"]);
    if (infos.count("<case_limit>")) case_limit = stringToInt(infos["<case_limit>"]);
    if (infos.count("<memory_limit>")) memory_limit = stringToInt(infos["<memory_limit>"]);
    if (infos.count("<special>")) spj = stringToInt(infos["<special>"]);
    if (infos.count("<vname>")) vname = infos["<vname>"];
    if (infos.count("<vid>")) vid = infos["<vid>"];
    if (infos.count("<memory_used>")) memory_used = stringToInt(infos["<memory_used>"]);
    if (infos.count("<time_used>")) memory_used = stringToInt(infos["<time_used>"]);
    if (infos.count("<result>")) result = infos["<result>"];
    if (infos.count("<data_type>")) data_type = stringToInt(infos["<data_type>"]);
    if (infos.count("<data_lang>")) data_lang = stringToInt(infos["<data_lang>"]);
    if (infos.count("<challenge_result>")) cha_result = infos["<challenge_result>"];
}

void Bott::toFile() {
    memory_used /= 1024;
    FILE *fp = fopen(out_filename.c_str(), "w");
    if (type == CHALLENGE_REPORT) {
        fprintf(fp, "<type> %d\n<cha_id> %d\n<cha_result> %s\n", CHALLENGE_REPORT, cha_id, cha_result.c_str());
        fprintf(fp, "__CHALLENGE-DETAIL-BEGIN-LABLE__\n");
        fprintf(fp, "%s\n", cha_detail.c_str());
        fprintf(fp, "__CHALLENGE-DETAIL-END-LABLE__\n");
    } else if (type == RESULT_REPORT) {
        fprintf(fp, "<type> %d\n<runid> %d\n<memory_used> %d\n<time_used> %d\n<result> %s\n", RESULT_REPORT, runid, memory_used, time_used, result.c_str());
        fprintf(fp, "__COMPILE-INFO-BEGIN-LABLE__\n");
        fprintf(fp, "%s\n", ce_info.c_str());
        fprintf(fp, "__COMPILE-INFO-END-LABLE__\n");
    }
    fclose(fp);
}
