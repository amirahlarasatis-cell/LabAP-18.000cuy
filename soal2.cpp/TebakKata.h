#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;

const int MAX_LEADERBOARD = 5;
const int ALPHABET_SIZE   = 26;

struct KataGame {
    string kataAsli;
    string statusTebakan;
    int    sisaNyawa;
};

struct LeaderboardEntry {
    string namaPemain;
    int    skor;
    string tingkatKesulitan;
};

const string bankKata[] = {
    "apel", "jeruk", "mangga", "pisang", "semangka",
    "komputer", "keyboard", "monitor", "program", "algoritma",
    "kucing", "anjing", "harimau", "gajah", "jerapah",
    "indonesia", "jakarta", "bandung", "surabaya", "yogyakarta",
    "matematika", "fisika", "kimia", "biologi", "sejarah"
};
const int JUMLAH_KATA = 25;

LeaderboardEntry leaderboard[MAX_LEADERBOARD];
int              jumlahLeaderboard = 0;

void bersihkanLayar() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

string namaTingkat(int tingkat) {
    switch (tingkat) {
        case 1: return "Easy";
        case 2: return "Medium";
        case 3: return "Hard";
        default: return "Medium";
    }
}

int maxNyawaDariKesulitan(int tingkat) {
    switch (tingkat) {
        case 1: return 8;
        case 2: return 6;
        case 3: return 4;
        default: return 6;
    }
}

string pilihKataAcak() {
    return bankKata[rand() % JUMLAH_KATA];
}

void inisialisasiGame(KataGame* game, const string& kata, int maxNyawa) {
    game->kataAsli      = kata;
    game->sisaNyawa     = maxNyawa;
    game->statusTebakan = string(kata.size(), '_');
}

bool prosesTobakan(KataGame* game, char tebakanSalah[], int* jumlahSalah, char huruf) {
    huruf = tolower(huruf);
    bool tepat = false;
    for (int i = 0; i < (int)game->kataAsli.size(); i++) {
        if (game->kataAsli[i] == huruf) {
            game->statusTebakan[i] = huruf;
            tepat = true;
        }
    }
    if (!tepat) {
        tebakanSalah[*jumlahSalah] = huruf;
        (*jumlahSalah)++;
        game->sisaNyawa--;
    }
    return tepat;
}

bool cekKataSelesai(const KataGame* game) {
    return game->statusTebakan == game->kataAsli;
}

void tampilkanHangman(int nyawaHilang, int maxNyawa) {
    int stage = (nyawaHilang * 6 + maxNyawa - 1) / maxNyawa;
    if (stage > 6) stage = 6;

    string head = (stage >= 1) ? "O"  : " ";
    string body = (stage >= 2) ? "|"  : " ";
    string larm = (stage >= 3) ? "/"  : " ";
    string rarm = (stage >= 4) ? "\\" : " ";
    string lleg = (stage >= 5) ? "/"  : " ";
    string rleg = (stage >= 6) ? "\\" : " ";

    cout << "  +---+" << endl;
    cout << "  |   |" << endl;
    cout << "  |   " << head << endl;
    cout << "  |  " << larm << body << rarm << endl;
    cout << "  |  " << lleg << " " << rleg << endl;
    cout << "  |"   << endl;
    cout << "=========" << endl;
}

void tampilkanStatus(const KataGame* game, const char tebakanSalah[],
                     int jumlahSalah, int maxNyawa) {
    tampilkanHangman(maxNyawa - game->sisaNyawa, maxNyawa);
    cout << endl;
    cout << "Kata  : ";
    for (char c : game->statusTebakan) cout << c << " ";
    cout << endl;
    cout << "Nyawa : " << game->sisaNyawa << "/" << maxNyawa << endl;
    cout << "Salah : ";
    for (int i = 0; i < jumlahSalah; i++) {
        cout << tebakanSalah[i];
        if (i < jumlahSalah - 1) cout << ", ";
    }
    cout << endl << endl;
}

bool hurufSudahDitebak(char huruf, const KataGame* game,
                        const char tebakanSalah[], int jumlahSalah) {
    huruf = tolower(huruf);
    for (int i = 0; i < jumlahSalah; i++)
        if (tebakanSalah[i] == huruf) return true;
    for (char c : game->statusTebakan)
        if (c == huruf) return true;
    return false;
}

