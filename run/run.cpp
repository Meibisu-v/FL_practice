#include "../solver.h"
#include<string>
#include <iostream>

int main() {

    std::string regularExpression, targetString;
    std::cin >> regularExpression >> targetString;

    int maxLength = solveTask(regularExpression, targetString);

    if (maxLength >= 0)
        std::cout << maxLength;
    else
        std::cout << "ERROR";
}

