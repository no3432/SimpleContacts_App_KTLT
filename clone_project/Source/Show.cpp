// contacts.cpp
#include <iostream>
#include <string>
#include "main.h"

void showAllContacts() {
    if (storeContacts.empty()) {
        cout << "Danh ba trong!" << endl;
    } else {
        string Relation[6] = {"Gia Dinh","Ban be","Thay/ Co","Dong nghiep","Khac"};
        cout << "-------------------------------" << endl;
    for(int i = 0; i < storeContacts.size(); i++) {
        cout << "Ten: " << storeContacts[i].name << endl 
             << "So Dien Thoai: " << storeContacts[i].number << endl
             << "Moi quan he: " << Relation[storeContacts[i].relation-1] << endl
             << "-------------------------------" << endl;
    }
}
}
