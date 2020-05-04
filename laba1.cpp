#include <iostream>
#include <string>

using namespace std;

struct Information {
    string name;
    string author;
    string carrier_type;
    int type_saver;
    union {
        unsigned capacity : 16;
        double int_capacity = 0;
    } prod;
    enum action { Add = 1, Print, Sort, Find, Find_all, Change, Delete, Exit };
};

int menu();
Information get_item_data();
Information* add_item(Information*& old_array, int& size);
void print_item(const Information temp);
void print_all(const Information* arr, const int size);
void sort(Information*& arr, const int size);
Information& find_item(Information*& arr, const int size);
void find_all(const Information* arr, const int size);
void change_item(Information*&, const int size);
void delete_item(Information*&, int& size);

int main() {
    int array_size = 0;
    Information* container = new Information[array_size];
    int command = menu();
    while (command != Information::action::Exit) {
        switch (command)
        {
        case Information::action::Add: {
            container = add_item(container, array_size);
            command = menu();
            break;
        }
        case Information::action::Print: {
            print_all(container, array_size);
            command = menu();
            break;
        }
        case Information::action::Sort: {
            sort(container, array_size);
            command = menu();
            break;
        }
        case Information::action::Find: {
            Information temp = find_item(container, array_size);
            print_item(temp);
            command = menu();
            break;
        }
        case Information::action::Find_all: {
            find_all(container, array_size);
            command = menu();
            break;
        }
        case Information::action::Change: {
            change_item(container, array_size);
            command = menu();
            break;
        }
        case Information::action::Delete: {
            delete_item(container, array_size);
            command = menu();
            break;
        }
        default:
            break;
        }
    }

    delete[] container;
    return 0;
}

int menu() {
    system("pause");
    system("cls");
    int command;
    cout
        << "1. Add item\n"
        << "2. Print all\n"
        << "3. Sort array\n"
        << "4. Find item\n"
        << "5. Find all items\n"
        << "6. Change item\n"
        << "7. Delete item\n"
        << "8. Exit\n";
    cin >> command;
    if (command < 1 || command > 8)
        command = menu();
    system("cls");
    return command;
}

Information get_item_data() {
    Information temp;
    cout << "Enter carrier type: ";
    cin.ignore();
    getline(cin, temp.carrier_type);
    cout << "Enter author: ";
    getline(cin, temp.author);
    cout << "Enter item name: ";
    getline(cin, temp.name);
    cout << "Enter capcity (1. int 2. unsigned): ";
    cin >> temp.type_saver;
    switch (temp.type_saver)
    {
    case 1: {
        cin >> temp.prod.int_capacity;
        break;
    }
    case 2: {
        unsigned cap;
        cin >> cap;
        temp.prod.capacity = cap;
        break;
    }
    default:
        break;
    }
    return temp;
}

Information* add_item(Information*& old_array, int& size) {
    Information* arr = new Information[++size];
    for (int i = 0; i < size - 1; i++) {
        arr[i] = old_array[i];
    }
    arr[size - 1] = get_item_data();
    delete[] old_array;
    return arr;
}

void print_item(const Information temp) {
    cout
        << "Carrier type: " << temp.carrier_type
        << "\nAuthor: " << temp.author
        << "\nTitle: " << temp.name;
    if (temp.type_saver == 1)
        cout << "\nInt capacity: " << temp.prod.int_capacity;
    else
        cout << "\nUnsigned capacity: " << temp.prod.capacity;
    cout << endl;
}

void print_all(const Information* arr, const int size) {
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". ";
        print_item(arr[i]);
        cout << endl;
    }
}

void sort(Information*& arr, const int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (arr[j].name > arr[j + 1].name) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void find_all(const Information* arr, const int size) {
    int dec = -1;
    cout << "Find by:"
        << "\n1. Title"
        << "\n2. Carrier type"
        << "\n3. Author" << endl;
    cin >> dec;
    string text;
    cout << "Enter searching text: ";
    cin.ignore();
    getline(cin, text);
    for (int i = 0; i < size; i++) {
        switch (dec)
        {
        case 1: {
            if (arr[i].name == text)
                print_item(arr[i]);
            break;
        }
        case 2: {
            if (arr[i].carrier_type == text)
                print_item(arr[i]);
            break;
        }
        case 3: {
            if (arr[i].author == text)
                print_item(arr[i]);
            break;
        }
        default:
            break;
        }
    }
}

Information& find_item(Information*& arr, const int size) {
    int dec = -1;
    cout << "Find by:"
        << "\n1. Title"
        << "\n2. Carrier type"
        << "\n3. Author" << endl;
    cin >> dec;
    string text;
    cout << "Enter searching text: ";
    cin.ignore();
    getline(cin, text);
    for (int i = 0; i < size; i++) {
        switch (dec)
        {
        case 1: {
            if (arr[i].name == text)
                return arr[i];
            break;
        }
        case 2: {
            if (arr[i].carrier_type == text)
                return arr[i];
            break;
        }
        case 3: {
            if (arr[i].author == text)
                return arr[i];
            break;
        }
        default:
            break;
        }
    }
}

void change_item(Information*& arr, const int size) {
    if (!size) return;
    print_all(arr, size);
    cout << "\n Enter a number of the element to change: ";
    int number; cin >> number;
    Information temp = get_item_data();
    arr[number - 1] = temp;
}

void delete_item(Information*& arr, int& size) {
    if (!size) return;
    print_all(arr, size);
    cout << "\n Enter a number of the element to delete: ";
    int number; cin >> number;
    for (int i = number - 1; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    size--;
}
