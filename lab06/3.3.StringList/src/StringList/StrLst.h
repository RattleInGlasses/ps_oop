#pragma once
#include <memory>
#include <string>
class CStrLst
{
public:
	CStrLst();
	~CStrLst();

	struct iterator;
	iterator begin() const;
	iterator end() const;
	void Insert(std::string const &, iterator &);
	void Delete(iterator &pos);

private:
	struct StrLstElem;
	typedef std::shared_ptr<StrLstElem> ElementPointer;
	struct StrLstElem
	{
		std::string data;
		ElementPointer next;
		ElementPointer prev;
	};

	ElementPointer m_pEnd;
	ElementPointer m_pBegin;

public:
	struct iterator
	{
	public:
		iterator() {};
		iterator(ElementPointer const &);
		bool operator ==(iterator const &) const;
		bool operator !=(iterator const &) const;
		iterator& operator ++();
		iterator const operator ++(int);
		iterator& operator --();
		iterator const operator --(int);
		std::string& operator *();
	private:
		ElementPointer m_pData;

		friend void CStrLst::Insert(std::string const &, iterator &);
		friend void CStrLst::Delete(iterator &);
		friend CStrLst::~CStrLst();
	};
};
