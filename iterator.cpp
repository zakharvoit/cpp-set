#include <stdexcept>

#include "node.hpp"
#include "set.hpp"

set::iterator::iterator() 
	: current(nullptr) {}

set::iterator::iterator(node const* t)
	: current((node*)t) {}

set::iterator& set::iterator::operator++() {
	if (current->get_right()) {
		current = current->get_right();
		while (current->get_left()) {
			current = current->get_left();
		}
	} else {
		while (current->get_parent()->get_right() == current) {
			current = current->get_parent();
		}
			current = current->get_parent();
	}
	return *this;
}

set::iterator set::iterator::operator++(int) {
	auto buffer = *this;
	++(*this);
	return buffer;
}

set::iterator& set::iterator::operator--() {
	if (current->get_left()) {
		current = current->get_left();
		while (current->get_right()) {
			current = current->get_right();
		}
	} else {
		while (current->get_parent()->get_left() == current) {
			current = current->get_parent();
		}
		current = current->get_parent();
	}
	return *this;
}

set::iterator set::iterator::operator--(int) {
	auto buffer = *this;
	--(*this);
	return buffer;
}

int set::iterator::operator*() const {
	return current->get_value();
}

bool set::iterator::operator==(set::iterator const& rhs) const {
	return current == rhs.current;
}

bool set::iterator::operator!=(set::iterator const& rhs) const {
	return current != rhs.current;
}
