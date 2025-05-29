#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers;

    numbers.push_back(20);
    numbers.push_back(60);
    numbers.push_back(40);

    std::cout << "Numbers : " << numbers[2];

    return 0;
}
