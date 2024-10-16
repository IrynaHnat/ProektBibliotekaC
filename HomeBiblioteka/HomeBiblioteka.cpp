
#include <iostream>
#include<string>
#include<fstream>
#include <Windows.h>

using namespace std;

const int MAX_SIZE = 100;
struct Library {
    string type;
    string title;
    string author;
    string year;
    string category;
};


string toLowerCase(const string& line)
{
    string str = line;
    for (size_t i = 0; i < line.length(); i++)
    {
        str[i] = tolower(line[i]);
    }
    return str;
}


void saveToFile(Library* library, int size, const string& filename) {
    ofstream file(filename); 
    if (!file.is_open()) {
         cout<< "Не вдалося відкрити файл для запису!" << endl;
        return;
    }
    for (int i = 0; i < size; ++i) {
        file << library[i].type << endl;
        file << library[i].title << endl;
        file << library[i].author << endl;
        file << library[i].year << endl;
        file << library[i].category << endl;
    }
    file.close();
}

void fillLibrary(Library*& library, int& size) {
    string userInput;
    do {
        if (size >= MAX_SIZE) {
            cout << "Максимальна кількість записів досягнута!" << endl;
            break;
        }

        cout << "\t\tEnter Type     :: "; getline(cin, library[size].type);
        cout << "\t\tEnter Title    :: "; getline(cin, library[size].title);
        cout << "\t\tEnter Author   :: "; getline(cin, library[size].author);
        cout << "\t\tEnter Year     :: "; getline(cin, library[size].year);
        cout << "\t\tEnter Category :: "; getline(cin, library[size].category);

        size++;

        cout << "Бажаєте додати ще одну книгу? (введіть 'стоп' для зупинки): ";
        getline(cin, userInput);

    } while (toLowerCase(userInput) != "стоп");
}


int loadFromFile(Library* &library,int &size, const string& filename) {
    ifstream file(filename);  
    if (!file.is_open()) {
        cout << "Файл не знайдено, буде створено новий!" << endl;
        return 0;  
    }

    size= 0;
    while (size < MAX_SIZE && getline(file, library[size].type)) {
        getline(file, library[size].title);
        getline(file, library[size].author);
        getline(file, library[size].year);
        getline(file, library[size].category);
        size++;
    }

    file.close();
    return size;
}

void appendToFile(Library* &library, int &size, const string& filename) {
    if (size >= MAX_SIZE) {
        cout << "Максимальна кількість записів досягнута!" << endl;
        return;
    }

    fillLibrary(library,size);
    size++;
    saveToFile(library, size, filename);
}


void viewAllData(Library* library,int size) {
    if (size == 0) {
        cout << "База даних порожня!" << endl;
        return;
    }

    for (int i = 0; i < size; i++) {
        cout << "==========================" << endl;
        cout << "Джерело №" << (i + 1) << endl;
        cout << "Type: " << library[i].type << endl;
        cout << "Title: " << library[i].title << endl;
        cout << "Author: " << library[i].author << endl;
        cout << "Year: " << library[i].year << endl;
        cout << "Category: " << library[i].category << endl;
        cout << "==========================" << endl;
    }
}


void removeByAuthor(Library*& library, int& size, const string& author) {
    bool found = false; 

    for (int i = 0; i < size; i++) {
        if (toLowerCase(library[i].author) == toLowerCase(author)) {
            for (int j = i; j < size - 1; j++) {
                library[j] = library[j + 1];  
            }
            size--;  
            i--;  
            found = true; 
        }
    }

    if (found) {
        cout << "Записи з автором \"" << author << "\" видалено." << endl;
    }
    else {
        cout << "Записів з автором \"" << author << "\" не знайдено." << endl;
    }
}


void sortByTypeAndTitle(Library* library, const int& size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (toLowerCase(library[j].type) > toLowerCase(library[j + 1].type) ||
                (toLowerCase(library[j].type) == toLowerCase(library[j + 1].type) &&
                    toLowerCase(library[j].title) > toLowerCase(library[j + 1].title))) {
                swap(library[j], library[j + 1]);
            }
        }
    }
}

int searchByAuthorAndTitle(const Library* library, const int& size, const string& author, const string& title) {
    for (int i = 0; i < size; i++) {
        if (toLowerCase(library[i].author) == toLowerCase(author) &&
            toLowerCase(library[i].title) == toLowerCase(title)) {

            return i;
        }
    }
    return -1;
}


void selectBooksByAuthor(const Library* library, const int& size, const string& author) {
    for (int i = 0; i < size; i++) {
        if (toLowerCase(library[i].author) == toLowerCase(author) && toLowerCase(library[i].type) == "book") {
            cout << "Title: " << library[i].title << ", Year: " << library[i].year << ", Category: " << library[i].category << endl;
        }
    }
}



void selectBooksByCategory(const Library* library, const int& size, const string& category) {
    for (int i = 0; i < size; i++) {
        if (toLowerCase(library[i].category) == toLowerCase(category) && toLowerCase(library[i].type) == "book") {
            cout << "Title: " << library[i].title << ", Author: " << library[i].author << ", Year: " << library[i].year << endl;
        }
    }
}

