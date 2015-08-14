#pragma once

#define SIZE 50

#include <string>

typedef std::string Key;

struct Value {
    unsigned age;
    unsigned weight;
};

class HashTable
{
private:
    struct Element {
        Key key;
        Value value;
        Element *next;
    };

    Element **table;

    int hashFunction(const Key& key) const;

public:
    HashTable();
    virtual ~HashTable();

    HashTable(const HashTable& b);

// ���������� �������� ���� ���-������.
// ���������, ����� ����� ���� �����, ��� ������� ����������� �������
// std::swap.
    void swap(HashTable& b);

    HashTable& operator=(const HashTable& b);

// ������� ���������.
    void clear();
// ������� ������� �� ��������� �����.
    bool erase(const Key& k);
// ������� � ���������. ������������ �������� - ���������� �������.
    bool insert(const Key& k, const Value& v);

// �������� ������� �������� �� ��������� �����.
    bool contains(const Key& k) const;

// ���������� �������� �� �����. ������������ �����.
// � ������ ���������� ����� � ���������� ������� �������� � ���������
// ��������, ��������� ������������� �� ��������� � ������� ������ �� ����.
    Value& operator[](const Key& k);

// ���������� �������� �� �����. ������� ���������� ��� �������.
    Value& at(const Key& k);
    const Value& at(const Key& k) const;

    //size_t 
    int size() const;
    bool empty() const;

    friend bool operator==(const HashTable & a, const HashTable & b);
    friend bool operator!=(const HashTable & a, const HashTable & b);

    enum Exceptions
    {   
        ElementNotFoundException
    };
};


