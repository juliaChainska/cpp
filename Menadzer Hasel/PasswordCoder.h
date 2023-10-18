//
// Created by Julia on 14/06/2022.
//

#ifndef PROJEKTC4_PASSWORDCODER_H
#define PROJEKTC4_PASSWORDCODER_H
#include <string>
#include <vector>
#include <fstream>
#include "Password.h"
#include "Timestamp.h"

using namespace std;

class PasswordCoder {
private:
    int klucz;
    vector<Password> passwordVec;
    vector<string> categoryVec;
    Timestamp t;
    string filePath;
public:
    PasswordCoder(int klucz, const vector<Password> &passwordVec, const vector<string> &categoryVec, const Timestamp &t,
                  const string &filePath);
    PasswordCoder(int klucz, const vector<Password> &passwordVec, const vector<string> &categoryVec);



public:
    static inline int sprawdz(char znak);

    void szyfruj(int klucz, string &tab);

    static bool isNumber(string text);

    void displayPasswords(vector<Password> &passwordVec, int klucz);
    //void displayPasswords2();

    void displayPasswordsUncoded(vector<Password> &passwordVec);

    void search(vector<Password> &passwordVec, int klucz);

    void displayCat(vector<string> &categoryVec);

    void addToPasswordCoded(Password &password, vector<Password> &passwordVec);

    void addToPasswordDecoded(vector<Password> &passwordVec);

    void editPass(vector<Password> &passwordVec, int klucz);

    void addCategory(vector<Password>&passwordVec,vector<string>& categoryVec);

    void removeCat(vector<Password>& passwordVec, vector<string>& categoryVec, int klucz);

    void addPassword(vector<Password> &passwordVec, int klucz);

    void addToVec(vector<Password>& passwordVec, Password passToAdd);

    void removePassword(vector<Password>& passwordVec,vector<string>&categoryVec, int klucz);

    void passwordDetails(vector<string>& categoryVec, vector<Password>& passwordVec, Password& password, int klucz);

    void sortPass(vector<Password>& passwordVec, int klucz);

    int compareStr(string str1, string str2);
};


#endif //PROJEKTC4_PASSWORDCODER_H
