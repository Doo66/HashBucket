#include "HashBucket.h"

void TestHashBucket()
{
	HashBucket<int,int> ht;
	ht.Insert(89,89);
	ht.Insert(18,18);
	ht.Insert(49,49);
	ht.Insert(58,58);
	ht.Insert(9,9);
	ht.Print();
	HashBucket<int, int> ht1(ht);
	ht1.Print();
	cout<<"Remove?"<<ht.Remove(9)<<endl;
	HashBucket<int, int> ht2 = ht1;
	ht2.Print();
	cout<<"Find?"<<ht.Find(9)<<endl;
	ht.Print();
}

int main()
{
	TestHashBucket();
	return 0;
}

