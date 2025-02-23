#include <bits/stdc++.h>

using namespace std;

struct sarasas {
    int duom;
    sarasas *kitas;
};

void reiksmes_iterpimas(sarasas *&pradzia, sarasas *&pabaiga, int duom);
void spausdinimas(sarasas *pradzia);
bool ar_nemazejanti(sarasas *pradzia);
sarasas* sukurti_atvirkstini(sarasas *pradzia);

int main() {
    sarasas *pradzia = nullptr, *pabaiga = nullptr;
    int n, reiksme;

    cout << "Iveskite elementu skaiciu: ";
    cin >> n;

    cout << "Iveskite skaicius: " << endl;
    for (int i = 0; i < n; i++) {
        cin >> reiksme;
        reiksmes_iterpimas(pradzia, pabaiga, reiksme);
    }

    if (ar_nemazejanti(pradzia)) {
        cout << "Seka yra nemazejanti, paliekama tokia pati: ";
    } else {
        cout << "Seka nera nemazejanti, sukuriamas atvirkstinis sarasas: ";
        pradzia = sukurti_atvirkstini(pradzia);
    }

    spausdinimas(pradzia);
    return 0;
}

void reiksmes_iterpimas(sarasas *&pradzia, sarasas *&pabaiga, int duom) {
    sarasas *naujas = new sarasas();
    naujas->duom = duom;
    naujas->kitas = nullptr;

    if (pabaiga != nullptr) {
        pabaiga->kitas = naujas;
    }
    pabaiga = naujas;

    if (pradzia == nullptr) {
        pradzia = naujas;
    }
}


bool ar_nemazejanti(sarasas *pradzia) {
    while (pradzia != nullptr && pradzia->kitas != nullptr) {
        if (pradzia->duom > pradzia->kitas->duom) {
            return false;
        }
        pradzia = pradzia->kitas;
    }
    return true;
}


sarasas* sukurti_atvirkstini(sarasas *pradzia) {
    sarasas *nauja_pradzia = nullptr;

    while (pradzia != nullptr) {
        sarasas *naujas = new sarasas();
        naujas->duom = pradzia->duom;
        naujas->kitas = nauja_pradzia;
        nauja_pradzia = naujas;

        pradzia = pradzia->kitas;
    }
    return nauja_pradzia;
}

void spausdinimas(sarasas *pradzia) {
    while (pradzia != nullptr) {
        cout << pradzia->duom << " ";
        pradzia = pradzia->kitas;
    }
    cout << endl;
}
