#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "main.h"

void changeInformation(const string& oldNum, string& newName, string& newNumber, int& newRelation) {
    //thay đổi thông tin theo số điện thoại - Toàn
    ifstream file("/Users/user/Documents/SimpleContacts_/Contacts_project/clone_project/Source/Data.txt");
    if (!file.is_open()) {
        cerr << "ERROR: Khong the mo file!" << endl;
        return;
    }

    vector<string> updatedLines;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string name, number; 
        int relation;

        getline(ss, name, ',');
        getline(ss, number, ',');
        ss >> relation;

        // Xoa khoang trang
        number.erase(remove(number.begin(), number.end(), ' '), number.end());
        //neu tim thay so dien thoai thi doi thong tin
        if (number == oldNum) {
            updatedLines.push_back(newName + "," + newNumber + "," + to_string(newRelation));
        } else {
            updatedLines.push_back(line);
        }
    }

    file.close();


    // Ghi lai du lieu

    ofstream outfile("/Users/user/Documents/SimpleContacts_/Contacts_project/clone_project/Source/Data.txt", ios::trunc);
    if (!outfile.is_open()) {
        cerr << "ERROR: Loi Khong the mo file" << endl;
        return;
    }

    for (const auto& updatedLine : updatedLines) {
        outfile << updatedLine << endl;
    }

    outfile.close();
    cout << "Da cap nhat thanh cong" << endl;

    Update();
}
