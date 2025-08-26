#include <iostream>
#include "Inventory.hpp"

using namespace std;

int main()
{
    Inventory<Item> inv(2);
    inv.AddItem(Item{ "포션", 30 });
    inv.AddItem(Item{ "해독제", 20 });
    inv.AddItem(Item{ "롱소드", 120 }); // capacity 자동 2배 확장

    cout << "용량: " << inv.GetCapacity() << ", 개수: " << inv.GetSize() << endl;
    inv.PrintAllItems();

    inv.SortItems();
    cout << endl << "[정렬 진행 ......]" << endl;
    cout << endl << "[정렬 현황 (가격 오름차순)]" << endl;
    inv.PrintAllItems();

    inv.RemoveLastItem();
    cout << endl << "[마지막 아이템 삭제 진행 ...]" << endl;
    cout << endl << "[삭제 후 현황: 용량: " << inv.GetCapacity() << ", 개수: " << inv.GetSize() << "]" << endl;
    inv.PrintAllItems();

    cout << endl << "[인벤토리 복사 진행 ]" << endl;
    Inventory<Item> copy(inv); // 새 인벤토리 생성 및 인벤토리 복사 
  
    cout << endl << "[ 기존 인벤토리 : ]" << endl;
    cout << "용량: " << inv.GetCapacity() << ", 개수: " << inv.GetSize() << endl;
    inv.PrintAllItems();

    cout << endl << "[ 복사된 인벤토리 : ]" << endl;
    cout << "용량: " << copy.GetCapacity() << ", 개수: " << copy.GetSize() << endl;
    copy.PrintAllItems();
    

    cout << endl << "[ 새로운 인벤토리 생성 ]" << endl;
    Inventory<Item> other(1);
    cout << endl << "[ 새 인벤토리 현황 : ]" << endl;
    cout << "용량: " << other.GetCapacity() << ", 개수: " << other.GetSize() << endl;
    other.PrintAllItems();

    cout << endl << "[ 새로운 인벤토리에 기존 인벤토리 복사 ]" << endl;
    other.Assign(inv);

    cout << endl << "[ 새 인벤토리 현황 : ]" << endl;
    cout << "용량: " << other.GetCapacity() << ", 개수: " << other.GetSize() << endl;
    other.PrintAllItems();

    return 0;
}


