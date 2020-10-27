/**
 * @author VMJWV
 * @Reference Milo Yip https://zhuanlan.zhihu.com/p/38013510
 * @return
 */
#include "TreeInfo.h"
#include "TreePrinter.h"
#include <random>
#include <ctime>

//继承TreeInfo 将实例化类型写为你的树名字 getLeft getRight content即可
struct BinaryTree : public TreeInfo<BinaryTree>{
    int val;
    BinaryTree *left;
    BinaryTree *right;
    //左子树是谁
    BinaryTree *getLeft() override {
        return left;
    }
    //右子树是谁
    BinaryTree *getRight() override {
        return right;
    }
    //每个结点要输入什么内容
    std::string content() override {
        return std::to_string(val);
    }
};


void insert(BinaryTree *&root,int value){
    if(!root){
        root = new BinaryTree();
        root->val = value;
    }
    BinaryTree *temp = root;
    BinaryTree *pre = nullptr;
    while(temp){
        pre = temp;
        if(temp->val > value){
            temp = temp->left;
        }
        else if(temp->val < value){
            temp = temp->right;
        }
        else{
            return;
        }
    }
    temp = new BinaryTree();
    temp->val = value;
    pre->val > value ? pre->left = temp : pre->right = temp;
}

void traversal(BinaryTree *root){
    if(!root) return;
    traversal(root->left);
    std::cout<<root->val<<" ";
    traversal(root->right);
}
int main() {
    using namespace std;
    //TreePinter 两个参数可选
    //1.offset 这个偏移量决定了生成树的图形大小  0 或者 1 即可 为1的话可能高度为5的时候就挂了
    //2.withNull 打印的时候 是否要把Null结点也打印出来
    BinaryTree *root = nullptr;
    //使用演示 只要你的结构体继承了TreeInfo实现了对应的方法 你就可以通过传递根结点Printer来打印树
    //当发现输出的内容贴的很紧密的时候 请调整offset为1
    //当用类实现树的数据结构的时候 还是只需要让节点类继承TreeInfo 然后想办法传递root结点即可
    default_random_engine e(time(0));
    uniform_int_distribution<int> u(0,50);
    int data[] = {8,4,2,6,1,3,5,7,12,10,14,13,15,9,11};
    for(int i = 0; i != sizeof(data)/sizeof(int); ++i){
        int value = u(e);
        cout<<"add Node ("<<data[i]<<")"<<endl;
        insert(root,data[i]);
        cout<<"Traversal"<<endl;
        traversal(root);
        cout<<endl;
        TreePrinter::printTree(root);
    }
    TreePrinter::setWithNull(true);
    //printerTree是一个默认参数方法 还可以传递ostream的子类选择输出的流
    TreePrinter::printTree(root,cout);
    //当树的一行 大于了屏幕的大小的时候 输出就会乱套了
    //在offset为0的情况下 一般可以输出一个5层的满树 offset为1 基本上只能输出4层的满树了
    TreePrinter::setOffset(1);
    cout<<"offset increasing"<<endl;
    //也可以通过treeStr来获取到树形的字符串
    cout<<TreePrinter::treeStr(root);//这里输出的就是offset为1在我电脑上的最大形状了 5层
    TreePrinter::setWithNull(false);
    TreePrinter::setOffset(0);
    TreePrinter::printTree(root);
    TreePrinter::setWithNull(true);
    TreePrinter::printTree(root);//offset为0的时候 最多可以支持6(不带null)层的满树 我这里是5层带null 即6层
}
