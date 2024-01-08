#include <iostream>
#include "load_balancer.cpp"

// \file

/** 
 * @brief Entry point of the program.
 *
 * This program initializes a Load Balancer with a specified number of servers
 * and runs it for a given duration.
 *
 * @return int The exit code of the program.
 */
int main()
{
    int server_count; ///< Number of servers to initialize in the load balancer.
    int time_count; ///< Duration for which the load balancer will run.

    // Requesting user input for the number of servers.
    std::cout << "Enter number of servers you want: " << std::endl;
    std::cin >> server_count;

    // Requesting user input for the duration to run the load balancer.
    std::cout << "Enter how long you want to run the load balancer: " << std::endl;
    std::cin >> time_count;

    // Initializing the load balancer with the specified number of servers.
    LoadBalancer loadBalancer(server_count);

    // Running the load balancer for the specified duration.
    loadBalancer.run(time_count);

    return 0;
}
