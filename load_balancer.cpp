#include <iostream>
#include <fstream>
#include <queue>
#include "web_server.cpp"

/**
 * @brief Class representing a load balancer.
 *
 * This class manages a set of web servers and distributes incoming requests among them.
 * It handles request addition, processing, and logging.
 */
class LoadBalancer {
    std::queue<Request> request_queue; ///< Queue of incoming requests.
    std::vector<WebServer> servers; ///< Vector of WebServer objects.
    int serverCount; ///< The initial number of servers.
    std::ofstream logFile; ///< File stream for logging activities.
    int totalRequestsCompleted; ///< Total number of requests completed.
    int requestAdded; ///< Total number of requests added.
    int serversAdded;
    int serversRemoved;

    public:
        /**
         * @brief Constructor for LoadBalancer.
         *
         * Initializes a LoadBalancer with a specified number of web servers.
         * @param serverCount The number of web servers to initialize.
         */
        LoadBalancer(int serverCount) : serverCount(serverCount) {
            logFile.open("log.txt"); // Open the log file
            totalRequestsCompleted = 0; // Total requests completed
            requestAdded = 0; // Total requests added
            serversAdded = 0;
            serversRemoved = 0;
        }

        /**
         * @brief Destructor for LoadBalancer.
         *
         * Closes the log file if it is open.
         */
        ~LoadBalancer() {
            if (logFile.is_open()) {
                logFile.close(); // Close the log file in the destructor
            }
        }

        /**
         * @brief Runs the load balancing process for a specified duration.
         *
         * Handles the addition of new requests, distribution of requests to servers,
         * and the logging of various events.
         * @param time_count The duration to run the load balancing process.
         */
        void run(int time_count) {
            int threshold, durationStart, durationEnd, randomRequestProbability, maxNewReq;
            threshold = serverCount * 20;
            std::cout << "Enter the minimum starting duration for the requests: ";
            std::cin >> durationStart;
            std::cout << "Enter the maximum ending duration for the requests: ";
            std::cin >> durationEnd;
            std::cout << "Enter the maximum number of new requests that can be added in one cycle: ";
            std::cin >> maxNewReq;
            std::cout << "Enter the probability of a new request being added (x/100): ";
            std::cin >> randomRequestProbability;

            logFile << "Starting Total Requests in Queue: " << serverCount * 20 << std::endl; // Write to log file
            logFile << "The Range of Duration Times is Between " << durationStart << " and " << durationEnd << " Cycles" << std::endl; // Write to log file
            logFile << "Request Queue Threshold: " << threshold << std::endl; // Write to log file
            logFile << "Probability of a New Request Being Added: " << randomRequestProbability << "%" << std::endl; // Write to log file
            logFile << "Maximum Number of New Requests That Can Be Added in One Cycle: " << maxNewReq << "\n" << std::endl; // Write to log file

            // create request_queue
            logFile << "Requests in Starting Queue" << std::endl;
            for (int i = 0; i < serverCount * 20; ++i) {
                Request request = Request(durationStart, durationEnd);
                request_queue.push(request);
                
                logFile << "IP in: " << request.ipIn << " | IP out: " << request.ipOut << " | Duration: " << request.taskDuration << " cycles" << std::endl; // Write to log file
            }
            logFile << std::endl; // Write to log file
            // fill servers with WebServers
            for (int i = 0; i < serverCount; ++i) {
                WebServer webServer;
                servers.push_back(webServer);
            }

            std::random_device rd;
            std::default_random_engine engine(rd());
            std::uniform_int_distribution<int> dist(1, 100);
            std::uniform_int_distribution<int> newReqDist(0, maxNewReq);

            // carry out load balancing program
            for (int i = 0; i < time_count; ++i) {
                logFile << "Cycle: " << i << std::endl; // Write to log file
                // add new requests to request_queue 
                for (int j = 0; j < newReqDist(engine); ++j) {
                    if (dist(engine) <= randomRequestProbability) { // Adjust the condition based on your desired frequency of adding requests
                        Request newRequest = Request(durationStart, durationEnd);
                        request_queue.push(newRequest);
                        logFile << "New Request Added | IP in: " << newRequest.ipIn << " | IP out: " << newRequest.ipOut << " | Duration: " << newRequest.taskDuration << " cycles" << std::endl;
                        requestAdded++;
                    }
                }
                
                int currentFullServers = 0;
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
                            totalRequestsCompleted++;

                            // Load next request if available
                            if (!request_queue.empty()) {
                                logFile << "Request Loaded | IP in: " << request_queue.front().ipIn << " | IP out: " << request_queue.front().ipOut << " | Duration: " << request_queue.front().taskDuration << " cycles" << std::endl; // Write to log file
                                servers[j].addRequest(request_queue.front());
                                request_queue.pop();
                            }
                        }
                    } else if (!request_queue.empty()) {
                        // Load request into empty server
                        logFile << "Request Loaded | IP in: " << request_queue.front().ipIn << " | IP out: " << request_queue.front().ipOut << " | Duration: " << request_queue.front().taskDuration << " cycles" << std::endl; // Write to log file
                        servers[j].addRequest(request_queue.front());
                        request_queue.pop();
                    }
                    if (!servers[j].isEmpty()) {
                        currentFullServers++;
                    }
                }

                if (i % 100 == 0) {
                    int higherbound = (servers.size() * 25);
                    int lowerbound = (servers.size() * 15);
                    if (request_queue.size() > higherbound) {
                        WebServer webServer;
                        servers.push_back(webServer);
                        serversAdded++;
                        logFile << "Over Threshold Web Server Added | Total Web Servers: " << servers.size() << std::endl; // Write to log file
                    } 
                    else if (request_queue.size() < lowerbound && servers.size() > 1) {
                        servers.pop_back();
                        serversRemoved++;
                        logFile << "Under Threshold Web Server Removed | Total Web Servers: " << servers.size() << std::endl; // Write to log file
                    }                    
                }
                
            }

            int uncompletedRequests = 0;
            for (int i = 0; i < servers.size(); ++i) {
                if (!servers[i].isEmpty()) {
                    uncompletedRequests++;
                }
            }

            logFile << "\nTotal Requests Completed: " << totalRequestsCompleted << std::endl; // Write to log file
            logFile << "Total New Requests Added Over Input Time: " << requestAdded << std::endl; // Write to log file
            logFile << "\nTotal Web Servers Added: " << serversAdded << std::endl; // Write to log file
            logFile << "Total Web Servers Removed: " << serversRemoved << std::endl; // Write to log file
            logFile << "Total Number of Web Servers Left: " << servers.size() << std::endl; // Write to log file
            logFile << "\nTotal Requests Remaining in Queue: " << request_queue.size() << std::endl; // Write to log file
            logFile << "Total Uncompleted Requests: " << request_queue.size() + uncompletedRequests << std::endl; // Write to log file
        }
};
