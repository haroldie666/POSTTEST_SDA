#include <iostream>
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    float ipk;
};

int main() {
    const int data_mhs = 5;
    Mahasiswa mahasiswa[data_mhs];
    
    cout << "=== Masukkan Data Mahasiswa ===" << endl;
    for(int i = 0; i < data_mhs; i++) {
        cout << "\nNama : ";
        getline(cin, mahasiswa[i].nama);
        cout << "NIM    : ";
        getline(cin, mahasiswa[i].nim);
        cout << "IPK    : ";
        cin >> mahasiswa[i].ipk;
        cin.ignore(); // Membersihkan karakter newline
    }

    Mahasiswa IPKTertinggi = mahasiswa[0];
    for(int i = 1; i < data_mhs; i++) {
        if(mahasiswa[i].ipk > IPKTertinggi.ipk) {
            IPKTertinggi = mahasiswa[i];
        }
    }
    
    cout << "\n=== Mahasiswa dengan IPK Tertinggi ===" << endl;
    cout << "Nama : " << IPKTertinggi.nama << endl;
    cout << "NIM  : " << IPKTertinggi.nim << endl;
    cout << "IPK  : " << IPKTertinggi.ipk << endl;
    
    return 0;
}
