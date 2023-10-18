////
//// Created by Julia on 14/06/2022.
////

#include <sstream>
#include <fstream>
#include "PasswordCoder.h"
#include "Password.h"
#include "Timestamp.h"


int PasswordCoder::sprawdz(char znak) {
    //jesli jest mala litera
    if(znak >= 'a' && znak <= 'z') return 0;
    //jesli jest duza litera
    if(znak >= 'A' && znak <= 'Z') return 1;
    //inna niż litera
    return 2;
}

void PasswordCoder::szyfruj(int klucz, string &tab) {
    //sprawdzenie, czy klucz miesci sie w zakresie
    if(!(klucz >= -26 && klucz <= 26)) return;

    int pom;
    char a, z;

    for(int i = 0; i < tab.size(); i++)
    {
        pom = sprawdz(tab[i]);
        //ustalienie wielkosci litery
        if(pom < 2)
        {
            if(pom == 0)
                a = 'a', z = 'z';
            else
                a = 'A', z = 'Z';

            if(klucz >= 0)

                if(tab[i] + klucz <= z)
                    tab[i] += klucz;
                else
                    tab[i] = tab[i] + klucz - 26;
            else
            if(tab[i] + klucz >= a)
                tab[i] += klucz;
            else
                tab[i] = tab[i] + klucz + 26;
        }
    }
}

bool PasswordCoder::isNumber(string text) {
    for (char c : text) {
        if (isdigit(c) == 0) return false;
    }
    return true;
}

PasswordCoder::PasswordCoder(int klucz, const vector<Password> &passwordVec, const vector<string> &categoryVec) : klucz(
        klucz), passwordVec(passwordVec), categoryVec(categoryVec) {}

void PasswordCoder::displayPasswords(vector<Password> &passwordVec, int klucz) {
    cout << "------info--------" << endl;
    for (auto password : passwordVec) {
        cout << "Numer: " << password.count << endl;

        cout << "Nazwa: ";
        string tempName = password.name;
        szyfruj(-klucz,tempName);
        cout << tempName << endl;

        cout << "Haslo: ";
        string tempPass = password.password;
        szyfruj(-klucz,tempPass);
        cout << tempPass << endl;

        cout << "Kategoria: ";
        string tempCat = password.category;
        szyfruj(-klucz,tempCat);
        cout << tempCat << endl;

        if (password.website != "--"){
            cout << "Strona: ";
            string tempWeb = password.website;
            szyfruj(-klucz,tempWeb);
            cout << tempWeb << endl;
        }

        if (password.login != "--"){
            cout << "Login: ";
            string tempLog = password.login;
            szyfruj(-klucz,tempLog);
            cout << tempLog << endl;
        }
        cout << "--------------" << endl;
    }
}

void PasswordCoder::search(vector<Password> &passwordVec, int klucz) {
    string phrase;
    vector<Password> tempVec;
    cout << "Wpisz po czym chcesz wyszukać: ";
    cin >> phrase;
    bool number = isNumber(phrase);

    for (auto password: passwordVec) {
        string name = password.name;
        szyfruj(-klucz, name);

        string login = password.login;
        szyfruj(-klucz, login);

        string haslo = password.password;
        szyfruj(-klucz, haslo);

        string cat = password.category;
        szyfruj(-klucz, cat);

        string web = password.website;
        szyfruj(-klucz, web);

        if (number) {
            int num;
            stringstream ss3;
            ss3 << phrase;
            ss3 >> num;
            if (num == password.count)tempVec.push_back(password);
        } else if (phrase == name || phrase == login || phrase == haslo || phrase == web || phrase == cat) {
            tempVec.push_back(password);
        }

        displayPasswords(tempVec,klucz);
    }
}

