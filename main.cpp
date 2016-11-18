/**
 *  this program is a simple fees management system
 *  designed for a school project
 *  @author
 *  source code is available freely
 *  at https://github.com/mishrasunny174/fees-management-system
 */

#include <iostream> //for basic stdin and stdout founctions
#include <string.h> //for stcpy() and strcat()
#include <stdlib.h> //for atoi()
#include <stdio.h> //for rename() and remove()
#include <fstream> //for streaming files
#include <iomanip> //for setw() and setfill()

using namespace std;

/*----------------------------class definition starts----------------------------*/

class Student //class student fro students
{
    int rollNo; //variables are self explainable by there names
    long mobNo;
    int addmissionNo;
    char name[25];
    char fathersName[25];
public:
    void add(); //function prototype for adding student
    int getRollNo() { return rollNo; } //getter function to get roll number
    void display(); //function prototype to display details of student
};

void Student::add() //add function for student class
{
    cout<<"### Student Registration ###"<<endl;
    cin.ignore();
    cout<<"Enter students name: ";
    cin.getline(name,25);
    cout<<"Enter roll no: ";
    cin>>rollNo;
    cout<<"Enter admission no: ";
    cin>>addmissionNo;
    cin.ignore();
    cout<<"Enter Fathers name: ";
    cin.getline(fathersName,25);
    cout<<"enter mobile no: ";
    cin>>mobNo;
}

void Student::display() //display function for Student class
{
    cout<<"### STUDENT INFO ####"<<endl;
    cout<<"Name: "<<name<<endl;
    cout<<"Roll no: "<<rollNo<<endl;
    cout<<"Admission No: "<<addmissionNo<<endl;
    cout<<"Fathers Name: "<<fathersName<<endl;
    cout<<"Mob No: "<<mobNo<<endl;
}

class Fees : public Student
{
    float monthlyFees;
    short nOfMonthsPaid;
    short nOfMonthsRem;
public:
    void display(); //function to display fees status
    void payFees(int nOfMonths);
    void add();
    float getmonthlyFees()
    {
        return monthlyFees;
    }
    short getNOfMonthsRem()
    {
        return nOfMonthsRem;
    }
};

void Fees::add() //add function for Student class
{
    Student::add(); //calling student add function to add details of student first
    cout<<"Enter monthly Fees: ";
    cin>>monthlyFees;
    nOfMonthsPaid=0; //assigning fees of paid months to be 0
    nOfMonthsRem=12; //assigning fees rem months to be 12
}


void Fees::payFees(int nOfMonths)
{
    nOfMonthsPaid+=nOfMonths;
    nOfMonthsRem-=nOfMonths;
}

void Fees::display()
{
    Student::display();
    cout<<"\n### FEES STATUS ###"<<endl;
    cout<<"No of Months ( fees not paid ): "<<nOfMonthsRem<<endl;
    cout<<"Monthly Fees: "<<monthlyFees<<endl;
    cout<<"No of months ( paid ): "<<nOfMonthsPaid<<endl;
}

/*----------------------------class definition ends-------------------------------*/

/*----------------------------function prototypes starts--------------------------*/

void searchStudent(char* clas);//function to search student and display their status
long fileSearch(char* fileName,int rollNo);//function to perform real search in file
void pause(); //function to pause the program
void getClass(char *clas); //function to input class
void payFees(char *clas); //function to pay fees
void listPaid(char *clas); //function to list all students (fees paid) of a class
void listUnpaid(char* clas); //function to list students (fees unpaid) of a class
void registerStudent(char* clas); //function to add student to data base
void delStudent(char *clas); //function to delete a student from database

/*----------------------------function prototypes ends----------------------------*/

/*----------------------------main function starts--------------------------------*/

int main()
{
    int choice;
    char clas[3]; //i will convert it to int to compare
    while(1) //infinity main menu loop exit via break statement
    {
home: //home point
        system("clear");
        cout<<"############  T. I. C.  ############"<<endl;
        cout<<"###### FEES MANAGEMENT SYSTEM ######"<<endl<<endl;
        cout<<"1- Search Student to see fee status"<<endl;
        cout<<"2- Pay Fees of a student"<<endl;
        cout<<"3- List all students(Fees incomplete)"<<endl;
        cout<<"4- List all students(Fees fully paid)"<<endl;
        cout<<"5- Register student to database "<<endl;
        cout<<"6- Delete student from database "<<endl;
        cout<<"Enter 0 to exit..."<<endl<<endl;
        cout<<"Enter choice: ";
        cin>>choice;
        switch(choice)
        {
        case 0:
            exit(1);
            break;
        case 1:
            getClass(clas);
            searchStudent(clas);
                cout<<"wrong choice"<<endl;
            break;
        case 2:
            getClass(clas);
            payFees(clas);
            break;
        case 3:
            getClass(clas);
            listUnpaid(clas);
            break;
        case 4:
            getClass(clas);
            listPaid(clas);
            break;
        case 5:
            getClass(clas);
            registerStudent(clas);
            break;
        case 6:
            getClass(clas);
            delStudent(clas);
            break;
        default:
            cout<<"Error wrong choice try again..."<<endl;
            pause();
            goto home;
        }
    }
}

/*----------------------------main function ends----------------------------------*/

void pause()
{
    cout<<"Press enter to continue...";
    cin.ignore();
    cin.get();
}

void getClass(char* clas)
{
    while(1)
    {
        cout<<"Enter class ( 1 to 12 ): ";
        cin>>clas;
        if(!(atoi(clas)<=12&&atoi(clas)>=1))
        {
            cout<<"ERROR wrong input try again...";
            pause();
        }
        else
            break;
    }
}

