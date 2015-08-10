#include "stdafx.h"
#include "..\rational\Rational.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

BOOST_AUTO_TEST_SUITE(CRational_)

	BOOST_AUTO_TEST_SUITE(can_be_created)
		BOOST_AUTO_TEST_CASE(from_nothing_to_zero)
		{
			CRational rational;
			BOOST_CHECK_CLOSE(rational.ToDouble(), 0.0, 0.001);
		}

		BOOST_AUTO_TEST_CASE(from_int)
		{
			CRational rational(34);
			BOOST_CHECK_CLOSE(rational.ToDouble(), 34.0, 0.001);
		}

		BOOST_AUTO_TEST_CASE(from_numerator_and_denominator)
		{
			CRational rational(3, 5);
			BOOST_CHECK_CLOSE(rational.ToDouble(), 0.6, 0.001);
		}

		BOOST_AUTO_TEST_CASE(from_zero_denominator_to_zero_number)
		{
			CRational rational(3, 0);
			BOOST_CHECK_CLOSE(rational.ToDouble(), 0.0, 0.001);
		}
	BOOST_AUTO_TEST_SUITE_END()


	void CheckEquality(CRational const &num1, CRational const &num2)
	{
		BOOST_CHECK_EQUAL(num1.GetNumerator(), num2.GetNumerator());
		BOOST_CHECK_EQUAL(num1.GetDenominator(), num2.GetDenominator());
	}
	void CheckEquality(pair<int, CRational> const &num1, pair<int, CRational> const &num2)
	{
		BOOST_CHECK_EQUAL(num1.first, num2.first);
		CheckEquality(num1.second, num2.second);
	}
	
	struct createdRational
	{
		CRational rational = { 2, 3 };
	};	

	BOOST_FIXTURE_TEST_SUITE(allows_to_get_properties, createdRational)
		BOOST_AUTO_TEST_CASE(numerator)
		{
			BOOST_CHECK_EQUAL(rational.GetNumerator(), 2);
		}

		BOOST_AUTO_TEST_CASE(denominator)
		{
			BOOST_CHECK_EQUAL(rational.GetDenominator(), 3);
		}

		BOOST_AUTO_TEST_CASE(double_)
		{
			BOOST_CHECK_CLOSE(rational.ToDouble(), ((double)2 / 3), 0.001);
		}

		BOOST_AUTO_TEST_CASE(compound_fraction)
		{
			CheckEquality(CRational(7, 2).ToCompoundFraction(), { 3, { 1, 2 } });
			CheckEquality(CRational(-7, 2).ToCompoundFraction(), { -3, { -1, 2 } });
			CheckEquality(CRational(1, 2).ToCompoundFraction(), { 0, { 1, 2 } });
			CheckEquality(CRational(0).ToCompoundFraction(), { 0, 0 });
		}
	BOOST_AUTO_TEST_SUITE_END()

	
	BOOST_AUTO_TEST_SUITE(normalize)
		BOOST_AUTO_TEST_SUITE(in_case)
			BOOST_AUTO_TEST_CASE(after_creation)
			{
				CheckEquality(CRational(25, 50), { 1, 2 });
			}

			BOOST_AUTO_TEST_CASE(after_addition)
			{
				CheckEquality(CRational(3, 5) + CRational(2, 5), { 1, 1 });
			}

			BOOST_AUTO_TEST_CASE(after_substraction)
			{
				CheckEquality(CRational(7, 5) - CRational(2, 5), { 1, 1 });
			}

			BOOST_AUTO_TEST_CASE(after_multiplication)
			{
				CheckEquality(CRational(3, 2) * CRational(2, 3), { 1, 1 });
			}

			BOOST_AUTO_TEST_CASE(after_division)
			{
				CheckEquality(CRational(3, 2) / CRational(3, 2), { 1, 1 });
			}

			BOOST_AUTO_TEST_CASE(after_addition_with_assignement)
			{
				CheckEquality(CRational(3, 5) += CRational(2, 5), { 1, 1 });
			}

			BOOST_AUTO_TEST_CASE(after_substraction_assignement)
			{
				CheckEquality(CRational(7, 5) -= CRational(2, 5), { 1, 1 });
			}

			BOOST_AUTO_TEST_CASE(after_multiplication_with_assignment)
			{
				CheckEquality(CRational(3, 2) *= CRational(2, 3), { 1, 1 });
			}

			BOOST_AUTO_TEST_CASE(after_division_with_assignment)
			{
				CheckEquality(CRational(3, 2) / CRational(3, 2), { 1, 1 });
			}
		BOOST_AUTO_TEST_SUITE_END()
		
		BOOST_AUTO_TEST_SUITE(by)
			BOOST_AUTO_TEST_CASE(set_denominator_to_1_when_numerator_has_been_set_to_0)
			{
				BOOST_CHECK_EQUAL(CRational(0, 25).GetDenominator(), 1);
				BOOST_CHECK_EQUAL((CRational(3, 25) *= 0).GetDenominator(), 1);
			}

			BOOST_AUTO_TEST_CASE(move_negative_sign_from_denominator_to_numerator)
			{
				CheckEquality(CRational(3, -7), { -3, 7 });
				CheckEquality(CRational(-3, -7), { 3, 7 });
			}
			
			BOOST_AUTO_TEST_CASE(divide_by_common_divisor)
			{
				CheckEquality(CRational(125, 3000), { 1, 24 });
				CheckEquality(CRational(15, 10), { 3, 2 });
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_SUITE(have_operations)
		
		BOOST_AUTO_TEST_SUITE(unary_operations)
			BOOST_AUTO_TEST_CASE(unary_plus)
			{
				CheckEquality(+CRational(2, 3), { 2, 3 });
			}

			BOOST_AUTO_TEST_CASE(unary_minus)
			{
				CheckEquality(-CRational(2, 3), { -2, 3 });
			}
		BOOST_AUTO_TEST_SUITE_END()

	
		BOOST_AUTO_TEST_SUITE(addition)
			BOOST_AUTO_TEST_CASE(rational_plus_rational)
			{
				CheckEquality(CRational(3, 5) + CRational(7, 6), { 53, 30 });
			}

			BOOST_AUTO_TEST_CASE(rational_plus_int)
			{
				CheckEquality(CRational(3, 2) + 10, { 23, 2 });
			}

			BOOST_AUTO_TEST_CASE(int_plus_rational)
			{
				CheckEquality(5 + CRational(2, 3), { 17, 3 });
			}
		BOOST_AUTO_TEST_SUITE_END()


		BOOST_AUTO_TEST_SUITE(substruction)
			BOOST_AUTO_TEST_CASE(rational_subst_rational)
			{
				CheckEquality(CRational(7, 3) - CRational(2, 3), { 5, 3 });
			}

			BOOST_AUTO_TEST_CASE(rational_subst_int)
			{
				CheckEquality(CRational(2, 3) - 10, { -28, 3 });
			}

			BOOST_AUTO_TEST_CASE(int_subst_rational)
			{
				CheckEquality(5 - CRational(2, 3), { 13, 3 });
			}
		BOOST_AUTO_TEST_SUITE_END()


		BOOST_AUTO_TEST_SUITE(multiplication)
			BOOST_AUTO_TEST_CASE(rational_mult_rational)
			{
				CheckEquality(CRational(7, 3) * CRational(2, 3), { 14, 9 });
			}

			BOOST_AUTO_TEST_CASE(rational_mult_int)
			{
				CheckEquality(CRational(2, 3) * -10, { -20, 3 });
			}

			BOOST_AUTO_TEST_CASE(int_mult_rational)
			{
				CheckEquality(5 * CRational(2, 3), { 10, 3 });
			}
		BOOST_AUTO_TEST_SUITE_END()


		BOOST_AUTO_TEST_SUITE(division)
			BOOST_AUTO_TEST_CASE(rational_div_rational)
			{
				CheckEquality(CRational(7, 3) / CRational(2, 3), { 7, 2 });
			}

			BOOST_AUTO_TEST_CASE(rational_div_int)
			{
				CheckEquality(CRational(2, 3) / -2, { -1, 3 });
			}

			BOOST_AUTO_TEST_CASE(int_div_rational)
			{
				CheckEquality(5 / CRational(2, 3), { 15, 2 });
			}
		BOOST_AUTO_TEST_SUITE_END()


		BOOST_AUTO_TEST_SUITE(addition_with_asignement)
			BOOST_AUTO_TEST_CASE(plus_rational)
			{
				CheckEquality(CRational(2, 3) += CRational(1, 5), { 13, 15 });
			}

			BOOST_AUTO_TEST_CASE(plus_int)
			{
				CheckEquality(CRational(2, 3) += 7, { 23, 3 });
			}

			BOOST_AUTO_TEST_CASE(plus_itself)
			{
				CRational r = { 2, 3 };
				CheckEquality(r += r, { 4, 3 });
			}
		BOOST_AUTO_TEST_SUITE_END()


		BOOST_AUTO_TEST_SUITE(substruction_with_assignement)
			BOOST_AUTO_TEST_CASE(subst_rational)
			{
				CheckEquality(CRational(2, 3) -= CRational(1, 5), { 7, 15 });
			}

			BOOST_AUTO_TEST_CASE(subst_int)
			{
				CheckEquality(CRational(7, 3) -= 2, { 1, 3 });
			}

			BOOST_AUTO_TEST_CASE(subst_itself)
			{
				CRational r = { 2, 3 };
				CheckEquality(r -= r, 0);
			}
		BOOST_AUTO_TEST_SUITE_END()


		BOOST_AUTO_TEST_SUITE(multiplication_with_assignement)
			BOOST_AUTO_TEST_CASE(mult_rational)
			{
				CheckEquality(CRational(7, 3) *= CRational(2, 3), { 14, 9 });
			}

			BOOST_AUTO_TEST_CASE(mult_int)
			{
				CheckEquality(CRational(2, 3) *= -10, { -20, 3 });
			}

			BOOST_AUTO_TEST_CASE(mult_itself)
			{
				CRational r = { 2, 3 };
				CheckEquality(r *= r, { 4, 9 });
			}
		BOOST_AUTO_TEST_SUITE_END()


		BOOST_AUTO_TEST_SUITE(division_with_assignement)
			BOOST_AUTO_TEST_CASE(div_rational)
			{
				CheckEquality(CRational(7, 3) /= CRational(2, 3), { 7, 2 });
			}

			BOOST_AUTO_TEST_CASE(div_int)
			{
				CheckEquality(CRational(2, 3) /= -2, { -1, 3 });
			}

			BOOST_AUTO_TEST_CASE(div_itself)
			{
				CRational r = { 2, 3 };
				CheckEquality(r /= r, 1);
			}
		BOOST_AUTO_TEST_SUITE_END()


		BOOST_AUTO_TEST_SUITE(equality)
			BOOST_AUTO_TEST_CASE(rational_eq_rational)
			{
				BOOST_CHECK(CRational(2, 3) == CRational(4, 6));
			}

			BOOST_AUTO_TEST_CASE(rational_eq_int)
			{
				BOOST_CHECK(CRational(-6, 3) == -2);
			}

			BOOST_AUTO_TEST_CASE(int_eq_rational)
			{
				BOOST_CHECK(-1 == CRational(-3, 3));
			}
		BOOST_AUTO_TEST_SUITE_END()


		BOOST_AUTO_TEST_SUITE(inequality)
			BOOST_AUTO_TEST_CASE(rational_ineq_rational)
			{
				BOOST_CHECK(CRational(2, 3) != CRational(5, 6));
			}

			BOOST_AUTO_TEST_CASE(rational_ineq_int)
			{
				BOOST_CHECK(CRational(-6, 3) != 3);
			}

			BOOST_AUTO_TEST_CASE(int_ineq_rational)
			{
				BOOST_CHECK(0 != CRational(-3, 3));
			}
		BOOST_AUTO_TEST_SUITE_END()


		BOOST_AUTO_TEST_SUITE(less)
			BOOST_AUTO_TEST_CASE(rational_less_rational)
			{
				BOOST_CHECK(CRational(2, 3) < CRational(5, 6));
			}

			BOOST_AUTO_TEST_CASE(rational_less_int)
			{
				BOOST_CHECK(CRational(-6, 3) < 3);
			}

			BOOST_AUTO_TEST_CASE(int_less_rational)
			{
				BOOST_CHECK(-1 < CRational(3, 7));
			}
		BOOST_AUTO_TEST_SUITE_END()


		BOOST_AUTO_TEST_SUITE(less_or_equal)
			BOOST_AUTO_TEST_CASE(rational_less_or_eq_rational)
			{
				BOOST_CHECK(CRational(2, 3) <= CRational(5, 6));
			}

			BOOST_AUTO_TEST_CASE(rational_less_or_eq_int)
			{
				BOOST_CHECK(CRational(-6, 3) <= -2);
			}

			BOOST_AUTO_TEST_CASE(int_less_or_eq_rational)
			{
				BOOST_CHECK(-1 <= CRational(3, 7));
			}
		BOOST_AUTO_TEST_SUITE_END()


		BOOST_AUTO_TEST_SUITE(more)
			BOOST_AUTO_TEST_CASE(rational_more_rational)
			{
				BOOST_CHECK(CRational(5, 6) > CRational(2, 3));
			}

			BOOST_AUTO_TEST_CASE(rational_more_int)
			{
				BOOST_CHECK(3 > CRational(-6, 3));
			}

			BOOST_AUTO_TEST_CASE(int_more_rational)
			{
				BOOST_CHECK(CRational(3, 7) > -1);
			}
		BOOST_AUTO_TEST_SUITE_END()


		BOOST_AUTO_TEST_SUITE(more_or_equal)
			BOOST_AUTO_TEST_CASE(rational_more_or_eq_rational)
			{
				BOOST_CHECK(CRational(5, 6) >= CRational(2, 3));
			}

			BOOST_AUTO_TEST_CASE(rational_more_or_eq_int)
			{
				BOOST_CHECK(-2 >= CRational(-6, 3));
			}

			BOOST_AUTO_TEST_CASE(int_more_or_eq_rational)
			{
				BOOST_CHECK(CRational(3, 7) >= -1);
			}
		BOOST_AUTO_TEST_SUITE_END()


		BOOST_AUTO_TEST_CASE(send_to_stream)
		{
			ostringstream output;
			output << CRational(7, 3);
			BOOST_CHECK_EQUAL(output.str(), "7/3");
		}

		
		BOOST_AUTO_TEST_SUITE(get_from_stream)
			BOOST_AUTO_TEST_CASE(with_exact_sequence)
			{
				istringstream input("-2/5");
				CRational rational;
				input >> rational;
				CheckEquality(rational, { -2, 5 });
			}
			
			BOOST_AUTO_TEST_CASE(with_spases_berore_the_sequence)
			{
				istringstream input("  3/21a");
				CRational rational;
				input >> rational;
				CheckEquality(rational, { 3, 21 });
			}

			struct readingError
			{
				CRational rational;
				istringstream input;
				
				readingError()
				{
					input.str("  3\\21a");
					input >> rational;
				}
			};
			BOOST_FIXTURE_TEST_CASE(zero_on_error, readingError)
			{
				CheckEquality(rational, 0);
			}

			BOOST_FIXTURE_TEST_CASE(set_fail_bit_on_error, readingError)
			{
				BOOST_CHECK(input.fail() && !input.bad());
			}

			BOOST_FIXTURE_TEST_CASE(dont_change_pos_on_error, readingError)
			{				
				string s;
				input.clear();
				getline(input, s);
				BOOST_CHECK_EQUAL(s, "  3\\21a");
			}
		BOOST_AUTO_TEST_SUITE_END()


		BOOST_AUTO_TEST_CASE(send_compound_to_stream)
		{
			ostringstream output;
			output << CRational(7, 3).ToCompoundFraction();
			BOOST_CHECK_EQUAL(output.str(), "(2 1/3)");

			output.str("");
			output << CRational(-7, 3).ToCompoundFraction();
			BOOST_CHECK_EQUAL(output.str(), "-(2 1/3)");
		}

	BOOST_AUTO_TEST_SUITE_END()
	
BOOST_AUTO_TEST_SUITE_END()