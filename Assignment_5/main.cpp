#include "BST.h"
#include "Student.h"
#include "Faculty.h"
#include "Person.h"
#include <iostream>
#include <string>
#include <locale>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define STUDENTFILENAME "students.txt"
#define FACULTYFILENAME "faculty.txt"

using namespace std;

BST<Student> *masterStudent = new BST<Student>(STUDENTFILENAME);
BST<Faculty> *masterFaculty = new BST<Faculty>(FACULTYFILENAME);
deque<int> dbAction;

int masterPrompt(){
	int prompt_selection;
	
	cout << "\r\nDatabase loaded, what would you like to do: " << endl;
	cout << " ------------------------------------------------------- " << endl;
	cout << "|1. New entry                                           |" << endl;
	cout << "|2. Search                                              |" << endl;
	cout << "|3. Delete entry                                        |" << endl;
	cout << "|4. Add mentor or mentee                                |" << endl;
	cout << "|5. Remove mentor or mentee                             |" << endl;
	cout << "|6. Edit entry                                          |" << endl;
	cout << "|7. Clear database                                      |" << endl;
	cout << "|8. Print entire database (could take several minutes)  |" << endl;
	cout << "|9. Roll back (stores last 5 states)                    |" << endl;
	cout << " ------------------------------------------------------- " << endl;
	
	cin >> prompt_selection;
	return prompt_selection;
}

int getID(string prompt){
	int response;
	
	cout << prompt << ": " << endl;
	cin >> response;
	return response;
}

string getString(string prompt){
	string response;
	
	cout << prompt << ": " << endl;
	cin >> response;
	return response;
}

double getGPA(string prompt){
	double response;
	
	cout << prompt << ": " << endl;
	cin >> response;
	return response;
}

Student findStudent(){
	int sid = getID("Please enter student's ID");

	Student *student = masterStudent->search(sid);
		if(student == NULL){
			cout << "ERROR: Student not on file.\r\n";
		}
		
		else{
			return *student;
		}
}

Faculty findFaculty(){
	int fid = getID("Please enter faculty member's ID");
	
	Faculty *faculty = masterFaculty->search(fid);
	if(faculty == NULL){
		cout << "ERROR: Member not on file.\r\n";
	}
	
	else{
		return *faculty;
	}
}

Faculty addFaculty(){
	string fname, ffirst, flast, fdep, ftitle;
	int fid, response;
	bool proceed = true;
	vector<int> advisees;
	
	ffirst = getString("\r\nPlease enter the faculty member's first name");
	flast = getString("Please enter faculty member's last name");
	fid = getID("Please enter faculty member's ID");
	fname = ffirst + "-" + flast;
	
	
	while(proceed){
		cout << "Facutly member's department: " << endl;
		cout << " ------------------- " << endl;
		cout << "|1. Mathematics     |" << endl;
		cout << "|2. Sciences        |" << endl;
		cout << "|3. Humanities      |" << endl;
		cout << "|4. Business		 |" << endl;
		cout << "|5. Liberal Arts    |" << endl;
		cout << " ------------------- " << endl;
		cin >> response;
			
		if(response == 1){
			fdep = "Mathematics";
			proceed = false;
		}
			
		else if(response == 2){
			fdep = "Science";
			proceed = false;
		}
			
		else if(response == 3){
			fdep = "Humanities";
			proceed = false;
		}
			
		else if(response == 4){
			fdep = "Business";
			proceed = false;
		}
		
		else if(response == 5){
			fdep = "Liberal Arts";
			proceed = false;
		}
			
		else{
			cout << "Invalid selection, please try again.";
		}
	}
	ftitle = getString("Title");
	
	Faculty f(advisees, fdep);
	f.setValues(fid, fname, ftitle);
	return f;
}

Student addStudent(){
	string sname, sfirst, slast, syear, smajor;
	int sid, temp, smentor, response;
	double sGPA;
	bool proceed = true;
	
	sfirst = getString("\r\nPlease enter student's first name");
	slast = getString("Please enter student's last name");	
	sid = getID("Student ID");
	sname = sfirst + "-" + slast;
		
	while(proceed){
		cout << "Student's current year: " << endl;
		cout << " ---------------- " << endl;
		cout << "|1. Freshman     |" << endl;
		cout << "|2. Sophmore     |" << endl;
		cout << "|3. Junior       |" << endl;
		cout << "|4. Senior       |" << endl;
		cout << " ---------------- " << endl;
		cin >> response;
			
		if(response == 1){
			syear = "Freshman";
			proceed = false;
		}
			
		else if(response == 2){
			syear = "Sophmore";
			proceed = false;
		}
			
		else if(response == 3){
			syear = "Junior";
			proceed = false;
		}
			
		else if(response == 4){
			syear = "Senior";
			proceed = false;
		}
			
		else{
			cout << "Invalid selection, please try again." << endl;
		}
	}		
	sGPA = getGPA("Please enter student's current GPA");
	smajor = getString("What is the student's intended major");
			
	Student s(smentor, sGPA, smajor);
	s.setValues(sid, sname, syear);
	s.assigned = 0;		
	return s;
}

