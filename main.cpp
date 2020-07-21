#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <string>
#include <windows.h>

using namespace std;

struct Uzytkownik {
    int id;
    string imie, nazwisko, telefon, email, adres;
};

vector<Uzytkownik> wczytajOsobyZPliku(vector<Uzytkownik> uzytkownicy) {
    string linia, idString;
    fstream plik;
    vector<Uzytkownik>kontakty;
    Uzytkownik wczytanyKontakt;

    plik.open("baza danych.txt", ios::in);

    if(plik.good()==false)
        cout<<"Nie mozna otworzyc pliku!"<<endl;

    while(getline(plik, linia)) {
        stringstream ss(linia);
        getline(ss, idString, '|');
        wczytanyKontakt.id = stoi(idString);
        getline(ss, wczytanyKontakt.imie, '|');
        getline(ss, wczytanyKontakt.nazwisko, '|');
        getline(ss, wczytanyKontakt.telefon, '|');
        getline(ss, wczytanyKontakt.email, '|');
        getline(ss, wczytanyKontakt.adres, '|');
        kontakty.push_back(wczytanyKontakt);
    }
    plik.close();
    return kontakty;
}

vector<Uzytkownik> wprowadzNowegoPrzyjaciela (vector<Uzytkownik>uzytkownicy, int &iloscUzytkownikow) {
    system("cls");
    fstream plik;
    Uzytkownik nowyKontakt;
    nowyKontakt.id = uzytkownicy.back().id+1;
    cout << "Prosze o podanie danych dotyczacych twojego nowego przyjaciela :)" << endl;
    cout << "Podaj imie: ";
    cin >> nowyKontakt.imie;
    cout << "Podaj nazwisko: ";
    cin >> nowyKontakt.nazwisko;
    cout << "Podaj telefon: ";
    cin >> nowyKontakt.telefon;
    cout << "Podaj adres e-mail: ";
    cin >> nowyKontakt.email;
    cout << "Podaj adres:";
    cin.sync();
    getline(cin, nowyKontakt.adres);
    uzytkownicy.push_back(nowyKontakt);

    plik.open("baza danych.txt",ios::out | ios::app);

    plik<<nowyKontakt.id <<"|";
    plik<<nowyKontakt.imie<<"|";
    plik<<nowyKontakt.nazwisko<<"|";
    plik<<nowyKontakt.telefon<<"|";
    plik<<nowyKontakt.email<<"|";
    plik<<nowyKontakt.adres<<"|"<<endl;

    plik.close();
    cout << "Nowy kontakt zostal zapisany." << endl;
    Sleep(2000);
    system("cls");
    iloscUzytkownikow++;

    return uzytkownicy;
}

void wczytajPoImieniu(vector<Uzytkownik>uzytkownicy) {
    system("cls");
    int liczbaWyszukanychOsob =0;
    string imie;
    cout << "Podaj szukane imie: ";
    cin >> imie;
    cout << endl;

    for (int licznik = 0; licznik < uzytkownicy.size(); licznik++) {
        if (uzytkownicy[licznik].imie == imie) {
            cout<<uzytkownicy[licznik].id <<endl;
            cout<<uzytkownicy[licznik].imie<<endl;
            cout<<uzytkownicy[licznik].nazwisko<<endl;
            cout<<uzytkownicy[licznik].telefon<<endl;
            cout<<uzytkownicy[licznik].email<<endl;
            cout<<uzytkownicy[licznik].adres<<endl<<endl;
            liczbaWyszukanychOsob++;
        }
    }
    if (liczbaWyszukanychOsob == 0) {
        cout << "Nie ma takiego kontaktu!" << endl;
    }
    system("pause");
    system("cls");
}

