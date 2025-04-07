//Sukurti dvejetaini medi, kurio elementai butu asmena pavardes (simboliu eilutes).
//Realizuoti iterpimo, paieskos, spausdinimo ir salinimo operacijas bei atlikti siuos veiksmus:
//a. Visas pavardes is medzio, kuriu ilgis didesnis nei 6 irasyti i deka, realizuota kaip sarasas, i pradzia.
//b. Visas pavardes is medzio, kuriu ilgis didesnis uz 6, bet mazesnis už 10 irasyti i ta pati deka, i pabaiga.
//c. Pasalinti is medzio visas pavardes, kuriu ilgis didesnis uz 10, is medzio, irasant jas i eile, realizuota kaip sarasas.
//d. Spausdinti deka ir eile.

#include <iostream>
using namespace std;

const int MAX_PAVARDE_ILGIS = 100;

struct Medis {
    char pavarde[MAX_PAVARDE_ILGIS];
    Medis* desine;
    Medis* kaire;
};

struct dekas {
    char pavarde[MAX_PAVARDE_ILGIS];
    dekas* pries ;
    dekas* kitas ;
};

dekas* pradzia = nullptr, *galas = nullptr;

struct eile {
    char pavarde[MAX_PAVARDE_ILGIS];
    eile* kitas ;
};

eile* eiles_pradzia = nullptr, *eiles_galas = nullptr;

Medis* naujas_elementas(const char* pavarde);
Medis* iterpti(Medis* saknis, const char* pavarde);
Medis* paieska(Medis* saknis, const char* pavarde);
void spausdinti(Medis* saknis);
Medis* min_reiksme(Medis* saknis);
Medis* panaikinti(Medis* saknis, const char* pavarde);

void iterpti_I_Pradzia(const char* pavarde);
void iterpti_I_Gala(const char* pavarde);
void iterpti_Eile(const char* pavarde);

void spausdinti_deka();
void spausdinti_eile();

void did_ses_dek(Medis* saknis);
void did_ses_des_dek(Medis* saknis);
void ilgis_did_des(Medis* saknis);

int palygink_pavardes(const char* p1, const char* p2) {
    int i = 0;
    while (p1[i] != '\0' && p2[i] != '\0') {
        if (p1[i] < p2[i]) return -1;
        if (p1[i] > p2[i]) return 1;
        i++;
    }
    if (p1[i] == '\0' && p2[i] == '\0') return 0;
    if (p1[i] == '\0') {
        return -1;
    }else
        return 1;
}

int ilgio_pavarde(const char* pavarde) {
    int ilgis = 0;
    while (pavarde[ilgis] != '\0') {
        ilgis++;
    }
    return ilgis;
}

int main() {
    Medis* saknis = nullptr;
    int num = 0;
    char pavarde[MAX_PAVARDE_ILGIS];

    while (num != 6) {
        cout << "Pasirinkite veiksma:" << endl;
        cout << "1. Veiksmai su medziu." << endl;
        cout << "2. Visas pavardes is medzio, kuriu ilgis didesnis nei 6 irasyti i deka, realizuota kaip sarasas, i pradzia." << endl;
        cout << "3. Visas pavardes is medzio, kuriu ilgis didesnis uz 6, bet mazesnis uz 10 irasyti i ta pati deka, i pabaiga." << endl;
        cout << "4. Pasalinti is medzio visas pavardes, kuriu ilgis didesnis uz 10, is medzio, irasant jas i eile, realizuota kaip sarasas. " << endl;
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
                    cin.getline(pavarde, MAX_PAVARDE_ILGIS);
                    saknis = iterpti(saknis, pavarde);
                }
                else if (s_num == 2) {
                    cout << "Iveskite pavarde: ";
                    cin.getline(pavarde, MAX_PAVARDE_ILGIS);
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
                    cin.getline(pavarde, MAX_PAVARDE_ILGIS);
                    saknis = panaikinti(saknis, pavarde);
                }
            }
            break;
        }
        case 2:
            did_ses_dek(saknis);
            break;
        case 3:
            did_ses_des_dek(saknis);
            break;
        case 4:
            ilgis_did_des(saknis);
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


Medis* naujas_elementas(const char* pavarde) {
    Medis* p = new Medis;
    int i = 0;
    while (pavarde[i] != '\0' && i < MAX_PAVARDE_ILGIS - 1) {
        p->pavarde[i] = pavarde[i];
        i++;
    }
    p->pavarde[i] = '\0';
    p->kaire = nullptr;
    p->desine = nullptr;
    return p;
}

Medis* iterpti(Medis* saknis, const char* pavarde) {
    Medis* naujas = naujas_elementas(pavarde);
    Medis* dabartinis = saknis;
    Medis* tevai = nullptr;

    if (saknis == nullptr) {
        return naujas;
    }

    while (dabartinis != nullptr) {
        tevai = dabartinis;
        if (palygink_pavardes(pavarde, dabartinis->pavarde) > 0)
            dabartinis = dabartinis->desine;
        else
            dabartinis = dabartinis->kaire;
    }

    if (palygink_pavardes(pavarde, tevai->pavarde) > 0)
        tevai->desine = naujas;
    else
        tevai->kaire = naujas;

    return saknis;
}

Medis* paieska(Medis* saknis, const char* pavarde) {
    Medis* dabartinis = saknis;

    while (dabartinis != nullptr) {
        if (palygink_pavardes(pavarde, dabartinis->pavarde) == 0)
            return dabartinis;
        if (palygink_pavardes(pavarde, dabartinis->pavarde) > 0)
            dabartinis = dabartinis->desine;
        else
            dabartinis = dabartinis->kaire;
    }
    return nullptr;
}

