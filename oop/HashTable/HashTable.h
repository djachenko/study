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

// Обменивает значения двух хэш-таблиц.
// Подумайте, зачем нужен этот метод, при наличии стандартной функции
// std::swap.
    void swap(HashTable& b);

    HashTable& operator=(const HashTable& b);

// Очищает контейнер.
    void clear();
// Удаляет элемент по заданному ключу.
    bool erase(const Key& k);
// Вставка в контейнер. Возвращаемое значение - успешность вставки.
    bool insert(const Key& k, const Value& v);

// Проверка наличия значения по заданному ключу.
    bool contains(const Key& k) const;

// Возвращает значение по ключу. Небезопасный метод.
// В случае отсутствия ключа в контейнера следует вставить в контейнер
// значение, созданное конструктором по умолчанию и вернуть ссылку на него.
    Value& operator[](const Key& k);

// Возвращает значение по ключу. Бросает исключение при неудаче.
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


