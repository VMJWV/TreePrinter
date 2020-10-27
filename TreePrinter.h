#ifndef TREEPRINTER_TREEPRINTER_H
#define TREEPRINTER_TREEPRINTER_H

#include <iostream>
#include <vector>
#include "TreeInfo.h"
#include <queue>
#include <sstream>

class TreePrinter {
public:
    //将二叉树的树形状输出到ostream中去
    template<typename T>
    static void printTree(TreeInfo<T> *root,std::ostream &out = std::cout);
    //获得二叉树树形的字符串
    template<typename T>
    static std::string treeStr(TreeInfo<T> *root);
    //把 一个 二叉链表 表示的tree 转换为 一个 顺序存储的完全二叉树
    template<typename T>
    static std::vector<std::vector<std::string>> treeToVec(TreeInfo<T> *root);
    template<typename T>
    std::string generateTreeStr(TreeInfo<T> *root) const;
    //这个偏移能够控制输出的树的空白大小 最小为0
    static unsigned offset;
    //是否要输出null
    static bool withNull;
    static void setOffset(unsigned offset = 0);
    static void setWithNull(bool withNull = false);
private:
    //获取指定长度的空串
    std::string getBlank(int size) const;
    //获取在输入结点内容之前应该输出多个少空格
    std::string getPreBlank(const std::string &str,int width) const;
    //获取在输入结点内容之后应该输出多个少空格
    std::string getBakcBlank(int width,int outCount) const;
    //打印左儿子向父节点的 / 符号
    void printLeftToParentBranchBottom(int width,std:: ostringstream &out) const;
    //打印右儿子向父节点的 \ 符号
    void printRightToParentBranchBottom(int width,std:: ostringstream &out) const;
    //打印父节点到左儿子的______/
    void printLeftToParentBranchTop(int width,std:: ostringstream &out) const;
    //打印父节点到右儿子的\________
    void printRightToParentBranchTop(int width,std:: ostringstream &out) const;
    //修剪生成的字符串
    std::string trim(std::vector<std::string> &tree) const;
};

template<typename T>
void TreePrinter::printTree(TreeInfo<T> *root, std::ostream &out) {
    if (!root) return;
    out << treeStr(root);
}

template<typename T>
std::string TreePrinter::treeStr(TreeInfo<T> *root){
    TreePrinter printer;
    return printer.generateTreeStr(root);
}


template<typename T>
std::vector<std::vector<std::string>> TreePrinter::treeToVec(TreeInfo<T> *root){
    std::vector<std::vector<std::string>> tree;
    std::queue<TreeInfo<T>*> q;
    std::vector<std::string> row;
    if(root){
        q.push(root);
    }
    while(!q.empty()){
        int size = q.size();
        bool all_null = true;
        for(int i = 0; i != size; ++i){
            TreeInfo<T>* node = q.front();
            q.pop();
            row.emplace_back(node ? node->content() : "null");
            q.push(node ? node->getLeft() : nullptr);
            q.push(node ? node->getRight() : nullptr);
            if(all_null){
                all_null = (node == nullptr);
            }
        }
        tree.emplace_back(row);
        if(all_null)
        break;
        row.clear();
    }
    return tree;
}


template<typename T>
std::string TreePrinter::generateTreeStr(TreeInfo<T> *root) const{
    auto vec = treeToVec(root);
    std::vector<std::string> res;
    if(!withNull){
        vec.pop_back();
    }
    std::ostringstream pipe;
    int i, j, depth = vec.size();
    for (i = 0; i < depth; i++) {
        int w = (1 << (depth - i + offset));
        if (i > 0) {
            if (w - 3 > 0) {
                for (j = 0; j < 1 << i; j++) {
                    if ( (vec[i][j] != "null" || (withNull && vec[i-1][j/2] != "null") ) ) {
                        if (j % 2 == 0) {
                            printLeftToParentBranchTop(w, pipe);
                        }
                        else {
                            printRightToParentBranchTop(w, pipe);
                        }
                    }
                    else {
                        pipe << getBlank(2*w);
                    }
                }
                pipe<<std::endl;
                res.emplace_back(pipe.str());
                pipe.str("");
                for (j = 0; j < 1 << i; j++){
                    if(vec[i][j] != "null" || (withNull && vec[i-1][j/2] != "null")) {
                        if (j % 2 == 0) {
                            printLeftToParentBranchBottom(w, pipe);
                        }
                        else {
                            printRightToParentBranchBottom(w, pipe);
                        }
                    }
                    else{
                        pipe << getBlank(2*w);
                    }
                }
                pipe<<std::endl;
                res.emplace_back(pipe.str());
                pipe.str("");
            }
            else {
                for (j = 0; j < 1 << i - 1; j++) {
                    if(vec[i-1][j] != "null" && (withNull || vec[i][j * 2] != "null")) {
                        pipe << getBlank(w) << "/ " ;
                    }
                    else{
                        pipe << getBlank(w+2);
                    }
                    if(vec[i-1][j] != "null" && (withNull || vec[i][j*2 + 1] != "null")) {
                        pipe << "\\" << getBlank(w+1);
                    }
                    else{
                        pipe << getBlank(w+2);
                    }
                }
                pipe << std::endl;
                res.emplace_back(pipe.str());
                pipe.str("");
            }
        }
        for (j = 0; j < 1 << i; j++) {
            if(vec[i][j] != "null" || (withNull && vec[i-1][j/2] != "null")) {
                std::string pre = getPreBlank(vec[i][j], w);
                std::string back = getBakcBlank(w, pre.size() + vec[i][j].size());
                pipe << pre << vec[i][j] << back;
            }
            else{
                pipe << getBlank(2*w);
            }
        }
        pipe << std::endl;
        res.emplace_back(pipe.str());
        pipe.str("");
    }

    return trim(res);
}
#endif //TREEPRINTER_TREEPRINTER_H
