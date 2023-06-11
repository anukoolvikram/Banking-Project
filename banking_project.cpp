#include <iostream>
#include <string>
#include<fstream>
#include <map>

using namespace std;


class Account{

private:
    string first;
    string last;
    float bal;
    long accNo;
    static long count;
    
public:
    
    Account(){};
    Account(string fn, string ln, float balance){
        count++;
        accNo=count;
        first=fn;
        last=ln;
        bal=balance;
    }
    string getfn(){
        return first;
    }
    string getln(){
        return last;
    }
    long getAccNo(){
        return accNo;
    }
    float getbal(){
        return bal;
    }
    void deposit(float b){
        bal+=b;
    }
    void withdraw(float b){
        bal-=b;
    }
    friend ofstream & operator<<(ofstream &off, Account &a);
    friend ifstream & operator>>(ifstream &inn, Account &a);
    friend ostream & operator<<(ostream &oss, Account &a);
};


ofstream & operator<<(ofstream &off, Account &a){
    off<<a.accNo<<endl;
    off<<a.first<<endl;
    off<<a.last<<endl;
    off<<a.bal<<endl;
    return off;
}

ifstream & operator>>(ifstream &inn, Account &a){
    inn>>a.accNo;
    inn>>a.first;
    inn>>a.last;
    inn>>a.bal;
    return inn;
}
ostream &  operator<<(ostream & oss, Account &a){
    oss<<"Account No: "<<a.getAccNo()<<endl;
    oss<<"First Name: "<<a.getfn()<<endl;
    oss<<"Last Name: "<<a.getln()<<endl;
    oss<<"Balance: "<<a.getbal()<<endl;
    return oss;
}

long Account::count=0;

class Bank{

private:
    map<long,Account> mapp;
public: 
    
    Bank(){

    }
    Account openAccount(string fn, string ln, float bal){
        Account a(fn, ln, bal);
        mapp.insert(pair<long,Account>(a.getAccNo(),a));
        ofstream outfile;
        outfile.open("Bank Details");

        map<long, Account>:: iterator itr;
        for(itr=mapp.begin(); itr!=mapp.end(); itr++){
            outfile<<itr->second;
        outfile.close();
        return a;
        }
    }

    float BalanceEnquiry(long acc)    {

        map<long, Account>::iterator itr;
        itr=mapp.find(acc);
        float b= itr->second.getbal();
        return b;

    }

    Account Deposit(long acc, float b){

        map<long, Account>:: iterator itr;
        itr=mapp.find(acc);
        itr->second.deposit(b);
        return itr->second;
    }

    Account Withdraw(long acc, float w){
        map<long, Account>:: iterator itr;
        itr=mapp.find(acc);
        itr->second.withdraw(w);
        return itr->second;
        
    }
    void CloseAccount(long acc){
        map<long,Account>::iterator itr;
        itr=mapp.find(acc);
        cout<<"Account Deleted: ";
        cout<< itr->second;
        mapp.erase(acc);
    }
    void ShowAll(){
        map<long, Account>::iterator itr;
        for(itr=mapp.begin(); itr!=mapp.end(); itr++){
            cout<<"Account: "<<itr->first<<endl;
            cout<<itr->second<<endl;
        }

    }
    ~Bank(){
        ofstream ofile;
        ofile.open("Bank Details");

        map<long, Account>::iterator itr;
        for(itr=mapp.begin(); itr!=mapp.end(); itr++){
            ofile<<itr->second;

        }
        ofile.close();
    }
};

int main()
{
    Bank b;
    Account ac;
    int choice=0;
    long acc;
    string first;
    string last;
    float bal;
    float amt;

cout<<"Banking System"<<endl;
while(choice!=7){
    cout<<"\n\tSelect one option below ";
    cout<<"\n\t1 Open an Account";
    cout<<"\n\t2 Balance Enquiry";
    cout<<"\n\t3 Deposit";
    cout<<"\n\t4 Withdrawal";
    cout<<"\n\t5 Close an Account";
    cout<<"\n\t6 Show All Accounts";
    cout<<"\n\t7 Quit"<<endl;

    cout<<"Enter your choice: "<<endl;
    cin>>choice;

if(choice==1) {

        cout<<"Enter first name: ";
        cin>>first;
        
        cout<<"Enter last name: ";
        cin>>last;
        
        cout<<"Enter the initial Balance: ";
        cin>>bal;
        
        ac=b.openAccount(first, last, bal);
        cout<<ac;
}

else if(choice==2){
        
        long a;
        cout<<"Enter the account Number: ";
        cin>>a;
        float bl=b.BalanceEnquiry(a);
        cout<<"Your current Balance is: "<<bl<<endl;
    }

else if(choice==3){

    long a;
    cout<<"Enter the account Number: ";
    cin>>a;

    float amt;
    cout<<"Enter the amount to deposit: ";
    cin>>amt;
    
    ac=b.Deposit(a,amt);
    cout<<"Your account details are: "<<ac<<endl;
}

else if (choice==4){

    long a;
    cout<<"Enter the account Number: ";
    cin>>a;

    float amt;
    cout<<"Enter the amount to withdraw: ";
    cin>>amt;

    ac=b.Withdraw(a,amt);
    cout<<"Your account details are: "<<ac<<endl;

} 

else if(choice==5){
    long a;
    cout<<"Enter the account Number: ";
    cin>>a;
    b.CloseAccount(a);
    cout<<"Your account is successfully deleted."<<endl;   

}
else if (choice==6){
    cout<<"The list of all the registered accounts are: "<<endl;
    b.ShowAll();
}
else if(choice==7) break;

}

return 0;
}