int removeMember(string s){
	string selection = s;
	int remove;
	
	remove = getID("\r\nID of member to be removed");
	
	if(selection == "s"){
		masterStudent->snapshot();
		masterStudent->remove(remove);
		cout << "Member removed successfully!" << endl;
	}
	
	else{
		masterFaculty->snapshot();
		masterFaculty->remove(remove);
		cout << "Member removed successfully!" << endl;
	}
}

void removeAdvisor(){
	string response;
	int sid, fid;
	Student *student;
	Faculty *faculty;
	
	sid = getID("\r\nPlease enter student's ID");
	student = masterStudent->search(sid);
		
	if(student != NULL && student->assigned == 1){
		masterStudent->snapshot();
		masterFaculty->snapshot();
		
		faculty = masterFaculty->search(student->mentor);
		faculty->mentee.erase(remove(faculty->mentee.begin(), faculty->mentee.end(), sid), faculty->mentee.end());
			
		student->mentor = 0;
		student->assigned = 0;
			
		cout << "SUCCESS: mentor removed." << endl;
	}
		
	else{
		cout << "ERROR: Student not on file." << endl;
	}
}

void addAdvisor(string s){
	string selection = s;
	string response;
	int sid, fid;
	
	if(selection == "s"){
		sid = getID("\r\nPlease enter student's ID");
		Student *student = masterStudent->search(sid);
		
		if(student != NULL){
			fid = getID("Please enter mentor's ID");
			Faculty *faculty = masterFaculty->search(fid);
		
			if(faculty == NULL){
				cout << "WARNING: Member ID " + to_string(fid) + " not on file, add anyway? [y/n]" << endl;
				cin >> response;
				transform(response.begin(), response.end(), response.begin(), ::tolower);
			
				if(response == "y"){
					masterStudent->snapshot();
					
					student->mentor = fid;
					student->assigned = 1;
				
					cout << "OPERATION SUCCESS: please ensure to update faculty database appropriately." << endl;
				}
			
				else{
					addAdvisor("s");
				}
			}
		
			else{
				masterStudent->snapshot();
				masterFaculty->snapshot();
				
				cout << "Member found: " + faculty->name + "\r\nAdding..." << endl;
			
				student->mentor = fid;
				student->assigned = true;
				faculty->mentee.push_back(student->identification);
			
				cout << "Done." << endl;
			}
		}
		
		else{
			cout << "ERROR: student not on file.\r\n";
		}
	}	
	
	else if(selection == "f"){
		fid = getID("Please enter faculty member's ID");
		Faculty *faculty = masterFaculty->search(fid);
		if(faculty != NULL){
			sid = getID("Please enter mentee's ID");
			Student *student = masterStudent->search(sid);
			
			if(student != NULL && student->assigned == 1){
				cout << "OPERATION FAILED: Student already assigned." << endl;
			}
			
			if(student == NULL){
				cout << "WARNING: Student ID " + to_string(sid) + " not on file, add anyway? [y/n]" << endl;
				cin >> response;
				transform(response.begin(), response.end(), response.begin(), ::tolower);
			
				if(response == "y"){
					masterFaculty->snapshot();
					
					faculty->mentee.push_back(sid);			
					cout << "OPERATION SUCCESS: please ensure to update student database appropriately." << endl;
				}
			
				else{
					addAdvisor("f");
				}
			}
			
			else{
				masterFaculty->snapshot();
				masterStudent->snapshot();
				
				cout << "Member found: " + student->name + "\r\nAdding..." << endl;			
				faculty->mentee.push_back(sid);
				student->mentor = fid;
				cout << "Done." << endl;
			}
		}
		
		else{
			cout << "ERROR: member not on file.\r\n";
		}
	}
		
	else{
		cout << "OPERATION FAILED: Incorrect value entered, please try again." << endl;
	}
}

