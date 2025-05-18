#include <iostream>
using namespace std;

int main() {
    cout << "======================================" << endl;
    cout << "||SELAMAT DATANG DI DIMENSI KENANGAN||" << endl;
    cout << "======================================" << endl;
    cout << "1. Charcharcharchar\n";
    cout << "2. Primprimprim\n";
    cout << "3. Bubulatlat\n";
    cout << "4. GanGanGan\n";
    cout << "5. GenGenGen\n";
    cout << "6. Kompopo\n";
    cout << "7. TrueFalseTrue\n";
    cout << "8. Ritritrit\n";
    cout << "Matriks tiks tiks: Masukkan pilihanmu, wahai jiwa yang rindu nan malang!!!" << endl;

    int input[8];
    int matrix[8][5][5];

    for (int i = 0; i < 8; i++) {
        cout << "Pilihan ke- " << i + 1 << " ku : ";
        cin >> input[i];
    }
    char current = 'A'; //char
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[0][i][j] = current;
            current++;
        }
    }
    int num = 2; //prima
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            while (true) {
                bool isPrime = true;
                for (int k = 2; k * k <= num; k++) {
                    if (num % k == 0) {
                        isPrime = false;
                        break;
                    }
                }
                if (isPrime) {
                    matrix[1][i][j] = num++;
                    break;
                }
                num++;
            }
        }
    }
    int biasa = 1; //bulat
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[2][i][j] = biasa++;
        }
    }
    int gan = 1; //ganjil
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[3][i][j] = gan;
            gan += 2;
        }
    }
    int gen = 2; //genap
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[4][i][j] = gen;
            gen += 2;
        }
    }
    int kom = 4; //komposit
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            while (true) {
                bool isPrime = true;
                for (int k = 2; k * k <= kom; k++) {
                    if (kom % k == 0) {
                        isPrime = false;
                        break;
                    }
                }
                if (!isPrime) {
                    matrix[5][i][j] = kom++;
                    break;
                }
                kom++;
            }
        }
    }
    bool curr = true; //truefalse
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[6][i][j] = curr;
            curr = !curr;
        }
    }
    int jump = 3;//pola bilangan
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[7][i][j] = jump;
            jump += 3;
        }
    }
    int rata[8];
    for (int x = 0; x < 8; x++) {
        int idx = input[x] - 1; //adjust - 1 karna dari indeks 0
        int sum = 0;
        cout << "Pilihan " << input[x] << " hasil matriks: " << endl;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (idx == 0) {
                    cout << (char)matrix[idx][i][j] << " ";
                    sum += matrix[idx][i][j];
                } else if (idx == 6) {
                    cout << (matrix[idx][i][j] ? "truee " : "false ");
                    sum += matrix[idx][i][j];
                } else {
                    if (matrix[idx][i][j] < 10) cout << "0";
                    cout << matrix[idx][i][j] << " ";
                    sum += matrix[idx][i][j];
                }
            }
            cout << endl;
        }
    rata[x] = sum / 25;
    cout << endl;
    }
    int dimensi[2][2];
    dimensi[0][0] = rata[0] + rata[2];
    dimensi[0][1] = rata[1] + rata[3];
    dimensi[1][0] = rata[2] + rata[4];
    dimensi[1][1] = rata[3] + rata[5];
    
    system("pause");
    system("cls");
	
	cout << "Mari meratakan semua :( seperti mukamu : " << endl;
	for(int i = 0; i < 8; i++){
		cout << rata[i] << " ";
	}
	cout << endl;
	int core[2][2];
	cout << "Changing 1 Dimension Into 2 Dimension : " << endl;
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++){
			cout << dimensi[i][j] << " ";
			core[i][j] = dimensi[i][j];
		}
		cout << endl;
	}
	system("pause");
	system("cls");
	cout << "Matriks tiks tiks tiks : " << "\"Hei Ningen, aku terlalu kecil!!!!\n	Perbesarlah aku!!!!\"" << endl;
	int expand; int startNum;
	cout << "Masukan jumlah penambahan luas: ";
	cin >> expand;
	cout << "Masukan angka yang dimulai: ";
	cin >> startNum;
	
	int coreSize = 2;
	int newSize = coreSize + 2 * expand;
	int shinArray[100][100];
	//int totalZone = 4;
    /*int pattern[4] = {
        (startNum + 0) % 4,  // Atas  (00)
        (startNum + 1) % 4,  // Kanan (01)
        (startNum + 2) % 4,  // Bawah (02)
        (startNum + 3) % 4   // Kiri  (03)
    };*/
    int borderMap[3][3] = {
        { 3,  0,  1 },   // baris atas
        { 3, -1,  1 },   // baris tengah (tengah = core)
        { 2,  2,  1 }    // baris bawah
    };

	for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            //kategori baris r
            int r;
            if (i < expand)                    r = 0;
            else if (i < expand + coreSize)    r = 1;
            else                                r = 2;
            // kategori kolom c
            int c;
            if (j < expand)                    c = 0;
            else if (j < expand + coreSize)    c = 1;
            else                                c = 2;
            
            int off = borderMap[r][c];
            if (off == -1) {
                // area core
                shinArray[i][j] = core[i - expand][j - expand];
            } else {
                // zona dinamis
                shinArray[i][j] = (startNum + off);
            }
        }
    }
	for(int i = 0; i < coreSize; i++){
		for(int j = 0; j < coreSize; j++){
			shinArray[i + expand][j + expand] = core[i][j];
		}
	}
	cout << "\nMatriks ShinArray diperbesar:" << endl;
	for(int i = 0; i < newSize; i++){
		for(int j = 0; j < newSize; j++){
			if(shinArray[i][j] < 10){
				cout << "0";
			}
			cout << shinArray[i][j] << " ";
		}
		cout << endl;
	}
	int rotasi[100][100];
	char jawab[4];
	for(int rot = 0; rot < 4; rot++){
		cout << "Matriks tiks tiks tiks : " << "\"Ningenyoo... kamu bisa rotate aku (ya/no)\"" << endl;
		cin >> jawab[i];
		
		cout << endl;
		cout << "\nMatriks ShinArray diperbesar:" << endl;
		for (int i = 0; i < newSize; i++) {
        	for (int j = 0; j < newSize; j++) {
            	if (shinArray[i][j] < 10) cout << '0';
            		cout << shinArray[i][j] << ' ';
        		}
        	cout << endl;
    	}
		if(jawab[i] == 'y' || jawab[i] == 'Y'){
			for(int i = 0; i < newSize; i++){
				for(int j = 0; i < newSize; j++){
					rotasi[j][size - 1 - i] = shinArray[i][j];
				}
			}
		}
	}
	
    return 0;
}
