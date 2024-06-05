#include <iostream>
#include <string>
#include "Course.h"
#include "Student.h"

using namespace std;

namespace PA4
{
	class SchoolManagerSystem
	{
	public:
		SchoolManagerSystem();
		SchoolManagerSystem(Course *, Student *);

		void mainMenu();
		void studentMenu();
		void courseMenu();
		
		void add_student();
		void select_student();
		void delete_student(Student&);
		void add_selected_student_to_a_course(Student&);
		void drop_selected_student_from_a_course(Student&);

		void add_course();
		void select_course();
		void delete_course(Course&);
		void list_students_registered_to_the_selected_course(Course&);
		void list_all_students() const;
		void list_all_courses() const;

		Student * getStudentLS() const
		{
			return studentLS;
		}

		~SchoolManagerSystem()
		{
			delete courseLS;
			delete studentLS;
		}

	private:
		int numStudents;
		int numCourses;
		Course * courseLS;
		Student * studentLS;
	};
}