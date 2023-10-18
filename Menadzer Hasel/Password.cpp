//
// Created by Julia on 14/06/2022.
//

#include <sstream>
#include "Password.h"

int Password::getNumber() const {
    return number;
}

const string &Password::getName() const {
    return name;
}

const string &Password::getPassword() const {
    return password;
}

const string &Password::getCategory() const {
    return category;
}

const string &Password::getWebsite() const {
    return website;
}

const string &Password::getLogin() const {
    return login;
}

void Password::showCodedInfo() {
    cout << count << " " << name + " " + password + " " + category + " " + website + " " + login;
}





