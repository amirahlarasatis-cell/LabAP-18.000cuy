#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;


string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}


string buatPola(const string& negara) {
    string pola = negara;
    int panjang = negara.length();

    
    for (int i = 1; i < panjang - 1; i++) {
        if (negara[i] != ' ') {
            
            if (rand() % 10 < 6) {
                pola[i] = '_';
            }
        }
    }

    
    bool adaSembunyi = false;
    for (char c : pola) {
        if (c == '_') { adaSembunyi = true; break; }
    }
    if (!adaSembunyi && panjang > 2) {
        pola[1] = '_';
    }

    return pola;
}

int main() {
    srand(time(0));


    vector<string> daftarNegara = {
        "norway", "oman", "slovakia", "brazil", "france",
        "germany", "japan", "china", "india", "canada",
        "australia", "mexico", "italy", "spain", "egypt",
        "turkey", "greece", "sweden", "poland", "ukraine",
        "portugal", "argentina", "colombia", "peru", "chile",
        "indonesia", "malaysia", "thailand", "vietnam", "philippines",
        "nigeria", "kenya", "ghana", "ethiopia", "tanzania",
        "denmark", "finland", "norway", "iceland", "ireland",
        "austria", "belgium", "netherlands", "switzerland", "hungary",
        "romania", "bulgaria", "croatia", "serbia", "slovakia"
    };


    sort(daftarNegara.begin(), daftarNegara.end());
    daftarNegara.erase(unique(daftarNegara.begin(), daftarNegara.end()), daftarNegara.end());

    int skor = 0;
    char mainLagi = 'y';

   
    while (mainLagi == 'y' || mainLagi == 'Y') {
        // Pilih negara acak
        int idx = rand() % daftarNegara.size();
        string negara = daftarNegara[idx];
        string pola = buatPola(negara);

        cout << "Tebak negara: " << pola << "\n";
        cout << "Negara apakah yang dimaksud? ";

        string jawaban;
        cin >> jawaban;
        jawaban = toLower(jawaban);

        if (jawaban == negara) {
            skor++;
            cout << "Selamat! Anda benar.\n";
        } else {
            cout << "Maaf, jawaban Anda salah. Coba lagi.\n";
            cout << "Jawaban yang benar: " << negara << "\n";
        }

        cout << "Skor Anda: " << skor << "\n";
        cout << "Ingin bermain lagi? (y/n): ";
        cin >> mainLagi;
        cout << "\n";
    }

    cout << "Game selesai :D";

    return 0;
}
