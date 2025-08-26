#pragma once
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// 예시 아이템 클래스
class Item
{
private:
	std::string name_;
	int price_;

public:
	Item() : name_(), price_(0) {}
	Item(string name, int price) : name_(name), price_(price) {}

	void PrintInfo() const { cout << "[이름: " << name_ << ", 가격: " << price_ << "G]" << endl; }

	int GetPrice() const { return price_; }
};

//두 Item 객체를 받아 가격을 기준으로 어떤 것이 먼저 와야 하는지 판단
bool compareItemsByPrice(const Item& a, const Item& b) { return a.GetPrice() < b.GetPrice(); }

// 템플릿 클래스를 이용한 Inventory 선언
template <typename T>
class Inventory
{
private:
	T* pItems_;		// 아이템 객체 포인터 (동적 배열)
	int capacity_;	// 인벤토리 최대 용량
	int size_;		// 현재 아이템 개수

public:
	// (필수 기능) 생성자
	Inventory(int capacity = 10) // 값 전달 없을 시 기본 값 10 지정
		: pItems_(nullptr), capacity_(capacity), size_(0)
	{
		if (capacity_ <= 0) { capacity_ = 1; } // 0이하의 값이 들어올 시, 최소 용량 1 보정
		pItems_ = new T[capacity_]; // 실행 시, 동적 할당으로 Heap 메모리에 저장 
	}
	// (도전 기능) 복사 생성자 (깊은 복사 구현)
	Inventory(const Inventory<T>& other) // 아이템의 복사 혹은 대입 시 호출 (아이템 정보 보존 후 새로운 메모리 할당)
		: pItems_(nullptr), capacity_(other.capacity_), size_(other.size_)
	{
		pItems_ = new T[capacity_];

		for (int i = 0; i < size_; i++) { pItems_[i] = other.pItems_[i]; }

		cout << "[***인벤토리 복사 완료***]" << endl;
	}
	// 소멸자
	~Inventory()
	{
		delete[] pItems_; // 메모리 해제 
		pItems_ = nullptr; // 안전을 위해 메모리 해제 후 포인터 초기화
		capacity_ = 0; // 초기화
		size_ = 0; // 초기화
	}

	// 필수 기능
	void AddItem(const T& item)
	{
		// 인벤토리가 꽉 찰 시, 기존 Capacity 용량을 2배로 확장
		if (size_ >= capacity_)
		{
			int newCapacity = (capacity_ <= 0) ? 1 : (capacity_ * 2);
			Resize(newCapacity); // 용량 확장
		}
		// 용량 내에 아이템이 들어올 시, 추가 후 사이즈 증가
		pItems_[size_] = item;
		++size_;
	}

	// 인벤토리 내 가장 마지막애 추가된 아이템 제거
	void RemoveLastItem()
	{
		// 인벤토리가 비어있는 경우
		if (size_ == 0)
		{
			cout << "[***인벤토리가 비어있습니다.***]" << endl;
			return;
		}
		// 아이템 개수에 대한 인덱스를 줄여 해당 아이템에 대한 접근만 막음.
		size_--;
	}

	// 인벤토리 내 저장된 아이템 개수 반환
	int GetSize() const { return size_; }

	// 인벤토리 내 최대 저장 용량 반환
	int GetCapacity() const { return capacity_; }

	// 인벤토리 내 모든 아이템 정보 출력
	void PrintAllItems() const
	{
		// 인벤토리가 비어있는 경우
		if (size_ == 0)
		{
			cout << "[***인벤토리가 비어있음.***]" << endl;
			return;
		}
		// 인벤토리 내 각 아이템 객체의 PrintInfo() 멤버 함수를 호출
		for (int i = 0; i < size_; i++) { pItems_[i].PrintInfo(); }
	}

	// 도전 기능
	void Assign(const Inventory<T>& other)
	{
		if (this == &other) { return; }

		if (capacity_ < other.capacity_) { Resize(other.capacity_); }

		size_ = other.size_;
		for (int i = 0; i < size_; ++i) { pItems_[i] = other.pItems_[i]; }
	}

	void Resize(int newCapacity) // 인벤토리의 capacity를 newCapacity로 변경
	{
		if (newCapacity <= 0) { newCapacity = 1; }

		T* newArray = new T[newCapacity]; // newCapacity로 새로운 인벤토리 생성

		int copyCount = (size_ < newCapacity) ? size_ : newCapacity; // 복사할 아이템 개수 

		// 기존 아이템 모두 유지 및 새로운 인벤토리에 복사
		for (int i = 0; i < copyCount; ++i) { newArray[i] = pItems_[i]; } 

		delete[] pItems_; // 기존 용량이 부족한 인벤토리 삭제(메모리 해제)
		pItems_ = newArray; // 새 인벤토리를 기존 포인터(메모리)에 지정
		capacity_ = newCapacity; // 새 용량
		size_ = copyCount; // 새 아이템 개수 
	}

	// 인벤토리 내 아이템 가격 오름차 순 정렬
	void SortItems()
	{
		// 인벤토리 내 아이템이 1개일 경우, 반환(별도의 동작X)
		if (size_ <= 1) return; 
		// 비교함수 compareItemsByPrice()를 sort()에 전달해 정렬
		sort(pItems_, pItems_ + size_, compareItemsByPrice);
	}
};