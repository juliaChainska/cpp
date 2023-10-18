#include <iostream>
#include "Password.h"
#include "PasswordCoder.h"
#include "Timestamp.h"
#include <vector>
#include <fstream>
#include <sstream>
//namespace fs = std::filesystem;



void displayMenu() {
    cout << "=========Menu=========" << endl;
    cout << "1) Wyszukaj hasla" << endl;
    cout << "2) Posortuj hasla" << endl;
    cout << "3) Dodaj haslo" << endl;
    cout << "4) Edytuj haslo" << endl;
    cout << "5) Usun haslo" << endl;
    cout << "6) Dodaj kategorie" << endl;
    cout << "7) Usun kategorie" << endl;
    cout << "======================" << endl;
}

string chooseFileToLoad() {

    string filePath;
    //while (true) {
        cout << "Wybierz plik ktory chcesz odszyfrowac" << endl;
        cout << "1) hasla1.txt" << endl;
        cout << "2) hasla2.txt" << endl;
        cout << "3) wprowadz wlasna sciezke do pliku" << endl;
        int in;
        cin >> in;
        switch (in) {
            case 1:
                filePath = "hasla1.txt";
                break;
            case 2:
                filePath = "hasla2.txt";
                break;
            case 3:
                cout << "Wprowadz sciezke: ";
                cin >> filePath;
                break;
            default:
                cout << "Wprowadziles zla wartosc" << endl;
                break;
        }
        return filePath;
    }

void writeToFile2(const vector<Password>& passwordVec, int klucz, Timestamp t,string filePath) {

    t.loadTimeStamp();
    string hour = t.getHour();
    string minute = t.getMinute();
    string second = t.getSecond();

    bool badPass;
    if (klucz == 5) badPass = false;
    else badPass = true;

    fstream file2;
    file2.open(filePath, ios::out);
    if (!file2.good()) {
        cout << "Wystapil blad podczas zapisu pliku";
        return;
    } else {
        int lineCounter = 1;
        string tempLine;
        string line;
        int num;
        if (!badPass) num = 5;
        else if (badPass) num = 7;
        for (auto password: passwordVec) {
            tempLine = password.name;
            if (lineCounter == 11)line += hour;
            else if (lineCounter == 22)line += minute;
            else if (lineCounter == 33)line += second;
            //reverse(tempLine.begin(), tempLine.end());
            for (int i = 0; i < tempLine.length(); i++) {
                line += int(tempLine[i] + num);
            }
            file2 << line << endl;
            lineCounter++;
            line = "";
            tempLine = password.password;
            if (lineCounter == 11)line += hour;
            else if (lineCounter == 22)line += minute;
            else if (lineCounter == 33)line += second;
            for (int i = 0; i < tempLine.length(); i++) {
                line += int(tempLine[i] + num);
            }
            file2 << line << endl;
            lineCounter++;
            line = "";
            tempLine = password.category;
            if (lineCounter == 11)line += hour;
            else if (lineCounter == 22)line += minute;
            else if (lineCounter == 33)line += second;
            for (int i = 0; i < tempLine.length(); i++) {
                line += int(tempLine[i] + num);
            }
            if (password.website == "" and password.login == "") {
                line += ' ';
                file2 << line << endl;
                line = "";
                lineCounter++;
            } else {
                file2 << line << endl;
                line = "";
                lineCounter++;
            }
            if (password.website.length() > 0) {
                tempLine = password.website;
                if (lineCounter == 11)line += hour;
                else if (lineCounter == 22)line += minute;
                else if (lineCounter == 33)line += second;
                for (int i = 0; i < tempLine.length(); i++) {
                    line += int(tempLine[i] + num);
                }
                if (password.website != "" and password.login == "") {
                    line += ' ';
                    file2 << line << endl;
                    line = "";
                    lineCounter++;
                } else if (password.website != "" and password.login != "") {
                    file2 << line << endl;
                    line = "";
                    lineCounter++;
                }
            }
            if (password.login.length() > 0) {
                tempLine = password.login;
                if (lineCounter == 11)line += hour;
                else if (lineCounter == 22)line += minute;
                else if (lineCounter == 33)line += second;
                for (int i = 0; i < tempLine.length(); i++) {
                    line += int(tempLine[i] + num);
                }
                if (password.login != "") {
                    line += ' ';
                    file2 << line << endl;
                    lineCounter++;
                    line = "";
                }

            }
        }
        if (lineCounter < 34) {
            bool flag = false;
            while (!flag) {
                if (lineCounter == 11) { file2 << hour; }
                else if (lineCounter == 22)file2 << minute;
                else if (lineCounter == 33) {
                    file2 << second;
                    flag = true;
                }
                file2 << endl;
                lineCounter++;
            }
        }
        file2.close();
    }
}

