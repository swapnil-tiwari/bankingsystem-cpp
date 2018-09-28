#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <conio.h>
#include <ctime>
#include <iomanip>

using namespace std;

int counter=-1;
//Classes
class BANK
{
protected:
    long long acc_no;
public:
    BANK();
    long long get_accno();
    void set_accno(long long);

};

class ACCOUNT: public BANK
{
    string name;
    string phone_no;
    string address;
    string email ;
    int amount_initial;
public:
    void add_account();
    void assign_accno();
    string get_name();
    string get_phone_no();
    string get_address();
    string get_email();
    int get_amount_i();
    void set_values (long long, string, string, string,string,int);
    ACCOUNT();


};
//Member Functions
ACCOUNT::ACCOUNT()
{
    amount_initial=0;
}

BANK::BANK()
{
    acc_no=100000;
}
long long BANK::get_accno()
{
    return acc_no;
}
void ACCOUNT::add_account()
{
    cout<<endl<<"----------------------------------------------------------------------------------------------------------"<<endl;
    cout<<endl<<"\t     ENTER DETAILS";
    cout<<endl<<"\t   ------------------";
    cin.ignore();
    cout<<endl<<"Enter your name: ";      getline(cin,name);
    cout<<endl<<"Enter Mobile number: ";  getline(cin,phone_no);
    cout<<endl<<"Enter your address: ";   getline(cin,address);
    cout<<endl<<"Enter your email id: ";  getline(cin,email);
    do {
    cout<<endl<<"Enter the opening amount(must be greater than 1000): ";
    cin>>amount_initial;

    }
    while (amount_initial<1000);
    cout<<endl<<"Thanks for your effort, Your account has been opened successfully ";
    assign_accno();
    cout<<endl<<endl<<"Your account number is: "<<acc_no;


}
void ACCOUNT::assign_accno()
{
    unsigned int sval;
    time_t t;
    sval=(unsigned)time(&t);
    srand(sval);
    acc_no+=rand();
}

string ACCOUNT:: get_name()
{
    return name;
}
string ACCOUNT:: get_phone_no()
{
    return phone_no;
}
string ACCOUNT::get_email()
{
    return email;
}
int ACCOUNT::get_amount_i()
{
    return amount_initial;
}

string ACCOUNT::get_address()
{
    return address;
}
void ACCOUNT::set_values(long long a_no, string n,string p, string adrs, string mail, int amount)
{
    acc_no=a_no;
    name=n;
    phone_no=p;
    address=adrs;
    email=mail;
    amount_initial=amount;
}
// Stacks Implementation
struct NODE
{
    string name;
    string phone_no;
    string address;
    string email ;
    int amount_initial;
    int amount_entered;
    long long acc_no;
    NODE *next;
};
NODE *head=NULL;

