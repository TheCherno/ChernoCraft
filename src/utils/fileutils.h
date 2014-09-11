#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class FileUtils {
public:
    static std::string read_file(const char *filename) {
        std::string result;
        std::ifstream stream(filename, std::ios::in);
        if (!stream.good()) {
            std::cerr << "File '" << filename << "' doesn't exist!" << std::endl;
            return NULL;
        }
        if (!stream.is_open()) {
            throw new std::runtime_error("Could not read file: " + std::string(filename));
        }
        std::string line = "";
        while (!stream.eof()) {
            std::getline(stream, line);
            result += line + "\n";
        }
        #ifdef DEBUG
            std::cout << "Loaded file: '" << filename << "'" << std::endl;
        #endif
        stream.close();
        return result;
    }
};
