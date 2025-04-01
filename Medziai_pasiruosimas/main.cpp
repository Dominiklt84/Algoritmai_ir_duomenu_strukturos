#include <iostream>
#include <string>

using namespace std;

struct Medis {
    string pavarde;
    Medis *desine;
    Medis *kaire;
};

struct dekas {
    string pavarde;
    dekas *pries, *kitas;
    dekas(string p) : pavarde(p), pries(nullptr), kitas(nullptr) {}
};

dekas *pradzia = nullptr, *galas = nullptr;

struct eile {
    string pavarde;
    eile *kitas;
    eile(string p) : pavarde(p), kitas(nullptr) {}
};

eile *eiles_pradzia = nullptr, *eiles_galas = nullptr;

Medis* naujas_elementas(string pavarde);
Medis* iterpti(Medis* saknis, string pavarde);
Medis* paieska(Medis* saknis, string pavarde);
void spausdinti(Medis* saknis);
Medis* min_reiksme(Medis* saknis);
Medis* panaikinti(Medis* saknis, string pavarde);

void iterpti_I_Pradzia(string pavarde);
void iterpti_I_Gala(string pavarde);
void iterpti_Eile(string pavarde);

void skirstyti_A_L(Medis* saknis);
void skirstyti_R_Z(Medis* saknis);
void skirstyti_M_P(Medis* saknis);

void spausdinti_deka();
void spausdinti_eile();

int main() {
    Medis* saknis = nullptr;
    int num = 0;
    string pavarde;

    while (num != 6) {
        cout << "Pasirinkite veiksma:" << endl;
        cout << "1. Veiksmai su medziu." << endl;
        cout << "2. Visas pavardes, prasidedancias raidemis nuo A iki L irasyti i deka, realizuota kaip sarasa, i pradzia." << endl;
        cout << "3. Visas pavardes, prasidedancias raidemis nuo R iki Z irasyti i ta pati deka, realizuota kaip sarasa, i pabaiga." << endl;
        cout << "4. Pasalinti visas pavardes nuo M iki P is medzio, irasant jas i eile, realizuota kaip sarasas. " << endl;
        cout << "5. Spausdinti deka ir eile." << endl;
        cout << "6. Iseiti." << endl;
        cin >> num;

        switch (num) {
        case 1: {
            int s_num = 0;
            while (s_num != 5) {
                cout << "Pasirinkite veiksma:" << endl;
                cout << "1. Iterpti pavarde" << endl;
                cout << "2. Ieskoti pavardes" << endl;
                cout << "3. Spausdinti medi" << endl;
                cout << "4. Pasalinti pavarde" << endl;
                cout << "5. Iseiti" << endl;
                cin >> s_num;
                cin.ignore();

                if (s_num == 1) {
                    cout << "Iveskite pavarde: ";
                    getline(cin, pavarde);
                    saknis = iterpti(saknis, pavarde);
                }
                else if (s_num == 2) {
                    cout << "Iveskite pavarde: ";
                    getline(cin, pavarde);
                    if (paieska(saknis, pavarde))
                        cout << "Pavarde rasta." << endl;
                    else
                        cout << "Pavarde nerasta." << endl;
                }
                else if (s_num == 3) {
                    if (saknis == nullptr)
                        cout << "Medis tuscias!" << endl;
                    else {
                        cout << "Medzio turinys: ";
                        spausdinti(saknis);
                        cout << endl;
                    }
                }
                else if (s_num == 4) {
                    cout << "Iveskite pavarde: " << endl;
                    getline(cin, pavarde);
                    saknis = panaikinti(saknis, pavarde);
                }
            }
            break;
        }
        case 2:
            skirstyti_A_L(saknis);
            break;
        case 3:
            skirstyti_R_Z(saknis);
            break;
        case 4:
            skirstyti_M_P(saknis);
            break;
        case 5:
            cout << "Dekas: "; spausdinti_deka();
            cout << "Eile: "; spausdinti_eile();
            break;
        case 6:
            cout << "Jus isejote is programos." << endl;
            break;
        default:
            cout << "Tokio pasirinkimo nera, bandykite dar karta." << endl;
        }
    }
    return 0;
}

Medis* naujas_elementas(string pavarde) {
    Medis* p = new Medis;
    p->pavarde = pavarde;
    p->kaire = nullptr;
    p->desine = nullptr;
    return p;
}