void PasswordCoder::addToPasswordCoded(Password &password,vector<Password> &passwordVec) {

    cout << "=======DODAWANIE=HASLA=======" << endl;
    cout << "1) Wpisz haslo reczenie" << endl;
    cout << "2) Wygeneruj haslo" << endl;
    string choice;
    cin >> choice;
    if (choice == "1" or choice == "2") {
    password.count = passwordVec.size() + 1;
    cout << "Podaj nazwę: ";
    string name;
    cin >> name;
    szyfruj(5,name);
    password.name = name;

        if (choice == "1") {
            cout << "Podaj haslo: ";
            string haslo;
            cin >> haslo;
            szyfruj(5, haslo);
            password.password = haslo;

        } else {
            int charsAmmount;
            string upperCaseChars;
            string specialSigns;
            cout << "Podaj ilosc znakow: ";
            while (true) {
                cin >> charsAmmount;
                if (charsAmmount >= 5 && charsAmmount <= 40) break;
                else {
                    cout << "Haslo musi zawierac nie mniej niz 5 liter i nie wiecej niz 40, sprobuj ponownie: " << endl;
                    charsAmmount = 0;
                }
            }
            cout << "Czy haslo ma zawierac duze i male litery, wpisz 'tak' lub 'nie': ";
            while (true) {
                cin >> upperCaseChars;
                if (upperCaseChars == "nie" || upperCaseChars == "tak")break;
                else {
                    cout << "Wpisales nieprawidlowa fraze, sprobuj ponownie: " << endl;
                    upperCaseChars = "";
                }
            }
            cout << "Czy haslo ma zawierac znaki specjalne, wpisz 'tak' lub 'nie': ";
            while (true) {
                cin >> specialSigns;
                if (specialSigns == "nie" || specialSigns == "tak")break;
                else {
                    cout << "Wpisales nieprawidlowa fraze, sprobuj ponownie: " << endl;
                    specialSigns = "";
                }
            }
            string pass;
            srand(time(nullptr));
            bool isSpecial = false;
            bool isUpper = false;
            int choice2;
            if (upperCaseChars == "tak" && specialSigns == "tak") {
                for (int i = 0; i < charsAmmount; i++) {
                    if (i ==charsAmmount - 2) {
                        for (int j = 0; j < charsAmmount - 2; j++) {
                            if (pass[j] >= 33 && pass[j] <= 47)isSpecial = true;
                            if (pass[j] >= 65 && pass[j] <= 90) isUpper = true;
                        }
                        if (!isSpecial)pass += char(33 + rand() % 15);
                        choice2 = 1 + rand() % 3;
                        if (choice2 == 1) {
                            pass += char(33 + rand() % 58);
                        }
                        else if (choice2 == 2) {
                            pass += char(97 + rand() % 27);
                        }
                    }
                    else if (i ==charsAmmount - 3) {
                        if (!isUpper)pass += char(33 + rand() % 47);
                        choice2 = 1 + rand() % 3;
                        if (choice2 == 1) {
                            pass += char(33 + rand() % 58);
                        }
                        else if (choice2 == 2) {
                            pass += char(97 + rand() % 27);
                        }
                    }

                    else {
                        choice2 = 1 + rand() % 2;
                        if (choice2 == 1) {
                            pass += char(48 + rand() % 10);
                        }
                        else if (choice2 == 2) {
                            pass += char(97 + rand() % 27);
                        }
                    }
                }
            }
            else if (upperCaseChars == "nie" && specialSigns == "tak") {
                for(int i =0; i<charsAmmount;i++){
                    if (i ==charsAmmount - 2) {
                        for (int j = 0; j < charsAmmount - 2; j++) {
                            if (pass[j]>= 33 && pass[j]<=47)isSpecial = true;
                        }
                        if(!isSpecial)pass += char(33 + rand() % 15);
                        choice2 = 1 + rand() % 2;
                        if (choice2 == 1) {
                            pass += char(97 + rand() % 27);
                        }
                        else if (choice2 == 2) {
                            pass+=char(33 + rand() % 32);
                        }
                    }
                    else {
                        choice2 = 1 + rand() % 2;
                        if (choice2 == 1) {
                            pass += char(97 + rand() % 27);
                        }
                        else if (choice2 == 2) {
                            pass += char(33 + rand() % 32);
                        }
                    }
                }

            }
            else if (upperCaseChars == "tak" && specialSigns == "nie") {
                for (int i = 0; i < charsAmmount; i++) {
                    if (i == charsAmmount - 2) {
                        for (int j = 0; j < charsAmmount - 2; j++) {
                            if (pass[j] >= 65 && pass[j] <= 90)isUpper = true;
                        }
                        if (!isUpper)pass += char(65 + rand() % 26);
                        else {
                            choice2 = 1 + rand() % 3;
                            if (choice2 == 1) {
                                pass += char(97 + rand() % 27);
                            }
                            else if (choice2 == 2) {
                                pass += char(65 + rand() % 26);
                            }
                            else if (choice2 == 3) {
                                pass += char(48 + rand() % 10);
                            }
                        }
                    }
                    else {
                        choice2 = 1 + rand() % 3;
                        if (choice2 == 1) {
                            pass += char(97 + rand() % 27);
                        }
                        else if (choice2 == 2) {
                            pass += char(65 + rand() % 26);
                        }
                        else if (choice2 == 3) {
                            pass += char(48 + rand() % 10);
                        }
                    }
                }
            }
            else if (upperCaseChars == "nie" && specialSigns == "nie") {
                for (int i = 0; i < charsAmmount; i++) {
                    choice2 = 1 + rand() % 2;
                    if (choice2 == 1) {
                        pass += char(48 + rand() % 10);
                    }
                    else if (choice2 == 2) {
                        pass += char(97 + rand() % 27);
                    }
                }
            }
            cout << "Wygenerowane haslo to: " << pass << endl;
            szyfruj(5,pass);
            password.password = pass;
        }

    cout << "Wybierz kategorie: ";
    displayCat(categoryVec);
    string cat;
    cin >> cat;
    szyfruj(5, cat);
    password.category = cat;

    cout << "Podaj stronę (jeśli bez -> wpisz \'nie\'): ";
    string website;
    cin >> website;
    if(website=="nie")password.website = "--";
    else {
        szyfruj(5, website);
        password.website = website;
    }

    cout << "Podaj login (jeśli bez -> wpisz \'nie\'): ";
    string login;
    cin >> login;
    if(login == "nie")password.login = "--";
    else {
        szyfruj(5,login);
        password.login = login;
    }
    }
}

