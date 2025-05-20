//
// Created by sputnik on 5/20/25.
//

#ifndef DEBUG_H
#define DEBUG_H

#include <raylib.h>
#include <string>

#include "../Common.h"

class Logger {
public:
    static void log(const std::string& message) {
        if (isReset) {
            debugString.clear();
            isReset = false;
        }
        debugString.append(message+"\n");
    }

    static void reset() {
        isReset = true;
    }
    static std::string& getString(){ return debugString; }

private:
    static std::string debugString;
    static bool isReset;
};

std::string Logger::debugString;
bool Logger::isReset = false;


#endif //DEBUG_H
