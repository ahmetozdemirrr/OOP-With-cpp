#include <iostream>
#include <string>
#include "Course.h"

using namespace std;

namespace PA4
{
	Course :: Course ()
	{
		this->name = "";
		this->code = 0;
		this->student = nullptr;
		this->studentSize = 0;
	}

	Course :: Course (string comName, int comCode)
	{
		this->name = comName;
		this->code = comCode;
		this->student = nullptr;
		this->studentSize = 0;
	}

	void Course :: setCode(int comCode)
	{
		this->code = comCode;
	}

	void Course :: setName(string comName)
	{
		this->name = comName;
	}

	void Course ::setStudent(string comStudent, int comID)
	{
	    if (studentSize == 0) 
	    {
	        studentSize++;
	        student = new Student[studentSize];

	        student[0].setName(comStudent);
	        student[0].setID(comID);
	    } 

	    else 
	    {
	        Student* temp = new Student[studentSize + 1];

	        for (int i = 0; i < studentSize; ++i) 
	        {
	            temp[i].setName(student[i].getName());
	            temp[i].setID(student[i].getID());
	        }
	        temp[studentSize].setName(comStudent);
	        temp[studentSize].setID(comID);

	        delete[] student;

	        student = temp;
	        studentSize++;
	    }
	}

	int Course :: getCode() const
	{
		return code;
	}

	Student * Course :: getStudent() const
	{
		return student;
	}

	string Course :: getName() const
	{
		return name;
	}

	int Course :: getStudentSize() const
	{
		return studentSize;
	}

	Course :: ~Course()
	{
		delete student;
	}
}