void PasswordCoder::addToPasswordDecoded(vector<Password> &passwordVec) {
}

void PasswordCoder::displayCat(vector<string> &categoryVec) {
    int i = 1;
    for (auto cats : categoryVec) {
        cout << endl;
        cout << i++ << ": ";
        cout << cats << endl;
    }
}

void PasswordCoder::displayPasswordsUncoded(vector<Password> &passwordVec) {
    for (auto password : passwordVec) {
        cout << "Numer: " << password.count << endl;

        cout << "Nazwa: ";
        string tempName = password.name;
        szyfruj(-5,tempName);
        cout << tempName << endl;

        cout << "Haslo: ";
        string tempPass = password.password;
        szyfruj(-5,tempPass);
        cout << tempPass << endl;

        cout << "Kategoria: ";
        string tempCat = password.category;
        szyfruj(-5,tempCat);
        cout << tempCat << endl;

        if (password.website != "--"){
            cout << "Strona: ";
            string tempWeb = password.website;
            szyfruj(-5,tempWeb);
            cout << tempWeb << endl;
        }

        if (password.login != "--"){
            cout << "Login: ";
            string tempLog = password.login;
            szyfruj(-5,tempLog);
            cout << tempLog << endl;
        }
        cout << "--------------" << endl;
    }
}

