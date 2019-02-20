#include <iostream> 


using namespace std; 

class Objects
{
	private:
	string name;
	int integervalue;
	int SecLevelObj;
	
	public:
	Objects(string s, int v);
	void SetObj(string name1, int SecLevelObj1);
	void SetObjVal(int value1);
	int GetObjSec();
	int GetObjValue();
	string GetObjName();	
};