#include <iostream>
#include <fstream>//для чтения из файла
#include <string>
#include <vector>
#include <stdexcept>//для обработки ошибок
#include "Header.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    cout << "Приветствую пользователь! С помощью данной программы ты сможешь построить двоичное дерево."
        "Путь по дереву определяется указанным двоичным кодом в этом листе"
        "(1 – переход к правому потомку, 0 - переход к левому потомку).\n";
    cout << "Ознакомься." << endl;
    cout << "1 - С клавиатуры" << endl;
    cout << "2 - Из файла" << endl;
    cout << "Выберите способ ввода данных: ";
    int ch;//переменная под выбор
    cin >> ch;
    // Инициализируем корень со значением 0, и отмечаем, что он имеет значение.
    Node* root = new Node(0, true);
    vector<pair<int, string>> data;//вектор под значение и его путь

    try {
        switch (ch) {
        case 1:
            data = Keyboard();//Ввод с консоли
            break;
        case 2:
            data = FromFile();//Чтение из файла
            break;
        default:
            cout << "Нет такого способа заполнения." << endl;
            return 1;
        }

        // Вставляем узлы в дерево
        for (const auto& pair : data) {
            //передаём указатель на дерево, значение, часть пути для построения, оригинальный путь
            AddLeaf(root, pair.first, pair.second, pair.second);
        }

        bool hasZeroNodes = false;
        CheckEmptyLeaf(root, hasZeroNodes);//проверяем дерево на вспомогательные листья
        if (hasZeroNodes) {
            cerr << "Дерево не может быть построено! Введите корректные данные" << endl;
            return 1;
        }
        else {
            // Отображение дерева
            cout << "\nПолучившиеся дерево: " << endl;
            string rpref = "";
            string cpref = "";
            string lpref = "";
            Print(root, rpref, cpref, lpref);
        }
        DeleteTree(root);//освобождаем память
    }
    //обработка ошибок 
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
        return 1;
    }
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return 1;
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}