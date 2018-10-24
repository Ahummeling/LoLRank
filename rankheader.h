#pragma once

typedef struct urlinfo{
    char* url;
    char* key;
    char* name;
    int state;
}urlinfo;

typedef struct memoryStruct {
  char *memory;
  size_t size;
}mem;

urlinfo readKey(urlinfo uinfo);

void appendKey(urlinfo* uinfo);

void appendName(urlinfo* uinfo);

void setURL(urlinfo* uinfo);

void cleanAll(CURL* easyhandle, urlinfo* uinfo);

size_t write_data(void *buffer, size_t size, size_t nmemb, void* userp);

mem writeFunction(CURL* easyhandle);