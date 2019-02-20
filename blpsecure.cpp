/*
	Preston Mitchell
	11091132
	Computer Security - Hoffman - 4550
	10/15/18
	
	This program models the Bell-LaPadula model of security
*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include "Subjects.h"
#include "Objects.h"


using namespace std;







struct InstructionSet
{
	bool addsubj;
	bool addobj;
	bool read;
	bool write;
	bool bad;
	string subj;
	string obj;
	int value;
	int security;
	
	InstructionSet()
	{
		addsubj = false;
		addobj = false;
		read = false;
		write = false;
		bad = false;
		value = 0;
		security = 0;
		
	}
	
};



class ReferenceMonitor
{
	private:
	vector<Subjects> subjlist;
	vector<string> subjnames;
	vector<Objects> objlist;
	vector<string> objnames;
	
	int i, k;
	
	
	public:
	ReferenceMonitor()
	{
		i = 0;
		k = 0;
	}
	
	void addSubject(InstructionSet instruct)
	{
		
		Subjects newsubj(instruct.subj, instruct.security);
		subjlist.push_back(newsubj);
		subjnames.push_back(instruct.subj);
		
		cout << "Subject Added: addsub " << instruct.subj << instruct.security << endl;
	
	}
	void addObject(InstructionSet instruct)
	{

		Objects newobjects(instruct.obj, instruct.security);
		objlist.push_back(newobjects);
		objnames.push_back(instruct.obj);
		
		cout << "Object Added: addobj " << instruct.obj << instruct.security << endl;

		
	}
	void executeRead(InstructionSet instruct)
	{

		//No read up. Only read same level or lower
		
		//cout << "Check if this is emtpy " << instruct.subj << endl;
		//cout << "Check if this obj is empty " << instruct.obj << endl;
		if(!instruct.subj.empty() || !instruct.obj.empty())
		{
			vector<string>::iterator it = find(subjnames.begin(), subjnames.end(), instruct.subj);
			int index = distance(subjnames.begin(), it);
			//cout << "Index of subject name " << instruct.subj << " is: " << index << endl;
			
			vector<string>::iterator it1 = find(objnames.begin(), objnames.end(), instruct.obj);
			int index1 = distance(objnames.begin(), it1);
			//cout << "The Index of object name " << instruct.obj << " is: " << index1 << endl;
			
			if(find(objnames.begin(), objnames.end(), instruct.obj) != objnames.end())
			{			
				if(subjlist[index].GetSubjSec() >= objlist[index1].GetObjSec()) //*Jazz hands* SECURITY
				{
					//cout << "------------------------" << endl;
					//cout << "Testing: " << objlist[index1].GetObjValue() << endl;
					subjlist[index].SetSubjTemp(objlist[index1].GetObjValue()); //(instruct.value);
					cout << "Access Granted: " << instruct.subj << " reads " << instruct.obj << endl;
					
				}
				else
				{
					cout << "Access Denied" << endl;
				}
			}
			else
			{
				cout << "Bad Instruction" << endl;
			}
		}
		
	}
	void executeWrite(InstructionSet instruct)
	{

		//*security property. We cannot write down in security levels. Only same or higher.
		
		vector<string>::iterator it = find(subjnames.begin(), subjnames.end(), instruct.subj);
		int index = distance(subjnames.begin(), it);
		//cout << "Index of subject name " << instruct.subj << " is: " << index << endl;
		
		vector<string>::iterator it1 = find(objnames.begin(), objnames.end(), instruct.obj);
		int index1 = distance(objnames.begin(), it1);
		//cout << "Index of object name " << instruct.obj << " is: " << index1 << endl;
		
		//We need to add security here. Just going to test if write works correctly.
		
		if(instruct.value != 0)
		{
			if(find(objnames.begin(), objnames.end(), instruct.obj) != objnames.end())
			{
				if(subjlist[index].GetSubjSec() <= objlist[index1].GetObjSec()) //*Jazz hands* SECURITY
				{
					objlist[index1].SetObjVal(instruct.value);
					cout << "Access Granted: " << instruct.subj << " writes value " << instruct.value << " to " << instruct.obj << endl;
				}
				else
				{
					cout << "Access Denied" << endl;
				}
			}
		}
	
	
	}
	
	
	void printVect()
	{
		cout << "|Subjects    Temp|" << endl;
		for(i = 0; i < subjlist.size(); i++)
		{
			//cout << "Subject #" << i +1 << endl;
			
			cout << "|" << subjlist[i].GetSubjName();
			//cout << "Subject Security Level: " << subjlist[i].GetSubjSec() << endl;
			cout << "       " << subjlist[i].GetSubjTemp() << "|" << endl;
		}
		cout << "|Objects    Value|" << endl;
		for(k = 0; k < objlist.size(); k++)
		{
			//cout << "Object #" << k +1 << endl;
			cout << "|" << objlist[k].GetObjName();
			//cout << "Object Security Level: " << objlist[k].GetObjSec() << endl;
			cout << "       " << objlist[k].GetObjValue() << "|" << endl;
			
		}
		
	}
	
};



int main(int argc, char *argv[])
{
	
	InstructionSet instruct;
	ReferenceMonitor reference;
	string file = argv[1];
	ifstream instruction(file.c_str());
	int counter;
	int printcounter = 0;
	string line;
	vector<string> tester;
	while (getline(instruction, line)) //gets one line from the input file
    {
		stringstream ss(line); 
		
		counter = 0;
		while(getline(ss, line, ' ')) //gets each word seperated by whitespace for the line we took
		{
			
			//tester.push_back(line);
			//line 1 will be out commands. 
			//line 2 is going to be a sub or obj name
			//line 3 is lots of different stuff 
			//line 4 is going to be only for the write commands
			//implement a counter. When counter = 0, get our command. When counter = 1, get the name of the subject or object. etc
			//Should I put the command in a string array? 
			if(counter == 0)
			{
				//cout << "This is line: " << line << endl;
				/*if(line != "addsub" || line != "addobj" || line != "read" || line != "write")
				{
					cout << "Bad Input" << endl;
					break;
				}*/
				if(line == "addsub")
				{
					instruct.addsubj = true;
				}
				else if(line == "addobj")
				{
					instruct.addobj = true;
				}
				else if(line == "read")
				{
					instruct.read = true;
				}
				else if(line == "write")
				{
					instruct.write = true;
				} //GET BAD INPUTS WORKING
				else
				{
					cout << "Bad input" << endl;
					instruct.bad = true;
					printcounter++;
					break;
				}
				
				
				
				//cout << "Testing 0" << endl;
				
				//If line = addsub, then check off the addsub command in the struct
				//if line = one of the others, do that for them. ez.
			}	
			if(counter == 1)
			{
				//cout << "Testing 1" << endl;
				if(instruct.addsubj == 1 || instruct.read == 1 || instruct.write == 1) //then add line to subj in the struct. Otherwise add it to obj
				{
					instruct.subj = line;
				}
				else if(instruct.addobj == 1)
				{
					instruct.obj = line;
				}
				else
				{
					cout << "Bad input" << endl;
					instruct.bad = true;
					printcounter++;
					break;
				}
			}	
			if(counter == 2)
			{
				if(line == "LOW" || line == "low")
				{
					instruct.security = 1;
				}
				else if(line == "MED" || line == "med" || line == "MEDIUM" || line == "medium")
				{
					instruct.security = 2;
				}
				else if(line == "HIGH" || line == "high")
				{
					instruct.security = 3;
				}
				
				
				else if(instruct.read == 1 || instruct.write == 1)
				{
					//cout << "Line testing: " << line << endl;
					instruct.obj = line;
				}
				else
				{
					//cout << "TESTING TESTING TESITNG ITNESTINSJDKLAFSDFAKLSJD" << endl;
					
					cout << "Bad input" << endl;
					instruct.bad = true;
					printcounter++;
					break;
				}
				
				//cout << "Testing 2" << endl;
				//if addsub or addobj then add line to security level otherwise read and write is object name

			}	
			if(counter == 3)
			{
				//cout << "Testing 3" << endl; 
				//this one is only for writes. Its our value.
				
				if(instruct.write == 1)
				{
					try{ instruct.value = stoi(line); }
					catch(std::invalid_argument& e)
					{
						cout << "ERROR with command" << endl;
					}
				}
				else
				{
					cout << "Bad input" << endl;
					instruct.bad = true;
					printcounter++;
					break;
				}
			}	
			if(counter == 4)
			{
				cout << "Bad instruction" << endl;
				instruct.bad = true;
				printcounter++;
				break;
			}
				
				
			counter++;
		}
		
		/*cout << "bool addsubj;" << instruct.addsubj << endl;
		cout << "bool addobj;" << instruct.addobj << endl;
		cout << "read;" << instruct.read << endl;
		cout << "write;" << instruct.write << endl;
		cout << "string subj;" << instruct.subj << endl;
		cout << "string obj;" << instruct.obj << endl;
		cout << "security;" << instruct.security << endl;
*/
		if(instruct.bad == 0)
		{
			if(instruct.addsubj == 1)
			{
				reference.addSubject(instruct);
				printcounter++;
			}
			if(instruct.addobj == 1)
			{
				reference.addObject(instruct);
				printcounter++;
			}
			if(instruct.read == 1)
			{
				reference.executeRead(instruct);
				printcounter++;
			}
			if(instruct.write == 1)
			{
				reference.executeWrite(instruct);
				printcounter++;
			}
		}
		else
		{
			instruct = InstructionSet();
		}
			
		if(printcounter == 10)
		{
			printcounter = 0;
			reference.printVect();
		}
	
		
		//Getting to right here, we should have a full struct that has all the commands and subject/obj names w/e. 
		//So for here, we need to send the struct to ref monitor to get it updated, then we need to 0 out the struct. 
		//cout << "We've hit whitespace bois" << endl;
		
		instruct = InstructionSet(); //This resets our struct so we can get the next line
    }
	
	
	cout << "Final State: " << endl;
	reference.printVect();
	
}
