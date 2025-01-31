#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

// Khai bao struct chua contacts
struct Contacts {
    std::string name;
    std::string number;
    int relation;

    Contacts(std::string n, std::string num, int rel) : name(n), number(num), relation(rel) {}
};

// Khai bao vector luu tru tam thoi
extern vector<Contacts> storeContacts;

// Khai bao ham
string toLowerCase(const string& str);
void showUI();
void showAllContacts();
void addNewContact(string& newName, string& newNumber, int& newRelation);
void searchContact(string& searchName);
void changeInformation(const string& oldNum, string& newName, string& newNumber, int& newRelation);
void deleteContact(string& deleteName);
void sortByRelation(int& relationShip);
void Processing(int& choice);
bool checkDuplicate(string& value, int step);
void updateData();
void setRelation(int& Relation);
void Update();
#endif // MAIN_H
