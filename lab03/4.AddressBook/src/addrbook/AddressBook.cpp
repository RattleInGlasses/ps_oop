#include "stdafx.h"
#include "AddressBook.h"

using namespace std;
using namespace boost;

namespace
{	
	// Read from file functions

	vector<string> ConstructVectorWithoutEmptyLines(vector<string> const &lines)
	{
		vector<string> result;
		copy_if(lines.begin(), lines.end(), back_inserter(result), [](string const &str){
			return (!str.empty()) ? true : false;
		});
		return result;
	}

	template <typename T>
	boost::optional<T> ReadFromLine(string const &line)
	{
		T result;
		istringstream lineStream(line);
		if (lineStream >> result)
		{
			return result;
		}
		return boost::none;
	}

	vector<string> SplitBySeparator(string const &line, escaped_list_separator<char> const &separator = escaped_list_separator<char>())
	{
		tokenizer<escaped_list_separator<char>> tok(line, separator);
		vector<string> splitted;
		copy(tok.begin(), tok.end(), back_inserter(splitted));
		return splitted;
	}
	
	vector<string> SplitMainLine(string const &line)
	{
		return SplitBySeparator(line);
	}

	vector<string> SplitSubLine(string const &line)
	{
		auto separator = escaped_list_separator<char>('\\', ';', '\"');
		return SplitBySeparator(line, separator);
	}

	CPostAddress ConstructAddressFromLines(vector<string> const &lines)
	{
		CPostAddress result;
		if (lines.size() == 4)
		{
			result.SetCity(lines.at(0));
			result.SetStreet(lines.at(1));
			result.SetHouse(lines.at(2));
			if (auto apartment = ReadFromLine<unsigned>(lines.at(3)))
			{
				result.SetApartment(*apartment);
			}
		}

		return result;
	}

	boost::optional<CSubscriber> ConstructSubscriberFromLines(vector<string> const &lines)
	{
		if (lines.size() == 4)
		{
			string name = lines.at(0);
			CPostAddress address = ConstructAddressFromLines(SplitSubLine(lines.at(1)));
			vector<string> phones = ConstructVectorWithoutEmptyLines(SplitSubLine(lines.at(2)));
			vector<string> emails = ConstructVectorWithoutEmptyLines(SplitSubLine(lines.at(3)));
			return CSubscriber(name, address, phones, emails);
		}
		return boost::none;
	}


	// Write to file functions

	string EscapeString(string const &str)
	{
		string escapedString;
		for (auto ch : str)
		{
			if (ch == '\"')
			{
				escapedString += "\\\"";
			}
			else if ((ch == ',') || (ch == ';'))
			{
				((escapedString += "\"") += ch) += "\"";
			}
			else
			{
				escapedString += ch;
			}
		}
		return escapedString;
	}

	void WriteVector(ostream &ost, vector<string> const &v)
	{
		for (size_t i = 0; i < v.size(); ++i)
		{
			ost << EscapeString(v.at(i));
			if (i < (v.size() - 1))
			{
				ost << ";";
			}
		}
	}

	void WriteAddress(ostream &ost, CPostAddress const &address)
	{
		ost << EscapeString(address.GetCity()) << ";"
			<< EscapeString(address.GetStreet()) << ";"
			<< EscapeString(address.GetHouse()) << ";"
			<< address.GetApartment();
	}

	void WriteString(ostream &ost, string const &str)
	{
		ost << str;
	}

	void WriteSubscriber(ostream &ost, CSubscriber const &subscriber)
	{
		WriteString(ost, EscapeString(subscriber.GetName()));
		ost << ",";
		WriteAddress(ost, subscriber.GetAddress());
		ost << ",";
		WriteVector(ost, subscriber.GetPhones());
		ost << ",";
		WriteVector(ost, subscriber.GetEmails());
		ost << endl;
	}
}


void CAddressBook::LoadSubsribers(string const &fileName)
{
	ifstream ifs(fileName);
	if (ifs.is_open())
	{
		string line;
		vector<string> splitted;
		while (getline(ifs, line))
		{
			if (auto subscriber = ConstructSubscriberFromLines(SplitMainLine(line)))
			{
				AddSubscriber(*subscriber);
			}
		}
	}
}


void CAddressBook::SaveSubsribers(string const &fileName) const
{
	ofstream ofs(fileName);
	if (ofs.is_open())
	{
		for (auto &subscriber : m_subscribers)
		{
			WriteSubscriber(ofs, subscriber);
		}
	}
}


void CAddressBook::AddSubscriber(CSubscriber const& subscriber)
{
	m_subscribers.push_back(subscriber);
}


void CAddressBook::DeleteSubscriber(size_t index)
{
	assert(index < m_subscribers.size());
	m_subscribers.erase(m_subscribers.begin() + index);
}


CSubscriber &CAddressBook::operator [](size_t index)
{
	return m_subscribers.at(index);
}


CSubscriber const &CAddressBook::operator [](size_t index) const
{
	return m_subscribers.at(index);
}


vector<size_t> CAddressBook::FindSubscribers(string const &name, CPostAddress const &address, vector<string> const &phones, vector<string> const &emails) const
{
	vector<size_t> result;
	for (size_t i = 0; i < m_subscribers.size(); ++i)
	{
		if (m_subscribers.at(i).Match(name, address, phones, emails))
		{
			result.push_back(i);
		}
	}

	return result;
}

