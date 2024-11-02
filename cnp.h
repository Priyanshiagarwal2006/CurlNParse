#ifndef cnp_h
#define cnp_h

#include <iostream>
#include <string>
#include <vector>

namespace cnp {
std::string download_page(const std::string &url);
std::string html_to_text(const std::string &html);
std::string get_webpage_text(const std::string &url);
std::vector<std::string> get_tags_to_array(const std::string &html,
                                           const std::string &tag_name);
std::vector<std::string> find_elements_by_class(const std::string &html,
                                                const std::string &class_name);

bool init();
void cleanup();

} // namespace cnp

#endif
