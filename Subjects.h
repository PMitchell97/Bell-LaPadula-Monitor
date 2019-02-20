#include <iostream> 


using namespace std; 

class Subjects
{
	private:
	string name;
	int temp;
	int SecLevelSubj;
	
	public:
	Subjects(string s, int v);
	void SetSubj(string name1, int SecLevelSubj1);
	void SetSubjTemp(int temp1);

	int GetSubjSec();
	int GetSubjTemp();
	string GetSubjName();
	
};