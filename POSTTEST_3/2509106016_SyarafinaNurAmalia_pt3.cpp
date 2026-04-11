#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <limits>
#include <tabulate/table.hpp>

using namespace std;
using namespace tabulate;

#define MAX 100 

struct Kereta {
    int nomor;
    string nama;
    string asal;
    string stasiunAwal;
    string tujuan;
    string stasiunAkhir;
    string jadwalJam;
    int harga;
};

struct Penumpang {
    string penumpang;
    Kereta detailKereta;
};

Penumpang stackRiwayat[MAX];
int top = -1; 

Penumpang queueAntrian[MAX];
int front = -1, rear = -1; 

void clearing() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

string formatRupiah(int harga) {
    string s = to_string(harga);
    int n = s.length();
    for (int i = n - 3; i > 0; i -= 3) {
        s.insert(i, ".");
    }
    return "Rp " + s;
}

int inputInt(string prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val && val >= 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        } else {
            cout << "Input harus berupa angka\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void swapKereta(Kereta* a, Kereta* b) {
    Kereta temp = *a;
    *a = *b;
    *b = temp;
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

void selectionSort(Kereta* arr, int n) {
    if (n == 0) return;
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->harga < (arr + min_idx)->harga) {
                min_idx = j;
            }
        }
        if (min_idx != i) swapKereta((arr + i), (arr + min_idx));
    }
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
        if (toLower((L + i)->nama) <= toLower((R + j)->nama)) {
            *(arr + k) = *(L + i); i++;
        } else {
            *(arr + k) = *(R + j); j++;
        }
        k++;
    }
    while (i < n1) { *(arr + k) = *(L + i); i++; k++; }
    while (j < n2) { *(arr + k) = *(R + j); j++; k++; }
    delete[] L; delete[] R;
}

void mergeSort(Kereta* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void linearSearch(Kereta* arr, int n, string asal, string tujuan) {
    bool ditemukan = false;
    string lowAsal = toLower(asal);
    string lowTujuan = toLower(tujuan);

    cout << "\n--- Hasil Pencarian Rute ---\n";
    for (int i = 0; i < n; i++) {
        if (toLower((arr + i)->asal) == lowAsal && toLower((arr + i)->tujuan) == lowTujuan) {
            cout << "-> [" << (arr + i)->nomor << "] " << (arr + i)->nama 
                 << " | " << (arr + i)->jadwalJam << " | " << formatRupiah((arr + i)->harga) << "\n";
            ditemukan = true;
        }
    }
    if (!ditemukan) cout << "Rute tidak ditemukan.\n";
}

void jumpSearch(Kereta* arr, int n, int target) {
    int step = sqrt(n);
    int prev = 0;

    while ((arr + min(step, n) - 1)->nomor < target) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            cout << "Nomor kereta " << target << " tidak ditemukan.\n";
            return;
        }
    }

    while ((arr + prev)->nomor < target) {
        prev++;
        if (prev == min(step, n)) {
            cout << "Nomor kereta " << target << " tidak ditemukan.\n";
            return;
        }
    }

    if ((arr + prev)->nomor == target) {
        cout << "\nData Ditemukan :\n";
        cout << "KA " << (arr + prev)->nama << " | " << (arr + prev)->asal << " -> " << (arr + prev)->tujuan << "\n";
    } else {
        cout << "Nomor kereta " << target << " tidak ditemukan\n";
    }
}

bool isStackEmpty() { 
    return top < 0; } 
bool isStackFull() { 
    return top >= MAX - 1; }

void pushRiwayat(Penumpang* p) {
    if (isStackFull()) {
        cout << "Riwayat transaksi penuh (overflow)" << endl; 
        return;
    }
    top++;
    *(stackRiwayat + top) = *p; 
}

void popRiwayat() {
    if (isStackEmpty()) {
        cout << "Tidak ada riwayat transaksi (underflow)" << endl; 
        return;
    }
    Penumpang p = *(stackRiwayat + top);
    top--;
    cout << "Transaksi terakhir atas nama " << p.penumpang << " berhasil dihapus dari riwayat" << endl;
}

void tampilkanRiwayat() {
    cout << "\n--- DAFTAR RIWAYAT TRANSAKSI ---" << endl;
    if (isStackEmpty()) {
        cout << "Riwayat transaksi kosong" << endl;
        return;
    }
    Penumpang* ptr = stackRiwayat + top;
    for (int i = top; i >= 0; i--) {
        cout << "Pemesanan : " << ptr->penumpang << " | KA : " << ptr->detailKereta.nama << endl;
        ptr--; 
    }
}

