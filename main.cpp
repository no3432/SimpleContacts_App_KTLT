#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <fstream>
#include<sstream>
using namespace std;

struct Contacts {
    string name;
    string number;
    string relation;

    Contacts(string n, string num, string rel): name(n), number(num), relation(rel){}
};

vector<pair<string,string>, string> storeContacts;

//ham chuyen chuoi thanh chu thuong
string toLowerCase(const string& str) {
    string result = str;
    for (char &c : result) {
        c = tolower(c);  
    }
    return result;
}
void showUI();
void showAllContacts();
void addNewContact(string& newName, string& newNumber, string& newRelation);
void searchContact(string& searchName);
void changeInformation(string& newName, string& newNumber, string& newRelation);
void deleteContact(string& deleteName);
void sortByRelation(string& relationShip);
void Processing(int& choice);
bool checkDuplicate(string& value, int step);

int main() {

    updateData(); //cap nhat du lieu tu file dau vao

    for(;true;) {

    showUI();//hien thi menu

    int cont =-1 ; 
    int choose; cin >> choose;

    while(choose < 1 || choose > 6) {
        cout << "Lua chon khong hop le!\nBan co muon tiep tuc khong? (1 de tiep tuc/0 de dung):" << endl;
        cin >> cont;
        if(cont == 0) break;
        else {
            showUI();
            cin >> choose;
        }
    }
    if(cont == 0) break;//xet xem nguoi dung co muon tiep tuc khong
    Processing(choose);
    cout << "Ban co muon tiep tuc khong? (1 de tiep tuc/0 de dung lai):";
    cin >> cont;
    if(cont == 0) break;//xet xem nguoi dung co muon tiep tuc khong
    }
    return 0;
}

void updateData() {
    ifstream file("Data.txt"); //mo file dau vao
    
    if (!file) {  // kiem tra xem co mo duoc file khong
        cout << "ERROR: Loi khong the mo file!";
        return;
    }
    
    string line;
    int count = 0;
    
    // xu li tung dong
    while (getline(file, line)) {
        stringstream ss(line);
        string name, number, relation;
        
        getline(ss, name, ',');    // doc ten
        getline(ss, number, ',');   // doc so dien thoai
        getline(ss, relation, ',');   // doc moi quan he

        // cap nhat du lieu vao vector
        storeContacts.push_back(make_pair(make_pair(name,number),relation)); 

        count++;
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
switch(choice) {
        case 1:
            cout << "---DANH BA---" << endl;
            showAllContacts();
            break;
        case 2: 
            cout << "---THEM LIEN HE MOI---" << endl;
            string name, num, rel;
            cout << "Nhap ten: "
            getline(cin, name);cin.ignore();
            //kiem tra xem co trung ten khong
            while(checkDuplicate(name,1)) {
                cout << "ERROR: Ten " << name << " da ton tai! \n Vui long nhap lai";
                getline(cin, name);
            }
            string newN = name;
            //lay so dien thoai
            cout << "Nhap so dien thoai: ";
            getline(cin, num);
            //kiem tra xem co trung so dien thoai khong
            while(checkDuplicate(num,2)) {
                cout << "ERROR: So dien thoai " << num << " da ton tai! \n Vui long nhap lai";
                getline(cin, num);
            }
            string newNum = num;
            //moi quan he
            cout << "Nhap moi quan he:";
            getline(cin, rel);
            addNewContact(newN, newNum, rel);
            break;
        case 3:
            cout << "---TIM LIEN HE THEO TEN---" << endl;
            string name; getline(cin, name);
            searchContact(name);
            break;
        case 4:
            cout << "---SUA THONG TIN LIEN HE---" << endl;
            //nhap so dien thoai muon sua
            cout << "Nhap so dien thoai: ";
            string num; getline(cin,num); cin.ignore();
            //check xem so dien thoai co ton tai khong
            bool appear = false;
            for(int i = 0; i < n; i++) {
                if(num == storeContacts[i].first.second) {
                    appear = true;
                    break;
                }
            }
            if(!appear) {
                cout << "ERROR: So dien thoai khong ton tai!" << endl;
                break;
            }
            else {
                //nhap ten
                cout << "Nhap ten muon thay doi: ";
                string newN; getline(cin, newN);
                while(checkDuplicate(newN,1)) {
                cout << "ERROR: Ten " << newN << " da ton tai! \n Vui long nhap lai";
                getline(cin, newN);
                }
                //nhap so dien thoai
                cout << "Nhap so dien thoai muon thay doi: ";
                string newNum; getline(cin, newNum);
                while(checkDuplicate(newNum,2)) {
                cout << "ERROR: Ten " << newNum << " da ton tai! \n Vui long nhap lai";
                getline(cin, newNum);
                }
                //nhap moi quan he
                string newRel; getline(cin, newRel);
                changeInformation(newN, newNum, newRel);
            }
            break;
        case 5:
            //code here
            break;
        case 6:
            //code here
            break;
        default:
            break;
    }
}

bool checkDuplicate(string& value, int step){ //step 1: name | step 2: number
    switch(step) {
        case 1:
            if(value == storeContacts[i].first.first) {
                    return false;
                }
            break;
        case 2:
            if(value == storeContacts[i].first.second) {
                    return false;
                }
            break;
        default:
            break;
    }
    return true;
}

/*
code 5 function
*/
