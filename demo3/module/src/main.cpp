#include <iostream>
#include <string>
#include "Person.h"
using namespace std;

int main()
{
    Person p("颜年华", "男", 27);
    Person p1;
    p1 = (move(p));
    cout << "p:--------------" << endl;
    p.show();
    cout << "p1:-------------" << endl;
    p1.show();
    return 0;
}