#include "../../header.h"

FileUtils::FileUtils() {}

FileUtils::~FileUtils() {}

bool FileUtils::fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

std::vector<std::string> FileUtils::readLines(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw FileNotFoundException(filename);
    }
    
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    
    file.close();
    return lines;
}

bool FileUtils::writeLines(const std::string& filename, const std::vector<std::string>& lines) {
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        return false;
    }
    
    for (const auto& line : lines) {
        file << line << "\n";
    }
    
    file.close();
    return true;
}

std::string FileUtils::getDataPath(const std::string& filename) {
    return std::string(DATA_PATH) + filename;
}