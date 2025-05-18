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
#define loop_back continue; system("pause"); system("cls");
#define next system("pause"); system("cls");
using namespace std;
const int max_akun = 100;
const int max_item = 100;
const int lebar = 70;
const int kolom = 3;
int user = -1, akun = 0;
bool success;
int jumlah_biodata = 0;
struct tanggal{
    string hari;
    int tanggal;
    string bulan;
    int tahun;
}; 
tanggal current_date = {"Jumat", 16, "Mei", 2025};
struct item {
    string nama_item;
    int harga;
    string deskripsi;
};
item food_item[max_item];
item drink_item[max_item];
item current_order[max_item]; int order_count = 0;
int food_count = 0;
int drink_count = 0;
struct anggota {
    string username;
    string password;
    string nama;
    string email;
    string phone;
    string gender;
    int umur;
    tanggal admission_date;
    item items[100];
    int item_count = 0;
};
anggota data_biodata[max_akun];
item guest_history[100]; int guest_count = 0;
void line(char teks){
    cout << " ";
    for (int i = 0; i <= lebar - 1; i++) cout << teks;
    cout << endl;
}
string inToString(int num) {
    if (num == 0) return "0";
    string result = "";
    int temp = num;
    while (temp > 0) {
        char digit = '0' + (temp % 10);
        result = digit + result;
        temp /= 10;
    }
    return result;
}
void banner(){
    system("cls");
    cout << R"(
    _____       __  __       _  __                                        
   / ____|     / _|/ _|     | |/ /                                        
  | |     __ _| |_| |_ ___  | ' / ___ _ __    __ _ _ __   ___   __ _ _ __  
  | |    / _` |  _|  _/ _ \ |  < / _  \ '_ \ / _` | '_ \ / _` |/ _` | '_ \ 
  | |___| (_| | | | ||  __/ | . \  __/ | | | (_| | | | | (_| | (_| | | | |
   \_____\__,_|_| |_| \___| |_|\_\___|_| |_|\__,_|_| |_|\__, |\__,_|_| |_| 
                                                         __/ |            
                                                        |___/             
                       C A F F E   K E N A N G A N
)";
   cout << endl;
}
void mid(item menu[], int jumlah = 3, int kolom = 3, string color = "") {
    int lebar = 22;
    for (int i = 0; i < jumlah; i++) {
        if ((int)menu[i].nama_item.length() > lebar) {
            lebar = menu[i].nama_item.length();
        }
    }
    //lebar += 2;
    for (int i = 0; i < jumlah; i++) {
        int padding = (lebar - menu[i].nama_item.length()) / 2;
        int sisa = (lebar - menu[i].nama_item.length()) % 2;
        cout << "|";
        for (int j = 0; j < padding; j++) cout << " ";
        if (color != "") cout << color;
        cout << menu[i].nama_item;
        if (color != "") cout << "\033[0m";
        for (int j = 0; j < padding + sisa; j++) cout << " ";
        if ((i + 1) % kolom == 0 || i == jumlah - 1) {
            cout << "|  " << endl; 
        }
    }
}
void center(string teks, int lebar, string color = "", bool isOption = false) {
    int padding = (lebar - teks.length()) / 2;
    int sisa = (lebar - teks.length()) % 2;
    int optionLength = (lebar - 22) / 2; int optionPadding = lebar - 22 - optionLength;
    if (isOption) {
        const int wavyLength = 22;
        int wavyPadding = (lebar - wavyLength) / 2;
        int wavyRightPadding = lebar - wavyLength - wavyPadding;
        cout << "|";
        for (int i = 0; i < wavyPadding; i++) cout << " ";
        for (int i = 0; i < wavyLength; i++) cout << "~";
        for (int i = 0; i < wavyRightPadding; i++) cout << " ";
        cout << "|" << endl;
    }
    cout << "|";
    for (int i = 0; i < padding; i++) cout << " ";
    if (color != "") cout << color;
    cout << teks;
    if (color != "") cout << "\033[0m";
    for (int i = 0; i < padding + sisa; i++) cout << " ";
    cout << "|" << endl;
    if (isOption) {
        const int wavyLength = 22;
        int wavyPadding = (lebar - wavyLength) / 2;
        int wavyRightPadding = lebar - wavyLength - wavyPadding;
        cout << "|";
        for (int i = 0; i < wavyPadding; i++) cout << " ";
        for (int i = 0; i < wavyLength; i++) cout << "~";
        for (int i = 0; i < wavyRightPadding; i++) cout << " ";
        cout << "|" << endl;
    }
}
void notMid(string teks, int lebar){
    int spasi = (lebar - teks.length());
    cout << "|"; cout << teks;
    for(int i = 0; i < spasi; i++) cout << " "; 
    cout << "|" << endl;
}
void format(string teks, int lebar){
    int spasi = (lebar - teks.length());
    cout << teks;
    for(int i = 0; i < spasi; i++) cout << " "; 
    cout << endl;
}
void kucing() {
    string catFace[] = {
        "~~~~~~~~~~~~~~~~~~~~~~",
        "|       /\\_/\\        |",
        "|      ( o.o )       |",
        "    |            >\xE2\x9D\xA4\xEF\xB8\x8F<      |",
        "~~~~~~~~~~~~~~~~~~~~~~"
    };
    for (const string line : catFace) {
        center(line, 70);
    }
}
void center_item(item items[], int count, int selected, int offset = 0){
    int width = 22;
    for (int i = 0; i < count; i++) {
        if (i % kolom == 0) line('-');
        string str = items[i].nama_item;
        int padding = (width - str.length()) / 2;
        cout << "|";
        if(i + offset == selected) cout << "\033[1;31m";
        for (int j = 0; j < padding; j++) cout << " ";
        cout << str;
        for (int j = 0; j < width - padding - str.length(); j++) cout << " ";
        if(i + offset == selected) cout << "\033[0m";
        cout << "|";
        if ((i + 1) % kolom == 0) cout << endl;
        
    }
    if (count % kolom != 0) cout << endl;
    line('-');
}
void display_button(int selected, int start){
    string button[] = {"[ OK / BAYAR ]", "[ CANCEL ]"};
    for(int i = 0; i < 2; i++){
        line('~');
        if(selected == start + i) cout << "\033[1;32m";
        center(button[i], 70);
        if(selected == start + i) cout << "\033[0m";
    }
    line('~');
}
bool payment(int order_count){
    system("cls"); banner(); line('=');
    if(order_count == 0) {
        center("No Item Selected", 70);line('=');
        next; return false;
    } else if(order_count > 0) {
        if (user != -1) center("7% discount applied!", 70); line('=');
        center("TOTAL PAYMENT", 70); line('=');
        string title = (user == -1) ? "Guest" : data_biodata[user].username;
        cout << "Customer Name  : " << title << endl;
        int total_pay = 0; int diskon = 0;
        for(int i = 0; i < order_count; i++){
            total_pay += current_order[i].harga;
        }
        if(user == -1) {
            for(int i = 0; i < order_count; i++) guest_history[guest_count++] = current_order[i];
        } else {
            diskon = total_pay * 7 / 100;
            total_pay -= diskon;
            for(int i = 0; i < order_count; i++) data_biodata[user].items[data_biodata[user].item_count++] = current_order[i];
        }
        cout << "Total Price    : " << total_pay << endl;
        line('-'); center("Pesanan berhasil disimpan!", 70); line('-');
        //order_count = 0;
        next;
    }
    return true;
}
void order_history_admin(){
    banner(); line('='); center("Sales History", 70); line('='); int order_num = 1;
    int total_order = guest_count > 0 ? 1 : 0;
    for(int i = 1; i < akun; i++){
        if(data_biodata[i].item_count > 0) total_order++;
    }
    if(total_order == 0) {
        cout << "  No Sales History." << endl;
        next; return;
    } 
    if (guest_count > 0) {
        cout << "Order #" << order_num << " by: Guest" << endl;
        string food_items[100]; string drink_items[100];
        int food_count_items = 0; int drink_count_items = 0;
        for (int i = 0; i < guest_count; i++) {
            item current_item = guest_history[i];
            bool isFood = false;
            for (int j = 0; j < food_count; j++) {
                if (current_item.nama_item == food_item[j].nama_item) {
                    isFood = true;
                    break;
                }
            }
            if (isFood) food_items[food_count_items++] = current_item.nama_item;
            else drink_items[drink_count_items++] = current_item.nama_item;
        }
        cout << " Food:" << endl;
        if (food_count_items == 0) {
            cout << "   - None" << endl;
        } else {
            for (int i = 0; i < food_count_items; i++) {
                cout << "   - " << food_items[i] << endl;
            }
        }
        cout << " Drink:" << endl;
        if (drink_count_items == 0) {
            cout << "   - None" << endl;
        } else {
            for (int i = 0; i < drink_count_items; i++) {
                cout << "   - " << drink_items[i] << endl;
            }
        }
        line('=');
        order_num++;
    }
    for (int j = 1; j < akun; j++) {
        if (data_biodata[j].item_count == 0) continue;
        cout << "Order #" << order_num << " by: " << data_biodata[j].username << endl;
        string food_items[100]; string drink_items[100];
        int food_count_items = 0; int drink_count_items = 0;
        for (int i = 0; i < data_biodata[j].item_count; i++) {
            item current_item = data_biodata[j].items[i];
            bool isFood = false;
            for (int k = 0; k < food_count; k++) {
                if (current_item.nama_item == food_item[k].nama_item) {
                    isFood = true;
                    break;
                }
            }
            if (isFood) food_items[food_count_items++] = current_item.nama_item;
            else drink_items[drink_count_items++] = current_item.nama_item;
        }
        cout << " Food:" << endl;
        if (food_count_items == 0) {
            cout << "   - None" << endl;
        } else {
            for (int i = 0; i < food_count_items; i++) {
                cout << "   - " << food_items[i] << endl;
            }
        }
        cout << " Drink:" << endl;
        if (drink_count_items == 0) {
            cout << "   - None" << endl;
        } else {
            for (int i = 0; i < drink_count_items; i++) {
                cout << "   - " << drink_items[i] << endl;
            }
        }
        line('=');
        order_num++;
    }
    next;
}
void order_history(){
    system("cls");
    line('='); center("Order History:", 70); line('=');
    if(data_biodata[user].item_count == 0){
        cout << "No order history yet." << endl;
        next; return;
    }else if(data_biodata[user].item_count > 0){
        int food_num = 1; int drink_num = 1;
        for(int i = 0; i < data_biodata[user].item_count; i++){
            item current_item = data_biodata[user].items[i];
            bool isFood = false;
            for(int j = 0; j < food_count; j++){
                if(current_item.nama_item == food_item[j].nama_item){
                    isFood = true; 
                    break;
                }
            }
            if(isFood) {
                cout << "Food Order " << food_num << " : " << current_item.nama_item
            << ", Price : " << current_item.harga << endl; food_num++;
            } else {
                cout << "Drink Order " << drink_num << " : " << current_item.nama_item
            << ", Price : " << current_item.harga << endl; drink_num++;
            }
        } 
    }
    next;
}
void order_summary(item item){
    system("cls"); banner(); line('=');
    center("YOU SELECTED", 70); line('=');
    center("", 70);
    center(item.nama_item, 70);
    string str = " - IDR " + inToString(item.harga);
    center(str, 70);
    center(item.deskripsi, 70);
    center("", 70); line('=');
    system("pause");
}
int select_item(item food_item[], int food_count, item drink_item[], int drink_count, int order_count){
    int selected = 0;
    int total_item = food_count + drink_count + 2;
    int start = food_count + drink_count;
    int max_row = (total_item + kolom - 1) / kolom;
    while(1){
        system("cls");
        banner();
        line('=');
        kucing(); line('=');
        center("==== OUR MENU ====", 70); line('=');
        string title = (user == -1) ? "Guest" : data_biodata[user].username;
        center(title, 70); line('=');
        cout << "FOODS:" << endl;
        if(food_count == 0){
            center("No food item available.", 70);
        } else{
            center_item(food_item, food_count, selected, 0);
        }
        cout << "\nDRINKS: " << endl;
        if(drink_count == 0){
            center("No drink item available.", 70);
        } else {
            center_item(drink_item, drink_count, selected, food_count);
        }
        line('=');
        center("Your Order(s):", 70);
        line('-');
        if (order_count == 0) {
            format(" - No order yet.", 70);
        } else {
            for (int i = 0; i < order_count; i++) {
                string type = "[Drink] ";
                for (int j = 0; j < food_count; j++) {
                    if (current_order[i].nama_item == food_item[j].nama_item) {
                        type = "[Food] ";
                        break;
                    }
                }
                cout << type << current_order[i].nama_item << " - IDR " << current_order[i].harga << endl;
            }
        }
        display_button(selected, start);
        int key = getch();
        if (key == 0 || key == 224) {
            int key = getch();
            switch (key) {
                case 72: if (selected >= kolom) selected -= kolom; break;
                case 80: if (selected + kolom < total_item) selected += kolom;
                    else if (selected < total_item - 1) selected = total_item - 1; 
                break;
                case 75: if (selected > 0) selected--; break;
                case 77: if (selected < total_item - 1) selected++; break;
            }
        } else if (key == 13) {
            if (selected < food_count) {
                current_order[order_count] = food_item[selected]; order_count++;
                order_summary(current_order[order_count - 1]);
            } else if (selected < food_count + drink_count) {
                current_order[order_count] = drink_item[selected - food_count]; order_count++;
                order_summary(current_order[order_count - 1]);
            } else if (selected == start) {
                if(payment(order_count)) return -1;
                else return order_count;
            } else {
                return -2; 
            }
        } else if (key == 27) {
            return -2;
        }
    }
}
void order() {
    int result = 0;
    while(true) {
        result = select_item(food_item, food_count, drink_item, drink_count, result >= 0 ? result : 0);
        if (result == -1 || result == -2) {
            result = 0;
            break;
        }
    }
    line('=');
}
void menu_profile(){
    banner(); line('='); center("------ Profile ------", 70); line('=');
    cout << "Username       : " << data_biodata[user].username << endl;
    cout << "Name           : " << data_biodata[user].nama << endl;
    cout << "Phone          : " << data_biodata[user].phone << endl;
    cout << "Email          : " << data_biodata[user].email << endl;
    cout << "Gender         : " << data_biodata[user].gender << endl;
    cout << "Age            : " << data_biodata[user].umur << endl;
    cout << "Account Created: " << data_biodata[user].admission_date.hari + ", " + inToString(data_biodata[user].admission_date.tanggal) 
    + " " + data_biodata[user].admission_date.bulan + " " + inToString(data_biodata[user].admission_date.tahun) << endl;
    line('=');
    cout << R"(1. Update Data
2. Back
)"; 
    cout << "Choose an option: ";
    int opsi; cin >> opsi;
    failed;
    if(opsi == 1){
        cout << "What do you want to change?" << endl;
        cout << R"(1. Username
2. Name
3. Password
4. Phone number
5. Email
)";   
    cout << "Enter your choice: "; int choice; cin >> choice;
    failed;
    string label, change;
    switch(choice){
        case 1: label = "username"; break;
        case 2: label = "name"; break;
        case 3: label = "password"; break;
        case 4: label = "phone number"; break;
        case 5: label = "email"; break;
    } cout << "Enter new " << label << ": "; cin.ignore(); getline(cin, change); failed;
    switch(choice){
        case 1: data_biodata[user].username = change; break;
        case 2: data_biodata[user].nama = change; break;
        case 3: data_biodata[user].password = change; break;
        case 4: data_biodata[user].phone = change; break;
        case 5: data_biodata[user].email = change; break;
    }
    cout << "Data updated successfully!" << endl;
    cout << "New " << label << ": " << change << endl;
    next;
    menu_profile(); return;
    }else if(opsi == 2){
    }    
    system("pause");
}
int show_menu(string options[], int jumlah_pilihan, string title, tanggal date){
    int pilihan = 0;
    while(1){
        system("cls");
        banner(); line('=');
        center(title, lebar);line('=');
        string date_str = date.hari + ", " + inToString(date.tanggal) + " " + date.bulan + " " + inToString(date.tahun);
        notMid(date_str, lebar); line('=');
        cout << "|"; for (int i = 0; i < lebar; i++) cout << " "; cout << "|" << endl;
        kucing();
        for(int i = 0; i < jumlah_pilihan; i++){
            string color = (i == pilihan) ? "\033[35m" : "";
            center(options[i], lebar, color, true);
        }
        line('=');
        int key = getch();
        if (key == 224) {
            key = getch();
            if (key == 72) {
                pilihan--;
                if (pilihan < 0) pilihan = jumlah_pilihan - 1;
            } else if (key == 80) {
                pilihan++;
                if (pilihan >= jumlah_pilihan) pilihan = 0;
            }
        } else if (key == 13) {
            break;
        }
    }
    return pilihan;
}
void main_menu() {
    const int jumlah_pilihan = 4;
    string options[] = {"Order", "Profile", "History", "Log-out"};
    int pilihan;
    do {
        string title = "Hai " + data_biodata[user].nama;
        pilihan = show_menu(options, jumlah_pilihan, title, current_date);
        system("cls");
        if(pilihan == 0) {
            order();
        } else if(pilihan == 1) {
            menu_profile();
        } else if(pilihan == 2) {
            order_history();
        } else if(pilihan == 3) {
            user = -1; break;
        }
    } while(pilihan != 3);
    system("cls");
}
void member_list() {
    banner();
    line('=');
    center("Member List", 70);
    line('=');
    
    if (jumlah_biodata == 0) {
        center("No members registered", 70);
        line('=');
    } else {
        for (int i = 1; i < akun; i++) { 
            cout <<"Member #" << i << endl; 
            format("    Username     : " + data_biodata[i].username, lebar);
            format("    Name         : " + data_biodata[i].nama, lebar);
            format("    Phone number : " + data_biodata[i].phone, lebar);
            format("    Email        : " + data_biodata[i].email, lebar);
            format("    Gender       : " + data_biodata[i].gender, lebar);
            format("    Age          : " + inToString(data_biodata[i].umur), lebar);
            string reg_date = data_biodata[i].admission_date.hari + ", " + 
                           inToString(data_biodata[i].admission_date.tanggal) + " " + 
                           data_biodata[i].admission_date.bulan + " " + 
                           inToString(data_biodata[i].admission_date.tahun);
            format("    Registered On: " + reg_date, lebar);
            line('=');
        }
    }
    char jawab; 
    do{
        cout << "Do you want to delete a member? (y/n): "; cin >> jawab; failed_loop;
        if(jumlah_biodata == 0){
            cout << "No members to delete" << endl;
            next; break;
        }
        if (jawab == 'y') {
            int hapus;
            cout << "Enter the member number to delete (1 - " << jumlah_biodata << "): "; cin >> hapus; failed_loop;
            if(hapus < 1 || hapus > jumlah_biodata){
                cout << "Invalid member number.." << endl;
                next; return;
            }else{
                for(int i = hapus; i < akun - 1; i++){
                    data_biodata[i] = data_biodata[i + 1];
				}
				jumlah_biodata--; akun--;
            }
        cout << "Member deleted successfully!" << endl;
        next;
        member_list();
        }else if(jawab == 'n'){
            break;
        }else{
            cout << "Invalid input. Please enter y or n." << endl;
            cin.clear(); cin.ignore(10000, '\n');
            next; continue;
        }
    }while(1);
}
tanggal manage_date(tanggal current) {
    tanggal t;
    cout << "Enter the new day of the week (e.g., Monday, Tuesday, etc.): "; cin >> t.hari; failed;
    cout << "Enter the new date (1-31): "; cin >> t.tanggal;failed;
    cout << "Enter the new month (e.g., January, February, etc.): "; cin >> t.bulan; failed;
    cout << "Enter the new year (e.g., 2025): "; cin >> t.tahun; failed;
    cout << "Date has been updated to: "
         << t.hari << ", " << t.tanggal << " " << t.bulan << " " << t.tahun << endl;
    next;
    return t;
}
void change_date(){
    current_date = manage_date(current_date);
}
void add_item(bool isFood){
    string label; item new_item;
    label = (isFood ? "food" : "drink");
    cout << "Enter " << label << " name: "; cin.ignore(); getline(cin, new_item.nama_item);
    cout << "Enter Description: "; getline(cin, new_item.deskripsi);
    cout << "Enter Price: "; cin >> new_item.harga; failed;
    if(new_item.harga <= 0){
        cout << "Invalid Price!" << endl;
        next; add_item(isFood); return;
    }
    if(isFood){
        food_item[food_count++] = new_item;
        cout << "Food item added successfully!" << endl;
    } else{
        drink_item[drink_count++] = new_item;
        cout << "Drink item added successfully!" << endl;
    }
    next;
}
void edit_item(bool isFood){
    string label = (isFood ? "food" : "drink");
    int count = isFood ? food_count : drink_count;
    if (count == 0) {
        cout << "No " << label << " items to edit!" << endl;
        next;
        return;
    }
    cout << "Enter the number of the " << label << " item to edit (1 - " << count << ") or 0 to cancel: ";
    int choice; cin >> choice; failed;
    if (choice == 0) {
        cout << "Edit cancelled." << endl;
        next;
        return;
    }
    if (choice < 1 || choice > count) {
        cout << "Invalid choice!" << endl;
        next;
        return;
    }
    item edited_item;
    if (isFood) edited_item = food_item[choice - 1];
    else edited_item = drink_item[choice - 1];
    cin.ignore(); 
    char buffer[100];
    cout << "Enter new name (or . to keep current): ";
    cin.getline(buffer, 100);
    if (!(buffer[0] == '.' && buffer[1] == '\0')) {
        edited_item.nama_item = buffer;
    }
    cout << "Enter new description (or . to keep current): ";
    cin.getline(buffer, 100);
    if (!(buffer[0] == '.' && buffer[1] == '\0')) {
        edited_item.deskripsi = buffer;
    }
    cout << "Enter new price (0 to keep current): ";
    int new_price; cin >> new_price; failed;
    if (new_price > 0) edited_item.harga = new_price;
    if (isFood) food_item[choice - 1] = edited_item;
    else drink_item[choice - 1] = edited_item;
    cout << label << " item updated successfully!" << endl;
    next;
}
void delete_item(bool isFood){
    string label = (isFood ? "food" : "drink");
    int count = isFood ? food_count : drink_count;
    if (count == 0) {
        cout << "No " << label << " item to delete!" << endl;
        next;
        return;
    }
    cout << "Select the item number to delete (1 - " << count << ") or 0 to cancel: ";
    int choice; cin >> choice; failed;
    if (choice == 0) {
        cout << "Delete cancelled." << endl;
        next;
        return;
    }
    if (choice < 1 || choice > count) {
        cout << "Invalid choice!" << endl;
        next;
        return;
    }
    int idx = choice - 1;
    if (isFood) {
        for (int i = idx; i < food_count - 1; i++) {
            food_item[i] = food_item[i + 1];
        }
        food_count--;
    } else {
        for (int i = idx; i < drink_count - 1; i++) {
            drink_item[i] = drink_item[i + 1];
        }
        drink_count--;
    }
    cout << label << " item deleted successfully!" << endl;
    next;
}
void menu_management(){
    banner(); line('=');
    center("------ Menu  Management ------", 70);
    line('=');
    cout << "Menu Food Items:" << endl;
    if(food_count == 0) center("No food items available", 70);
    else {
        for(int i = 0; i < food_count; i++){
            cout << i + 1 << ". " << food_item[i].nama_item << " - Rp" << food_item[i].harga 
            << " |  " << food_item[i].deskripsi << endl;
        }
    }
    cout << "\nMenu Drink Items:" << endl;
    if(drink_count == 0) center("No drink items available", 70);
    else {
        for(int i = 0; i < drink_count; i++){
            cout << i + 1 << ". " << drink_item[i].nama_item << " - Rp" << drink_item[i].harga 
            <<  " |  " << drink_item[i].deskripsi << endl;
        }
    }
    line('=');
    center("------ Edit Menu ------", 70);
    line('=');
    cout << R"(1. Add Food
2. Add Drink
3. Edit Food
4. Edit Drink
5. Delete Food
6. Delete Drink
0. Back
)";
    cout << "Enter your choice: "; int choice; cin >> choice; failed;
    switch(choice){
        case 1: add_item(true); break;
        case 2: add_item(false); break;
        case 3: edit_item(true); break;
        case 4: edit_item(false); break;
        case 5: delete_item(true); break;
        case 6: delete_item(false); break;
        default: return;
    }
    system("cls"); menu_management();
}
void menu_admin(){
    const int jumlah_pilihan = 5;
    string options[] = {"Sales History", "Member List", "Set Menu", "Change Date", "Log-out"};
    int pilihan;
    do{
        pilihan = show_menu(options, jumlah_pilihan, "Admin Mode", current_date);
        system("cls");
        if(pilihan == 0) {
            order_history_admin();
        } else if(pilihan == 1) {
            member_list();
        } else if(pilihan == 2) {
            menu_management();
        } else if(pilihan == 3) {
            change_date();
        } else if(pilihan == 4) {
            user = -1; break; 
        } 
    }while(pilihan != 4); cout << "Redirecting..." << endl;
}
void login() {
    system("cls"); banner(); line('=');
    center("Login here", 70); line('=');
    string input_username, input_password;
    cout << "Username: "; cin >> input_username;
    cout << "Password: "; cin >> input_password;
    data_biodata[0].username = "Mahesa";
    data_biodata[0].password = "mahesa052";
    success = false;
    bool isAdmin = false;
    for (int i = 0; i < akun; i++) {
        if (input_username == data_biodata[i].username) {
            if (input_password == data_biodata[i].password) {
                user = i;
                success = true;
                if (i == 0){
                    if(input_username == "Mahesa"){
                        if(input_password == "mahesa052"){
                            isAdmin = true;
                        }
                    }
                }
                break;
            } else {
                cout << "Password salah!" << endl; next; return; 
            }
        }
    }
    if (!success) {  
        cout << "Username tidak ditemukan!" << endl;
    } else {
        cout << "Login berhasil!" << endl;
        next;
        if (isAdmin) {
            menu_admin();
        } else {
            main_menu();
        }
    }
    next;
}
void sign_up(){
    system("cls"); banner();
    line('='); center("Register Here", 70); line('=');
    if(akun >= max_akun){
        cout << "Akun penuh!" << endl;
        system("pause"); return;
    }
    int new_akun = akun;
    cout << "Username  : "; cin >> data_biodata[new_akun].username;
    for(int i = 0; i < akun; i++){
        if(data_biodata[i].username == data_biodata[new_akun].username){
            if(data_biodata[i].username == data_biodata[0].username){
                cout << "Username sudah digunakan!"; return;
            }
        }
    }
    cout << "Password  : "; cin >> data_biodata[new_akun].password; failed;
    cout << "Name      : "; cin.ignore(); getline(cin, data_biodata[new_akun].nama);
    cout << "Phone     : "; cin >> data_biodata[new_akun].phone; failed;
    cout << "Email     : "; cin >> data_biodata[new_akun].email; failed;
    cout << "Gender    : "; cin >> data_biodata[new_akun].gender; failed;
    cout << "Age       : "; cin >> data_biodata[new_akun].umur; failed;
    while (data_biodata[new_akun].umur <= 0) {
        cout << "Umur tidak valid! Masukkan umur yang valid: ";
        cin >> data_biodata[new_akun].umur;
    } failed;
    data_biodata[new_akun].admission_date = current_date;
    akun++;
    jumlah_biodata++;
    cout << "Pendaftaran berhasil!" << endl;
    next;
    return;
}
int main(){
    data_biodata[1].username = "Emilia";
    data_biodata[1].password = "lia";
    data_biodata[1].nama = "Emilia-tan Maji Tenshi";
    data_biodata[1].email = "emilia.lia@example.com";
    data_biodata[1].phone = "081234567891";
    data_biodata[1].gender = "Female";
    data_biodata[1].umur = 103;
    data_biodata[1].admission_date = {"Senin", 1, "Januari", 2025};
    data_biodata[1].item_count = 0;

    data_biodata[2].username = "Satella";
    data_biodata[2].password = "tela";
    data_biodata[2].nama = "Satella Maji-Tenshi";
    data_biodata[2].email = "satella.envy@example.com";
    data_biodata[2].phone = "081234567892";
    data_biodata[2].gender = "Female";
    data_biodata[2].umur = 400;
    data_biodata[2].admission_date = {"Selasa", 2, "Januari", 2025};
    data_biodata[2].item_count = 0;

    food_item[0] = {"Truffle Pasta", 55000, "Creamy pasta with truffle oil and mushrooms"};
    food_item[1] = {"Teriyaki Bowl", 48000, "Grilled chicken with sweet soy glaze over rice"};
    food_item[2] = {"Avocado Toast", 42000, "Toasted bread with mashed avocado, eggs, and chili flakes"};
    food_item[3] = {"Mushroom Soup", 35000, "Warm creamy mushroom soup with garlic bread"};
    food_item[4] = {"Beef Lasagna", 58000, "Oven-baked lasagna with layers of beef and cheese"};
    drink_item[0] = {"Caramel Macchiato", 40000, "Espresso with steamed milk and caramel drizzle"};
    drink_item[1] = {"Iced Americano", 32000, "Cold espresso with water over ice"};
    drink_item[2] = {"Matcha Latte", 38000, "Japanese matcha blended with milk"};
    drink_item[3] = {"Vanilla Cold Brew", 39000, "Cold brewed coffee with vanilla syrup"};
    drink_item[4] = {"Hot Chocolate", 35000, "Creamy hot chocolate topped with marshmallows"};
    food_count = 5; drink_count = 5;
    akun = 3; jumlah_biodata = 2;
    const int jumlah_pilihan = 4;
    string options[] = {"Order", "Sign-Up", "Log-In", "Keluar"};
    int pilihan;
    do {
        pilihan = show_menu(options, jumlah_pilihan, "Hai", current_date);
        system("cls");
        if(pilihan == 0) {
            if(user == -1) order();
            else main_menu();
        } else if(pilihan == 1) {
            sign_up();
        } else if(pilihan == 2) {
            login();
        } else if(pilihan == 3) {
            break;
        }
    } while(pilihan != 3);
    banner(); line('='); kucing(); line('=');center("Goodbye...", 70); line('=');
    next;
    return 0;
}