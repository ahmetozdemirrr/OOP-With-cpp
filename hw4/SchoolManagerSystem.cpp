#include <iostream>
#include <vector>
#include "SchoolManagerSystem.h"
#include "Course.h"
#include "Student.h"

using namespace std;

namespace PA4
{
	SchoolManagerSystem :: SchoolManagerSystem()
	{
		courseLS = nullptr;
		studentLS = nullptr;
	}

	SchoolManagerSystem :: SchoolManagerSystem(Course * comCourse, Student * comStudent)
	{
		for (int i = 0; i < numCourses; ++i)
		{
			courseLS[i] = comCourse[i];
		}

		for (int i = 0; i < numStudents; ++i)
		{
			studentLS[i] = comStudent[i];
		}
	}

	void SchoolManagerSystem :: mainMenu()
	{	
		int selection;

		cout << "Main_menu" << endl << "0 exit" << endl << "1 student" << endl << "2 course" << endl
		     << "3 list_all_students" << endl << "4 list_all_courses" << endl;

		cin >> selection;

		if (selection == 0)
		{
			cout << "Program is finished." << endl;
			exit(1);
		}

		else if (selection == 1)
		{
			studentMenu();
		}

		else if (selection == 2)
		{
			courseMenu();
		}

		else if (selection == 3)
		{
			list_all_students();
		}

		else if (selection == 4)
		{
			list_all_courses();
		}

		else
		{
			cout << "Invalid value for selection." << endl;
			exit(1);
		}
	}

	void SchoolManagerSystem :: studentMenu()
	{
		int selection;

		cout << "0 up" << endl << "1 add_student" << endl << "2 select_student" << endl;
		cin >> selection;

		if (selection == 0)
		{
			mainMenu();
		}

		else if (selection == 1)
		{
			add_student();
		}

		else if (selection == 2)
		{
			select_student();
		}

		else
		{
			cout << "Invalid value for selection." << endl;
			exit(1);
		}
	}

	void SchoolManagerSystem :: add_student()
	{
	    string input;
	    getline(cin, input);

	    string addName = input.substr(0, input.find_last_of(" "));
	    int addId = stoi(input.substr(input.find_last_of(" ") + 1));

	    Student newStudent(addName, addId);

	    Student * newStudentList = new Student[numStudents + 1];

	    for (int i = 0; i < numStudents; i++) 
	    {
	        newStudentList[i] = studentLS[i];
	    }
	    newStudentList[numStudents] = newStudent;

	    delete [] studentLS;

	    numStudents++;

	    studentLS = new Student[numStudents];

	    for (int i = 0; i < numStudents; i++) 
	    {
	        studentLS[i] = newStudentList[i];
	    }	    
	    delete [] newStudentList;
	}

	void SchoolManagerSystem :: select_student()
	{
		cout << "First select student (Enter name and ID): " << endl;

		string input;
	    getline(cin, input);

	    string selectName = input.substr(0, input.find_last_of(" "));
	    int selectID = stoi(input.substr(input.find_last_of(" ") + 1));

	    Student object(selectName,selectID);

	    int selection;

		cout << "0 up" << endl << "1 delete_student" << endl;
		cin >> selection;

		if (selection == 0)
		{
			mainMenu();
		}

		else if (selection == 1)
		{
			delete_student(object);
			studentMenu();
		}

		else if (selection == 3)
		{
			add_selected_student_to_a_course(object);
		}

		else if (selection == 4)
		{
			drop_selected_student_from_a_course(object);
		}

		else
		{
			cout << "Invalid value for selection." << endl;
			exit(1);
		}
	}

	void SchoolManagerSystem :: delete_student(Student & selectedStudent) 
	{
		int index = -1;
		int j = 0;

		for (int i = 0; i < numStudents; ++i)
		{
			if (studentLS[i].getName() == selectedStudent.getName() && studentLS[i].getID() == selectedStudent.getID())
			{
				index = i;
			}
		}

		if (index != -1)
		{
			Student * temp = new Student[numStudents - 1];

			for (int i = 0; i < index; ++i)
			{
				if (i == index)
				{
					continue;
				}
				temp[j] = studentLS[i];
				j++;
			}
			delete studentLS;
			studentLS = temp;
			delete [] temp;
		}

		else
		{
			cerr <<	"Student to be deleted not found";
			exit(1);
		}
	}

	void SchoolManagerSystem :: add_selected_student_to_a_course(Student& selectedStudent)
	{
		cout << "Enter course name and code: ";

		string input;
	    getline(cin, input);

	    string courseName = input.substr(0, input.find_last_of(" "));
	    int courseCode = stoi(input.substr(input.find_last_of(" ") + 1));

	    Course newCourse(courseName, courseCode);

	    selectedStudent.setCourse(newCourse.getName(),newCourse.getCode());
	}

