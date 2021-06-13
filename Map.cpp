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
    _data = new std::pair<Key, Value> [_capacity + 2];
    for(int i = 1; i < _size + 1; ++i){
        _data[i] = other._data[i];
    }
}

template<typename Key, typename Value, class comparator>
Map<Key, Value, comparator>& Map<Key, Value, comparator>::operator=(const Map &other) {
    if(this != &other){
        delete[] _data; //постпаю аналогично как и в конструкторе копирование, только предварительно очистив память
        _capacity = other._capacity;
        _size = other._size;
        _data = new std::pair<Key, Value> [_capacity + 2];
        for(int i = 1; i < _size + 1; ++i){
            _data[i] = other._data[i];
        }
    }
    return *this;
}

template<typename Key, typename Value, class comparator>
std::pair<MapIterator<Key, Value>, bool> Map<Key, Value, comparator>::insert(const std::pair<Key, Value>& node) {
    auto temp = find(node.first);
    if(temp != end()){ //проверяю, существует ли уже элемент с ключам key
        (*temp).second = node.second;
        return {temp, false};
    } else{
        if(_size == _capacity){ //проверяю, нужно ли дополнительно выделить память под новый элемент
            if(_capacity == 0){
                _capacity = 1;
            } else if(_capacity == 1){
                _capacity = 2;
            } else {
                _capacity = std::floor(1.5 * _capacity);
            }
            std::pair<Key, Value>* tempData = new std::pair<Key, Value>[_capacity + 2];
            for(int i = 1; i < _size + 1; ++i){
                tempData[i] = _data[i];
            }
            _data = tempData;
        }
        _data[_size + 2] = _data[_size + 1];//делаю сдвиг массива, для того чтобы встваить элемент. В этой строке двигаю элемент стоящий за последним
        for(int i = _size + 1; i > 1; --i){ //алгоритм сдвига работает так: иду с конца, копируя в текщую ячейку значение из
            _data[i] = _data[i-1];          //предыдущей. Если key больше ключа текущей ячейки, то на её место вставляю переданну пару
            if(comparator()(node.first, (_data[i]).first)){
                _data[i] = node;
                ++_size;
                return {MapIterator(&_data[i]), true};
            }
        }
        _data[1] = node; //если к этому моменту функция не закончила работу, то элемент нужно вставить на первую позицию
        ++_size;
        return {MapIterator(&_data[1]), true};
    }
}

template<typename Key, typename Value, class comparator>
Value& Map<Key, Value, comparator>::operator[](const Key &key) { //по сути это тот же insert, но они отличаются возвращаемым значением
    auto temp = find(key);
    if(temp != end()){
        return (*temp).second;
    } else{
        if(_size == _capacity){
            if(_capacity == 0){
                _capacity = 1;
            } else if(_capacity == 1){
                _capacity = 2;
            } else {
                _capacity = std::floor(1.5 * _capacity);
            }
            std::pair<Key, Value>* tempData = new std::pair<Key, Value>[_capacity + 2];
            for(int i = 1; i < _size + 1; ++i){
                tempData[i] = _data[i];
            }
            _data = tempData;
        }
        _data[_size + 2] = _data[_size + 1];
        for(int i = _size + 1; i > 1; --i){
            _data[i] = _data[i-1];
            if(comparator()(key, (_data[i]).first)){
                _data[i].first = key;
                ++_size;
                return _data[i].second;
            }
        }
        _data[1].first = key;
        ++_size;
        return _data[1].second;
    }
}

template<typename Key, typename Value, class comparator>
int Map<Key, Value, comparator>::count(const Key &key) {
    int pos = 0;
    int h = std::floor(_size/2);
    h = 1 << h;
    while (h > 0){
        if(pos + h >= _size){
            h /= 2;
        } else if(key >= _data[pos + h + 1].first){
            pos += h;
            if(key == _data[pos + 1].first){
                break;
            }
        }
        h /= 2;
    }
    if(_data[pos + 1].first == key){
        return 1;
    } else {
        return 0;
    }
}

template<typename Key, typename Value, class comparator>
MapIterator<Key, Value> Map<Key, Value, comparator>::find(const Key &key) {
    int pos = 0;
    int h = std::floor(_size/2);
    h = 1 << h;
    while (h > 0){
        if(pos + h >= _size){
            h /= 2;
        } else if(key >= _data[pos + h + 1].first){
            pos += h;
            if(key == _data[pos + 1].first){
                break;
            }
        }
        h /= 2;
    }
    if(_data[pos + 1].first == key){
        return MapIterator(&_data[pos + 1]);
    } else {
        return end();
    }
}

