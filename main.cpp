#include "Matrica.h"
#include<iostream>
#include<vector>
using namespace std;

int main(){
Matrica m1(2,3); //Pravi 2x3 matricu koja ima sve 0 kao elemente
Matrica m2(4); //Pravi 4x4 matricu koja ima sve 0 kao elemente
m1[0][0] = 1; //Postavlja element u prvom redu i prvoj koloni na 1
Matrica m3(m1 * 2); //Moze se inicijalizirat sa rezultatom neke operacije
Matrica m4({{1,2,3}, {4,5,4}, {2,2,2}}); //Inicijlizacija preko inicijalizatorske lise
cout << m4 << "determinanta je: " << det(m4) << endl << endl; //moze se ispisati preko << operatora
cout << "inverzna je: " << endl << (m4^-1) << endl << "transponovana je: " << endl << (m4^'T'); //osnovne operacija sa matricama rade
m4 *= napravi_jedinicnu(3); //Svi ocekivani operatori su optereceni i mozemo praviti jedinicnu matricu
try{m1 * m2; }catch(const char* poruka){cout << endl << poruka << endl << endl; } //Sve operacije bacaju izuzetke
m4 ^= -5; //matricu mozemo stepenovat sa bilo kojim cijelim brojem
cout << "Stepenovanje sa 0 je jedinicna matrica:" << endl << (m4^0) << endl;
const Matrica m5(m4); //Konstruktor kopije
//m5[0][0] = 1; //Ne dozvoljava
cout << m5[0][0] << endl << endl; //Dozvoljava
//m5 + 5 //Zabranjena autmatska konverzija double u Matricu
cout << (vector<vector<double>>({{1,2,3}, {4,5,4}, {2,2,2}}) - m4) << endl; //ovo je dozvoljeno
cout << "broj redova od m5 je: " << m5.get_broj_redova() << " a broj kolona od m5 je: " << m5.get_broj_kolona() << endl;
cout << m5;
m1 = napravi_jedinicnu(3);
m2 = m1;
m2[0][0] = 0;
cout << endl << "m1: " << endl << m1 << endl << "m2: " << endl << m2; //Ako mjenjas jednu ne mjenja se druga;
cout << endl;

//Parser i Evaluator
while(true)
    try{
            //[1 2;3 4]^3*(4*[1 2 3;4 5 6]+[7 8;9 1;2 3]^T)-[1 3;7 2]^-1*[7 8 1;1 2 3]*I3
            Matrica m;
            cin >> m;
            cout << endl << m;

    }catch(const char* poruka){cin.ignore(1000, '\n'); cout << poruka << endl;}

}
