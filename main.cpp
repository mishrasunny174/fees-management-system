/**
 *  this program is a simple fees management system
 *  designed for a school project
 *  source code is available freely
 *  under GNU Open Source License
 *  @author Sunny Mishra
 */

#include <iostream> //for basic stdin and stdout founctions
#include <string.h> //for stcpy() and strcat()
#include <stdlib.h> //for atoi() and system()
#include <stdio.h> //for rename() and remove()
#include <fstream> //for streaming files
#include <iomanip> //for setw() and setfill()
#include <ctime> //for time related things

using namespace std;

/*----------------------------class definition starts----------------------------*/

class Student //class student fro students
{
    int rollNo; //variables are self explainable by there names
    long mobNo;
    int addmissionNo;
    char name[20];
    char fathersName[25];
public:
    void add(); //function prototype for adding student
    int getRollNo() { return rollNo; } //getter function to get roll number
    char* getName() { return name; } //getter function to get name
    void display(); //function prototype to display details of student
    int getAdmNo() { return addmissionNo; }

};

void Student::add() //add function for student class
{
    cout<<"### Student Registration ###"<<endl;
    cin.ignore();
    cout<<"Enter students name: ";
    cin.getline(name,20);
    cout<<"Enter roll no: ";
    cin>>rollNo;
    cout<<"Enter admission no: ";
    cin>>addmissionNo;
    cin.ignore();
    cout<<"Enter Fathers name: ";
    cin.getline(fathersName,25);
    cout<<"Enter mobile no: ";
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
    bool feeStatus;
    char date[25];
public:
    Fees(){}
    Fees(int clas);
    void display(bool ); //function to display fees status
    void setDate(char* temp)
    {
        strcpy(date,temp);
    }
    void payFees();
    void add();
    float getMonthlyFees()
    {
        return monthlyFees;
    }
    bool isFeesPaid()
    {
        return feeStatus;
    }
    char* getDate()
    {
        return date;
    }
};

Fees::Fees(int clas) //add function for Student class
{
    Student::add(); //calling student add function
    if(clas<=5)
        monthlyFees=550;
    else if(clas<=10)
        monthlyFees=750;
    else if(clas==11)
        monthlyFees=1100;
    else
        monthlyFees=1600;
    feeStatus=false;
    strcpy(date,"N/A");
}

void Fees::display(bool all = false)
{
    if(all)
    {
        cout<<setw(1)<<"|"<<setfill(' ')<<setw(6)<<left<<getAdmNo();
        cout<<setw(1)<<"|"<<setw(8)<<left<<getRollNo();
        cout<<setw(1)<<"|"<<setw(20)<<left<<getName();
        if(feeStatus)
            cout<<setw(1)<<"|"<<setw(10)<<left<<"PAID";
        else
            cout<<setw(1)<<"|"<<setw(10)<<left<<"DUE";
        cout<<setw(1)<<"|"<<setw(30)<<left<<date<<setw(1)<<"|"<<endl;
    }
    else
    {
        Student::display();
        cout<<"\n### FEES STATUS ###"<<endl;
        cout<<"Monthly Fees: "<<monthlyFees<<endl;
        cout<<"Fee Status: ";
        if(feeStatus)
        {
            cout<<"paid"<<endl;
            cout<<"payment date: "<<date<<endl;
        }
        else
            cout<<"unpaid"<<endl;
    }

}

void Fees::payFees()
{
    time_t rawtime;
    time(&rawtime);
    feeStatus=true;
    strcpy(date,ctime(&rawtime));
}

/*----------------------------class definition ends-------------------------------*/

/*----------------------------function prototypes starts--------------------------*/

void searchStudent(char*);//function to search student and display their status
long fileSearch(char*,int);//function to perform search using roll no
long fileSearch(char*,char*); //function to perform search using name
void pause(); //function to pause the program
void getFileName(char*); //function to assemble filename
void payFees(char*,bool); //function to pay fees
void listPaid(char*); //function to list all students (fees paid) of a class
void listUnpaid(char*); //function to list students (fees unpaid) of a class
void addStudent(char*); //function to add student to data base
void delStudent(char*); //function to delete a student from database
void browseDatabase(); //function to view database
void manageStudents(); //function to manage students in database
void summarize(char*); //to create summary of total fees paid and unpaid
void fileError(); //function to show file error message
void studentNotFoundError();// function to show student not found error
void getMonth(char*); //function to input correct month
void getClas(char*); //function to input correct class
void banner(); //function to show program banner
void paymentportal(); //sub menu for payment function
void showAll(char* ); //function to show all students
void drawLine(); //to draw line in table
void writeHeadLine(); //to write headline of table

