#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "main.h"

void addNewContact(string& newName, string& newNumber, int& newRelation) {
    // Thêm liên lạc mới vào vector
    storeContacts.push_back(Contacts(newName, newNumber, newRelation));
    
    // Cập nhật vào file Data.txt
    ofstream file("/Users/user/Documents/SimpleContacts_/Contacts_project/clone_project/Source/Data.txt", ios::app); 
    if (!file) {
        cerr << "ERROR: Khong the mo file!" << endl;
        return;
    }

    // Ghi thông tin liên lạc mới vào file
    file << "\n" << newName << "," << newNumber << ", " << newRelation << "\n";
    file.close(); // Đóng file sau khi ghi

    cout << "Da them lien he moi: " << newName << endl;
}

