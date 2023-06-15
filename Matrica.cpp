#include "Matrica.h"
#include <iostream>
#include <initializer_list>
#include <iomanip>
#include <string>

double preciznost = 0.000001;
int decimale = 100000;

int najduzi_decimalni(const Matrica& m);
Matrica rekurzivno_mnozenje(const Matrica&, const Matrica&);


//Osnove
Matrica::Matrica(int broj_redova, int broj_kolona):broj_redova(broj_redova), broj_kolona(broj_kolona){
        matrica = new double*[broj_redova];
            for(int i = 0; i < broj_redova; i++)
                matrica[i] = new double[broj_kolona];

        for(int i = 0; i < broj_redova;i++)
            for(int j = 0; j < broj_kolona; j++)
                matrica[i][j] = 0;
}

Matrica::Matrica(int dimenzija):broj_redova(dimenzija), broj_kolona(dimenzija){
        matrica = new double*[broj_redova];
            for(int i = 0; i < broj_redova; i++)
                matrica[i] = new double[broj_kolona];

        for(int i = 0; i < broj_redova;i++)
            for(int j = 0; j < broj_kolona; j++)
                matrica[i][j] = 0;
}

Matrica::Matrica(initializer_list<initializer_list<double>> l):broj_redova(l.size()), broj_kolona((*l.begin()).size()){
    for(auto red:l)
        if(red.size() != broj_kolona)
            throw "Inicijalizatorska lista nije matrica";

    matrica = new double*[broj_redova];
            for(int i = 0; i < broj_redova; i++)
                matrica[i] = new double[broj_kolona];

        auto iterator_listi = l.begin();
        for(int i = 0; i < broj_redova;i++){
            auto iterator_liste = (*iterator_listi).begin();
            for(int j = 0; j < broj_kolona; j++){
                matrica[i][j] = *iterator_liste;
                iterator_liste++;
            }
            iterator_listi++;
        }

}

Matrica::Matrica(vector<vector<double>> v):broj_redova(v.size()), broj_kolona(v[0].size()){
    for(int i = 0; i < v.size(); i++)
        if(v[i].size() != broj_kolona)
            throw "Vektor vektora nije matrica";

    matrica = new double*[broj_redova];
            for(int i = 0; i < broj_redova; i++)
                matrica[i] = new double[broj_kolona];

    for(int i = 0; i < v.size(); i++)
        for(int j = 0; j < v[i].size(); j++)
            matrica[i][j] = v[i][j];

}

Matrica::Matrica(const Matrica& kopija):broj_redova(kopija.broj_redova), broj_kolona(kopija.broj_kolona){
    matrica = new double*[broj_redova];
            for(int i = 0; i < broj_redova; i++)
                matrica[i] = new double[broj_kolona];

    for(int i = 0; i < broj_redova;i++)
        for(int j = 0; j < broj_kolona; j++)
            matrica[i][j] = kopija[i][j];

}

Matrica::Matrica(Matrica&& kopija):broj_redova(kopija.broj_kolona), broj_kolona(kopija.broj_kolona), matrica(kopija.matrica){
    kopija.matrica = nullptr;
    kopija.broj_redova = 0;
    kopija.broj_kolona = 0;

}

Matrica& Matrica::operator=(const Matrica& rhs){
    for(int i = 0; i < broj_redova; i++)
        delete[] matrica[i];
    delete[] matrica;

    broj_redova = rhs.broj_redova;
    broj_kolona = rhs.broj_kolona;

    matrica = new double*[broj_redova];
    for(int i = 0; i < broj_redova; i++)
        matrica[i] = new double[broj_kolona];

    for(int i = 0; i < broj_redova; i++)
        for(int j = 0; j < broj_kolona; j++)
            matrica[i][j] = rhs.matrica[i][j];

    return *this;

}

Matrica& Matrica::operator=(Matrica&& rhs){
    for(int i = 0; i < broj_redova; i++)
        delete[] matrica[i];
    delete[] matrica;

    broj_redova = rhs.broj_redova;
    broj_kolona = rhs.broj_kolona;
    matrica = rhs.matrica;

    rhs.matrica = nullptr;
    rhs.broj_kolona = 0;
    rhs.broj_redova = 0;

    return *this;

}

