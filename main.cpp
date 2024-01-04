#include <iostream>
#include "load_balancer.cpp"
#include "request.cpp"

int main()
{
    Request request;
    std::cout << "Request: " << request.ipIn << ", " << request.ipOut << ", " << request.time << std::endl;
    return 0;
}
