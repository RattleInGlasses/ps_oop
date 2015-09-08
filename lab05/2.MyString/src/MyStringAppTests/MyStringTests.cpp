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

BOOST_AUTO_TEST_SUITE_END()