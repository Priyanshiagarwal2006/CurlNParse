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

## Project Structure

- `main.cpp` - Example usage and main program entry point
- `cnp.cpp` - Implementation of the CurlNParse functionality
- `cnp.h` - Header file containing function declarations

## Function Reference

| Function | Description | Parameters | Return Value | Notes |
|----------|-------------|------------|--------------|-------|
| `init()` | Initializes the curl library | None | `bool` - Returns true if initialization was successful | Must be called before using any other functions |
| `cleanup()` | Cleans up curl resources | None | `void` | Should be called when done using the library |
| `download_page()` | Downloads HTML content from a URL | `const string& url` - The URL to download | `string` - The downloaded HTML content | Returns empty string on failure |
| `html_to_text()` | Converts HTML to plain text | `const string& html` - HTML content to convert | `string` - Plain text version of the HTML | Removes tags, scripts, and styling |
| `get_webpage_text()` | Downloads and converts webpage to text | `const string& url` - The URL to process | `string` - Plain text content of the webpage | Combines `download_page()` and `html_to_text()` |

## Usage Example

```cpp
#include "cnp.h"
#include <iostream>

int main() {
    std::string url = "https://www.example.com/";
    
    cnp::init();
    std::string text = cnp::get_webpage_text(url);
    std::cout << text << std::endl;
    cnp::cleanup();
    
    return 0;
}
```

## License

MIT LICENSE
