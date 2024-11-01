#include <curl/curl.h>
#include <string> 
#include <iostream>
#include <cstring> 
#include <memory>
#include <string> 
#include <fstream>
#include <vector> 
using namespace std;

size_t writeCallback(void* content, size_t size, size_t nmemb, void* userdata){
    size_t realsize = size * nmemb;
    string* str = static_cast<string*>(userdata);
    str->append(static_cast<char*>(content), realsize);
    return realsize;
}

bool download_page(const string& url, string& content){
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
                cerr << "HTTP Error: " << http_code << endl;
            }
        }else{
            cerr << "Curl Error : " << curl_easy_strerror(res) << endl;
        }
        curl_easy_cleanup(curl);
    }
    return result;
}

vector<string> readFileLinesToArray(const string& fileName){
    ifstream file(fileName);
    vector<string> lines;
    
    if (!file.is_open()){
        cerr << "Could not open the url file." << endl;
        return lines;
    }
    
    string line;
    while(getline(file, line)){
        if(!line.empty()) {  // Skip empty lines
            cout << line << endl;
            lines.push_back(line);
        }
    }
    file.close();
    return lines;
}

int main(){
    vector<string> fileLines = readFileLinesToArray("list.txt");
    if (!fileLines.empty()){
        cout << "URL file correctly fetched" << endl;
    }else{
        cerr << "Some error in opening the URL file" << endl;
        return 1;
    }
    
    CURLcode global_init_result = curl_global_init(CURL_GLOBAL_ALL);
    
    if(global_init_result != CURLE_OK){
        cerr << "Failed to initialize: " << curl_easy_strerror(global_init_result) << endl;
        return 1;
    }else{
        cout << "Curl Initialized" << endl;
    }
    
    for (const auto& url : fileLines){
        cout << "Fetching url: " << url << endl;
        string content;
        if (download_page(url, content)){
            cout << "Download successful!" << endl;
        }else{
            cerr << "Failed to Download the URL" << endl;
        }
    }
    
    curl_global_cleanup();
    return 0;
}
