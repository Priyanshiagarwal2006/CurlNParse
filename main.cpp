
#include "cnp.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::string url = "https://www.example.com/";

  cnp::init();

  std::string result_text = cnp::download_page(url);
  std::string plain_text = cnp::html_to_text(result_text);

  std::cout << cnp::get_webpage_text(url) << std::endl;

  cnp::cleanup();

  return 0;
}