void PasswordCoder::editPass(vector<Password> &passwordVec, int klucz) {
    displayPasswordsUncoded(passwordVec);
    cout << "Wpisz numer hasla ktore chcesz edytowac: ";
    int num;
    bool isInVec = false;
    while (1) {
        cin >> num;
        for (auto password: passwordVec) {
            if (password.count == num)isInVec = true;
        }
        if (isInVec)break;
        else {
            cout << "Na liscie nie ma tekiego numeru, wprowdz numer ponownie: ";
            num = NULL;
        }
    }
    //while (1) {
    cout << "Wybierz co chcialbys edytowac" << endl;
    cout << "1) Nazwa" << endl;
    cout << "2) Haslo" << endl;
    cout << "3) Kategoria" << endl;
    cout << "4) Strona" << endl;
    cout << "5) Login" << endl;
    cout << "Wpisz numer: ";
    string choice;
    cin >> choice;
    int nr;
    stringstream ss4;
    ss4 << choice;
    ss4 >> nr;
    if (nr == 1) {
        cout << "Wpisz nowa nazwe dla hasla o numerze " << num << " : ";
        string name;
        cin >> name;
        szyfruj(klucz, name);
        for (auto i = passwordVec.begin(); i != passwordVec.end(); i++) {
            if (i->count == num) {
                i->name = name;
            }
        }
        displayPasswordsUncoded(passwordVec);
        cout << "Nazwa hasla zostala pomyslnie zmieniona!" << endl;

    } else if (nr == 2) {
        cout << "Wpisz nowe haslo dla hasla o numerze " << num << " : ";
        string password;
        cin >> password;
        szyfruj(klucz, password);
        for (auto i = passwordVec.begin(); i != passwordVec.end(); i++) {
            if (i->count == num) {
                i->password = password;
            }
        }
        displayPasswordsUncoded(passwordVec);
        cout << "Haslo zostalo pomyslnie zmienione!" << endl;
    } else if (nr == 3) {
        cout << "Wpisz nowa nazwe kategori dla hasla o numerze " << num << " : ";
        string category;
        string prevCat;
        cin >> category;
        szyfruj(klucz, category);
        for (auto i = passwordVec.begin(); i != passwordVec.end(); i++) {
            if (i->count == num) {
                prevCat = i->category;
                i->category = category;
            }
        }
        for (auto i = categoryVec.begin(); i != categoryVec.end(); i++) {
            if (*i == prevCat) {
                *i = category;
            }
        }
        displayPasswordsUncoded(passwordVec);
        cout << "Haslo zostalo pomyslnie zmienione!" << endl;
    } else if (nr == 4) {
        cout << "Wpisz nowa nazwe strony dla hasla o numerze " << num << " : ";
        string webiste;
        cin >> webiste;
        szyfruj(klucz, webiste);
        for (auto i = passwordVec.begin(); i != passwordVec.end(); i++) {
            if (i->count == num) {
                i->website = webiste;
            }
        }
        displayPasswordsUncoded(passwordVec);
        cout << "Nazwa strony zostala pomyslnie zmieniona!" << endl;
    } else if (nr == 5) {
        cout << "Wpisz nowy login dla hasla o numerze " << num << " : ";
        string login;
        cin >> login;
        szyfruj(klucz, login);
        for (auto i = passwordVec.begin(); i != passwordVec.end(); i++) {
            if (i->count == num) {
                i->login = login;
            }
        }
        displayPasswordsUncoded(passwordVec);
        cout << "Login zostala pomyslnie zmieniona!" << endl;
    }


}

void PasswordCoder::addCategory(vector<Password> &passwordVec, vector<string> &categoryVec) {
    string newCategory;
    bool isNewCategory = true;
    cout << "Wpisz nazwe nowej kategori : ";
    while (1) {
        cin >> newCategory;
        for (auto category: categoryVec) {
            if (category == newCategory)isNewCategory = false;
        }
        if (isNewCategory)break;
        else {
            cout << "Taka kategoria juz istnieje, wpisz inna nazwe: ";
            newCategory = "";
            isNewCategory = true;
        }
    }
    categoryVec.push_back(newCategory);
    cout << "Nowa kategoria zostala poprawnie dodana!" << endl;
}

