//
// Created by Julia on 18/06/2022.
//

#ifndef PROJEKTC4_TIMESTAMP_H
#define PROJEKTC4_TIMESTAMP_H
#include <string>
#include <iostream>

using namespace std;



class Timestamp {
    string hour;
    string minute;
    string second;

    string getTimestamp();

public:
    void loadTimeStamp(){

        string timestamp = getTimestamp();
        hour.push_back(timestamp[11]);
        hour.push_back(timestamp[12]);
        minute.push_back(timestamp[14]);
        minute.push_back(timestamp[15]);
        second.push_back(timestamp[17]);
        second.push_back(timestamp[18]);


    }

    const string &getHour() const;

    const string &getMinute() const;

    const string &getSecond() const;
};


#endif //PROJEKTC4_TIMESTAMP_H
