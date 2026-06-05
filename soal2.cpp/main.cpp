#include "TebakKata.h"

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    bersihkanLayar();
    cout << "============================================" << endl;
    cout << "        GAME TEBAK KATA  (Hangman)          " << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "Selamat datang di Game Tebak Kata!" << endl;
    cout << "Masukkan nama Anda: ";
    string namaPemain;
    getline(cin, namaPemain);
    if (namaPemain.empty()) namaPemain = "Pemain";

    bool terusMain = true;

    while (terusMain) {
        bersihkanLayar();
        cout << "============================================" << endl;
        cout << "        GAME TEBAK KATA  (Hangman)          " << endl;
        cout << "============================================" << endl;
        cout << endl;

        int tingkat  = pilihTingkatKesulitan();
        int maxNyawa = maxNyawaDariKesulitan(tingkat);

        KataGame game;
        inisialisasiGame(&game, pilihKataAcak(), maxNyawa);

        char tebakanSalah[ALPHABET_SIZE];
        memset(tebakanSalah, 0, sizeof(tebakanSalah));
        int jumlahSalah = 0;

        // Game loop
        while (game.sisaNyawa > 0 && !cekKataSelesai(&game)) {
            bersihkanLayar();
            cout << "Pemain : " << namaPemain
                 << "  |  Kesulitan : " << namaTingkat(tingkat) << endl;
            cout << "--------------------------------------------" << endl;
            tampilkanStatus(&game, tebakanSalah, jumlahSalah, maxNyawa);

            char huruf = inputHuruf();

            if (huruf == 'h') {
                gunakanPetunjuk(&game);
                cout << "Tekan Enter untuk melanjutkan...";
                cin.ignore(1000, '\n');
                continue;
            }

            if (hurufSudahDitebak(huruf, &game, tebakanSalah, jumlahSalah)) {
                cout << "Huruf '" << huruf << "' sudah pernah ditebak! Coba huruf lain." << endl;
                cout << "Tekan Enter untuk melanjutkan...";
                cin.ignore(1000, '\n');
                continue;
            }

            if (prosesTobakan(&game, tebakanSalah, &jumlahSalah, huruf))
                cout << "Tebakan benar! Huruf '" << huruf << "' ada dalam kata." << endl;
            else
                cout << "Tebakan salah! Huruf '" << huruf << "' tidak ada dalam kata." << endl;

            cout << "Tekan Enter untuk melanjutkan...";
            cin.ignore(1000, '\n');
        }

        // Result
        bersihkanLayar();
        if (cekKataSelesai(&game)) {
            cout << "============================================" << endl;
            cout << "  SELAMAT! Anda berhasil menebak katanya!   " << endl;
            cout << "============================================" << endl;
            cout << "Kata rahasia : " << game.kataAsli << endl;
            int skor = hitungSkor(tingkat, game.sisaNyawa);
            cout << "Skor Anda    : " << skor << endl;
            tambahLeaderboard(namaPemain, skor, tingkat);
        } else {
            cout << "============================================" << endl;
            cout << "    GAME OVER! Nyawa Anda habis.            " << endl;
            cout << "============================================" << endl;
            tampilkanHangman(maxNyawa, maxNyawa);
            cout << "Kata rahasia : " << game.kataAsli << endl;
        }

        tampilkanLeaderboard();
        terusMain = mainLagi();
    }

    cout << endl << "Terima kasih sudah bermain, " << namaPemain << "!" << endl;
    cout << "Sampai jumpa lagi!" << endl;

    return 0;
}