void PasswordCoder::removeCat(vector<Password> &passwordVec, vector<string> &categoryVec, int klucz) {
    cout << "Podaj nazwe kategori ktora chcesz usunac: ";
    displayCat(categoryVec);
    string toRemove;
    bool isInVec = false;
    while (true) {
        cin >> toRemove;
        for (auto cat : categoryVec) {
            if (cat == toRemove)isInVec = true;
        }
        if (isInVec)break;
        else {
            cout << "Nie znaleziono takiej kategori, sprobuj ponownie: ";
            isInVec = false;
            toRemove = "";
        }
    }
    cout << "Czy jestes pewny, ze chcesz to zrobic ? ('tak'/'nie') : ";
    string choice;
    while (true) {
        cin >> choice;
        if (choice == "tak" || choice == "nie") break;
        else {
            choice = "";
            cout << "Wpisales nieprawidlowa wartosc, sprobuj jeszcze raz: ";
        }
    }
    if (choice == "tak") {
        for (auto cat : passwordVec) {
            string temp = cat.category;
            szyfruj(-klucz,temp);
                if(temp==toRemove) {
                    int nr = cat.count;
                    categoryVec.erase(categoryVec.begin()+nr);
                    cout << "Usuwanie kategori zostalo zakonczone pomyslnie!" << endl;
                    displayPasswords(passwordVec, klucz);
                }
        }
    }
    else if (choice == "nie") {
        cout << "Zrezygnowales z usuniecia kategori" << endl;
        displayPasswords(passwordVec, klucz);
    }
}

void PasswordCoder::addPassword(vector<Password> &passwordVec, int klucz) {
    Password p1;
    addToPasswordCoded(p1,passwordVec);
    addToVec(passwordVec,p1);

    cout << "Siła hasła -> " << endl;
    passwordDetails(categoryVec,passwordVec,p1,klucz);
    cout << endl;

}

PasswordCoder::PasswordCoder(int klucz, const vector<Password> &passwordVec, const vector<string> &categoryVec,
                             const Timestamp &t, const string &filePath) : klucz(klucz), passwordVec(passwordVec),
                                                                           categoryVec(categoryVec), t(t),
                                                                           filePath(filePath) {}

void PasswordCoder::addToVec(vector<Password> &passwordVec, Password passToAdd) {
    passwordVec.push_back(passToAdd);
}

void PasswordCoder::removePassword(vector<Password> &passwordVec, vector<string> &categoryVec, int klucz) {
    cout << "Wpisz numer hasła/haseł, które chcesz usunąc" << endl;
    int choice;
    cin >> choice;

    for (auto password: passwordVec) {
        int number = password.count;
        stringstream ss5;
        string nn;
        ss5 << number;
        ss5 >> nn;
        szyfruj(-klucz, nn);
        if (choice == number) {
            cout << "Czy na pewno chcesz usunąć hasło numer: " << number << " ? (wpisz: 'tak' lub 'nie') ";
            string ch;
            cin >> ch;

            if (ch == "tak") {
                passwordVec.erase(passwordVec.begin() + number);
                cout << "Hasło nr: " << number << " usunięto" <<endl;
            }
        }
    }
}

void PasswordCoder::passwordDetails(vector<string> &categoryVec, vector<Password> &passwordVec, Password &password, int klucz) {
    string temp = password.password;
    szyfruj(-klucz, temp);
    int points = 0;
    if (password.password.length() > 7) points++;
    for (char c : temp) {
        if ((c <= 64) && (c >= 33)) {
            points++;
            //break;
        }
    }
    for (char c : temp) {
        if ((c >= 65) && (c <= 90)) {
            points++;
            //break;
        }
    }
    if (points <= 1) cout << "Towje haslo jest slabe" << endl;
    else if (points == 2) cout << "Towje haslo jest srednie" << endl;
    else if (points > 3) cout << "Towje haslo jest mocne" << endl;
}

