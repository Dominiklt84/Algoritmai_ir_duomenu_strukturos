//Simbolius (raides, skyrybos simbolius bei tarpus) irasykite i dvikrypti sarasas. Apskaiciuoti daugiausia einanciu is eiles tarpu.
#include <iostream>

using namespace std;

struct dvipKrypt {
    dvipKrypt *pirmyn;
    char duom;
    dvipKrypt *atgal;
};

dvipKrypt *pradzia = nullptr, *pabaiga = nullptr;

void iterptiElementa(char simbolis);
int daugiausiaTarpu();

int main() {
    int num = 0;
    while (num != 3) {
        cout << "Pasirinkite veiksma:" << endl;
        cout << "1. Iterpti elementa i dvikrypti sarasa." << endl;
        cout << "2. Apskaiciuoti daugiausia einanciu is eiles tarpu." << endl;
        cout << "3. Iseiti." << endl;
        cin >> num;
        cin.ignore();

        switch (num) {
            case 1: {
                cout << "Iveskite simboli (gali buti tarpas): ";
                string ivestis;
                getline(cin, ivestis);

                if (ivestis.length() != 1) {
                    cout << "Klaida: prasome ivesti tik viena simboli!" << endl;
                } else {
                    char simbolis = ivestis[0];
                    iterptiElementa(simbolis);
                    cout << "Simbolis sekmingai iterptas." << endl;
                }
                break;
            }
            case 2: {
                int rezultatas = daugiausiaTarpu();
                cout << "Daugiausia is eiles einanciu tarpu: " << rezultatas << endl;
                break;
            }
            case 3:
                cout << "Programa baigta." << endl;
            break;
            default:
                cout << "Tokio pasirinkimo nera, bandykite dar karta." << endl;
            break;
        }
    }
    return 0;
}

void iterptiElementa(char simbolis) {
    dvipKrypt* naujas = new dvipKrypt;
    naujas->duom = simbolis;
    naujas->pirmyn = nullptr;
    naujas->atgal = pabaiga;
    if (pabaiga != nullptr) {
        pabaiga->pirmyn = naujas;
    }
    pabaiga = naujas;
    if (pradzia == nullptr) {
        pradzia = naujas;
    }
}

int daugiausiaTarpu() {
    int maxTarpu = 0;
    int dabartinisTarpu = 0;
    dvipKrypt* dabartinis = pradzia;

    while (dabartinis != nullptr) {
        if (dabartinis->duom == ' ') {
            dabartinisTarpu++;
            if (dabartinisTarpu > maxTarpu) {
                maxTarpu = dabartinisTarpu;
            }
        } else {
            dabartinisTarpu = 0;
        }
        dabartinis = dabartinis->pirmyn;
    }

    return maxTarpu;
}