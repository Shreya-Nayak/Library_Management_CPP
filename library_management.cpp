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
#include <unordered_set>
using namespace std;
#define MAX 200

int i=0,j=0,k1,k2,k3,k=0;
int stud[MAX];
string cho;
string lineu,linep,lines,temp,temp1;

class book
{
private:
    int number;
public:
    void check_in();
    void check_out();
};

class student {
private:
    string stu_name;
    int stu_id;

public:
    set<int> uniqueStudentIds;
    void add_stu();
    int edit_stu();
    void view_det(int w);
    void list_ofall();
    int initial();
};


/// Add student to database for able to issue books
void student :: add_stu()
{
    cout << "----------------------" << endl;
    cout << "Enter the name of the student to add: ";
    cin >> stu_name;

    // Check if the student ID is unique
    while (true) {
        cout << "Enter the student ID (only numbers): ";
        cin >> stu_id;

        // Check if the student ID is unique
        if (uniqueStudentIds.find(stu_id) != uniqueStudentIds.end()) {
            cout << "----------------------" << endl;
            cout << "Student ID already exists. Please enter a unique ID." << endl;
            cout << "----------------------" << endl;
        } else {
            // If the ID is unique, insert it into the set and proceed
            uniqueStudentIds.insert(stu_id);
            break;
        }
    }

    fstream studentfile("stu.txt", ios::app);
    studentfile << stu_name << " " << stu_id << endl;
    stud[k] = stu_id;
    studentfile.close();
    k++;

    cout << "----------------------" << endl;
    cout << "Student added successfully." << endl;
    cout << "----------------------" << endl;

}

/// View the details of particular student
void student :: view_det(int w)
{
  time_t tt;
  struct tm * ti;
  time (&tt);
  ti = localtime(&tt);
  time_t now = time(0);
  struct tm *ltm = localtime(&now);

  fstream studentfile("stu.txt",ios::in);

  cout<<endl;
  int y=0;
  while(y<k)
  {
    if(stud[y]==w)
    {
      break;
    }
    y++;
  }
  y=y+1;
  if(y==k+1)
  {
    cout<<"----------------------"<<endl;
    cout<<"Not found"<<endl;
    cout<<"----------------------"<<endl;
  }
  else
  {
    cout<<"----------------------"<<endl;
    cout<<"The entered ID is in line no.: "<<y<<endl;
    fstream studentfile("stu.txt",ios::in);
    int lineno=0;
    do
    {
        if (lineno == y)
        {
            cout <<"Student name and ID: "<<lines<< endl;
            cout<<"----------------------"<<endl;
            break;
        }
        lineno++;

    }
    while(getline(studentfile,lines));
    fstream file ("book.txt",ios::in);
    string str;
    cout<<"The list of checked out books under ID: "<<w<<endl;
    while(getline(file,str))
    {
      smatch matches;
      regex reg2("([0-9]+)");
      regex_search(str,matches,reg2);
      if(matches.str(1)==to_string(w))
      {
        regex reg("[0-9]+ (.*)");
        sregex_iterator currentmatch(str.begin(),str.end(),reg);
        sregex_iterator lastmatch;
        
        while(currentmatch!=lastmatch)
        {
            smatch match=*currentmatch;
            cout<<matches.str(1)<<": "<<match.str()<<endl;

            smatch mat;
            regex rew("[0-9A-Za-z .]*([0-9][0-9]/[0-9][0-9]/[0-9][0-9][0-9][0-9])");
            regex_search(str,mat,rew);
            if(regex_search(str,mat,rew))
            {
              string k;
              k=mat.str(1);

              // Checking for fine starts //
              int date1,month1,year1;
              smatch date2;smatch month2;smatch year2;
              regex reg1("([0-9][0-9])/[0-9][0-9]/[0-9][0-9][0-9][0-9]");
              regex reg2("[0-9][0-9]/([0-9][0-9])/[0-9][0-9][0-9][0-9]");
              regex reg3("[0-9][0-9]/[0-9][0-9]/([0-9][0-9][0-9][0-9])");
              regex_search(k,date2,reg1);
              regex_search(k,month2,reg2);
              regex_search(k,year2,reg3);
              int temp_date,temp_month,temp_year;
              smatch matches;
              regex reg("([0-9][0-9]/[0-9][0-9]/[0-9][0-9][0-9][0-9])");
              regex_search(k,matches,reg);

              if(regex_search(k,matches,reg))
              {
                if(stoi(year2[1]) < 1900+ltm->tm_year)
                {
                  cout<<"---> Passed by year. Huge Fine has to be paid for this book"<<endl;
                }
                else if(stoi(year2[1]) > 1900+ltm->tm_year)
                {
                  cout<<"---> The check in date will come soon. No need to worry"<<endl;
                }
                else
                {
                  if(stoi(month2[1]) < 1+ltm->tm_mon)
                  {
                    cout<<"---> Passed by month. Huge Fine has to be paid for this book"<<endl;
                  }
                  else if(stoi(month2[1]) > 1+ltm->tm_mon)
                  {
                    cout<<"---> The check in date will come soon. No need to worry"<<endl;
                  }
                  else
                  {
                    if(stoi(date2[1]) < ltm->tm_mday)
                    {
                      cout<<"---> Passed by date. Fine has to be paid for the this book"<<endl;
                    }
                    else if(stoi(date2[1]) > ltm->tm_mday)
                    {
                      cout<<"---> The check in date will come soon. No need to worry"<<endl;
                    }
                    else
                    {
                      cout<<"---> The book has been issued today !!"<<endl;
                    }
                  }
                }
              }
              // Checking for fine ends //

            }

            
            currentmatch++;
        }
        
      }
    }
    cout<<"----------------------"<<endl;
    cout<<endl;
    file.close();
  }
    
}

