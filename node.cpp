#include "node.hpp"

node::node(int value, node* left, node *right, node* parent)
	: value(value)
	, left(left)
	, right(right) 
	, parent(parent) {}

node::node(int value) 
	: node(value, nullptr, nullptr, nullptr) {}

node::node(node const& rhs)
	: node(rhs.value, rhs.left, rhs.right, rhs.parent) {}

node::~node() {
}

int compare(node const* a, node const* b) {
	return b->get_value() - a->get_value();
}

int node::get_value() const {
	return value;
}

node* node::get_left() const {
	return left;
}

node* node::get_right() const {
	return right;
}

node* node::get_parent() const {
	return parent;
}
	
node* node::set_left(node* left) {
	if (left) left->parent = this;
	this->left = left;
	return this;
}

node* node::set_right(node* right) {
	if (right) right->parent = this;
	this->right = right;
	return this;
}
