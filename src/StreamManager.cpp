#include "StreamManager.h"
#include "InterpreterException.h"

StreamManager::StreamManager(StreamManager&& other) noexcept
    : inputStream(other.inputStream), outputStream(other.outputStream),
      ownsInput(other.ownsInput), ownsOutput(other.ownsOutput) {
    other.inputStream = &std::cin;
    other.outputStream = &std::cout;
    other.ownsInput = false;
    other.ownsOutput = false;
}

StreamManager& StreamManager::operator=(StreamManager&& other) noexcept {
    if (this != &other) {
        cleanup();
        inputStream = other.inputStream;
        outputStream = other.outputStream;
        ownsInput = other.ownsInput;
        ownsOutput = other.ownsOutput;
        other.inputStream = &std::cin;
        other.outputStream = &std::cout;
        other.ownsInput = false;
        other.ownsOutput = false;
    }
    return *this;
}

void StreamManager::setInputStream(std::istream* stream, bool owns)
{
    if (ownsInput && inputStream != &std::cin) delete inputStream;
    inputStream = stream;
    ownsInput = owns;
}

void StreamManager::setOutputStream(std::ostream* stream, bool owns)
{
    if (ownsOutput && outputStream != &std::cout) delete outputStream;
    outputStream = stream;
    ownsOutput = owns;
}

void StreamManager::setInputFile(const std::string& filename) {
    std::ifstream* file = new std::ifstream(filename);

    if (!file->is_open()) {
        delete file;
        throw FileError("File not found or cannot be opened", filename);
    }

    setInputStream(file, true);
}

void StreamManager::setInputString(const std::string& str) {
    std::stringstream* ss = new std::stringstream(str);
    setInputStream(ss, true);
}

void StreamManager::setOutputFile(const std::string& filename, bool append) {
    std::ios_base::openmode mode = std::ios::out;
    if (append) mode |= std::ios::app;
    else        mode |= std::ios::trunc;

    std::ofstream* file = new std::ofstream(filename, mode);

    if (!file->is_open()) {
        delete file;
        throw FileError("Cannot open file for writing", filename);
    }

    setOutputStream(file, true);
}

void StreamManager::cleanup()
{
    if (ownsInput && inputStream != &std::cin) {
        delete inputStream;
        inputStream = &std::cin;
        ownsInput = false;
    }
    if (ownsOutput && outputStream != &std::cout) {
        delete outputStream;
        outputStream = &std::cout;
        ownsOutput = false;
    }
}