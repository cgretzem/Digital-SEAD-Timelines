#include "../Sexagesimal.h"
using namespace std;
int main()
{
    //test 1 -- printing format
    Sexagesimal s = Sexagesimal(24, 59, 31);
    cout << "Test 1: " << s << endl;
    //test 2 -- basic addition
    Sexagesimal t1 = s + Sexagesimal(20, 20, 11);
    cout << "Test 2: " << t1 << endl;
    //test 3 -- basic subtraction
    Sexagesimal t2 = s - Sexagesimal(2, 20, 11);
    cout << "Test 3: " << t2 << endl;
    //test 4 -- addition going over 2400
    Sexagesimal t3 = s + Sexagesimal(5, 50, 50);
    cout << "Test 4: " << t3 << endl;
    //tet 5 -- addition  going under 0000
    Sexagesimal t4 = s - Sexagesimal(20, 50, 50);
    cout << "Test 5: " << t4 << endl;
    //test 6 -- addition using int overload 
}