#include <curl/curl.h>
#include <string> 
#include <iostream>
#include <cstring> 
#include <memory>


using namespace std;

bool download_page(const char* url, string& content){
  //TODO
  return true;
}

int main(){
  CURLcode global_init_result = curl_global_init(CURL_GLOBAL_ALL);
  
  if(global_init_result != CURLE_OK){
    cerr << "Failed to initialize: " << curl_easy_strerror(global_init_result) << endl;
    return 1;
  }else{
    cout << "Curl Initialized" << endl;
  }

  
  string content;

  const char* url = "https://en.wikipedia.org/wiki/Linus_Torvalds";

  cout << "Downloading the text content: " << url << endl;


  if (download_page(url, content)){
    cout << "Download successful!" << endl;
    cout << content << endl;
  }else{
    cerr << "Failed to Download the URL" << endl;
  }

  curl_global_cleanup();

  return 0;
}
