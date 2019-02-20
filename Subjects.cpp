#include "Subjects.h"
#include <iostream>


using namespace std;

Subjects::Subjects(string s, int v)
{
	name = s;
	SecLevelSubj = v;
	temp = 0;
}
void Subjects::SetSubj(string name1, int SecLevelSubj1)
{
	name = name1;
	SecLevelSubj = SecLevelSubj1;
}
void Subjects::SetSubjTemp(int temp1)
{
	temp = temp1;
}


int Subjects::GetSubjSec()
{
	//cout << "Also returning: " << endl;
	return SecLevelSubj;
}
int Subjects::GetSubjTemp()
{
	return temp;
}
string Subjects::GetSubjName()
{
	//cout << "Returning: " << endl;
	return name;
}
