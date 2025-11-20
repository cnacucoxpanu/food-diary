#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <vector>

class FileUtils {
public:
    FileUtils();
    ~FileUtils();
    
    static bool fileExists(const std::string& filename);
    static std::vector<std::string> readLines(const std::string& filename);
    static bool writeLines(const std::string& filename, const std::vector<std::string>& lines);
    static std::string getDataPath(const std::string& filename);
};

#endif