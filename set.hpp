#ifndef SET_HPP
#define SET_HPP

#include <stddef.h>
#include <memory>

#include "node.hpp"

struct set {
	set();
	set(set const&);
	set& operator=(set const&);
	~set();
	
	size_t size() const;
	bool empty() const;

	struct iterator;
	iterator begin() const;
	iterator end() const;
	
	iterator find(int value) const;
	iterator insert(int value);
	iterator erase(iterator it);

private:
	node* root;	
	size_t _size;
};

struct set::iterator {
	iterator();
	iterator& operator++();
	iterator operator++(int);
	iterator& operator--();
	iterator operator--(int);
	int operator*() const;

    bool operator==(iterator const& rhs) const;
    bool operator!=(iterator const& rhs) const;
	
	friend set::iterator set::begin() const;
	friend set::iterator set::end() const;
	friend set::iterator set::find(int value) const;
	friend set::iterator set::insert(int value);
	friend set::iterator set::erase(iterator it);
private:
	iterator(node const*);
	node* current;
};

#endif // SET_HPP
