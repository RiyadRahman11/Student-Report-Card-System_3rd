#include<bits/stdc++.h>
using namespace std;

double gpa(int mark)
{
    if(mark>=0 && mark<=39) return 0.00;//F
    else if(mark>=40 && mark<=44)return 2.00;//D
    else if(mark>=45 && mark<=49) return 2.25;
    else if(mark>=50 && mark<=54) return 2.50;
    else if(mark>=55 && mark<=59) return 2.75;
    else if(mark>=60 && mark<=64) return 3.00;
    else if(mark>=65 && mark<=69) return 3.25;
    else if(mark>=70 && mark<=74) return 3.50;
    else if(mark>=75 && mark<=79) return 3.75;
    else if(mark>=80 && mark<=100) return 4.00;
    else return -1.0;

}
string grade(int mark)
{
    if(mark>=0 && mark<=39) return "F";//F
    else if(mark>=40 && mark<=44)return "D";//D
    else if(mark>=45 && mark<=49) return "C-";
    else if(mark>=50 && mark<=54) return  "C";
    else if(mark>=55 && mark<=59) return "B";
    else if(mark>=60 && mark<=64) return "B-";
    else if(mark>=65 && mark<=69) return "B+";
    else if(mark>=70 && mark<=74) return "A-";
    else if(mark>=75 && mark<=79) return "A";
    else if(mark>=80 && mark<=100) return "A+";
    else return "N/A";

}
vector<int> toIntV(string& str) {
    vector<int> num;
    int start = 0,last=0;

   int i=0;
    int n = str.size();

    while (i<n) {

        while (i<n&&str[i]==' ')
            i++;
        if (i>=n) break;
        int j= i;
        while (j<n &&str[j]!=' ') {
            j++;
        }
        num.push_back(stoi(str.substr(i,j-i)));
        i=j;
    }

    return num;
    }
void merge(vector<COURSE> &vt,int start,int mid,int end)
{
    int n=end-start+1;
    vector<COURSE> sorted(n);
    int indA=start,indB=mid+1,i=0,j;
    while(indA<=mid && indB<=end)
    {
        if(vt[indA].marks<=vt[indB].marks)
            sorted[i++]=vt[indA++];
        else
            sorted[i++]=vt[indB++];
    }
    while(indA<=mid)
    {
        sorted[i++]=vt[indA++];
    }
     while(indB<=end)
    {
        sorted[i++]=vt[indB++];
    }
    for(i=0,j=start;i<n;i++,j++)
    {
        vt[j]=sorted[i];
    }

}

void divide(vector<COURSE> &vt,int start,int end)
{
    if(start>=end)return;
    int mid=(start+end)/2;
    divide(vt,start,mid);
    divide(vt,mid+1,end);
    merge(vt,start,mid,end);

}
void mergesort(vector<COURSE> &vt)
{
    //divide(arr,0,n-1);
    divide(vt,0,vt.size()-1);
}
int Binary_search(vector<COURSE> &vt,int item)
{
    int lo=0,hi=vt.size()-1;
    while(lo<=hi)
    {
        int mid=(lo+hi)/2;
        if(vt[mid].cid==item)return mid;
        else if(vt[mid].cid<item)lo=mid+1;
        else hi=mid-1;
    }
    return -2;
}

double weight_avg(vector<COURSE>u)
{
    int tW=0;
    double value=0;
    for(auto c:u)
    {
        tW+=c.cgpa;
        value+=(c.cgpa*c.marks);
    }
    return floor(value/tW);

}


void heapify(vector<COURSE>& arr, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;


    if (left < n && arr[left].marks < arr[smallest].marks)
        smallest = left;


    if (right < n && arr[right].marks < arr[smallest].marks)
        smallest = right;


    if (smallest != i) {
        swap(arr[i], arr[smallest]);


        heapify(arr, n, smallest);
    }
}


void heapsort(vector<COURSE>& arr) {
    int n = arr.size();


    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);


    for (int i = n - 1; i > 0; i--) {

        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
void display(const vector<COURSE>& arr) {
    for (const auto& course : arr) {
        cout << course.marks << " ";
    }
    cout << endl;
}