	void SchoolManagerSystem::drop_selected_student_from_a_course(Student& selectedStudent)
	{
	    cout << "Enter course name and code: ";

		string input;
	    getline(cin, input);

	    string courseName = input.substr(0, input.find_last_of(" "));
	    int courseCode = stoi(input.substr(input.find_last_of(" ") + 1));

	    Course* courseToRemove = NULL;

	    for (int i = 0; i < selectedStudent.getCourseSize(); i++) 
	    {
	        if (selectedStudent.getCourse()[i].getCode() == courseCode && selectedStudent.getCourse()[i].getName() == courseName) 
	        {
	            courseToRemove = &selectedStudent.getCourse()[i];
	        }
	    }

	    if (courseToRemove != NULL) 
	    {
	        Course* newCourseList = new Course[selectedStudent.getCourseSize() - 1];

	        int j = 0;
	        
	        for (int i = 0; i < selectedStudent.getCourseSize(); i++) 
	        {
	            if (&selectedStudent.getCourse()[i] != courseToRemove) 
	            {
	                newCourseList[j] = selectedStudent.getCourse()[i];
	                j++;
	            }
	        }
	        selectedStudent.setCourseSize(selectedStudent.getCourseSize() - 1);
	    }

	    else 
	    {
	        cerr << "The student is not registered in the course." << endl;
	        exit(1);
	    }
	}

	void SchoolManagerSystem :: courseMenu()
	{
		int selection;

		cout << "0 up" << endl << "1 add_course" << endl
		     << "2 select_course" << endl;
		cin >> selection;

		if (selection == 0)
		{
			mainMenu();
		}

		else if (selection == 1)
		{
			add_course();
		}

		else if (selection == 2)
		{
			select_course();
		}

		else
		{
			cout << "Invalid value for selection." << endl;
			exit(1);
		}
	}

	void SchoolManagerSystem :: list_all_students() const
	{
		for (int i = 0; i < numStudents; ++i)
		{
			cout << studentLS[i].getName() << " " << studentLS[i].getID() << endl;
		}
	}

	void SchoolManagerSystem :: list_all_courses() const
	{
		for (int i = 0; i < numCourses; ++i)
		{
			cout << courseLS[i].getCode() << courseLS[i].getName() << endl;
		}
	}

	void SchoolManagerSystem :: select_course()
	{
		cout << "First select course (Enter name and Code): " << endl;

		string input;
	    getline(cin, input);

	    string selectName = input.substr(0, input.find_last_of(" "));
	    int selectCode = stoi(input.substr(input.find_last_of(" ") + 1));

	    Course object(selectName,selectCode);

		cout << "0 up" << endl << "1 delete_course" 
		     << endl << "2 list_students_registered_to_the_selected_course" << endl;

		int selection;
		cin >> selection;

		if (selection == 0)
		{
			courseMenu();
		}

		else if (selection == 1)
		{
			delete_course(object);
		}

		else if (selection == 2)
		{
			list_students_registered_to_the_selected_course(object);
		}

		else
		{
			cerr << "Invalid selection" << endl;
			exit(1);
		}

	}

	void SchoolManagerSystem :: add_course()
	{
		string input;
	    getline(cin, input);
		
		int addCode = stoi(input.substr(input.find("CSE") + 3, 3));
    	string addName = input.substr(input.find(" ") + 1);

	    Course newCourse(addName, addCode);

	    Course * newCourseList = new Course[numCourses + 1];

	    for (int i = 0; i < numCourses; i++) 
	    {
	        newCourseList[i] = courseLS[i];
	    }
	    newCourseList[numCourses] = newCourse;

	    delete [] courseLS;

	    numCourses++;

	    courseLS = new Course[numCourses];

	    for (int i = 0; i < numCourses; i++) 
	    {
	        courseLS[i] = newCourseList[i];
	    }	    
	    delete [] newCourseList;
	}

	void SchoolManagerSystem::list_students_registered_to_the_selected_course(Course& selectedCourse)
	{
	    cout << "Students registered in " << selectedCourse.getName() << ":" << endl;

	    Student * registeredStudents = selectedCourse.getStudent();

	    for (int i = 0; i < selectedCourse.getStudentSize(); i++) 
	    {
	        cout << registeredStudents[i].getID() << " " << registeredStudents[i].getName() << endl;
	    }
	}

	void SchoolManagerSystem :: delete_course(Course& selectedCourse)
	{
		int index = -1;
		int j = 0;

		for (int i = 0; i < numCourses; ++i)
		{
			if (courseLS[i].getName() == selectedCourse.getName() && courseLS[i].getCode() == selectedCourse.getCode())
			{
				index = i;
			}
		}

		if (index != -1)
		{
			Course * temp = new Course[numCourses - 1];

			for (int i = 0; i < index; ++i)
			{
				if (i == index)
				{
					continue;
				}
				temp[j] = courseLS[i];
				j++;
			}
			delete studentLS;
			courseLS = temp;
			delete [] temp;
		}

		else
		{
			cerr <<	"Course to be deleted not found";
			exit(1);
		}
	}
}