#include "../timeline.h"
using namespace std;
int main()
{
   
    cout<<"Standard example 1"<<endl;	
    Standard_Timeline t0 = Standard_Timeline(15, 25, ILLUM, 30, CONTINUOUS);
    t0.print();

    cout<<"Standard example 2"<<endl;

    Standard_Timeline t1 = Standard_Timeline(20, 31, WP, 40, INTERRUPTED);
    t1.print();

    cout<<"Non-Standard example 3"<<endl;
    std::vector<fireRange> frVec;
    frVec.push_back(fireRange{-2, 1}); // 1 - (-2) = 3 min interval
    //cout<<"gap"<<endl;               // 3 - 1 = 2 min interval
    frVec.push_back(fireRange{3, 5}); // 5 - 3 = 2 min interval

    NonStandard_Timeline nST = NonStandard_Timeline(40, 30, frVec, 30);
    nST.print();

}