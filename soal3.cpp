#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// ============================================
// BAGIAN 1: Struktur Data Barang (struct)
// ============================================
struct Barang {
    string kodeBarang;
    string namaBarang;
    double harga;
    int stok;
};

// Data disimpan dalam vector
vector<Barang> inventaris;

// ============================================
// BAGIAN 2: Fungsi Validasi Input
// ============================================

// Validasi harga (tidak boleh negatif)
double inputHarga() {
    double harga;
    while (true) {
        cout << "Masukkan harga barang : Rp ";
        cin >> harga;
        if (cin.fail() || harga < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[ERROR] Harga tidak boleh negatif! Silakan masukkan ulang." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return harga;
        }
    }
}

// Validasi stok (tidak boleh negatif)
int inputStok() {
    int stok;
    while (true) {
        cout << "Masukkan stok barang  : ";
        cin >> stok;
        if (cin.fail() || stok < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[ERROR] Stok tidak boleh negatif! Silakan masukkan ulang." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return stok;
        }
    }
}

// ============================================
// BAGIAN 3: Fungsi-Fungsi Menu
// ============================================

// Fungsi 1: Tambah Barang
void tambahBarang() {
    Barang b;
    cout << "\n===========================================" << endl;
    cout << "           Tambah Barang Baru" << endl;
    cout << "===========================================" << endl;

    cout << "Masukkan kode barang  : ";
    getline(cin, b.kodeBarang);

    cout << "Masukkan nama barang  : ";
    getline(cin, b.namaBarang);

    b.harga = inputHarga();
    b.stok  = inputStok();

    inventaris.push_back(b);
    cout << "\n[SUKSES] Barang \"" << b.namaBarang << "\" berhasil ditambahkan!" << endl;
}

// Fungsi 2: Tampilkan Semua Barang
void tampilkanSemuaBarang() {
    cout << "\n===========================================" << endl;
    cout << "         Daftar Semua Barang" << endl;
    cout << "===========================================" << endl;

    if (inventaris.empty()) {
        cout << "[INFO] Belum ada data barang dalam inventaris." << endl;
        return;
    }

    cout << "No | Kode\t| Nama Barang\t| Harga\t\t| Stok" << endl;
    cout << "---------------------------------------------------------------" << endl;

    for (size_t i = 0; i < inventaris.size(); i++) {
        cout << i + 1 << "  | "
             << inventaris[i].kodeBarang << "\t| "
             << inventaris[i].namaBarang << "\t| Rp "
             << inventaris[i].harga << "\t| "
             << inventaris[i].stok << endl;
    }

    cout << "---------------------------------------------------------------" << endl;
    cout << "Total barang: " << inventaris.size() << endl;
}

// Fungsi 3: Cari Barang Harga Tertinggi
void cariBarangHargaTinggi() {
    cout << "\n===========================================" << endl;
    cout << "       Barang dengan Harga Tertinggi" << endl;
    cout << "===========================================" << endl;

    if (inventaris.empty()) {
        cout << "[INFO] Belum ada data barang dalam inventaris." << endl;
        return;
    }

    // Mencari index barang dengan harga tertinggi
    int idxMax = 0;
    for (size_t i = 1; i < inventaris.size(); i++) {
        if (inventaris[i].harga > inventaris[idxMax].harga) {
            idxMax = i;
        }
    }

    cout << "Kode Barang  : " << inventaris[idxMax].kodeBarang << endl;
    cout << "Nama Barang  : " << inventaris[idxMax].namaBarang << endl;
    cout << "Harga        : Rp " << inventaris[idxMax].harga << endl;
    cout << "Stok         : " << inventaris[idxMax].stok << endl;
}

// ============================================
// FUNGSI MAIN - Menu Utama (Loop)
// ============================================
int main() {
    int pilihan;

    do {
        cout << "\n===========================================" << endl;
        cout << "    SISTEM MANAJEMEN INVENTARIS RITEL" << endl;
        cout << "===========================================" << endl;
        cout << " 1. Tambah Barang" << endl;
        cout << " 2. Tampilkan Semua Barang" << endl;
        cout << " 3. Cari Barang Harga Tertinggi" << endl;
        cout << " 0. Keluar" << endl;
        cout << "===========================================" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[ERROR] Input tidak valid! Masukkan angka." << endl;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pilihan) {
            case 1:
                tambahBarang();
                break;
            case 2:
                tampilkanSemuaBarang();
                break;
            case 3:
                cariBarangHargaTinggi();
                break;
            case 0:
                cout << "\nTerima kasih! Program selesai." << endl;
                break;
            default:
                cout << "[ERROR] Pilihan tidak valid! Silakan pilih 0-3." << endl;
        }
    } while (pilihan != 0);

    return 0;
}
