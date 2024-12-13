#include <stdio.h>

// Fungsi untuk menampilkan angka pada 7-segment display dalam format ASCII
void displayNumber(int num) {
    // Pola untuk masing-masing angka (0 hingga 9)
    // Representasi 7-segment dengan urutan segmen: ABCDEFG
    const char digits[10][3][4] = {
        {" _ ", "| |", "|_|"}, // 0
        {"   ", "  |", "  |"}, // 1
        {" _ ", " _|", "|_ "}, // 2
        {" _ ", " _|", " _|"}, // 3
        {"   ", "|_|", "  |"}, // 4
        {" _ ", "|_ ", " _|"}, // 5
        {" _ ", "|_ ", "|_|"}, // 6
        {" _ ", "  |", "  |"}, // 7
        {" _ ", "|_|", "|_|"}, // 8
        {" _ ", "|_|", " _|"}  // 9
    };

    // Menampilkan angka dalam format ASCII 7-segment
    printf("Angka yang ditampilkan: %d\n", num);
    for (int i = 0; i < 3; i++) {
        printf("%s\n", digits[num][i]);
    }
    printf("\n");
}

int main() {
    int input;

    // Program utama
    while (1) {
        // Meminta input angka (0 hingga 9)
        printf("Masukkan angka (0 hingga 9): ");
        scanf("%d", &input);

        // Verifikasi input
        if (input >= 0 && input <= 9) {
            displayNumber(input); // Tampilkan angka
        } else {
            printf("Input tidak valid! Masukkan angka antara 0-9.\n");
        }
    }

    return 0;
}

