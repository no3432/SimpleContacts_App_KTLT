#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <fstream>
#include<sstream>
#include "main.h"

#define NAME 20

using namespace std;

vector<Contacts> storeContacts;

//ham chuyen chuoi thanh chu thuong
string toLowerCase(const string& str) {
    string result = str;
    for (char &c : result) {
        c = tolower(c);  
    }
    return result;
}

int main() {

    updateData(); //cap nhat du lieu tu file dau vao

    char cont = 'y' ; 
    while(tolower(cont) == 'y') {

    showUI();//hien thi menu

    int choose; cin >> choose;

    while(choose < 1 || choose > 6) {
        cout << "Lua chon khong hop le!\nBan co muon tiep tuc khong? (Y/N) : " << endl;
        cin >> cont; 
        if(cont == 0) break;
        else {
            showUI();
            cin >> choose;
        }
    }
    if(tolower(cont) != 'y') break;//xet xem nguoi dung co muon tiep tuc khong
    Processing(choose);
    cout << endl << "Ban co muon tiep tuc khong? (Y/N) : ";
    cin >> cont;
    if(tolower(cont) != 'y') break;//xet xem nguoi dung co muon tiep tuc khong
    }
    return 0;
}

void updateData() {

    storeContacts = {};

    ifstream file("/Users/user/Documents/SimpleContacts_/Contacts_project/clone_project/Source/Data.txt"); //mo file dau vao
    
    if (!file) {
    cerr << "ERROR: Khong the mo file!" << endl;
    return;
}

    
    string line;
    int count = 0;
    
    // xu li tung dong
    while (getline(file, line)) {
        stringstream ss(line);
        string name, number;int relation;
        
        // Đảm bảo mỗi dòng có đủ 3 phần dữ liệu
        if (getline(ss, name, ',') && getline(ss, number, ',') && (ss >> relation)) {
            // Cập nhật dữ liệu vào vector
            storeContacts.push_back(Contacts(name, number, relation)); 
            count++;
        }
    }

    file.close();  // dong file
    cout << "--- Da cap nhat " << count << " lien he tu file dau vao! ----" << endl;

}

void showUI() {
    cout << "----------CONTACTS----------" << endl 
         << "1. Hien thi danh sach lien lac." << endl
         << "2. Them lien he moi." << endl
         << "3. Tim kiem nguoi lien he theo ten." << endl
         << "4. Sua thong tin lien he." << endl
         << "5. Xoa lien he theo ten" << endl
         << "6. Hien thi cac lien he theo moi quan he." << endl
         << "Vui long chon (1-6): ";
}

