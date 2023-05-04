#include "src/head/sort.h"
#include "src/head/tree.h"
#include "src/head/dp.h"
 
bool cmp_char(char a, char b) {
    return a < b;
}

void visit_char(char a) {
    cout<<"node:"<<a<<"\t";
}
int main()
{
    const char* a = "dacbe";
    vector<char> b;
    b.insert(b.end(), a, a + strlen(a));
    binary_tree<char> c;
    c.create_BST(b, cmp_char);
    c.traverse(1, visit_char);
    c.trans_BST_to_RBT(c.root);
    c.traverse(1, visit_char);
}