void editEntry(string s){
	string selection = s;
	string sfirst, slast, ffirst, flast, response;
	int sid, fid, option;
	bool next = true;
	
	if(selection == "s"){
		while(next){
			sid = getID("Please enter student's ID");
			Student *student = masterStudent->search(sid);
		
			if(student != NULL){
				cout << "Student found. What would you like to do: " << endl;
				cout << " -------------------- " << endl;
				cout << "|1. Edit name        |" << endl;
				cout << "|2. Edit ID          |" << endl;
				cout << "|3. Edit year        |" << endl;
				cout << "|4. Edit GPA         |" << endl;
				cout << "|5. Edit major       |" << endl;
				cout << " -------------------- " << endl;
				cin >> option;
				
				masterStudent->snapshot();
				
				switch(option){
					case 1:
						sfirst = getString("Please enter student's updated first name");
						slast = getString("Please enter student's updated last name");
						student->name = sfirst + "-" + slast;
						break;
						
					case 2:
						student->identification = getID("Please enter student's updated ID");
						break;
					
					case 3:
						student->level = getString("Please enter student's updated year");
						break;
						
					case 4:
						student->GPA = getGPA("Please enter updated GPA");
						break;
						
					case 5:
						student->major = getString("Please enter student's updated major");
						break;
				}
				cout << "Would you like to edit another student? [y/n]" << endl;
				cin >> response;
				
				transform(response.begin(), response.end(), response.begin(), ::tolower);
				
				if(response == "n"){
					next = false;
				}
				
				else if(response == "y"){
					next = true;
				}
				
				else{
					cout << "ERROR: invalid selection, aborting..." << endl;
					next = false;
				}
			}
			
			else{
				"ERROR: Member not on file.\r\n";
			}
		}
	}
	
	else{
		while(next){
			fid = getID("Please enter faculty member's ID");
			Faculty *faculty = masterFaculty->search(fid);
		
			if(faculty != NULL){
				cout << "Member found. What would you like to do: " << endl;
				cout << " --------------------- " << endl;
				cout << "|1. Edit name         |" << endl;
				cout << "|2. Edit ID           |" << endl;
				cout << "|3. Edit title        |" << endl;
				cout << "|4. Edit department   |" << endl;
				cout << " --------------------- " << endl;
				cin >> option;
				
				masterFaculty->snapshot();
				
				switch(option){
					case 1:
						ffirst = getString("Please enter faculty member's updated first name");
						flast = getString("Please enter faculty member's last name");
						faculty->name = ffirst + " " + flast;
						break;
						
					case 2:
						faculty->identification = getID("Please enter faculty member's updated ID");
						break;
					
					case 3:
						faculty->level = getString("Please enter faculty member's updated title");
						break;
						
					case 4:
						faculty->department = getString("Please enter updated department");
						break;
				}
				cout << "Would you like to edit another faculty member? [y/n]" << endl;
				cin >> response;
				
				transform(response.begin(), response.end(), response.begin(), ::tolower);
				
				if(response == "n"){
					next = false;
				}
				
				else if(response == "y"){
					next = true;
				}
				
				else{
					cout << "ERROR: invalid selection, aborting..." << endl;
					next = false;
				}
			}
			
			else{
				"ERROR: Member not on file.\r\n";
			}
		}
	}
}

void commitDatabases(){
	masterStudent->serialize();
	masterFaculty->serialize();
}

void initDatabases(){
	masterStudent->deserialize();
	masterFaculty->deserialize();
}

bool quitProgram(){	
	string pquit;
	bool valid = true;
	
	while(valid){
		cout << "\r\nType 'quit' to exit system, 'c' to continue" << endl;
		cin >> pquit;
	
		if(pquit == "quit"){
			commitDatabases();
			cout << "Databases' states saved. Good bye." << endl;
			valid = false;
			return true;
		}
	
		else if(pquit == "c"){
			valid = false;
			cout << ".....Loading\r\n";
			cout << string(50, '\n');
			return false;
		}
	
		else{
			cout << "Invalid entry." << endl;
		}
	}
}

