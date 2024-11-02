
#include "cnp.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::string url = "https://www.example.com/";

  cnp::init();

  std::string result_text = cnp::download_page(url);

  std::cout << result_text << std::endl;

  cnp::cleanup();

  return 0;
}
