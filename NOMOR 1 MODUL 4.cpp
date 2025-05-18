#include <iostream>
#include <conio.h>
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

const int max_akun = 100;
const int max_game = 100;
const int max_item = 100;
const int max_voucher = 100;
const int max_riwayat = 1000;
string username;
string password;
string data_username[max_akun];
string data_password[max_akun];
int saldo[max_akun] = {0};
int member[max_akun];
int akun = 1;
int user;
string nama_game[max_game];
int jumlah_game = 0;
string item[max_game][max_item];
int harga_item[max_game][max_item];
int jumlah_item[max_game] = {0};
string kode_voucher[max_voucher];
int diskon_voucher[max_voucher];
int jumlah_voucher = 0;
bool voucher_valid;
float harga_asli;
float harga_diskon;
float diskon;
string riwayat[max_riwayat];
int jumlah_riwayat = 0;
string transaction_log = "";
int top_up;
int jumlah_isi;
bool success;
bool isMember;

void banner() {
	cout << R"(
===============================================================================================================
|  /$$       /$$ /$$                           /$$            /$$$$$$   /$$                                   |
| | $$      |__/| $$                          |__/           /$$__  $$ | $$                                   |
| | $$       /$$| $$$$$$$   /$$$$$$   /$$$$$$  /$$  /$$$$$$ | $$  \__//$$$$$$    /$$$$$$   /$$$$$$   /$$$$$$  |
| | $$      | $$| $$__  $$ /$$__  $$ /$$__  $$| $$ /$$__  $$|  $$$$$$|_  $$_/   /$$__  $$ /$$__  $$ /$$__  $$ |
| | $$      | $$| $$  \ $$| $$$$$$$$| $$  \__/| $$| $$  \ $$ \____  $$ | $$    | $$  \ $$| $$  \__/| $$$$$$$$ |
| | $$      | $$| $$  | $$| $$_____/| $$      | $$| $$  | $$ /$$  \ $$ | $$ /$$| $$  | $$| $$      | $$_____/ |
| | $$$$$$$$| $$| $$$$$$$/|  $$$$$$$| $$      | $$|  $$$$$$/|  $$$$$$/ |  $$$$/|  $$$$$$/| $$      |  $$$$$$$ |
| |________/|__/|_______/  \_______/|__/      |__/ \______/  \______/   \___/   \______/ |__/       \_______/ |                                                                                                        
===============================================================================================================                                                                                                                                                                                                                
)";
}
void header_admin(){
		cout << R"(
~~~~~~~~~~~~~~~~~~~~~~~~~
|      Menu Admin       |
~~~~~~~~~~~~~~~~~~~~~~~~~
)";
}
void header_member(){
	cout << R"(
~~~~~~~~~~~~~~~~~~~~~~~~~
|      Menu Member      |
~~~~~~~~~~~~~~~~~~~~~~~~~
)";
}
void header_pilih_game(){
	cout << R"(
~~~~~~~~~~~~~~~~~~~~~~~~~
|      Pilih Game       |
~~~~~~~~~~~~~~~~~~~~~~~~~
)";
}
void header_history(){
	cout << R"(
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|    Riwayat Pemberilan    |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
)";
}
void menu_admin(){
	system("cls");
	int jawab, pilih;
	do{
	header_admin();
	cout << "1. Kelola Game" << endl;
	cout << "2. Buat Voucher" << endl;
	cout << "3. Lihat Riwayat" << endl;
	cout << "4. Keluar" << endl;
	cout << "Pilih: ";
	cin >> jawab;
	failed_loop;
	switch(jawab){
		case 1:
			system("cls");
			header_admin();
			cout << "1. Tambah Game" << endl;
			cout << "2. Hapus Game" << endl;
			cout << "3. Kelola Item Game" << endl;
			cout << "Pilih: "; 
			cin >> pilih;
			failed;
			if(pilih == 1){
				cout << "\nNama game: ";
				cin.ignore();
				getline(cin, nama_game[jumlah_game]);
				jumlah_game++;
				cout << "\nGame ditambahkan." << endl;
			}else if(pilih == 2){
				if(jumlah_game == 0){	
					cout << "Belum ada game yang ditambahkan" << endl;
				}else{
					for(int i = 0; i < jumlah_game; i++){
            			cout << i + 1 << ". " << nama_game[i] << endl;
        			}
					int hapus;
					cout << "Pilih: ";
					cin >> hapus;
					if(hapus < 1 || hapus > jumlah_game){
						cout << "Pilihan tidak valid." << endl;
					}else{
						for(int i = hapus - 1; i < jumlah_game - 1; i++){
        					nama_game[i] = nama_game[i + 1];
						}
						jumlah_game--;
					}
				cout << "Game berhasil dihapus." << endl;
				}
			}else if(pilih == 3){
				int pilih_game, kelola;
				if(jumlah_game == 0){
					cout << "Belum ada game yang ditambahkan" << endl;
				}else{
				for(int i = 0; i < jumlah_game; i++){
					cout << i + 1 << ". "<< nama_game[i] << endl;
				}
				cout << "Pilih game: ";
				cin >> pilih_game;
				pilih_game--;
				if(pilih_game < 0 || pilih_game >= jumlah_game){
					cout << "Game tidak valid" << endl;
				}
				cout << "\n1. Tambah Item" << endl;
				cout << "2. Lihat Item" << endl;
				cout << "Pilih: ";
				cin >> kelola;
				}if(kelola == 1){
					string nama_item;
					int harga;
					cout << "Nama item: ";
					cin.ignore();
					getline(cin, nama_item);
					cout << "Harga item: ";
					cin >> harga;
					int idx = jumlah_item[pilih_game];
					item[pilih_game][idx] = nama_item;
					harga_item[pilih_game][idx] = harga;
					jumlah_item[pilih_game]++;
					cout << "Item berhasil ditambahkan." << endl;
				}else if(kelola == 2){
					if(jumlah_item[pilih_game] == 0){
                    	cout << "Belum ada item pada " << nama_game[pilih_game] << endl;
                	}else {
                    	cout << "Item pada " << nama_game[pilih_game] << ": " << endl;
                    	for(int j = 0; j < jumlah_item[pilih_game]; j++){
                        	cout << j + 1 << ". " << item[pilih_game][j] << " - " << harga_item[pilih_game][j] << " rupiah" << endl;
                    	}
                	}
            	}
			}
			system("pause");
			system("cls");
			break;
		case 2:
			system("cls");
			header_admin();
			cout << "Kode voucher: ";
			cin.ignore();
    		getline(cin, kode_voucher[jumlah_voucher]);
    		cout << "Diskon (%): ";
    		cin >> diskon_voucher[jumlah_voucher];
    		jumlah_voucher++;
    		cout << "Voucher berhasil dibuat!\n";
    		system("pause");
    		system("cls");
			break;
		case 3:
			system("cls");
			header_history();
			if(jumlah_riwayat == 0){
				cout << "Belum ada transaksi." << endl;
			}else{
				for(int i = 0; i < jumlah_riwayat; i++){
					cout << i + 1 << ". " << riwayat[i] << endl;
				}
			}
			system("pause");
			system("cls");
			break;
		case 4:
			return;
	}
	}while(jawab != 4);
	menu_admin();
}
void menu_member(){
	system("cls");
	int jawab;
	do{
	header_member();
	cout << "1. Top Up Diamond" << endl;
	cout << "2. Isi Saldo" << endl;
	cout << "3. Keluar" << endl;
	cout << "Pilih: ";
	cin >> jawab;
	failed_loop;
	switch(jawab){
		case 1:
			int pilih_game;
			if(jumlah_game == 0){
				cout << "Belum ada game yang tersedia" << endl;
			}else{
				system("cls");
				header_pilih_game();
				for(int i = 0; i < jumlah_game; i++){
					cout << i + 1 << ". "<< nama_game[i] << endl;
				}
				cout << "\nPilih nomor game: ";
				cin >> pilih_game;
				failed;
				pilih_game--;
				if(pilih_game < 0 || pilih_game > jumlah_game){
					cout << "Game tidak Valid";
					break;
				}
				system("cls");
				cout << "_________________________________________________" << endl;
				cout << "=== Daftar Item di " << nama_game[pilih_game] << " ===" << endl;
				for(int j = 0; j < jumlah_item[pilih_game]; j++){
					cout << j + 1 << ". " << item[pilih_game][j] << " - " << harga_item[pilih_game][j] << " rupiah" << endl;
				}
				int pilih_item;
				cout << "\nPilih item (nomor): ";
				cin >> pilih_item;
				failed;
				pilih_item--;
				if(pilih_item < 0 || pilih_item >= jumlah_item[pilih_game]){
					cout << "Item tidak Valid";
					break;
				}
				harga_asli = harga_item[pilih_game][pilih_item];
        		harga_diskon = harga_asli;
        		string voucher_input;

				cout << "Masukkan kode voucher (jika ada): ";
				cin.ignore();
				getline(cin, voucher_input);
				voucher_valid = false;
				if(voucher_input != "tidak"){
					for(int i = 0; i < jumlah_voucher; i++){
						if(voucher_input == kode_voucher[i]){
							voucher_valid = true;
							diskon = diskon_voucher[i];
							harga_diskon = harga_asli - (harga_asli * diskon / 100);
						}
					}
					if(!voucher_valid){
						cout << "Voucher tidak valid/kadaluarsa" << endl;
						system("pause");
						system("cls");
						break;
					}
				}
				if(voucher_valid){
					cout << "Total setelah diskon member: " << harga_diskon << " rupiah" << endl;
				}else{
					cout << "Total pembayaran: " << harga_asli << " rupiah" << endl;
				}
				cout << "Bayar dengan (1. Saldo, 2. Tunai): ";
				int metode_bayar;
				bool bayar = false;
				cin >> metode_bayar;
				failed;
				if(metode_bayar != 1 && metode_bayar != 2){
					cout << "Metode bayar tidak valid";
					break;
				}else if(metode_bayar == 1){
					if(voucher_valid && saldo[user] >= harga_diskon){
						saldo[user] -= harga_diskon;
						cout << "Pembayaran berhasil dengan saldo!" << endl;
						cout << "Sisa saldo anda: " << saldo[user] << " rupiah" << endl;
						bayar = true;
					}else if(saldo[user] >= harga_asli){
						saldo[user] -= harga_asli;
						cout << "Pembayaran berhasil dengan saldo!" << endl;
						cout << "Sisa saldo anda: " << saldo[user] << " rupiah" << endl;
						bayar = true;
					}else if(saldo[user] < harga_asli || saldo[user] < harga_diskon){
						cout << "Saldo tidak cukup" << endl;
					}
				}else if(metode_bayar == 2){
					cout << "Pembayaran dengan tunai berhasil." << endl;
					bayar = true;
				}
				if(bayar){
					transaction_log = data_username[user] + ": " + item[pilih_game][pilih_item];
					riwayat[jumlah_riwayat++] = transaction_log;
				}
			}
			system("pause");
			system("cls");
			break;
		case 2:
			cout << "Jumlah isi saldo: ";
			cin >> jumlah_isi;
			failed;
			if(jumlah_isi > 0){
				saldo[user] += jumlah_isi;
				cout << "Jumlah saldo sekarang: " << saldo[user] << " rupiah" << endl;
			}else{
				cout << "Jumlah tidak valid"<< endl;
			}
			system("pause");
			system("cls");
			break;
		case 3:
			return;
	}
	}while(jawab != 3);
	menu_member();
}
void sign_up(){
	cout << R"(
~~~~~~~~~~~~~~~~~~~~~~~~~
|  Daftar Member Baru   |
~~~~~~~~~~~~~~~~~~~~~~~~~
)";
	string new_username, new_password;
	cout << "Username: ";
	cin >> new_username;
	cout << "Password: ";
	cin >> new_password;
	success = true;
	for(int i = 0; i < akun; i++){
		if(new_username == data_username[i]){
			cout << "Username tidak tersedia" << endl;
			success = false;
			break;
		}
	}
	if(success){
		data_username[akun] = new_username;
		data_password[akun] = new_password;
		member[akun] = 1;
		top_up = 0;
		akun++;
		cout << "Pendaftaran berhasil!" << endl;
	}
	system("pause");
}
void login_member(){
	cout << R"(
~~~~~~~~~~~~~~~~~~~~~~~~~
|      Login Member     |
~~~~~~~~~~~~~~~~~~~~~~~~~
)";
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;
	success = false;
	for(int i = 0; i < akun; i++){
		if(username == data_username[i]){
			if(password == data_password[i]){
				user = i;
				cout << "Login Berhasil!" << endl;
				success = true;
			}else{
				cout << "Login gagal." << endl;
			}
		}
	}
	if(!success) cout << "Login gagal." << endl;
	system("pause");
	system("cls");	
	if(success){
		menu_member();
	}
}
void login_admin(){
		cout << R"(
~~~~~~~~~~~~~~~~~~~~~~~~~
|      Login Admin      |
~~~~~~~~~~~~~~~~~~~~~~~~~
)";
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;
	success = false;
	data_username[0] = "Mahesa";
	data_password[0] = "10052";
	for(int i = 0; i < akun; i++){
		if(username == data_username[i]){
			if(password == data_password[i]){
				user = i;
				cout << "Login Berhasil!" << endl;
				success = true;
			}else{
				cout << "Login gagal." << endl;
			}
		}
	}
	system("pause");
	system("cls");	
	if(success){
		menu_admin();
	}
}
void sign_in(){
		cout << R"(
~~~~~~~~~~~~~~~~~~~~~~~~~
|    Sign In Sebagai    |
~~~~~~~~~~~~~~~~~~~~~~~~~
)";
	int sign; 
	cout << "1. Member\n";
	cout << "2. Admin\n";
	cout << "Pilih: ";
	cin >> sign;
	failed;
	switch(sign){
		case 1:
			system("cls");
			login_member();
			break;
		case 2:
			system("cls");
			login_admin();
			break;
		default:
			cout << "Tidak ada di pilihan";
			break;
	}
	return;
}
int main(){
	int pilihan = 0;
do{
	const int jumlah_pilihan = 3;
	int key;
	while(true){
		system("cls");
		banner();
		for(int i = 0; i < jumlah_pilihan;i++){
			if(i == pilihan) cout << "\033[35m";
			else cout << "\033[0m";
			cout << "~~~~~~~~~~~~~~~" << endl;
			if(i == 0) cout << "|   Sign In   |" << endl;
			else if(i ==1) cout << "|   Sign Up   |" << endl;
			else if(i == 2) cout << "|    Exit     |" << endl;
			cout << "~~~~~~~~~~~~~~~" << endl;
			cout << "\033[0m";
		}
		key = getch();
		if(key == 224){
			key = getch();
			if(key == 72){
				pilihan--;
				if(pilihan < 0) pilihan = jumlah_pilihan - 1;
			} else if(key == 80){
				pilihan++;
				if(pilihan >= jumlah_pilihan) pilihan = 0;
			}
		}else if(key == 13){
			break;
		}
	}
	system("cls");
	if(pilihan == 0){
		sign_in();
	}else if(pilihan == 1){
		sign_up();
		continue;
	}else{
		cout << "Terima Kasih";
	}
}while(pilihan != 2);
    return 0;
}
