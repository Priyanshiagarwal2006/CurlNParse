
#include <curl/curl.h>
#include <string>
#include <iostream>
#include <cstring>
#include <memory>
#include <fstream>
#include <vector>

size_t writeCallback(void* content, size_t size, size_t nmemb, void* userdata){
    size_t realsize = size * nmemb;
    std::string* str = static_cast<std::string*>(userdata);
    str->append(static_cast<char*>(content), realsize);
    return realsize;
}

bool download_page(const std::string& url, std::string& content){
    bool result = false;
    
    CURL* curl = curl_easy_init();
    if (curl){
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 3L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36");
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
        
        CURLcode res = curl_easy_perform(curl);
        if(res == CURLE_OK){
            long http_code = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
            if (http_code == 200){
                result = true;
            }else{
                std::cerr << "HTTP Error: " << http_code << std::endl;
            }
        }else{
            std::cerr << "Curl Error : " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    return result;
}

std::vector<std::string> readFileLinesToArray(const std::string& fileName){
    std::ifstream file(fileName);
    std::vector<std::string> lines;
    
    if (!file.is_open()){
        std::cerr << "Could not open the url file." << std::endl;
        return lines;
    }
    
    std::string line;
    while(std::getline(file, line)){
        if(!line.empty()) {  // Skip empty lines
            std::cout << line << std::endl;
            lines.push_back(line);
        }
    }
    file.close();
    return lines;
}

int main(){
    std::vector<std::string> fileLines = readFileLinesToArray("list.txt");
    if (!fileLines.empty()){
        std::cout << "URL file correctly fetched" << std::endl;
    }else{
        std::cerr << "Some error in opening the URL file" << std::endl;
        return 1;
    }
    
    CURLcode global_init_result = curl_global_init(CURL_GLOBAL_ALL);
    
    if(global_init_result != CURLE_OK){
        std::cerr << "Failed to initialize: " << curl_easy_strerror(global_init_result) << std::endl;
        return 1;
    }else{
        std::cout << "Curl Initialized" << std::endl;
    }
    
    for (const auto& url : fileLines){
        std::cout << "Fetching url: " << url << std::endl;
        std::string content;
        if (download_page(url, content)){
            std::cout << "Download successful!" << std::endl;
        }else{
            std::cerr << "Failed to Download the URL" << std::endl;
        }
    }
    
    curl_global_cleanup();
    return 0;
}
