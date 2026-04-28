/** # Latihan Soal Circular Linked List

## Soal 1: Inventaris Toko Sembako

Kamu diminta membuat fungsi untuk menampilkan daftar barang sembako beserta stoknya yang tersimpan dalam struktur data Circular Linked List. Berbeda dengan linked list biasa, pada Circular Linked List, pointer `next` dari node terakhir tidak menunjuk ke `nullptr`, melainkan kembali menunjuk ke node `head`. 

Lengkapi fungsi untuk melakukan traversal dan mencetak seluruh data sembako tanpa terjebak dalam *infinite loop*.

```c++*/

#include <iostream>
#include <string>
using namespace std;

// Struktur Node untuk Circular Linked List Toko Sembako
struct BarangNode {
    string namaBarang;
    int stok;
    BarangNode* next;

    // Constructor
    BarangNode(string nama, int jumlah) {
        namaBarang = nama;
        stok = jumlah;
        next = nullptr;
    }
};

// Fungsi insert di akhir Circular Linked List untuk membangun data
BarangNode* tambahBarang(BarangNode* head, string nama, int jumlah) {
    BarangNode* newNode = new BarangNode(nama, jumlah);
    if (head == nullptr) {
        newNode->next = newNode; // Menunjuk ke dirinya sendiri (Sirkuler)
        return newNode;
    }
    
    BarangNode* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = head;
    return head;
}

/**
 * @brief Fungsi untuk menampilkan semua barang dalam Circular Linked List.
 * @param head Pointer ke node pertama (head) dari circular linked list.
 * @logic
 * 1. Base case: Jika head adalah nullptr, cetak "Gudang kosong." dan return.
 * 2. Gunakan pointer sementara (temp) yang dimulai dari head.
 * 3. Lakukan perulangan (do-while disarankan) untuk mencetak namaBarang dan stok.
 * 4. Pindah ke node selanjutnya (temp = temp->next).
 * 5. Berhenti ketika temp kembali menunjuk ke head.
 */
void tampilkanStokSembako(BarangNode* head) {
    // --- LENGKAPI KODE DI SINI ---
    if (head==nullptr) {
        cout << "Gudang kosong." << endl;
        return;
    }

    BarangNode* temp = head;

    do{
        cout << "- " << temp->namaBarang << ": " << temp->stok << endl;
        temp = temp->next;
    }

    while (temp!=head);

    // -----------------------------
}

int main() {
    BarangNode* head = nullptr;
    
    head = tambahBarang(head, "Beras", 50);
    head = tambahBarang(head, "Minyak Goreng", 30);
    head = tambahBarang(head, "Gula Pasir", 20);
    head = tambahBarang(head, "Tepung Terigu", 15);

    cout << "Daftar Stok Sembako:" << endl;
    tampilkanStokSembako(head); 
    /* Harusnya output:
       - Beras: 50
       - Minyak Goreng: 30
       - Gula Pasir: 20
       - Tepung Terigu: 15
    */
    
    return 0;
}