/*----------------------------function prototypes ends----------------------------*/

/*----------------------------main function starts--------------------------------*/

int main()
{
    int choice;
    while(1) //infinity main menu loop exit via break statement
    {
        banner();
        cout<<"1- Payment portal"<<endl;
        cout<<"2- Browse Database"<<endl;
        cout<<"3- Manage Database"<<endl;
        cout<<"Enter 0 to exit..."<<endl<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 0:
            exit(1);
            break;
        case 1:
            paymentportal(); //sub menu for payment
            break;
        case 2:
            browseDatabase(); //sub menu for browsing database
            break;
        case 3:
            manageStudents(); //sub menu for managing students
            break;
        default:
            cout<<"Error wrong choice try again..."<<endl;
            pause();
        }
    }
}

/*----------------------------main function ends----------------------------------*/

/*----------------------------function definition starts--------------------------*/
void pause()
{
    cout<<"Press enter to continue...";
    cin.ignore();
    cin.get();
}

void banner()
{
    system("clear"); //change it to cls to make it work in windows
    cout<<"############  T. I. C.  ############"<<endl;
    cout<<"###### FEES MANAGEMENT SYSTEM ######"<<endl<<endl;
    time_t rawTime; // time is a alias for storing time
    time(&rawTime); //getting no of seconds till unix standard time stamp
    tm *local; //declaring a pointer of struct type tm
    local = localtime(&rawTime); //converting rawtime to tm structure
    cout<<"Date: "<<local->tm_mday<<'/'<<local->tm_mon+1; //now the program will
    cout<<'/'<<1900+local->tm_year<<endl<<endl; //show current system date
}
void fileError()
{
    cout<<"ERROR while opening database!!!"<<endl;
    cout<<"Check whether database is created or not!!!"<<endl;
    cout<<"Otherwise contact sys admin"<<endl;
}

void studentNotFoundError()
{
    cout<<"Student not found in database check roll no and try again"<<endl;
    cout<<"Also make sure you added the student to database first"<<endl;
    cout<<"If error still persist contact sys admin"<<endl;
}

void drawLine()
{
    cout<<setw(1)<<"+"<<setfill('-')<<setw(6)<<"-";
    cout<<setw(1)<<"+"<<setw(8)<<"-";
    cout<<setw(1)<<"+"<<setw(20)<<"-";
    cout<<setw(1)<<"+"<<setw(10)<<"-";
    cout<<setw(1)<<"+"<<setw(30)<<"-";
    cout<<setw(1)<<"+"<<endl;
}

void writeHeadLine()
{
    cout<<setw(1)<<"|"<<setfill(' ')<<setw(6)<<left<<"Adm No";
    cout<<setw(1)<<"|"<<setw(8)<<left<<"Roll No";
    cout<<setw(1)<<"|"<<setw(20)<<left<<"Name";
    cout<<setw(1)<<"|"<<setw(10)<<left<<"Fee Status";
    cout<<setw(1)<<"|"<<setw(30)<<left<<"Date Of Payment"<<setw(1)<<"|"<<endl;
}
void getMonth(char* month)
{
    while(1)
    {
        cout<<"Enter month ( 1 to 12 ): ";
        cin>>month;
        if(!(atoi(month)<=12&&atoi(month)>=1))
        {
            cout<<"ERROR wrong input try again..."<<endl;
            pause();
        }
        else
            break;
    }
}

void getClas(char* clas)
{
    while(1)
    {
        cout<<"Enter class ( 1 to 12 ): ";
        cin>>clas;
        if(!(atoi(clas)<=12&&atoi(clas)>=1))
        {
            cout<<"ERROR wrong input try again..."<<endl;
            pause();
        }
        else
            break;
    }
}
void getFileName(char* fileName,char* month,char* clas)
{
    strcpy(fileName,"database/");
    strcat(fileName,month);
    strcat(fileName,clas);
    strcat(fileName,".dat");
}

