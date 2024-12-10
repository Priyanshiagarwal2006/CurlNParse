

# CurlNParse (CNP)

CurlNParse is a C++ library that provides simple web page downloading and HTML parsing functionality using libcurl. It allows you to easily download web pages and convert HTML content to plain text.

## Prerequisites

- C++ compiler
- libcurl development libraries
- Make sure libcurl is installed on your system

## Building the Project

You can build the project using the following command:

```bash
g++ -c cnp.cpp -lcurl && g++ main.cpp cnp.o -lcurl -o cnp && ./cnp
```

Or by using ```make```:

```bash
make all
make run
```

## Project Structure

- `main.cpp` - Example usage and main program entry point
- `cnp.cpp` - Implementation of the CurlNParse functionality
- `cnp.h` - Header file containing function declarations

## Function Reference

| Function | Description | Parameters | Return Value  |
|----------|-------------|------------|--------------|
| `init()` | Initializes the curl library | None | `bool` - Returns true if initialization was successful |
| `cleanup()` | Cleans up curl resources | None | `void` | Should be called when done using the library |
| `download_page()` | Downloads HTML content from a URL | `const string& url` | `string` - The downloaded HTML content |
| `html_to_text()` | Converts HTML to plain text | `const string& html`| `string` - Plain text version of the HTML |
| `get_webpage_text()` | Downloads and converts webpage to text | `const string& url`| `string` - Plain text content of the webpage |
| `get_tags_to_array()` | Finds  tags & converts to array | `const string& html` && `const string& tag`| `vector` - vector containing the tag |
| `find_elements_by_class()` | Finds elements by a particular class name | `const string& html` && `const string& class_name`| `vector` - vector containing the elements |
| `find_element_by_id()` | Find element by a particular id | `const string& html` && `const string& id`| `string` - string containing the element |
| `find_elements_by_attr_val()` | Find elements by an attribute with a particular value | `const string& html`, `const string& attr_name`, `const string& attr_val`| `vector` - vector containing all the elements |
## Usage Example

```cpp


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
  std::string e = cnp::find_element_by_id(result_text, "topnav");
  std::cout << e << std::endl;
  std::vector<std::string> attr_test =
      cnp::find_elements_by_attr_val(result_text, "target", "_blank");
  for (auto s : attr_test) {
    std::cout << s << std::endl;
  }
  cnp::cleanup();

  return 0;
}

```

### To-Do

- ~~Find elements by tag name~~
- ~~Find elements by a class~~
- ~~Find element by an ID~~
- ~~Find elements by attribute values~~
- Extract text content from elements
- Navigate parent/child relationships
- Extract links and URLs
- Basic element manipulation
- Support for different parsers (like libxml2)
- CSS selector support
- XPath-like queries
## License

MIT LICENSE

