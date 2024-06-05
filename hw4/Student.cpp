#include <iostream>
#include <string>
#include "Student.h"

using namespace std;

namespace PA4
{
	Student :: Student()
	{
		this->name = "";
		this->ID = 0;
		this->course = nullptr;
		this->courseSize = 0;
	}

	Student :: Student(string comName, int comID)
	{
		this->name = comName;
		this->ID = comID;
		this->course = nullptr;
		this->courseSize = 0;
	}

	void Student :: setName(string comName)
	{
		this->name = comName;
	}

	void Student :: setID(int comID)
	{
		this->ID = comID;
	}

	void Student ::setCourse(string comCourse, int comCode)
	{
	    if (courseSize == 0) 
	    {
	        courseSize++;
	        course = new Course[courseSize];

	        course[0].setName(comCourse);
	        course[0].setCode(comCode);
	    } 

	    else 
	    {
	        Course* temp = new Course[courseSize + 1];

	        for (int i = 0; i < courseSize; ++i) 
	        {
	            temp[i].setName(course[i].getName());
	            temp[i].setCode(course[i].getCode());
	        }
	        temp[courseSize].setName(comCourse);
	        temp[courseSize].setCode(comCode);

	        delete[] course;

	        course = temp;
	        courseSize++;
	    }
	}

	void Student :: setCourseSize(int comSize)
	{
		courseSize = comSize;
	}

	int Student :: getID() const
	{
		return ID;
	}

	int Student :: getCourseSize() const
	{
		return courseSize;
	}

	Course * Student :: getCourse() const
	{
		return course;
	}

	string Student :: getName() const
	{
		return name;
	}

	Student :: ~Student()
	{
		delete course;
	}
}