void selectJournalsByYearAndTitle(const Library* library, const int& size, const string& title, const string& year) {
    for (int i = 0; i < size; i++) {
        if (toLowerCase(library[i].title) == toLowerCase(title) && library[i].year == year && toLowerCase(library[i].type) == "magazine") {
            cout << "Title: " << library[i].title << "," <<" Year: " << library[i].year << ", Category : " << library[i].category<< endl;
        }
    }
}

int countBooksByCategory(const Library* library, const int& size, const string& category) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (toLowerCase(library[i].category) == toLowerCase(category) && toLowerCase(library[i].type) == "book") {
            count++;
        }
    }
    return count;

}

void removeNewspapersByYear(Library*& library, int& size, const string& year) {
    bool found = false;
    for (int i = 0; i < size; i++) {
        if (library[i].year == year && toLowerCase(library[i].type) == "newspaper") {
            for (int j = i; j < size - 1; j++) {
                library[j] = library[j + 1];
            }
            size--;
            i--; 
            found = true;
        }
    }
    if (found) {
        cout << "Газети за рік \"" << year << "\" видалено." << endl;
    }
    else {
        cout << "Газет за рік \"" << year << "\" не знайдено." << endl;
    }
}


void showMenu() {
    cout << "===== Меню =====" << endl;
    cout << "1. Заповнення бази даних" << endl;
    cout << "2. Перегляд даних про всі джерела" << endl;
    cout << "3. Доповнення бази даних записом джерела" << endl;
    cout << "4. Видалення запису за автором" << endl;
    cout << "5. Упорядкування по полях: тип і назва" << endl;
    cout << "6. Пошук джерела за автором і назвою" << endl;
    cout << "7. Вибірка: книги автора ХХ; книги певної категорії, журнали за певний рік" << endl;
    cout << "8. Обчислення: кількість книг деякої категорії" << endl;
    cout << "9. Корекція: видалення зведень про газети за певний рік" << endl;

    cout << "0. Вихід" << endl;
    cout << "================" << endl;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int size = 0;
    Library* library = new Library[MAX_SIZE];

    int choice;
    string filename = "libraryDatabase.txt";

    loadFromFile(library, size, filename);


    do {
        showMenu();
        cout << "Ваш вибір: ";
        cin >> choice;
        cin.ignore();  

        switch (choice) {
        case 1:
            if (size < MAX_SIZE) {
                fillLibrary(library,size);
                saveToFile(library, size, filename);
            }
            else {
                cout << "Максимальна кількість записів досягнута!" << endl;
            }
            break;
        case 2:
            viewAllData(library, size);
            break;
        case 3:
            appendToFile(library, size, filename);
            break;
        case 4:
        {
            string author;
            cout << "Введіть ім'я автора для видалення: ";
            getline(cin, author);
            removeByAuthor(library, size, author);
            saveToFile(library, size, filename);
        }
        break;
        case 5:
        {
            sortByTypeAndTitle(library, size);
            cout << "Дані упорядковано за типом і назвою." << endl;
            saveToFile(library, size, filename);
            viewAllData(library, size);
            break;
        }
        case 6:
        {
            string author, title;
            cout << "Введіть автора : ";
            getline(cin, author);
            cout << "Введіть назву: ";
            getline(cin, title);
            int position = searchByAuthorAndTitle(library, size, author, title);
            if (position != -1) {
                cout << "Джерело знайдено в базі даних на позиції " << position + 1 << "." << endl;
            }
            else {
                cout << "Джерело не знайдено в базі даних." << endl;
            }
            break;
        }
        case 7:
        {
            string author, category, year, titleJournal;

            cout << "Введіть ім'я автора книг для вибірки: " << endl;
            getline(cin, author);

            cout << "Введіть категорію для вибірки книг: ";
            getline(cin, category);


            cout << "Введіть рік журналу: " << endl;
            getline(cin, year);

            cout << "Введіть назву журналу для вибірки: " << endl;
            getline(cin, titleJournal);
            cout << endl;
            cout << "========BOOK==========" << endl;
            selectBooksByAuthor(library, size, author);
            selectBooksByCategory(library, size, category);
            cout << endl;
            cout << "========MAGAZINE==========" << endl;
            selectJournalsByYearAndTitle(library, size, titleJournal, year);
        }
        break;

        case 8:
        {
            string category;
            cout << "Введіть категорію книги: " << endl;
          
            getline(cin,category);
            cout<<"Кількість книг категорії "<< category <<" : "<<countBooksByCategory(library, size, category)<<endl;
            
        }
        break;

        case 9:
        {
            string year;
            cout << "Введіть рік для видалення газет: ";
            getline(cin, year);
            removeNewspapersByYear(library,size,year);
            saveToFile(library, size, filename);
            ;
        }
        break;
        
        case 0:
            cout << "Вихід з програми..." << endl;
            break;
        default:
            cout << "Невірний вибір! Спробуйте знову." << endl;
        }
    } while (choice != 0);

    delete[] library;

}