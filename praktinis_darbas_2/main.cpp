//Sukurti dinamini vienkrypti sarasa, realizuojant elemento iterpimo, pasalinimo,
// spausdinimo bei paieskos funkcijas. Perkelti to saraso visus elementus i
// dvejetaini medi. Atspausdinti visus dvejetainio medzio elementus.
#include <iostream>

using namespace std;

struct sarasas {
    int duom;
    sarasas* kitas;
};

sarasas* pradzia = nullptr;
sarasas* pabaiga = nullptr;

struct medis {
    int duom;
    medis* kairys;
    medis* desinys;
};

medis* saknis = nullptr;

void iterpti_pradzia(int reiksme);
void spausdinti_sarasa(sarasas* pradzia);
bool pasalinti_konkrecia_reiksme(int reiksme);
sarasas* rasti_elementa(int reiksme);

void iterpti_i_medi(medis*& saknis, int reiksme);
void perkelti_i_medi(sarasas* pradzia, medis*& saknis);
void spausdinti_medi(medis* saknis);

int main() {
    int num = 0, reiksme;
    while (num != 7) {
        cout << "Pasirinkite veiksma:"<<endl;
        cout << "1. Iterpti elementa i vienkrypti sarasa."<<endl;
        cout << "2. Pasalinti elementa is vienkrypcio saraso."<<endl;
        cout << "3. Spausdinti vienkrypti sarasa."<<endl;
        cout << "4. Rasti elementa sarase."<<endl;
        cout << "5. Perkelti elementus i dvejetaini medi."<<endl;
        cout << "6. Atspausdinti dvejetaini medi."<<endl;
        cout << "7. Iseiti."<<endl;
        cin >> num;

        switch (num) {
            case 1:
                cout << "Iveskite skaiciu: ";
                cin >> reiksme;
                iterpti_pradzia(reiksme);
                break;
            case 2:
                cout << "Iveskite kokia reiksme norite pasalinti: ";
                cin >> reiksme;
                if (pasalinti_konkrecia_reiksme(reiksme))
                    cout << "Elementas sekmingai pasalintas."<<endl;
                else
                    cout << "Tokios reiksmes sarase nera."<<endl;
                break;
            case 3:
                cout << "Sarasas: ";
                spausdinti_sarasa(pradzia);
                break;
            case 4:
                cout << "Iveskite ieskoma skaiciu: ";
                cin >> reiksme;
                if (rasti_elementa(reiksme) != nullptr)
                    cout << "Elementas rastas sarase."<<endl;
                else
                    cout << "Elemento nera sarase."<<endl;
                break;
            case 5:
                perkelti_i_medi(pradzia, saknis);
                cout << "Elementai perkelti i medi."<<endl;
                break;
            case 6:
                cout << "Medzio elementai: ";
                spausdinti_medi(saknis);
                cout << endl;
                break;
            case 7:
                cout << "Programa baigta."<<endl;
                break;
            default:
                cout << "Tokio pasirinkimo nera, bandykite dar karta."<<endl;
                break;
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

bool pasalinti_konkrecia_reiksme(int reiksme) {
    if (pradzia == nullptr) return false;

    if (pradzia->duom == reiksme) {
        sarasas* temp = pradzia;
        pradzia = pradzia->kitas;
        if (temp == pabaiga) pabaiga = nullptr;
        delete temp;
        return true;
    }

    sarasas* dabartinis = pradzia;
    while (dabartinis->kitas != nullptr) {
        if (dabartinis->kitas->duom == reiksme) {
            sarasas* salinamas = dabartinis->kitas;
            dabartinis->kitas = salinamas->kitas;
            if (salinamas == pabaiga)
                pabaiga = dabartinis;
            delete salinamas;
            return true;
        }
        dabartinis = dabartinis->kitas;
    }
    return false;
}

sarasas* rasti_elementa(int reiksme) {
    sarasas* pr = pradzia;
    while (pr != nullptr) {
        if (pr->duom == reiksme)
            return pr;
        pr = pr->kitas;
    }
    return nullptr;
}

void iterpti_i_medi(medis*& saknis, int reiksme) {
    if (saknis == nullptr) {
        saknis = new medis{reiksme, nullptr, nullptr};
    } else if (reiksme < saknis->duom) {
        iterpti_i_medi(saknis->kairys, reiksme);
    } else {
        iterpti_i_medi(saknis->desinys, reiksme);
    }
}

void perkelti_i_medi(sarasas* pradzia, medis*& saknis) {
    while (pradzia != nullptr) {
        iterpti_i_medi(saknis, pradzia->duom);
        pradzia = pradzia->kitas;
    }
}

void spausdinti_medi(medis* saknis) {
    if (saknis != nullptr) {
        spausdinti_medi(saknis->kairys);
        cout << saknis->duom << " ";
        spausdinti_medi(saknis->desinys);
    }
}
