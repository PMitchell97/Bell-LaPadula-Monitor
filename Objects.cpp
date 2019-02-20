#include "Objects.h"
#include <iostream>


using namespace std;



Objects::Objects(string s, int v)
{
	name = s;
	SecLevelObj = v;
	integervalue = 0;
}
void Objects::SetObj(string name1, int SecLevelObj1)
{
	name = name1;
	SecLevelObj = SecLevelObj1;
}
void Objects::SetObjVal(int value1)
{
	integervalue = value1;
}

int Objects::GetObjSec()
{
	//cout << "Also returning: " << endl;
	return SecLevelObj;
}
int Objects::GetObjValue()
{
	return integervalue;
}
string Objects::GetObjName()
{
	//cout << "Returning: " << endl;
	return name;
}



	