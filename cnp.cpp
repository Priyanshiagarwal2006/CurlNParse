#include "cnp.h"
#include <algorithm>
#include <cctype>
#include <curl/curl.h>
#include <iostream>
#include <regex>

namespace cnp {

size_t writeCallback(void *content, size_t size, size_t nmemb, void *userdata) {
  std::string *str = static_cast<std::string *>(userdata);
  str->append(static_cast<char *>(content), size * nmemb);
  return size * nmemb;
}

bool init() { return curl_global_init(CURL_GLOBAL_ALL) == CURLE_OK; }

void cleanup() { curl_global_cleanup(); }

std::string download_page(const std::string &url) {
  std::string content;
  long http_code = 0;
  CURL *curl = curl_easy_init();
  bool result = false;

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 3L);
    curl_easy_setopt(
        curl, CURLOPT_USERAGENT,
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36");
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);

    CURLcode res = curl_easy_perform(curl);

    if (res == CURLE_OK) {
      curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
      if (http_code == 200) {
        result = true;
      } else {
        std::cerr << "HTTP Error: " << http_code << std::endl;
      }
    } else {
      std::cerr << "Curl Error: " << curl_easy_strerror(res) << std::endl;
    }
    curl_easy_cleanup(curl);
  }
  return (result ? content : "");
}

std::string html_to_text(const std::string &html) {
  std::string result = html;

  result =
      std::regex_replace(result, std::regex("<script[^>]*>[^<]*</script>"), "");
  result =
      std::regex_replace(result, std::regex("<style[^>]*>[^<]*</style>"), "");
  result = std::regex_replace(result, std::regex("<[^>]+>"), " ");
  result = std::regex_replace(result, std::regex("\\s+"), " ");
  result = std::regex_replace(result, std::regex("^\\s+|\\s+$"), "");
  return result;
}

std::string get_webpage_text(const std::string &url) {
  std::string html_code = download_page(url);
  return html_to_text(html_code);
}

} // namespace cnp
