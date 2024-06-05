#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include "Student.h"

using namespace std;

namespace PA4
{
	class Student;

	class Course
	{
	public:
		Course();
		Course(string,int);

		void setCode(int);
		void setName(string);
		void setStudent(string,int);
		int getCode() const;
		Student * getStudent() const;
		string getName() const;
		int getStudentSize() const;

		~Course();

	private:
		int code;
		string name;
		Student * student;
		int studentSize;
	};
}

#endif // COURSE_H
