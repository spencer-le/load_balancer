#include <iostream>
#include <vector>
#include "request.cpp"

/**
 * @brief Class representing a web server.
 *
 * This class models a web server that can handle a single request at a time. It provides 
 * methods to add, remove, and retrieve the current request.
 */
class WebServer {
    bool empty; ///< Flag indicating whether the server is handling a request.
    Request* request; ///< Pointer to the current request being handled.

    public:
        /**
         * @brief Default constructor.
         *
         * Initializes a new WebServer instance as empty and without any request.
         */
        WebServer() {
            empty = true;
            request = nullptr;
        }

        /**
         * @brief Destructor.
         *
         * Cleans up any allocated resources.
         */
        ~WebServer() {

        }

        /**
         * @brief Copy constructor.
         *
         * Creates a new WebServer instance as a copy of another instance.
         * @param other The WebServer instance to copy from.
         */
        WebServer(const WebServer& other) {
            empty = other.empty;
            if (other.request) {
                request = other.request;
            }
        }

        /**
         * @brief Copy assignment operator.
         *
         * Assigns this instance the values from another instance.
         * @param other The WebServer instance to assign from.
         * @return Reference to the current instance after assignment.
         */
        WebServer& operator=(const WebServer& other) {
            if (this != &other) {
                empty = other.empty;
                if (other.request) {
                    request = other.request;
                } else {
                    request = nullptr;
                }
            }
            return *this;
        }

        /**
         * @brief Adds a request to the web server.
         *
         * Deletes any existing request and replaces it with the new one.
         * @param request The request to add.
         */
        void addRequest(Request request) {
            this->request = &request;
            empty = false;
        }

        /**
         * @brief Removes the current request from the web server.
         *
         * Deletes the current request and sets the server to empty.
         */
        void removeRequest() {
            request = nullptr;
            empty = true;
        }

        /**
         * @brief Retrieves the current request.
         *
         * @return Reference to the current request.
         */
        Request& getRequest() {
            return *request;
        }

        /**
         * @brief Checks if the web server is empty.
         *
         * @return True if the web server is empty, false otherwise.
         */
        bool isEmpty() {
            return empty;
        }
};
