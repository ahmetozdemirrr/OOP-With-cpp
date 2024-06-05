#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include "Course.h"

using namespace std;

namespace PA4
{
	class Course;

	class Student
	{
	public:
		Student();
		Student(string,int);

		void setName(string);
		void setID(int);
		void setCourse(string,int);
		void setCourseSize(int);
		int getID() const;
		int getCourseSize() const;
		Course * getCourse() const;
		string getName() const;

		~Student();

	private:
		string name;
		int ID;
		Course * course;
		int courseSize;
	};
}

#endif // STUDENT_H