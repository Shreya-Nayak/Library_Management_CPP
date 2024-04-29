#include <iostream>
#include<string>
#include<stdlib.h>
#include<fstream>
#include<cstring>
#include<sstream>
#include<ctime>
#include<string.h>
#include <cstdio>
#include <iomanip>
#include<bits/stdc++.h>
#include<regex>
using namespace std;

#define MAX 200

int i=0,j=0,k1,k2,k3,k=0;
string users[MAX];
string passw[MAX];
int stud[MAX];

class login
{
private:
  string user;
  string pass;
public:
  int check();
  string regis();
  void disp();
  void change_pass();
  void exit();
  void append();
  int initial();
};

class book
{
private:
    int number;
public:
    void due_details();
    void check_in();
    void check_out();
    void date_enroll();
    void reset_enroll();
};

class student
{
private:
    string stu_name;
    int stu_id;
public:
    void add_stu(){
        cout<<"----------------------"<<endl;
        cout<<"Enter the name of student to add: ";
        cin>>stu_name;
        cout<<"Enter the student ID(only numbers): ";
        cin>>stu_id;
        cout<<"----------------------"<<endl;
        fstream studentfile("stu.txt",ios::app);
        studentfile<<stu_name<<" ";
        studentfile<<stu_id<<endl;
        stud[k]=stu_id;
        studentfile.close();
        k=k+1;
        }

    int edit_stu();
    void view_det(int w);
    void list_ofall();
    int initial();
};