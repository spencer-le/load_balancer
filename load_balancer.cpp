#include <iostream>
#include <queue>
#include "web_server.cpp"

class LoadBalancer {
    std::queue<Request> request_queue;
    std::vector<WebServer> servers;
    int serverCount;

    public:
        LoadBalancer(int serverCount) : serverCount(serverCount) {}

        void run(int time_count) {
            // create request_queue
            for (int i = 0; i < serverCount * 20; ++i) {
                Request request;
                request_queue.push(request);
            }

            // fill servers with WebServers
            for (int i = 0; i < serverCount; ++i) {
                WebServer webServer;
                servers.push_back(webServer);
            }

            // carry out load balancing program
            for (int i = 0; i < time_count; ++i) {
                std::cout << "Cycle: " << i << std::endl;
                for (int j = 0; j < servers.size(); ++j) {
                    if (!servers[j].isEmpty()) {
                        // Decrement the time of the current request
                        Request& currentRequest = servers[j].getRequest();
                        if (currentRequest.time > 0) {
                            currentRequest.time -= 1;
                        }

                        // Check if the request is completed
                        if (currentRequest.time <= 0) {
                            std::cout << "Request Completed | IP in: " << currentRequest.ipIn << " | IP out: " << currentRequest.ipOut << " | Duration: " << currentRequest.taskDuration << " cycles"<< std::endl;
                            servers[j].removeRequest();

                            // Load next request if available
                            if (!request_queue.empty()) {
                                std::cout << "Request Loaded | IP in: " << request_queue.front().ipIn << " | IP out: " << request_queue.front().ipOut << " | Duration: " << request_queue.front().taskDuration << " cycles"<< std::endl;
                                servers[j].addRequest(request_queue.front());
                                request_queue.pop();
                            }
                        }
                    } else if (!request_queue.empty()) {
                        // Load request into empty server
                        servers[j].addRequest(request_queue.front());
                        request_queue.pop();
                    }
                }
            }
        }
};