/// Edit the details of particular student (issue or return)
int student :: edit_stu()
{ 
  cout<<'\n';
  int id_temp;
  cout<<"----------------------"<<endl;
  cout<<"Enter the student ID: ";
  cin>>id_temp;
  int i=0;
  while(i<MAX)
  {
    if(id_temp==stud[i])
    {
      k3=id_temp;
      cout<<"----------------------"<<endl;
      cout<<"1:Issue (check out) a book\n2:Return (check in) a book\n";
      book b;
      int choice2;
      cin>>choice2;
      switch(choice2)
      {
        case 1:
        {
          b.check_out();
          break;
        }
        case 2:
        {
          b.check_in();
          break;
        }
        default:
        {
          cout<<"----------------------"<<endl;
          cout<<"Incorrect entry"<<endl;
          cout<<"----------------------"<<endl;
          break;
        }
      }

      break;
    }
    else
    {
      i++;
    }
    if(i==MAX)
    {
      cout<<"----------------------"<<endl;
      cout<<"No student found"<<endl;
      cout<<"----------------------"<<endl;
    }
  }

  return k3;
}

/// Check out of book (issuing the book)
void book :: check_out()
{
  string book;
  fstream booklist("book.txt",ios::app | ios::out);
  cout<<"----------------------"<<endl;
  cout<<"Enter the number books to be issued: ";
  cin>>number;
  int i=0;
  cin.ignore();
  time_t tt;
  struct tm * ti;
   
  ti = localtime(&tt);
  cout<<"----------------------"<<endl;
  cout << "Issue Day, Date and Time is: " <<endl;
  cout<<"Day Month Date Time Year"<<endl;
  cout<<asctime(ti);
  cout<<"----------------------"<<endl;
  time_t now = time(0);
  struct tm *ltm = localtime(&now);
  int upload_temp;
  char upload[50];
  upload_temp=sprintf(upload,"%02d/%02d/%04d",ltm->tm_mday + 15,1+ltm->tm_mon,1900 + ltm->tm_year);

  while(i<number)
  {
    cout<<"----------------------"<<endl;
    cout<<"Enter the name of book: ";
    getline(cin,book);
    booklist<<k3<<" "<<book<<" "<<upload<<endl;
    i++;
  }
  cout<<"----------------------"<<endl;
  cout<<"Books issued"<<endl;
  cout<<"----------------------"<<endl;
  booklist.close();
}

/// Printing all Students who are registered for library
void student :: list_ofall()
{
  cout<<"----------------------"<<endl;
  string alpha("");
  string num("");
  fstream studentfile("stu.txt",ios::in);
  string temp;
  while(getline(studentfile,temp))
  {
    for (int i=0; i<temp.length(); i++)
    {

      if((temp[i] >= 'A' && temp[i] <= 'Z') ||
              (temp[i] >= 'a' && temp[i] <= 'z') ||
              (temp[i]==' '))
      {
          alpha=alpha+temp[i];

      }
      if (isdigit(temp[i]))
      {
        num=num+temp[i];

      }
    }
    cout<<"Student name: "<<alpha <<"---";
    cout<<"Student ID: "<<num << endl;
    num="";
    alpha="";

  }
  cout<<"----------------------"<<endl;
  studentfile.close();
}

