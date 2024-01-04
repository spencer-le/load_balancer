#include <iostream>
#include "load_balancer.cpp"

int main()
{
    int server_count;
    int time_count;

    std::cout << "Enter number of servers you want: " << std::endl;
    std::cin >> server_count;
    std::cout << "Enter how long you want to run the load balancer: " << std::endl;
    std::cin >> time_count;

    LoadBalancer loadBalancer(server_count);
    loadBalancer.run(time_count);

    return 0;
}