Matrica::~Matrica(){
    for(int i = 0; i < broj_redova; i++)
        delete[] matrica[i];
    delete[] matrica;

}


//Operacije
Matrica operator+(const Matrica& m1, const Matrica& m2){
    if(!(m1.broj_kolona == m2.broj_kolona && m1.broj_redova == m2.broj_redova))
        throw "Dimenzije ne odgovaraju za sabiranje";

    Matrica rez(m1.broj_redova, m1.broj_kolona);

    for(int i = 0; i < m1.broj_redova; i++)
        for(int j = 0; j < m1.broj_kolona; j++)
            rez[i][j] = m1[i][j] + m2[i][j];

    return rez;

}

Matrica operator-(const Matrica& m1, const Matrica& m2){
    if(!(m1.broj_kolona == m2.broj_kolona && m1.broj_redova == m2.broj_redova))
        throw "Dimenzije ne odgovaraju za oduzimanje";

    Matrica rez(m1.broj_redova, m1.broj_kolona);

    for(int i = 0; i < m1.broj_redova; i++)
        for(int j = 0; j < m1.broj_kolona; j++)
            rez[i][j] = m1[i][j] - m2[i][j];

    return rez;

}

Matrica operator*(const Matrica& m1, const Matrica& m2){
    if(!(m1.broj_kolona == m2.broj_redova))
        throw "Dimenzije ne odgovaraju za mnozenje";

    int dimenzija = 1;
    while(dimenzija < max(max(m1.broj_kolona, m1.broj_redova), max(m2.broj_kolona, m2.broj_redova)))
        dimenzija *= 2;

    Matrica modifikovani_m1(dimenzija), modifikovani_m2(dimenzija);

    for(int i = 0; i < m1.broj_redova; i++)
        for(int j = 0; j < m1.broj_kolona; j++)
            modifikovani_m1[i][j] = m1[i][j];

    for(int i = 0; i < m2.broj_redova; i++)
        for(int j = 0; j < m2.broj_kolona; j++)
            modifikovani_m2[i][j] = m2[i][j];

    Matrica C = rekurzivno_mnozenje(modifikovani_m1, modifikovani_m2);
    int broj_redova = m1.broj_redova;
    int broj_kolona = m2.broj_kolona;
    return C.presjeci_matricu(0, 0, broj_kolona - 1, broj_redova - 1);

}

Matrica operator*(const Matrica& m, double broj){
    Matrica rez(m);
    for(int i = 0; i < m.broj_redova; i++)
        for(int j = 0; j < m.broj_kolona; j++)
            rez.matrica[i][j] *= broj;



    return rez;

}

Matrica operator/(const Matrica& m1, const Matrica& m2){
    if(det(m2) == 0)
        throw "Ne moguce djeliti sa neinvertibilnom matricom";

    return m1 * (m2 ^ (-1));

}

Matrica operator/(const Matrica& m, double broj){
    if(broj == 0)
        throw "Ne moguce djeljenje sa nulom";

    return m * (1/broj);

}

Matrica operator/(double broj, const Matrica& m){
    if(det(m) == 0)
        throw "Ne moguce djeliti sa neinvertibilnom matricom";

    return broj * (m ^ (-1));

}

Matrica Matrica::operator^(int n) const{
    if(!this->je_kvadratna())
        throw "Ne moze se stepenovat jer nije kvadratna";
    if(n < 0 && det(*this) == 0)
        throw "Matrica nije invertibilna pa se ne moze stepenovat sa negativnim brojem";

    Matrica rez(*this);
    if(n == 1)
        return rez;

    if (n < 0)
        rez = this->inverzna();
    n = abs(n);

    if(n == 0)
        return napravi_jedinicnu(broj_redova);

    if(n % 2 == 0){
        Matrica a = (rez^(n / 2));
        return a * a;
        }
    return (rez^((n - 1) / 2)) * (rez^((n - 1) / 2)) * rez;

}

