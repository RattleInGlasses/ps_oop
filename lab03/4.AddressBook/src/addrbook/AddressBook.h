#pragma once
#include "Subscriber.h"
#include "Name.h"
#include "PostAddress.h"
#include <vector>
#include <xrefwrap>
class CAddressBook
{
public:
	class CSubscriberReferenceList
	{
	public:
		typedef std::reference_wrapper<CSubscriber> value_type;
	public:
		void push_back(CSubscriber &);
		size_t size() const;
		CSubscriber &operator [](size_t);
		CSubscriber const &operator [](size_t) const;
	private:
		std::vector<value_type> m_data;
	};
public:
	void LoadSubsribers(std::string const &fileName);
	void SaveSubsribers(std::string const &fileName) const;
	
	void AddSubscriber(CSubscriber const&);
	void DeleteSubscriber(size_t);
	void ChangeSubscriber(size_t, CSubscriber const &);
	size_t GetSubscribersCount() const;
	CSubscriber &operator [](size_t);
	CSubscriber const &operator [](size_t) const;

	CSubscriberReferenceList FindSubscribers(std::string const &name = "",
		CPostAddress const &address = CPostAddress(),
		std::vector<std::string> const &phones = {},
		std::vector<std::string> const &emails = {});
private:
	std::vector<CSubscriber> m_subscribers;
};

