#include <iostream>
#include <cstdlib>
#define failed if (cin.fail()) { \
    cin.clear(); \
    cin.ignore(10000, '\n'); \
}
using namespace std;
const int TYPE_CHAR = 1; const int TYPE_UINT = 2;
const int TYPE_CSTRING = 3; const int TYPE_PASCAL = 4;
void header() {
    cout << "             Hipster" << endl;
    cout << "    Heap Memory Visualization" << endl;
    for (int i = 0; i < 34; i++) cout << "-";
    cout << endl;
}
struct Record {
    unsigned int type;
    void* address;
    size_t size;
};
struct Heap {
    char* memory;
    int capacity;
    int used;
    int offset; //THISSSSSSS GOT ME COOKED!
    Record* records;
    int record_count;
    int record_capacity;
};
void inisiasi_heap(Heap& heap) {
    heap.capacity = 32;
    heap.used = 0;
    heap.memory = (char*)malloc(heap.capacity);
    if (!heap.memory) { 
        cout << "\033[33mERROR\033[0m: Failed to allocate heap memory\n";
        return;
    }
    heap.record_capacity = 10;
    heap.records = (Record*)malloc(heap.record_capacity * sizeof(Record));
    if (!heap.records) {
        cout << "\033[33mERROR\033[0m: Failed to allocate record memory\n";
        free(heap.memory);
        return;
    }
    heap.record_count = 0;
    heap.offset = 0;
}
int text_length(const char* str) {
    int len = 0;
    while (str[len] != '\0') len++;
    return len;
}
bool expand_records(Heap& heap) {
    int new_record_capacity = heap.record_capacity * 2; 
    Record* new_records = (Record*)realloc(heap.records, new_record_capacity * sizeof(Record));
    if (!new_records) {
        cout << "\033[33mERROR\033[0m: Failed to expand record array\n";
        return false;
    }
    heap.records = new_records;
    heap.record_capacity = new_record_capacity;
    return true;
}
void configure_heap(Heap& heap) {
    int input;
    while (true) {
        system("cls");
        header();
        cout << "Used Heap: " << heap.used << endl;
        cout << "Heap Capacity: " << heap.capacity << endl;
        cout << "Input 0 to Go Back." << endl;
        cout << "Expand Heap to Capacity: ";
        cin >> input; failed;
        if (input == 0) return;
        if (input < heap.capacity) {
            cout << "\033[33mERROR\033[0m: New capacity must be greater than or equal to current capacity\n";
            system("pause");
            continue;
        }
        char* new_heap = (char*)realloc(heap.memory, input);
        if (!new_heap) {
            cout << "\033[33mERROR\033[0m: Failed to expand heap\n";
            system("pause"); continue;
        }
        heap.memory = new_heap;
        heap.capacity = input;
        cout << "Heap expanded successfully.\n";
        system("pause");
        return;
    }
}
void view_heap(Heap& heap) {
    system("cls"); header();
    cout << "Heap: " << heap.used << "/" << heap.capacity << "\n";
    cout << "Heap Content:\n";
    for (int i = 0; i < heap.record_count; i++) {
        cout << heap.records[i].address << " : ";
        switch (heap.records[i].type) {
            case TYPE_CHAR:
                cout << *(char*)heap.records[i].address;
                break;
            case TYPE_UINT:
                cout << *(unsigned int*)heap.records[i].address;
                break;
            case TYPE_CSTRING: {
                char* str = (char*)heap.records[i].address;
                size_t len = 0;
                while (str[len] != '\0') {
                    if (str[len] < 32 || str[len] > 126) { 
                        cout << "\\" << (int)str[len];
                    } else {
                        cout << str[len];
                    }
                    len++;
                }
                cout << "\\0";
                break;
            }
            case TYPE_PASCAL: {
                unsigned char length = *(unsigned char*)heap.records[i].address;
                cout << (int)length; 
                char* str = (char*)heap.records[i].address + 1;
                for (int j = 0; j < length; j++) {
                    if (str[j] < 32 || str[j] > 126) { 
                        cout << "\\" << (int)str[j];
                    } else {
                        cout << str[j];
                    }
                }
                break;
            }
        }
        cout << "\n";
    }
    int back; cout << "Enter 0 to go back: "; cin >> back;
    if (cin.fail() || back != 0) {
        cin.clear(); cin.ignore(10000, '\n');
        cout << "\033[33mERROR\033[0m: Invalid input, please enter 0\n";
    } system("pause");
}
void insert_char(Heap& heap) {
    char input; cout << "Insert Char: "; cin >> input;
    if (cin.fail()) {
        cin.clear(); cin.ignore(10000, '\n');
        cout << "\033[33mERROR\033[0m: unexpected input value\n";
        system("pause");
        return;
    }
    cin.ignore(10000, '\n');

    int data_size = sizeof(char);
    if (heap.used + data_size > heap.capacity) { 
        cout << "\033[33mERROR\033[0m: record exceeded memory capacity, it would not be included in memory\n";
        system("pause");
        return;
    }

    if (heap.record_count >= heap.record_capacity && !expand_records(heap)) {
        system("pause");
        return;
    }
    *((unsigned int*)(heap.memory + heap.offset)) = TYPE_CHAR;
    *((unsigned int*)(heap.memory + heap.offset + 4)) = data_size;
    *(heap.memory + heap.offset + 8) = input; //this store the real data (with metadat)
    heap.records[heap.record_count].type = TYPE_CHAR;
    heap.records[heap.record_count].address = heap.memory + heap.offset + 8;
    heap.records[heap.record_count].size = data_size;
    heap.offset += 8 + data_size;
    heap.used += data_size;
    heap.record_count++;
    system("pause");
}
void insert_uint(Heap& heap) {
    unsigned int input; cout << "Insert Unsigned Int: "; cin >> input;
    if (cin.fail()) {
        cin.clear(); cin.ignore(10000, '\n');
        cout << "\033[33mERROR\033[0m: unexpected input value\n";
        system("pause"); return;
    }
    cin.ignore(10000, '\n');
    int data_size = sizeof(unsigned int);
    if (heap.used + data_size > heap.capacity) {
        cout << "\033[33mERROR\033[0m: record exceeded memory capacity, it would not be included in memory\n";
        system("pause"); return;
    }
    if (heap.record_count >= heap.record_capacity) {
        if (!expand_records(heap)) {
            system("pause"); return;
        }
    }
    *((unsigned int*)(heap.memory + heap.offset)) = TYPE_UINT;
    *((unsigned int*)(heap.memory + heap.offset + 4)) = data_size;
    *((unsigned int*)(heap.memory + heap.offset + 8)) = input;
    heap.records[heap.record_count].type = TYPE_UINT;
    heap.records[heap.record_count].address = heap.memory + heap.offset + 8;
    heap.records[heap.record_count].size = data_size;
    heap.offset += 8 + data_size;
    heap.used += data_size;
    heap.record_count++;
    system("pause");
}
void insert_cstring(Heap& heap) {
    char input[256]; cout << "Insert C String: ";
    cin.getline(input, 256);
    int len = text_length(input) + 1;
    int data_size = len;
    if (heap.used + data_size > heap.capacity) {
        cout << "\033[33mERROR\033[0m: record exceeded memory capacity, it would not be included in memory\n";
        system("pause");
        return;
    }
    if (heap.record_count >= heap.record_capacity) {
        if (!expand_records(heap)) {
            system("pause");
            return;
        }
    }
    *((unsigned int*)(heap.memory + heap.offset)) = TYPE_CSTRING;
    *((unsigned int*)(heap.memory + heap.offset + 4)) = data_size;
    for (int i = 0; i < len; i++) {
        heap.memory[heap.offset + 8 + i] = input[i];
    }
    heap.records[heap.record_count].type = TYPE_CSTRING;
    heap.records[heap.record_count].address = heap.memory + heap.offset + 8;
    heap.records[heap.record_count].size = data_size;
    heap.offset += 8 + data_size;
    heap.used += data_size;
    heap.record_count++;
    system("pause");
}
void insert_pascal(Heap& heap) {
    char input[256]; cout << "Insert Pascal String: ";
    cin.getline(input, 256);
    int len = text_length(input);
    if (len > 255) {
        cout << "\033[33mERROR\033[0m: Pascal string length cannot exceed 255\n";
        system("pause");
        return;
    }
    int data_size = len + 1;
    if (heap.used + data_size > heap.capacity) { 
        cout << "\033[33mERROR\033[0m: record exceeded memory capacity, it would not be included in memory\n";
        system("pause");
        return;
    }
    if (heap.record_count >= heap.record_capacity) {
        if (!expand_records(heap)) {
            system("pause");
            return;
        }
    }
    *((unsigned int*)(heap.memory + heap.offset)) = TYPE_PASCAL;
    *((unsigned int*)(heap.memory + heap.offset + 4)) = data_size;
    heap.memory[heap.offset + 8] = (unsigned char)len;
    for (int i = 0; i < len; i++) {
        heap.memory[heap.offset + 9 + i] = input[i];
    }
    heap.records[heap.record_count].type = TYPE_PASCAL;
    heap.records[heap.record_count].address = heap.memory + heap.offset + 8;
    heap.records[heap.record_count].size = data_size;
    heap.offset += 8 + data_size;
    heap.used += data_size;
    heap.record_count++;
    system("pause");
}
void insert_record(Heap& heap) {
    while (true) {
        system("cls"); header();
        cout << R"(1) Insert Char
2) Insert Unsigned Int
3) Insert C String
4) Insert Pascal String
5) Go Back
)";
        cout << ">> ";
        int input; cin >> input; cin.ignore(10000, '\n');
        switch (input) {
            case 1: insert_char(heap); break;
            case 2: insert_uint(heap); break;
            case 3: insert_cstring(heap); break;
            case 4: insert_pascal(heap); break;
            case 5: return;
            default:
                cout << "\033[33mERROR\033[0m: Invalid option\n";
                continue; system("pause");
        }
    }
}
void main_menu(Heap& heap) {
    while (true) {
        system("cls"); header();
        cout << R"(1) Configure Heap
2) View Heap
3) Insert Record
4) Exit
)";
        cout << ">> "; int pilihan;
        cin >> pilihan;cin.ignore(10000, '\n');
        switch (pilihan) {
            case 1: configure_heap(heap); break;
            case 2: view_heap(heap); break;
            case 3: insert_record(heap); break;
            case 4:
                free(heap.memory);
                free(heap.records); return;
            default:
                cout << "\033[33mERROR\033[0m: Invalid option\n";
                system("pause");
        }
    }
}
int main() {
    Heap heap;
    inisiasi_heap(heap);
    main_menu(heap);
    return 0;
}