void push(ACCOUNT newacc)
{
    NODE *temp=new NODE;
    temp->name=newacc.get_name();
    temp->phone_no=newacc.get_phone_no();
    temp->address=newacc.get_address();
    temp->email=newacc.get_email();
    temp->amount_initial=newacc.get_amount_i();
    temp->acc_no=newacc.get_accno();
    temp->next=head;
    head=temp;
}
NODE *pop()
{
    NODE *temp=head;
    head=head->next;
    return temp;

}
// File Functions
void read_file()
{
    long long acc_no;
    string name;
    string phone_no;
    string address;
    string email ;
    int amount_initial;
    ACCOUNT read;
    ifstream fin("Details.TXT", ios::in);
    fin.seekg(0);
    while(fin)
    {
        push(read);
        counter++;
        fin>>acc_no;
        fin>>name;
        fin>>phone_no;
        fin>>address;
        fin>>email;
        fin>>amount_initial;
        read.set_values(acc_no,name,phone_no,address,email,amount_initial);


    }
    fin.close();
}
void write_file()
{
    NODE *write;
    ofstream fout;
    fout.open("Details.TXT",ios::out);
    while(head->next!=NULL)
    {
        write=pop();
        fout<<write->acc_no<<endl;
        fout<<write->name<<endl;
        fout<<write->phone_no<<endl;
        fout<<write->address<<endl;
        fout<<write->email<<endl;
        fout<<write->amount_initial<<endl;

    }
    fout.close();
}
//Other Functions
void deposit_amount(long long user_acc, int amount_change)
{
    NODE *temp=head;
    while(temp->next!=NULL)
    {
        if(temp->acc_no==user_acc)
        {
            temp->amount_initial+=amount_change;

        }
        temp=temp->next;
    }
            cout<<endl<<"Thank You, amount added successfully: ";


}
void withdraw_amount(long long user_acc, int amount_change)
{
    NODE *temp=head;
    while(temp->next!=NULL)
    {
        if(temp->acc_no==user_acc)
        {
            if (amount_change<temp->amount_initial)
            {
               temp->amount_initial-=amount_change;
            }
            else
            {
                cout<<endl<<"Insufficient Funds";
                return;
            }


        }
        temp=temp->next;
    }



}
void display_node(NODE *temp)
{
    cout<<endl<<"\t_____________________________________________________________";
    cout<<endl<<"\t          ACCOUNT DETAILS";
    cout<<endl<<"\t        --------------------";
    cout<<endl<<"\tName: "<<temp->name<<endl;
    cout<<endl<<"\tMobile Number: "<<temp->phone_no<<endl;
    cout<<endl<<"\tAddress: "<<temp->address<<endl;
    cout<<endl<<"\tEmail ID: "<<temp->email<<endl;
    cout<<endl<<"\tAmount: "<<temp->amount_initial;
    cout<<endl<<"\t______________________________________________________________";
}
void print_details(long long user_acc)
{

    NODE *temp=head;
    while(temp->next!=NULL)
    {
        if(temp->acc_no==user_acc)
        {

            display_node(temp);
        }
        temp=temp->next;
    }


}
bool check_accno(long long user_acc)
{
    NODE *temp=head;
    while (temp->next!=NULL)
    {
      if (temp->acc_no==user_acc)
    {
        return true;
    }
        temp=temp->next;
    }


    return false ;

}
int tell_position(long long user_acc)
{
    int n=1;
    NODE *temp=head;
    while(temp->next!=NULL)
    {
        if(temp->acc_no==user_acc)
        {
            return n;
        }
        temp=temp->next;
        n++;
    }
}

