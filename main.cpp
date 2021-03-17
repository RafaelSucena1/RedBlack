#include <iostream>
#include <vector>
#include "RBT.h"

using namespace std;
int main() {

    RBT<int> tree = RBT<int>();
    vector<int> vect{ 10,16,0,11,6,5,8,7,4,1};
    for(int i : vect){

        tree.insert(i);

    }
    tree.print();
    if(tree.testRB()){
        cout << "tree OK on all counts" << endl;
    } else {
        cout << "tree FAILED!!!!" << endl;
    }
    return 0;
}
