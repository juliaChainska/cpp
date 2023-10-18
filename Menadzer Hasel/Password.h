//
// Created by Julia on 14/06/2022.
//

#ifndef PROJEKTC4_PASSWORD_H
#define PROJEKTC4_PASSWORD_H
#include <string>
#include <iostream>

using namespace std;


class Password {
public:
    int count;
    int number;
    string name;
    string password;
    string category;
    string website;
    string login;



public:
    int getNumber() const;

    const string &getName() const;

    const string &getPassword() const;

    const string &getCategory() const;

    const string &getWebsite() const;

    const string &getLogin() const;

    void showCodedInfo();


};


#endif //PROJEKTC4_PASSWORD_H
