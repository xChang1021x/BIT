#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>
#include <string>
#include <map>
#include <vector>

struct Config {
    int localPort;
    std::string remoteIP;
    int remotePort;
    int dataSize;
    int windowSize;
    int timeout; // in milliseconds
    double errorRate; // percentage
    double lossRate; // percentage
    std::string fileToSend;
    std::string fileToReceive;
};

Config readConfig(const std::string& filename) {
    Config config{};
    std::ifstream file(filename);
    std::string line;
    std::map<std::string, std::string> params;
    while (std::getline(file, line)) {
        size_t pos = line.find('=');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            params[key] = value;
        }
    }
    config.localPort = std::stoi(params["LocalPort"]);
    config.remoteIP = params["RemoteIP"];
    config.remotePort = std::stoi(params["RemotePort"]);
    config.dataSize = std::stoi(params["DataSize"]);
    config.windowSize = std::stoi(params["WindowSize"]);
    config.timeout = std::stoi(params["Timeout"]);
    config.errorRate = std::stod(params["ErrorRate"]) / 100.0;
    config.lossRate = std::stod(params["LossRate"]) / 100.0;
    config.fileToSend = params["FileToSend"];
    config.fileToReceive = params["FileToReceive"];
    return config;
}

class Logger {
public:
    Logger(const std::string& logFileName) : logFile(logFileName, std::ios::app), running(true) {
        if (!logFile) {
            throw std::runtime_error("Cannot open log file");
        }
        loggingThread = std::thread(&Logger::loggingFunction, this);
    }

    ~Logger() {
        stop();
    }

    void log(const std::string& message) {
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            logQueue.push(message);
        }
        cv.notify_one();
    }

    void stop() {
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            running = false;
        }
        cv.notify_one();
        if (loggingThread.joinable()) {
            loggingThread.join();
        }
    }

private:
    std::ofstream logFile;
    std::queue<std::string> logQueue;
    std::mutex queueMutex;
    std::condition_variable cv;
    std::thread loggingThread;
    bool running;

    void loggingFunction() {
        while (running || !logQueue.empty()) {
            std::vector<std::string> batch;
            {
                std::unique_lock<std::mutex> lock(queueMutex);
                cv.wait(lock, [this]{ return !logQueue.empty() || !running; });
                while (!logQueue.empty()) {
                    batch.push_back(logQueue.front());
                    logQueue.pop();
                }
            }
            for (const auto& msg : batch) {
                logFile << msg << std::endl;
            }
            logFile.flush(); // Ensure logs are written immediately
        }
    }
};

#endif // UTILS_H