void rollback(string s){
	string selection = s;
	string response, both;
	
	if(selection == "s"){
		cout << "WARNING: are you sure you want to restore to previous state? [y/n]\r\n";
		cin >> response;
		
		transform(response.begin(), response.end(), response.begin(), ::tolower);
	
		if(response == "y"){
			cout << "WARNING: if reverting back from the addition or removal of a" << endl;
			cout << "         mentor or mentee, you may need to rollback both data-" << endl;
			cout << "         bases. Would you like to rollback both databases now?" << endl;
			cout << "         [y/n]\r\n" << endl;
			cin >> both;
			
			transform(both.begin(), both.end(), both.begin(), ::tolower);
		
			if(both == "y"){
				masterStudent->rollback();
				masterFaculty->rollback();
			}
		
			else if(both == "n"){
				masterStudent->rollback();
			}
		
			else{
				cout << "OPERATION FAILED: invalid selection." << endl;
			}
		}
	
		else{
			cout << "No action taken..." << endl;
		}
	}
	
	else{
		cout << "WARNING: are you sure you want to restore to previous state? [y/n]\r\n";
		cin >> response;
		
		transform(response.begin(), response.end(), response.begin(), ::tolower);
	
		if(response == "y"){
			cout << "WARNING: if reverting back from the addition or removal of a" << endl;
			cout << "         mentor or mentee, you may need to rollback both data-" << endl;
			cout << "         bases. Would you like to rollback both databases now?" << endl;
			cout << "         [y/n]\r\n" << endl;
			cin >> both;
			
			transform(both.begin(), both.end(), both.begin(), ::tolower);
		
			if(both == "y"){
				masterStudent->rollback();
				masterFaculty->rollback();
			}
		
			else if(both == "n"){
				masterFaculty->rollback();
			}
		
			else{
				cout << "OPERATION FAILED: invalid selection." << endl;
			}
		}
	
		else{
			cout << "No action taken..." << endl;
		}
	}
}

int main(){
	Student new_student, retrieve_student;
	Faculty new_faculty, retrieve_faculty;
	string selection, response;
	int prompt_select, to_remove;
	bool quit = false;
	bool next = true;
	
	initDatabases();

	while(quit == false){
		next = true;
		cout << "Which database would you like to access [Student = s, Faculty = f]: " << endl;
		cin >> selection;
		transform(selection.begin(), selection.end(), selection.begin(), ::tolower);
	
		prompt_select = masterPrompt();
	
		switch(prompt_select){
			case 1:
				while(next){
					if(selection == "s"){
						new_student = addStudent();
						masterStudent->snapshot();
						masterStudent->insert(new_student);
						
						cout << "Would you like to enter another student? [y/n]" << endl;
						cin >> response;
						transform(response.begin(), response.end(), response.begin(), ::tolower);
						
						if(response == "y"){
							next = true;
						}
						
						else if(response == "n"){
							next = false;
						}
						
						else{
							cout << "ERROR: Invalid entry, action aborted" << endl;
							next = false;
						}
					}
			
					else{
						new_faculty = addFaculty();
						masterFaculty->snapshot();
						masterFaculty->insert(new_faculty);
						
						cout << "Would you like to enter another faculty member? [y/n]" << endl;
						cin >> response;
						transform(response.begin(), response.end(), response.begin(), ::tolower);
						
						if(response == "y"){
							next = true;
						}
						
						else if(response == "n"){
							next = false;
						}
						
						else{
							cout << "ERROR: Invalid entry, action aborted" << endl;
							next = false;
						}
					}
				}
				
				if(quitProgram()){
					quit = true;
				}
				break;
			
			case 2:
				if(selection == "s"){
					retrieve_student = findStudent();
					retrieve_student.display();
				}
			
				else{
					retrieve_faculty = findFaculty();
					retrieve_faculty.display();
				}
				
				if(quitProgram()){
					quit = true;
				}
				break;
			
			case 3:
				removeMember(selection);
				
				if(quitProgram()){
					quit = true;
				}
				break;
				
			case 4:
				addAdvisor(selection);
				
				if(quitProgram()){
					quit = true;
				}
				break;
				
			case 5:
				removeAdvisor();
				break;
				
			case 6:
				editEntry(selection);
				
				if(quitProgram()){
					quit = true;
				}
				break;
			
			case 7:
				if(selection == "s"){
					masterStudent->deleteTree(masterStudent->root);
				}
				
				else{
					masterFaculty->deleteTree(masterFaculty->root);
				}
				
				if(quitProgram()){
					quit = true;
				}
				break;
				
			case 8:
				cout << "This feature not available at this time...\r\n";
				
				if(quitProgram()){
					quit = true;
				}
				break;
			
			case 9:
				rollback(selection);
				
				if(quitProgram()){
					quit = true;
				}
				break;
				
		}
	
	}
}