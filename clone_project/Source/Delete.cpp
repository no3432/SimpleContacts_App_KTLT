#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "main.h"

void deleteContact(string& deleteName) {
    //xoá liên lạc - Trí
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
        name.erase(remove(name.begin(), name.end(), ' '), name.end());
        deleteName.erase(remove(deleteName.begin(), deleteName.end(), ' '), deleteName.end());
        //neu khong tim thay ten de xoa thi giu nguyen
        if (toLowerCase(deleteName) != toLowerCase(name)) {
            updatedLines.push_back(line);
        }
    }

    file.close();

    // Ghi lai du lieu
    ofstream outfile("/Users/user/Documents/SimpleContacts_/Contacts_project/clone_project/Source/Data.txt");
    if (!outfile.is_open()) {
        cerr << "ERROR: Loi Khong the mo file" << endl;
        return;
    }

    for (const auto& updatedLine : updatedLines) {
        outfile << updatedLine << endl;
    }

    outfile.close();
    cout << "Da xoa thanh cong" << endl;

    Update();
}
