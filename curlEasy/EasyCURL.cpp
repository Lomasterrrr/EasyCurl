#include <iostream>
#include "EasyCURL.h"
#include "curl/curl.h"

// size_t
size_t EasyCURL::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
size_t EasyCURL::ReadCallback(void *ptr, size_t size, size_t nmemb, void *stream)
{
    curl_off_t nread;
    size_t retcode = fread(ptr, size, nmemb, (FILE *) stream);
    nread = (curl_off_t) retcode;
    fprintf(stderr, "*** We read %" CURL_FORMAT_CURL_OFF_T " bytes from filen", nread);
    return retcode;
}
size_t EasyCURL::ClearWrite(void *buffer, size_t size, size_t nmemb, void *userp)
{
    return size * nmemb;
}

// lib
std::string EasyCURL::DownloadPage(std::string link)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    const char * linkConvert = link.c_str();
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, linkConvert);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}
void EasyCURL::DownloadFile(std::string link, std::string outfile)
{
    CURL *curl;
    FILE *fp;
    CURLcode res;
    const char *outfileConvert = outfile.c_str();
    const char * linkConvert = link.c_str();
    curl = curl_easy_init();                                                                                                                                                                                                                                                           
    if (curl)
    {   
        fp = fopen(outfileConvert,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, linkConvert);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }   
}
bool EasyCURL::HttpGet(std::string link)
{
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if(curl) {
        const char * linkConvert = link.c_str();
        curl_easy_setopt(curl, CURLOPT_URL, linkConvert);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ClearWrite);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            return false;
        curl_easy_cleanup(curl);
    }
    return true;
}
long EasyCURL::ResponseCode(std::string link)
{
    CURL *curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        const char * linkConvert = link.c_str();
        curl_easy_setopt(curl, CURLOPT_URL, linkConvert);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ClearWrite);
        res = curl_easy_perform(curl);
        
        if(res == CURLE_OK) {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            return response_code;
        }
        curl_easy_cleanup(curl);
        return 0;
    }
}       
int EasyCURL::HeadersGet(std::string link) {
    CURL *curl = curl_easy_init();
    CURLcode res;
    if(curl) {
        const char * linkConvert = link.c_str();
        curl_easy_setopt(curl, CURLOPT_URL, linkConvert);
        curl_easy_setopt(curl, CURLOPT_HEADER, 1);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        return 0;
    }
    return 0;
}