void Processing(int& choice) {
switch(choice) { //hien thi danh ba
        case 1: {
            cout << "------------DANH BA------------" << endl;
            showAllContacts();
            break;
        }
        case 2: { //them lien he moi
            int exit = -1;
            cout << "------THEM LIEN HE MOI------" << endl;
            string name, num; int rel;
            //tens
            cout << "Nhap ten: ";
            cin.ignore();getline(cin, name);
            while(!checkDuplicate(name,1)){
                cout << "ERROR: Ten da ton tai, vui long nhap lai!" << endl;
                cout << "Nhap ten: "; getline(cin,name);
            }
            //lay so dien thoai
            cout << "Nhap so dien thoai: ";
            getline(cin, num);
            while(!checkDuplicate(num,2)){
                cout << "ERROR: So dien thoai da ton tai, vui long nhap lai!" << endl;
                cout << "Nhap so dien thoai: "; getline(cin,num);
                cout << "Neu ban muon thoat chuong trinh vui long nhan phim \"1\": ";
                cin >> exit; if(exit == 1) break;
            }
            //moi quan he
            setRelation(rel);
            addNewContact(name, num, rel);
            break;
        }
        case 3: { //tim lien he theo ten
            cin.ignore();
            cout << "----TIM LIEN HE THEO TEN----" << endl;
            cout << "Nhap ten: ";
            string Name; getline(cin, Name);
            searchContact(Name);
            break;
        }
        case 4: { //sua thong tin lien he
            cout << "---SUA THONG TIN LIEN HE---" << endl;
            //nhap so dien thoai muon sua
            cout << "Nhap so dien thoai: ";
            string Num;cin.ignore(); getline(cin,Num); 
            //check xem so dien thoai co ton tai khong
            if(checkDuplicate(Num,2)) {
                cout << "ERROR: So dien thoai khong ton tai!" << endl;
            }
            else {
                //nhap ten
                cout << "Nhap ten muon thay doi: ";
                string newNAME;
                getline(cin, newNAME);
                while (!checkDuplicate(newNAME, 1)) {
                    cout << "ERROR: Ten " << newNAME << " da ton tai! \n Vui long nhap lai" << endl;
                    getline(cin, newNAME);
                }

                //nhap so dien thoai
                cout << "Nhap so dien thoai muon thay doi: ";
                string newNum; getline(cin, newNum);
                while(!checkDuplicate(newNum,2)) {
                    if(newNum == Num) break;
                    cout << "ERROR: So dien thoai " << newNum << " da ton tai! \n Vui long nhap lai" << endl;
                    getline(cin, newNum);
                }
                //nhap moi quan he
                int newRel; setRelation(newRel);
                changeInformation(Num, newNAME, newNum, newRel);
            }
            break;
        }
        case 5: { //xoa lien he theo ten
            string delName;
            cin.ignore();
            cout << "Nhap ten muon xoa: "; getline(cin, delName);
            if(checkDuplicate(delName, 1)) {
                cout << "ERROR: ten khong ton tai!";
                break;
            }
            else deleteContact(delName);
            break;
        }
        case 6: { //trich loc lien he theo moi quan he
            cout << "---TRICH LOC LIEN LAC THEO MOI QUAN HE---" << endl
                 << "1. Gia Dinh\n2. Ban be\n3. Thay/ Co\n4. Dong Nghiep\n5. Khac"
                 << endl
                 << "Vui long chon moi quan he: ";
            int filterRel; cin >> filterRel; cin.ignore();
            while(filterRel < 1 || filterRel > 5) {
                cout << "ERROR: Gia tri khong hop le, vui long nhap lai!" << endl;
                cout << "Chon moi quan he: "; cin >> filterRel;
            }
            sortByRelation(filterRel);
            break;
        }
        default: {
            cout << "ERROR: Gia tri khong hop le!";
            break;
        }
    }
}

bool checkDuplicate(string& value, int step){ //step 1: name | step 2: number
    switch(step) {
        case 1: {
            value.erase(remove(value.begin(), value.end(), ' '), value.end());
            for(int i = 0; i < storeContacts.size(); i++) {
                string checkName = storeContacts[i].name;
                checkName.erase(remove(checkName.begin(), checkName.end(), ' '), checkName.end());
                if(toLowerCase(value) == toLowerCase(checkName)) {
                        return false;
                    }
                }
            break;
        }
        case 2: {
            value.erase(remove(value.begin(), value.end(), ' '), value.end());
            for(int i = 0; i < storeContacts.size(); i++) {
                string checkNum = storeContacts[i].number;
                checkNum.erase(remove(checkNum.begin(), checkNum.end(), ' '), checkNum.end());
                if(value == checkNum) {
                        return false;
                    }
                }
            break;
        }
        default:
            break;
    }
    return true;
}


void setRelation(int& Relation) {
    cout << "Chon moi quan he voi lien lac nay: " << endl
         << "1. Gia Dinh\n2. Ban be\n3. Thay/ Co\n4. Dong Nghiep\n5. Khac" << endl
         << "Vui long chon (1-5): ";
    cin >> Relation;
    while(Relation < 1 || Relation > 5) {
        cout << "ERROR: Lua chon khong hop le!" << endl;
        cout << "Chon moi quan he voi lien lac nay: " << endl
         << "1. Gia Dinh\n2. Ban be\n3. Thay/ Co\n4. Dong Nghiep\n5. Khac" << endl
         << "Vui long chon (1-5): ";
        cin >> Relation;
    }
}

void Update() {
    storeContacts = {};

    ifstream file("/Users/user/Documents/SimpleContacts_/Contacts_project/clone_project/Source/Data.txt"); //mo file dau vao
    
    if (!file) {
    cerr << "ERROR: Khong the mo file!" << endl;
    return;
}

    
    string line;
    int count = 0;
    
    // xu li tung dong
    while (getline(file, line)) {
        stringstream ss(line);
        string name, number;int relation;
        
        // Đảm bảo mỗi dòng có đủ 3 phần dữ liệu
        if (getline(ss, name, ',') && getline(ss, number, ',') && (ss >> relation)) {
            // Cập nhật dữ liệu vào vector
            storeContacts.push_back(Contacts(name, number, relation)); 
            count++;
        }
    }

    file.close();  // dong file

}