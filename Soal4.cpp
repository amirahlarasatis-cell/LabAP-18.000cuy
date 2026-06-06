#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Minesweeper {
private:
    int size;
    int bombCount;

    char board[10][10];
    bool opened[10][10];
    bool flagged[10][10];

    time_t startTime;
    bool gameOver;

public:
    Minesweeper() {
        size = 0;
        bombCount = 0;
        gameOver = false;
    }

    void initializeGame() {
        do {
            cout << "Masukkan ukuran papan (4 - 10): ";
            cin >> size;
        } while (size < 4 || size > 10);

        int maxBombs = size * size - 1;

        do {
            cout << "Masukkan jumlah bom (1 - " << maxBombs << "): ";
            cin >> bombCount;
        } while (bombCount < 1 || bombCount > maxBombs);

        gameOver = false;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                board[i][j] = '0';
                opened[i][j] = false;
                flagged[i][j] = false;
            }
        }

        placeBombs();
        calculateNumbers();

        startTime = time(NULL);
    }

    void placeBombs() {
        int placed = 0;

        while (placed < bombCount) {
            int r = rand() % size;
            int c = rand() % size;

            if (board[r][c] != '*') {
                board[r][c] = '*';
                placed++;
            }
        }
    }

    void calculateNumbers() {
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {

                if (board[r][c] == '*')
                    continue;

                int count = 0;

                for (int dr = -1; dr <= 1; dr++) {
                    for (int dc = -1; dc <= 1; dc++) {

                        int nr = r + dr;
                        int nc = c + dc;

                        if (nr >= 0 && nr < size &&
                            nc >= 0 && nc < size &&
                            board[nr][nc] == '*') {
                            count++;
                        }
                    }
                }

                board[r][c] = count + '0';
            }
        }
    }

    void displayBoard(bool revealAll = false) {

        int flagsUsed = 0;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (flagged[i][j])
                    flagsUsed++;
            }
        }

        cout << "\nBom belum ditandai : "
             << bombCount - flagsUsed << endl;

        cout << "Waktu : "
             << (int)(time(NULL) - startTime)
             << " detik\n";

        cout << "\n   ";

        for (int c = 0; c < size; c++)
            cout << c + 1 << " ";

        cout << endl;

        for (int r = 0; r < size; r++) {

            if (r + 1 < 10)
                cout << r + 1 << "  ";
            else
                cout << r + 1 << " ";

            for (int c = 0; c < size; c++) {

                if (revealAll) {
                    cout << board[r][c] << " ";
                }
                else if (flagged[r][c]) {
                    cout << "F ";
                }
                else if (!opened[r][c]) {
                    cout << "# ";
                }
                else {
                    cout << board[r][c] << " ";
                }
            }

            cout << endl;
        }

        cout << endl;
    }

    void floodFill(int r, int c) {

        if (r < 0 || r >= size ||
            c < 0 || c >= size)
            return;

        if (opened[r][c])
            return;

        if (flagged[r][c])
            return;

        opened[r][c] = true;

        if (board[r][c] != '0')
            return;

        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {

                if (dr != 0 || dc != 0)
                    floodFill(r + dr, c + dc);
            }
        }
    }

    void openCell(int r, int c) {

        if (flagged[r][c]) {
            cout << "Kotak ditandai! Hapus tanda dulu.\n";
            return;
        }

        if (opened[r][c]) {
            cout << "Kotak sudah dibuka.\n";
            return;
        }

        if (board[r][c] == '*') {
            gameOver = true;
            return;
        }

        if (board[r][c] == '0')
            floodFill(r, c);
        else
            opened[r][c] = true;
    }

    void toggleFlag(int r, int c) {

        if (opened[r][c]) {
            cout << "Kotak sudah dibuka.\n";
            return;
        }

        flagged[r][c] = !flagged[r][c];
    }

    bool checkWin() {

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {

                if (board[i][j] == '*' &&
                    !flagged[i][j])
                    return false;

                if (board[i][j] != '*' &&
                    flagged[i][j])
                    return false;
            }
        }

        return true;
    }

    void play() {

        initializeGame();

        while (!gameOver) {

            displayBoard();

            if (checkWin()) {

                cout << "\n================================\n";
                cout << "SELAMAT! ANDA MENANG!\n";
                cout << "Waktu: "
                     << (int)(time(NULL) - startTime)
                     << " detik\n";
                cout << "================================\n";

                displayBoard(true);
                return;
            }

            int choice;
            int row;
            int col;

            cout << "1. Buka Kotak\n";
            cout << "2. Tandai / Hapus Tanda\n";
            cout << "Pilihan : ";
            cin >> choice;

            cout << "Baris (1-" << size << "): ";
            cin >> row;

            cout << "Kolom (1-" << size << "): ";
            cin >> col;

            row--;
            col--;

            if (row < 0 || row >= size ||
                col < 0 || col >= size) {

                cout << "Koordinat tidak valid!\n";
                continue;
            }

            if (choice == 1) {
                openCell(row, col);
            }
            else if (choice == 2) {
                toggleFlag(row, col);
            }
            else {
                cout << "Pilihan tidak valid!\n";
            }
        }

        cout << "\n================================\n";
        cout << "GAME OVER! KENA BOM!\n";
        cout << "Waktu: "
             << (int)(time(NULL) - startTime)
             << " detik\n";
        cout << "================================\n";

        displayBoard(true);
    }
};

int main() {

    srand(time(NULL));

    int menu;

    do {

        cout << "\n========== MINESWEEPER++ ==========\n";
        cout << "1. Mulai Permainan Baru\n";
        cout << "2. Keluar\n";
        cout << "Pilihan : ";
        cin >> menu;

        if (menu == 1) {

            Minesweeper game;
            game.play();

        } else if (menu == 2) {

            cout << "Terima kasih telah bermain!\n";

        } else {

            cout << "Pilihan tidak valid!\n";
        }

    } while (menu != 2);

    return 0;
}