void delete_node(long long user_acc)
{
    NODE *temp1=head;
   int pos=0;
   pos=tell_position(user_acc);
   if (pos==1)
   {
       head=temp1->next;
       delete temp1;
       return;
   }
    for (int i=0;i<pos-2;i++)
    {
        temp1=temp1->next;
    }
    NODE *temp2=temp1->next;
    temp1->next=temp2->next;
    delete temp2;
}
void print_time()
{
    string month[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    string day[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
    time_t timer;
    tm *time;
    const int BASE_YEAR = 1900;
     std::time(&timer);
    time = localtime(&timer);
    cout << "Current Date: " << day[time->tm_wday] << " "
              << month[time->tm_mon] << " " << time->tm_mday
              << " " << (time->tm_year + BASE_YEAR);
    cout << "\nCurrent Time:  " << std::setw(2) << std::setfill('0')
              << time->tm_hour << " : " << std::setw(2) << std::setfill('0')
              << time->tm_min << " : " << std::setw(2) << std::setfill('0')
              << time->tm_sec;

}
//Main
int main()
{



    read_file();

    ACCOUNT newacc;
    long long user_acc;
    int amount_change;
    int n1,n2;
    char ch;
    cout<<endl;
    cout<<endl<<endl<<endl<<endl;
    cout<<"                                               "<<" _____________________________________________________________________ "<<endl;
    cout<<"                                               "<<"|---------------------------------------------------------------------|"<<endl;
    cout<<"                                               "<<"|.....................................................................|"<<endl;
    cout<<"                                               "<<"|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|"<<endl;
    cout<<"                                               "<<"|                              WELCOME                                |"<<endl;
    cout<<"                                               "<<"|                        TO THE BANKING SYSTEM                        |"<<endl;
    cout<<"                                               "<<"|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|"<<endl;
    cout<<"                                               "<<"|.....................................................................|"<<endl;
    cout<<"                                               "<<"|---------------------------------------------------------------------|"<<endl;
    cout<<"                                               "<<"|_____________________________________________________________________|"<<endl;
    cout<<endl;
    print_time();
    cout<<endl;
    system("pause");
    system("cls");
    print_time();
    cout<<endl;
    cout<<endl<<"TOTAL ACCOUNTS PRESENT : "<<counter<<endl<<"_____________________________________________________________________________________________________________________"<<endl;
    cout<<endl<<"\t _______________________ ";
    cout<<endl<<"\t|                       |";
    cout<<endl<<"\t|     1.New user        |";
    cout<<endl<<"\t|                       |";
    cout<<endl<<"\t|     2.Existing user   |";
    cout<<endl<<"\t|                       |";
    cout<<endl<<"\t|     3.Exit            |";
    cout<<endl<<"\t|_______________________|"<<endl;
    cout<<endl<<"Enter your choice: "; cin>>n1;
    switch(n1)

    {

      case 1:  do
    {
        system("cls");

        print_time();
        cout<<endl;

        cout<<endl<<"\t _________________________ ";
        cout<<endl<<"\t|                         |";
        cout<<endl<<"\t|   1.Open a new account  |";
        cout<<endl<<"\t|                         |";
        cout<<endl<<"\t|   2.Exit                |";
        cout<<endl<<"\t|_________________________|"<<endl;
        cout<<endl<<"Enter you choice: ";
        cin>>n2;
        switch (n2)
        {
            case 1: newacc.add_account();
                    push(newacc);
                    break;
            case 2: write_file();
                    return 0;

        }
        cout<<endl<<endl<<"Want to open more accounts:(y/n) ";
        cin>>ch;
    }
    while(ch=='y'||ch=='Y');

      case 2: do
    {
        system ("cls");
        print_time();
        cout<<endl;

        cout<<endl<<"\t ______________________________";
        cout<<endl<<"\t|------------------------------|";
        cout<<endl<<"\t|    1. Deposit amount         |";
        cout<<endl<<"\t|                              |";
        cout<<endl<<"\t|    2. Withdraw amount        |";
        cout<<endl<<"\t|                              |";
        cout<<endl<<"\t|    3. View Details           |";
        cout<<endl<<"\t|                              |";
        cout<<endl<<"\t|    4. Close account          |";
        cout<<endl<<"\t|                              |";
        cout<<endl<<"\t|    5. Exit                   |";
        cout<<endl<<"\t|------------------------------|";
        cout<<endl<<"\t|______________________________|";
        cout<<endl;
        cout<<endl<<"Enter your choice: ";
        cin>>n2;
        switch (n2)
        {

            case 1: cout<<endl<<"--------------------------------------------------------------------------------------------------------";
                    cout<<endl<<"Enter account number: ";
                    cin>>user_acc;
                    while(!check_accno(user_acc))
                    {
                      cout<<endl<<"Wrong account number entered, Enter again: ";
                      cin>>user_acc;
                    }

                    cout<<endl<<"Enter amount to be deposited: ";
                    cin>>amount_change;
                    deposit_amount(user_acc,amount_change);

                    break;
            case 2: cout<<endl<<"---------------------------------------------------------------------------------------------------------";
                    cout<<endl<<"Enter account number: ";
                    cin>>user_acc;
                    while(!check_accno(user_acc))
                    {
                      cout<<endl<<"Wrong account number entered, Enter again: ";
                      cin>>user_acc;
                    }
                    cout<<endl<<"Enter amount to be withdrew: ";
                    cin>>amount_change;
                    withdraw_amount(user_acc,amount_change);
                    cout<<endl<<"Thank You!";
                    break;


            case 3: cout<<endl<<"---------------------------------------------------------------------------------------------------------";
                    cout<<endl<<"Enter account number: ";
                    cin>>user_acc;
                    while(!check_accno(user_acc))
                    {
                      cout<<endl<<"Wrong account number entered, Enter again: ";
                      cin>>user_acc;
                    }
                    print_details(user_acc);
                    break;
            case 4: cout<<endl<<"---------------------------------------------------------------------------------------------------------";
                    cout<<endl<<"Enter account number: ";
                    cin>>user_acc;
                    while(!check_accno(user_acc))
                    {
                      cout<<endl<<"Wrong account number entered, Enter again: ";
                      cin>>user_acc;
                    }
                     //n=tell_position(user_acc);
                     delete_node(user_acc);
                     cout<<endl<<"Account deleted successfully";
                    break;
            case 5: write_file();
                    return 0;

        }
        cout<<endl<<endl<<"Continue:(y/n) ";
        cin>>ch;
    }
        while(ch=='y'||ch=='Y');
        break;

        case 3: write_file();
                return 0;
    }

      write_file();
}

//End
