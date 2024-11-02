#ifndef cnp_h
#define cnp_h

#include <iostream>
#include <string>

namespace cnp {
std::string download_page(const std::string &url);
std::string html_to_text(const std::string &html);
std::string get_webpage_text(const std::string &url);

bool init();
void cleanup();

} // namespace cnp

#endif
