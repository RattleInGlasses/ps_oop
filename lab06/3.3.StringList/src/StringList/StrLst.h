#pragma once
#include <memory>
#include <string>
#include <iterator>
class CStrLst
{
public:
	CStrLst();
	~CStrLst();

	struct iterator;
	struct const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	iterator begin();
	const_iterator begin() const;
	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;
	iterator end();
	const_iterator end() const;
	reverse_iterator rend();
	const_reverse_iterator rend() const;
	void Insert(std::string const &, iterator const &);
	void Delete(iterator const &pos);

private:
	struct StrLstElem;
	typedef std::shared_ptr<StrLstElem> ElementPointer;
	typedef std::shared_ptr<const StrLstElem> ConstElementPointer;
	struct StrLstElem
	{
		StrLstElem() {};
		StrLstElem(std::string const &initData, ElementPointer const &initNext, ElementPointer const &initPrev);
		std::string data;
		ElementPointer next;
		ElementPointer prev;
	};

	ElementPointer m_pEnd;
	ElementPointer m_pBegin;

	static ElementPointer MakeNewElement();
	static ElementPointer MakeNewElement(std::string const &initData, CStrLst::ElementPointer const &initNext, CStrLst::ElementPointer const &initPrev);
public:
	struct iterator : std::iterator<std::bidirectional_iterator_tag, StrLstElem>
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

		friend class CStrLst;
	};
	struct const_iterator : std::iterator<std::bidirectional_iterator_tag, StrLstElem>
	{
	public:
		const_iterator() {};
		const_iterator(ConstElementPointer const &);
		bool operator ==(const_iterator const &) const;
		bool operator !=(const_iterator const &) const;
		const_iterator& operator ++();
		const_iterator const operator ++(int);
		const_iterator& operator --();
		const_iterator const operator --(int);
		std::string const& operator *();
	private:
		ConstElementPointer m_pData;
	};
};
