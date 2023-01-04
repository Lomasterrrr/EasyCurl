#include <iostream>
class EasyCURL
{
public:
    // size_t
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
    static size_t ReadCallback(void *ptr, size_t size, size_t nmemb, void *stream);
    static size_t ClearWrite(void *buffer, size_t size, size_t nmemb, void *userp);

    // lib
    std::string DownloadPage(std::string link);
    void DownloadFile(std::string link,std::string outfile);
    bool HttpGet(std::string link);
    long ResponseCode(std::string link);
    int HeadersGet(std::string link);
};
