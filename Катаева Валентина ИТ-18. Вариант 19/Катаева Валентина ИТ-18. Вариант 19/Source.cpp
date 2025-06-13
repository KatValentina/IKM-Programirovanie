#include <iostream>
#include <fstream>//��� ������ �� �����
#include <string>
#include <vector>
#include <stdexcept>//��� ��������� ������
#include "Header.h"

using namespace std;


// ������� ��� ������� ���� � ������
void AddLeaf(Node*& ptr, int value, const string& s, const string& original_s) {
    // ���� �������� ���� ���, ������
    // ���� ����� ���� �������������, ������� has_key = false
    if (ptr == NULL) {
        ptr = new Node(-1, false); // ������� ��������� ���� � -1, ��� ���������� ������
    }

    if (s.empty()) {
        // ������ ���������� ���� �����������, ptr ������ ��������� �� ������� ����.
        if (ptr->has_key) {//���� � ����� ���� ���� ��������(has_key = true) ������ ���� �����������, � ����� �� ������ ����
            throw runtime_error("���� '" + original_s + "' ��� ����� ������ ���������");
        }
        // ����������� �������� � ��������, ��� ���� ������ �������� ������
        ptr->key = value;
        ptr->has_key = true;
        return;
    }

    // ������ s �� �����, ���������� �����
    char b = s[0];
    string chast = s.substr(1);//������� ������ ������ ����

    if (b == '0') { // ���� �����
        AddLeaf(ptr->left, value, chast, original_s);
    }
    else if (b == '1') { // ���� ������
        AddLeaf(ptr->right, value, chast, original_s);
    }
}


// ������� ��� ������ ������ �� �����
vector<pair<int, string>> FromFile() {
    vector<pair<int, string>> data;//������ ������ ��� ������ ��������
    ifstream file("�����.txt");

    if (!file.is_open()) {
        throw runtime_error("�� ������� ������� ���� �����.txt");
    }

    // ���������, ��� ���� �� ������
    if (file.peek() == ifstream::traits_type::eof()) {
        throw runtime_error("���� '�����.txt' ����");
    }

    int value;//��������
    string path;//����

    while (file.peek() != EOF) { // ������, ���� �� �������� ����� �����

        // ��������� ��������
        if (!(file >> value)) {//���� ������
            file.clear();
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("������ ������ ������ �� �����. ������������ ������.");
        }

        // ���������, ��� ����� ������ 0
        if (value <= 0) {
            cerr << "�������� ������ ���� ������ 0. � ��������� ��� ���� ������������" << endl;
            throw runtime_error("������������ ��������.");
        }

        //���������� ����
        file >> path;
        for (char c : path) {
            if (c != '0' && c != '1') {
                throw runtime_error("������������ ��������");
                break; // ��������� ����, ���� ������ ������������ ������
            }
        }

        data.emplace_back(value, path);//���������� �������� � ���� � ������
    }

    file.close();
    return data;
}

// ������� ��� ����� ������ � ����������
vector<pair<int, string>> Keyboard() {
    vector<pair<int, string>> data;//������� ������
    int value;//��������
    string path;//����

    cout << "������� ���� ��������-����. ��� ���������� ����� � ���� '��������' ������: 'stop'" << endl;
    while (true) {
        cout << "��������: ";
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            string str;
            cin >> str;
            if (str == "stop") {
                break;
            }
            cerr <<"�������� ��������! �������� ������ ��������" << endl;
            throw runtime_error("");
        }

        if (value <= 0) {
            cerr << "�������� ������ ���� ������ ������ 0. ��������� ������, �� ���� ����������" << endl;
            throw runtime_error("");
        }

        cout << "����: ";
        cin >> path;
        for (char c : path) {
            if (c != '0' && c != '1') {
                cerr << "���� '" << path << "' ������ ��������� ������ 0 � 1!" << endl;
                throw runtime_error("");
            }
        }

        data.emplace_back(value, path);//���������� �������� � ���� � ������
    }

    return data;
}

// �������� �� ������� ����� �� ��������� -1. ��� ��� ���� � ����� ��������� �������� ��������������

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


//������� ��� ������ ������
void Print(Node* Tree, string const& rpref, string const& cpref, string const& lpref) {
    if (!Tree) return;
    if (Tree->right)
        Print(Tree->right, rpref + "   ", rpref + " +--", rpref + " | ");
    cout << cpref << to_string(Tree->key) << endl;
    if (Tree->left)
        Print(Tree->left, lpref + " | ", lpref + " +--", lpref + "   ");
}

//������� �������� ������
void DeleteTree(Node* tree) {
    if (tree->left)   DeleteTree(tree->left);
    if (tree->right)  DeleteTree(tree->right);
    delete tree;
}