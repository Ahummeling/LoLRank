#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "curl/curl.h"
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

void setURL(urlinfo* uinfo){
    char url[] = "https://euw1.api.riotgames.com/lol/summoner/v3/summoners/by-name/tedtski?api_key=\0";
    uinfo->url = malloc(300*sizeof(char));
    strcpy(uinfo->url,url);
    strcat(uinfo->url,uinfo->key);
    free(uinfo->key);
}

void cleanAll(CURL* easyhandle, urlinfo* uinfo){
    free(uinfo->url);
    curl_easy_cleanup(easyhandle);
    curl_global_cleanup();
}

int main(){
    CURL* easyhandle = initFunction();
    urlinfo uinfo;
    uinfo.key = malloc(KEYSIZE*sizeof(char));
    uinfo = readKey(uinfo);
    setURL(&uinfo);
    curl_easy_setopt(easyhandle,CURLOPT_URL,uinfo.url);
    
    cleanAll(easyhandle, &uinfo);
    return 0;
}