#pragma once
#include "Subscriber.h"
#include "Name.h"
#include "PostAddress.h"
#include <vector>
#include <xrefwrap>
class CAddressBook
{
public:
	void LoadSubsribers(std::string const &fileName);
	void SaveSubsribers(std::string const &fileName) const;
	
	void AddSubscriber(CSubscriber const&);
	void DeleteSubscriber(size_t);
	CSubscriber &operator [](size_t);
	CSubscriber const &operator [](size_t) const;

	std::vector<size_t> FindSubscribers(std::string const &name = "",
		CPostAddress const &address = CPostAddress(),
		std::vector<std::string> const &phones = {},
		std::vector<std::string> const &emails = {}) const;
private:
	std::vector<CSubscriber> m_subscribers;
};