template<typename Key, typename Value, class comparator>
Value& Map<Key, Value, comparator>::at(const Key &key) {
    int pos = 0;
    int h = std::floor(_size/2);
    h = 1 << h;
    while (h > 0){
        if(pos + h >= _size){
            h /= 2;
        } else if(key >= _data[pos + h + 1].first){
            pos += h;
            if(key == _data[pos + 1].first){
                break;
            }
        }
        h /= 2;
    }
    if(_data[pos + 1].first == key){
        return _data[pos + 1].second;
    } else {
        throw std::out_of_range("out_of_range");
    }
}

template<typename Key, typename Value, class comparator>
MapIterator<Key, Value> Map<Key, Value, comparator>::erase(MapIterator<Key, Value> node) {
    if(node._pos >= end()._pos || node._pos < begin()._pos){ //проверяю, принадлежит ли
        throw std::logic_error("Container does not contain the element "); //переданный итератор текущему экзампляру класса, сравнивая адреса ячеек
    }
    int dist = node._pos - begin()._pos; //нахожу номер ячейки, которую нужно удаалить, используя фунционал адресовячеек в статическом массиве
    for(int i = dist + 1; i <= _size; ++i){ //сдвиг массива. Теперь выхода за рамки выделенной памяти нет, так как появился нулевой элемент,необходимый для ревер итератора
        _data[i] = _data[i+1];
    }
    --_size;
    return MapIterator(&_data[dist + 1]);
}

template<typename Key, typename Value, class comparator>
MapIterator<Key, Value> Map<Key, Value, comparator>::erase(MapIterator<Key, Value> first, MapIterator<Key, Value> last) {
    if(first._pos >= end()._pos || first._pos < begin()._pos || //делаю проверку на принадлежность переданных итераторов
    (last._pos > end()._pos) || last._pos < begin()._pos){ //текущему контейнеру
        throw std::logic_error("Container does not contain the element");
    }
    int distFirst = first._pos - begin()._pos; //нахожу номера ячеек итераторов
    int distLast = last._pos - begin()._pos;
    int range = distLast - distFirst; //проверяю, находится ли first перед last
    if(distLast <= distFirst){
        throw std::logic_error("The range is set incorrectly");
    }
    for(int i = distLast+1; i <= _size; ++i){
        _data[i-range] = _data[i];
    }
    _size -= range;
    return MapIterator(&_data[distFirst + 1]);
}

template<typename Key, typename Value, class comparator>
MapIterator<Key, Value> Map<Key, Value, comparator>::erase(const Key& key) {
    auto temp = find(key); //нахожу итератор, который соответствует переданному ключу. Далее удаление аналогично предыдущим реализациям
    if(temp == end()){
        throw std::logic_error("Container does not contain the element");
    }
    int dist = temp._pos - begin()._pos;
    for(int i = dist + 1; i <= _size; ++i){
        _data[i] = _data[i + 1];
    }
    --_size;
    return MapIterator(&_data[dist + 1]);
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
std::pair<Key, Value> Map<Key, Value, comparator>::extract(MapIterator<Key, Value> node) {
    std::pair<Key, Value> result = *node;
    erase(node); //при удалении ячейки, если обнаружится, что итеартор не принадлежит текущему контейнеру, будет выброшено исключение
    return result;
}

template<typename Key, typename Value, class comparator>
void Map<Key, Value, comparator>::merge(Map<Key, Value, comparator> &other) {
    int tempSize = _size + other._size;
    std::pair<Key, Value>* tempData = new std::pair<Key, Value> [tempSize + 2]; //выделяю память на максимально возможное число элементов. Если в двух контейнерах будут одинаковые жлементы, то памяти будет выделено "с запасом"
    int thisFlag = 1, otherFlag = 1, i = 1; //решил использовать принцип с двумя флагами, которые пробегают каждый по своему массиву и сравнивают элементы. Меньший из них добавляется в итоговый массив
    while(thisFlag <= _size || otherFlag <= other._size){
        if((thisFlag <= _size) && (otherFlag <= other._size) && (_data[thisFlag].first == other._data[otherFlag].first)){
            tempData[i] = _data[thisFlag];
            ++thisFlag;
            ++otherFlag;
            ++i;
        } else if((!comparator()(_data[thisFlag].first, other._data[otherFlag].first) || otherFlag > other._size) && (thisFlag <= _size)){ //делаю проверку на то, что элемент из первого массивабыл меньше элемента из второго массива,
            tempData[i] = _data[thisFlag]; //при этом, этот код выполняется, если otherFlag дошёл до конца второго массива. Но этот код не должен выполняться, если thisFlag дошёл до конца первого массива,
            ++thisFlag; //и все элементы должны быть добавлены из второго массива
            ++i;
        }  else {
            tempData[i] = other._data[otherFlag];
            ++otherFlag;
            ++i;
        }
    }
    delete [] _data;
    _data = tempData;
    _size = i - 1; //вычетаю единицу, потому что она добавляется на последней итарции цикла, чтобы вставить следующий элемент
    _capacity = tempSize;

}