long fileSearch(char* fileName,int rollNo)
{
    Fees temp;
    long location;
    ifstream file(fileName,ios::in|ios::binary);
    if(!file)
    {
        cout<<"ERROR while opening file!!!\nCheck whether database is created or not!!!"<<endl;
        cout<<"Otherwise contact sys admin"<<endl;
        pause();
        exit(2);
    }
    else
    {
        file.seekg(ios::beg);
        location=file.tellg();
        while(file.read((char*)&temp,sizeof(Fees)))
        {
            if(temp.getRollNo()==rollNo)
                return location;
            location=file.tellg();
        }
    }
    return -1;
}

void searchStudent(char* clas)
{
    system("clear");
    int rollNo;
    ifstream file;
    Fees temp;
    cout<<"Enter roll no: ";
    cin>>rollNo;
    char fileName[10];
    long location=-1;
    strcpy(fileName,clas);
    strcat(fileName,".dat");
    location=fileSearch(fileName,rollNo);
    if (!(location==-1))
    {
        file.open(fileName,ios::in|ios::binary);
        if(file)
        {
            file.seekg(location);
            file.read((char*)&temp,sizeof(Fees));
            temp.display();
        }
        pause();
    }
    else
    {
        cout<<"Student not found in database"<<endl;
        pause();
    }
}

void payFees(char* clas)
{
    system("clear");
    Fees temp;
    fstream file;
    int rollNo;
    int nOfMonths;
    char choice;
    cout<<"Enter roll no: ";
    cin>>rollNo;
    char fileName[10];
    long location=-1;
    strcpy(fileName,clas);
    strcat(fileName,".dat");
    location=fileSearch(fileName,rollNo);
    if (!(location==-1))
    {
        file.open(fileName,ios::in|ios::binary|ios::out);
        file.seekg(location);
        if(file.read((char*)&temp,sizeof(Fees)))
        {
            temp.display();
            cout<<"Enter no of months to pay: ";
            cin>>nOfMonths;
            if(nOfMonths<=temp.getNOfMonthsRem())
            {
                cout<<"Amount to pay: "<<temp.getmonthlyFees()*nOfMonths<<endl;
                cout<<"update database (y/n): ";
                cin.ignore();
                cin.get(choice);
                if(choice=='y')
                {
                    temp.payFees(nOfMonths);
                    file.seekp(location);
                    if(file.write((char*)&temp,sizeof(Fees)))
                        cout<<"wrote to database successfully"<<endl;
                }
                else
                    cout<<"exiting to main menu"<<endl;
            }
            else
                cout<<"sir you are overpaying..."<<endl;
            file.close();
            pause();
        }
    }
    else
    {
        cout<<"Student not found in database"<<endl;
        pause();
    }
}

void listPaid(char *clas)
{
    system("clear");
    char fileName[10];
    strcpy(fileName,clas);
    strcat(fileName,".dat");
    Fees temp;
    ifstream file(fileName,ios::in|ios::binary);
    if(file)
    {
        while(file.read((char*)&temp,sizeof(Fees)))
        {
            if(temp.getNOfMonthsRem()==0)
            {
                cout<<setw(36)<<setfill('-')<<"-"<<endl;
                temp.display();
                cout<<endl;
                cout<<setw(36)<<setfill('-')<<"-"<<endl;
            }
        }
    }
    else
        cout<<"ERROR while opening database contact sys admin"<<endl;
    pause();
}

void listUnpaid(char *clas)
{
    system("clear");
    char fileName[10];
    strcpy(fileName,clas);
    strcat(fileName,".dat");
    Fees temp;
    ifstream file(fileName,ios::in|ios::binary);
    if(file)
    {
        while(file.read((char*)&temp,sizeof(Fees)))
        {
            if(temp.getNOfMonthsRem()!=0)
            {
                cout<<setw(36)<<setfill('-')<<"-"<<endl;
                temp.display();
                cout<<endl;
                cout<<setw(36)<<setfill('-')<<"-"<<endl;
            }
        }
    }
    else
        cout<<"ERROR while opening database contact sys admin"<<endl;
    pause();
}

void registerStudent(char *clas)
{
    system("clear");
    char fileName[10];
    char choice;
    strcpy(fileName,clas);
    strcat(fileName,".dat");
    Fees temp;
    temp.add();
    ofstream file(fileName,ios::out|ios::binary|ios::app);
    if(file)
    {
        cout<<"Sure to write details to database (y/n): ";
        cin.ignore();
        cin.get(choice);
        if(choice=='y'||choice=='Y')
        {
            if(file.write((char*)&temp,sizeof(Fees)))
                cout<<"data written successfully"<<endl;
        }
        else
            cout<<"exiting to main menu"<<endl;
        pause();
    }
}

void delStudent(char *clas)
{
    system("clear");
    char fileName[10];
    int rollNo;
    char choice;
    cout<<"Enter roll no: ";
    cin>>rollNo;
    strcpy(fileName,clas);
    strcat(fileName,".dat");
    Fees temp;
    ifstream file(fileName,ios::in|ios::binary);
    ofstream tempFile("temp.dat",ios::binary|ios::out|ios::trunc);
    if(file&&tempFile)
    {
        while(file.read((char*)&temp,sizeof(Fees)))
        {
            if(temp.getRollNo()==rollNo)
            {
                cout<<"sure to delete (y/n): ";
                cin.ignore();
                cin.get(choice);
                if(choice=='y'||choice=='Y')
                    continue;
                else
                {
                    cout<<"Exiting to main menu..."<<endl;
                    break;
                }
            }
            tempFile.write((char*)&temp,sizeof(Fees));
        }
        file.close();
        tempFile.close();
        remove(fileName);
        rename("temp.dat",fileName);
        cout<<"Record deleted successfully"<<endl;

    }
    else
        cout<<"ERROR while opening database contact sys admin"<<endl;
    pause();
}