Medis* iterpti(Medis* saknis, string pavarde) {
    if (saknis == nullptr)
        return naujas_elementas(pavarde);
    if (pavarde > saknis->pavarde)
        saknis->desine = iterpti(saknis->desine, pavarde);
    else
        saknis->kaire = iterpti(saknis->kaire, pavarde);
    return saknis;
}

Medis* paieska(Medis* saknis, string pavarde) {
    if (saknis == nullptr || saknis->pavarde == pavarde)
        return saknis;
    if (pavarde > saknis->pavarde)
        return paieska(saknis->desine, pavarde);
    return paieska(saknis->kaire, pavarde);
}

void spausdinti(Medis* saknis) {
    if (saknis != nullptr) {
        spausdinti(saknis->kaire);
        cout << saknis->pavarde << " ";
        spausdinti(saknis->desine);
    }
}

Medis* min_reiksme(Medis* saknis) {
    while (saknis->kaire != nullptr)
        saknis = saknis->kaire;
    return saknis;
}

Medis* panaikinti(Medis* saknis, string pavarde) {
    if (saknis == nullptr)
        return nullptr;
    if (pavarde > saknis->pavarde)
        saknis->desine = panaikinti(saknis->desine, pavarde);
    else if (pavarde < saknis->pavarde)
        saknis->kaire = panaikinti(saknis->kaire, pavarde);
    else {
        if (saknis->kaire == nullptr) {
            Medis* temp = saknis->desine;
            delete saknis;
            return temp;
        }
        else if (saknis->desine == nullptr) {
            Medis* temp = saknis->kaire;
            delete saknis;
            return temp;
        }
        Medis* temp = min_reiksme(saknis->desine);
        saknis->pavarde = temp->pavarde;
        saknis->desine = panaikinti(saknis->desine, temp->pavarde);
    }
    return saknis;
}

void iterpti_I_Pradzia(string pavarde) {
    dekas* naujas = new dekas(pavarde);
    if (pradzia == nullptr) {
        pradzia = galas = naujas;
    }
    else {
        pradzia->pries = naujas;
        naujas->kitas = pradzia;
        pradzia = naujas;
    }
}

void iterpti_I_Gala(string pavarde) {
    dekas* naujas = new dekas(pavarde);
    if (galas == nullptr) {
        pradzia = galas = naujas;
    }
    else {
        galas->kitas = naujas;
        naujas->pries = galas;
        galas = naujas;
    }
}

void iterpti_Eile(string pavarde) {
    eile* nauja = new eile(pavarde);
    if (eiles_galas == nullptr) {
        eiles_pradzia = eiles_galas = nauja;
    }
    else {
        eiles_galas->kitas = nauja;
        eiles_galas = nauja;
    }
}

void skirstyti_A_L(Medis* saknis) {
    if (saknis != nullptr) {
        skirstyti_A_L(saknis->kaire);
        char pirmoji = toupper(saknis->pavarde[0]);  // Užtikrinsime, kad raidės būtų lyginamos tik didžiosiomis
        if (pirmoji >= 'A' && pirmoji <= 'L') {
            iterpti_I_Pradzia(saknis->pavarde);
        }
        skirstyti_A_L(saknis->desine);
    }
}

void skirstyti_R_Z(Medis* saknis) {
    if (saknis != nullptr) {
        skirstyti_R_Z(saknis->kaire);
        char pirmoji = toupper(saknis->pavarde[0]);
        if (pirmoji >= 'R' && pirmoji <= 'Z') {
            iterpti_I_Gala(saknis->pavarde);
        }
        skirstyti_R_Z(saknis->desine);
    }
}

void skirstyti_M_P(Medis* saknis) {
    if (saknis != nullptr) {
        skirstyti_M_P(saknis->kaire);
        char pirmoji = toupper(saknis->pavarde[0]);
        if (pirmoji >= 'M' && pirmoji <= 'P') {
            iterpti_Eile(saknis->pavarde);
        }
        skirstyti_M_P(saknis->desine);
    }
}

void spausdinti_deka() {
    dekas* temp = pradzia;
    while (temp) {
        cout << temp->pavarde << " ";
        temp = temp->kitas;
    }
    cout << endl;
}

void spausdinti_eile() {
    eile* temp = eiles_pradzia;
    while (temp) {
        cout << temp->pavarde << " ";
        temp = temp->kitas;
    }
    cout << endl;
}
