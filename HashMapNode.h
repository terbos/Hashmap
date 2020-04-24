/*
Implement a hashmap including the following features:
1. Constructing a generic map with fixed table size given upfront.
2. Lookup, insertion, and deletion.
3. Standard library classes that fall under the C++ container concept are not allowed (refer to: http://en.cppreference.com/w/cpp/concept/Container)
4. Please include a main program or unit test that checks that the map works.
5. You will get bonus points for:
   - discussing a (thread-safe) table resizing strategy (do not implement this)
   - good test coverage
*/
#pragma once
#include <iostream>
using namespace std;

template <typename K, typename V>
class HashMapNode
{
private:
	K key;
	V value;
	// next bucket with the same key 
	HashMapNode* nextNode;

public:
	HashMapNode(const K& key, const V& value) :
		key(key),
		value(value),
		nextNode(nullptr)
	{ /*empty*/}

	void setValue(V value)
	{
		this->value = value;
	}

	HashMapNode* getNextNode() const
	{
		return nextNode;
	}

	void setNextNode(HashMapNode* nextNode)
	{
		this->nextNode = nextNode;
	}

	K getKey(void) const
	{
		return key;
	}

	V getValue(void) const
	{
		return value;
	}
};
