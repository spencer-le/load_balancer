#include <iostream>
#include <vector>
#include "request.cpp"

class WebServer {
    bool empty;
    Request* request;

public:
    WebServer() {
        empty = true;
        request = nullptr;
    }

    // Destructor
    ~WebServer() {
        delete request;
    }

    // Copy constructor
    WebServer(const WebServer& other) {
        empty = other.empty;
        if (other.request) {
            request = new Request(*other.request);
        }
    }

    // Copy assignment operator
    WebServer& operator=(const WebServer& other) {
        if (this != &other) {
            empty = other.empty;
            delete request;
            if (other.request) {
                request = new Request(*other.request);
            } else {
                request = nullptr;
            }
        }
        return *this;
    }

    void addRequest(Request request) {
        delete this->request;
        this->request = new Request(request);
        empty = false;
    }

    void removeRequest() {
        delete request;
        request = nullptr;
        empty = true;
    }

    Request& getRequest() {
        return *request;
    }

    bool isEmpty() {
        return empty;
    }
};
