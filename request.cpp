#include <string>
#include <random>
#include <sstream>

class Request {
public:
    std::string ipIn;
    std::string ipOut;
    int time;

    Request() {
        std::random_device rd;
        std::default_random_engine engine(rd());

        ipIn = generateRandomIP(engine);
        ipOut = generateRandomIP(engine);
        std::uniform_int_distribution<int> dist(0, 100);
        time = dist(engine);
    }

    Request(const std::string& ipIn, const std::string& ipOut, int time)
        : ipIn(ipIn), ipOut(ipOut), time(time) {
    }

    ~Request() {
        // Destructor
    }

    Request(const Request& other) {
        // Copy constructor
        ipIn = other.ipIn;
        ipOut = other.ipOut;
        time = other.time;
    }

    Request& operator=(const Request& other) {
        // Copy assignment operator
        if (this != &other) {
            ipIn = other.ipIn;
            ipOut = other.ipOut;
            time = other.time;
        }
        return *this;
    }

private:
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
