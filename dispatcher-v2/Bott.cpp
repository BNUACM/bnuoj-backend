/* 
 * File:   Bott.cpp
 * Author: 51isoft
 * 
 * Created on 2014年1月19日, 上午1:04
 */

#include "Bott.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

const string Bott::RAW_FILES_DIRECTORY = "raw_files/";
const string Bott::CHA_RAW_FILES_DIRECTORY = "cha_raw_files/";
const string Bott::RESULTS_DIRECTORY = "results/";
const string Bott::CHA_RESULTS_DIRECTORY = "cha_results/";
const string Bott::EXTENTION = ".bott";

Bott::Bott() {
  //ctor
}

Bott::~Bott() {
  //dtor
}

Bott::Bott(string filename) {
  Document document;
  document.Parse(loadAllFromFile(filename).c_str());
  if (document.HasMember("type")) {
    type = document["type"].GetInt();
  }
  if (document.HasMember("runid")) {
    runid = document["runid"].GetString();
  }
  if (document.HasMember("source")) {
    src = document["source"].GetString();
  }
  if (document.HasMember("compileInfo")) {
    ce_info = document["compileInfo"].GetString();
  }
  if (document.HasMember("language")) {
    language = document["language"].GetString();
  }
  if (document.HasMember("pid")) {
    pid = document["pid"].GetString();
  }
  if (document.HasMember("testcases")) {
    number_of_testcases = document["testcases"].GetString();
  }
  if (document.HasMember("timeLimit")) {
    time_limit = document["timeLimit"].GetString();
  }
  if (document.HasMember("caseLimit")) {
    case_limit = document["caseLimit"].GetString();
  }
  if (document.HasMember("memoryLimit")) {
    memory_limit = document["memoryLimit"].GetString();
  }
  if (document.HasMember("spjStatus")) {
    spj = document["spjStatus"].GetString();
  }
  if (document.HasMember("vname")) {
    vname = document["vname"].GetString();
  }
  if (document.HasMember("vid")) {
    vid = document["vid"].GetString();
  }
  if (document.HasMember("memoryUsed")) {
    memory_used = document["memoryUsed"].GetString();
  }
  if (document.HasMember("timeUsed")) {
    time_used = document["timeUsed"].GetString();
  }
  if (document.HasMember("result")) {
    result = document["result"].GetString();
  }
  if (document.HasMember("challenge")) {
    if (document["challenge"].HasMember("id")) {
      cha_id = document["challenge"]["id"].GetString();
    }
    if (document["challenge"].HasMember("dataType")) {
      data_type = document["challenge"]["dataType"].GetString();
    }
    if (document["challenge"].HasMember("dataLanguage")) {
      data_lang = document["challenge"]["dataLanguage"].GetString();
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
  addStringValue(document, "source", src);
  addStringValue(document, "language", language);
  addStringValue(document, "pid", pid);
  addStringValue(document, "memoryLimit", memory_limit);
  addStringValue(document, "spjStatus", spj);
  addStringValue(document, "caseLimit", case_limit);
  if (type == NEED_JUDGE || type == DO_PRETEST || type == DO_TESTALL ||
      type == DO_INTERACTIVE) {
    addStringValue(document, "runid", runid);
    addStringValue(document, "testcases", number_of_testcases);
    addStringValue(document, "timeLimit", time_limit);
    addStringValue(document, "vname", vname);
    addStringValue(document, "vid", vid);
  } else if (type == DO_CHALLENGE) {
    Value challenge;
    challenge.SetObject();
    addStringValueToRef(document, challenge, "id", cha_id);
    addStringValueToRef(document, challenge, "dataType", data_type);
    addStringValueToRef(document, challenge, "dataLanguage", data_lang);
    addStringValueToRef(document, challenge, "dataDetail", data_detail);
    document.AddMember("challenge", challenge, document.GetAllocator());
    addStringValue(document, "timeLimit", case_limit);
  }
  FILE *fp = fopen(out_filename.c_str(), "w");
  StringBuffer buffer;
  Writer<StringBuffer> writer(buffer);
  document.Accept(writer);
  fprintf(fp, "%s", buffer.GetString());
  fclose(fp);
}
