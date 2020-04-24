#pragma once
#include "KeyHash.h"
#include "HashMapNode.h"

template <typename K, typename V, size_t tableSize, typename KH = KeyHash<K, tableSize>>
class HashMap
{
private: // members
	HashMapNode<K, V>* table[tableSize];
	KH KeyHashFunction;

public: // constructor/destructor
	HashMap(void):
		table(),
		KeyHashFunction()
	{/*empty*/ }

	~HashMap() // delete all nodes
	{
		cout << "ATTENTION: Deleting the hash table!" << endl;
		for (auto i = 0; i < tableSize; i++)
		{
			HashMapNode<K, V>* thisNode = table[i];

			while (thisNode != nullptr)
			{
				HashMapNode<K, V>* previousNode = thisNode;
				thisNode = thisNode->getNextNode();
				delete previousNode;
			}
			table[i] = nullptr;
		}
	}
public: // member functions
	bool nodeLookup(const K& key, V& value)
	{
		unsigned long hashValue = KeyHashFunction(key);
		HashMapNode<K, V>* thisNode = table[hashValue];
		auto nodeFound(false);

		while (thisNode != nullptr)
		{
			if (thisNode->getKey() == key)
			{
				value = thisNode->getValue();
				nodeFound = true;
			}
			thisNode = thisNode->getNextNode();
		}
		return nodeFound;
	}

	void nodeInsert(const K& key, const V& value)
	{
		unsigned long hashValue = KeyHashFunction(key);
		HashMapNode<K, V>* previousNode = nullptr;
		HashMapNode<K, V>* thisNode = table[hashValue];

		while ((thisNode != nullptr) && (thisNode->getKey() != key))
		{
			previousNode = thisNode;
			thisNode = thisNode->getNextNode();
		}

		if (thisNode == nullptr)
		{
			thisNode = new HashMapNode <K, V> (key, value);

			if (previousNode == nullptr)
			{
				table[hashValue] = thisNode;
			}
			else
			{
				previousNode->setNextNode(thisNode);

			}
		}
		else
		{
			thisNode->setValue(value);
		}
	}

	void remove(const K& key)
	{
		unsigned long hashValue = KeyHashFunction(key);
		HashMapNode<K, V>* previousNode = nullptr;
		HashMapNode<K, V>* thisNode = table[hashValue];

		while ((thisNode != nullptr) && (thisNode->getKey() != key))
		{
			previousNode = thisNode;
			thisNode = thisNode->getNextNode();
			cout << "ATTENTION: Tried to delete an node with the key: " << key << " that does not exist" << endl;
		}

		if (thisNode == nullptr)
		{
			return;
		}
		else
		{
			if (previousNode == nullptr)
			{
				table[hashValue] = thisNode->getNextNode();
			}
			else
			{
				previousNode->setNextNode(thisNode->getNextNode());
			}
			delete thisNode;
		}
	}

	void printHashTable()
	{
		cout << "Start printing table..." << endl;
		for (auto i = 0; i < tableSize; i++)
		{
			if (table[i] == nullptr)
			{
				cout << "[" << i << "] :";
				cout << " Empty Bucket" << endl;
			}
			else
			{
				cout << "[" << i << "] :";
				HashMapNode<K, V>* thisNode = table[i];
				while (thisNode != nullptr)
				{
					cout << " - " << thisNode->getValue();
					thisNode = thisNode->getNextNode();
				}
				cout << endl;
			}
		}
		cout << "Table End..." << endl;
	}
};