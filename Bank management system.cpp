//Header files used

#include<iostream>
#include<fstream>
#include<ctype.h>
#include<iomanip>
#include<stdio.h>
#define el '\n'

using namespace std;

//class used
class account{
    int acno;
    char name[70];
    int deposit;
    char type;//account type

//***FUNCTION DECLARATIONS***
public:
    void new_acc(); //create new account
    void display_acc(); //display acc data
    void update(); //update with new data from user
    void dep_amt(float); //deposit money into account
    void draw_amt(float); //withdraw money from account
    void report(); //display details in tabular form
    int ret_acno();
    int ret_dep();
    char ret_type();
};
//end of class

//***FUNCTION DEFINITIONS***//
void account::new_acc(){
    cout<<"Enter account number : ";
    cin>>acno;
    cout<<el<<"Enter name of account holder : ";
    gets(name);
    cout<<el<<"Enter account type [S/C] : ";
    cin>>type;
    type=toupper(type);
    cout<<el<<"Enter initial amount [min. 500 for Saving & min.1000 for Current] : ";
    cin>>deposit;
    cout<<el<<"Account created successfully"<<el;
}

void account::display_acc(){
    cout<<"Account Details : "<<el;
    cout<<"Account no. : "<<acno<<el;
    cout<<"Account holder name : "<<name<<el;
    cout<<"Account type : "<<type<<el;
    cout<<"Balance amount : "<<deposit<<el;
}

void account::update(){
    cout<<"Account no. : "<<acno<<el;
    cout<<"Enter new account holder name : ";
    cin>>name;
    cout<<el<<"Enter account type [C/S] : ";
    cin>>type;
    type=toupper(type);
    cout<<"Enter initial amount : ";
    cin>>deposit;
}

void account::dep_amt(float n){
    deposit+=n;
}

void account::draw_amt(float n){
    deposit-=n;
}

void account::report(){
    cout<<"Acc. No."<<setw(10)<<" "<<"Name"<<setw(20)<<" "<<"Type"<<setw(10)<<" "<<"Balance"<<el;
    cout<<acno<<setw(15)<<" "<<name<<setw(18)<<" "<<type<<setw(12)<<" "<<deposit<<el;
}

void account::ret_acno(){
    return acno;
}

void account::ret_dep(){
    return deposit;
}

void account::ret_type(){
    return type;
}



//***FUNTIONS DECLARATIONS FOR FILES***//
void write_acc();
void display_bal(int);
void update_acc(int);
void delete_acc(int);
void display_all();
void transaction(int, int);



//***FUNCTION DEFINITIONS***//

//Writing in file
void write_acc(){
    account ac;
    ofstream outFile;
    //open file in write mode
    outFile.open("account.txt",ios::out);
    ac.new_acc();
    outFile.write((char *) &ac, sizeof(account));
    outFile.close();
}

//Reading balance details of an account from file
void display_bal(){
    account ac;
    bool found=false;
    ifstream inFile;
    inFile.open("account.txt",ios::in);
    if(!inFile){
        cout<<"File not found...press any key to continue");
        return;
    }
    cout<<"\t***BALANCE DETAILS***"<<el;
    while(inFile.read((char *) %ac, sizeof(account))){
        if(ac.ret_acno()==n){
            ac.display_acc();
            found=true;
        }
    }
    inFile.close();
    if(found==false){
        cout<<"Account does not exist"<<el;
    }
}

//Updating account record in the file
void update_acc(int n){
    bool found=false;
    account ac;
    fstream File;
    File.open("account.txt",ios::in,ios::out);
    if(!File){
        cout<<"File not found...press any key to continue"<<el;
        return;
    }
    while(File.read((char *) &ac, sizeof(account)) && found==false){
        if(ac.ret_acno()==n){
            cout<<"Old account details : "<<el;
            ac.display_acc();
            cout<<"Enter new details : "<<el;
            ac.update();
            int pos=(-1)*sizeof(account);
            File.seekp(pos,ios::cur);
            File.write((char *) &ac, sizeof(account));
            cout<<el<<"Record Updated successfully"<<el;
            found=true;
        }
    }
    File.close();
    if(found==false){
        cout<<el<<"Record not found"<<el;
    }
}

