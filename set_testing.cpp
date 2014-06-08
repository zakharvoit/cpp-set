#include <algorithm>
#include <cstdlib>
#include <set>
#include <gtest/gtest.h>

#include "set.hpp"

TEST(correctness, 3_4_5)
{
	set a;
	std::set <int> b;
	a.insert(5);
	a.insert(3);
	a.insert(4);
	b.insert(5);
	b.insert(3);
	b.insert(4);
	
	auto a_it = a.begin();
	auto b_it = b.begin();
	for (; a_it != a.end() && b_it != b.end(); ++a_it, ++b_it) {
		ASSERT_EQ(*a_it, *b_it);
	}
}

TEST(correctness, iter_down)
{
	set a;
	std::set <int> b;
	a.insert(5);
	a.insert(3);
	a.insert(4);
	b.insert(5);
	b.insert(3);
	b.insert(4);
	
	auto a_it = a.end();
	auto b_it = b.end();
	
	do {
		--a_it;
		--b_it;
		ASSERT_EQ(*a_it, *b_it);
	} while (a_it != a.begin() || b_it != b.begin());
}

TEST(correctness, find)
{
	set a;
	a.insert(5);
	a.insert(3);
	a.insert(4);
	
	ASSERT_EQ(a.find(6), a.end());
	ASSERT_EQ(a.find(-120), a.end());
	ASSERT_EQ(*a.find(5), 5);
	ASSERT_EQ(*a.find(3), 3);
	ASSERT_EQ(*a.find(4), 4);
}

TEST(correctness, erase)
{
	set a;
	a.insert(5);
	a.insert(3);
	a.insert(4);
	a.insert(10);
	a.insert(20);
	a.insert(30);
	
	ASSERT_EQ(*a.erase(a.find(10)), 20);
	ASSERT_EQ(*a.erase(a.find(20)), 30);
	ASSERT_EQ(a.erase(a.find(30)), a.end());
	ASSERT_EQ(*a.erase(a.find(3)), 4);
	ASSERT_EQ(a.find(3), a.end());
	ASSERT_EQ(*a.erase(a.find(4)), 5);
	ASSERT_EQ(a.find(4), a.end());
	ASSERT_EQ(a.erase(a.find(5)), a.end());
	ASSERT_EQ(a.find(5), a.end());
}

TEST(correctness, size)
{
	set a;
	ASSERT_EQ(a.size(), 0);
	a.insert(5);
	ASSERT_EQ(a.size(), 1);
	a.insert(3);
	ASSERT_EQ(a.size(), 2);
	a.insert(4);
	ASSERT_EQ(a.size(), 3);
}

TEST(correctness, random)
{
	std::set<int> a;
	set b;
	
	for (int i = 0; i < 10000; i++) {
		if (a.empty() || rand() % 2 || rand() % 2) {
			int x = rand();
			a.insert(x);
			b.insert(x);
		} else {
			int pos = rand() % a.size();
			auto it = a.begin();
			for (int j = 0; j < pos; j++) {
				++it;
			}
			int x = *it;
			a.erase(a.find(x));
			b.erase(b.find(x));
		}
		auto a_it = a.begin();
		auto b_it = b.begin();
		for (; a_it != a.end() && b_it != b.end(); ++a_it, ++b_it) {
			ASSERT_EQ(*a_it, *b_it);
		}	
	}
}
