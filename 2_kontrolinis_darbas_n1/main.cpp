//1. Sukurti dvikrypti sarasa, realizuojant duomenu ivedima, iterpima pries ir po nurodyto elemento,
//norimo elemento pasalinima bei didziausio elemento radima. Realizuoti funkcijas, kurios:
//a. Visus nelyginius skaisius perkelia is dvikrypcio saraso i steka, realizuota kaip vienkryptis
//sarasas.
//b. Iterpia i steka 5 atsitiktinius skaicius.
//c. Panaikina visus steko elementus, atspausdinant juos ekrane.

#include <iostream>
#include <ctime>
using namespace std;

struct dviKrypt {
    dviKrypt *pirmyn;
    int duom;
    dviKrypt *atgal;
};

struct StekoElementas {
    int duom;
    StekoElementas *kitas;
};

void iterptiPrie(dviKrypt *&pradzia, int pries, int duom);
void iterptiPo(dviKrypt *&pradzia, int po, int duom);
void pasalinti(dviKrypt *&pradzia, int salinti);
int rastiDidziausia(dviKrypt *pradzia);
void perkeltiNelyginius(dviKrypt *&pradzia, StekoElementas *&stekas);
void iterptiAtsitiktinius(StekoElementas *&stekas);
void isvalytiSteka(StekoElementas *&stekas);

int main() {
    dviKrypt *pradzia = nullptr, *pabaiga = nullptr;
    StekoElementas *stekas = nullptr;
    int num = 0, duom, sk = 0;

    cout << "Iveskite kiek elementu bus: ";
    cin >> num;

    for (int i = 0; i < num; i++) {
        cout << "Iveskite " << i + 1 << " elementa: ";
        cin >> duom;
        dviKrypt *naujas = new dviKrypt{};

        naujas->duom = duom;
        if (pabaiga != nullptr) {
            pabaiga->pirmyn = naujas;
        }
        pabaiga = naujas;
        if (pradzia == nullptr) {
            pradzia = naujas;
        }
    }
    num = 0;
    while (num != 5) {
        cout << "Pasirinkite veiksma:" << endl;
        cout << "1. Veiksmai su dvykrypciu sarasu." << endl;
        cout << "2. Perkelti nelyginius skaicius i steka." << endl;
        cout << "3. Iterpti i steka 5 atsitiktinius skaicius." << endl;
        cout << "4. Ispausdinti ir isvalyti steka." << endl;
        cout << "5. Iseiti." << endl;
        cin >> num;

        switch (num) {
            case 1: {
                int s_num = 0;
                while (s_num != 5) {
                    cout << "Pasirinkite veiksma:" << endl;
                    cout << "1. Iterpimas pries." << endl;
                    cout << "2. Iterpimas po." << endl;
                    cout << "3. Pasalinimas." << endl;
                    cout << "4. Didziausio elemento radimas." << endl;
                    cout << "5. Pabaigti." << endl;
                    cin >> s_num;

                    if (s_num == 1) {
                        cout << "Pries ka iterpti? ";
                        cin >> sk;
                        cout << "Iveskite duomenis: ";
                        cin >> duom;
                        iterptiPrie(pradzia, sk, duom);
                    } else if (s_num == 2) {
                        cout << "Po ko iterpti? ";
                        cin >> sk;
                        cout << "Iveskite duomenis: ";
                        cin >> duom;
                        iterptiPo(pradzia, sk, duom);
                    } else if (s_num == 3) {
                        cout << "Ka pasalinti? ";
                        cin >> sk;
                        pasalinti(pradzia, sk);
                    } else if (s_num == 4) {
                        cout << "Didziausias: " << rastiDidziausia(pradzia) << endl;
                    }
                }
                break;
            }
            case 2:
                perkeltiNelyginius(pradzia, stekas);
                break;
            case 3:
                iterptiAtsitiktinius(stekas);
                break;
            case 4:
                isvalytiSteka(stekas);
                break;
            case 5:
                cout << "Jus isejote is programos." << endl;
                break;
            default:
                cout << "Tokio pasirinkimo nera, bandykite dar karta." << endl;
        }
    }
    return 0;
}

void iterptiPrie(dviKrypt *&pradzia, int pries, int duom) {
    dviKrypt *dabartinis = pradzia;
    while (dabartinis && dabartinis->duom != pries) {
        dabartinis = dabartinis->pirmyn;
    }
    if (dabartinis != nullptr) {
        dviKrypt *naujas = new dviKrypt{};
        naujas->duom = duom;
        if (dabartinis->atgal != nullptr) {
            dabartinis->atgal->pirmyn = naujas;
        } else {
            pradzia = naujas;
        }
        naujas->atgal = dabartinis->atgal;
        naujas->pirmyn = dabartinis;
        dabartinis->atgal = naujas;
    }
}

void iterptiPo(dviKrypt *&pradzia, int po, int duom) {
    dviKrypt *dabartinis = pradzia;
    while (dabartinis && dabartinis->duom != po) {
        dabartinis = dabartinis->pirmyn;
    }
    if (dabartinis != nullptr) {
        dviKrypt *naujas = new dviKrypt{};
        naujas->duom = duom;
        naujas->pirmyn = dabartinis->pirmyn;
        naujas->atgal = dabartinis;
        if (dabartinis->pirmyn != nullptr) {
            dabartinis->pirmyn->atgal = naujas;
        }
        dabartinis->pirmyn = naujas;
    }
}

void pasalinti(dviKrypt *&pradzia, int salinti) {
    dviKrypt *dabartinis = pradzia;
    while (dabartinis && dabartinis->duom != salinti) {
        dabartinis = dabartinis->pirmyn;
    }
    if (dabartinis != nullptr) {
        if (dabartinis->atgal) {
            dabartinis->atgal->pirmyn = dabartinis->pirmyn;
        } else {
            pradzia = dabartinis->pirmyn;
        }
        if (dabartinis->pirmyn != nullptr) {
            dabartinis->pirmyn->atgal = dabartinis->atgal;
        }
        delete dabartinis;
    }
}

int rastiDidziausia(dviKrypt *pradzia) {
    if (pradzia == nullptr) {
        cout << "Sarasas tuscias!" << endl;
        return -1;
    }

    int didziausias = pradzia->duom;
    dviKrypt *dabartinis = pradzia->pirmyn;

    while (dabartinis != nullptr) {
        if (dabartinis->duom > didziausias) {
            didziausias = dabartinis->duom;
        }
        dabartinis = dabartinis->pirmyn;
    }
    return didziausias;
}


void perkeltiNelyginius(dviKrypt *&pradzia, StekoElementas *&stekas) {
    while (pradzia != nullptr) {
        if (pradzia->duom % 2 != 0) {
            StekoElementas *naujas = new StekoElementas{};
            naujas->duom = pradzia->duom;
            naujas->kitas = stekas;
            stekas = naujas;
        }
        pradzia = pradzia->pirmyn;
    }
}

void iterptiAtsitiktinius(StekoElementas *&stekas) {
    srand(time(0));
    for (int i = 0; i < 5; i++) {
        StekoElementas *naujas = new StekoElementas{};
        naujas->duom = rand() % 100;
        naujas->kitas = stekas;
        stekas = naujas;
    }
}

void isvalytiSteka(StekoElementas *&stekas) {
    while (stekas != nullptr) {
        cout << "Steko elementas: " << stekas->duom << endl;
        StekoElementas *temp = stekas;
        stekas = stekas->kitas;
        delete temp;
    }
}
