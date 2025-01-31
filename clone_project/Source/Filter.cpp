#include <iostream>
#include <vector>
#include <algorithm>
#include "main.h"

void sortByRelation(int& relationShip) {
    //lọc liên lạc theo mối quan hệ - Toạ
    string Relation[6] = {"Gia dinh", "Ban be", "Thay/ Co", "Dong Nghiep", "Khac"};
    vector<Contacts> filteredContacts;
    
    for (const auto& contact : storeContacts) {
        if (contact.relation == relationShip) {
            filteredContacts.push_back(contact);
        }
    }

    cout << "Danh sach lien lac theo moi quan he " << Relation[relationShip-1] << " : " << endl;
        cout << "-------------------------------" << endl;
    for(int i = 0; i < storeContacts.size(); i++) {
        if(storeContacts[i].relation == relationShip) {
            cout << "Ten: " << storeContacts[i].name << endl 
                << "So Dien Thoai: " << storeContacts[i].number << endl
                << "Moi quan he: " << Relation[storeContacts[i].relation-1] << endl
                << "-------------------------------" << endl;
        }
    }
}
