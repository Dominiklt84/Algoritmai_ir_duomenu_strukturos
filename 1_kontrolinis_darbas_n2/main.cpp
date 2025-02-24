#include <iostream>

using namespace std;

struct sarasas {
    int duom;
    sarasas *kitas;
};

int sumaMax(sarasas *pradzia);
void surusiuotiSarasa(sarasas *&pradzia);
void spausdintiSarasa(sarasas *pradzia);

int main() {
    sarasas *pradzia = nullptr, *pabaiga = nullptr;
    int num = 0, n, duom;

    cout << "Iveskite kiek elementu bus: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Iveskite " << i + 1 << " elementa: ";
        cin >> duom;
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

    while (num != 4) {
        cout << "Pasirinkite veiksma:"<<endl;
        cout << "1. Rasti elementu esanciu intervale [a;b] kieki."<<endl;
        cout << "2. Suma elementu einanciu po maksimalios reiksmes."<<endl;
        cout << "3. Surusiuoti sarasa didejimo tvarka."<<endl;
        cout << "4. Iseiti."<<endl;
        cin >> num;

        switch (num) {
            case 1: {
                int a, b;
                cout << "Iveskite a: ";
                cin >> a;
                cout << "Iveskite b: ";
                cin >> b;

                int kiekis = 0;
                sarasas *temp = pradzia;
                while (temp != nullptr) {
                    if (temp->duom >= a && temp->duom <= b) {
                        kiekis++;
                    }
                    temp = temp->kitas;
                }
                cout << "Elementu intervale [" << a << ";" << b << "] kiekis: " << kiekis << endl;
                break;
            }
            case 2: {
                int suma = sumaMax(pradzia);
                cout << "Suma po maksimalios reiksmes: " << suma << endl;
                break;
            }
            case 3:
                surusiuotiSarasa(pradzia);
                cout << "Saraso elementai po rusiavimo: ";
                spausdintiSarasa(pradzia);
                break;
            case 4:
                cout << "Jus isejote is programos" << endl;
                break;
            default:
                cout << "Tokio pasirinkimo nera, bandykite dar karta" << endl;
        }
    }

    // Atlaisviname atmintį
    while (pradzia != nullptr) {
        sarasas *temp = pradzia;
        pradzia = pradzia->kitas;
        delete temp;
    }

    return 0;
}

void spausdintiSarasa(sarasas *pradzia) {
    if (pradzia == nullptr) {
        cout << "Sąrašas tuščias." << endl;
        return;
    }

    sarasas *temp = pradzia;
    while (temp != nullptr) {
        cout << temp->duom << " ";
        temp = temp->kitas;
    }
    cout << endl;
}

int sumaMax(sarasas *pradzia) {
    if (pradzia == nullptr) return 0;

    int maxReiksme = pradzia->duom;
    sarasas *temp = pradzia;

    while (temp != nullptr) {
        if (temp->duom > maxReiksme) {
            maxReiksme = temp->duom;
        }
        temp = temp->kitas;
    }

    temp = pradzia;
    while (temp != nullptr && temp->duom != maxReiksme) {
        temp = temp->kitas;
    }

    if (temp != nullptr) temp = temp->kitas;

    int suma = 0;
    while (temp != nullptr) {
        suma += temp->duom;
        temp = temp->kitas;
    }
    return suma;
}

void surusiuotiSarasa(sarasas *&pradzia) {
    if (pradzia == nullptr || pradzia->kitas == nullptr) return;
    sarasas *i, *j;
    for (i = pradzia; i->kitas != nullptr; i = i->kitas) {
        for (j = pradzia; j->kitas != nullptr; j = j->kitas) {
            if (j->duom > j->kitas->duom) {
                int laikinas = j->duom;
                j->duom = j->kitas->duom;
                j->kitas->duom = laikinas;
            }
        }
    }
}
