//Skaiciai x1, x2, … , xn surasyti i vienkrypti sarasa. Sukurti kita vienkrypti sarasa
//kuriame butu elementai x1-xn, x2-xn-1, …., xn-1-x2, xn-x1.

#include <iostream>
using namespace std;

struct sarasas {
    int duom;
    sarasas* kitas;
};

sarasas* pradzia = nullptr;
sarasas* pabaiga = nullptr;
sarasas* antras_sarasas = nullptr;

struct sarasas;
void iterpti_pradzia(int reiksme);
void spausdinti_sarasa(sarasas* pradzia);
int ilgis(sarasas* pradzia);
sarasas* gauti_elementa(sarasas* pradzia, int index);
void sukurti_antra_sarasa();

int main() {
    int num = 0, reiksme;
    while (num != 4) {
        cout << "Pasirinkite veiksma:" << endl;
        cout << "1. Iterpti elementa i vienkrypti sarasa." << endl;
        cout << "2. Perkelti elementus i kita vienkrypti sarasa (x1-xn, x2-xn-1, ...)." << endl;
        cout << "3. Spausdinti antra vienkrypti sarasa." << endl;
        cout << "4. Iseiti." << endl;
        cin >> num;

        switch (num) {
            case 1:
                cout << "Iveskite skaiciu: ";
                cin >> reiksme;
                iterpti_pradzia(reiksme);
                break;

            case 2:
                sukurti_antra_sarasa();
                break;

            case 3:
                cout << "Antras sarasas: ";
                spausdinti_sarasa(antras_sarasas);
                break;

            case 4:
                cout << "Programa baigta." << endl;
                break;

            default:
                cout << "Tokio pasirinkimo nera, bandykite dar karta." << endl;
        }
    }

    return 0;
}

void iterpti_pradzia(int reiksme) {
    sarasas* naujas = new sarasas{reiksme, nullptr};
    if (pradzia == nullptr) {
        pradzia = pabaiga = naujas;
    } else {
        pabaiga->kitas = naujas;
        pabaiga = naujas;
    }
}

void spausdinti_sarasa(sarasas* pradzia) {
    sarasas* tmp = pradzia;
    while (tmp != nullptr) {
        cout << tmp->duom << " ";
        tmp = tmp->kitas;
    }
    cout << endl;
}

int ilgis(sarasas* pradzia) {
    int ilgis = 0;
    while (pradzia != nullptr) {
        ilgis++;
        pradzia = pradzia->kitas;
    }
    return ilgis;
}

sarasas* gauti_elementa(sarasas* pradzia, int index) {
    int ilgis_1 = 0;
    while (pradzia != nullptr && ilgis_1 < index) {
        pradzia = pradzia->kitas;
        ilgis_1++;
    }
    return pradzia;
}

void sukurti_antra_sarasa() {
    sarasas* temp;
    while (antras_sarasas != nullptr) {
        temp = antras_sarasas;
        antras_sarasas = antras_sarasas->kitas;
        delete temp;
    }

    int n = ilgis(pradzia);
    for (int i = 0; i < n; i++) {
        sarasas* priekyje = gauti_elementa(pradzia, i);
        sarasas* gale = gauti_elementa(pradzia, n - i - 1);
        int skirtumas = priekyje->duom - gale->duom;

        sarasas* naujas = new sarasas{skirtumas, nullptr};
        if (antras_sarasas == nullptr) {
            antras_sarasas = naujas;
        } else {
            sarasas* p = antras_sarasas;
            while (p->kitas != nullptr) p = p->kitas;
            p->kitas = naujas;
        }
    }

    cout << "Antras sarasas sukurtas." << endl;
}