void wczytajPoNazwisku(vector<Uzytkownik>uzytkownicy) {
    system("cls");
    int liczbaWyszukanychOsob =0;
    string nazwisko;
    cout << "Podaj szukane nazwisko: ";
    cin >> nazwisko;
    cout << endl;

    for (int licznik=0; licznik < uzytkownicy.size(); licznik++) {
        if (uzytkownicy[licznik].nazwisko == nazwisko) {
            cout<<uzytkownicy[licznik].id <<endl;
            cout<<uzytkownicy[licznik].imie<<endl;
            cout<<uzytkownicy[licznik].nazwisko<<endl;
            cout<<uzytkownicy[licznik].telefon<<endl;
            cout<<uzytkownicy[licznik].email<<endl;
            cout<<uzytkownicy[licznik].adres<<endl<<endl;
            liczbaWyszukanychOsob++;
        }
    }
    if (liczbaWyszukanychOsob == 0) {
        cout << "Nie ma takiego kontaktu!" << endl;
    }
    system("pause");
    system("cls");
}


void wyswietlKontakty(vector<Uzytkownik> uzytkownicy, int iloscUzytkownikow) {
    system("cls");
    for (int licznik=0; licznik < uzytkownicy.size(); licznik++) {
        cout << uzytkownicy[licznik].id << endl;
        cout<<uzytkownicy[licznik].imie<<endl;
        cout<<uzytkownicy[licznik].nazwisko<<endl;
        cout<<uzytkownicy[licznik].telefon<<endl;
        cout<<uzytkownicy[licznik].email<<endl;
        cout<<uzytkownicy[licznik].adres<<endl<< endl;
    }
    cout << "Ilosc konaktow w ksiazce adresowej: " << iloscUzytkownikow << endl;
    system("pause");
    system("cls");
}

void usunAdresata(vector<Uzytkownik> uzytkownicy) {
    int idUzytkownika;
    char znak;
    system("cls");
    cout << "Wprowadz id uzytkownika do usuniecia: ";
    cin >> idUzytkownika;
    system("cls");
    cout << "Aby usunac kontakt, wprowadz klawisz t" << endl;
    cin >> znak;
    if (znak == 't') {
        uzytkownicy.erase(
        remove_if(uzytkownicy.begin(), uzytkownicy.end(),[&](Uzytkownik const & uzytkownicy) {
            return uzytkownicy.id == idUzytkownika;
        }),
        uzytkownicy.end());
        ofstream plik("baza danych.txt",ios::out | ios::trunc);
        for(vector<Uzytkownik>::const_iterator licznik = uzytkownicy.begin(); licznik!=uzytkownicy.end(); ++licznik) {
            plik << (*licznik).id << "|";
            plik << (*licznik).imie << "|";
            plik << (*licznik).nazwisko << "|";
            plik << (*licznik).telefon << "|";
            plik << (*licznik).email << "|";
            plik << (*licznik).adres << "|" << endl;
        }
        plik.close();
        cout << "Uzytkownik o podanym id zostal usuniety !";
        Sleep(2000);
        system("cls");
    } else {
        cout << "Usuniecie kontaktu zostalo anulowane.";
        Sleep(2000);
        system("cls");
    }
}

