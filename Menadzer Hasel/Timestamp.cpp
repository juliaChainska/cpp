//
// Created by Julia on 18/06/2022.
//

#include "Timestamp.h"
#include <string>

using namespace std;

string Timestamp::getTimestamp() {
    time_t localtime;
    string timestamp;
    time(&localtime);
    char buffer[26];
    ctime_r(&localtime, buffer);
    for (int i = 0; i < 19; i++) {
        timestamp += buffer[i];
    }
    return timestamp;
}

const string &Timestamp::getHour() const {
    return hour;
}

const string &Timestamp::getMinute() const {
    return minute;
}

const string &Timestamp::getSecond() const {
    return second;
}


