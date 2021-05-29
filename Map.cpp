//
// Created by bayk on 21.05.2021.
//

#include <cmath>
#include <iostream>
#include "Map.h"

template<typename Key, typename Value, class comparator>
Map<Key, Value, comparator>::Map(const Map&other) {
    _size = other._size; //переприсваиваю нединамические переменные и делаю глубокое копирование
    _capacity = other._capacity;
    _data = new std::pair<Key, Value> [_capacity];
    for(int i = 0; i < _size; ++i){
        _data[i] = other._data[i];
    }
}

template<typename Key, typename Value, class comparator>
Map<Key, Value, comparator>& Map<Key, Value, comparator>::operator=(const Map &other) {
    if(this != &other){
        delete[] _data; //постпаю аналогично как и в конструкторе копирование, только предварительно очистив память
        _capacity = other._capacity;
        _size = other._size;
        _data = new std::pair<Key, Value> [_capacity];
        for(int i = 0; i < _size; ++i){
            _data[i] = other._data[i];
        }
    }
    return *this;
}

template<typename Key, typename Value, class comparator>
std::pair<MapIterator<Key, Value>, bool> Map<Key, Value, comparator>::insert(const std::pair<Key, Value>& node) {
    if(count(node.first)){ //проверяю, существует ли уже элемент с ключам key
        auto temp = find(node.first);
        (*temp).second = node.second;
        return {temp, false};
    } else{
        if(_size == _capacity - 1){ //проверяю, нужно ли дополнительно выделить память под новый элемент
            if(_capacity == 1){
                _capacity = 2;
            } else {
                _capacity = std::floor(1.5 * _capacity);
            }
            std::pair<Key, Value>* temp = new std::pair<Key, Value>[_capacity];
            for(int i = 0; i < _size; ++i){
                temp[i] = _data[i];
            }
            _data = temp;
        }
        _data[_size+1] = _data[_size]; //делаю сдвиг массива, для того чтобы встваить элемент. В этой строке двигаю элемент стоящий за последним
        for(int i = _size; i > 0; --i){ //алгоритм сдвига работает так: иду с конца, копируя в текщую ячейку значение из
            _data[i] = _data[i-1];      //предыдущей. Если key больше ключа текущей ячейки, то на её место вставляю переданну пару
            if(comparator()(node.first, (_data[i]).first)){
                _data[i] = node;
                ++_size;
                return {MapIterator(&_data[i]), true};
            }
        }
        _data[0] = node; //если к этому моменту функция не закончила работу, то элемент нужно вставить на первую позицию
        ++_size;
        return {MapIterator(&_data[0]), true};
    }
}

template<typename Key, typename Value, class comparator>
int Map<Key, Value, comparator>::count(const Key &key) {
    for(auto i = begin(); i != end(); ++i){ //функция пробегает по всем элементам и ищет совпадение по ключу
        if((*i).first == key){
            return 1;
        }
    }
    return 0;
}

template<typename Key, typename Value, class comparator>
MapIterator<Key, Value> Map<Key, Value, comparator>::find(const Key &key) {
    for(auto i = begin(); i != end(); ++i){ //работа аналогична функции count
        if((*i).first == key){
            return i;
        }
    }
    return end();
}

template<typename Key, typename Value, class comparator>
Value& Map<Key, Value, comparator>::at(const Key &key) {
    for(int i = 0; i < _size; ++i){ //функция пробегает все значения и при совпадении по ключу, возращает значаение ячейки
        if(_data[i].first == key){
            return _data[i].second;
        }
    }
    throw std::out_of_range("out_of_range");
}

template<typename Key, typename Value, class comparator>
MapIterator<Key, Value> Map<Key, Value, comparator>::erase(MapIterator<Key, Value> node) {
    if(node.operator->() >= end().operator->() || node.operator->() < begin().operator->()){ //проверяю, принадлежит ли
        throw std::logic_error("Container does not contain the element "); //переданный итератор текущему экзампляру класса, сравнивая адреса ячеек
    }
    int dist = node.operator->() - begin().operator->(); //нахожу номер ячейки, которую нужно удаалить, используя фунционал адресовячеек в статическом массиве
    for(int i = dist; i <= _size; ++i){ //сдвиг массива
        _data[i] = _data[i+1];
    }
    --_size;
    return MapIterator(&_data[dist]);
}

template<typename Key, typename Value, class comparator>
MapIterator<Key, Value> Map<Key, Value, comparator>::erase(MapIterator<Key, Value> first, MapIterator<Key, Value> last) {
    if(first.operator->() >= end().operator->() || first.operator->() < begin().operator->() || //делаю проверку на принадлежность переданных итераторов
    (last.operator->() > end().operator->()) || last.operator->() < begin().operator->()){ //текущему контейнеру
        throw std::logic_error("Container does not contain the element");
    }
    int distFirst = first.operator->() - begin().operator->(); //нахожу номера ячеек итераторов
    int distLast = (last.operator->()) - (begin().operator->());
    int range = distLast - distFirst; //проверяю, находится ли first перед last
    if(distLast <= distFirst){
        throw std::logic_error("The range is set incorrectly");
    }
    for(int i = distLast; i <= _size; ++i){
        _data[i-range] = _data[i];
    }
    _size -= range;
    return MapIterator(&_data[distFirst]);
}

template<typename Key, typename Value, class comparator>
MapIterator<Key, Value> Map<Key, Value, comparator>::erase(const Key& key) {
    auto temp = find(key); //нахожу итератор, который соответствует переданному ключу. Далее удаление аналогично предыдущим реализациям
    if(temp == end()){
        throw std::logic_error("Container does not contain the element");
    }
    int dist = temp.operator->() - begin().operator->();
    for(int i = dist; i <= _size; ++i){
        _data[i] = _data[i+1];
    }
    --_size;
    return MapIterator(&_data[dist]);
}

template<typename Key, typename Value, class comparator>
std::pair<Key, Value> Map<Key, Value, comparator>::extract(const Key &key) {
    auto temp = find(key); //нахожу итератор, который нужно извлечь
    if(temp == end()){
        throw std::logic_error("Container does not contain the element");
    }
    std::pair<Key, Value> result = *temp; //сохраняю разыменованный итератор в отдельную переменную, потому что после erase итератор сдвигается
    erase(temp);
    return result;
}

template<typename Key, typename Value, class comparator>
void Map<Key, Value, comparator>::merge(Map<Key, Value, comparator> &other) {
    for(auto i = other.begin(); i != other.end(); ++i){ //прохожу по всему other, и если нет какого-то элемента в текущем контейнере,
        if(!count((*i).first)){ //который есть в other, то вставляю его, используя ранее реализованную функцию
            insert(*i);
        }
    }
}