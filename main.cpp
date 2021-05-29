#include <algorithm>
#include "comparator.h"
#include <functional>
#include <iostream>
#include "Map.h"
#include <map>

void print(std::pair<int, int>& it){
    std::cout << "{key : " << it.first << ", value : " << it.second << "}\n";
}

bool comp(std::pair<int, int>& a){
    return a.first > 5;
}

int main() {
    Map<int, int, comparator> myMap1;
    myMap1.insert({1, 10});
    myMap1.insert({3, 30});
    myMap1.insert({2, 20});
    myMap1.insert({4, 40});
    myMap1.insert({0, 0});
    myMap1.insert({5, 50});
    myMap1.insert({8, 80});
    myMap1.insert({6, 60});
    myMap1.insert({7, 70});
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
