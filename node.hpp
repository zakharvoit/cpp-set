#ifndef NODE_HPP
#define NODE_HPP

struct node {
	node(int value, node* left, node* right, node* parent);
	node(int value);
	node(node const& rhs);
	~node();

	int get_value() const;
	node* get_left() const;
	node* get_right() const;
	node* get_parent() const;
	
	node* set_left(node* left);
	node* set_right(node* right);

private:
	int value;
	node* left;
	node* right;
	node* parent;
};

int compare(node const* a, node const* b);

#endif // NODE_HPP
