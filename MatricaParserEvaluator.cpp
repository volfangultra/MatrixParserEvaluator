#include "Matrica.h"
#include <iostream>
#include <stack>
#include <cmath>
#include <vector>

using namespace std;


//Parser i Evaluator
ostream& operator<<(ostream& ispis, stack<char> s){
    while(!s.empty()){
        ispis << s.top() << " ";
        s.pop();
    }

    return ispis;
}

ostream& operator<<(ostream& ispis, stack<Operand*> s){
    cout << "Ovo su operandi: " << endl;
    while(!s.empty()){
        if(s.top()->daj_tip() == "matrica")
            ispis << s.top()->daj_matricu() << endl;
        else if(s.top()->daj_tip() == "broj")
            ispis << s.top()->daj_broj() << endl;
        else
            ispis << s.top()->daj_znak() << endl;

        s.pop();

    }
    cout << "Kraj";

    return ispis;

}



template<typename Tip>
ostream& operator<<(ostream& ispis, vector<Tip> v){
    for(int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;

    return ispis;
}

int prioritet(char operacija){
    if(operacija == '+' || operacija == '-')
        return 1;
    if(operacija == '*')
        return 2;
    if(operacija == '^')
        return 3;

}

Operand* rezultat(Operand* b, Operand* a, char operacija){
    if(a->daj_tip() == "broj" && b->daj_tip() == "broj"){
        if(operacija == '+')
            return new Broj(a->daj_broj() + b->daj_broj());
        else if(operacija == '-')
            return new Broj(a->daj_broj() - b->daj_broj());
        else if(operacija == '*')
            return new Broj(a->daj_broj() * b->daj_broj());
        else if(operacija == '/'){
            if(b->daj_broj() == 0)
                throw "Ne moze se djeliti sa 0";

            return new Broj(a->daj_broj() / b->daj_broj());

        }
        else if(operacija == '^')
            return new Broj(pow(a->daj_broj(), b->daj_broj()));

    }
    else if(a->daj_tip() == "matrica" && b->daj_tip() == "matrica"){
        if(operacija == '+')
            return new Matrica(a->daj_matricu() + b->daj_matricu());
        else if(operacija == '-')
            return new Matrica(a->daj_matricu() - b->daj_matricu());
        else if(operacija == '*')
            return new Matrica(a->daj_matricu() * b->daj_matricu());
        else if(operacija == '/')
            return new Matrica(a->daj_matricu() / b->daj_matricu());
        else if(operacija == '^')
            throw "Ne moguce je stepenovat matrice";

    }
    else if(a->daj_tip() == "matrica" && b->daj_tip() == "broj"){
        if(operacija == '+')
            throw "Ne moguce sabrati broj i matricu";
        else if(operacija == '-')
            throw "Ne moguce oduzeti broj i matricu";
        else if(operacija == '*')
            return new Matrica(a->daj_matricu() * b->daj_broj());
        else if(operacija == '/')
            return new Matrica(a->daj_matricu() / a->daj_broj());
        else if(operacija == '^'){
            if(int(b->daj_broj()) != b->daj_broj())
                throw "Matrica se ne moze stepenovati sa realnim brojem";

            return new Matrica(a->daj_matricu() ^ int(b->daj_broj()));
        }
    }
    else if(a->daj_tip() == "broj" && b->daj_tip() == "matrica"){
        if(operacija == '+')
            throw "Ne moguce sabrati broj i matricu";
        else if(operacija == '-')
            throw "Ne moguce oduzeti broj i matricu";
        else if(operacija == '*')
            return new Matrica(a->daj_broj() * b->daj_matricu());
        else if(operacija == '/')
            return new Matrica(a->daj_broj() / b->daj_matricu());
        else if(operacija == '^')
            throw "Nije moguce stepenovati broj sa matricom";
    }
    else if(a->daj_tip() == "matrica" && b->daj_tip() == "znak"){
        if(operacija == '^')
            return new Matrica(a->daj_matricu() ^ b->daj_znak());
        else
            throw "izmedju matrice i znaka samo moze biti transponovanje";
    }
    else
        throw "Operacije sa znakovima nisu moguce osim transponovanja";


}

void izvrsi_operaciju(stack<Operand*>& operandi, stack<char>& operacije){
    if(operacije.empty() && operandi.size() < 2)
        throw "Odnos operacija i brojeva nije dobar";

    char operacija = operacije.top();
    operacije.pop();
    Operand* operand1 = operandi.top();
    operandi.pop();
    Operand* operand2 = operandi.top();
    operandi.pop();
    operandi.push(rezultat(operand1, operand2, operacija));

}

bool je_cifra(char z){
    return (z >= '0' && z <= '9');

}

bool je_operacija(char z){
    return (z == '+' || z == '-' || z =='*' || z == '/' || z == '^');

}

Matrica unesi_matricu(istream& upis){
    upis.get();
    if(upis.peek() == ']'){
        return Matrica();

    }

    vector<vector<double>> rez;
    while(upis.peek() != ']'){
        vector<double> red;
        while(upis.peek() != ';' && upis.peek() != ']'){
            if(!je_cifra(upis.peek()) && upis.peek() != '-')
                throw "Nije validan unos u matrici";

            double broj;
            upis >> broj;
            if(upis.peek() == ' ')
                upis.get();

            red.push_back(broj);
        }

        rez.push_back(red);
        if(upis.peek() == ';')
            upis.get();
    }

    return Matrica(rez);

}

istream& operator>>(istream& upis, Matrica& matrica){
    stack<Operand*> operandi;
    stack<char> operacije;
    char prethodni = '(';
    while(upis.peek() != '\n'){
        char znak = upis.peek();
        if(znak == '['){
            if(!je_operacija(prethodni) && prethodni != '(')
                throw "Prije matrice mora biti operacija";

            operandi.push(new Matrica(unesi_matricu(upis)));
            prethodni = upis.get();
        }
        else if(znak == '('){
            if(!je_operacija(prethodni) && prethodni != '(')
                throw "Prije  zatvorene zagrade mora biti operacija";

            operacije.push(znak);
            prethodni = upis.get();
        }
        else if(znak == ')'){
            if(je_operacija(prethodni))
                throw "Prije otvorene zagrade ne smije biti operacija";
            if(prethodni == 'I')
                throw "Nije definisana velicina jedinicne matrice";

            while(!operacije.empty() && je_operacija(operacije.top()))
                izvrsi_operaciju(operandi, operacije);
            if(operacije.empty() || operacije.top() != '(')
                throw "Zagrade nisu balansirane";
            else
                operacije.pop();
            prethodni = upis.get();
        }
        else if(je_operacija(znak)){
            if(znak == '-' && prethodni == '('){
                operandi.push(new Broj(-1));
                znak = '*';
            }
            else if(znak == '-' && prethodni == '^'){
                upis.get();
                if(!je_cifra(upis.peek()))
                    throw "stepenovati se moze samo sa brojem";
                double broj;
                upis >> broj;
                prethodni = '0';
                operandi.push(new Broj(-1*broj));
                continue;
            }
            else if(znak == '-' && prethodni == 'I')
                throw "Ne moguce je napraviti jedinicnu negativnih dimenzija";
            else if(je_operacija(prethodni) || prethodni == '(')
                throw "Operacija nakon otvorene zagrade ili dvije uzastopne operacije";

            while(!operacije.empty() && je_operacija(operacije.top()) && prioritet(znak) <= prioritet(operacije.top()))
                    izvrsi_operaciju(operandi, operacije);
                operacije.push(znak);
                prethodni = upis.get();

            }
        else if(je_cifra(znak)){
            if(prethodni == ')')
                throw "Ne moze nakon zatvorene zagrade broj";
            if(prethodni == ']')
                throw "Ne moze nakon matrice broj";
            if(prethodni == 'T')
                throw "Nakon transponovanja ne moze broj";
            if(prethodni == 'I'){
                double broj;
                upis >> broj;
                operandi.push(new Matrica(napravi_jedinicnu(broj)));
                prethodni = ']';
            }
            else{
                double broj;
                upis >> broj;
                operandi.push(new Broj(broj));
                prethodni = '0';
            }
        }
        else if(znak == 'I'){
            if((!je_operacija(prethodni) || prethodni == '^') && prethodni != '(')
                throw "Prije jedinicne mora biti samo operacija osim ^ ili otvorena zagrada";
            prethodni = upis.get();

        }
        else if(znak == 'T'){
            if(prethodni != '^')
                throw "T moze samo nakon ^";
            prethodni = upis.get();
            operandi.push(new Znak('T'));

        }
        else
            throw "Nedozvoljen znak";

    }

    while(!operacije.empty()){
        if(!je_operacija(operacije.top()))
            throw "Fali zatvorenih zagrada";

        izvrsi_operaciju(operandi, operacije);
    }

    if(operandi.size() != 1)
        throw "Izraz nije dobro napisan";
    if(operandi.top()->daj_tip() != "matrica")
        throw "Rezultat izraza nije matrica";

    matrica = operandi.top()->daj_matricu();
    upis.get();
    return upis;

}
