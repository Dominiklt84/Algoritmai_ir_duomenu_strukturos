#include <iostream>

using namespace std;

struct sarasas {
    int duom;
    sarasas* kitas;
};

struct Medis {
    int key;
    Medis* Kaire;
    Medis* Desine;
    int dydis;
};
sarasas* pradzia = nullptr;
sarasas* pabaiga = nullptr;
Medis* medis = nullptr;

void iterpti_pradzia(int elementas);
int pasalinti_elementa_pradzia();
void spausdinti_sarasa();
sarasas* rasti_elementa(int reiksme);
Medis* sarasas_i_avl();
void spausdinti_medi(Medis* root);

int RastiDydi(Medis* N);
int max(int a, int b);
int BalansinisKoef(Medis* N);
Medis* NaujasElementas(int key);
Medis* DesinePosukis(Medis* y);
Medis* KairePosukis(Medis* x);
Medis* IterptiElementa(Medis* root, int key);

int main() {
    int num=0, reiksme;
    while (num != 7) {
        cout << "Pasirinkite veiksma:" << endl;
        cout << "1. Iterpti elementa i vienkrypti sarasa." << endl;
        cout << "2. Pasalinti elementa is vienkrypcio saraso ." << endl;
        cout << "3. Spausdinti vienkrypti sarasa." << endl;
        cout << "4. Rasti elementa sarase." << endl;
        cout << "5. Perkelti sarasa i AVL medi." << endl;
        cout << "6. Atspausdinti AVL medi." << endl;
        cout << "7. Iseiti." << endl;
        cin >> num;

        switch (num) {
            case 1:
                cout << "Iveskite skaiciu: ";
            cin >> reiksme;
            iterpti_pradzia(reiksme);
            break;

            case 2:
                if (pradzia != nullptr)
                    cout << "Pasalintas elementas: " << pasalinti_elementa_pradzia() << endl;
                else
                    cout << "Sarasas tuscias." << endl;
            break;

            case 3:
                cout << "Sarasas: ";
            spausdinti_sarasa();
            break;

            case 4:
                cout << "Iveskite ieskoma skaiciu: ";
            cin >> reiksme;
            if (rasti_elementa(reiksme) != nullptr)
                cout << "Elementas rastas sarase." << endl;
            else
                cout << "Elemento nera sarase." << endl;
            break;

            case 5:
                medis = sarasas_i_avl();
            cout << "Elementai perkelti i AVL medi." << endl;
            break;

            case 6:
                cout << "AVL medis : ";
            spausdinti_medi(medis);
            cout << endl;
            break;

            case 7:
                cout << "Programa baigta." << endl;
            break;

            default:
                cout << "Tokio pasirinkimo nera, bandykite dar karta." << endl;
            break;
        }
    }

    return 0;
}

void iterpti_pradzia(int elementas) {
    sarasas* el = new sarasas();
    el->duom = elementas;
    el->kitas = pradzia;
    pradzia = el;
    if (pabaiga == nullptr) pabaiga = el;
}

int pasalinti_elementa_pradzia() {
    if (pradzia == nullptr) return -1;
    sarasas* el = pradzia;
    int sal = el->duom;
    pradzia = pradzia->kitas;
    if (pradzia == nullptr) pabaiga = nullptr;
    delete el;
    return sal;
}

void spausdinti_sarasa() {
    sarasas* pr = pradzia;
    while (pr != nullptr) {
        cout << pr->duom << " ";
        pr = pr->kitas;
    }
    cout << endl;
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

int RastiDydi(Medis* N) {
    if (N == nullptr) return 0;
    return N->dydis;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int BalansinisKoef(Medis* N) {
    if (N == nullptr) return 0;
    return RastiDydi(N->Kaire) - RastiDydi(N->Desine);
}

Medis* NaujasElementas(int key) {
    Medis* Medis1 = new Medis;
    Medis1->key = key;
    Medis1->Kaire = nullptr;
    Medis1->Desine = nullptr;
    Medis1->dydis = 1;
    return Medis1;
}

Medis* DesinePosukis(Medis* y) {
    Medis* x = y->Kaire;
    Medis* T2 = x->Desine;
    x->Desine = y;
    y->Kaire = T2;
    y->dydis = max(RastiDydi(y->Kaire), RastiDydi(y->Desine)) + 1;
    x->dydis = max(RastiDydi(x->Kaire), RastiDydi(x->Desine)) + 1;
    return x;
}

Medis* KairePosukis(Medis* x) {
    Medis* y = x->Desine;
    Medis* T2 = y->Kaire;
    y->Kaire = x;
    x->Desine = T2;
    x->dydis = max(RastiDydi(x->Kaire), RastiDydi(x->Desine)) + 1;
    y->dydis = max(RastiDydi(y->Kaire), RastiDydi(y->Desine)) + 1;
    return y;
}

Medis* IterptiElementa(Medis* root, int key) {
    if (root == nullptr)
        return NaujasElementas(key);

    if (key < root->key)
        root->Kaire = IterptiElementa(root->Kaire, key);
    else if (key > root->key)
        root->Desine = IterptiElementa(root->Desine, key);
    else
        return root;

    root->dydis = 1 + max(RastiDydi(root->Kaire), RastiDydi(root->Desine));
    int balansas = BalansinisKoef(root);

    if (balansas > 1 && key < root->Kaire->key)
        return DesinePosukis(root);

    if (balansas < -1 && key > root->Desine->key)
        return KairePosukis(root);

    if (balansas > 1 && key > root->Kaire->key) {
        root->Kaire = KairePosukis(root->Kaire);
        return DesinePosukis(root);
    }

    if (balansas < -1 && key < root->Desine->key) {
        root->Desine = DesinePosukis(root->Desine);
        return KairePosukis(root);
    }
    return root;
}

void spausdinti_medi(Medis* root) {
    if (root != nullptr) {
        spausdinti_medi(root->Kaire);
        cout << root->key << " ";
        spausdinti_medi(root->Desine);
    }
}

Medis* sarasas_i_avl() {
    sarasas* pr = pradzia;
    Medis* root = nullptr;
    while (pr != nullptr) {
        root = IterptiElementa(root, pr->duom);
        pr = pr->kitas;
    }
    return root;
}