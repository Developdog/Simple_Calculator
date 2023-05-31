#pragma once

#include "List.h"

template <typename T, class Container>

class Stack {
protected:
	Container c;

public:
	void push(const T& x) { c.push_back(x); }
	void pop() { c.pop_back(); }
	T top() const { return c.back(); }
	bool empty() const { return c.empty(); }
	unsigned int size() const { return c.size(); }
};



