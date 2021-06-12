#include <algorithm>
#include "comparator.h"
#include <functional>
#include <iostream>
#include "Map.h"
#include <map>

void print(const std::pair<int, int>& it){
    std::cout << "{key : " << it.first << ", value : " << it.second << "}\n";
}

bool comp(std::pair<int, int>& a){
    return a.first > 5;
}

int main() {
    Map<int, int> myMap1, myMap2;
    myMap1.insert({1, 10});
    myMap2.insert({3, 30});
    myMap1.insert({2, 20});
    myMap1.insert({4, 40});
    myMap1.insert({5, 55});
    myMap2.insert({0, 0});
    myMap2.insert({5, 50});
    myMap1.insert({8, 80});
    myMap2.insert({6, 60});
    myMap1.insert({7, 70});
    std::for_each(myMap1.cbegin(), myMap1.cend(), print); //добавил работу с константными итераторами
    std::cout << '\n';
    //(*myMap1.cbegin()).second = 123; //на этой строке рушится компилятор, что подтверждает константность значения
    std::for_each(myMap1.rbegin(), myMap1.rend(), print);
    std::cout << '\n';
    std::for_each(myMap1.begin(), myMap1.end(), print);
    std::cout << '\n';
    std::for_each(myMap2.begin(), myMap2.end(), print);
    std::cout << '\n';
    myMap1.merge(myMap2);
    std::for_each(myMap1.begin(), myMap1.end(), print);
    std::cout << '\n';
    myMap1[3] = 35;
    std::for_each(myMap1.begin(), myMap1.end(), print);
    std::cout << '\n';
    myMap1[10] = 100;
    std::for_each(myMap1.begin(), myMap1.end(), print);
    std::cout << '\n';
    print(*myMap1.erase(3));
    for(auto i : myMap1){
        std::cout << '{' << i.first << " : " << i.second << '}' << '\n';
    }
    std::cout << '\n';
    auto min = std::min_element(myMap1.begin(), myMap1.end());
    auto max = std::max_element(myMap1.begin(), myMap1.end());
    std::cout << '{' << (*min).first << " : " << (*min).second << '}' << '\n';
    std::cout << '{' << (*max).first << " : " << (*max).second << '}' << '\n';
    std::cout << '\n';
    std::for_each(myMap1.begin(), myMap1.end(), print);
    return 0;
}
