#include "stdafx.h"
#include "AddressBook.h"

using namespace std;

namespace
{
	bool SubscriberHasData(CSubscriber const &subscriber,
		string const &name, 
		CPostAddress const &address, 
		vector<string> const &phones, 
		vector<string> const &emails)
	{
		return ((subscriber.GetName() == name)
			&& (subscriber.GetAddress() == address)
			&& (subscriber.HasPhones(phones))
			&& (subscriber.HasEmails(emails)));
	}
}


void CAddressBook::LoadSubsribers(string const &fileName)
{

}


void CAddressBook::SaveSubsribers(string const &fileName) const
{

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


void CAddressBook::ChangeSubscriber(size_t index, CSubscriber const &newValue)
{
	m_subscribers.at(index) = newValue;
}


size_t CAddressBook::GetSubscribersCount() const
{
	return m_subscribers.size();
}


CSubscriber &CAddressBook::operator [](size_t index)
{
	return m_subscribers.at(index);
}


CSubscriber const &CAddressBook::operator [](size_t index) const
{
	return m_subscribers.at(index);
}


CAddressBook::CSubscriberReferenceList CAddressBook::FindSubscribers(string const &name, CPostAddress const &address, vector<string> const &phones, vector<string> const &emails)
{
	CSubscriberReferenceList result;
	copy_if(m_subscribers.begin(), m_subscribers.end(), back_inserter(result), [&](CSubscriber const &subscriber){
		return SubscriberHasData(subscriber, name, address, phones, emails);
	});
	return result;
}


// CSubscribersReferenceList

void CAddressBook::CSubscriberReferenceList::push_back(CSubscriber &value)
{
	m_data.push_back(value);
}


size_t CAddressBook::CSubscriberReferenceList::size() const
{
	return m_data.size();
}


CSubscriber &CAddressBook::CSubscriberReferenceList::operator [](size_t index)
{
	return m_data.at(index).get();
}


CSubscriber const &CAddressBook::CSubscriberReferenceList::operator [](size_t index) const
{
	return m_data.at(index).get();
}
