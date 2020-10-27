
#include "TreePrinter.h"


std::string TreePrinter::getPreBlank(const std::string &str, int width) const{
    int size = str.size();
    int len = (size  % 2) ? (size+1)/2 : size/2;
    return width - len ? std::string(width - len,' ') : "";
}

std::string TreePrinter::getBakcBlank(int width, int outCount) const{
    return 2 * width - outCount ? std::string(2 * width - outCount,' ') : "";
}

void TreePrinter::printLeftToParentBranchBottom(int width,std:: ostringstream &out) const{
    out << std::string(width,' ') << "/" << std::string(width - 1,' ');
}

void TreePrinter::printRightToParentBranchBottom(int width,std:: ostringstream &out) const{
    out << std::string(width - 2,' ') << "\\" << std::string(width + 1,' ');
}

void TreePrinter::printLeftToParentBranchTop(int width,std:: ostringstream &out) const{
    out << std::string(width + 1,' ') << std::string(width - 3,'_') << "/ ";
}

void TreePrinter::printRightToParentBranchTop(int width,std:: ostringstream &out) const{
    out << "\\" << std::string(width - 3,'_') << std::string(width + 2,' ');
}

std::string TreePrinter::getBlank(int size) const{
    return std::string(size,' ');
}

unsigned  TreePrinter::offset = 0;

bool TreePrinter::withNull = false;

void TreePrinter::setOffset(unsigned  offset) {
    TreePrinter::offset = offset;
}

void TreePrinter::setWithNull(bool withNull) {
    TreePrinter::withNull = withNull;
}

std::string TreePrinter::trim(std::vector<std::string> &tree) const{
    std::string res;
    if(!tree.size()) return res;
    for(int i = 0; i != tree.back().size(); ++i){
        for(int j = 0; j != tree.size(); ++j){
            if(tree[j][i] != ' '){
                for(int k = 0; k != tree.size();++k){
                    res += tree[k].substr(i);
                }
                return res;
            }
        }
    }
    return res;
}