bool isQueueEmpty() { 
    return front == -1 || front > rear; } 
bool isQueueFull() { 
    return rear == MAX - 1; } 

void enqueueAntrian(Penumpang* p) {
    if (isQueueFull()) {
        cout << "Antrian penuh (overflow)" << endl; 
        return;
    }
    if (front == -1) front = 0; 
    rear++;
    *(queueAntrian + rear) = *p; 
    cout << "Penumpang " << p->penumpang << " berhasil masuk antrian" << endl;
}

void dequeueAntrian() {
    if (isQueueEmpty()) {
        cout << "Antrian kosong (underflow)" << endl; 
        return;
    }
    Penumpang p = *(queueAntrian + front);
    cout << "\n--- MEMPROSES TIKET ---" << endl;
    cout << "Nama Penumpang : " << p.penumpang << endl;
    cout << "Rute Kereta    : " << p.detailKereta.asal << " -> " << p.detailKereta.tujuan << endl;
    cout << "Status         : Berhasil diproses" << endl;
    pushRiwayat(&p);
    front++;
    if (isQueueEmpty()) front = rear = -1;
}

void readAntrian() {
    cout << "\n--- DAFTAR ANTRIAN PEMBELIAN TIKET ---" << endl;
    if (isQueueEmpty()) {
        cout << "Belum ada antrian" << endl;
        return;
    }
    Penumpang* ptr = queueAntrian + front;
    for (int i = front; i <= rear; i++) {
        cout << "[" << i + 1 << "] Nama: " << ptr->penumpang 
             << " | Tujuan: " << ptr->detailKereta.tujuan << endl;
        ptr++; 
    }
}

void createJadwal(Kereta* arr, int* n) {
    if (*n >= MAX) {
        cout << "\n[Error] Kapasitas data penuh!\n";
        return;
    }
    cout << "\n--- Tambah Data Kereta ---\n";
    (arr + *n)->nomor = inputInt("Nomor kereta     : ");
    cout << "Nama kereta      : "; getline(cin, (arr + *n)->nama);
    cout << "Kota asal        : "; getline(cin, (arr + *n)->asal);
    cout << "Stasiun awal     : "; getline(cin, (arr + *n)->stasiunAwal);
    cout << "Kota tujuan      : "; getline(cin, (arr + *n)->tujuan);
    cout << "Stasiun akhir    : "; getline(cin, (arr + *n)->stasiunAkhir);
    cout << "Jam (HH:MM)      : "; getline(cin, (arr + *n)->jadwalJam);
    (arr + *n)->harga = inputInt("Harga tiket      : ");
    (*n)++;
    cout << "\nData berhasil ditambahkan\n";
}

void peekSistem() {
    cout << "\n--- Data Penumpang (Peek) ---" << endl;
    if (!isQueueEmpty()) {
        Penumpang depan = *(queueAntrian + front);
        cout << "Antrian terdepan    : " << depan.penumpang << " (Tujuan " << depan.detailKereta.tujuan << ")" << endl;
    } else cout << "Antrian terdepan : antrian kosong" << endl;

    if (!isStackEmpty()) {
        Penumpang terakhir = *(stackRiwayat + top);
        cout << "Transaksi terakhir: " << terakhir.penumpang << " (KA " << terakhir.detailKereta.nama << ")" << endl;
    } else 
    cout << "Transaksi terakhir: transaksi kosong" << endl;
}

void readJadwal(Kereta* arr, int n) {
    if (n == 0) {
        cout << "\nBelum ada data jadwal kereta.\n";
        return;
    }
    Table jadwalTable;
    jadwalTable.add_row({"No KA", "Nama Kereta", "Kota Asal", "Stasiun Awal", "Kota Tujuan", "Stasiun Akhir", "Jam", "Harga"});
    for (size_t i = 0; i < 8; ++i) {
        jadwalTable[0][i].format().font_color(Color::yellow).font_align(FontAlign::center);
    }
    for (int i = 0; i < n; i++) {
        jadwalTable.add_row({
            to_string((arr + i)->nomor), (arr + i)->nama, (arr + i)->asal, (arr + i)->stasiunAwal,
            (arr + i)->tujuan, (arr + i)->stasiunAkhir, (arr + i)->jadwalJam, formatRupiah((arr + i)->harga)
        });
    }
    cout << "\n" << jadwalTable << "\n";
}

