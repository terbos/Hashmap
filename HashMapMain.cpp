#include "HashMap.h"
#include <string>
#include <assert.h>

const int TABLE_SIZE = 5;

struct MyKeyHash
{
	unsigned long operator()(const int& k) const
	{
		return k % TABLE_SIZE;
	}
};

struct MyStringKeyHash
{
	unsigned long operator()(const string& k) const
	{
		int charSum = 0;
		for (char c : k)
		{
			if ((c > 64 || c < 95) && (c > 96 || c < 123))
			{
				charSum += c;
			}
		}
		return charSum % TABLE_SIZE;
	}
};

int main(void)
{
	HashMap<int, string, TABLE_SIZE, MyKeyHash> carBrands;

	carBrands.printHashTable();

	carBrands.nodeInsert(1, "Vauxhall");
	carBrands.nodeInsert(2, "Ford");
	carBrands.nodeInsert(3, "Kia");

	carBrands.printHashTable();

	carBrands.nodeInsert(4, "BMW");
	carBrands.nodeInsert(5, "Mercedes");
	carBrands.nodeInsert(6, "Ferrari");
	carBrands.nodeInsert(7, "Corvette");
	carBrands.nodeInsert(8, "Chevrolet");
	carBrands.nodeInsert(9, "Fiat");
	carBrands.nodeInsert(10, "Renault");
	carBrands.nodeInsert(11, "Skoda");
	carBrands.nodeInsert(12, "Peugeot");

	carBrands.printHashTable();
	carBrands.remove(4);

	carBrands.printHashTable();
	carBrands.remove(4);

	carBrands.remove(19);
	carBrands.printHashTable();

	
	string value;
	bool result = carBrands.nodeLookup(9, value);
	assert(result);
	carBrands.remove(9);
	result = carBrands.nodeLookup(9, value);
	// this should fail as 9 has been deleted and is not an existing key
	//assert(("ERROR: Node was NOT found in the lookup!", result)); 
	result = carBrands.nodeLookup(5, value);
	assert(value == "Mercedes");
	// this shoudl fail as Vauxhall is a not a value associated with key 5
	//assert(value == "Vauxhall");

	carBrands.remove(2);
	result = carBrands.nodeLookup(2, value);
	// this should succeed as the result should be false after we remove node with key = 2
	assert(!result);


	cout << "=========ANOTHER TEST=================" << endl;

	HashMap<string, int, TABLE_SIZE, MyStringKeyHash> personalNin;
	personalNin.printHashTable();
	personalNin.nodeInsert("Yiannis", 1984554);
	personalNin.nodeInsert("Mike", 19443554);
	personalNin.nodeInsert("Donna", 19845154);
	personalNin.nodeInsert("Julie", 1984999);

	personalNin.printHashTable();

	personalNin.nodeInsert("April", 1324554);
	personalNin.nodeInsert("Lucky", 2224554);
	personalNin.nodeInsert("Sandro", 1114554);
	personalNin.nodeInsert("Jamie", 9994554);
	personalNin.nodeInsert("Leon", 1114554);
	personalNin.nodeInsert("Lucy", 1144554);
	personalNin.nodeInsert("Andy", 1444554);
	personalNin.printHashTable();

	personalNin.remove("Leon");
	personalNin.remove("Yiannis");
	personalNin.remove("Donna");
	personalNin.printHashTable();

	int nin;
	bool result2 = personalNin.nodeLookup("Lucky", nin);
	assert(result2);

	result2 = personalNin.nodeLookup("Jamie", nin);
	assert(result2);
	personalNin.remove("Jamie");
	result2 = personalNin.nodeLookup("Jamie", nin);
	assert(("ERROR: Node was NOT found in the lookup!", result2));
	


	return 0;
}