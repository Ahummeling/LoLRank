#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "curl/curl.h"
#include "cJSON.h"
#include "rankheader.h"

size_t write_data(void *contents, size_t size, size_t nmemb, void *userp){
  size_t realsize = size * nmemb;
  struct memoryStruct *mem = (struct memoryStruct *)userp;
 
  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(ptr == NULL) {
    /* out of memory! */ 
    fprintf(stderr,"not enough memory (realloc returned NULL)\n");
    exit(-1);
  }
  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
  return realsize;
}

void writeFunction(CURL* easyhandle){
    mem chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;
    curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, (void*)&chunk);
    if(curl_easy_perform(easyhandle)!=CURLE_OK){
        fprintf(stderr, "error in the curl_easy_perform() failed.\n");
        exit(-1);
    }
    printf("%lu bytes retrieved.\n",(unsigned long)chunk.size);
}