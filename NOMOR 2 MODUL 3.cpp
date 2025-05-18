#include <iostream>
using namespace std;

int main() {
    char ulang;
    do {
        int menu;
        cout << "============ MENU PROGRAM ============\n";
        cout << "1. Enkripsi & Dekripsi\n";
        cout << "2. Teks ke Angka / Angka ke Teks\n";
        cout << "Pilih menu: ";
        cin >> menu;
        cin.ignore();

        if (menu == 1) {
            int mode, key;
            char pesan[10000];
            cout << "======= ENKRIPSI & DEKRIPSI =======\n";
            cout << "1. Enkripsi\n";
            cout << "2. Dekripsi\n";
            cout << "-> ";
            cin >> mode;
            cin.ignore();

            cout << "Masukkan Pesan: ";
            cin.getline(pesan, 10000);
            cout << "Masukkan Kunci: ";
            cin >> key;

            string hasil = "";
            for (int i = 0; pesan[i] != '\0'; i++) {
                char c = pesan[i];
                bool prima = true;
                if (i <= 1) prima = false;
                else {
                    for (int j = 2; j * j <= i; j++) {
                        if (i % j == 0) {
                            prima = false;
                            break;
                        }
                    }
                }

                if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                    char base = (c >= 'A' && c <= 'Z') ? 'A' : 'a';
                    if (!prima) {
                        if (mode == 1)
                            hasil += (char)(((c - base + key) % 26) + base);
                        else
                            hasil += (char)(((c - base - key + 26) % 26) + base);
                    } else {
                        if (mode == 1)
                            hasil += (char)(((c - base - i + 26) % 26) + base);
                        else
                            hasil += (char)(((c - base + i) % 26) + base);
                    }
                } else {
                    hasil += c;
                }
            }
            if (mode == 1)
                cout << "\nHasil Enkripsi: " << hasil << endl;
            else if (mode == 2)
                cout << "\nHasil Dekripsi: " << hasil << endl;
            else
                cout << "Mode tidak valid!\n";

        } else if (menu == 2) {
            int mode;
            cout << "===== ENKRIPSI KE ANGKA / DEKRIPSI KE TEKS =====\n";
            cout << "1. Enkripsi ke Angka" << endl;
			cout << "2. Dekripsi ke Kalimat" << endl;
			cout << "--> ";
            cin >> mode;
            cin.ignore();

            if (mode == 1) {
                char teks[10000];
                cout << R"(
            ____         __      ___  __ 
     /\    |  _ \        \ \    / _ \/_ |
    /  \   | |_) |  ______\ \  | | | || |
   / /\ \  |  _ <  |______|> > | | | || |
  / ____ \ | |_) |        / /  | |_| || |
 /_/    \_\|____/        /_/    \___/ |_|
                                         
                                         
)" << endl;
                cout << "Masukkan Teks: ";
                cin.getline(teks, 10000);
                int i = 0;
                while (teks[i] != '\0') {
                    char c = teks[i];
                    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                        int val = (c >= 'a') ? c - 'a' + 1 : c - 'A' + 1;
                        cout << val << " ";
                    } else if (c == ' ') {
                        cout << "| ";
                    }
                    i++;
                }
                cout << endl;
            } else if (mode == 2) {
                char input[10000];
                cout << R"(
				
   ___  __        __               ____  
  / _ \/_ |       \ \       /\    |  _ \ 
 | | | || |  ______\ \     /  \   | |_) |
 | | | || | |______|> >   / /\ \  |  _ < 
 | |_| || |        / /   / ____ \ | |_) |
  \___/ |_|       /_/   /_/    \_\|____/ 
                                         
                                         
)" << endl;
                cout << "Masukkan Angka (Pisahkan huruf dengan spasi, kata dengan '|'): ";
                cin.getline(input, 10000);

                int i = 0, val = 0;
                while (input[i] != '\0') {
                    char c = input[i];
                    if (c >= '0' && c <= '9') {
                        val = val * 10 + (c - '0');
                    } else if (c == ' ') {
                        if (val > 0) {
                            cout << (char)(val + 'A' - 1);
                            val = 0;
                        }
                    } else if (c == '|') {
                        if (val > 0) {
                            cout << (char)(val + 'A' - 1);
                            val = 0;
                        }
                        cout << ' ';
                    }
                    i++;
                }
                if (val > 0) cout << (char)(val + 'A' - 1);
                cout << endl;
            } else {
                cout << "Mode tidak valid!\n";
            }
        } else {
            cout << "Menu tidak tersedia!\n";
        }

        cout << "\nIngin menggunakan program lagi? (Y/N)? ";
        cin >> ulang;
        cin.ignore();
    } while (ulang == 'Y' || ulang == 'y');

    cout << "Terima kasih telah menggunakan program.\n";
    return 0;
}