Matrica Matrica::operator^(char T) const{
    if(T != 'T')
        throw "Operacija nije moguca";

    Matrica rez(broj_kolona, broj_redova);
    for(int i = 0; i < broj_redova; i++)
        for(int j = 0; j < broj_kolona; j++)
            rez[j][i] = this->matrica[i][j];

    return rez;

}


//Upis i Ispis
ostream& operator<<(ostream& ispis, const Matrica& m){
    int duzina = najduzi_decimalni(m);
    string trenutni;
    for(int i = 0; i < m.broj_redova; i++){
        for(int j = 0; j < m.broj_kolona; j++){
            double potencijalni = round(m[i][j] * decimale) / decimale;
            if(abs(potencijalni - int(potencijalni)) < preciznost)
                trenutni = to_string(int(potencijalni));
            else
                trenutni = to_string(potencijalni);

            while(trenutni[trenutni.size() - 1] == '0' && trenutni.size() != 1)
                trenutni.pop_back();
            ispis << setw(duzina) << trenutni << " ";
        }

        ispis << endl;

    }

    return ispis;

}


//Korisne funkcije
double det(Matrica m){
    if(!m.je_kvadratna())
        throw "Matrici ne mozemo izracunati determinantu";

    int znak = 1;
    for(int i = 0; i < m.broj_kolona; i++){
        int potencijalni = i + 1;
        while(potencijalni < m.broj_kolona && m[i][i] == 0){
            m.zamjeni_dva_reda(potencijalni, i);
            znak *= -1;
            potencijalni++;
        }

        if(m[i][i] == 0)
            return 0;

        for(int j = i + 1; j < m.broj_redova; j++){
            double mnozim = m[j][i] / m[i][i];
            for(int k = 0; k < m.broj_kolona; k++){
                m[j][k] -= mnozim * m[i][k];
                if(abs(m[j][k] - int(m[j][k])) < preciznost)
                    m[j][k] = int(m[j][k]);
            }
        }
    }

    double rez = 1;
    for(int i = 0; i < m.broj_kolona; i++)
        rez *= m[i][i];

    if(abs(rez - int(rez)) < preciznost)
        rez = int(rez);

    return znak * rez;

}

Matrica napravi_jedinicnu(double dimenzija){
    if(int(dimenzija) != dimenzija || dimenzija < 0)
        throw "Nisu validne dimenzije jedinicne matrice";
    Matrica rez(dimenzija);
    for(int i = 0; i < rez.broj_redova; i++)
        for(int j = 0; j < rez.broj_kolona; j++)
            if(i == j)
                rez[i][j] = 1;

    return rez;

}

void Matrica::zamjeni_dva_reda(int prvi_red, int drugi_red){
    double* pomoc = matrica[prvi_red];
    matrica[prvi_red] = matrica[drugi_red];
    matrica[drugi_red] = pomoc;

}

Matrica Matrica::presjeci_matricu(int x1, int y1, int x2, int y2) const{
    if(x1 > x2)
        swap(x1, x2);
    if(y1 > y2)
        swap(y1, y2);

    Matrica rez(y2 - y1 + 1, x2 - x1 + 1);
    for(int i = 0; i < rez.broj_redova; i++)
        for(int j = 0; j < rez.broj_kolona; j++)
            rez[i][j] = this->matrica[i + x1][j + y1];

    return rez;

}

