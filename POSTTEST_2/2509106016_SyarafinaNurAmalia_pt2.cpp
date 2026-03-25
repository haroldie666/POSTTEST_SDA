#include <iostream>
#include <cstdlib>   // Untuk membersihkan terminal
#include <cmath>     // Untuk sqrt()
#include <algorithm> // Untuk min()
#include <tabulate/table.hpp>

using namespace std;
using namespace tabulate;

struct Kereta {
    int nomor;1
    
    string nama;
    string asal;            
    string stasiunAwal;     
    string tujuan;          
    string stasiunAkhir;    
    string jadwalJam; 
    int harga;
};

void swapKereta(Kereta* a, Kereta* b) {
    Kereta temp = *a; 
    *a = *b;          
    *b = temp;        
}

void readJadwal(Kereta* arr, int n) { // Menampilkan semua jadwal kereta menggunakan pointer
    Table jadwalTable;

    jadwalTable.add_row({"No KA", "Nama Kereta", "Kota Asal", "Stasiun Awal", "Kota Tujuan", "Stasiun Akhir", "Jam", "Harga"});

    for (size_t i = 0; i < 8; ++i) {
        jadwalTable[0][i].format()
            .font_color(Color::yellow)
            .font_align(FontAlign::center);
    }

    for (int i = 0; i < n; i++) {
        jadwalTable.add_row({
            to_string((arr + i)->nomor), 
            (arr + i)->nama,
            (arr + i)->asal,
            (arr + i)->stasiunAwal,
            (arr + i)->tujuan,
            (arr + i)->stasiunAkhir,
            (arr + i)->jadwalJam,
            "Rp " + to_string((arr + i)->harga) 
        });
    }

    cout << "\n" << jadwalTable << "\n";
}

void createJadwal(Kereta* arr, int* n) {
    cout << "\n--- Tambah Data Kereta ---\n";
    cout << "Nomor kereta     : "; cin >> (arr + *n)->nomor;
    cin.ignore(); 
    cout << "Nama kereta      : "; getline(cin, (arr + *n)->nama);
    cout << "Kota asal        : "; getline(cin, (arr + *n)->asal);
    cout << "Stasiun awal     : "; getline(cin, (arr + *n)->stasiunAwal);
    cout << "Kota tujuan      : "; getline(cin, (arr + *n)->tujuan);
    cout << "Stasiun akhir    : "; getline(cin, (arr + *n)->stasiunAkhir);
    cout << "Jam              : "; getline(cin, (arr + *n)->jadwalJam);
    cout << "Harga tiket      : "; cin >> (arr + *n)->harga;
    
    (*n)++; 
    cout << "\nData berhasil ditambahkan\n";
}

void linearSearch(Kereta* arr, int n, string asal, string tujuan) {
    bool tersedia = false;
    cout << "\n---  Linear Search (Rute Kota " << asal << " ke " << tujuan << ") ---\n"; 
    for (int i = 0; i < n; i++) {
        cout << "Iterasi " << i + 1 << ": Mengecek rute " << (arr + i)->asal << " - " << (arr + i)->tujuan << "\n";
        
        if ((arr + i)->asal == asal && (arr + i)->tujuan == tujuan) {
            cout << "Ditemukan kereta Api " << (arr + i)->nama << " (" << (arr + i)->stasiunAwal << " - " << (arr + i)->stasiunAkhir << ") Pukul " << (arr + i)->jadwalJam << "\n";
            tersedia = true;
        }
    }
    if (!tersedia) {
        cout << "Rute " << asal << " ke " << tujuan << " tidak ditemukan dalam jadwal.\n";
    }
}

void insertionSort(Kereta* arr, int n) {
    for (int i = 1; i < n; i++) {
        Kereta key = *(arr + i);
        int j = i - 1;
        while (j >= 0 && (arr + j)->nomor > key.nomor) {
            *(arr + j + 1) = *(arr + j);
            j = j - 1;
        }
        *(arr + j + 1) = key;
    }
}

void jumpSearch(Kereta* arr, int n, int target) {
    insertionSort(arr, n);

    int step = sqrt(n); 
    int prev = 0;       

    cout << "\n---  Jump Search (Cari KA Nomor " << target << ") ---\n";
    
    while ((arr + min(step, n) - 1)->nomor < target) {
        cout << "Jump dari indeks " << prev << " ke " << step << " (Nomor KA di ujung blok : " << (arr + min(step, n) - 1)->nomor << ")\n";
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            cout << "Nomor kereta " << target << " tidak ditemukan.\n";
            return;
        }
    }

    cout << "Melakukan Linear Search dalam blok (mulai indeks " << prev << ")\n";
    while ((arr + prev)->nomor < target) {
        cout << "Indeks data " << prev << " (Nomor : " << (arr + prev)->nomor << ")\n";
        prev++;
        if (prev == min(step, n)) {
            cout << "Nomor kereta " << target << " tidak ditemukan.\n";
            return;
        }
    }

    cout << "Indeks data " << prev << " (Nomor : " << (arr + prev)->nomor << ")\n";
    if ((arr + prev)->nomor == target) {
        cout << "Kereta Api " << (arr + prev)->nama << " berangkat dari " << (arr + prev)->stasiunAwal << " pukul " << (arr + prev)->jadwalJam << "\n";
    } else {
        cout << "Nomor kereta " << target << " tidak ditemukan.\n";
    }
}

