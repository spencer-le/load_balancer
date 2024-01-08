#include <string>
#include <random>
#include <sstream>

/** 
 * @brief Class representing a network request.
 *
 * The Request class models a network request with input and output IP addresses,
 * a time stamp, and a task duration.
 */
class Request {
    public:
        std::string ipIn; ///< Input IP address.
        std::string ipOut; ///< Output IP address.
        int time; ///< Time associated with the request.
        int taskDuration; ///< Duration of the task.

        /**
         * @brief Default constructor.
         *
         * Initializes a new Request instance with random IP addresses and time.
         */
        Request() { 
            std::random_device rd;
            std::default_random_engine engine(rd());

            ipIn = generateRandomIP(engine);
            ipOut = generateRandomIP(engine);
            std::uniform_int_distribution<int> dist(1, 100);
            time = dist(engine);
            taskDuration = time;
        }

        /**
         * @brief Parameterized constructor.
         *
         * @param ipIn The input IP address.
         * @param ipOut The output IP address.
         * @param time The time associated with the request.
         */
        Request(const std::string& ipIn, const std::string& ipOut, int time)
            : ipIn(ipIn), ipOut(ipOut), time(time), taskDuration(time) { // Initialize taskDuration with time
        }

        /**
         * @brief Constructor with range for random time.
         *
         * @param start The start of the range for the random time.
         * @param end The end of the range for the random time.
         */
        Request(int start, int end) { // Initialize taskDuration with time
            std::random_device rd;
            std::default_random_engine engine(rd());

            ipIn = generateRandomIP(engine);
            ipOut = generateRandomIP(engine);
            std::uniform_int_distribution<int> dist(start, end);
            time = dist(engine);
            taskDuration = time;
        }

        /**
         * @brief Destructor.
         */
        ~Request() {
            // Destructor
        }
        
        /**
         * @brief Copy constructor.
         *
         * @param other The Request object to copy from.
         */
        Request(const Request& other) {
            // Copy constructor
            ipIn = other.ipIn;
            ipOut = other.ipOut;
            time = other.time;
            taskDuration = other.taskDuration; // Added assignment for taskDuration
        }

        /**
         * @brief Copy assignment operator.
         *
         * @param other The Request object to assign from.
         * @return Reference to the current object.
         */
        Request& operator=(const Request& other) {
            // Copy assignment operator
            if (this != &other) {
                ipIn = other.ipIn;
                ipOut = other.ipOut;
                time = other.time;
                taskDuration = other.taskDuration; // Added assignment for taskDuration
            }
            return *this;
        }

    private:
        /**
         * @brief Generates a random IP address.
         *
         * @param engine The random number engine to use.
         * @return A randomly generated IP address.
         */
        std::string generateRandomIP(std::default_random_engine& engine) {
            std::uniform_int_distribution<int> dist(0, 255);
            std::stringstream ipStream;
            
            for (int i = 0; i < 4; ++i) {
                ipStream << dist(engine);
                if (i < 3) ipStream << ".";
            }

            return ipStream.str();
        }
};
