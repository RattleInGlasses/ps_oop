#include "stdafx.h"
#include "..\student\Student.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(CStudent_)
	
	void checkStudentProperties(CStudent const &st, string const& name, string const& surname, string const& patronymic, int age)
	{
		BOOST_CHECK_EQUAL(st.GetAge(), age);
		BOOST_CHECK_EQUAL(st.GetName(), name);
		BOOST_CHECK_EQUAL(st.GetPatronymic(), patronymic);
		BOOST_CHECK_EQUAL(st.GetSurname(), surname);
	}

	bool CheckExceptionMessage(exception const &e, string const &msg)
	{
		BOOST_CHECK_EQUAL(e.what(), msg);
		return true;
	}

	function<bool(exception const&)> CheckMessage(string const &msg)
	{
		return bind(CheckExceptionMessage, placeholders::_1, msg);
	}

	BOOST_AUTO_TEST_SUITE(can_be_created)
		BOOST_AUTO_TEST_CASE(with_empty_patronymic)
		{
			CStudent st("name", "surname", "", 21);
			checkStudentProperties(st, "name", "surname", "", 21);

			CStudent st2("name", "surname", "  ", 21);
			checkStudentProperties(st2, "name", "surname", "", 21);

			CStudent st3("this is a name too %!?", "surname", "  ", 21);
			checkStudentProperties(st3, "this is a name too %!?", "surname", "", 21);
		}

		BOOST_AUTO_TEST_CASE(with_non_empty_patronymic)
		{
			CStudent st("name", "surname", "patronymic", 21);
			checkStudentProperties(st, "name", "surname", "patronymic", 21);
		}
		
		BOOST_AUTO_TEST_CASE(with_age_in_range_from_14_to_60)
		{
			for (int age = 14; age <= 60; ++age)
			{
				CStudent st("name", "surname", "patronymic", age);
				checkStudentProperties(st, "name", "surname", "patronymic", age);
			}
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_SUITE(if_cant_be_created)		

		BOOST_AUTO_TEST_SUITE(throws_invalid_argument)
			BOOST_AUTO_TEST_CASE(when_name_is_empty)
			{
				BOOST_CHECK_EXCEPTION(CStudent("", "surname", "", 25), invalid_argument, CheckMessage("name must not be empty"));
				BOOST_CHECK_EXCEPTION(CStudent("    ", "surname", "", 25), invalid_argument, CheckMessage("name must not be empty"));
			}		

			BOOST_AUTO_TEST_CASE(when_surname_is_empty)
			{
				BOOST_CHECK_EXCEPTION(CStudent("name", "", "", 25), invalid_argument, CheckMessage("surname must not be empty"));
				BOOST_CHECK_EXCEPTION(CStudent("name", "   ", "", 25), invalid_argument, CheckMessage("surname must not be empty"));
			}
		BOOST_AUTO_TEST_SUITE_END()


		BOOST_AUTO_TEST_SUITE(throws_out_of_range)
			BOOST_AUTO_TEST_CASE(when_age_is_less_than_14)
			{
				BOOST_CHECK_EXCEPTION(CStudent("name", "surname", "", 13), out_of_range, CheckMessage("age must be in a range [14; 60]"));
				BOOST_CHECK_EXCEPTION(CStudent("name", "surname", "", 0), out_of_range, CheckMessage("age must be in a range [14; 60]"));
				BOOST_CHECK_EXCEPTION(CStudent("name", "surname", "", -10), out_of_range, CheckMessage("age must be in a range [14; 60]"));
			}

			BOOST_AUTO_TEST_CASE(when_age_is_more_than_60)
			{
				BOOST_CHECK_EXCEPTION(CStudent("name", "surname", "", 61), out_of_range, CheckMessage("age must be in a range [14; 60]"));
				BOOST_CHECK_EXCEPTION(CStudent("name", "surname", "", 100), out_of_range, CheckMessage("age must be in a range [14; 60]"));
			}
		BOOST_AUTO_TEST_SUITE_END()


		BOOST_AUTO_TEST_SUITE(throws_bad_alloc)
			BOOST_AUTO_TEST_SUITE(when_available_memory_is_exceeded)
				struct bigstring
				{
					string bigstr = string(1000000000, 'n');
				};
				BOOST_FIXTURE_TEST_CASE(if_name_is_too_big, bigstring)
				{
					BOOST_CHECK_THROW(CStudent(bigstr, "surname", "", 21), bad_alloc);
				}

				BOOST_FIXTURE_TEST_CASE(if_surname_is_too_big, bigstring)
				{
					BOOST_CHECK_THROW(CStudent("name", bigstr, "", 21), bad_alloc);
				}

				BOOST_FIXTURE_TEST_CASE(if_patronymic_is_too_big, bigstring)
				{
					BOOST_CHECK_THROW(CStudent("name", "surname", bigstr, 21), bad_alloc);
				}
			BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()


	struct createdStudent
	{
		CStudent student = { "name", "surname", "patronymic", 21 };
	};
	BOOST_FIXTURE_TEST_SUITE(can_give_properties, createdStudent)
		BOOST_AUTO_TEST_CASE(name)
		{
			BOOST_CHECK_EQUAL(student.GetName(), "name");
		}		

		BOOST_AUTO_TEST_CASE(surname)
		{
			BOOST_CHECK_EQUAL(student.GetSurname(), "surname");
		}

		BOOST_AUTO_TEST_CASE(patronymic)
		{
			BOOST_CHECK_EQUAL(student.GetPatronymic(), "patronymic");
		}

		BOOST_AUTO_TEST_CASE(age)
		{
			BOOST_CHECK_EQUAL(student.GetAge(), 21);
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_FIXTURE_TEST_SUITE(can_be_renamed, createdStudent)
		BOOST_AUTO_TEST_CASE(with_empty_patronymic)
		{
			student.Rename("anotherName", "anotherSurname", "");
			checkStudentProperties(student, "anotherName", "anotherSurname", "", 21);

			student.Rename("anotherName", "anotherSurname", "   ");
			checkStudentProperties(student, "anotherName", "anotherSurname", "", 21);
		}

		BOOST_AUTO_TEST_CASE(with_non_empty_patronymic)
		{
			student.Rename("anotherName", "anotherSurname", "anotherPatronymic");
			checkStudentProperties(student, "anotherName", "anotherSurname", "anotherPatronymic", 21);
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_FIXTURE_TEST_SUITE(if_cant_be_renamed, createdStudent)
		
		BOOST_AUTO_TEST_SUITE(throws_invalid_argument)
			BOOST_AUTO_TEST_CASE(when_name_is_empty)
			{
				BOOST_CHECK_EXCEPTION(student.Rename("", "surname", ""), invalid_argument, CheckMessage("name must not be empty"));
				BOOST_CHECK_EXCEPTION(student.Rename("     ", "surname", ""), invalid_argument, CheckMessage("name must not be empty"));
			}		

			BOOST_AUTO_TEST_CASE(when_surname_is_empty)
			{
				BOOST_CHECK_EXCEPTION(student.Rename("name", "", ""), invalid_argument, CheckMessage("surname must not be empty"));
				BOOST_CHECK_EXCEPTION(student.Rename("name", "   ", ""), invalid_argument, CheckMessage("surname must not be empty"));
			}
		BOOST_AUTO_TEST_SUITE_END()

		
		struct studentAndBigString : createdStudent
		{
			string bigstr = string(1000000000, 'n');
		};
		BOOST_FIXTURE_TEST_SUITE(throws_bad_alloc, studentAndBigString)
			BOOST_AUTO_TEST_SUITE(when_available_memory_is_exceeded)
				BOOST_AUTO_TEST_CASE(if_name_is_too_big)
				{
					BOOST_CHECK_THROW(student.Rename(bigstr, "surname", ""), bad_alloc);
				}

				BOOST_AUTO_TEST_CASE(if_surname_is_too_big)
				{
					BOOST_CHECK_THROW(student.Rename("name", bigstr, ""), bad_alloc);
				}

				BOOST_AUTO_TEST_CASE(if_patronymic_is_too_big)
				{
					BOOST_CHECK_THROW(student.Rename("name", "surname", bigstr), bad_alloc);
				}
			BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE_END()


		BOOST_AUTO_TEST_SUITE(provides_strong_exception_safety)		
			BOOST_AUTO_TEST_CASE(when_throws_invalid_argument)
			{
				BOOST_REQUIRE_THROW(student.Rename("", "", ""), invalid_argument);
				BOOST_REQUIRE_THROW(student.Rename("n", "", ""), invalid_argument);
				BOOST_REQUIRE_THROW(student.Rename("", "s", ""), invalid_argument);

				checkStudentProperties(student, "name", "surname", "patronymic", 21);
			}

			BOOST_FIXTURE_TEST_CASE(when_throws_bad_alloc, studentAndBigString)
			{
				BOOST_REQUIRE_THROW(student.Rename(bigstr, "s", ""), bad_alloc);
				BOOST_REQUIRE_THROW(student.Rename("n", bigstr, ""), bad_alloc);
				BOOST_REQUIRE_THROW(student.Rename("n", "s", bigstr), bad_alloc);

				checkStudentProperties(student, "name", "surname", "patronymic", 21);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()


	struct studentWithAge : createdStudent
	{
		int initialAge = student.GetAge();
	};
	BOOST_FIXTURE_TEST_SUITE(can_set_age, studentWithAge)
		BOOST_AUTO_TEST_CASE(to_the_same_age)
		{
			student.SetAge(initialAge);
			BOOST_CHECK_EQUAL(student.GetAge(), initialAge);
		}

		BOOST_AUTO_TEST_CASE(to_older_age)
		{
			student.SetAge(initialAge + 1);
			BOOST_CHECK_EQUAL(student.GetAge(), initialAge + 1);
		}

		BOOST_AUTO_TEST_CASE(to_age_that_is_less_than_60)
		{
			for (int age = initialAge; age <= 60; ++age)
			{
				student.SetAge(age);
				BOOST_CHECK_EQUAL(student.GetAge(), age);
			}
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_FIXTURE_TEST_SUITE(if_cant_set_age, studentWithAge)
		
		BOOST_AUTO_TEST_SUITE(throws_out_of_range)
			BOOST_AUTO_TEST_CASE(when_age_is_less_than_14)
			{
				BOOST_CHECK_EXCEPTION(student.SetAge(13), out_of_range, CheckMessage("age must be in a range [14; 60]"));
				BOOST_CHECK_EXCEPTION(student.SetAge(0), out_of_range, CheckMessage("age must be in a range [14; 60]"));
			}

			BOOST_AUTO_TEST_CASE(when_age_is_more_than_60)
			{
				BOOST_CHECK_EXCEPTION(student.SetAge(61), out_of_range, CheckMessage("age must be in a range [14; 60]"));
				BOOST_CHECK_EXCEPTION(student.SetAge(100), out_of_range, CheckMessage("age must be in a range [14; 60]"));
			}
		BOOST_AUTO_TEST_SUITE_END()		


		BOOST_AUTO_TEST_SUITE(throws_domain_error)
			BOOST_AUTO_TEST_CASE(when_new_age_is_less_than_previous)
			{
				BOOST_CHECK_EXCEPTION(student.SetAge(initialAge - 1), domain_error, CheckMessage("age cannot decrease"));
			}
		BOOST_AUTO_TEST_SUITE_END()

		
		BOOST_AUTO_TEST_SUITE(provides_strong_exception_safety)
			BOOST_AUTO_TEST_CASE(when_throws_out_of_range)
			{
				BOOST_REQUIRE_THROW(student.SetAge(-10), out_of_range);

				BOOST_CHECK_EQUAL(student.GetAge(), initialAge);
			}

			BOOST_AUTO_TEST_CASE(when_throws_domain_error)
			{
				BOOST_REQUIRE_THROW(student.SetAge(14), domain_error);

				BOOST_CHECK_EQUAL(student.GetAge(), initialAge);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
