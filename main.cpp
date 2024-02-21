#include "LongNumber.h"
#include <ctime>

int main(){
    clock_t startTime = clock();
    LongNumber Pi = LongNumber::pi(10);
    clock_t endTime = clock();

    double totalTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;

    std::cout << "Time passed: " << totalTime << " (sec) ";
    return 0;
}