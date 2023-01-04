# EasyCurl
![alt text](https://i.imgur.com/QjLZFzt.png)

The most simplified version of the curl library c++

## Linux
- git clone https://github.com/Lomasterrrr/EasyCurl.git
- Transfer the folder inside to your project.
- #include "curlEasy/EasyCURL.h"
- Gone!

## Windows
- Download git
- Unzip
- Transfer the folder inside to your project.
- #include "curlEasy/EasyCURL.h
- Gone!

## Func
```c++
string EasyCURL::DownloadPage(string link)
void EasyCURL::DownloadFile(string link, string outfile)
bool EasyCURL::HttpGet(string link)
long EasyCURL::ResponseCode(string link)
int EasyCURL::HeadersGet(string link)
```