long fileSearch(char* fileName,int rollNo)
{
    Fees temp;
    long location;
    ifstream file(fileName,ios::in|ios::binary);
    if(!file)
    {
        fileError();
        pause();
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

long fileSearch(char* fileName,char* name)
{
    Fees temp;
    long location;
    ifstream file(fileName,ios::in|ios::binary);
    if(!file)
    {
        fileError();
        pause();
    }

    else
    {
        file.seekg(ios::beg);
        location=file.tellg();
        while(file.read((char*)&temp,sizeof(Fees)))
        {
            if(strcmp(temp.getName(),name)==0)
                return location;
            location=file.tellg();
        }
    }
    return -1;
}

void searchStudent(char* fileName)
{
    banner();
    int rollNo;
    ifstream file;
    Fees temp;
    long location=-1;
    file.open(fileName,ios::in|ios::binary);
    if(file)
    {
        cout<<"Enter roll no: ";
        cin>>rollNo;
        location=fileSearch(fileName,rollNo);
        if(location!=-1)
        {
            file.seekg(location);
            file.read((char*)&temp,sizeof(Fees));
            temp.display();
        }
        else
            studentNotFoundError();
        file.close();
    }
    else
        fileError();
    pause();
}

void payFees(char* fileName,bool searchByName)
{
    banner();
    Fees temp;
    fstream file;
    int rollNo;
    char choice;
    char name[25];
    long location=-1;
    file.open(fileName,ios::in|ios::binary|ios::out);
    if (file)
    {
        if(!searchByName)
        {
            cout<<"Enter roll no: ";
            cin>>rollNo;
            location=fileSearch(fileName,rollNo);
        }
        else
        {
            cout<<"Enter name: ";
            cin.ignore();
            cin.getline(name,25);
            location=fileSearch(fileName,name);
        }
        if(location!=-1)
        {
            file.seekg(location);
            file.read((char*)&temp,sizeof(Fees));
            banner();
            temp.display();
            if(!temp.isFeesPaid())
            {
                cout<<"Amount to submit: "<<temp.getMonthlyFees()<<endl;
                cout<<"pay amount (y/n): ";
                cin.ignore();
                cin.get(choice);
                if(choice=='y'||choice=='Y')
                {
                    temp.payFees();
                    file.seekp(location);
                    file.write((char*)&temp,sizeof(Fees));
                    cout<<"database updated successfully"<<endl;
                }
                else
                    cout<<"exiting to main menu"<<endl;
            }
            else
                cout<<"fees already paid..."<<endl;
        }
        else
            studentNotFoundError();
        file.close();
    }
    else
        fileError();
    pause();
}

void listPaid(char *fileName)
{
    banner();
    Fees temp;
    ifstream file(fileName,ios::in|ios::binary);
    if(file)
    {
        drawLine();
        writeHeadLine();
        drawLine();;
        while(file.read((char*)&temp,sizeof(Fees)))
        {
            if(temp.isFeesPaid())
            {
                temp.display(true);
                drawLine();
            }
        }
    }
    else
        fileError();
    pause();
}

void listUnpaid(char *fileName)
{
    banner();
    Fees temp;
    ifstream file(fileName,ios::in|ios::binary);
    if(file)
    {
        drawLine();
        writeHeadLine();
        drawLine();
        while(file.read((char*)&temp,sizeof(Fees)))
        {
            if(!temp.isFeesPaid())
            {
                temp.display(true);
                drawLine();
            }
        }
    }
    else
        fileError();
    pause();
}

void addStudent(char *fileName,char* clas)
{
    banner();
    char choice;
    Fees temp(atoi(clas));
    ofstream file(fileName,ios::out|ios::binary|ios::app);
    if(file)
    {
        cout<<"Sure to submit details to database (y/n): ";
        cin.ignore();
        cin.get(choice);
        if(choice=='y'||choice=='Y')
        {
            file.write((char*)&temp,sizeof(Fees));
                cout<<"database updated successfully"<<endl;
        }
        else
            cout<<"exiting to main menu"<<endl;
    }
    else
        fileError();
    pause();
}

void delStudent(char *fileName)
{
    banner();
    int rollNo;
    char choice;
    cout<<"Enter roll no: ";
    cin>>rollNo;
    Fees temp;
    ifstream file(fileName,ios::in|ios::binary);
    ofstream tempFile("database/temp.dat",ios::binary|ios::out|ios::trunc);
    if(file&&tempFile)
    {
        while(file.read((char*)&temp,sizeof(Fees)))
        {
            if(temp.getRollNo()==rollNo)
            {
                temp.display();
                cout<<"sure to delete (y/n): ";
                cin.ignore();
                cin.get(choice);
                if(choice=='y'||choice=='Y')
                    continue;
                else
                {
                    cout<<"Exiting to main menu..."<<endl;
                    remove("database/temp.dat");
                    goto mainMenu;
                }
            }
            tempFile.write((char*)&temp,sizeof(Fees));
        }
        file.close();
        tempFile.close();
        remove(fileName);
        rename("database/temp.dat",fileName);
        cout<<"Record deleted successfully"<<endl;

    }
    else
        fileError();
mainMenu:
    pause();
}

void browseDatabase()
{
    int choice;
    banner();
    char month[3];
    char clas[3];
    char fileName[30];
    getMonth(month);
    getClas(clas);
    getFileName(fileName,month,clas);
    while(1)
    {
        banner();
        cout<<"######### Database Browser #########"<<endl;
        cout<<"Class: "<<clas<<"\t\tMonth: "<<month<<endl<<endl;
        cout<<"1- Search student in database"<<endl;
        cout<<"2- List students(fees paid)"<<endl;
        cout<<"3- List students(fees not paid)"<<endl;
        cout<<"4- Summary of collected fees"<<endl;
        cout<<"5- Return to main menu "<<endl;
        cout<<"Enter 0 to exit..."<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 0:
            pause();
            exit(1);
        case 1:
            searchStudent(fileName);
            break;
        case 2:
            listPaid(fileName);
            break;
        case 3:
            listUnpaid(fileName);
            break;
        case 4:
            summarize(fileName);
            break;
        case 5:
            goto mainMenu;
            break;
        default:
            cout<<"Error wrong choice try again..."<<endl;
            pause();
        }
    }
mainMenu:
    pause();
}

void manageStudents()
{
    int choice;
    banner();
    char month[3];
    char clas[3];
    char fileName[30];
    getMonth(month);
    getClas(clas);
    getFileName(fileName,month,clas);
    while(1)
    {
        banner();
        cout<<"######## Database Management ########"<<endl;
        cout<<"Class: "<<clas<<"\t\tMonth: "<<month<<endl<<endl;
        cout<<"1- Add student in database"<<endl;
        cout<<"2- Delete student from database"<<endl;
        cout<<"3- Show all students in database"<<endl;
        cout<<"4- Return to Main Menu"<<endl;
        cout<<"Enter 0 to exit..."<<endl<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 0:
            pause();
            exit(1);
        case 1:
            addStudent(fileName,clas);
            break;
        case 2:
            delStudent(fileName);
            break;
        case 3:
            showAll(fileName);
            break;
        case 4:
            goto mainMenu;
            break;
        default:
            cout<<"Error wrong choice try again..."<<endl;
            pause();
        }
    }
mainMenu:
    pause();
}

