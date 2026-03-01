#include <iostream>
using namespace std;

void reverseArray(int* arr, int n) {
    int* sebelum = arr;      
    int* sesudah = arr + n - 1;
    
    while (sebelum < sesudah) {
        int temp = *sebelum;
        *sebelum = *sesudah;
        *sesudah = temp;
        sebelum++;
        sesudah--;
    }
}

int main() {
    int prima[7] = {2, 3, 5, 7, 11, 13, 17};
    int n = 7;
    
    cout << "======= Data Sebelum Dibalik =======" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "Index\t| Nilai\t| Alamat memori" << endl;
    cout << "---------------------------------------------" << endl;
    for (int* ptr = prima; ptr < prima + n; ptr++) {
        cout << (ptr - prima) << "\t| " << *ptr << "\t| " << ptr << endl;
    }
    cout << endl;
    
    reverseArray(prima, n);
    
    cout << "======= Data Sesudah Dibalik =======" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "Index\t| Nilai\t| Alamat memori" << endl;
    cout << "---------------------------------------------" << endl;
    for (int* ptr = prima; ptr < prima + n; ptr++) {
        cout << (ptr - prima) << "\t| " << *ptr << "\t| " << ptr << endl;
    }

    return 0;
}