void spausdinti(Medis* saknis) {
    if (saknis == nullptr) return;
    spausdinti(saknis->kaire);
    cout << saknis->pavarde << " ";
    spausdinti(saknis->desine);
}

Medis* min_reiksme(Medis* saknis) {
    while (saknis->kaire != nullptr)
        saknis = saknis->kaire;
    return saknis;
}

Medis* panaikinti(Medis* saknis, const char* pavarde) {
    Medis* dabartinis = saknis;
    Medis* tevai = nullptr;

    while (dabartinis != nullptr) {
        if (palygink_pavardes(pavarde, dabartinis->pavarde) == 0) {
            if (dabartinis->kaire == nullptr) {
                if (tevai == nullptr)
                    saknis = dabartinis->desine;
                else if (palygink_pavardes(pavarde, tevai->pavarde) > 0)
                    tevai->desine = dabartinis->desine;
                else
                    tevai->kaire = dabartinis->desine;
                delete dabartinis;
            } else if (dabartinis->desine == nullptr) {
                if (tevai == nullptr)
                    saknis = dabartinis->kaire;
                else if (palygink_pavardes(pavarde, tevai->pavarde) > 0)
                    tevai->desine = dabartinis->kaire;
                else
                    tevai->kaire = dabartinis->kaire;
                delete dabartinis;
            } else {
                Medis* min = min_reiksme(dabartinis->desine);
                for (int i = 0; min->pavarde[i] != '\0' && i < MAX_PAVARDE_ILGIS - 1; ++i) {
                    dabartinis->pavarde[i] = min->pavarde[i];
                }
                dabartinis->pavarde[MAX_PAVARDE_ILGIS - 1] = '\0';  // pabaiga
                saknis = panaikinti(saknis, min->pavarde);
            }
            return saknis;
        }
        tevai = dabartinis;
        if (palygink_pavardes(pavarde, dabartinis->pavarde) > 0)
            dabartinis = dabartinis->desine;
        else
            dabartinis = dabartinis->kaire;
    }
    return saknis;
}

void iterpti_I_Pradzia(const char* pavarde) {
    dekas* naujas = new dekas;
    int i = 0;
    while (pavarde[i] != '\0' && i < MAX_PAVARDE_ILGIS - 1) {
        naujas->pavarde[i] = pavarde[i];
        i++;
    }
    naujas->pavarde[i] = '\0';

    if (pradzia == nullptr) {
        pradzia = galas = naujas;
    } else {
        pradzia->pries = naujas;
        naujas->kitas = pradzia;
        pradzia = naujas;
    }
}


void iterpti_I_Gala(const char* pavarde) {
    dekas* naujas = new dekas;
    int i = 0;
    while (pavarde[i] != '\0' && i < MAX_PAVARDE_ILGIS - 1) {
        naujas->pavarde[i] = pavarde[i];
        i++;
    }
    naujas->pavarde[i] = '\0';

    if (galas == nullptr) {
        pradzia = galas = naujas;
    } else {
        galas->kitas = naujas;
        naujas->pries = galas;
        galas = naujas;
    }
}

void iterpti_Eile(const char* pavarde) {
    eile* nauja = new eile;
    int i = 0;
    while (pavarde[i] != '\0' && i < MAX_PAVARDE_ILGIS - 1) {
        nauja->pavarde[i] = pavarde[i];
        i++;
    }
    nauja->pavarde[i] = '\0';

    if (eiles_galas == nullptr) {
        eiles_pradzia = eiles_galas = nauja;
    } else {
        eiles_galas->kitas = nauja;
        eiles_galas = nauja;
    }
}

void did_ses_dek(Medis* saknis) {
    if (saknis == nullptr) return;

    Medis* dabartinis = saknis;
    while (dabartinis != nullptr) {
        if (ilgio_pavarde(dabartinis->pavarde) > 6) {
            iterpti_I_Pradzia(dabartinis->pavarde);
        }

        if (dabartinis->kaire != nullptr) {
            dabartinis = dabartinis->kaire;
        } else {
            dabartinis = dabartinis->desine;
        }
    }
}


void did_ses_des_dek(Medis* saknis) {
    if (saknis == nullptr) return;

    Medis* dabartinis = saknis;
    while (dabartinis != nullptr) {
        if (ilgio_pavarde(dabartinis->pavarde) > 6 && ilgio_pavarde(dabartinis->pavarde) < 10) {
            iterpti_I_Gala(dabartinis->pavarde);
        }

        if (dabartinis->kaire != nullptr) {
            dabartinis = dabartinis->kaire;
        } else {
            dabartinis = dabartinis->desine;
        }
    }
}

void ilgis_did_des(Medis* saknis) {
    if (saknis == nullptr) return;

    Medis* dabartinis = saknis;
    while (dabartinis != nullptr) {
        if (ilgio_pavarde(dabartinis->pavarde) > 10) {
            iterpti_Eile(dabartinis->pavarde);
            saknis = panaikinti(saknis, dabartinis->pavarde);
        }

        if (dabartinis->kaire != nullptr) {
            dabartinis = dabartinis->kaire;
        } else {
            dabartinis = dabartinis->desine;
        }
    }
}


void spausdinti_deka() {
    dekas* temp = pradzia;
    while (temp != nullptr) {
        cout << temp->pavarde << " ";
        temp = temp->kitas;
    }
    cout << endl;
}

void spausdinti_eile() {
    eile* temp = eiles_pradzia;
    while (temp != nullptr) {
        cout << temp->pavarde << " ";
        temp = temp->kitas;
    }
    cout << endl;
}
