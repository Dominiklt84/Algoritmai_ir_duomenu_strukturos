#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

int keitimai = 0;  // Globalus keitimų skaitiklis

void sujungti(int arr[], int kairys, int vidurys, int desinys) {
    int dydis1 = vidurys - kairys + 1;
    int dydis2 = desinys - vidurys;

    int* kaire = new int[dydis1];
    int* desine = new int[dydis2];

    for (int i = 0; i < dydis1; i++)
        kaire[i] = arr[kairys + i];
    for (int j = 0; j < dydis2; j++)
        desine[j] = arr[vidurys + 1 + j];

    int i = 0, j = 0, k = kairys;
    while (i < dydis1 && j < dydis2) {
        if (kaire[i] <= desine[j]) {
            arr[k++] = kaire[i++];
        } else {
            arr[k++] = desine[j++];
        }
        keitimai++;  // įrašymas = keitimas vietomis
    }

    while (i < dydis1) {
        arr[k++] = kaire[i++];
        keitimai++;
    }

    while (j < dydis2) {
        arr[k++] = desine[j++];
        keitimai++;
    }

    delete[] kaire;
    delete[] desine;
}

void MergeSort(int arr[], int kairys, int desinys) {
    if (kairys < desinys) {
        int vidurys = (kairys + desinys) / 2;
        MergeSort(arr, kairys, vidurys);
        MergeSort(arr, vidurys + 1, desinys);
        sujungti(arr, kairys, vidurys, desinys);
    }
}

int main() {
    int n = 100000;
    ifstream inputFile("skaiciai.txt");
    if (!inputFile) {
        cout << "Nepavyko atidaryti failo!" << endl;
        return 1;
    }

    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        inputFile >> arr[i];
    }
    inputFile.close();

    auto start = high_resolution_clock::now();
    MergeSort(arr, 0, n - 1);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Rūšiavimas truko: " << duration.count() << " ms" << endl;
    cout << "Keitimų vietomis skaičius: " << keitimai << endl;

    ofstream outputFile("output.txt");
    if (!outputFile) {
        cout << "Nepavyko atidaryti failo įrašymui!" << endl;
        delete[] arr;
        return 1;
    }

    outputFile << "Masyvas po rūšiavimo: ";
    for (int i = 0; i < n; i++) {
        outputFile << arr[i] << " ";
    }
    outputFile << endl;
    outputFile << "Rūšiavimo trukmė: " << duration.count() << " ms" << endl;
    outputFile << "Keitimų vietomis skaičius: " << keitimai << endl;
    outputFile.close();

    delete[] arr;
    return 0;
}
