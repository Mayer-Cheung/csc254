/////////////////////////////////////////////////////////////////////////////
// foo2.cpp, test file for CS254, assignment 5
/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdlib.h>
#include "tombstones.h"

using namespace std;

void Error(const char *text)
{
    cout << "ERROR: " << text << endl;
    exit(-1);
}

int main(int argc, char **argv)
{
    Pointer<int> foo;
    foo = new int(12);
    Pointer<int> bar(foo);

    if (bar == 0)
	Error("Bar should not be null!");
    if (*bar != 12)
	Error("Bar got the wrong value!");
    if (foo != bar)
	Error("Foo and bar are NOT distinct pointers!");
    if (*foo != *bar)
	Error("Foo and bar should have the same value here!");
    *foo = 15;
    if (*bar != 15)
	Error("Bar should still match foo!");

    free(foo);
    free(bar);
    Error("Attempt to double-delete pointer not flagged!");

    return 0;
}
