// #AKSES INDEXNYA GAK NGOTAK TwT
#include <iostream>
#include <conio.h>
#define next system("pause"); system("cls");
#define failed_loop if (cin.fail()) { \
    cin.clear(); \
    cin.ignore(10000, '\n'); \
    cout << "Input tidak valid.\n"; \
    continue; \
}
#define failed if (cin.fail()) { \
    cin.clear(); \
    cin.ignore(10000, '\n'); \
    cout << "Input tidak valid.\n"; \
}
using namespace std;

struct Dosen {
    string kode;
    string nama;
    string password;
    string mata_kuliah[3];
    char kelas[3];
    int jumlah_matkul;
};
struct Mahasiswa {
    string nim;
    string nama;
    string password;
    string mata_kuliah[24];
    float ipk;
    char kelas[24];
    bool nilai_diisi[24];
    int jumlah_matkul;
    int total_sks;
    int sks_max;
    float nilai[24];
};
struct Matakuliah {
    string nama;
    int sks;
    int jumlah_dosen;
    string dosen[3];
    char kelas[3];
};
struct Sistem {
    Dosen* dosen;
    Mahasiswa* mahasiswa;
    Matakuliah* mata_kuliah;
    int jumlah_dosen;
    int jumlah_mahasiswa;
    int jumlah_matkul;
};
void banner(){
    cout<<R"(
|====================================|
|   ___ ___     _   _                |
|  / __|_ _|   /_\ | |_ __ _ _ ___   |
|  \__ \| |   / _ \| | '_ \ '_/ _ \  |
|   ___/___| /_/ \_\_| .__/_| \___/  |
|                    |_|             |
)";
}
void line(){
    cout << "|"; for(int i = 0;i < 36; i++) cout << "="; cout << "|" << endl;
}
int text_length(const string& str) {
    int len = 0;
    while (str[len] != '\0') len++;
    return len;
}
string cts(char c){
    char temp[2] = {c, '\0'};
    string result = temp;
    return result;
}
bool validasi_nim(string& nim) {
    if (text_length(nim) < 3) return false;
    string prefix = nim.substr(0, 3);
    return (prefix == "F1D" || prefix == "f1d" || prefix == "F1d" || prefix == "f1D");
}
void center_text(const string& text, string color = ""){
    int len = text_length(text);
    int padding = (36 - len )/ 2;
    int sisa = (36 - len )%2; 
    cout << "|";
    for(int i = 0; i < padding; i++) cout << " ";
    if(color != "") cout << color;
    cout << text; 
    if(color != "") cout << "\033[0m";
    for(int i = 0; i < padding + sisa; i++) cout << " ";
    cout << "|" << endl;
}
int navigate_menu(const char* options[], int jumlah_pilihan, string text) {
    int pilihan = 0;
    char key;
    do {
        system("cls");
        banner(); line();
        center_text(text);
        line();
        for (int i = 0; i < jumlah_pilihan; i++) {
            if (i == pilihan) {
                center_text(options[i], "\033[1;32m");
            } else {
                center_text(options[i]);
            }
        }
        line();
        key = getch();
        if (key == 72) pilihan = (pilihan - 1 + jumlah_pilihan) % jumlah_pilihan;
        else if (key == 80) pilihan = (pilihan + 1) % jumlah_pilihan;
        else if (key == 13) return pilihan;
    } while (true);
}
void pilih_matkul(Sistem* sistem) {
    do {
        system("cls");
        banner(); line(); center_text("Pilih Mata Kuliah"); line();
        cout << "Total mata kuliah yang sudah diambil: " << sistem->dosen[sistem->jumlah_dosen - 1].jumlah_matkul << endl;
        for (int i = 0; i < sistem->jumlah_matkul; i++) {
            cout << i + 1 << ". " << sistem->mata_kuliah[i].nama << " - SKS: " << sistem->mata_kuliah[i].sks 
                 << " - Jumlah Dosen: " << sistem->mata_kuliah[i].jumlah_dosen << "/3" << endl;
        }
        int pilihan;
        cout << "Pilih Mata Kuliah (0 jika sudah tidak ada): "; 
        cin >> pilihan; failed_loop;
        cin.ignore(10000, '\n');
        if (pilihan == 0) break;
        if (sistem->dosen[sistem->jumlah_dosen - 1].jumlah_matkul >= 3) {
            cout << "Mata kuliah yang diajarkan sudah mencapai batas 3 mata kuliah!" << endl;
            system("pause");
            break;
        }
        if (pilihan > 0 && pilihan <= sistem->jumlah_matkul) {
            if (sistem->mata_kuliah[pilihan - 1].jumlah_dosen >= 3) {
                cout << "Mata kuliah " << sistem->mata_kuliah[pilihan - 1].nama << " sudah memiliki 3 dosen!" << endl;
                system("pause");
            } else {
                int current_dosen_idx = sistem->jumlah_dosen - 1;
                int current_matkul_idx = pilihan - 1;
                int classes_assigned = 0;
                for (int i = 0; i < sistem->dosen[current_dosen_idx].jumlah_matkul; i++) {
                    if (sistem->dosen[current_dosen_idx].mata_kuliah[i] == sistem->mata_kuliah[current_matkul_idx].nama) {
                        classes_assigned++;
                    }
                }
                char assigned_class;
                if (classes_assigned > 0) {
                    if (classes_assigned == 1) {
                        assigned_class = 'B';
                    } else if (classes_assigned == 2) {
                        assigned_class = 'C';
                    } else {
                        cout << "Dosen sudah mengajar " << sistem->mata_kuliah[current_matkul_idx].nama 
                             << " di semua kelas (A, B, C)!" << endl;
                        system("pause"); continue;
                    }
                } else {
                    if (sistem->mata_kuliah[current_matkul_idx].jumlah_dosen == 0) {
                        assigned_class = 'A';
                    } else {
                        assigned_class = 'C';
                    }
                }
                int current_matkul = sistem->dosen[current_dosen_idx].jumlah_matkul;
                sistem->dosen[current_dosen_idx].mata_kuliah[current_matkul] = sistem->mata_kuliah[current_matkul_idx].nama;
                sistem->mata_kuliah[current_matkul_idx].dosen[sistem->mata_kuliah[current_matkul_idx].jumlah_dosen] = 
                    sistem->dosen[current_dosen_idx].kode;
                sistem->dosen[current_dosen_idx].kelas[current_matkul] = assigned_class;
                sistem->mata_kuliah[current_matkul_idx].kelas[sistem->mata_kuliah[current_matkul_idx].jumlah_dosen] = 
                    assigned_class;
                sistem->dosen[current_dosen_idx].jumlah_matkul++;
                sistem->mata_kuliah[current_matkul_idx].jumlah_dosen++;
                cout << "Dosen Mata Kuliah " << sistem->mata_kuliah[current_matkul_idx].nama 
                     << " berhasil ditambahkan!" << endl;
                system("pause");
            }
        } else {
            cout << "Pilihan Mata Kuliah Tidak Valid" << endl;
            system("pause");
        }
    } while (true);
}
void nilai_dosen(Sistem* sistem, int dosen_idx) {
    string teks = "KELAS DOSEN " + sistem->dosen[dosen_idx].nama;
    system("cls"); banner(); line(); center_text(teks); line();
    cout << "Mata kuliah yang diampu dosen: " << endl;
    for (int i = 0; i < sistem->dosen[dosen_idx].jumlah_matkul; i++) {
        cout << i + 1 << ". " << sistem->dosen[dosen_idx].mata_kuliah[i] 
             << " (" << sistem->dosen[dosen_idx].kelas[i] << ")" << endl;
    }
    int pilihan;
    cout << "Pilih Mata Kuliah: "; cin >> pilihan; failed;
    if (pilihan > 0 && pilihan <= sistem->dosen[dosen_idx].jumlah_matkul) {
        string pilih_matkul = sistem->dosen[dosen_idx].mata_kuliah[pilihan-1];
        char pilih_kelas = sistem->dosen[dosen_idx].kelas[pilihan-1];
        string kelas = "DAFTAR MAHASISWA " + cts(pilih_kelas);
        system("cls"); banner(); line(); center_text(kelas); line();
        bool ada_mahasiswa = false;
        for (int i = 0; i < sistem->jumlah_mahasiswa; i++) {
            for (int j = 0; j < sistem->mahasiswa[i].jumlah_matkul; j++) {
                if (sistem->mahasiswa[i].mata_kuliah[j] == pilih_matkul && 
                    sistem->mahasiswa[i].kelas[j] == pilih_kelas) {
                    ada_mahasiswa = true;
                    cout << "Mahasiswa: " << sistem->mahasiswa[i].nama << " -> Nilai: ";
                    if (sistem->mahasiswa[i].nilai_diisi[j]) {
                        cout << sistem->mahasiswa[i].nilai[j] << endl;
                    } else {
                        float nilai; cin >> nilai; failed;
                        if (nilai >= 0 && nilai <= 100) {
                            sistem->mahasiswa[i].nilai[j] = nilai;
                            sistem->mahasiswa[i].nilai_diisi[j] = true;
                        } else {
                            cout << "Nilai harus antara 0 dan 100!" << endl; system("pause");
                        }
                    }
                }
            }
        }
        if (!ada_mahasiswa) {
            cout << "Belum ada mahasiswa di kelas ini!" << endl;
            system("pause");
        }
    } else {
        cout << "Pilihan tidak valid!" << endl;
        system("pause");
    }
    system("pause");
}
void dasboard_dosen(Sistem* sistem, int dosen_idx) {
    if (dosen_idx == -1) return; 
    string teks = "DASBOARD " + sistem->dosen[dosen_idx].nama;
    const char* options[] = {"Tambah Mata Kuliah", "Nilai", "Log Out"};
    do {
        int pilihan = navigate_menu(options, 3, teks);
        if (pilihan == 0) {
            if (sistem->dosen[dosen_idx].jumlah_matkul >= 3) {
                cout << "Mata kuliah yang diajarkan sudah mencapai batas 3 mata kuliah!" << endl;
                system("pause");
            } else pilih_matkul(sistem); 
        } else if (pilihan == 1) nilai_dosen(sistem, dosen_idx); 
        else if (pilihan == 2) return;
    } while (1);
}
void sign_up_mahasiswa(Sistem* sistem) {
    system("cls"); banner(); line(); center_text("SIGN UP MAHASISWA"); line();
    string nim, nama, password;
    float ipk;
    bool nim_ada;
    do {
        cout << "Masukkan NIM: ";
        getline(cin, nim); failed;
        if (!validasi_nim(nim)) {
            cout << "Masukkan NIM yang valid!" << endl;
            system("pause"); cin.ignore(10000, '\n');
            system("cls"); banner(); line(); center_text("SIGN UP MAHASISWA"); line();
            continue;
        }
        nim_ada = false;
        for (int i = 0; i < sistem->jumlah_mahasiswa; i++) {
            if (sistem->mahasiswa[i].nim == nim) {
                nim_ada = true;
                cout << "NIM " << nim << " sudah terdaftar!" << endl; 
                system("pause"); cin.ignore(10000, '\n');
                system("cls");
                banner(); line(); center_text("SIGN UP MAHASISWA"); line();
                break;
            }
        }
    } while (nim_ada || !validasi_nim(nim));
    cout << "Masukkan Nama Mahasiswa: ";
    getline(cin, nama);
    if (text_length(nama) == 0) {
        cout << "Nama tidak boleh kosong!" << endl;
        system("pause"); cin.ignore(10000, '\n');
        return;
    }
    cout << "Masukkan Password: ";
    getline(cin, password);
    if (text_length(password) == 0) {
        cout << "Password tidak boleh kosong!" << endl;
        system("pause"); cin.ignore(10000, '\n');
        return;
    }
    do {
        cout << "Masukkan IPK terakhir: ";
        cin >> ipk; failed_loop;
        if (ipk < 0.0 || ipk > 4.0) {
            cout << "Rentang IPK dari 0.0 dan 4.0!" << endl;
            system("pause");
        } else break;
    } while (true);
    sistem->mahasiswa[sistem->jumlah_mahasiswa].nim = nim;
    sistem->mahasiswa[sistem->jumlah_mahasiswa].nama = nama;
    sistem->mahasiswa[sistem->jumlah_mahasiswa].password = password;
    sistem->mahasiswa[sistem->jumlah_mahasiswa].ipk = ipk;
    sistem->mahasiswa[sistem->jumlah_mahasiswa].jumlah_matkul = 0;
    sistem->mahasiswa[sistem->jumlah_mahasiswa].total_sks = 0;
    sistem->jumlah_mahasiswa++;
    cout << "Sign Up Mahasiswa Berhasil!" << endl;
    next;
    cin.ignore(10000, '\n');
}
int range_ipk(Sistem* sistem){
    if(sistem->mahasiswa[sistem->jumlah_mahasiswa-1].ipk < 2.0){
        sistem->mahasiswa[sistem->jumlah_mahasiswa-1].sks_max = 12;
    }else if(sistem->mahasiswa[sistem->jumlah_mahasiswa-1].ipk < 2.99){
        sistem->mahasiswa[sistem->jumlah_mahasiswa-1].sks_max = 16;
    }else if(sistem->mahasiswa[sistem->jumlah_mahasiswa-1].ipk < 3.49){
        sistem->mahasiswa[sistem->jumlah_mahasiswa-1].sks_max = 20;
    }else if(sistem->mahasiswa[sistem->jumlah_mahasiswa-1].ipk <= 4.0){
        sistem->mahasiswa[sistem->jumlah_mahasiswa-1].sks_max = 24;
    }
    int maks_sks = sistem->mahasiswa[sistem->jumlah_mahasiswa-1].sks_max;
    return maks_sks;
}
void krs(Sistem* sistem, int mahasiswa_idx) {
    do {
        system("cls"); banner(); line(); center_text("DAFTAR MATA KULIAH"); line();
        for (int i = 0; i < sistem->jumlah_matkul; i++) {
            cout << i + 1 << ". " << sistem->mata_kuliah[i].nama << " - SKS: " << sistem->mata_kuliah[i].sks << endl;
        }
        cout << endl;
        cout << "Jumlah SKS yang sudah diambil: " << sistem->mahasiswa[mahasiswa_idx].total_sks 
             << "/" << range_ipk(sistem) << endl;
        cout << "Pilih Mata Kuliah (0 jika sudah tidak ada): ";
        int pilihan;
        cin >> pilihan; failed_loop; cin.ignore(10000, '\n');
        if (pilihan == 0) {
            cout << "KRS berhasil disimpan!" << endl;
            system("pause");
            break;
        }
        if (sistem->mahasiswa[mahasiswa_idx].total_sks >= range_ipk(sistem)) {
            cout << "Jumlah SKS yang dapat diambil telah terpenuhi!" << endl;
            system("pause"); break;
        }
        if (pilihan > 0 && pilihan <= sistem->jumlah_matkul) {
            if (sistem->mata_kuliah[pilihan-1].jumlah_dosen == 0) {
                cout << "Belum ada dosen yang mengajar mata kuliah ini!" << endl;
                system("pause"); continue;
            }
            bool sudah_diambil = false;
            for (int i = 0; i < sistem->mahasiswa[mahasiswa_idx].jumlah_matkul; i++) {
                if (sistem->mahasiswa[mahasiswa_idx].mata_kuliah[i] == sistem->mata_kuliah[pilihan-1].nama) {
                    sudah_diambil = true; break;
                }
            }
            if (sudah_diambil) {
                cout << "Mata kuliah sudah diambil!" << endl;
                system("pause"); continue;
            }
            if (sistem->mahasiswa[mahasiswa_idx].total_sks + sistem->mata_kuliah[pilihan-1].sks > range_ipk(sistem)) {
                cout << "Penambahan mata kuliah ini akan melebihi batas SKS maksimum!" << endl;
                system("pause"); continue;
            }
            string selected_matkul = sistem->mata_kuliah[pilihan-1].nama;
            string header = "DAFTAR KELAS - " + selected_matkul;
            bool class_selected = false;
            do {
                system("cls"); banner(); line(); center_text(header); line();
                int student_count[3] = {0, 0, 0}; 
                for (int i = 0; i < sistem->jumlah_mahasiswa; i++) {
                    for (int j = 0; j < sistem->mahasiswa[i].jumlah_matkul; j++) {
                        if (sistem->mahasiswa[i].mata_kuliah[j] == selected_matkul) {
                            if (sistem->mahasiswa[i].kelas[j] == 'A') student_count[0]++;
                            else if (sistem->mahasiswa[i].kelas[j] == 'B') student_count[1]++;
                            else if (sistem->mahasiswa[i].kelas[j] == 'C') student_count[2]++;
                        }
                    }
                }
                for (int i = 0; i < sistem->mata_kuliah[pilihan-1].jumlah_dosen; i++) {
                    char kelas = sistem->mata_kuliah[pilihan-1].kelas[i];
                    string dosen_nama = "Tidak ada dosen";
                    string dosen_kode = sistem->mata_kuliah[pilihan-1].dosen[i];
                    for (int j = 0; j < sistem->jumlah_dosen; j++) {
                        if (sistem->dosen[j].kode == dosen_kode) {
                            dosen_nama = sistem->dosen[j].nama;
                            break;
                        }
                    }
                    int idx = (kelas == 'A') ? 0 : (kelas == 'B') ? 1 : 2;
                    cout << i + 1 << ". Kelas " << kelas << " - Dosen: " << dosen_nama 
                         << " - Jumlah Mahasiswa: " << student_count[idx] << "/10" << endl;
                }
                cout << "Pilih Kelas (1-" << sistem->mata_kuliah[pilihan-1].jumlah_dosen << "): ";
                int class_choice;
                cin >> class_choice; failed_loop; cin.ignore(10000, '\n');
                if (class_choice > 0 && class_choice <= sistem->mata_kuliah[pilihan-1].jumlah_dosen) {
                    char selected_class = sistem->mata_kuliah[pilihan-1].kelas[class_choice-1];
                    int idx = (selected_class == 'A') ? 0 : (selected_class == 'B') ? 1 : 2;
                    if (student_count[idx] >= 10) {
                        cout << "Kelas " << selected_class << " sudah penuh (maksimum 10 mahasiswa)!" << endl;
                        system("pause"); 
                        break;
                    }
                    int current_matkul = sistem->mahasiswa[mahasiswa_idx].jumlah_matkul;
                    sistem->mahasiswa[mahasiswa_idx].mata_kuliah[current_matkul] = selected_matkul;
                    sistem->mahasiswa[mahasiswa_idx].kelas[current_matkul] = selected_class;
                    sistem->mahasiswa[mahasiswa_idx].jumlah_matkul++;
                    sistem->mahasiswa[mahasiswa_idx].total_sks += sistem->mata_kuliah[pilihan-1].sks;
                    sistem->mahasiswa[mahasiswa_idx].nilai_diisi[current_matkul] = false;
                    cout << "Mata kuliah " << selected_matkul << " (Kelas " << selected_class << ") berhasil ditambahkan!" << endl;
                    system("pause");
                    class_selected = true;
                    break;
                } else {
                    cout << "Pilihan kelas tidak valid!" << endl;
                    system("pause");
                }
            } while (!class_selected);
        } else {
            cout << "Pilihan tidak valid!" << endl;
            system("pause");
        }
    } while (true);
}
string grade(float nilai) {
    if (nilai >= 85) return "A";
    else if (nilai >= 80 && nilai <= 84) return "B+";
    else if (nilai >= 75 && nilai <= 79) return "B";
    else if (nilai >= 70 && nilai <= 74) return "C+";
    else if (nilai >= 65 && nilai <= 69) return "C";
    else if (nilai >= 60 && nilai <= 64) return "D+";
    else if (nilai >= 55 && nilai <= 59) return "D";
    return "E";
}
float bobot_nilai(float nilai) {
    if (nilai >= 85) return 4.0;
    else if (nilai >= 80 && nilai <= 84) return 3.5;
    else if (nilai >= 75 && nilai <= 79) return 3.0;
    else if (nilai >= 70 && nilai <= 74) return 2.5;
    else if (nilai >= 65 && nilai <= 69) return 2.0;
    else if (nilai >= 60 && nilai <= 64) return 1.5;
    else if (nilai >= 55 && nilai <= 59) return 1.0;
    else return 0.5;
}
float current_ipk(Sistem* sistem, int mahasiswa_idx) {
    float total_sks_bobot = 0.0;
    int total_sks = 0;
    for (int i = 0; i < sistem->mahasiswa[mahasiswa_idx].jumlah_matkul; i++) {
        if (sistem->mahasiswa[mahasiswa_idx].nilai_diisi[i]) {
            int matkul_idx = -1;
            for (int j = 0; j < sistem->jumlah_matkul; j++) {
                if (sistem->mata_kuliah[j].nama == sistem->mahasiswa[mahasiswa_idx].mata_kuliah[i]) {
                    matkul_idx = j;
                    break;
                }
            }
            if (matkul_idx != -1) {
                int sks = sistem->mata_kuliah[matkul_idx].sks;
                float bobot = bobot_nilai(sistem->mahasiswa[mahasiswa_idx].nilai[i]);
                total_sks_bobot += sks * bobot;
                total_sks += sks;
            }
        }
    }
    if (total_sks == 0) return 0.0;
    return total_sks_bobot / total_sks;
}
void nilai_mahasiswa(Sistem* sistem, int mahasiswa_idx) {
    string teks = "NILAI " + sistem->mahasiswa[mahasiswa_idx].nama;
    system("cls"); banner(); line(); center_text(teks); line();
    cout << "NIM Mahasiswa: " << sistem->mahasiswa[mahasiswa_idx].nim << endl;
    cout << "Nama Mahasiswa: " << sistem->mahasiswa[mahasiswa_idx].nama << endl << endl;
    cout << "Total SKS: " << sistem->mahasiswa[mahasiswa_idx].total_sks << endl;
    cout << "Daftar Mata Kuliah yang diambil: " << endl;
    for(int i = 0; i< 80; i++) cout << "="; cout << endl;
    if (sistem->mahasiswa[mahasiswa_idx].jumlah_matkul == 0) {
        cout << "Belum ada mata kuliah yang diambil" << endl;
    } else {
        for (int i = 0; i < sistem->mahasiswa[mahasiswa_idx].jumlah_matkul; i++) {
            int matkul_idx = -1;
            for (int j = 0; j < sistem->jumlah_matkul; j++) {
                if (sistem->mata_kuliah[j].nama == sistem->mahasiswa[mahasiswa_idx].mata_kuliah[i]) {
                    matkul_idx = j;
                    break;
                }
            }
            cout << i + 1 << ". Mata Kuliah: " << sistem->mahasiswa[mahasiswa_idx].mata_kuliah[i];
            cout << " (" << sistem->mahasiswa[mahasiswa_idx].kelas[i] << ")";
            if (matkul_idx != -1) {
                cout << " - SKS: " << sistem->mata_kuliah[matkul_idx].sks;
            } else {
                cout << " - SKS: N/A";
            }
            if (sistem->mahasiswa[mahasiswa_idx].nilai_diisi[i]) {
                cout << " - Nilai: " << sistem->mahasiswa[mahasiswa_idx].nilai[i]; 
                cout <<" - Grade: " << grade(sistem->mahasiswa[mahasiswa_idx].nilai[i]);
            } else {
                cout << " - Nilai: 0";
                cout << " - Grade: N/A";
            }
            string dosen_nama = " - Tidak ada dosen";
            if (matkul_idx != -1) {
                for (int k = 0; k < sistem->mata_kuliah[matkul_idx].jumlah_dosen; k++) {
                    if (sistem->mata_kuliah[matkul_idx].kelas[k] == sistem->mahasiswa[mahasiswa_idx].kelas[i]) {
                        string dosen_kode = sistem->mata_kuliah[matkul_idx].dosen[k];
                        for (int m = 0; m < sistem->jumlah_dosen; m++) {
                            if (sistem->dosen[m].kode == dosen_kode) {
                                dosen_nama = sistem->dosen[m].nama;
                                break;
                            }
                        }
                        break;
                    }
                }
            }
            cout << " - Dosen: " << dosen_nama << endl;
            for(int i = 0; i< 80; i++) cout << "="; 
            cout << endl;
        }
    }
    cout << endl << "IPK Terakhir: " << sistem->mahasiswa[mahasiswa_idx].ipk << endl;
    cout << "IPK Saat ini: " << current_ipk(sistem, mahasiswa_idx) << endl;;
    for (int i = 0; i < 36; i++) cout << "="; cout << endl;
    system("pause");
}
void dasboard_mahasiswa(Sistem* sistem, int mahasiswa_idx) {
    if (mahasiswa_idx == -1) return; 
    string teks = sistem->mahasiswa[mahasiswa_idx].nama + "'s DASBOARD";
    const char* options[] = {"KRS", "Nilai", "Log Out"};
    do {
        int pilihan = navigate_menu(options, 3, teks);
        if (pilihan == 0) krs(sistem, mahasiswa_idx); 
        else if (pilihan == 1) nilai_mahasiswa(sistem, mahasiswa_idx);
        else if (pilihan == 2) return;
    } while (true);
}
int sign_in_mahasiswa(Sistem* sistem) {
    do {
        system("cls"); banner(); line(); center_text("SIGN IN MAHASISWA"); line();
        string nim, password;
        if (sistem->jumlah_mahasiswa == 0) {
            cout << "Belum ada mahasiswa yang terdaftar" << endl;
            system("pause");
            return -1;
        }
        cout << "Masukkan NIM: "; 
        getline(cin, nim);
        cout << "Masukkan Password: "; 
        getline(cin, password); failed;
        int mahasiswa_idx = -1;
        for (int i = 0; i < sistem->jumlah_mahasiswa; i++) {
            if (sistem->mahasiswa[i].nim == nim) {
                mahasiswa_idx = i;
                break;
            }
        }
        if (mahasiswa_idx == -1) {
            cout << "Tidak ada mahasiswa dengan NIM " << nim << endl;
            system("pause");
            continue;
        }
        if (sistem->mahasiswa[mahasiswa_idx].password != password) {
            cout << "Password salah" << endl; system("pause");
            continue;
        }
        cout << "Sign In Mahasiswa Berhasil!" << endl;
        system("pause");
        return mahasiswa_idx; 
    } while (true);
}
void sign_up_dosen(Sistem* sistem) {
    system("cls");
    banner(); line(); center_text("SIGN UP DOSEN"); line();
    string kode, nama, password;
    bool kode_ada;
    do {
        cout << "Masukkan Kode Dosen: ";
        getline(cin, kode);
        if (text_length(kode) == 0) {
            cout << "Kode tidak boleh kosong!" << endl;
            next;
            banner(); line(); center_text("SIGN UP DOSEN"); line();
            continue;
        }
        kode_ada = false;
        for (int i = 0; i < sistem->jumlah_dosen; i++) {
            if (sistem->dosen[i].kode == kode) {
                kode_ada = true;
                cout << "Kode dosen " << kode << " sudah terdaftar dengan nama " 
                     << sistem->dosen[i].nama << endl;
                system("pause"); cin.ignore(10000, '\n');
                system("cls");
                banner(); line(); center_text("SIGN UP DOSEN"); line();
                break;
            }
        }
    } while (kode_ada);
    
    cout << "Masukkan Nama Dosen: ";
    getline(cin, nama); failed;
    if (text_length(nama) == 0) {
        cout << "Nama tidak boleh kosong!" << endl;
        system("pause"); cin.ignore(10000, '\n');
        return;
    }
    
    cout << "Masukkan Password: ";
    getline(cin, password); failed;
    if (text_length(password) == 0) {
        cout << "Password tidak boleh kosong!" << endl;
        system("pause"); cin.ignore(10000, '\n');
        return;
    }
    sistem->dosen[sistem->jumlah_dosen].kode = kode;
    sistem->dosen[sistem->jumlah_dosen].nama = nama;
    sistem->dosen[sistem->jumlah_dosen].password = password;
    sistem->dosen[sistem->jumlah_dosen].jumlah_matkul = 0;
    sistem->jumlah_dosen++;
    cout << "Lanjut isi mata kuliah, tekan enter untuk melanjutkan" << endl;
    system("pause");
    pilih_matkul(sistem);
    cout << "Sign Up Dosen Berhasil!" << endl;
    next;
}
int sign_in_dosen(Sistem* sistem) {
    do {
        system("cls"); banner(); line(); center_text("SIGN IN DOSEN"); line();
        string kode, password; bool kcorrect = false; bool pcorrect = false;
        if (sistem->jumlah_dosen == 0) {
            cout << "Belum ada dosen yang terdaftar" << endl; system("pause"); return -1;
        }
        cout << "Masukkan kode dosen: "; 
        getline(cin, kode);
        cout << "Masukkan Password: "; getline(cin, password); failed;
        int dosen_idx = -1;
        for (int i = 0; i < sistem->jumlah_dosen; i++) {
            if (sistem->dosen[i].kode == kode) {
                dosen_idx = i;
                break;
            }
        }
        if (dosen_idx == -1) {
            cout << "Tidak ada dosen dengan kode dosen " << kode << endl;
            system("pause");
            continue;
        }
        if (sistem->dosen[dosen_idx].password != password) {
            cout << "Password salah" << endl;
            system("pause");
            continue;
        }
        cout << "Sign In Dosen Berhasil!" << endl; system("pause");
        return dosen_idx; 
    } while (1);
}
void sign_up(Sistem* sistem){
    const char* options[] = {"Sign Up Dosen", "Sign Up Mahasiswa", "Back"};
    int pilihan = navigate_menu(options, 3, "SIGN UP");
    if(pilihan == 0) sign_up_dosen(sistem);
    else if(pilihan == 1) sign_up_mahasiswa(sistem);
    else if(pilihan == 2) return;
}
void sign_in(Sistem* sistem) {
    const char* options[] = {"Sign In Dosen", "Sign In Mahasiswa", "Back"};
    int pilihan = navigate_menu(options, 3, "SIGN IN");
    if (pilihan == 0) {
        int dosen_idx = sign_in_dosen(sistem);
        if (dosen_idx != -1) dasboard_dosen(sistem, dosen_idx);
    } else if (pilihan == 1) {
        int mahasiswa_idx = sign_in_mahasiswa(sistem);
        if (mahasiswa_idx != -1) dasboard_mahasiswa(sistem, mahasiswa_idx);
    } else if (pilihan == 2) return;
}
int main() {
    Sistem* sistem = new Sistem;

    sistem->dosen = new Dosen[100];
    sistem->mahasiswa = new Mahasiswa[100];
    sistem->mata_kuliah = new Matakuliah[9];
    
    sistem->dosen[0].jumlah_matkul = 0;
    sistem->jumlah_dosen = 0;
    sistem->jumlah_mahasiswa = 0;
    sistem->jumlah_matkul = 9;

    sistem->mata_kuliah[0] = {"Sistem Basis Data", 3, 0};
    sistem->mata_kuliah[1] = {"Sistem Operasi", 3, 0};
    sistem->mata_kuliah[2] = {"Jaringan Komputer", 3, 0};
    sistem->mata_kuliah[3] = {"Algoritma dan Struktur Data", 3, 0};
    sistem->mata_kuliah[4] = {"Metode Numerik", 3, 0};
    sistem->mata_kuliah[5] = {"Sistem Informasi", 3, 0};
    sistem->mata_kuliah[6] = {"Interaksi Manusia dan Komputer", 3, 0};
    sistem->mata_kuliah[7] = {"Etika Profesi", 2, 0};
    sistem->mata_kuliah[8] = {"Riset Operasional", 2, 0};

    const int jumlah_pilihan = 3;
    const char* options[jumlah_pilihan] = {"Sign Up", "Sign In", "Exit"};

    while (1) {
        int pilihan = navigate_menu(options, jumlah_pilihan, "SISTEM INFORMASI ALPRO");
        if (pilihan == 0) {
            sign_up(sistem);
        } else if (pilihan == 1) {
            sign_in(sistem);
        } else if (pilihan == 2) {
            next;
            break;
        }
    }
    delete[] sistem->dosen;
    delete[] sistem->mahasiswa;
    delete[] sistem->mata_kuliah;
    delete sistem;

    return 0;
}