Matrica rekurzivno_mnozenje(const Matrica& m1, const Matrica& m2){
    int dimenzija = m1.get_broj_redova();

    if(dimenzija < 2)
        return Matrica({{m1[0][0] * m2[0][0]}});

    Matrica A11 = m1.presjeci_matricu(0, 0, dimenzija/2 - 1, dimenzija/2 - 1);
    Matrica A12 = m1.presjeci_matricu(0, dimenzija/2, dimenzija/2 - 1, dimenzija - 1);
    Matrica A21 = m1.presjeci_matricu(dimenzija/2, 0, dimenzija - 1, dimenzija/2 - 1);
    Matrica A22 = m1.presjeci_matricu(dimenzija/2, dimenzija/2, dimenzija - 1, dimenzija - 1);

    Matrica B11 = m2.presjeci_matricu(0, 0, dimenzija/2 - 1, dimenzija/2 - 1);
    Matrica B12 = m2.presjeci_matricu(0, dimenzija/2, dimenzija/2 - 1, dimenzija - 1);
    Matrica B21 = m2.presjeci_matricu(dimenzija/2, 0, dimenzija - 1, dimenzija/2 - 1);
    Matrica B22 = m2.presjeci_matricu(dimenzija/2, dimenzija/2, dimenzija - 1, dimenzija - 1);

    Matrica P1 = rekurzivno_mnozenje(A11, (B12 - B22));
    Matrica P2 = rekurzivno_mnozenje((A11 + A12), B22);
    Matrica P3 = rekurzivno_mnozenje((A21 + A22), B11);
    Matrica P4 = rekurzivno_mnozenje(A22, (B21 - B11));
    Matrica P5 = rekurzivno_mnozenje((A11 + A22), (B11 + B22));
    Matrica P6 = rekurzivno_mnozenje((A12 - A22), (B21 + B22));
    Matrica P7 = rekurzivno_mnozenje((A11 - A21), (B11 + B12));

    Matrica C11 = P5 + P4 - P2 + P6;
    Matrica C12 = P1 + P2;
    Matrica C21 = P3 + P4;
    Matrica C22 = P5 + P1 - P3 - P7;
    Matrica C(2*C11.get_broj_redova(), 2*C11.get_broj_kolona());

    int broj_redova = C.get_broj_redova();
    int broj_kolona = C.get_broj_kolona();
    for(int i = 0; i < broj_redova; i++)
        for(int j = 0; j < broj_kolona; j++){
            if(i < broj_redova / 2 && j < broj_kolona / 2)
                C[i][j] = C11[i][j];
            if(i < broj_redova / 2 && j >= broj_kolona / 2)
                C[i][j] = C12[i][j - broj_kolona / 2];
            if(i >= broj_redova / 2 && j < broj_kolona / 2)
                C[i][j] = C21[i - broj_redova / 2][j];
            if(i >= broj_redova / 2 && j >= broj_kolona / 2)
                C[i][j] = C22[i - broj_redova / 2][j - broj_kolona / 2];
    }

    return C;
}

int najduzi_decimalni(const Matrica& m){
    int najduzi = 0;
    string trenutni;
    for(int i = 0; i < m.broj_redova; i++)
        for(int j = 0; j < m.broj_kolona; j++){
            double potencijalni = round(m[i][j] * decimale) / decimale;
            if(abs(potencijalni - int(potencijalni)) < preciznost)
                trenutni = to_string(int(potencijalni));
            else
                trenutni = to_string(potencijalni);
            while(trenutni[trenutni.size() - 1] == '0')
                trenutni.pop_back();
            int duzina = trenutni.size();
            najduzi = max(najduzi, duzina);
    }

    return najduzi;

};

Matrica Matrica::inverzna() const{
    if(det(*this) == 0)
        throw "Matrica nije invertibilna";

    Matrica m(*this);
    Matrica inverzna = napravi_jedinicnu(broj_redova);

    for(int i = 0; i < m.broj_kolona; i++){
        int potencijalni = i + 1;
        while(potencijalni < m.broj_kolona && m[i][i] == 0){
            m.zamjeni_dva_reda(potencijalni, i);
            inverzna.zamjeni_dva_reda(potencijalni, i);
            potencijalni++;
        }

        for(int j = 0; j < m.broj_redova; j++){
            if(i != j){
                double mnozim = m[j][i] / m[i][i];
                for(int k = 0; k < m.broj_kolona; k++){
                   inverzna[j][k] -= mnozim * inverzna[i][k];
                     m[j][k] -= mnozim * m[i][k];
                    if(abs(m[j][k] - int(m[j][k])) < preciznost)
                        m[j][k] = int(m[j][k]);
                    if(abs(inverzna[j][k] - int(inverzna[j][k])) < preciznost)
                        inverzna[j][k] = int(inverzna[j][k]);
                }
            }
        }
    }
    for(int i = 0; i < broj_redova; i++)
        for(int j = 0; j < broj_kolona; j++){
            inverzna[i][j] /= m[i][i];
    }

    return inverzna;

}
