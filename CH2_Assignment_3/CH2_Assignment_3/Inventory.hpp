#pragma once
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// ���� ������ Ŭ����
class Item
{
private:
	std::string name_;
	int price_;

public:
	Item() : name_(), price_(0) {}
	Item(string name, int price) : name_(name), price_(price) {}

	void PrintInfo() const { cout << "[�̸�: " << name_ << ", ����: " << price_ << "G]" << endl; }

	int GetPrice() const { return price_; }
};

//�� Item ��ü�� �޾� ������ �������� � ���� ���� �;� �ϴ��� �Ǵ�
bool compareItemsByPrice(const Item& a, const Item& b) { return a.GetPrice() < b.GetPrice(); }

// ���ø� Ŭ������ �̿��� Inventory ����
template <typename T>
class Inventory
{
private:
	T* pItems_;		// ������ ��ü ������ (���� �迭)
	int capacity_;	// �κ��丮 �ִ� �뷮
	int size_;		// ���� ������ ����

public:
	// (�ʼ� ���) ������
	Inventory(int capacity = 10) // �� ���� ���� �� �⺻ �� 10 ����
		: pItems_(nullptr), capacity_(capacity), size_(0)
	{
		if (capacity_ <= 0) { capacity_ = 1; } // 0������ ���� ���� ��, �ּ� �뷮 1 ����
		pItems_ = new T[capacity_]; // ���� ��, ���� �Ҵ����� Heap �޸𸮿� ���� 
	}
	// (���� ���) ���� ������ (���� ���� ����)
	Inventory(const Inventory<T>& other) // �������� ���� Ȥ�� ���� �� ȣ�� (������ ���� ���� �� ���ο� �޸� �Ҵ�)
		: pItems_(nullptr), capacity_(other.capacity_), size_(other.size_)
	{
		pItems_ = new T[capacity_];

		for (int i = 0; i < size_; i++) { pItems_[i] = other.pItems_[i]; }

		cout << "[***�κ��丮 ���� �Ϸ�***]" << endl;
	}
	// �Ҹ���
	~Inventory()
	{
		delete[] pItems_; // �޸� ���� 
		pItems_ = nullptr; // ������ ���� �޸� ���� �� ������ �ʱ�ȭ
		capacity_ = 0; // �ʱ�ȭ
		size_ = 0; // �ʱ�ȭ
	}

	// �ʼ� ���
	void AddItem(const T& item)
	{
		// �κ��丮�� �� �� ��, ���� Capacity �뷮�� 2��� Ȯ��
		if (size_ >= capacity_)
		{
			int newCapacity = (capacity_ <= 0) ? 1 : (capacity_ * 2);
			Resize(newCapacity); // �뷮 Ȯ��
		}
		// �뷮 ���� �������� ���� ��, �߰� �� ������ ����
		pItems_[size_] = item;
		++size_;
	}

	// �κ��丮 �� ���� �������� �߰��� ������ ����
	void RemoveLastItem()
	{
		// �κ��丮�� ����ִ� ���
		if (size_ == 0)
		{
			cout << "[***�κ��丮�� ����ֽ��ϴ�.***]" << endl;
			return;
		}
		// ������ ������ ���� �ε����� �ٿ� �ش� �����ۿ� ���� ���ٸ� ����.
		size_--;
	}

	// �κ��丮 �� ����� ������ ���� ��ȯ
	int GetSize() const { return size_; }

	// �κ��丮 �� �ִ� ���� �뷮 ��ȯ
	int GetCapacity() const { return capacity_; }

	// �κ��丮 �� ��� ������ ���� ���
	void PrintAllItems() const
	{
		// �κ��丮�� ����ִ� ���
		if (size_ == 0)
		{
			cout << "[***�κ��丮�� �������.***]" << endl;
			return;
		}
		// �κ��丮 �� �� ������ ��ü�� PrintInfo() ��� �Լ��� ȣ��
		for (int i = 0; i < size_; i++) { pItems_[i].PrintInfo(); }
	}

	// ���� ���
	void Assign(const Inventory<T>& other)
	{
		if (this == &other) { return; }

		if (capacity_ < other.capacity_) { Resize(other.capacity_); }

		size_ = other.size_;
		for (int i = 0; i < size_; ++i) { pItems_[i] = other.pItems_[i]; }
	}

	void Resize(int newCapacity) // �κ��丮�� capacity�� newCapacity�� ����
	{
		if (newCapacity <= 0) { newCapacity = 1; }

		T* newArray = new T[newCapacity]; // newCapacity�� ���ο� �κ��丮 ����

		int copyCount = (size_ < newCapacity) ? size_ : newCapacity; // ������ ������ ���� 

		// ���� ������ ��� ���� �� ���ο� �κ��丮�� ����
		for (int i = 0; i < copyCount; ++i) { newArray[i] = pItems_[i]; } 

		delete[] pItems_; // ���� �뷮�� ������ �κ��丮 ����(�޸� ����)
		pItems_ = newArray; // �� �κ��丮�� ���� ������(�޸�)�� ����
		capacity_ = newCapacity; // �� �뷮
		size_ = copyCount; // �� ������ ���� 
	}

	// �κ��丮 �� ������ ���� ������ �� ����
	void SortItems()
	{
		// �κ��丮 �� �������� 1���� ���, ��ȯ(������ ����X)
		if (size_ <= 1) return; 
		// ���Լ� compareItemsByPrice()�� sort()�� ������ ����
		sort(pItems_, pItems_ + size_, compareItemsByPrice);
	}
};