void summarize(char* fileName)
{
    banner();
    int countPaid=0;
    int countUnpaid=0;
    Fees temp;
    ifstream file(fileName,ios::in|ios::binary);
    if(file)
    {
        while(file.read((char*)&temp,sizeof(Fees))) //counting number of
        {                                           //paid and unpaid
            if(temp.isFeesPaid())                   //students
                countPaid++;
            else
                countUnpaid++;
        }
        cout<<"No of students (fees paid): "<<countPaid<<endl;
        cout<<"No of students (fees unpaid): "<<countUnpaid<<endl;
        cout<<"Total amount collected: "<<countPaid*temp.getMonthlyFees()<<endl;
    }
    else
        fileError();
    pause();
}

void paymentportal()
{
    banner();
    char month[3];
    char clas[3];
    char fileName[30];
    getMonth(month);
    getClas(clas);
    getFileName(fileName,month,clas);
    int choice;
    while(1)
    {
        banner();
        cout<<"########## Payment Portal ##########"<<endl;
        cout<<"Class: "<<clas<<"\t\tMonth: "<<month<<endl<<endl;
        cout<<"1- Pay fees by roll no"<<endl;
        cout<<"2- Pay fees by name:"<<endl;
        cout<<"3- Return to main menu"<<endl;
        cout<<"Enter 0 to exit..."<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 0:
            pause();
            exit(2);
        case 1:
            payFees(fileName,false);
            break;
        case 2:
            payFees(fileName,true);
            break;
        case 3:
            goto mainMenu;
            break;
        default:
            cout<<"Error wrong choice try again..."<<endl;
            pause();
        }
    }
mainMenu:
    pause();
}

void showAll(char* fileName)
{
    banner();
    Fees temp;
    fstream file(fileName,ios::in|ios::binary);
    if(file)
    {
        drawLine();
        writeHeadLine();
        drawLine();
        while(file.read((char*)&temp,sizeof(Fees)))
        {
            temp.display(true);
            drawLine();
        }
    }
    else
        fileError();
    pause();
}
/*----------------------------function definition ends----------------------------*/
