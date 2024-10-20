#include <iostream>
#include <string>

int main() {
    std::string str = "<abc>1</abc>";
    
    size_t openTagStart = str.find("</");
    size_t openTagEnd = str.find('>', openTagStart);
    size_t closeTagStart = str.find("</", openTagEnd);
    
    // Extract the tag name
    std::string tagName = str.substr(openTagStart + 1, openTagEnd - openTagStart - 1);
    
    // Extract the content
    std::string content = str.substr(openTagEnd + 1, closeTagStart - openTagEnd - 1);
    
    // Output the results
    std::cout << "Tag: <" << tagName << ">\n";
    std::cout << "Content: " << content << "\n";

    return 0;
}
