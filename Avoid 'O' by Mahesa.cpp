#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

const int tinggi = 5;
const int lebar = 30;
int max_score = 0;

struct Karakter {
    int x;
    char player = 'M';
    int score = 0;
};
struct Obstacle {
    int x, y;
    char simbol = 'O';
};
void tampil(Karakter player, Obstacle obs, Karakter score) {
    system("cls");
    for (int i = 0; i < lebar + 2; i++) cout << "#";
    cout << endl;
    for (int i = 0; i < tinggi; i++) {
        cout << "#"; 
        for (int j = 0; j < lebar; j++) {
            if (i == obs.y && j == obs.x)
                cout << obs.simbol;
            else if (i == tinggi - 1 && j == player.x)
                cout << player.player;
            else
                cout << " ";
        }
        cout << "#" << endl; 
    }
    for (int i = 0; i < lebar + 2; i++) cout << "#";
    cout << endl; cout << "Score: " << player.score;
}
bool tabrakan(Karakter p, Obstacle o) {
    return (o.y == tinggi - 1 && o.x == p.x);
}
void start() {
    Karakter player = { lebar / 2 };
    Obstacle obs = { 0, 0 };
    Karakter score; score.score;
    obs.x = lebar / 4;
    while (true) {
        if (_kbhit()) {
            char tombol = getch();
            if (tombol == 0 || tombol == -32) tombol = getch();
            if (tombol == 75 && player.x > 0) player.x--; 
            else if (tombol == 77 && player.x < lebar - 1) player.x++;
        }
        obs.y++;
        if (tabrakan(player, obs)) {
            system("cls");
            cout << "\n\tGame Over! Kamu tertabrak!\n";
            cout << "\tYour Score: " << player.score << "\n\n";
            (player.score > max_score) ? max_score = player.score : player.score;
            system("pause");
            break;
        }
        if (obs.y >= tinggi) {
            if(!tabrakan(player, obs)){
                obs.y = 0;
                player.score++;
                obs.x = (obs.x + 7) % lebar; 
            }
        }
        tampil(player, obs, score);
        Sleep(150);
    }
}

int main() {
    const int jumlah_pilihan = 2;
    string option[] = {"Start", "Exit"};
    int pilihan;
    do {
        system("cls");
        cout << "==============================\n";
        cout << "          MAIN MENU           \n";
        cout << "==============================\n";
        for (int i = 0; i < jumlah_pilihan; i++) {
            cout << (i == pilihan ? "> \033[1;31m" : "  ") << option[i] << "\033[0m"<<endl;
        }
        cout  << "\033[0m";
        cout << "==============================\n";
        cout << "Highest Score: " << max_score << endl;
        cout << "==============================\n";
        cout << "Press arrow (up/down) " << endl;
        char key = getch();
        if (key == 72) pilihan = (pilihan - 1 + jumlah_pilihan) % jumlah_pilihan; 
        else if (key == 80) pilihan = (pilihan + 1) % jumlah_pilihan; 
        else if (key == 13) {
            if (pilihan == 0) start();
            else break;
        }
    } while (true);
    return 0;
}
