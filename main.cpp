
#include "cnp.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::string url = "https://lichess.org/";

  cnp::init();

  std::string result_text = cnp::download_page(url);
  std::string plain_text = cnp::html_to_text(result_text);

  /*std::cout << cnp::get_webpage_text(url) << std::endl;*/

  std::vector<std::string> result;
  result = cnp::get_tags_to_array(result_text, "a");

  std::cout << result.size() << std::endl;
  for (auto s : result) {
    std::cout << s << std::endl;
  }

  std::vector<std::string> elements =
      cnp::find_elements_by_class(result_text, "site-name");

  for (auto s : elements) {
    std::cout << s << std::endl;
  }

  cnp::cleanup();

  return 0;
}
