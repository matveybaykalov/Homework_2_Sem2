//
// Created by bayk on 21.05.2021.
//

#ifndef HOMEWORK_2_SEM2_MAP_H
#define HOMEWORK_2_SEM2_MAP_H

#include <functional>

template<typename Key, typename Value>
class MapIterator{
public:
    std::pair<Key, Value>* _pos;
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer = std::pair<Key, Value>*;
    using reference = std::pair<Key, Value>&;

    MapIterator(std::pair<Key, Value>* _pos): _pos(_pos){}

    bool operator==(const MapIterator<Key, Value>& other){
        return _pos == other._pos;
    }

    bool operator!=(const MapIterator<Key, Value>& other){
        return _pos != other._pos;
    }

    reference operator*(){
        return *_pos;
    }

    pointer operator->(){
        return _pos;
    }

    MapIterator& operator++(){
        ++_pos;
        return *this;
    }

    MapIterator& operator++(int){
        MapIterator temp = *this;
        ++_pos;
        return temp;
    }

    MapIterator& operator--(){
        --_pos;
        return *this;
    }

    MapIterator& operator--(int){
        MapIterator temp = *this;
        --_pos;
        return temp;
    }
};

template<typename Key, typename Value>
class const_MapIterator{
    const std::pair<Key, Value>* _pos;
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer = const std::pair<Key, Value>*;
    using reference = const std::pair<Key, Value>&;

    const_MapIterator(const std::pair<Key, Value>* _pos): _pos(_pos){}

    bool operator==(const const_MapIterator<Key, Value>& other) const{
        return _pos == other._pos;
    }

    bool operator!=(const const_MapIterator<Key, Value>& other) const{
        return _pos != other._pos;
    }

    reference operator*() const{
        return *_pos;
    }

    pointer operator->() const{
        return _pos;
    }
    const_MapIterator& operator++(){
        ++_pos;
        return *this;
    }

    const_MapIterator& operator++(int){
        MapIterator temp = *this;
        ++_pos;
        return temp;
    }

    const_MapIterator& operator--(){
        --_pos;
        return *this;
    }

    const_MapIterator& operator--(int){
        MapIterator temp = *this;
        --_pos;
        return temp;
    }
};

template<typename Key, typename Value>
class revers_MapIterator{
    std::pair<Key, Value>* _pos;
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer = std::pair<Key, Value>*;
    using reference = std::pair<Key, Value>&;

    revers_MapIterator(std::pair<Key, Value>* _pos): _pos(_pos){}

    bool operator==(const revers_MapIterator<Key, Value>& other){
        return _pos == other._pos;
    }

    bool operator!=(const revers_MapIterator<Key, Value>& other){
        return _pos != other._pos;
    }

    reference operator*(){
        return *_pos;
    }

    pointer operator->(){
        return _pos;
    }

    revers_MapIterator& operator++(){
        --_pos;
        return *this;
    }

    revers_MapIterator& operator++(int){
        MapIterator temp = *this;
        --_pos;
        return temp;
    }

    revers_MapIterator& operator--(){
        ++_pos;
        return *this;
    }

    revers_MapIterator& operator--(int){
        MapIterator temp = *this;
        ++_pos;
        return temp;
    }
};

template<typename Key, typename Value>
class const_revers_MapIterator{
    const std::pair<Key, Value>* _pos;
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer = const std::pair<Key, Value>*;
    using reference = const std::pair<Key, Value>&;

    const_revers_MapIterator(const std::pair<Key, Value>* _pos): _pos(_pos){}

    bool operator==(const const_revers_MapIterator<Key, Value>& other) const{
        return _pos == other._pos;
    }

    bool operator!=(const const_revers_MapIterator<Key, Value>& other) const{
        return _pos != other._pos;
    }

    reference operator*() const{
        return *_pos;
    }

    pointer operator->() const{
        return _pos;
    }
    const_revers_MapIterator& operator++(){
        --_pos;
        return *this;
    }

    const_revers_MapIterator& operator++(int){
        MapIterator temp = *this;
        --_pos;
        return temp;
    }

    const_revers_MapIterator& operator--(){
        ++_pos;
        return *this;
    }

    const_revers_MapIterator& operator--(int){
        MapIterator temp = *this;
        ++_pos;
        return temp;
    }
};

template<typename Key, typename Value, class comparator = std::greater<Key>>
class Map {
    std::pair<Key, Value>* _data;
    int _size;
    int _capacity;
public:
    Map(const Map& other);
    Map& operator= (const Map& other);
    ~Map(){
        delete _data;
    }
    Map(){
        _size = 0;
        _capacity = 0;
        _data = new std::pair<Key, Value>[_capacity + 2]; //выделяю память под 2 элемента стоящий за последним и перед первым (для реверс итераторов)
    }
    MapIterator<Key, Value> begin(){
        return MapIterator(&_data[1]);
    }
    MapIterator<Key, Value> end(){
        return MapIterator(&_data[_size+1]);
    }
    const_MapIterator<Key, Value> cbegin(){
        return const_MapIterator(&_data[1]);
    }
    const_MapIterator<Key, Value> cend(){
        return const_MapIterator(&_data[_size+1]);
    }
    revers_MapIterator<Key, Value> rbegin(){
        return revers_MapIterator(&_data[_size]);
    }
    revers_MapIterator<Key, Value> rend(){
        return revers_MapIterator(&_data[0]);
    }
    const_revers_MapIterator<Key, Value> crbegin(){
        return const_revers_MapIterator(&_data[_size]);
    }
    const_revers_MapIterator<Key, Value> crend(){
        return const_revers_MapIterator(&_data[0]);
    }
    std::pair<MapIterator<Key, Value>, bool> insert(const std::pair<Key, Value>& node);
    MapIterator<Key, Value> erase(MapIterator<Key, Value> node);
    MapIterator<Key, Value> erase(MapIterator<Key, Value> first, MapIterator<Key, Value> last);
    MapIterator<Key, Value> erase(const Key& key);
    std::pair<Key, Value> extract(const Key& key);
    std::pair<Key, Value> extract(MapIterator<Key, Value> node);
    void merge(Map& other);
    int count(const Key& key);
    MapIterator<Key, Value> find(const Key& key);
    Value& at(const Key& key);
    Value& operator[](const Key& key);
    int capacity(){
        return _capacity;
    }
    bool empty(){
        return _size == 0;
    }
    int size(){
        return _size;
    }
    void clear(){
        delete _data; //удаляю предыдущие данные и инициализирую поля теми  же значениями, которые задаю при создании контейнера
        _size = 0;
        _capacity = 0;
        _data = new std::pair<Key, Value>[_capacity+2];
    }
    void swap(Map& other){ //в этой функции решил использовать функционал оператора присваивания
        Map temp = *this;
        *this = other;
        other =  temp;
    }
};


#endif //HOMEWORK_2_SEM2_MAP_H
