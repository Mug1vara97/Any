#include <iostream>
#include "any.h"
#include <vector>

int main() {
    Any a = 5;
    Any b = std::string("hello, world");
    Any c = std::vector<int>{1, 2, 3};
    
    try {
        int value = a.GetValue<int>();
        std::cout << "a: " << value << std::endl;
    } catch (const std::bad_cast& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    try {
        std::string value = b.GetValue<std::string>();
        std::cout << "b: " << value << std::endl;
    } catch (const std::bad_cast& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    try {
        std::vector<int> value = c.GetValue<std::vector<int>>();
        for (int num : value) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    } catch (const std::bad_cast& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}