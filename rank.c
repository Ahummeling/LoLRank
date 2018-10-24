#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "curl/curl.h"
#include "cJSON.h"
#include "rankheader.h"

#define KEYSIZE 43

CURL* initFunction(){
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *easyhandle = curl_easy_init();
    if(easyhandle==NULL){
        fprintf(stderr,"curl_easy_init returned a null pointer.\n");
        exit(-1);
    }
    return easyhandle;
}

urlinfo readKey(urlinfo uinfo){
    FILE *keyfile;
    keyfile = fopen("../key.txt","r+");
    fgets(uinfo.key,KEYSIZE,(FILE*)keyfile);
    fclose(keyfile);
    return uinfo;
}

void appendKey(urlinfo* uinfo){
    uinfo->key = malloc(KEYSIZE*sizeof(char));
    *uinfo = readKey(*uinfo);
    strcat(uinfo->url,uinfo->key);
    free(uinfo->key);
}

void appendName(urlinfo* uinfo){
    strcat(uinfo->url,uinfo->name);
    char api_key[] = "?api_key=";
    char* api = malloc(10*sizeof(char));
    strcpy(api,api_key);
    strcat(uinfo->url,api);
    free(api);
}

void setURL(urlinfo* uinfo){
    char url[] = "https://euw1.api.riotgames.com/lol/summoner/v3/summoners/by-name/\0";
    //char url[] = "https://euw1.api.riotgames.com/lol/league/v3/positions/by-summoner/\0";
    uinfo->url = malloc(300*sizeof(char));
    strcpy(uinfo->url,url);
    appendName(uinfo);
    appendKey(uinfo);
}

void cleanAll(CURL* easyhandle, urlinfo* uinfo){
    free(uinfo->url);
    free(uinfo->name);
    curl_easy_cleanup(easyhandle);
    curl_global_cleanup();
}

int main(int argc, char** argv){
    CURL* easyhandle = initFunction();
    urlinfo uinfo;
    mem mem;
    uinfo.name = malloc(50*sizeof(char));
    if(argc>=2) {
        strcpy(uinfo.name,argv[1]);
    } else{
        printf("Please input your summonername: \n");
        scanf("%s",uinfo.name);
    }
    setURL(&uinfo);
    curl_easy_setopt(easyhandle,CURLOPT_URL,uinfo.url);
    //printf("url %s\n",uinfo.url);
    //curl_easy_perform(easyhandle);
    //printf("\n");
    mem = writeFunction(easyhandle);
    printf("output = %s\n",mem.memory);
    cleanAll(easyhandle, &uinfo);
    return 0;
}