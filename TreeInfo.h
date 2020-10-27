#ifndef TREEPRINTER_TREEINFO_H
#define TREEPRINTER_TREEINFO_H

#include <string>

template <typename T>
class TreeInfo{
public:
    virtual std::string content() = 0;
    //告诉 left 是谁
    virtual T *getLeft() = 0;
    //告诉 right 是谁
    virtual T *getRight() = 0;
};

#endif //TREEPRINTER_TREEINFO_H
