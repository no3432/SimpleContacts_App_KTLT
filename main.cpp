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
    int relation;

    Contacts(string n, string num, int rel): name(n), number(num), relation(rel){}
};

vector<Contacts> storeContacts;

//ham chuyen chuoi thanh chu thuong
string toLowerCase(const string& str) {
    string result = str;
    for (char &c : result) {
        c = tolower(c);  
    }
    return result;
}
//khai bao cac ham su dung
void showUI();
void showAllContacts();
void addNewContact(string& newName, string& newNumber, int& newRelation);
void searchContact(string& searchName);
void changeInformation(string& newName, string& newNumber, int& newRelation);
void deleteContact(string& deleteName);
void sortByRelation(int& relationShip);
void Processing(int& choice);
bool checkDuplicate(string& value, int step);
void updateData();
void Update(string& newN, string& newNum, int& newRel);
void setRelation(int& Relation);

int main() {

    updateData(); //cap nhat du lieu tu file dau vao

    for(;true;) {

    showUI();//hien thi menu

    char cont = 'y' ; 
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
    cout << "Ban co muon tiep tuc khong? (Y/N) : ";
    cin >> cont;
    if(tolower(cont) != 'y') break;//xet xem nguoi dung co muon tiep tuc khong
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
        
        // Đảm bảo mỗi dòng có đủ 3 phần dữ liệu
        if (getline(ss, name, ',') && getline(ss, number, ',') && getline(ss, relation, ',')) {
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
            string name, num, rel;
            //tens
            cout << "Nhap ten: ";
            getline(cin, name);cin.ignore();
            while(checkDuplicate(name,1)){
                cout << "ERROR: Ten da ton tai, vui long nhap lai!" << endl;
                cout << "Nhap ten: "; getline(cin,name);
                cout << "Neu ban muon thoat chuong trinh vui long nhan phim \"1\": ";
                cin >> exit; if(exit == 1) break;
            }
            //lay so dien thoai
            cout << "Nhap so dien thoai: ";
            getline(cin, num);
            while(checkDuplicate(num,2)){
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
            cout << "----TIM LIEN HE THEO TEN----" << endl;
            string Name; getline(cin, Name);
            searchContact(Name);
            break;
        }
        case 4: { //sua thong tin lien he
            cout << "---SUA THONG TIN LIEN HE---" << endl;
            //nhap so dien thoai muon sua
            cout << "Nhap so dien thoai: ";
            string Num; getline(cin,Num); cin.ignore();
            //check xem so dien thoai co ton tai khong
            if(checkDuplicate(Num,2)) {
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
                string newRel; setRelation(newRel);
                changeInformation(newN, newNum, newRel);
            }
            break;
        }
        case 5: { //xoa lien he theo so dien thoai
            string delNum;
            cout << "Nhap so dien thoai muon xoa: "; getline(cin, delNum);
            if(checkDuplicate(delNum)) {
                cout << "ERROR: So dien thoai khong ton tai!";
                break;
            }
            else deleteContact(delNum);
            break;
        }
        case 6: { //trich loc lien he theo moi quan he
            cout << "---TRICH LOC LIEN LAC THEO MOI QUAN HE---" << endl
                 << "1. Cha/Me\n2. Anh/Chi/Em\n3. Nguoi yeu/Vo\n4. Ban be\n5. Khac"
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
        case 1:
            for(int i = 0; i < storeContacts.size(); i++) {
            if(toLowerCase(value) == toLowerCase(storeContacts[i].name)) {
                    return false;
                }
            }
            break;
        case 2:
        for(int i = 0; i < storeContacts.size(); i++) {
            if(toLowerCase(value) == toLowerCase(storeContacts[i].number)) {
                    return false;
                }
        }
            break;
        default:
            break;
    }
    return true;
}

void Update(string newN, string newNum, int newRel) {
    ostream file("Data.txt", ios::app); //ios::app de set con tro o dong cuoi cung
    if(!file) {
        cout << "ERROR: Khong the mo file!" << endl;
        return;
    }
    //nhap du lieu vao file
    file << "\"" << newN << "\", \"" << newNum << "\", " << newRel << "\n";
    file.close();
    cout << "Da nhap lien lac " << newN << " vao danh sach.";
}

void setRelation(int& Relation) {
    cout << "Chon moi quan he voi lien lac nay: " << endl
         << "1. Cha/Me\n2. Anh/Chi/Em\n3. Nguoi yeu/Vo\n4. Ban be\n5. Khac" << endl
         << "Vui long chon (1-5): ";
    cin >> Relation;
    while(Relation < 1 || Relation > 5) {
        cout << "ERROR: Lua chon khong hop le!" << endl;
        cout << "Chon moi quan he voi lien lac nay: " << endl
         << "1. Cha/Me\n2. Anh/Chi/Em\n3. Nguoi yeu/Vo\n4. Ban be\n5. Khac" << endl
         << "Vui long chon (1-5): ";
        cin >> Relation;
    }
}

void showAllContacts() {
    //hiển thị danh bạ - Toàn 
    string Relation[7] = {"0","Cha/Me","Anh/Chi/Em","Nguoi yeu/Vo","Ban be","Khac"};
    cout << "-------------------------------" << endl;
    for(int i = 0; i < storeContacts.size(); i++) {
        cout << "Ten: " << storeContacts[i].name << endl 
             << "So Dien Thoai: " << storeContacts[i].number << endl
             << "Moi quan he: " << Relation[i] << endl
             << "-------------------------------" << endl;
    }
}

void addNewContact(string& newName, string& newNumber, int& newRelation) {
    //thêm liên lạc mới - Trình
}

void searchContact(string& searchName) {
    //tìm kiếm liên lạc theo tên - Trọng
}

void changeInformation(string& newName, string& newNumber, int& newRelation) {
    //thay đổi thông tin theo số điện thoại - Trọng
}

void deleteContact(string& deleteName) {
    //xoá liên lạc - Trí
}

void sortByRelation(int& relationShip) {
    //lọc liên lạc theo mối quan hệ - Toạ
}