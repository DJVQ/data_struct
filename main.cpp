#include "src/head/sort.h"
#include "src/head/tree.h"

void visit_char(char data) {
    cout<<"node: "<<data<<"\t\t";
}

int main(){
    const char a[] = "hello";
    vector<char> b(a, a + strlen(a));
    binary_tree<char> c;
    c.create_note_layer(b.begin(), b.end());
    c.traverse(0, visit_char);
    // c.traverse(1, visit);
    // c.traverse(2, visit);
    // c.traverse(3, visit);
    return 0;
}