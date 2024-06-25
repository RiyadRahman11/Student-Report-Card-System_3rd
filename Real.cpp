#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include "myalgoe.h"
#define UP 72
#define DOWN 80
#define ENTER 13

using namespace std;
int lastid = 241000, lastTid = 1200;


int Rank(int,int);
void Colour(int color);
void gotoxy(int x, int y);
void LogS();
void stuDash(int id);
void StuSC(int id);
void StuP(int id);
void StuRank(int id);
void StuReport(int id);
int stuDashM(int id);
int courseDashM(int id);
void CourseSC(int id);
void CourseP(int id);
void CourseUp(int id);
void CourseRank(int id);
int CourseMenu();
void CorReg();
void CorL();
void CourseOv(int id);
void get_course();
void updatelastid();
int WELCOME();
int StuReg();
void studentM();

void get_stu();
void SReg();
void arrowF(int realPosition, int arrowPosition);
void courseDash(int id);
void CourseM();

int windowHeight = 45;
int windowWidth = 160;
int borderX = windowWidth / 4;
int borderY = windowHeight / 4;
int borderWidth = windowWidth / 2;
int borderHeight = windowHeight / 2;
int menuX = borderX + borderWidth / 2 - 6;
int menuY = borderY + 2;

struct TEACHER;
struct COURSE;
struct STUDENTS;


