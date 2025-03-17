//2. Sukurti steka. Sukurti funkcijas, kurios vykdo duomenu ivedima, bei pasalinima. Realizuoti
//funkcijas,kurios:
//a. 5 pasalintus elementus irasys i vienkrypti ciklini sarasa;
//b. Vienkrypciame cikliniame sarase sukeis vietomis pirma teigiama elementa su paskutiniu
//bei atspausdins pradini ir sukeista ciklini sąraša.
//c. Pasalins is vienkrypcio ciklinio saraso visus elementus bei parodys juos ekrane

#include <iostream>
#include <stack>
using namespace std;

struct CiklinisSarasas {
    int data;
    CiklinisSarasas *next;
};

void addToStack(stack<int>& st, int duom);
void removeFromStack(stack<int>& st, int M[], int& k);
void idetiElementa(CiklinisSarasas*& galas, int value);
void sukeistiPirmaSuPaskutiniu(CiklinisSarasas* galas);
void atspausdintiSarasas(CiklinisSarasas* galas, int ilgis);
void pasalintiVisusElementus(CiklinisSarasas*& galas);

int main() {
    CiklinisSarasas* galas = nullptr;
    int num = 0, duom,M[5],k=0;
    stack<int> st;

    cout << "Iveskite kiek elementu bus: ";
    cin >> num;


    while (num > 0) {
        cout << "Iveskite duomenis: ";
        cin >> duom;
        st.push(duom);
        num--;
    }

    CiklinisSarasas ciklinisSarasas;
    ciklinisSarasas.next = nullptr;

    num = 0;
    while (num != 5) {
        cout << "Pasirinkite veiksma:" << endl;
        cout << "1. Veiksmai su steku." << endl;
        cout << "2. 5 pasalintus elementus irasys i vienkrypti ciklini sarasa." << endl;
        cout << "3. Vienkrypciame cikliniame sarase sukeis vietomis pirma teigiama elementa su paskutiniu bei atspausdins pradini ir sukeista ciklini sarasa." << endl;
        cout << "4. Pasalins is vienkrypcio ciklinio saraso visus elementus bei parodys juos ekrane." << endl;
        cout << "5. Iseiti." << endl;
        cin >> num;

        switch (num) {
            case 1: {
                int s_num = 0;
                while (s_num != 3) {
                    cout << "Pasirinkite veiksma:" << endl;
                    cout << "1. Duomenu ivedimas." << endl;
                    cout << "2. Pasalinimas." << endl;
                    cout << "3. Pabaigti." << endl;
                    cin >> s_num;

                    if (s_num == 1) {
                        cout << "Iveskite duomenis: ";
                        cin >> duom;
                        addToStack(st, duom);
                    } else if (s_num == 2) {
                        cout << "Pasalinimas. ";
                        removeFromStack(st, M, k);
                    }
                }
                break;
            }
            case 2:
                for (int i = 0; i < k; i++) {
                    idetiElementa(galas, M[i]);
                }
                break;
            case 3:
                cout << "Pradinis ciklinis sarasas: ";
            atspausdintiSarasas(galas, k);
            sukeistiPirmaSuPaskutiniu(galas);
            cout << "Sukeistas ciklinis sarasas: ";
            atspausdintiSarasas(galas, k);
                break;
            case 4:
            pasalintiVisusElementus(galas);
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

void addToStack(stack<int>& st, int duom) {
    st.push(duom);
    cout << "I steka pridetas elementas. " << duom << endl;
}
void removeFromStack(stack<int>& st, int M[], int& k) {
    if (!st.empty()) {
        int topElement = st.top();
        st.pop();
        M[k]=topElement;
        k++;
        cout << "Pasalintas elementas is steko: " << topElement << endl;
    } else {
        cout << "Stekas yra tuscias! Negalima pasalinti elemento." << endl;
    }
}
CiklinisSarasas* sukurtiElementa(int value) {
    CiklinisSarasas* naujas = new CiklinisSarasas;
    naujas->data = value;
    naujas->next = nullptr;
    return naujas;
}

void idetiElementa(CiklinisSarasas*& galas, int value) {
    CiklinisSarasas* naujas = sukurtiElementa(value);

    if (galas == nullptr) {
        galas = naujas;
        galas->next = galas;
    } else {
        naujas->next = galas->next;
        galas->next = naujas;
        galas = naujas;
    }
}
void sukeistiPirmaSuPaskutiniu(CiklinisSarasas* galas) {
    if (galas == nullptr || galas->next == galas) {
        return;
    }

    CiklinisSarasas* pirmasTeigiamas = nullptr;
    CiklinisSarasas* paskutinis = galas;
    //pirmas teig elem
    CiklinisSarasas* temp = galas->next;
    while (temp != galas->next) {
        if (temp->data > 0) {
            pirmasTeigiamas = temp;
            break;
        }
        temp = temp->next;
    }
    //nera teig elem
    if (pirmasTeigiamas == nullptr) return;
    //paskutinis elem
    while (paskutinis->next != galas->next) {
        paskutinis = paskutinis->next;
    }
    //tas pats
    if (pirmasTeigiamas == paskutinis) return;
    //keitimas vietomis
    int tempData = pirmasTeigiamas->data;
    pirmasTeigiamas->data = paskutinis->data;
    paskutinis->data = tempData;
}
void atspausdintiSarasas(CiklinisSarasas* galas, int ilgis) {
    if (galas == nullptr) {
        cout << "Sarasas tuscias." << endl;
        return;
    }

    CiklinisSarasas* temp = galas->next;
    for (int i = 0; i < ilgis; i++) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}
void pasalintiVisusElementus(CiklinisSarasas*& galas) {
    if (galas == nullptr) {
        cout << "Sarasas tuscias, nieko nera ka salinti." << endl;
        return;
    }

    CiklinisSarasas* temp = galas->next;
    CiklinisSarasas* toDelete = nullptr;

    //elem atspausdinimas
    cout << "Pries salinant, ciklinis sarasas: ";
    atspausdintiSarasas(galas, 5);

    while (temp != galas) {
        toDelete = temp;
        temp = temp->next;
        delete toDelete;
    }

    delete galas; //paskutinis elem
    galas = nullptr;
    cout << "Visi elementai buvo pašalinti." << endl;
}