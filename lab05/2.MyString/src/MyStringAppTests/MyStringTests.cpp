#include "stdafx.h"
#include "..\MyStringApp\MyString.h"
#include <vld.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(MyString_)

	BOOST_AUTO_TEST_SUITE(can_be_created)
		BOOST_AUTO_TEST_CASE(empty_by_default)
		{
			CMyString str;
			BOOST_CHECK_EQUAL(str.GetLength(), 0);
			BOOST_CHECK_EQUAL(str.GetStringData(), "");
		}

		BOOST_AUTO_TEST_CASE(from_c_string)
		{
			CMyString str("test");
			BOOST_CHECK_EQUAL(str.GetLength(), 4);
			BOOST_CHECK_EQUAL(str.GetStringData(), "test");
		}

		BOOST_AUTO_TEST_CASE(from_char_array)
		{
			CMyString str("test string", 4);
			BOOST_CHECK_EQUAL(str.GetLength(), 4);
			BOOST_CHECK_EQUAL(str.GetStringData(), "test");
		}

		BOOST_AUTO_TEST_CASE(from_stl_string)
		{
			string stlString = "test";
			CMyString str(stlString);
			BOOST_CHECK_EQUAL(str.GetLength(), 4);
			BOOST_CHECK_EQUAL(str.GetStringData(), "test");
		}

		BOOST_AUTO_TEST_CASE(by_copy)
		{
			CMyString str1("test");
			CMyString str2(str1);
			BOOST_CHECK_EQUAL(str2.GetLength(), 4);
			BOOST_CHECK_EQUAL(str2.GetStringData(), "test");
		}

		BOOST_AUTO_TEST_CASE(by_move)
		{
			CMyString str(CMyString("test"));
			BOOST_CHECK_EQUAL(str.GetLength(), 4);
			BOOST_CHECK_EQUAL(str.GetStringData(), "test");
		}
	BOOST_AUTO_TEST_SUITE_END()	


	struct CreatedStrings
	{
		CMyString str1;
		CMyString str2 = CMyString("s");
		CMyString const str3 = CMyString("data");
	};
	BOOST_FIXTURE_TEST_SUITE(have_properties, CreatedStrings)
		BOOST_AUTO_TEST_CASE(length)
		{
			BOOST_CHECK_EQUAL(str1.GetLength(), 0);
			BOOST_CHECK_EQUAL(str2.GetLength(), 1);
			BOOST_CHECK_EQUAL(str3.GetLength(), 4);
		}
		
		BOOST_AUTO_TEST_CASE(c_string_data)
		{
			BOOST_CHECK_EQUAL(str1.GetStringData(), "");
			BOOST_CHECK_EQUAL(str2.GetStringData(), "s");
			BOOST_CHECK_EQUAL(str3.GetStringData(), "data");
		}

		BOOST_AUTO_TEST_CASE(symbols)
		{
			str2[0] = 'n';
			BOOST_CHECK_EQUAL(str2[0], 'n');
			BOOST_CHECK_EQUAL(str3[1], 'a');
			BOOST_CHECK_EQUAL(str3[2], 't');
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(have_operations, CreatedStrings)
		BOOST_AUTO_TEST_CASE(get_substring)
		{
			CMyString substr = str1.SubString(0);
			BOOST_CHECK_EQUAL(substr.GetStringData(), "");
			substr = str1.SubString(10, 20);
			BOOST_CHECK_EQUAL(substr.GetStringData(), "");

			substr = str3.SubString(0);
			BOOST_CHECK_EQUAL(substr.GetStringData(), "data");
			substr = str3.SubString(1, 2);
			BOOST_CHECK_EQUAL(substr.GetStringData(), "at");
			substr = str3.SubString(1, 10);
			BOOST_CHECK_EQUAL(substr.GetStringData(), "ata");
		}		

		BOOST_AUTO_TEST_CASE(clear)
		{
			str2.Clear();
			BOOST_CHECK_EQUAL(str2.GetLength(), 0);
			BOOST_CHECK_EQUAL(str2.GetStringData(), "");
			str2.Clear();
			BOOST_CHECK_EQUAL(str2.GetLength(), 0);
			BOOST_CHECK_EQUAL(str2.GetStringData(), "");
		}

		BOOST_AUTO_TEST_CASE(assignement_by_copy)
		{
			str2 = str3;
			BOOST_CHECK_EQUAL(str3.GetLength(), str2.GetLength());
			BOOST_CHECK_EQUAL(str3.GetStringData(), str2.GetStringData());

			str2 = str2;
			BOOST_CHECK_EQUAL(str3.GetLength(), str2.GetLength());
			BOOST_CHECK_EQUAL(str3.GetStringData(), str2.GetStringData());
		}

		BOOST_AUTO_TEST_CASE(assignement_by_move)
		{
			str1 = move(str2);
			BOOST_CHECK_EQUAL(str1.GetLength(), 1);
			BOOST_CHECK_EQUAL(str1.GetStringData(), "s");
		}

		BOOST_AUTO_TEST_CASE(concatenation)
		{
			BOOST_CHECK_EQUAL((str1 + str1).GetStringData(), "");
			BOOST_CHECK_EQUAL((str1 + str2).GetStringData(), "s");
			BOOST_CHECK_EQUAL((str1 + str3).GetStringData(), "data");
			BOOST_CHECK_EQUAL((str2 + str3).GetStringData(), "sdata");
		}

		BOOST_AUTO_TEST_CASE(concatenetion_with_assignement)
		{
			str1 += str1;
			BOOST_CHECK_EQUAL(str1.GetStringData(), "");
			str1 += str2;
			BOOST_CHECK_EQUAL(str1.GetStringData(), "s");
			str1 += str3;
			BOOST_CHECK_EQUAL(str1.GetStringData(), "sdata");
		}

		BOOST_AUTO_TEST_SUITE(compare_operations)
			BOOST_AUTO_TEST_CASE(equal)
			{
				BOOST_CHECK(str1 == str1);
				str2 = str1;
				BOOST_CHECK(str2 == str1);
				str1 = str3;
				BOOST_CHECK(str3 == str1);
			}

			BOOST_AUTO_TEST_CASE(unequal)
			{
				BOOST_CHECK(str1 != str2);
				BOOST_CHECK(str2 != str3);
				BOOST_CHECK(str1 != str3);
			}

			BOOST_AUTO_TEST_CASE(less)
			{
				BOOST_CHECK(str1 < str2);
				BOOST_CHECK(str2 < "z");
				BOOST_CHECK(str3 < "date");
			}

			BOOST_AUTO_TEST_CASE(more)
			{
				BOOST_CHECK(str2 > str1);
				BOOST_CHECK("z" > str2);
				BOOST_CHECK("date" > str3);
			}

			BOOST_AUTO_TEST_CASE(less_or_equal)
			{
				BOOST_CHECK(str1 <= str1);
				BOOST_CHECK(str1 <= str2);
				BOOST_CHECK(str3 <= "date");
				BOOST_CHECK(str3 <= "data");
			}

			BOOST_AUTO_TEST_CASE(more_or_equal)
			{
				BOOST_CHECK(str1 >= str1);
				BOOST_CHECK(str2 >= str1);
				BOOST_CHECK("date" >= str3);
				BOOST_CHECK("data" >= str3);
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_CASE(read_from_stream)
		{
				istringstream input("");
				input >> str1;
				BOOST_CHECK_EQUAL(str1.GetStringData(), "");

				input.clear();
				input.str("  word word2");
				input >> str1;
				BOOST_CHECK_EQUAL(str1.GetStringData(), "word");
			}

		BOOST_AUTO_TEST_CASE(write_to_stream)
		{
			ostringstream output;
			output << str1;
			BOOST_CHECK_EQUAL(output.str(), "");
			output << str2;
			BOOST_CHECK_EQUAL(output.str(), "s");
			output << str3;
			BOOST_CHECK_EQUAL(output.str(), "sdata");
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_FIXTURE_TEST_SUITE(have_iterators_that_can, CreatedStrings)
		BOOST_AUTO_TEST_CASE(compare)
		{
			BOOST_CHECK(str1.begin() == str1.end());
			BOOST_CHECK(str2.begin() != str2.end());
			BOOST_CHECK(str3.begin() != str3.end());
		}

		BOOST_AUTO_TEST_CASE(move_forward)
		{
			BOOST_CHECK(str2.begin()++ == --str2.end());
			BOOST_CHECK(++str2.begin() == str2.end());
			BOOST_CHECK((str2.begin() + 1) == str2.end());
			BOOST_CHECK((1 + str2.begin()) == str2.end());
		}

		BOOST_AUTO_TEST_CASE(move_backwards)
		{
			BOOST_CHECK_EQUAL(*--str2.end(), 's');
			BOOST_CHECK_EQUAL(*(str2.end() - 1), 's');
			BOOST_CHECK_EQUAL(*((str3.begin() + 1)--), 'a');
		}

		BOOST_AUTO_TEST_CASE(find_difference)
		{
			BOOST_CHECK_EQUAL(str1.end() - str1.begin(), 0);
			BOOST_CHECK_EQUAL(str2.end() - str2.begin(), 1);
		}

		BOOST_AUTO_TEST_CASE(access_to_a_symbol)
		{
			BOOST_CHECK_EQUAL(*str2.begin(), 's');
			BOOST_CHECK_EQUAL(str3.begin()[1], 'a');
		}

		void TestRangeBasedForWithString(CMyString const & myStr)
		{
			string stlStr;
			for (auto ch : myStr)
			{
				stlStr += ch;
			}
			BOOST_CHECK_EQUAL(myStr.GetStringData(), stlStr.c_str());
		}
		BOOST_AUTO_TEST_CASE(be_used_in_a_range_based_for_loop)
		{
			TestRangeBasedForWithString(str1);
			TestRangeBasedForWithString(str2);
		}
	BOOST_AUTO_TEST_SUITE_END()

	
	BOOST_FIXTURE_TEST_SUITE(have_reverse_iterators_that_can, CreatedStrings)
		BOOST_AUTO_TEST_CASE(compare)
		{
			BOOST_CHECK(str1.rbegin() == str1.rend());
			BOOST_CHECK(str2.rbegin() != str2.rend());
			BOOST_CHECK(str3.rbegin() != str3.rend());
		}

		BOOST_AUTO_TEST_CASE(move_forward)
		{
			BOOST_CHECK(str2.rbegin()++ == --str2.rend());
			BOOST_CHECK(++str2.rbegin() == str2.rend());
			BOOST_CHECK((str2.rbegin() + 1) == str2.rend());
			BOOST_CHECK((1 + str2.rbegin()) == str2.rend());
		}

		BOOST_AUTO_TEST_CASE(move_backwards)
		{
			BOOST_CHECK_EQUAL(*--str2.rend(), 's');
			BOOST_CHECK_EQUAL(*(str2.rend() - 1), 's');
			BOOST_CHECK_EQUAL(*((str3.rbegin() + 1)--), 't');
		}

		BOOST_AUTO_TEST_CASE(find_difference)
		{
			BOOST_CHECK_EQUAL(str1.rend() - str1.rbegin(), 0);
			BOOST_CHECK_EQUAL(str2.rend() - str2.rbegin(), 1);
			BOOST_CHECK_EQUAL(str3.rend() - str3.rbegin(), 4);
		}

		BOOST_AUTO_TEST_CASE(access_to_a_symbol)
		{
			BOOST_CHECK_EQUAL(*str2.rbegin(), 's');
			BOOST_CHECK_EQUAL(str3.rbegin()[1], 't');
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()