void gunakanPetunjuk(KataGame* game) {
    if (game->sisaNyawa <= 1) {
        cout << "Nyawa tidak cukup untuk menggunakan petunjuk!" << endl;
        return;
    }
    char hurufPertama = '\0';
    for (int i = 0; i < (int)game->kataAsli.size(); i++) {
        if (game->statusTebakan[i] == '_') {
            hurufPertama = game->kataAsli[i];
            break;
        }
    }
    if (hurufPertama == '\0') {
        cout << "Semua huruf sudah terbuka!" << endl;
        return;
    }
    game->sisaNyawa--;
    for (int i = 0; i < (int)game->kataAsli.size(); i++)
        if (game->kataAsli[i] == hurufPertama)
            game->statusTebakan[i] = hurufPertama;
    cout << "Petunjuk: huruf '" << hurufPertama << "' telah dibuka! (-1 nyawa)" << endl;
}

int hitungSkor(int tingkat, int sisaNyawa) {
    int base = 0;
    switch (tingkat) {
        case 1: base = 100; break;
        case 2: base = 200; break;
        case 3: base = 300; break;
    }
    return base + (sisaNyawa * 10);
}

void tambahLeaderboard(const string& nama, int skor, int tingkat) {
    if (jumlahLeaderboard < MAX_LEADERBOARD) {
        leaderboard[jumlahLeaderboard++] = {nama, skor, namaTingkat(tingkat)};
    } else {
        int minIdx = 0;
        for (int i = 1; i < MAX_LEADERBOARD; i++)
            if (leaderboard[i].skor < leaderboard[minIdx].skor) minIdx = i;
        if (skor > leaderboard[minIdx].skor)
            leaderboard[minIdx] = {nama, skor, namaTingkat(tingkat)};
    }
    for (int i = 0; i < jumlahLeaderboard - 1; i++)
        for (int j = 0; j < jumlahLeaderboard - i - 1; j++)
            if (leaderboard[j].skor < leaderboard[j+1].skor) {
                LeaderboardEntry tmp = leaderboard[j];
                leaderboard[j]       = leaderboard[j+1];
                leaderboard[j+1]     = tmp;
            }
}

void tampilkanLeaderboard() {
    cout << endl;
    cout << "============================================" << endl;
    cout << "           LEADERBOARD (Top 5)              " << endl;
    cout << "============================================" << endl;
    if (jumlahLeaderboard == 0) {
        cout << "  (Belum ada skor tersimpan)" << endl;
    } else {
        cout << "  No | Nama              | Skor | Kesulitan" << endl;
        cout << "  ---+-------------------+------+----------" << endl;
        for (int i = 0; i < jumlahLeaderboard; i++) {
            string padded = leaderboard[i].namaPemain;
            while ((int)padded.size() < 17) padded += ' ';
            cout << "  " << (i+1) << "  | " << padded
                 << " | " << leaderboard[i].skor
                 << "  | " << leaderboard[i].tingkatKesulitan << endl;
        }
    }
    cout << "============================================" << endl;
}

int pilihTingkatKesulitan() {
    int pilihan = 0;
    cout << "Pilih Tingkat Kesulitan:" << endl;
    cout << "  1. Easy   (8 nyawa)" << endl;
    cout << "  2. Medium (6 nyawa)" << endl;
    cout << "  3. Hard   (4 nyawa)" << endl;
    cout << "Masukkan pilihan (1-3): ";
    while (!(cin >> pilihan) || pilihan < 1 || pilihan > 3) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Pilihan tidak valid. Masukkan 1, 2, atau 3: ";
    }
    cin.ignore(1000, '\n');
    return pilihan;
}

char inputHuruf() {
    string line;
    while (true) {
        cout << "Masukkan huruf (atau 'h' untuk petunjuk): ";
        getline(cin, line);
        if (line.size() == 1 && isalpha(line[0]))
            return tolower(line[0]);
        cout << "Input tidak valid. Masukkan satu huruf saja." << endl;
    }
}

bool mainLagi() {
    string jawaban;
    cout << endl << "Apakah Anda ingin bermain lagi? (Y/N): ";
    getline(cin, jawaban);
    return (!jawaban.empty() && toupper(jawaban[0]) == 'Y');
}
