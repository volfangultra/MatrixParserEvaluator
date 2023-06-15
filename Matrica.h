#ifndef MATRICA
#define MATRICA

#include <string>
#include <initializer_list>
#include <iostream>
#include <cmath>
#include <vector>
#include <stack>

using namespace std;

class Operand;
class Matrica;

class Operand{
    virtual string daj_tip() = 0;
    virtual double daj_broj() = 0;
    virtual Matrica daj_matricu() = 0;
    virtual char daj_znak() = 0;
public:
    ~Operand(){};

    //Prijatelji
    friend Operand* rezultat(Operand* a, Operand* b, char operacija);
    friend istream& operator>>(istream& upis, Matrica& matrica);
    friend void izvrsi_operaciju(stack<Operand*>& operandi, stack<char>& operacije);
    friend ostream& operator<<(ostream& ispis, stack<Operand*> s);

};


class Matrica: public Operand{
    int broj_redova;
    int broj_kolona;
    double** matrica;

    //Obavezne
    string daj_tip(){return "matrica"; }
    double daj_broj(){return 0; }
    char daj_znak(){return 0; }
    Matrica daj_matricu(){return *this; }

public:
    //Osnove
    Matrica():broj_redova(0), broj_kolona(0), matrica(nullptr){};    //Konstruktor
    explicit Matrica(int, int);                                      //Konstruktor sa dimenzijama
    explicit Matrica(int);                                           //Konsturktor pravi kvadratnu
    Matrica(initializer_list<initializer_list<double>>);             //Konstruktor sa inicijalizacijskom listom
    Matrica(vector<vector<double>>);                                 //Konstruktor sa vektorom vektora
    Matrica(const Matrica&);                                         //Konstruktor kopije
    Matrica(Matrica&&);                                              //Pomjerajuci konstruktor kopije
    Matrica& operator=(const Matrica&);                              //Operator dodjele
    Matrica& operator=(Matrica&&);                                   //Pomjerajuci operator dodjele
    ~Matrica();                                                      //Destruktor

    //Operacije
    friend Matrica operator+(const Matrica&, const Matrica&);                           //Sabiranje
    Matrica& operator+=(const Matrica& m) {*this = *this + m; return *this; }
    friend Matrica operator-(const Matrica&, const Matrica&);                           //Oduzimanje
    Matrica& operator-=(const Matrica& m) {*this = *this - m; return *this; }
    friend Matrica operator*(const Matrica&, const Matrica&);                           //Množenje
    Matrica& operator*=(const Matrica& m) {*this = *this * m; return *this; }
    friend Matrica operator*(const Matrica&, double);
    friend Matrica operator*(double broj, const Matrica& m){return m * broj; }
    Matrica& operator*=(double broj) {*this = *this * broj; return *this; }
    friend Matrica operator/(const Matrica&, const Matrica&);                           //Djeljenje
    Matrica operator/=(const Matrica& m){*this = *this / m; return *this; }
    friend Matrica operator/(const Matrica&, double);
    friend Matrica operator/(double, const Matrica&);
    Matrica operator^(int) const;                                                       //Stepenovanje
    Matrica operator^=(int n){*this = *this ^ n; return *this; }
    Matrica operator^(char) const;                                                      //Transponovanje
    Matrica operator^=(char z){*this = *this ^ z; return *this; }
    double* operator[](int i) {return matrica[i];}
    const double* operator[](int i) const {return matrica[i];}                          //Pojedinacni elementi

    //Geteri
    int get_broj_kolona()const {return broj_kolona;}
    int get_broj_redova()const {return broj_redova;}

    //Upis i ispis
    friend ostream& operator<<(ostream&, const Matrica&);
    friend istream& operator>>(istream&, Matrica&);

    //Korisne_funkcije
    friend double det(Matrica);                                         //racuna determinantu
    bool je_kvadratna() const {return broj_kolona == broj_redova;}      //provjerava da li je kvadratna
    friend Matrica napravi_jedinicnu(double);                              //pravi jedinicnu matricu
    void zamjeni_dva_reda(int, int);                                    //mjenja dva reda matrice
    Matrica presjeci_matricu(int, int, int, int) const;                 //Uzima komad matrice izmedju i ukljucujuci te 2 koordinate
    Matrica inverzna() const;                                           //Nalazi inverznu matricu

    //Prijatelji
    friend Operand* rezultat(Operand* a, Operand* b, char operacija);
    friend void izvrsi_operaciju(stack<Operand*>& operandi, stack<char>& operacije);
    friend ostream& operator<<(ostream& ispis, stack<Operand*> s);
    friend najduzi_decimalni(const Matrica& m);

};

Matrica napravi_jedinicnu(double);


class Broj: public Operand{
    //Osnove
    double broj;
    Broj():broj(0){}
    Broj(double broj):broj(broj){}

    //Prijatelji
    friend Operand* rezultat(Operand* a, Operand* b, char operacija);
    friend istream& operator>>(istream& upis, Matrica& matrica);
    friend void izvrsi_operaciju(stack<Operand*>& operandi, stack<char>& operacije);
    friend ostream& operator<<(ostream& ispis, stack<Operand*> s);

    //Obavezne
    string daj_tip(){return "broj"; }
    Matrica daj_matricu(){return Matrica(0); }
    double daj_broj(){return broj; }
    char daj_znak(){return 0; }


};


class Znak: public Operand{
    //Osnove
    char znak;
    Znak():znak(0){}
    Znak(char znak):znak(znak){}

    //Prijatelji
    friend Operand* rezultat(Operand* a, Operand* b, char operacija);
    friend istream& operator>>(istream& upis, Matrica& matrica);
    friend void izvrsi_operaciju(stack<Operand*>& operandi, stack<char>& operacije);
    friend ostream& operator<<(ostream& ispis, stack<Operand*> s);

    //Obavezne
    string daj_tip(){return "znak"; }
    Matrica daj_matricu(){return Matrica(0); }
    double daj_broj(){return 0; }
    char daj_znak(){return znak; }

};


#endif
