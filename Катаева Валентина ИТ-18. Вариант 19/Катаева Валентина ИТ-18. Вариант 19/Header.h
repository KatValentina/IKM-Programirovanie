#pragma once
#include <iostream>
#include <fstream>//для чтения из файла
#include <string>
#include <vector>
#include <stdexcept>//для обработки ошибок

using namespace std;

// Структура узла дерева
class Node {
public:
    int key;
    Node* left;
    Node* right;//указатели на левое и правое поддерево 
    bool hasKey; // true, если узел содержит значение из входных данных

    // По умолчанию создаем узел без значения (hasKey = false)
    Node(int val = -1, bool hasK = false)
        : key(val), left(NULL), right(NULL), hasKey(hasK) {
    }

};

// Функция для вставки узла в дерево
void AddLeaf(Node*& ptr, int value, const string& s, const string& original_s);

// Функция для чтения данных из файла
vector<pair<int, string>> FromFile();

// Функция для ввода данных с клавиатуры
vector<pair<int, string>> Keyboard();

// Проверка на наличие узлов со значением -1. Так как узлы с таким значением являются промежуточными
void CheckEmptyLeaf(Node* node, bool &h);

//функция для вывода дерева
void Print(Node* Tree, string const& rpref, string const& cpref, string const& lpref);

//функция удаления дерева
void DeleteTree(Node* tree);