int main() {
    Kereta jadwal[MAX];
    int jumlahData = 0;
    int pilihan;

    jadwal[0] = {101, "Argo Bromo", "Jakarta", "Gambir", "Surabaya", "Pasar Turi", "08:00", 600000};
    jadwal[1] = {103, "Taksaka", "Jakarta", "Gambir", "Yogyakarta", "Tugu", "09:00", 450000};
    jadwal[2] = {102, "Turangga", "Bandung", "Kiaracondong", "Surabaya", "Gubeng", "18:00", 500000};
    jadwal[3] = {104, "Mutiara Selatan", "Semarang", "Tugu", "Jakarta", "Gambir", "10:00", 700000};
    jumlahData = 4;

    do {
        clearing();
        cout << "====== SISTEM LAYANAN KERETA API SENKU WOOSH ======\n";
        cout << "1. Lihat Jadwal Kereta\n";
        cout << "2. Tambah Data Kereta\n";
        cout << "3. Cari Kereta Berdasarkan Rute (Linear Search)\n";
        cout << "4. Cari Kereta Berdasarkan Nomor (Jump Search)\n";
        cout << "5. Urutkan Nama Kereta (Merge Sort)\n";
        cout << "6. Urutkan Harga Tiket (Selection Sort)\n";
        cout << "7. Pesan Tiket (Enqueue)\n";
        cout << "8. Pemrosesan Tiket (Dequeue)\n";
        cout << "9. Batalkan Riwayat Terakhir (Pop)\n";
        cout << "10. Lihat Penumpang Terdepan & Riwayat Terakhir (Peek)\n";
        cout << "11. Lihat Semua Antrian (Queue)\n";
        cout << "12. Lihat Semua Riwayat (Stack)\n";
        cout << "0. Logout\n";
        pilihan = inputInt("\nMasukkan pilihan Anda: ");

        clearing();
        switch (pilihan) {
            case 1: readJadwal(jadwal, jumlahData); 
            break;
            case 2: createJadwal(jadwal, &jumlahData); 
            break;
            case 3: {
                string asal, tujuan;
                cout << "Masukkan kota asal  : "; getline(cin, asal);
                cout << "Masukkan kota tujuan: "; getline(cin, tujuan);
                linearSearch(jadwal, jumlahData, asal, tujuan);
                break;
            }
            case 4: {
                insertionSort(jadwal, jumlahData); 
                int target = inputInt("Masukkan Nomor KA: ");
                jumpSearch(jadwal, jumlahData, target);
                break;
            }
            case 5:
                if (jumlahData > 0) {
                    mergeSort(jadwal, 0, jumlahData - 1);
                    cout << "Data diurutkan berdasarkan nama\n";
                    readJadwal(jadwal, jumlahData);
                }
                break;
            case 6:
                if (jumlahData > 0) {
                    selectionSort(jadwal, jumlahData);
                    cout << "Data diurutkan berdasarkan harga\n";
                    readJadwal(jadwal, jumlahData);
                }
                break;
            case 7: {
                readJadwal(jadwal, jumlahData);
                int no = inputInt("Masukkan Nomor KA yang ingin dipesan : ");
                bool tersedia = false;
                for (int i = 0; i < jumlahData; i++) {
                    if ((jadwal + i)->nomor == no) {
                        Penumpang p;
                        cout << "Masukkan nama Anda: "; 
                        getline(cin, p.penumpang);
                        p.detailKereta = *(jadwal + i);
                        enqueueAntrian(&p);
                        tersedia = true; 
                        break;
                    }
                }
                if (!tersedia) cout << "Nomor KA tidak ditemukan\n";
                break;
            }
            case 8: dequeueAntrian(); 
            break;
            case 9: popRiwayat(); 
            break;
            case 10: peekSistem(); 
            break;
            case 11: readAntrian(); 
            break;
            case 12: tampilkanRiwayat(); 
            break;
            case 0: cout << "Terima kasih telah menggunakan program layanan kami\n"; break;
            default: cout << "Pilihan tidak valid\n";
        }

        if (pilihan != 0) {
            cout << "\nTekan enter untuk kembali...";
            cin.get();
        }
    } while (pilihan != 0);

    return 0;
}