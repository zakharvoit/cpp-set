#include <algorithm>
#include <stdexcept>

#include "node.hpp"
#include "set.hpp"

static node* copy(node* t);
static node* merge(node* a, node* b);
static void delete_rec(node *a);
 
set::set() 
	: _size(0) {

	root = new node(-1);
}

set::set(set const& rhs)
	: _size(rhs._size) {

	root = copy(rhs.root);
}

set::~set() {
	delete_rec(root);
}

set& set::operator=(set const& rhs) {

	set tmp(rhs);
	delete_rec(root);

	_size = tmp._size;
	root = tmp.root;
	
	return *this;
}

size_t set::size() const {
	return _size;
}

bool set::empty() const {
	return _size == 0;
}

set::iterator set::begin() const {
	set::iterator it(root);
	while (it.current->get_left()) {
		it.current = it.current->get_left();
	}
	return it;
}

set::iterator set::end() const {
	return root;
}

set::iterator set::find(int value) const {
	node *current = root->get_left();
	node t(value, nullptr, nullptr, nullptr);
	int res;
	while (current && (res = compare(current, &t))) {
		if (res < 0) {
			current = current->get_left();
		} else {
			current = current->get_right();
		}
	}
	
	if (!current) return end();
	return current;
}

set::iterator set::insert(int value) {
	node *t;
	t = new node(value);
	
	node *current = root->get_left();
	if (!current) {
		root->set_left(t);
		++_size;
		return root->get_left();
	}
	int res;
	bool success = false;
	while ((res = compare(current, t))) {
		if (res < 0) {
			if (current->get_left()) {
				current = current->get_left();
			} else {
				success = true;
				current = current->set_left(t)->get_left();
			}
		} else {
			if (current->get_right()) {
				current = current->get_right();
			} else {
				success = true;
				current = current->set_right(t)->get_right();
			}
		}
	}
	
	if (!success) {
		delete t;
	} else {
		++_size;
	}
	
	return iterator(current);
}

set::iterator set::erase(set::iterator it) {
	--_size;
	auto parent = it.current->get_parent();
	bool left = parent->get_left() == it.current;
	auto l = it.current->get_left();
	auto r = it.current->get_right();
	delete it.current;
	it = merge(l, r);
	if (left) {
		parent->set_left(it.current);
	} else {
		parent->set_right(it.current);
	}
	if (it.current) {
		return it;
	}
	if (left) {
		return parent;
	} else {
		return ++iterator(parent);
	}
}

static node* copy(node* t) {
	if (!t) {
		return t;
	}

	node* res;
	node* l;
	node* r;
	res = new node(*t);
	try {
		l = copy(res->get_left());
	} catch (...) {
	    delete res;
		throw;
	}

	try {
		r = copy(res->get_right());
	} catch (...) {
		delete_rec(l);
		delete res;
		throw;
	}
	
	res->set_left(l);
	res->set_right(r);
	
	return res;
}

static node* merge(node* a, node* b) {
	if (!a || !b) {
		return a ? a : b;
	}
	
	if (compare(a, b) < 0) {
		a->set_left(merge(a->get_left(), b));
	} else {
		a->set_right(merge(a->get_right(), b));
	}
	
	return a;
}

static void delete_rec(node *a) {
	if (!a) return;
	delete_rec(a->get_left());
	delete_rec(a->get_right());
	delete a;
}
