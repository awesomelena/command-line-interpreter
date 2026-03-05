#ifndef CLI_STREAMMANAGER_H
#define CLI_STREAMMANAGER_H

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

class StreamManager {
public:
    StreamManager() : inputStream(&std::cin), outputStream(&std::cout), ownsInput(false), ownsOutput(false) {}

    ~StreamManager() { cleanup(); }

    StreamManager(const StreamManager&) = delete;
    StreamManager& operator=(const StreamManager&) = delete;

    StreamManager(StreamManager&& other) noexcept;
    StreamManager& operator=(StreamManager&& other) noexcept;

    void setInputStream(std::istream* stream, bool owns = false);
    void setOutputStream(std::ostream* stream, bool owns = false);
    void setInputFile(const std::string& filename);
    void setInputString(const std::string& str);
    void setOutputFile(const std::string& filename, bool append);

    bool isConsoleInput() const {return inputStream == &std::cin;}

    std::istream& getInputStream() const { return *inputStream; }
    std::ostream& getOutputStream() const { return *outputStream; }

    void cleanup();

private:
    std::istream* inputStream;
    std::ostream* outputStream;
    bool ownsInput;
    bool ownsOutput;
};

#endif //CLI_STREAMMANAGER_H