void modyfikujKontakt(vector <Uzytkownik> uzytkownicy, int numerId, char wybor) {
    string noweImie,noweNazwisko,nowyTelefon,nowyAdres,nowyEmail;
    vector <Uzytkownik>::iterator it;
    auto iter = find_if(uzytkownicy.begin(),uzytkownicy.end(),[&](Uzytkownik const &uzytkownicy) {
        return uzytkownicy.id == numerId;
    });
    if(wybor == '1') {
        cout << "Podaj nowe imie: "; cin>>noweImie;
        if(iter != uzytkownicy.end()) (*iter).imie = noweImie;
    } else if (wybor == '2') {
        cout << "Podaj nowe nazwisko: "; cin>>noweNazwisko;
        if(iter != uzytkownicy.end()) (*iter).nazwisko = noweNazwisko;
    } else if (wybor == '3') {
        cout << "Podaj nowy numer telefonu: "; cin>>nowyTelefon;
        if(iter != uzytkownicy.end()) (*iter).telefon = nowyTelefon;
    } else if (wybor == '4') {
        cout << "Podaj nowy adres email: "; cin>>nowyEmail;
        if(iter != uzytkownicy.end()) (*iter).email = nowyEmail;
    } else if (wybor == '5') {
        cout << "Podaj nowe adres: "; getline(cin, nowyAdres);
        if(iter != uzytkownicy.end()) (*iter).adres = nowyAdres;
    }
    ofstream plik("baza danych.txt",ios::out | ios::trunc);
    for(vector<Uzytkownik>::const_iterator licznik = uzytkownicy.begin(); licznik!=uzytkownicy.end(); ++licznik) {
        plik << (*licznik).id << "|";
        plik << (*licznik).imie << "|";
        plik << (*licznik).nazwisko << "|";
        plik << (*licznik).telefon << "|";
        plik << (*licznik).adres << "|";
        plik << (*licznik).email << "|" << endl;
    }
    plik.close();
    cout << "Edycja przebiegla pomyslnie !";
    Sleep(2000);
    system("cls");
}

int main() {
    vector<Uzytkownik> uzytkownicy;
    char wybor, wybor1;
    int nrId;
    while(1) {
        uzytkownicy = wczytajOsobyZPliku(uzytkownicy);
        int idUzytkownika= uzytkownicy.size();
        int iloscUzytkownikow = uzytkownicy.size();
        idUzytkownika = iloscUzytkownikow;
        cout << "Ilosc wczytanych uzytkownikow: "<< iloscUzytkownikow << endl;
        system("pause");
        system("cls");
        cout << "KSIAZKA ADRESOWA" << endl;
        cout << "1.Dodaj adresata" << endl;
        cout << "2.Wyszukaj po imieniu" << endl;
        cout << "3.Wyszukaj po nazwisku" << endl;
        cout << "4.Wyswietl wszystkich adresatow" << endl;
        cout << "5.Usun adresata" << endl;
        cout << "6.Edytuj adresata" << endl;
        cout << "9.Zakoncz program" << endl;
        cout << "Twoj wybor: ";
        cin >> wybor;

        if (wybor == '1') {
            uzytkownicy = wprowadzNowegoPrzyjaciela(uzytkownicy,iloscUzytkownikow);
        } else if (wybor == '2') {
            wczytajPoImieniu(uzytkownicy);
        } else if (wybor == '3') {
            wczytajPoNazwisku(uzytkownicy);
        } else if (wybor == '4') {
            wyswietlKontakty(uzytkownicy, iloscUzytkownikow);
        } else if (wybor == '5') {
            usunAdresata(uzytkownicy);
        } else if (wybor == '6') {
            system("cls");
            cout << "Wprowadz numer id kontaktu do edycji: ";
            cin >> nrId;
            system("cls");
            cout << "Wybierz dane, ktore chcesz zmienic: " << endl;
            cout << "1 - imie" << endl;
            cout << "2 - nazwisko" << endl;
            cout << "3 - numer telefonu" << endl;
            cout << "4 - email" << endl;
            cout << "5 - adres" << endl;
            cout << "6 - powrot do menu" << endl;
            cout << "Twoj wybor: ";
            cin >> wybor1;
            if (wybor1 == '1') {
                modyfikujKontakt(uzytkownicy, nrId, wybor1);
            } else if (wybor1 == '2') {
                modyfikujKontakt(uzytkownicy, nrId, wybor1);
            } else if (wybor1 == '3') {
                modyfikujKontakt(uzytkownicy, nrId, wybor1);
            } else if (wybor1 == '4') {
                modyfikujKontakt(uzytkownicy, nrId, wybor1);
            } else if (wybor1 == '5') {
                modyfikujKontakt(uzytkownicy, nrId, wybor1);
            } else if (wybor1 == '6') {
                system("cls");
                exit(1);
            }
        } else if (wybor == '9') {
            system("cls");
            exit(0);
        }
    }
    return 0;
}
