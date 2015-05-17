#include "Bott.h"
#include "Logger.h"
#include "chaclient.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

extern string tmpnam();

Bott::Bott() {
  //ctor
}

Bott::~Bott() {
  //dtor
}

int Bott::satoi(string str) {
  return atoi(str.c_str());
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
  Document document;
  document.Parse(loadAllFromFile(filename).c_str());
  if (document.HasMember("type")) {
    type = document["type"].GetInt();
  }
  if (document.HasMember("runid")) {
    runid = satoi(document["runid"].GetString());
  }
  if (document.HasMember("source")) {
    src = document["source"].GetString();
  }
  if (document.HasMember("compileInfo")) {
    ce_info = document["compileInfo"].GetString();
  }
  if (document.HasMember("language")) {
    language = satoi(document["language"].GetString());
  }
  if (document.HasMember("pid")) {
    pid = satoi(document["pid"].GetString());
  }
  if (document.HasMember("testcases")) {
    number_of_testcases = satoi(document["testcases"].GetString());
  }
  if (document.HasMember("timeLimit")) {
    time_limit = satoi(document["timeLimit"].GetString());
  }
  if (document.HasMember("caseLimit")) {
    case_limit = satoi(document["caseLimit"].GetString());
    if (case_limit == 0) {
      case_limit = time_limit;
    }
  }
  if (document.HasMember("memoryLimit")) {
    memory_limit = satoi(document["memoryLimit"].GetString());
  }
  if (document.HasMember("spjStatus")) {
    spj = satoi(document["spjStatus"].GetString());
  }
  if (document.HasMember("vname")) {
    vname = document["vname"].GetString();
  }
  if (document.HasMember("vid")) {
    vid = document["vid"].GetString();
  }
  if (document.HasMember("memoryUsed")) {
    memory_used = satoi(document["memoryUsed"].GetString());
  }
  if (document.HasMember("timeUsed")) {
    time_used = satoi(document["timeUsed"].GetString());
  }
  if (document.HasMember("result")) {
    result = document["result"].GetString();
  }
  if (document.HasMember("challenge")) {
    if (document["challenge"].HasMember("id")) {
      cha_id = satoi(document["challenge"]["id"].GetString());
    }
    if (document["challenge"].HasMember("dataType")) {
      data_type = satoi(document["challenge"]["dataType"].GetString());
    }
    if (document["challenge"].HasMember("dataLanguage")) {
      data_lang = satoi(document["challenge"]["dataLanguage"].GetString());
    }
    if (document["challenge"].HasMember("dataDetail")) {
      data_detail = document["challenge"]["dataDetail"].GetString();
    }
    if (document["challenge"].HasMember("detail")) {
      cha_detail = document["challenge"]["detail"].GetString();
    }
    if (document["challenge"].HasMember("result")) {
      cha_result = document["challenge"]["result"].GetString();
    }
  }
}

void Bott::addIntValue(Document & document, const char * name, int v) {
  Value value(v);
  document.AddMember(StringRef(name), value, document.GetAllocator());
}

void Bott::addStringValue(Document & document, const char * name, string v) {
  Value value(StringRef(v.c_str()));
  document.AddMember(StringRef(name), value, document.GetAllocator());
}

void Bott::addStringValueToRef(
    Document & document, Value & ref, const char * name, string v) {
  Value value(StringRef(v.c_str()));
  document.AddMember(StringRef(name), value, document.GetAllocator());
}

void Bott::toFile() {
  Document document;
  document.SetObject();
  addIntValue(document, "type", type);
  memory_used /= 1024;
  
  if (type == CHALLENGE_REPORT) {
    Value challenge;
    challenge.SetObject();
    addStringValueToRef(document, challenge, "id", intToString(cha_id));
    addStringValueToRef(document, challenge, "result", cha_result);
    addStringValueToRef(document, challenge, "detail", cha_detail);
    document.AddMember("challenge", challenge, document.GetAllocator());
  }
  if (type == RESULT_REPORT) {
    addStringValue(document, "runid", intToString(runid));
    addStringValue(document, "memoryUsed", intToString(memory_used));
    addStringValue(document, "timeUsed", intToString(time_used));
    addStringValue(document, "result", result);
    addStringValue(document, "compileInfo", ce_info);
  }
  FILE *fp = fopen(out_filename.c_str(), "w");
  StringBuffer buffer;
  Writer<StringBuffer> writer(buffer);
  document.Accept(writer);
  fprintf(fp, "%s", buffer.GetString());
  fclose(fp);
}