void PasswordCoder::sortPass(vector<Password> &passwordVec, int klucz) {
    vector<Password> passVecCopy;
    for (int i=0; i<passVecCopy.size(); i++)
        passVecCopy.push_back(passwordVec[i]);

    for (auto password : passVecCopy) {
        szyfruj(-klucz, password.name);
        szyfruj(-klucz, password.password);
        szyfruj(-klucz, password.category);
        szyfruj(-klucz, password.website);
        szyfruj(-klucz, password.login);
    }

    cout << "Wybierz zestaw parametrow po ktorch chcesz posortowac liste hasel" << endl;
    cout << " 1) numer i nazwa" << endl;
    cout << " 2) nazwa i haslo" << endl;
    cout << " 3) haslo i kategoria" << endl;
    cout << " 4) kategoria i strona" << endl;
    cout << " 5) strona i login" << endl;
    cout << " 6) login i numer" << endl;

    string choice;
    stringstream ss6;
    int x;
    ss6 << choice;
    ss6 >> x;

    while (true) {
        cin >> choice;
        ss6 << choice;
        ss6 >> x;
        if (isNumber(choice) && x > 0 && x < 12)break;
        else {
            choice = "";
            cout << "Zla wartosc, sprobuj ponownie ";
        }
    }

    if (choice == "1") {
        sort(passwordVec.begin(), passwordVec.end(), [this](const Password& pass1, const Password& pass2) {
            if (pass1.count != pass2.count)return pass1.count < pass2.count;
            else if (pass1.name != pass2.name) { return compareStr(pass1.name, pass2.name) < 0;
            } else return false;
        });
    }
    else if (choice == "2") {
        sort(passwordVec.begin(), passwordVec.end(), [this](const Password& pass1, const Password& pass2) {
            if (pass1.name != pass2.name)return compareStr(pass1.name, pass2.name) < 0;
            else if (pass1.password != pass2.password)return compareStr(pass1.password, pass2.password) < 0;
            else return false;
        });
    }
    else if (choice == "3") {
        sort(passwordVec.begin(), passwordVec.end(), [this](const Password& pass1, const Password& pass2) {
            if (pass1.password != pass2.password)return compareStr(pass1.password, pass2.password) < 0;
            else if (pass1.category != pass2.category)return compareStr(pass1.category, pass2.category) < 0;
            else return false;
        });
    }
    else if (choice == "4") {
        sort(passwordVec.begin(), passwordVec.end(), [this](const Password& pass1, const Password& pass2) {
            if (pass1.category != pass2.category)return compareStr(pass1.category, pass2.category) < 0;
            else if (pass1.website != pass2.website)return compareStr(pass1.website, pass2.website) < 0;
            else return false;
        });
    }
    else if (choice == "5") {
        sort(passwordVec.begin(), passwordVec.end(), [this](const Password& pass1, const Password& pass2) {
            if (pass1.website != pass2.website)return compareStr(pass1.website, pass2.website) < 0;
            else if (pass1.login != pass2.login)return compareStr(pass1.login, pass2.login) < 0;
            else return false;
        });
    }
    else if (choice == "6") {
        sort(passwordVec.begin(), passwordVec.end(), [this](const Password& pass1, const Password& pass2) {
            if (pass1.login != pass2.login)return compareStr(pass1.login, pass2.login) < 0;
            else if (pass1.number != pass2.number)return pass1.number < pass2.number;
            else return false;
        });
    }
    cout << "Hasla zostaly posortowane" << endl;

    displayPasswords(passVecCopy,klucz);

}

int PasswordCoder::compareStr(string str1, string str2) {
    transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
    transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
    return str1.compare(str2);
}





