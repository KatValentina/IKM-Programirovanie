#include <iostream>
#include <fstream>//для чтения из файла
#include <string>
#include <vector>
#include <stdexcept>//для обработки ошибок
#include "Header.h"

using namespace std;

// Функция для вставки узла в дерево
void AddLeaf(Node*& ptr, int value, const string& s, const string& originalS) {
    // Если текущего узла нет, создаём
    // Узел может быть промежуточным, поэтому hasKey = false
    if (ptr == NULL) {
        ptr = new Node(-1, false); // Создаем временный узел с -1, для построения дерева
    }

    if (s.empty()) {
        // Строка содержащая путь закончилась, ptr теперь указывает на целевой узел.
        if (ptr->hasKey) {//если у этого узла есть значение(hasKey = true) значит путь дублируется, а этого не должно быть
            throw runtime_error("Путь '" + originalS + "' уже занят другим значением");
        }
        // Присваиваем значение и отмечаем, что узел теперь содержит данные
        ptr->key = value;
        ptr->hasKey = true;
        return;
    }

    // строка s не пуста, продолжаем обход
    char b = s[0];
    string chast = s.substr(1);//убираем первый символ пути

    if (b == '0') { // Идем влево
        AddLeaf(ptr->left, value, chast, originalS);
    }
    else if (b == '1') { // Идем вправо
        AddLeaf(ptr->right, value, chast, originalS);
    }
}


// Функция для чтения данных из файла
vector<pair<int, string>> FromFile() {
    vector<pair<int, string>> data;//создаём вектор для записи значений
    ifstream file("Текст.txt");

    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл Текст.txt");
    }

    // Проверяем, что файл не пустой
    if (file.peek() == ifstream::traits_type::eof()) {
        throw runtime_error("Файл 'Текст.txt' пуст");
    }

    int value;//значение
    string path;//путь

    while (file.peek() != EOF) { // Читаем, пока не достигли конца файла

        // Считываем значение
        if (!(file >> value)) {//если ошибка
            file.clear();
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Ошибка чтения данных из файла. Некорректный формат.");
        }

        // Проверяем, что число больше 0
        if (value <= 0) {
            cerr << "Значение должно быть больше 0. В следующий раз будь внимательнее" << endl;
            throw runtime_error("Некорректное значение.");
        }

        //Записываем путь
        file >> path;
        for (char c : path) {
            if (c != '0' && c != '1') {
                throw runtime_error("Некорректное значение");
                break; // Прерываем цикл, если найден некорректный символ
            }
        }

        data.emplace_back(value, path);//записываем значение и путь в вектор
    }

    file.close();
    return data;
}

// Функция для ввода данных с клавиатуры
vector<pair<int, string>> Keyboard() {
    vector<pair<int, string>> data;//создаем вектор
    int value;//значение
    string path;//путь

    cout << "Введите пары значение-путь. Для завершения ввода в поле 'значение' ввести: 'stop'" << endl;
    while (true) {
        cout << "Значение: ";
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            string str;
            cin >> str;
            if (str == "stop") {
                break;
            }
            cerr <<"Неверное значение! Попробуй ввести повторно" << endl;
            throw runtime_error("");
        }

        if (value <= 0) {
            cerr << "Значение должно быть строго больше 0. Небольшая ошибка, но будь внимателен" << endl;
            throw runtime_error("");
        }

        cout << "Путь: ";
        cin >> path;
        for (char c : path) {
            if (c != '0' && c != '1') {
                cerr << "Путь должен содержать только 0 и 1!" << endl;
                throw runtime_error("");
            }
        }

        data.emplace_back(value, path);//записываем значение и путь в вектор
    }

    return data;
}

// Проверка на наличие узлов со значением -1. Так как узлы с таким значением являются промежуточными
void CheckEmptyLeaf(Node* node, bool &h) {
    if (node == NULL) {
        return;
    }
    if (node->key == -1) {
        h = true;
        return;
    }
    CheckEmptyLeaf(node->left,h);
    CheckEmptyLeaf(node->right,h);
}


//функция для вывода дерева
void Print(Node* Tree, string const& rpref, string const& cpref, string const& lpref) {
    if (!Tree) return;
    if (Tree->right)
        Print(Tree->right, rpref + "   ", rpref + " +--", rpref + " | ");
    cout << cpref << to_string(Tree->key) << endl;
    if (Tree->left)
        Print(Tree->left, lpref + " | ", lpref + " +--", lpref + "   ");
}

//функция удаления дерева
void DeleteTree(Node* tree) {
    if (tree->left)   DeleteTree(tree->left);
    if (tree->right)  DeleteTree(tree->right);
    delete tree;
}