//Deleting record of an account from file
void delete_acc(int n){
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.txt",ios::in,ios::out);
    if(!inFile){
        cout<<"File not found...press any key to continue"<<el;
        return;
    }
    outFile.open("Temp.txt",ios::in,ios::out);
    inFile.seekg(0,ios::beg);
    while(inFile.read((char *) &Ac, sizeof(account)){
        if(ac.ret_acno()!=n){
            outFile.write((char *) &ac, sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("Account.txt");
    rename("Temp.txt", "Account.txt");
    cout<<"Account record deleted sccuessfully"<<el;
}

//Display details of all accounts
void display_all(){
    account ac;
    ifstream inFile;
    inFile.open("Account.txt",ios::in,ios::out);
    if(!inFile){
        cout<<"File not found...press any key to continue"<<el;
        return;
    }
    cout<<"***ALL ACCOUNT DETAILS***"<<el;
    cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-"<<el;
    cout<<"Acc.No.          Name        Type        Balance"<<el;
    while(inFile.read((char *) &ac, sizeof(account))){
        ac.report();
    }
    inFile.close();
}

//Performing transactions on accounts
void transaction(int n, int choice){
    float amt;
    bool found=false;
    account ac;
    fstream File;
    File.open("Account.txt", ios::in | ios::out);
    if(!File){
        cout<<"File not found...press any key to continue"<<el;
        return;
    }
    while(File.read((char *) &ac, sizeof(account)) && found=false){
        if(ret_acno()==n){
            ac.display_acc();
            if(choice==1){
                cout<<"\tDEPOSIT MONEY"<<el;
                cout<<"Enter amount to be deposited : ";
                cin>>amt;
                ac.dep_amt();
            }
            if(choice==2){
                cout<<"\tWITHDRAW MONEY"<<el;
                cout<<"Enter amount to be withdrawn : ";
                cin>>amt;
                float bal=ret_dep();
                if((bal<500 && ac.ret_type()=='S') || (bal<1000 && ac.ret_type()=='C')){
                    cout<<"Not enough balance";
                }
                else{
                    ac.draw_amt();
                }
            }
            int pos=(-1)* sizeof(ac);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout<<"\t Record Updated successfully"<<el;
			found=true;
        }
    }
    File.close();
    if(found==false){
        cout<<"Record not found"<<el;
    }
}
          
    



//Driver code
int main(){
    char ch;
    int num;

    do{
        cout<<el<<"\t\tMENU"<<el;
        cout<<"\t1) Create New Account";
        cout<<"\t2) Deposit Amount";
        cout<<"\t3) Withdraw Amount";
        cout<<"\t4) Display Balance";
        cout<<"\t5) Update Account Info";
        cout<<"\t6) Display All Account's Details";
        cout<<"\t7) Close Account";
        cout<<"\t8) Exit";

        cout<<"Please enter a choice [1-8] : ";
        cin>>ch;

        switch(ch){

            case '1':
                    write_acc();
                    break;

            case '2':
                    cout<<"Enter account no. : ";
                    cin>>num;
                    transaction(num, 1);
                    break;

            case '3':
                    cout<<"Enter account no. : ";
                    cin>>num;
                    transaction(num, 2);
                    break;

            case '4':
                    cout<<"Enter account no. : ";
                    cin>>num;
                    display_acc();
                    break;

            case '5':
                    cout<<"Enter account no. : ";
                    cin>>num;
                    update(num);
                    break;

            case '6':
                    display_all();
                    break;

            case '7':
                    cout<<"Enter account no. : ";
                    cin>>num;
                    break;

            case '8':
                    cout<<"\t\t---THANK YOU FOR BANK MANAGEMENT SYSTEM !!---"<<el;
                    break;
                
            default:
                    cout<<"\a";
            }
    }while(ch!=8);
    
    return 0;



    }
}
