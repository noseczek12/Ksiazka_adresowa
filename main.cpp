#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <string>
#include <windows.h>

using namespace std;

struct Adresat {
    int id, idZalogowanegoUzytkownika;
    string imie, nazwisko, telefon, email, adres;
};

struct Uzytkownik {
    int idUzytkownika;
    string nazwa, haslo;
};

vector<Uzytkownik> wczytajOsobyZPliku(vector<Uzytkownik> uzytkownicy) {
    string linia, idString;
    fstream plik;
    vector<Uzytkownik>kontakty;
    Uzytkownik wczytanyKontakt;

    plik.open("baza uzytkownikow.txt", ios::in);

    if(plik.good()==false)
        cout<<"Nie mozna otworzyc pliku!"<<endl;

    while(getline(plik, linia)) {
        stringstream ss(linia);
        stringstream konwersja;
        getline(ss, idString, '|');
        konwersja << idString;
        konwersja >> wczytanyKontakt.idUzytkownika;
        getline(ss, wczytanyKontakt.nazwa, '|');
        getline(ss, wczytanyKontakt.haslo, '|');
        kontakty.push_back(wczytanyKontakt);
    }
    plik.close();

    return kontakty;
}

int rejestracja(vector<Uzytkownik> uzytkownicy, int iloscUzytkownikow) {
    system("cls");
    string nazwa, haslo;
    Uzytkownik nowyKontakt;
    fstream plik;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nowyKontakt.nazwa;
    int i=0;
    while (i < iloscUzytkownikow) {
        if (uzytkownicy[i].nazwa == nazwa) {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> nazwa;
            struct Adresat {
                int id, idZalogowanegoUzytkownika;
                string imie, nazwisko, telefon, email, adres;
            };
            i=0;
        } else {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> nowyKontakt.haslo;
    nowyKontakt.idUzytkownika = uzytkownicy.size()+1;
    uzytkownicy.push_back(nowyKontakt);

    plik.open("baza uzytkownikow.txt",ios::out | ios::app);

    plik<<nowyKontakt.idUzytkownika <<"|";
    plik<<nowyKontakt.nazwa <<"|";
    plik<<nowyKontakt.haslo<<"|"<<endl;

    plik.close();
    cout << "Konto zalozone" <<endl;
    Sleep(1000);
    return iloscUzytkownikow+1;
}

int logowanie (vector<Uzytkownik> uzytkownicy, int iloscUzytkownikow) {
    system("cls");
    string nazwa, haslo;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;

    for (int licznik = 0; licznik < uzytkownicy.size(); licznik++) {
        if (uzytkownicy[licznik].nazwa == nazwa) {
            for (int proby=0; proby<3; proby++) {
                cout << "podaj haslo. Pozostalo prob " << 3-proby << ": ";
                cin >> haslo;
                if (uzytkownicy[licznik].haslo == haslo) {
                    cout << "Zalogowales sie." << endl;
                    Sleep(1000);
                    return uzytkownicy[licznik].idUzytkownika;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba" << endl;
            Sleep(3000);
            return 0;
        }
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl;
    Sleep(1500);
    return 0;
}

void zmianaHasla(vector<Uzytkownik> uzytkownicy, int idZalogowanegoUzytkownika, int iloscUzytkownikow) {
    system("cls");
    string noweHaslo;
    vector <Uzytkownik>::iterator it;
    auto iter = find_if(uzytkownicy.begin(),uzytkownicy.end(),[&](Uzytkownik const &uzytkownicy) {
        return uzytkownicy.idUzytkownika == idZalogowanegoUzytkownika;
    });
    cout << "Podaj nowe haslo: ";
    cin >> noweHaslo;
    if(iter != uzytkownicy.end())
        (*iter).haslo = noweHaslo;

    ofstream plik("baza uzytkownikow.txt",ios::out | ios::trunc);
    for(vector<Uzytkownik>::const_iterator licznik = uzytkownicy.begin(); licznik!=uzytkownicy.end(); ++licznik) {
        plik << (*licznik).idUzytkownika << "|";
        plik << (*licznik).nazwa << "|";
        plik << (*licznik).haslo << "|" << endl;
    }
    plik.close();
    cout << "Haslo zostalo zmienione." << endl;
    Sleep(1500);
}

vector<Adresat> wczytajOsobyZPliku(vector<Adresat> uzytkownicy, int idZalogowanegoUzytkownika) {
    string linia, idString, idString1;
    fstream plik;
    vector<Adresat>kontakty;
    Adresat wczytanyKontakt;

    plik.open("baza danych.txt", ios::in);

    if(plik.good()==false)
        cout<<"Nie mozna otworzyc pliku!"<<endl;

    while(getline(plik, linia)) {
        stringstream ss(linia);
        stringstream konwersja, konwersja1;
        getline(ss, idString, '|');
        konwersja << idString;
        konwersja >> wczytanyKontakt.id;
        getline(ss, idString1, '|');
        konwersja1 << idString1;
        konwersja1 >> wczytanyKontakt.idZalogowanegoUzytkownika;
        getline(ss, wczytanyKontakt.imie, '|');
        getline(ss, wczytanyKontakt.nazwisko, '|');
        getline(ss, wczytanyKontakt.telefon, '|');
        getline(ss, wczytanyKontakt.email, '|');
        getline(ss, wczytanyKontakt.adres, '|');
        if(wczytanyKontakt.idZalogowanegoUzytkownika == idZalogowanegoUzytkownika) {
            kontakty.push_back(wczytanyKontakt);
        }
    }
    plik.close();
    return kontakty;
}

int znajdzUnikalneId () {
    int unikalneId=0;
    string linia, idString, idString1;
    fstream plik;
    Adresat wczytanyKontakt;

    plik.open("baza danych.txt", ios::in);

    if(plik.good()==false)
        cout<<"Nie mozna otworzyc pliku!"<<endl;

    while(getline(plik, linia)) {
        stringstream ss(linia), konwersja;
        getline(ss, idString, '|');
        konwersja << idString;
        konwersja >> unikalneId;
        getline(ss, idString1, '|');
        getline(ss, wczytanyKontakt.imie, '|');
        getline(ss, wczytanyKontakt.nazwisko, '|');
        getline(ss, wczytanyKontakt.telefon, '|');
        getline(ss, wczytanyKontakt.email, '|');
        getline(ss, wczytanyKontakt.adres, '|');
    }
    plik.close();
    return unikalneId+1;
}

vector<Adresat> wprowadzNowegoPrzyjaciela (vector<Adresat>uzytkownicy, int idZalogowanegoUzytkownika, int idNowegoAdresata) {
    system("cls");
    fstream plik;
    Adresat nowyKontakt;
    nowyKontakt.id = idNowegoAdresata;
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
    plik<<idZalogowanegoUzytkownika<<"|";
    plik<<nowyKontakt.imie<<"|";
    plik<<nowyKontakt.nazwisko<<"|";
    plik<<nowyKontakt.telefon<<"|";
    plik<<nowyKontakt.email<<"|";
    plik<<nowyKontakt.adres<<"|"<<endl;

    plik.close();
    cout << "Nowy kontakt zostal zapisany." << endl;
    Sleep(2000);
    system("cls");

    return uzytkownicy;
}

void wczytajPoImieniu(vector<Adresat>uzytkownicy) {
    system("cls");
    int liczbaWyszukanychOsob =0;
    string imie;
    cout << "Podaj szukane imie: ";
    cin >> imie;
    cout << endl;

    for (int licznik = 0; licznik < uzytkownicy.size(); licznik++) {
        if (uzytkownicy[licznik].imie == imie) {
            cout<<uzytkownicy[licznik].id <<endl;
            cout<<uzytkownicy[licznik].idZalogowanegoUzytkownika <<endl;
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

void wczytajPoNazwisku(vector<Adresat>uzytkownicy) {
    system("cls");
    int liczbaWyszukanychOsob =0;
    string nazwisko;
    cout << "Podaj szukane nazwisko: ";
    cin >> nazwisko;
    cout << endl;

    for (int licznik=0; licznik < uzytkownicy.size(); licznik++) {
        if (uzytkownicy[licznik].nazwisko == nazwisko) {
            cout<<uzytkownicy[licznik].id <<endl;
            cout<<uzytkownicy[licznik].idZalogowanegoUzytkownika <<endl;
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

void wyswietlKontakty(vector<Adresat> uzytkownicy, int iloscUzytkownikow) {
    system("cls");
    for (int licznik=0; licznik < uzytkownicy.size(); licznik++) {
        cout << uzytkownicy[licznik].id << endl;
        cout<<uzytkownicy[licznik].idZalogowanegoUzytkownika <<endl;
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

void zaktualizujBazeDanychPoEdycji(vector<Adresat>uzytkownicy, int idUzytkownika) {
    string linia, idString, idString1, imie, nazwisko, telefon, email, adres;
    fstream plik, plikTymczasowy;
    int idAdresata, idZalogowanegoUzytkownika;

    plik.open("baza danych.txt", ios::in);
    plikTymczasowy.open("baza danych tymczasowa.txt", ios::out | ios::app);

    if(plik.good()==false)
        cout<<"Nie mozna otworzyc pliku oryginalnego!"<<endl;

    if(plikTymczasowy.good()==false)
        cout<<"Nie mozna otworzyc pliku tymczasowego!"<<endl;

    vector <Adresat>::iterator it;
    auto iter = find_if(uzytkownicy.begin(),uzytkownicy.end(),[&](Adresat const &uzytkownicy) {
        return uzytkownicy.id == idUzytkownika;
    });
    while(getline(plik, linia)) {
        stringstream ss(linia), konwersja, konwersja1;
        getline(ss, idString, '|');
        konwersja << idString;
        konwersja >> idAdresata;
        getline(ss, idString1, '|');
        konwersja1 << idString1;
        konwersja1 >> idZalogowanegoUzytkownika;
        getline(ss, imie, '|');
        getline(ss, nazwisko, '|');
        getline(ss, telefon, '|');
        getline(ss, email, '|');
        getline(ss, adres, '|');

        if ((*iter).id != idAdresata) {
            plikTymczasowy<<idAdresata <<"|";
            plikTymczasowy<<idZalogowanegoUzytkownika<<"|";
            plikTymczasowy<<imie<<"|";
            plikTymczasowy<<nazwisko<<"|";
            plikTymczasowy<<telefon<<"|";
            plikTymczasowy<<email<<"|";
            plikTymczasowy<<adres<<"|"<<endl;
        } else {
            plikTymczasowy<<(*iter).id <<"|";
            plikTymczasowy<<(*iter).idZalogowanegoUzytkownika<<"|";
            plikTymczasowy<<(*iter).imie<<"|";
            plikTymczasowy<<(*iter).nazwisko<<"|";
            plikTymczasowy<<(*iter).telefon<<"|";
            plikTymczasowy<<(*iter).email<<"|";
            plikTymczasowy<<(*iter).adres<<"|"<<endl;
        }
    }
    plikTymczasowy.close();
    plik.close();
    remove("baza danych.txt");
    rename("baza danych tymczasowa.txt","baza danych.txt");
}

void zaktualizujBazeDanychPoUsunieciu(vector<Adresat>uzytkownicy, int idUzytkownika) {
    string linia, idString, idString1, imie, nazwisko, telefon, email, adres;
    fstream plik, plikTymczasowy;
    int idAdresata, idZalogowanegoUzytkownika;

    plik.open("baza danych.txt", ios::in);
    plikTymczasowy.open("baza danych tymczasowa.txt", ios::out | ios::app);

    if(plik.good()==false)
        cout<<"Nie mozna otworzyc pliku oryginalnego!"<<endl;

    if(plikTymczasowy.good()==false)
        cout<<"Nie mozna otworzyc pliku tymczasowego!"<<endl;

    while(getline(plik, linia)) {
        stringstream ss(linia), konwersja, konwersja1;
        getline(ss, idString, '|');
        konwersja << idString;
        konwersja >> idAdresata;
        getline(ss, idString1, '|');
        konwersja1 << idString1;
        konwersja1 >> idZalogowanegoUzytkownika;
        getline(ss, imie, '|');
        getline(ss, nazwisko, '|');
        getline(ss, telefon, '|');
        getline(ss, email, '|');
        getline(ss, adres, '|');
        if (idUzytkownika != idAdresata) {
            plikTymczasowy<<idAdresata <<"|";
            plikTymczasowy<<idZalogowanegoUzytkownika<<"|";
            plikTymczasowy<<imie<<"|";
            plikTymczasowy<<nazwisko<<"|";
            plikTymczasowy<<telefon<<"|";
            plikTymczasowy<<email<<"|";
            plikTymczasowy<<adres<<"|"<<endl;
        }
    }
    plikTymczasowy.close();
    plik.close();
    remove("baza danych.txt");
    rename("baza danych tymczasowa.txt","baza danych.txt");
}

void usunAdresata(vector<Adresat> uzytkownicy) {
    int idUzytkownika;
    char znak;
    system("cls");
    cout << "Wprowadz id adresata do usuniecia: ";
    cin >> idUzytkownika;
    system("cls");
    cout << "Aby usunac kontakt, wprowadz klawisz t" << endl;
    cin >> znak;
    if (znak == 't') {
        uzytkownicy.erase(
        remove_if(uzytkownicy.begin(), uzytkownicy.end(),[&](Adresat const & uzytkownicy) {
            return uzytkownicy.id == idUzytkownika;
        }),
        uzytkownicy.end());
        zaktualizujBazeDanychPoUsunieciu(uzytkownicy, idUzytkownika);
        cout << "Uzytkownik o podanym id zostal usuniety !";
        Sleep(2000);
        system("cls");
    } else {
        cout << "Usuniecie kontaktu zostalo anulowane.";
        Sleep(2000);
        system("cls");
    }
}

void modyfikujKontakt(vector <Adresat> uzytkownicy, int numerId, char wybor) {
    string noweImie,noweNazwisko,nowyTelefon,nowyAdres,nowyEmail;
    vector <Adresat>::iterator it;
    auto iter = find_if(uzytkownicy.begin(),uzytkownicy.end(),[&](Adresat const &uzytkownicy) {
        return uzytkownicy.id == numerId;
    });
    if(wybor == '1') {
        cout << "Podaj nowe imie: ";
        cin>>noweImie;
        if(iter != uzytkownicy.end())
            (*iter).imie = noweImie;
    } else if (wybor == '2') {
        cout << "Podaj nowe nazwisko: ";
        cin>>noweNazwisko;
        if(iter != uzytkownicy.end())
            (*iter).nazwisko = noweNazwisko;
    } else if (wybor == '3') {
        cout << "Podaj nowy numer telefonu: ";
        cin>>nowyTelefon;
        if(iter != uzytkownicy.end())
            (*iter).telefon = nowyTelefon;
    } else if (wybor == '4') {
        cout << "Podaj nowy adres email: ";
        cin>>nowyEmail;
        if(iter != uzytkownicy.end())
            (*iter).email = nowyEmail;
    } else if (wybor == '5') {
        cout << "Podaj nowe adres: ";
        cin.sync();
        getline(cin, nowyAdres);
        if(iter != uzytkownicy.end())
            (*iter).adres = nowyAdres;
    }
    zaktualizujBazeDanychPoEdycji(uzytkownicy, (*iter).id);
    cout << "Edycja przebiegla pomyslnie !";
    Sleep(2000);
    system("cls");
}

int main() {
    vector<Adresat> uzytkownicy;
    vector<Uzytkownik> zarejestrowaniUzytkownicy;
    char wybor, wybor1;
    int nrId, idZalogowanegoUzytkownika=0, iloscZarejestrowanychUzytkownikow=0;
    while(1) {
        zarejestrowaniUzytkownicy = wczytajOsobyZPliku(zarejestrowaniUzytkownicy);
        iloscZarejestrowanychUzytkownikow = zarejestrowaniUzytkownicy.size();
        if(idZalogowanegoUzytkownika == 0) {
            system("cls");
            cout << "1.Rejestracja" << endl;
            cout << "2.Logowanie" << endl;
            cout << "3.Zamknij program" << endl;
            cout << "Twoj wybor: ";
            cin >> wybor;
            if (wybor == '1') {
                iloscZarejestrowanychUzytkownikow = rejestracja(zarejestrowaniUzytkownicy, iloscZarejestrowanychUzytkownikow);
            } else if (wybor == '2') {
                idZalogowanegoUzytkownika = logowanie(zarejestrowaniUzytkownicy, iloscZarejestrowanychUzytkownikow);
            } else if (wybor == '3') {
                system("cls");
                exit(0);
            }
        } else {
            int idNowegoAdresata = znajdzUnikalneId();
            uzytkownicy = wczytajOsobyZPliku(uzytkownicy, idZalogowanegoUzytkownika);
            int iloscUzytkownikow = uzytkownicy.size();
            system("cls");
            cout << "Zalogowany Uzytkownik: " << idZalogowanegoUzytkownika << endl;
            cout << "Ilosc wczytanych uzytkownikow: "<< iloscUzytkownikow << endl;
            cout << "Unikalne ID: "<< idNowegoAdresata << endl;
            system("pause");
            system("cls");
            cout << "KSIAZKA ADRESOWA" << endl;
            cout << "1.Dodaj adresata" << endl;
            cout << "2.Wyszukaj po imieniu" << endl;
            cout << "3.Wyszukaj po nazwisku" << endl;
            cout << "4.Wyswietl wszystkich adresatow" << endl;
            cout << "5.Usun adresata" << endl;
            cout << "6.Edytuj adresata" << endl;
            cout << "7.Zmien haslo" << endl;
            cout << "9.Wyloguj sie" << endl;
            cout << "Twoj wybor: ";
            cin >> wybor;

            if (wybor == '1') {
                uzytkownicy = wprowadzNowegoPrzyjaciela(uzytkownicy, idZalogowanegoUzytkownika, idNowegoAdresata);
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
            } else if (wybor == '7') {
                zmianaHasla(zarejestrowaniUzytkownicy, idZalogowanegoUzytkownika, iloscZarejestrowanychUzytkownikow);
            } else if (wybor == '9') {
                idZalogowanegoUzytkownika = 0;
            }
        }
    }
    return 0;
}