void selectionSort(Kereta* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->harga < (arr + min_idx)->harga) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swapKereta(&(arr[i]), &(arr[min_idx]));
        }
    }
    cout << "\nData berhasil diurutkan berdasarkan harga termurah (Selection Sort)\n";
}

void merge(Kereta* arr, int left, int mid, int right) {
    int n1 = mid - left + 1; 
    int n2 = right - mid;    

    Kereta* L = new Kereta[n1]; 
    Kereta* R = new Kereta[n2]; 

    for (int i = 0; i < n1; i++) *(L + i) = *(arr + left + i); 
    for (int j = 0; j < n2; j++) *(R + j) = *(arr + mid + 1 + j); 

    int i = 0, j = 0, k = left; 
    while (i < n1 && j < n2) { 
        if ((L + i)->nama <= (R + j)->nama) {
            *(arr + k) = *(L + i);
            i++;
        } else {
            *(arr + k) = *(R + j); 
            j++; 
        }
        k++; 
    }

    while (i < n1) { *(arr + k) = *(L + i); i++; k++; } 
    while (j < n2) { *(arr + k) = *(R + j); j++; k++; } 

    delete[] L; 
    delete[] R; 
}

void mergeSort(Kereta* arr, int left, int right) {
    if (left < right) { 
        int mid = left + (right - left) / 2; 
        mergeSort(arr, left, mid);           
        mergeSort(arr, mid + 1, right);      
        merge(arr, left, mid, right);        
    }
}

int main() {
    Kereta jadwal[100]; 
    int jumlahData = 0;
    int pilihan;

    jadwal[0] = {101, "Argo Bromo", "Jakarta", "Gambir", "Surabaya", "Pasar Turi", "08:00", 600000};
    jadwal[1] = {103, "Taksaka", "Jakarta", "Gambir", "Yogyakarta", "Tugu", "09:00", 450000};
    jadwal[2] = {102, "Turangga", "Bandung", "Kiaracondong", "Surabaya", "Gubeng", "18:00", 500000};
    jadwal[3] = {104, "Kereta Api", "Semarang", "Tugu", "Jakarta", "Gambir", "10:00", 700000};
    jumlahData = 4;

    do {
        system("cls"); 

        cout << "\n====== SISTEM LAYANAN KERETA API SENKU WOOSH ======\n";
        cout << "1. Lihat Jadwal Kereta\n";
        cout << "2. Tambah Data Kereta\n";
        cout << "3. Cari Kereta Berdasarkan Rute (Linear Search)\n";
        cout << "4. Cari Kereta Berdasarkan Nomor (Jump Search)\n";
        cout << "5. Urutan Nama Kereta Dari A-Z (Merge Sort)\n";
        cout << "6. Urutan Harga Tiket Termurah (Selection Sort)\n";
        cout << "0. Logout\n"; 
        cout << "\nSilakan masukkan pilihan Anda : ";
        cin >> pilihan;
        cin.ignore(); 

        system("cls"); 

        switch (pilihan) {
            case 1:
                readJadwal(jadwal, jumlahData);
                break;
            case 2:
                createJadwal(jadwal, &jumlahData);
                break;
            case 3: {
                string asal, tujuan;
                cout << "Masukkan kota asal   : "; 
                getline(cin, asal); 
                cout << "Masukkan kota tujuan : "; 
                getline(cin, tujuan);
                linearSearch(jadwal, jumlahData, asal, tujuan);
                break;
            }
            case 4: {
                int no;
                cout << "Masukkan nomor kereta: "; cin >> no;
                cin.ignore();
                jumpSearch(jadwal, jumlahData, no);
                break;
            }
            case 5:
                mergeSort(jadwal, 0, jumlahData - 1);
                cout << "\nData berhasil diurutkan berdasarkan nama (Merge Sort).\n";
                readJadwal(jadwal, jumlahData);
                break;
            case 6:
                selectionSort(jadwal, jumlahData);
                readJadwal(jadwal, jumlahData);
                break;
            case 0:
                cout << "Terima kasih telah menggunakan program layanan kami\n";
                break;
            default:
                cout << "Pilihan tidak valid\n";
        }

        if (pilihan != 0) {
            cout << "\nTekan enter untuk melanjutkan...";
            cin.get(); 
        }

    } while (pilihan != 0);

    return 0;
}