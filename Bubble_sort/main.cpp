#include <iostream>
#include <fstream>
#include <chrono>  // Laiko matavimui
using namespace std;
using namespace std::chrono;

// Atnaujinta funkcija – grąžina sukeitimų skaičių
int bubbleSort(int *array, int size){
    int totalSwaps = 0; // visų sukeitimų skaičius

    for(int i = 0; i < size; i++) {
        int swaps = 0;
        for(int j = 0; j < size - i - 1; j++) {
            if(array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                swaps++;
                totalSwaps++;
            }
        }
        if(swaps == 0)
            break;
    }

    return totalSwaps;
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
    int swapCount = bubbleSort(arr, n);  // Grąžinamas sukeitimų skaičius
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Rūšiavimas truko: " << duration.count() << " ms" << endl;
    cout << "Sukeitimų skaičius: " << swapCount << endl;

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
    outputFile << "Sukeitimų skaičius: " << swapCount << endl;
    outputFile << "Rūšiavimo trukmė: " << duration.count() << " ms" << endl;
    outputFile.close();

    delete[] arr;
    return 0;
}
