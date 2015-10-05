#include "stdafx.h"
#include "..\Persons\SaverLoader.h"

using namespace std;


BOOST_AUTO_TEST_SUITE(SaverLoader)

	BOOST_AUTO_TEST_SUITE(Load_data_is_reversed_to_Save)

		bool UniversitiesCmp(CUniversity const &univer1, CUniversity const &univer2)
		{
			return (univer1.GetName() == univer2.GetName());
		}

		bool StudentsCmp(CStudent const &student1, CStudent const &student2)
		{				
			return ((student1.GetAge() == student2.GetAge())
				&& (student1.GetGender() == student2.GetGender())
				&& (student1.GetHeight() == student2.GetHeight())
				&& (student1.GetWeight() == student2.GetWeight())
				&& (student1.GetStudyYear() == student2.GetStudyYear())
				&& (student1.GetUniversity()->GetName() == student2.GetUniversity()->GetName()));
		}

		bool CompaniesCmp(CCompany const &company1, CCompany const &company2)
		{		
			return ((company1.GetName() == company2.GetName())
				&& (company1.GetWebsite() == company2.GetWebsite()));
		}

		bool WorkersCmp(CWorker const &worker1, CWorker const &worker2)
		{				
			return ((worker1.GetAge() == worker2.GetAge())
				&& (worker1.GetGender() == worker2.GetGender())
				&& (worker1.GetHeight() == worker2.GetHeight())
				&& (worker1.GetWeight() == worker2.GetWeight())
				&& (worker1.GetPost() == worker2.GetPost())
				&& (worker1.GetCompany()->GetName() == worker2.GetCompany()->GetName())
				&& (worker1.GetCompany()->GetWebsite() == worker2.GetCompany()->GetWebsite()));
		}

		void CheckDataEquality(list<CUniversity> const &universities1, list<CStudent> const &students1,
			list<CCompany> const &companies1, list<CWorker> const &workers1,
			list<CUniversity> const &universities2, list<CStudent> const &students2,
			list<CCompany> const &companies2, list<CWorker> const &workers2)
		{
			BOOST_CHECK(boost::equal(universities1, universities2, UniversitiesCmp));
			BOOST_CHECK(boost::equal(students1, students2, StudentsCmp));
			BOOST_CHECK(boost::equal(companies1, companies2, CompaniesCmp));
			BOOST_CHECK(boost::equal(workers1, workers2, WorkersCmp));
		}

		void DeleteDataFile()
		{
			remove("test.dat");
		}

		void CheckSaveLoadReversedEquality(list<CUniversity> const &universitiesToSave, list<CStudent> const &studentsToSave,
			list<CCompany> const &companiesToSave, list<CWorker> const &workersToSave)
		{
			string dataFileName = "test.dat";
			SaveData(dataFileName, studentsToSave, universitiesToSave, workersToSave, companiesToSave);

			list<CUniversity> universitiesLoaded;
			list<CStudent> studentsLoaded;
			list<CCompany> companiesLoaded;
			list<CWorker> workersLoaded;
			LoadData(dataFileName, studentsLoaded, universitiesLoaded, workersLoaded, companiesLoaded);

			CheckDataEquality(universitiesToSave, studentsToSave, companiesToSave, workersToSave,
				universitiesLoaded, studentsLoaded, companiesLoaded, workersLoaded);
		}

	
		BOOST_AUTO_TEST_CASE(if_all_data_is_empty)
		{
			CheckSaveLoadReversedEquality({}, {}, {}, {});
		}


		struct CreatedData
		{
			CUniversity university;
			shared_ptr<CUniversity> pStudentUniversity;
			CStudent student;
			CCompany company;
			CWorker worker;

			CreatedData() :
				university("un1"),
				student(Gender::MALE, 1u, "1", 1u, 1u, &university, 1),
				company("cmp1", ""),
				worker(Gender::FEMALE, 1u, "1", 1u, 1u, &company, "p")
			{
			}
		};
		BOOST_FIXTURE_TEST_SUITE(if_everithyng_is_empty_except, CreatedData)
			BOOST_AUTO_TEST_CASE(universities)
			{
				CheckSaveLoadReversedEquality({ university }, {}, {}, {});
			}

			BOOST_AUTO_TEST_CASE(students_and_universities)
			{
				CheckSaveLoadReversedEquality({ university }, { student }, {}, {});
			}

			BOOST_AUTO_TEST_CASE(companies)
			{
				CheckSaveLoadReversedEquality({}, {}, { company }, {});
			}

			BOOST_AUTO_TEST_CASE(workers_and_companies)
			{
				CheckSaveLoadReversedEquality({}, {}, { company }, { worker });
			}
		BOOST_AUTO_TEST_SUITE_END()

		
		BOOST_FIXTURE_TEST_SUITE(if_one_list_is_empty, CreatedData)
			BOOST_AUTO_TEST_CASE(students)
			{
				CheckSaveLoadReversedEquality({ university }, {}, { company }, { worker });
			}	

			BOOST_AUTO_TEST_CASE(workers)
			{
				CheckSaveLoadReversedEquality({ university }, { student }, { company }, {});
			}
		BOOST_AUTO_TEST_SUITE_END()


		BOOST_FIXTURE_TEST_CASE(if_all_lists_have_1_element, CreatedData)
		{
			CheckSaveLoadReversedEquality({ university }, { student }, { company }, { worker });
		}


		BOOST_FIXTURE_TEST_CASE(if_all_lists_have_3_elements, CreatedData)
		{
			CheckSaveLoadReversedEquality({ university, CUniversity(university), CUniversity(university) }, 
			{ student, CStudent(student), CStudent(student) }, 
			{ company, CCompany(company), CCompany(company) },
			{ worker, CWorker(worker), CWorker(worker) });
		}


		BOOST_FIXTURE_TEST_CASE(if_data_has_special_characters, CreatedData)
		{
			university.SetName("\"MGU\",\\UGM");
			student.SetName("name\\, \"name\", name");
			company.SetName("nm, \"nm\",\\ nm");
			company.SetWebsite("web.\\\"site\",sites.com");
			worker.SetName("n, \"\\n\", n");
			CheckSaveLoadReversedEquality({ university }, { student }, { company }, { worker });
		}


		// this is a cleaning function
		BOOST_AUTO_TEST_CASE(_)
		{
			DeleteDataFile();
			BOOST_CHECK_EQUAL(1, 1);
		}

	BOOST_AUTO_TEST_SUITE_END()
	
BOOST_AUTO_TEST_SUITE_END()
