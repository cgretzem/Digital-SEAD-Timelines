#include "Sexagesimal.h"
using namespace std;
int main()
{
    Sexagesimal s = Sexagesimal(23, 59, 31);
    cout  << s.print() << endl;
}