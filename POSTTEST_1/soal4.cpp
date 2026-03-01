#include <iostream>
using namespace std;

void tukarVariabel(int* a, int* b) {
    int temp = *a;    
    *a = *b;          
    *b = temp;        
}

int main() {
    int angka1, angka2;
    
    cout << "Masukkan nilai pertama  : ";
    cin >> angka1;
    cout << "Masukkan nilai kedua    : ";
    cin >> angka2;
    
    cout << "\n====== SEBELUM DITUKAR ======" << endl;
    cout << "Nilai pertama : " << angka1 << " | Alamat : " << &angka1 << endl;
    cout << "Nilai kedua : " << angka2 << "   | Alamat : " << &angka2 << endl;
    
    tukarVariabel(&angka1, &angka2);
    
    cout << "\n====== SESUDAH DITUKAR ======" << endl;
    cout << "Nilai pertama : " << angka1 << " | Alamat : " << &angka1 << endl;
    cout << "Nilai kedua : " << angka2 << "   | Alamat: " << &angka2 << endl;
    
    return 0;
}