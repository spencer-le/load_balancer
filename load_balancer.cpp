#include <iostream>
#include <fstream>
#include <queue>
#include "web_server.cpp"

class LoadBalancer {
    std::queue<Request> request_queue;
    std::vector<WebServer> servers;
    int serverCount;
    std::ofstream logFile; // File stream for logging
    int totalRequestsCompleted; // Total requests completed
    int requestAdded; // Total requests added

    public:
        LoadBalancer(int serverCount) : serverCount(serverCount) {
            logFile.open("log.txt"); // Open the log file
            totalRequestsCompleted = 0; // Total requests completed
            requestAdded = 0; // Total requests added
        }

        ~LoadBalancer() {
            if (logFile.is_open()) {
                logFile.close(); // Close the log file in the destructor
            }
        }


        void run(int time_count) {
            logFile << "Starting Total Requests in Queue: " << serverCount * 20 << std::endl; // Write to log file
            logFile << "The range of task times is between 1 and 100 cycles\n" << std::endl; // Write to log file

            // create request_queue
            logFile << "Requests in Starting Queue" << std::endl;
            for (int i = 0; i < serverCount * 20; ++i) {
                Request request;
                request_queue.push(request);
                
                logFile << "IP in: " << request.ipIn << " | IP out: " << request.ipOut << " | Duration: " << request.taskDuration << " cycles" << std::endl; // Write to log file
            }
            
            // fill servers with WebServers
            for (int i = 0; i < serverCount; ++i) {
                WebServer webServer;
                servers.push_back(webServer);
            }

            std::random_device rd;
            std::default_random_engine engine(rd());
            std::uniform_int_distribution<int> dist(0, 5);

            // carry out load balancing program
            for (int i = 0; i < time_count; ++i) {
                logFile << "Cycle: " << i << std::endl; // Write to log file
                std::cout << "Cycle: " << i << std::endl;

                if (dist(engine) == 0) { // Adjust the condition based on your desired frequency of adding requests
                    Request newRequest;
                    request_queue.push(newRequest);
                    logFile << "New Request Added | IP in: " << newRequest.ipIn << " | IP out: " << newRequest.ipOut << " | Duration: " << newRequest.taskDuration << " cycles" << std::endl;
                    std::cout << "New Request Added | IP in: " << newRequest.ipIn << " | IP out: " << newRequest.ipOut << " | Duration: " << newRequest.taskDuration << " cycles" << std::endl;
                    requestAdded++;
                }

                for (int j = 0; j < servers.size(); ++j) {
                    if (!servers[j].isEmpty()) {
                        // Decrement the time of the current request
                        Request& currentRequest = servers[j].getRequest();
                        if (currentRequest.time > 0) {
                            currentRequest.time -= 1;
                        }

                        // Check if the request is completed
                        if (currentRequest.time <= 0) {
                            logFile << "Request Completed | IP in: " << currentRequest.ipIn << " | IP out: " << currentRequest.ipOut << " | Duration: " << currentRequest.taskDuration << " cycles" << std::endl; // Write to log file
                            std::cout << "Request Completed | IP in: " << currentRequest.ipIn << " | IP out: " << currentRequest.ipOut << " | Duration: " << currentRequest.taskDuration << " cycles"<< std::endl;
                            servers[j].removeRequest();
                            totalRequestsCompleted++;

                            // Load next request if available
                            if (!request_queue.empty()) {
                                logFile << "Request Loaded | IP in: " << request_queue.front().ipIn << " | IP out: " << request_queue.front().ipOut << " | Duration: " << request_queue.front().taskDuration << " cycles" << std::endl; // Write to log file
                                std::cout << "Request Loaded | IP in: " << request_queue.front().ipIn << " | IP out: " << request_queue.front().ipOut << " | Duration: " << request_queue.front().taskDuration << " cycles"<< std::endl;
                                servers[j].addRequest(request_queue.front());
                                request_queue.pop();
                            }
                        }
                    } else if (!request_queue.empty()) {
                        // Load request into empty server
                        logFile << "Request Loaded | IP in: " << request_queue.front().ipIn << " | IP out: " << request_queue.front().ipOut << " | Duration: " << request_queue.front().taskDuration << " cycles" << std::endl; // Write to log file
                        std::cout << "Request Loaded | IP in: " << request_queue.front().ipIn << " | IP out: " << request_queue.front().ipOut << " | Duration: " << request_queue.front().taskDuration << " cycles"<< std::endl;
                        servers[j].addRequest(request_queue.front());
                        request_queue.pop();
                    }
                }
            }

            logFile << "\nTotal Requests Completed: " << totalRequestsCompleted << std::endl; // Write to log file
            logFile << "Total Requests Added Over Input Time: " << requestAdded << std::endl; // Write to log file
            logFile << "Total Requests Remaining in Queue: " << request_queue.size() << std::endl; // Write to log file
        }
};