void clear_input_buffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void Colour(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

struct TEACHER
{
    int tid, cid;
    string name, tpass;
};

struct COURSE
{
    int cid, tid, marks;
    double credit, cgpa;
    string name;
    vector<STUDENTS> stc;
    TEACHER th;
    PriorityQueue pq;
    //priority_queue< psq;
   BST tree;
};

struct STUDENTS
{
    int sid, marks;
    double cgpa;
    string name, spass;
    vector<COURSE> stcourse;
};
#include "myalgo.h"

map<int, COURSE> course_hash;

map<int, STUDENTS> stu_hash;
vector<COURSE> course;
vector<STUDENTS> stu;
vector<vector<int>> marks, cgpa;

void arrowF(int realPosition, int arrowPosition)
{
    if (realPosition == arrowPosition)
    {
        Colour(12);
        cout << "==> ";
    }
    else
    {
        Colour(3);
        cout << "    ";
    }
}

void updatelastid()
{
    ifstream infile;
    infile.open("sid.txt");
    if (infile.is_open())
    {
        int id;
        while (infile >> id)
        {
            lastid = max(lastid, id);
        }
        infile.close();
    }
}
void updatelastidT()
{
    ifstream infile;
    infile.open("tid.txt");
    if (infile.is_open())
    {
        int id;
        while (infile >> id)
        {
            lastid = max(lastid, id);
        }
        infile.close();
    }
}

int WELCOME()
{
    system("cls");
    int pos = 1;
    int keyP = 0;
    while (keyP != ENTER)
    {
        int headerX = borderX + borderWidth / 2 - 10;
        Colour(5);
        gotoxy(headerX, borderY + 1);
        printf("*******        ******");
        gotoxy(headerX, borderY + 2);
        printf("******   HOME  *****");
        gotoxy(headerX, borderY + 3);
        printf("******         ******");

        gotoxy(menuX, menuY + 2);
        Colour(3);
        arrowF(1, pos);
        printf("About");

        gotoxy(menuX, menuY + 4);
        Colour(3);
        arrowF(2, pos);
        printf("Student");

        gotoxy(menuX, menuY + 6);
        Colour(3);
        arrowF(3, pos);
        printf("Course");

        gotoxy(menuX, menuY + 8);
        Colour(3);
        arrowF(4, pos);
        printf("Admin");

        gotoxy(menuX, menuY + 10);
        Colour(3);
        arrowF(5, pos);
        printf("Credits");

        gotoxy(menuX, menuY + 12);
        Colour(3);
        arrowF(6, pos);
        printf("Exit");

        keyP = _getch();
        if (keyP == DOWN)
        {
            if (pos == 6)
                pos = 1;
            else
                pos++;
        }
        else if (keyP == UP)
        {
            if (pos == 1)
                pos = 6;
            else
                pos--;
        }
    }

    system("cls");
    return pos;
}

int StuReg()
{
    system("cls");
    int pos = 1;
    int keyP = 0;
    while (keyP != ENTER)
    {
        int headerX = borderX + borderWidth / 2 - 10;
        Colour(5);
        gotoxy(headerX, borderY + 1);
        printf("*******        ******");
        gotoxy(headerX, borderY + 2);
        printf("******   HOME  *****");
        gotoxy(headerX, borderY + 3);
        printf("******         ******");

        gotoxy(menuX, menuY + 2);
        Colour(3);
        arrowF(1, pos);
        printf("Register");

        gotoxy(menuX, menuY + 4);
        Colour(3);
        arrowF(2, pos);
        printf("Login");

        gotoxy(menuX, menuY + 6);
        Colour(3);
        arrowF(3, pos);
        printf("Exit");

        keyP = _getch();
        if (keyP == DOWN)
        {
            if (pos == 3)
                pos = 1;
            else
                pos++;
        }
        else if (keyP == UP)
        {
            if (pos == 1)
                pos = 3;
            else
                pos--;
        }
    }
    _getch();
    system("cls");
    return pos;
}

void studentM()
{
    int x;
    do
    {
        x = StuReg();
        if (x == 1)
            SReg();
        else if (x == 2)
            LogS();
    } while (x != 3);
}

void write_to_f(STUDENTS temp)
{
    ofstream outfile, outid;
    outfile.open("studentA.txt", ios::app);
    outid.open("sid.txt", ios::app);
    outfile<<temp.sid << " " << temp.spass << " " << temp.marks << " " << temp.cgpa << " " << temp.name<<endl;
    outid << temp.sid<<endl;
    outfile.close();
    outid.close();
}

void SReg() {
    updatelastid();

    int id = lastid + 1;
    STUDENTS temp;
    temp.marks = 0;
    temp.cgpa = 0;
    temp.sid = id;
    clear_input_buffer();
    cout << "Enter your Full Name: ";
    string nm;
    getline(cin, nm);
    cout << "Set a password: ";
    string pass;
    cin >> pass;
    clear_input_buffer();
    temp.name = nm;
    temp.spass = pass;
    write_to_f(temp);
    stu_hash[id] = temp;
    int counter=0;
    cout << "Your registration is completed" << endl;
    cout << "Your Student ID is: " << id << endl;
    if (course.size() == 0) return;
    cout << course.size()<<" ·"<<"You may now select your courses:" << endl << endl;
    for (auto& u : course)
    {
        cout << u.cid << " " << u.name << endl;
    }
    cout<<"Enter the course ids using spaces :"<<endl;
    string sC;
    getline(cin,sC);
    vector<int>ids=toIntV(sC);
    for(int i=0;i<ids.size();i++)
    {

            COURSE u=course_hash[ids[i]];
            cout<<u.name<<endl;
            u.marks = -1;
            u.cgpa = -1;
            ofstream stufile, csfile;
            string stName = to_string(id) + ".txt";
            string csName = "CSE" + to_string(u.cid) + ".txt";
            stufile.open(stName, ios::app);
            csfile.open(csName, ios::app);
            stufile << u.cid << " " << u.marks<<endl;
            csfile<<id<<endl;
            stufile.close();
            csfile.close();
            temp.stcourse.push_back(u);
            u.stc.push_back(temp);
    }
    mergesort(temp.stcourse);
  }



void LogS()
{
    int id;
    string pass;
    cout << "Enter your ID: ";
    cin >> id;
    cout << "Enter your Password: ";
    cin >> pass;
    if (stu_hash[id].spass == pass)
        stuDash(id);
    else
        cout << "Incorrect Password or Incorrect ID" << endl;
    _getch();
}
void get_stu()
{
    ifstream infile;
    infile.open("studentA.txt");
    if (infile.is_open())
    {
        STUDENTS temp;
        stu.clear();
        while (true)
        {
            STUDENTS temp;
            if (!(infile >> temp.sid >> temp.spass >> temp.marks >> temp.cgpa))
                break;
            infile.ignore();
            getline(infile, temp.name);


            ifstream pqfile;
            string stfile = to_string(temp.sid) + ".txt";
            pqfile.open(stfile);
            if (pqfile.is_open())
            {
                int k=0;
                COURSE u;
                while (pqfile >> u.cid >> u.marks)
                {
                    COURSE ct=course_hash[u.cid];
                    temp.stcourse.push_back(u);



                }

            }
              pqfile.close();
            stu_hash[temp.sid] = temp;
            stu.push_back(temp);
        }

    }

     infile.close();

     for(int i=0;i<stu.size();i++)
     {

         for(int j=0;j<stu[i].stcourse.size();j++)
         {
            //stu[i].stcourse[j].tree.Binsert(stu[i].stcourse[j].marks);
            //stu[i].stcourse[j].pq.insert(stu[i].sid,stu[i].stcourse[j].marks);
            //cout<<"Course :"<<stu[i].stcourse[j].cid<<" "<<stu[i].stcourse[j].marks<<endl;
            //cout<<stu[i].stcourse[j].pq.returnsize()<<endl<<endl;
         }
     }
    //_getch();
}

void StuP(int id)
{
    STUDENTS temp =stu_hash[id];
    cout<<id<<endl;
    cout<<temp.name<<endl;
    cout<<"Number of course taken :"<<temp.stcourse.size()<<endl;
     _getch();
}

void StuSC(int id)
{
    get_stu();
    STUDENTS temp = stu_hash[id];
    cout << "Selected Courses:" << " "<<id<<endl;
    for (auto u : temp.stcourse)
    {
        COURSE c=course_hash[u.cid];
        cout << u.cid << " ";
        if(u.marks==-1)cout<<"N/A"<<endl;
        cout<<u.marks<<endl;
    }

    _getch();
}

void StuRank(int id)
{
    STUDENTS temp = stu_hash[id];
    for(auto c:temp.stcourse)
    {
        COURSE u=course_hash[c.cid];
        if(u.marks==-1)
        {
            cout<<"Marks not updated yet"<<endl;
        }
        else cout<<"Course"<< u.name<<" "<<u.cid<<" "<<"Current Rank : "<<Rank(u.cid,id)<<endl;
    }
    _getch();
}

void StuReport(int id)
{
    STUDENTS u=stu_hash[id];
    vector<COURSE>AC;
    for(auto courses:u.stcourse)
    {
        AC.push_back(courses);
    }
    int total_cs=AC.size();
    int sum=0;
    double cgpa= weight_avg(AC);
    for(auto c:AC)
    {
        sum+=c.marks;

    }
    cout<<u.name<<endl<<u.sid<<endl<<endl;
    cout<<"Report Card : "<<endl<<endl;
    cout<<"Marks | "<<"GPA | "<<"Grade | "<<"Rank | "<<endl;
    for(auto c:AC)
    {
        COURSE temp;
        temp=course_hash[c.cid];
        cout<<c.cid<<" "<<temp.name<<" "<<temp.credit<<" ";
        if(c.marks==-1)cout<<"N/A"<<" "<<"N/A"<<"N/A"<<"N/A"<<endl;
        else
        cout<<c.marks<<" "<<gpa(c.marks)<<" "<<grade(c.marks)<<" "<<Rank(c.cid,id)<<endl;
    }
    cout<<endl;

    if(sum<0)
    {
    cout<<"Total marks :"<<"N/A"<<endl;
    cout<<"Current CGPA :"<<"N/A"<<endl;
    cout<<"Overall grade :"<<"N/A"<<endl;
    }
    else
    cout<<"Total marks :"<<sum<<endl;
    cout<<"Current CGPA :"<<gpa(sum)<<endl;
    cout<<"Overall grade :"<<grade(sum)<<endl;
    _getch();

}

void stuDash(int id)
{
    int x;
    do
    {
        x = stuDashM(id);
        if (x == 1)
            StuP(id);
        else if (x == 2)
            StuSC(id);
        else if (x == 3)
            StuRank(id);
        else if (x == 4)
            StuReport(id);
    } while (x != 5);
}

int stuDashM(int id)
{
    system("cls");
    int pos = 1;
    int keyP = 0;
    while (keyP != ENTER)
    {
        int headerX = borderX + borderWidth / 2 - 10;
        Colour(5);
        gotoxy(headerX, borderY + 1);
        printf("*******    DASHBOARD    ******");
        gotoxy(headerX, borderY + 2);
        printf("******   STUDENT HOME  ******");
        gotoxy(headerX, borderY + 3);
        printf("******        PAGE       ******");

        gotoxy(menuX, menuY + 2);
        Colour(3);
        arrowF(1, pos);
        printf("Profile");

        gotoxy(menuX, menuY + 4);
        Colour(3);
        arrowF(2, pos);
        printf("Selected Courses");

        gotoxy(menuX, menuY + 6);
        Colour(3);
        arrowF(3, pos);
        printf("Rank");

        gotoxy(menuX, menuY + 8);
        Colour(3);
        arrowF(4, pos);
        printf("Report Card");

        gotoxy(menuX, menuY + 10);
        Colour(3);
        arrowF(5, pos);
        printf("Exit");

        keyP = _getch();
        if (keyP == DOWN)
        {
            if (pos == 5)
                pos = 1;
            else
                pos++;
        }
        else if (keyP == UP)
        {
            if (pos == 1)
                pos = 5;
            else
                pos--;
        }
    }

    system("cls");
    return pos;
}



void courseDash(int id)
{
    int x;
    do
    {
        x = courseDashM(id);
        if (x == 1)
            CourseP(id);
        else if (x == 2)
            CourseSC(id);
         else if(x==3)
            CourseUp(id);
        else if (x == 4)
            CourseRank(id);
        else if (x == 5)
            CourseOv(id);
    } while (x !=6);
}

int courseDashM(int id)
{
    system("cls");
    int pos = 1;
    int keyP = 0;
    while (keyP != ENTER)
    {
        int headerX = borderX + borderWidth / 2 - 10;
        Colour(5);
        gotoxy(headerX, borderY + 1);
        printf("*******    DASHBOARD    ******");
        gotoxy(headerX, borderY + 2);
        printf("******   COURSE HOME   ******");

        gotoxy(menuX, menuY + 2);
        Colour(3);
        arrowF(1, pos);
        printf("Course Profile");

        gotoxy(menuX, menuY + 4);
        Colour(3);
        arrowF(2, pos);
        printf("Enrolled Students");

        gotoxy(menuX, menuY + 6);
        Colour(3);
        arrowF(3, pos);
        printf("Result Update");

        gotoxy(menuX, menuY + 8);
        Colour(3);
        arrowF(4, pos);
        printf("Course Rank");

        gotoxy(menuX, menuY + 10);
        Colour(3);
        arrowF(5, pos);
        printf("Overview");

        gotoxy(menuX, menuY + 12);
        Colour(3);
        arrowF(6, pos);
        printf("Exit");

        keyP = _getch();
        if (keyP == DOWN)
        {
            if (pos == 6)
                pos = 1;
            else
                pos++;
        }
        else if (keyP == UP)
        {
            if (pos == 1)
                pos = 6;
            else
                pos--;
        }
    }

    system("cls");
    return pos;
}

void CourseSC(int id)
{
    COURSE temp=course_hash[id];
    cout<<id<<endl;
    cout<<"Enrolled Students :"<<endl;
    if(temp.stc.size()==0)
    {
        cout<<"No students Enrolled So Far..."<<endl;
        _getch();
        return;
    }
    for(auto u:temp.stc)
    {

        cout<<u.sid <<" "<<u.name;
    }
    _getch();
}

void CourseP(int id)
{
    COURSE u=course_hash[id];
    cout<<u.cid<<" "<<u.name<<" "<<u.credit<<endl;
    _getch();
}
int Rank(int id,int sid)
{
    COURSE temp=course_hash[id];
    if(temp.stc.size()==0)
    {
        return -1;
    }
    vector<pair<int,int>>vpp;
    for(int i=0;i<temp.stc.size();i++)
    {
        STUDENTS  sk;
        sk=stu_hash[temp.stc[i].sid];

        for(int j=0;j<sk.stcourse.size();j++)
        {
            if(sk.stcourse[j].cid==id)
            {
                vpp.push_back({sk.stcourse[j].marks,sk.sid});
            }
        }
    }
    sort(vpp.rbegin(),vpp.rend());
    int k=1;
    for(auto [x,y]:vpp)
    {
        if(y==sid) return k;
        //cout<<x<<" "<<y<<endl;
        k++;
    }
}

void CourseRank(int id)
{
    COURSE temp=course_hash[id];
    cout<<"Enrolled Students :"<<endl;
    if(temp.stc.size()==0)
    {
        cout<<"No students Enrolled to provide Rank"<<endl;
        _getch();
        return;
    }
    vector<pair<int,int>>vpp;
    for(int i=0;i<temp.stc.size();i++)
    {
        STUDENTS  sk;
        sk=stu_hash[temp.stc[i].sid];

        for(int j=0;j<sk.stcourse.size();j++)
        {
            if(sk.stcourse[j].cid==id)
            {
                vpp.push_back({sk.stcourse[j].marks,sk.sid});
            }
        }
    }
    sort(vpp.rbegin(),vpp.rend());
    for(auto [x,y]:vpp)
    {
        cout<<x<<" "<<y<<endl;
    }
    _getch();
}

void CourseOv(int id)
{
    COURSE temp=course_hash[id];
    cout<<temp.cid<<" "<<temp.name<<" "<<temp.credit<<endl;
    cout<<"Enrolled Students :"<<endl;
    if(temp.stc.size()==0)
    {
        cout<<"No students Enrolled So Far..."<<endl;
        _getch();
        return;
    }
    for(auto u:temp.stc)
    {

        cout<<u.sid <<" "<<u.name;

    }
    _getch();
}

void UpdateFile(int k,int st,int cs,int val,int j)
{
                COURSE u=course_hash[cs];
                ofstream stufile,csfile;
                string stName=to_string(st)+".txt";
                string csName="CSE"+to_string(cs)+".txt";
                stufile.open(stName,ios::trunc);
                for(int i=0;i<stu[k].stcourse.size();i++)
                {

                    stufile<<stu[k].stcourse[i].cid<<" "<<stu[k].stcourse[i].marks<<endl;
                }
                stufile.close();
                csfile.open(csName,ios::trunc);
                for(int i=0;i<u.stc.size();i++)
                {
                   // STUDENTS sp;
                   // sp=stu_hash[u]
                    //u.stc[i].stcourse[j].pq.insert(u.stc[i].sid,u.stc[i].stcourse[j].marks);
                    csfile<<u.stc[i].sid<<endl;

                }
                csfile.close();
                //get_stu();
                //get_course();
}
void CourseUp(int id)
{
    COURSE u=course_hash[id];
    cout<<"Marks updation for :"<<" "<<u.cid<<" "<<u.name<<endl;

     for(int i=0;i<stu.size();i++)
    {
        int val=0;
        mergesort(stu[i].stcourse);
        int j=Binary_search(stu[i].stcourse,u.cid);
        cout<<"Student "<<stu[i].sid<<" "<<j<<endl;
        if(j==-2)continue;
        do{
        cout<<"Enter the marks for student :"<<endl<<stu[i].sid<<" "<<stu[i].name<<" "<<stu[i].stcourse[j].marks<<endl;
        cin>>val;
        if (val>=0 && val<=100)
            break;
        else
        cout<<"Invalid marks.It should be between 0 and 100" << std::endl;
       }while (true);
        cout<<"You've entered: "<<val<<endl;
                stu[i].stcourse[j].marks=val;

               UpdateFile(i,stu[i].sid,id,val,j);
    }
    _getch();
}

int CourseMenu()
{
    system("cls");
    int pos = 1;
    int keyP = 0;
    while (keyP != ENTER)
    {
        int headerX = borderX + borderWidth / 2 - 10;
        Colour(5);
        gotoxy(headerX, borderY + 1);
        printf("*******        ******");
        gotoxy(headerX, borderY + 2);
        printf("******   HOME  *****");
        gotoxy(headerX, borderY + 3);
        printf("******         ******");

        gotoxy(menuX, menuY + 2);
        Colour(3);
        arrowF(1, pos);
        printf("Login Into the Course");

        gotoxy(menuX, menuY + 4);
        Colour(3);
        arrowF(2, pos);
        printf("Exit");

        keyP = _getch();
        if (keyP == DOWN)
        {
            if (pos == 2)
                pos = 1;
            else
                pos++;
        }
        else if (keyP == UP)
        {
            if (pos == 1)
                pos = 2;
            else
                pos--;
        }
    }

    system("cls");
    return pos;
}

void CorReg()
{
    updatelastidT();
    int cid,teach_id;
    double cr;
    string nm,tnm;
    cout<<"Enter course id: ";
    cin>>cid;
    cout<<"Enter course credit: ";
    cin>>cr;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"Enter course name: ";
    getline(cin, nm);
    cout<<"Enter teacher name: ";
    getline(cin, tnm);
    teach_id=lastTid+1;
    cout<<"Assigned ID for the teacher :"<<teach_id<<endl;
    string pass;
    cout<<"Enter a password: ";
    cin>>pass;

    COURSE c;
    c.cid = cid;
    c.credit = cr;
    c.name = nm;
    c.th.tid=teach_id;
    c.th.name=tnm;
    c.th.cid=cid;
    course.push_back(c);
    ofstream outfile("mycourse.txt", ios::app);
    ofstream outTeach("myteach.txt", ios::app);
    outfile<<c.cid<<" "<<c.credit<<" "<<c.name<<endl;
    outTeach<<c.th.tid+10<<" "<<pass<<" "<<c.th.cid<<" "<<tnm<<endl;
    course_hash[cid]=c;
    outfile.close(); outTeach.close();
    cout << "Course added successfully: " << c.cid << " " << tnm<<endl;
    _getch();
}
void updatecq()
{
     for(int i=0;i<course.size();i++)
     {
         for(int j=0;j<course[i].stc.size();j++)
         {
             mergesort(course[i].stc[j].stcourse);
            int x=Binary_search(course[i].stc[j].stcourse,course[i].cid);

            STUDENTS sk;
            sk=stu_hash[course[i].stc[j].sid];
            //sk.stcourse[j].pq.insert(stu[i].sid, sk.stcourse[j].marks);
            //cout<<"CHECK 5 :"<<sk.stcourse[j].pq.isEmpty()<<endl;
            //cout<<" NUmber :"<<x<< " "<<course[i].stc[j].stcourse.size()<<endl;
         }
     }
     _getch();
}
void get_course()
{
     ifstream infile,infileT;
    infile.open("mycourse.txt");infileT.open("myteach.txt");
    if (infile.is_open())
    {
        course.clear();
        while(true)
        {
            COURSE temp;
            if(!(infile>>temp.cid>>temp.credit))break;
            infile.ignore();
            getline(infile,temp.name);

            infileT>>temp.th.tid>>temp.th.tpass>>temp.th.cid;
            infileT.ignore();
            getline(infileT,temp.th.name);
            ifstream pqfile;
            ifstream csfile;
            string csName="CSE"+to_string(temp.cid)+".txt";
            csfile.open(csName);
             if (csfile.is_open())
            {
                 STUDENTS st;
                while (csfile >>st.sid)
                {
                    temp.stc.push_back(st);
                }

            }
             csfile.close();
             course_hash[temp.cid]=temp;
             course.push_back(temp);
        }

    }
     infile.close();



        //_getch();
}
int AdminMM()
{
     system("cls");
    int pos = 1;
    int keyP = 0;
    while (keyP != ENTER)
    {
        int headerX = borderX + borderWidth / 2 - 10;
        Colour(5);
        gotoxy(headerX, borderY + 1);
        printf("*******        ******");
        gotoxy(headerX, borderY + 2);
        printf("******   Admin  *****");
        gotoxy(headerX, borderY + 3);
        printf("******         ******");

        gotoxy(menuX, menuY + 2);
        Colour(3);
        arrowF(1, pos);
        printf("Course Registration");
        gotoxy(menuX, menuY + 4);
        Colour(3);
        arrowF(2, pos);
        printf("Exit");

        keyP = _getch();
        if (keyP == DOWN)
        {
            if (pos == 2)
                pos = 1;
            else
                pos++;
        }
        else if (keyP == UP)
        {
            if (pos == 1)
                pos = 2;
            else
                pos--;
        }
    }
    _getch();
    system("cls");
    return pos;
}
void admMenu()
{

     int x;
    do
    {
        x = AdminMM();
        if (x == 1)
            CorReg();
    } while (x != 2);
}
void AdmL()
{
    string id,pass;
    cout << "Enter your ID: ";
    cin >> id;
    cout << "Enter your Password: ";
    cin >> pass;
    if ("admin" == id && "admin" == pass)
        admMenu();
    else
        cout << "Incorrect Password Or Incorrect ID" << endl;
    _getch();
}
void AdmReg()
{
    string em,pass;
    cout<<"Enter your email :"<<endl;
    cin>>em;
    cout<<"Enter a password :"<<endl;
    cin>>pass;
    _getch();

}
int AdminRM()
{
    system("cls");
    int pos = 1;
    int keyP = 0;
    while (keyP != ENTER)
    {
        int headerX = borderX + borderWidth / 2 - 10;
        Colour(5);
        gotoxy(headerX, borderY + 1);
        printf("*******        ******");
        gotoxy(headerX, borderY + 2);
        printf("******   Admin  *****");
        gotoxy(headerX, borderY + 3);
        printf("******         ******");

        gotoxy(menuX, menuY + 2);
        Colour(3);
        arrowF(1, pos);
        printf("Login");


        gotoxy(menuX, menuY + 4);
        Colour(3);
        arrowF(2, pos);
        printf("Exit");

        keyP = _getch();
        if (keyP == DOWN)
        {
            if (pos == 2)
                pos = 1;
            else
                pos++;
        }
        else if (keyP == UP)
        {
            if (pos == 1)
                pos = 2;
            else
                pos--;
        }
    }
    _getch();
    system("cls");
    return pos;
}
void AdminM()
{

     int x;
    do
    {
        x = AdminRM();
        if (x == 1)
            AdmL();
    } while (x != 2);
}
void CorL()
{
    string pass;
    int id;
    cout<<"Enter Course ID : "<<endl;
    cin>>id;
    cout<<"Enter your Teacher Password : "<<endl;
    cin>>pass;
    if(course_hash[id].th.tpass==pass)
    {
        cout<<"Login Successfull"<<endl;
        courseDash(id);
    }
    else cout<<"INvalid"<<endl;
   _getch();

}
void About()
{
    cout<<"It is a Student Report Card System"<<endl;
    _getch();
}
void Credit()
{
    cout<<"Jillur Rahman Riyad - C231019 - 3AM -CSE"<<endl;
    cout<<"Aftakil Hossain Fahim -C231034 - 3AM -CSE"<<endl;
    cout<<"Mohammad Nazim Uddin - C231020 - 3AM -CSE"<<endl;
    _getch();
}

void CourseM()
{
    int x;
    do
    {
        x = CourseMenu();
        if (x == 1)
            CorL();
    } while (x != 2);
}

int main()
{
    get_stu();
    get_course();
    //updatecq();
    for(int i=1;i<=100;i++)
    mp[i]=-1;
    //get_all();
    int x;
    do
    {
        x = WELCOME();
        if (x == 1)
           About();
        else if (x == 2)
            studentM();
        else if (x == 3)
            CourseM();
        else if (x == 4)
           AdminM();
        else if (x == 5)
            Credit();
    } while (x != 6);

    return 0;
}

