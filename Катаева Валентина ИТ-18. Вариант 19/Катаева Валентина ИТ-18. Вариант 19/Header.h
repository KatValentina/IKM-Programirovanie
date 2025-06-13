#pragma once
#include <iostream>
#include <fstream>//��� ������ �� �����
#include <string>
#include <vector>
#include <stdexcept>//��� ��������� ������

using namespace std;

// ��������� ���� ������
class Node {
public:
    int key;
    Node* left;
    Node* right;//��������� �� ����� � ������ ��������� 
    bool has_key; // true, ���� ���� �������� �������� �� ������� ������

    // �� ��������� ������� ���� ��� �������� (has_key = false)
    Node(int val = -1, bool has_k = false)
        : key(val), left(NULL), right(NULL), has_key(has_k) {
    }

};

// ������� ��� ������� ���� � ������
void AddLeaf(Node*& ptr, int value, const string& s, const string& original_s);

// ������� ��� ������ ������ �� �����
vector<pair<int, string>> FromFile();

// ������� ��� ����� ������ � ����������
vector<pair<int, string>> Keyboard();

// �������� �� ������� ����� �� ��������� -1. ��� ��� ���� � ����� ��������� �������� ��������������
void CheckEmptyLeaf(Node* node, bool &h);

//������� ��� ������ ������
void Print(Node* Tree, string const& rpref, string const& cpref, string const& lpref);

//������� �������� ������
void DeleteTree(Node* tree);