/// Check in of book by student (Returning the book)
void book :: check_in()
{
  string stri;
  string str,ee[MAX];
  int h;
  int j=0;
  fstream file("book.txt",ios::in);
  while(getline(file,str))
  {
      smatch matches;
      regex reg2("([0-9]+)");
      regex_search(str,matches,reg2);
      if(matches.str(1)==to_string(k3))
      {
        regex reg("[0-9]+ (.*)");
        sregex_iterator currentmatch(str.begin(),str.end(),reg);
        sregex_iterator lastmatch;
        while(currentmatch!=lastmatch)
        {
            smatch match=*currentmatch;
            ee[j]=match.str();
            currentmatch++;
        }
        j++;
      }
  }
  file.close();
  if(j==0)
  {
    cout<<"----------------------"<<endl;
    cout<<"No entry found in that ID"<<endl;
    cout<<"----------------------"<<endl;
  }
  else
  {
    cout<<"----------------------"<<endl;
    cout<<"what do u want to remove in: "<<endl;
    for (int i=0;i<j;i++)
    {
      cout<<i+1<<": "<<ee[i]<<endl;
    }
    cout<<"----------------------"<<endl;
    cin>>h;
    int i;
    int c=0;
    for(i=0;i<j;i++)
    {
      if(ee[i]!=ee[h-1])
      {
        c++;
      }
      else
      {
        fstream f("book.txt",ios::in);
        fstream temp("temp.txt",ios::out);
        while (getline(f, stri))
        {
        if (stri != ee[h-1])
        {
            temp<<stri<<endl;
        }
        }
        f.close();
        temp.close();
        remove("book.txt");
        rename("temp.txt","book.txt");
      }
    }
    
    if(c==j)
    {
      cout<<"----------------------"<<endl;
      cout<<"Not found"<<'\n';
      cout<<"----------------------"<<endl;
    }
    else
    {
      cout<<"----------------------"<<endl;
      cout<<"Removed successfully"<<'\n';
      cout<<"----------------------"<<endl;
    }
  }

}

/// Initializing (the code that runs first of all)
int student :: initial()
{
	ifstream studentfile("stu.txt");
  if(studentfile.is_open())
  {
    string lines;
    while(!studentfile.eof())
    {
      getline(studentfile,lines);
        stringstream ss(lines);
        string temp;
        int fou;
        while(ss>>temp)
        {
          if(stringstream(temp) >> fou)
          {
            stud[k]=fou;

          }

        }
        k++;
    }
    k=k-1;
  }
  else
  {
    k=0;
  }

  studentfile.close();

  return k;
}


/// Main function starts
int main()
{
    student s;
    s.initial(); // Initialize the student data

    int choice;
    while (true) {
        cout << "----------------------" << endl;
        cout << "1: Add a student to the database" << endl;
        cout << "2: Edit the details of a student" << endl;
        cout << "3: View the details of a particular student" << endl;
        cout << "4: View all enrolled students for library books" << endl;
        cout << "5: Exit portal" << endl;
        cout << "----------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                s.add_stu();
                break;
            case 2: {
                cout << "----------------------" << endl;
                cout << "Processing...." << endl;
                cout << "----------------------" << endl;
                int studentId = s.edit_stu();
                if (studentId != 0) {
                    book b;
                    int choice2;
                    cout << "----------------------" << endl;
                    cout << "1: Issue (check out) a book" << endl;
                    cout << "2: Return (check in) a book" << endl;
                    cout << "3: Go Back" << endl;
                
                    cout << "----------------------" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice2;
                    switch (choice2) {
                        case 1:
                            b.check_out();
                            break;
                        case 2:
                            b.check_in();
                            break;
                        case 3:                         
                            break;
                        
                        default:
                            cout << "----------------------" << endl;
                            cout << "Incorrect entry" << endl;
                            cout << "----------------------" << endl;
                            break;
                    }
                }
                break;
            }
            case 3:
                int q;
                cout << "----------------------" << endl;
                cout << "Enter the ID of the student to view the details" << endl;
                cin >> q;
                s.view_det(q);
                break;
            case 4:
                s.list_ofall();
                break;
            case 5:
                exit(0);
            default:
                cout << "----------------------" << endl;
                cout << "Incorrect entry" << endl;
                cout << "----------------------" << endl;
                break;
        }
    }
    return 0;
}