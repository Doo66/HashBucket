#ifndef __HASHBUCKET_H__
#define __HASHBUCKET_H__

#include <iostream>
#include <vector>

using namespace std;

template <class K, class V> 
struct HashTableNode
{
	K _key;
	V _value;
	HashTableNode<K,V>* _next;

	HashTableNode(const K& key, const V& value)
		:_key(key)
		,_value(value)
		,_next(NULL)
	{}
};

template <class K, class V>
class HashBucket
{
	typedef HashTableNode<K, V> Node;
public:
	HashBucket()
		:_size(0)
	{
		_tables.resize(_GetPrimeSize());
	}
	HashBucket(const HashBucket<K,V>& HB)
		:_size(HB._size)
	{
		this->_tables.resize(HB._tables.size());
		for(size_t i = 0; i<_tables.size(); i++)
		{
			Node* cur = HB._tables[i];
			while(cur)
			{
				Node* tmp = new Node(cur->_key, cur->_value);
				tmp->_next = _tables[i];
				_tables[i] = tmp;
				cur = cur->_next;
			}
		}
	}
	HashBucket<K,V> operator=(HashBucket<K,V> HB)
	{
		if(this != HB)
		{
			this->_tables.swap(HB._tables);
			swap(_size, HB._size)
		}
		return *this;
	}
	~HashBucket()
	{
		if(_tables.size() != 0)
		{
			for(size_t i = 0; i<_tables.size(); i++)
			{
				Node* cur = _tables[i];
				while(cur)
				{
					Node* del = cur;
					cur = cur->_next;
					delete del;
					del = NULL;
				}
			}
		}
	}
public:
	bool Insert(const K& key, const V& value)
	{
		_CheckCapacity(); //�������
		size_t index = _HashFun(key, _tables.size());
		Node* cur = _tables[index];
		while(cur)
		{
			if(cur->_value == value)
			{
				return false;
			}
			cur = cur->_next;
		}
		Node* newNode = new Node(key, value);
		//ͷ��
		newNode->_next = _tables[index];
		_tables[index] = newNode;
		_size++;	//Ԫ�ظ�������
		return true;
	}
	Node* Find(const K& key)
	{
		size_t index = _HashFun(key, _tables.size());
		Node* cur = _tables[index];
		while(cur)
		{
			if(cur->_key == key)
			{
				return cur;
			}
			cur = cur->_next;
		}
		return NULL;
	}
	bool Remove(const K& key)
	{
		size_t index = _HashFun(key, _tables.size());
		Node* cur = _tables[index];
		Node* prev = cur;
		while(cur)
		{
			prev = cur;
			if(cur->_key == key)
			{
				break;
			}
			cur = cur->_next;
		}
		if(cur)
		{
			if(cur = _tables[index])	//������ͷ
			{
				_tables[index] = cur->_next;
			}
			else
			{
				prev->_next = cur->_next;
			}
			delete cur;
			cur = NULL;
			--_size;
			return true;
		}
		return false;
	}
	void Print()
	{
		for(size_t i = 0; i<_tables.size(); i++)
		{
			Node* cur = _tables[i];
			while(cur)
			{
				printf("_tables[%d]:[%d,%d]-->",i,cur->_key,cur->_value);
				cur = cur->_next;
			}
			cout<<"Nvl."<<endl;
		}
		cout<<endl;
	}
protected:
	void _CheckCapacity()
	{
		if(_tables.size() == _size)
		{
			size_t _PrimeSize = _GetPrimeSize();
			vector<Node*> newTables;
			newTables.resize(_PrimeSize);	//����
			for(size_t i = 0; i<newTables.size(); i++)
			{
				Node* cur = _tables[i];
				while(cur)
				{
					Node* tmp = cur;
					cur = cur->_next;
					size_t index = _HashFun(tmp->_key, newTables.size());
					//ͷ��Ԫ��
					tmp->_next = newTables[index];
					newTables[index] = tmp;
				}
				_tables[i] = NULL;
			}
			this->_tables.swap(newTables);
		}
	}
	size_t _HashFun(K key, size_t capacity)
	{
		return key%capacity;
	}
	unsigned long _GetPrimeSize()
	{
		/*ѧ���о�����һ���̶ȱ����ϣ��ײ������*/
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList[_PrimeSize]=
		{
			53ul, 97ul, 193ul, 389ul, 769ul,1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
            49157ul, 98317ul, 196613ul, 393241ul, 786433ul,1572869ul, 3145739ul, 
			6291469ul, 12582917ul, 25165843ul,50331653ul, 100663319ul, 201326611ul,
			402653189ul, 805306457ul,1610612741ul, 3221225473ul, 4294967291ul
		};
		if(_tables.size() == 0)	//һ��ʼĬ������
		{
			return _PrimeSize;
		}
		size_t i = 0;
		for(i = 0; i<_tables.size(); i++)
		{
			if(_tables.size() < _PrimeList[i])	//_tables.size()
			{
				return _PrimeList[i];
			}
		}
		return _PrimeList[_PrimeSize];
	}
private:
	vector<Node*> _tables;	//��Žڵ�ı�
	size_t _size;			//���ڽڵ���Ԫ�ظ���
};


#endif
