//
// Created by bayk on 21.05.2021.
//

#ifndef HOMEWORK_2_SEM2_COMPARATOR_H
#define HOMEWORK_2_SEM2_COMPARATOR_H

class comparator{
public:
    bool operator()(const int & lhs, const int & rhs){
        return lhs > rhs;
    }
};

#endif //HOMEWORK_2_SEM2_COMPARATOR_H
