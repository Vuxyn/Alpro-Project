#include <iostream>
#include <conio.h>
#include <windows.h>
#define wait Sleep(1000); system("cls");
using namespace std;

const int tinggi = 5;
const int lebar = 30;
int max_score = 0;
int delay = 150;
bool ready = false; 

struct Karakter {
    int x;
    char player = 'M';
    int score = 0;
};
struct Obstacle {
    int x, y;
    char object = 'O';
};

const int max_obs = 5; //biar challenging
Obstacle obs[max_obs];
int obs_active = 1;
int fall = 0;

void set_up(string teks, int lebar, bool color = false){ 
    int padding = (lebar - 2 - teks.length()) / 2;
    int sisa = (lebar - 2 - teks.length()) % 2;
    for (int i = 0; i < 7; i++) {
        if (i == 0 || i == 7 - 1) {
            for (int j = 0; j < lebar; j++) cout << "#";
        } else if (i == 7 / 2) {
            cout << "#";
            for (int j = 0; j < padding; j++) cout << " ";
            (color == true) ? cout << "\033[1;32m" : cout << "\033[1;31m";
            cout << teks;
            cout << "\033[0m";
            for (int j = 0; j < padding + sisa; j++) cout << " ";
            cout << "#";
        } else {
            cout << "#";
            for (int j = 0; j < lebar - 2; j++) cout << " ";
            cout << "#";
        }
        cout << endl;
    }
}
void get_ready(){
    if(!ready){
        system("cls");
        set_up("READY?", lebar, false); wait;
        set_up("3..", lebar, false); wait;
        set_up("2..", lebar, false); wait;
        set_up("1..", lebar, false); wait;
        set_up("GO!", lebar, true); wait;
        ready = false;
    }
}
void tampil(Karakter player, Obstacle obs[], int obs_active, Karakter score) {
    system("cls");
    for (int i = 0; i < lebar + 2; i++) cout << "#";
    cout << endl;
    for (int i = 0; i < tinggi; i++) {
        cout << "#";
        for (int j = 0; j < lebar; j++) {
            if (i == tinggi - 1 && j == player.x)
                cout << player.player;
            else {
                bool printed = false;
                for (int k = 0; k < obs_active; k++) {
                    if (i == obs[k].y && j == obs[k].x) {
                        cout << obs[k].object;
                        printed = true;
                        break;
                    }
                }
                if (!printed) cout << " ";
            }
        }
        cout << "#" << endl;
    }
    for (int i = 0; i < lebar + 2; i++) cout << "#";
    cout << endl;
    cout << "Score: " << player.score << endl;
    if(player.score > 14 && player.score < 20) cout << "\033[1;31mGet Ready....\033[0m";
    if(player.score > 7 && player.score < 11) cout << "\033[1;31mYou doing well so far....\033[0m";
    if(player.score > 20 && player.score < 25) cout << "\033[1;31mDifficulty a little bit harder...\033[0m";
    if(player.score > 35 && player.score < 40) cout << "\033[1;31mWoah... turns out you're a bit skilled.\033[0m";
    if(player.score > 100 && player.score < 110) cout << "\033[1;31mGod level!\033[0m";
}
bool tabrakan(Karakter p, Obstacle o) {
    return (o.y == tinggi - 1 && o.x == p.x);
}
void start() {
    ready = false;
    get_ready();
    system("cls");
    Karakter player = { lebar / 2 };
    Karakter score;
    score.score = 0;
    for (int i = 0; i < max_obs; i++) {
        obs[i].x = (lebar / 4 + i * 7) % lebar; 
        obs[i].y = 0;
    }
    int game_delay = delay;
    while (true) {
        if (kbhit()) {
            char tombol = getch();
            if (tombol == 0 || tombol == -32) tombol = getch();
            if (tombol == 75 && player.x > 0) player.x--;
            else if (tombol == 77 && player.x < lebar - 1) player.x++;
        }
        for (int i = 0; i < obs_active; i++) {
            obs[i].y++;
            if (tabrakan(player, obs[i])) {
                system("cls");
                cout << "\n\tGame Over! Kamu tertabrak!\n";
                cout << "\tYour Score: " << player.score << "\n\n";
                if (player.score > max_score) max_score = player.score;
                obs_active = 1;
                system("pause");
                return;
            }
            if (obs[i].y >= tinggi) {
                fall++;
                obs[i].y = 0;
                obs[i].x = (obs[i].x + i + 7) % lebar;
                if(fall == obs_active){
                    player.score++;
                    fall = 0;
                }
            }
        }
        if (player.score > 0 && player.score % 20 == 0 && obs_active < max_obs) obs_active++;
        if (player.score % 10 == 0 && game_delay > 50) game_delay--;
        tampil(player, obs, obs_active, score);
        Sleep(game_delay);
    }
}
int main() {
    const int jumlah_pilihan = 2;
    string option[] = { "Start", "Exit" };
    int pilihan = 0;
    do {
        system("cls"); //Develop by mahesa
        cout << "==============================\n";
        cout << "          MAIN MENU           \n";
        cout << "==============================\n";
        for (int i = 0; i < jumlah_pilihan; i++) {
            cout << (i == pilihan ? "> \033[1;31m" : "  ") << option[i] << "\033[0m"<<endl;
        }
        cout << "==============================\n";
        cout << "Highest Score: " << max_score << endl;
        cout << "==============================\n";
        cout << "Press arrow (up/down) to move\n";
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
