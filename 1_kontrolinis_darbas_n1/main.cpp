#include <iostream>

using namespace std;
void Maz_ind(int n, int M[100], int &k, int &m);
void san_elem(int M[100], int n, int &pirmas_neig, int &antras_neig, int &sandauga);
void Peform_Masyv(int M[100], int n);
int main() {
    int n, M[100], k = 0, num = 0, m, pirmas_neig = -1, antras_neig = -1, sandauga = 1;
    cout << "Iveskite kiek elementu bus masyve: " << endl;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Iveskite " << i + 1 << " elementa masyve: ";
        cin >> M[i];
    }
    while (num != 4) {
        cout << "Pasirinkite veiksma: " << endl;
        cout << "1. Rasti maziausia elemento indeksa. " << endl;
        cout << "2. Sandauga elementu, esanciu tarp pirmojo neigiamo elemento ir antrojo neigiamo elemento." << endl;
        cout << "3. Performuoti masyva, taip kad pirmiausia eit elementai, kurie pagal absoliucia reiksme nedidesni nei 3, o paskui visi like."<<endl;
        cout << "4. Iseiti." << endl;
        cin >> num;
        switch (num) {
            case 1:
                Maz_ind(n, M, k, m);
                break;
            case 2:
                san_elem(M, n, pirmas_neig, antras_neig, sandauga);
                break;
            case 3:
                Peform_Masyv(M, n);
                break;
            case 4:
                cout << "Jus isejote is programos" << endl;
                break;
            default:
                cout << "Tokio pasirinkimo nera, bandykite dar karta" << endl;
        }
    }
    return 0;
}

void Maz_ind(int n, int M[100], int &k, int &m) {
    m = M[0];
    k = 0;
    for (int i = 1; i < n; i++) {
        if (M[i] < m) {
            m = M[i];
            k = i;
        }
    }
    cout << "Maziausio masyvo elemento indeksas: " << k << endl;
}

void san_elem(int M[100], int n, int &pirmas_neig, int &antras_neig, int &sandauga) {
    int neig_skaic = 0;
    pirmas_neig = -1;
    antras_neig = -1;
    sandauga = 1;

    for (int i = 0; i < n; i++) {
        if (M[i] < 0) {
            neig_skaic++;
            if (pirmas_neig == -1) {
                pirmas_neig = i;
            } else if (antras_neig == -1) {
                antras_neig = i;
            }
        }
    }

    if (neig_skaic == 2) {
        for (int i = pirmas_neig + 1; i < antras_neig; i++) {
            sandauga = M[i]*sandauga;
        }
        cout << "Rezultatas: " << sandauga << endl;
    } else if (neig_skaic == 1) {
        cout << "Truksta vieno neigiamo elemento, kad butu ivykdyta salyga" << endl;
    } else {
        cout << "Truksta dvieju neigiamu elementu, kad butu ivykdyta salyga" << endl;
    }
}

void Peform_Masyv(int M[100], int n) {
    int nauj_M[100], in=0;
    for (int i = 0; i < n; i++) {
        if (abs(M[i]) <= 3) {
            nauj_M[in++] = M[i];
        }
    }
    for (int i = 0; i < n; i++) {
        if (abs(M[i]) > 3) {
            nauj_M[in++] = M[i];
        }
    }
    for (int i = 0; i < n; i++) {
        M[i] = nauj_M[i];
    }
    cout << "Performuotas masyvas: ";
    for (int i = 0; i < n; i++) {
        cout << M[i] << " ";
    }
    cout << endl;
}
