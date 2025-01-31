#include <iostream>
#include <string>
#include "main.h"

void searchContact(string& searchName) {
    //tìm kiếm liên lạc theo tên - Trọng
    string Relation[6] = {"Gia Dinh","Ban be","Thay/ Co","Dong nghiep","Khac"}; 
    //flag
    bool found = false;
    for (const auto& contact : storeContacts) {
        string checkName = contact.name;
        checkName.erase(remove(checkName.begin(), checkName.end(), ' '), checkName.end());
        searchName.erase(remove(searchName.begin(), searchName.end(), ' '), searchName.end());
        if (toLowerCase(checkName) == toLowerCase(searchName)) {
            cout << "Ten: " << contact.name << endl 
                 << "So Dien Thoai: " << contact.number << endl
                 << "Moi quan he: " << Relation[contact.relation-1] << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Khong tim thay lien he!" << endl;
    }
}