//Password loadFromFile(string line, int lineCounter, Password password, vector<Password>& passwordVec, int number) {
//    string tempLine;
//    bool last = false;
//    int i = 0;
//    if (lineCounter == 11 || lineCounter == 22 || lineCounter == 33)i=2;
//    for (i ; i < line.length(); i++) {
//        if (int(line[i]) == 32 && i +1  == line.length())
//        {
//            last = true;
//        }
//        else {
//            tempLine += int(line[i] + number);
//        }
//    }
//
//    if (password.name == "") {
//        password.name = tempLine;
//    }
//    else if (password.password == "") {
//        password.password = tempLine;
//    }
//    else if (password.category == "") {
//        password.category = tempLine;
//    }
//    else if (password.website == "") {
//        password.website = tempLine;
//    }
//    else if (password.login == "") {
//        password.login = tempLine;
//    }
//    if (last) {
//        password.count = passwordVec.size() + 1;
//        passwordVec.push_back(password);
//        password.name = "";
//        password.password = "";
//        password.category = "";
//        password.website = "";
//        password.login = "";
//    }
//    return password;
//}

void readFromFile(vector<Password>& passwordVec, Timestamp t,string filePath) {
    string filename(filePath);
    vector<string> lines;
    string line;

    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Nie udalo sie otworzyc pliku - '"
             << filename << "'" << endl;
    }
    Password p;
    while (getline(input_file, line)) {
        lines.push_back(line);
        p.password = line;
        passwordVec.push_back(p);
    }

    input_file.close();
}


int main() {

    vector<Password> passwordVec;
    vector<Password> passwordVecUncoded;
    vector<string> categoryVec;

    Timestamp tt;

    string pass;
    cout << "Podaj haslo do pliku: " << endl;
    cin >> pass;
    int klucz;
    if(pass=="123") klucz = 5;
    else klucz = 7;

    chooseFileToLoad();
    string filePath = chooseFileToLoad();
    //std::filesystem::path filePath = std::filesystem::current_path().parent_path();
    readFromFile(passwordVec,tt, filePath);
    tt.loadTimeStamp();


    PasswordCoder ps(klucz,passwordVec,categoryVec,tt,filePath);

    displayMenu();

    int choice;
    cin >> choice;

    bool end = false;
    int count = 1;


    while(!end) {
        switch (choice) {
            case 1:
                ps.search(passwordVec, klucz);
                break;
            case 2:
                ps.sortPass(passwordVec,klucz);
                break;
            case 3:
                cout << "Ile hasel chcesz dodac?: ";
                cin >> count;
                while (count > 0) {
                    ps.addPassword(passwordVec, klucz);
                    writeToFile2(passwordVec, klucz, tt, filePath);
                    count--;
                }
                break;
            case 4:
                ps.editPass(passwordVec, klucz);
                writeToFile2(passwordVec, klucz, tt,filePath);
                break;
            case 5:
                ps.removePassword(passwordVec,categoryVec,klucz);
                writeToFile2(passwordVec, klucz, tt,filePath);
                break;
            case 6:
                ps.addCategory(passwordVec, categoryVec);
                break;
            case 7:
                ps.removeCat(passwordVec, categoryVec, klucz);
                break;
            default:
                cout << "Błędna liczba" << endl;
                break;
        }

        cout << "Koniec programu?" << '\n' << "'tak' lub 'nie'" << endl;
        string ch;
        cin >> ch;
        if(ch=="tak"){
            end = true;
        } else {
            end = false;
            displayMenu();
            cin >> choice;
        }
    }

}




