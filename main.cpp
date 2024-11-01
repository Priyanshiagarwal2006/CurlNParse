#include <curl/curl.h>
#include <string> 
#include <iostream>
#include <cstring> 
#include <memory>


using namespace std;



int main(){
  CURLcode global_init_result = curl_global_init(CURL_GLOBAL_ALL);
  
  if(global_init_result != CURLE_OK){
    cerr << "Failed to initialize: " << curl_easy_strerror(global_init_result) << endl;
    return 1;
  }else{
    cout << "Curl Initialized" << endl;
  }

  return 0;
}
