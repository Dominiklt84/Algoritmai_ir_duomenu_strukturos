#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main() {
    ifstream inputFile("sk.txt");
    if (!inputFile.is_open()) {
        cout << "Nie udało się otworzyć pliku!" << endl;
        return 1;
    }

    string linia;
    int licznik = 0;

    while (getline(inputFile, linia)) {
        stringstream ss(linia);
        int liczba;
        while (ss >> liczba) {
            licznik++;
        }
    }

    inputFile.close();

    cout << "Liczba znalezionych liczb w pliku: " << licznik << endl;
    return 0;
}
