#include <iostream>
#include <vector>
#include <conio.h>
#include <regex>
#include <fstream>
#include <map>

using namespace std;

struct Users_info
{
    string First_name;
    string Middle_name;
    string Last_name;
    string username;
    string password;
    string email;
    string phone_number;
};

vector <Users_info> users;

string to_string(Users_info user1){
    string Info;
    Info+=user1.First_name+"\n"+user1.Middle_name+"\n"+user1.Last_name+"\n";
    Info+=user1.username+"\n";
    Info+=user1.password+"\n";
    Info+=user1.email+"\n";
    Info+=user1.phone_number+"\n";
    return Info;
}
void write_content_to_db(){
    fstream datafile;
    string add= "";
    // for(int i=0;i<users.size();i++){
    add+="New user \n";
    add+= to_string(users[users.size()-1]);
    // }
    //To overwrite what was in the file
    datafile.open("database.txt",ios::app);
    datafile<<add;
    datafile.close();

}
void read_content_to_db(){
    ifstream f;
    f.open("database.txt", ios::in);
    string str;

    while(!f.eof()){
        getline(f, str);
        if(str=="New user "){
            Users_info user;
            getline(f,user.First_name);
            getline(f,user.Middle_name);
            getline(f,user.Last_name);
            getline(f,user.username);
            getline(f,user.password);
            getline(f,user.email);
            getline(f,user.phone_number);
            users.push_back(user);

        }
    }
    f.close();
}

bool valid_username(string& u){
    if(users.size() == 0 ){
        return true;
    }
    for(int i=0;i<users.size();i++){
        if(u == users[i].username){
            return false;
        }
        else{
            return true;
        }
    }
}

bool valid_name(string& n)
{
    regex valid_name("[A-Z][a-z]+");
    return regex_match(n, valid_name);
}

bool valid_email(string& e){
    regex valid_email("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    for(int i=0; i< e.length()-1; i++){
        if(e[i] == '.' && e[i+1] =='.')i++;
            //return false;
    }
    return regex_match(e,valid_email);
}

bool valid_phonenumber(string& n){

    regex valid_phonenumber("[0][1][0125][0-9]+{8}");
    return regex_match(n, valid_phonenumber);

}
bool Check_Password_Strength(string password){
    bool upperch,lowerch,num,specialch;
    if(password.length()<12){
        cout<<"Wrong.Password has to be at least 12 characters: "<<endl;
        return false;
    }
    for(int i=0;i<password.length();i++){
        if(password[i]>='A' && password[i]<='Z')
            upperch=true;
        else if(password[i]>='a' && password[i]<='z')
            lowerch=true;
        else if(password[i]>='0' && password[i]<='9')
            num=true;
        else if(password[i]!='\n' && password[i]!=' ')
            specialch=true;
    }
    if(upperch && lowerch && num && specialch)
        return true;
    else{
        cout<<"Please make sure that your password has at least 1 uppercase letter,1 lowercase letter,1 number and 1 special character"<<endl;
        return false;
    }

}
string Masking_password(){
    string pass="";
    char ch;
    while(true){
        ch= getch();
        if ((ch>=32&&ch<=126)){
            pass+=ch;
            // ++i;
            cout<<"*";
        }
        else if (ch=='\b')
        {
            cout<<"\b \b";
            pass += "\b \b";
            // --i;
        }
        else if (ch=='\r'){
            break;
        }
    }
    return pass;
}


string Encrypt_password(string word)
{
    int key=15;
    string Nword;
    for(int i = 0;i<word.length();i++){
        Nword += char(int(word[i]+key-32)%95 +32);
    }
    return Nword;
}


void Enter_info(){
    Users_info user1;
    string verify_password;
    cout << "Enter your name: ";
    cout << endl <<"(Enter your first, middle and last name each with a the first letter capital)"<< endl;

    cout << "First name: ";
    cin >> user1.First_name;


    while (!valid_name(user1.First_name))
    {
        cout << endl << "Incorrect Format!\nPlease enter your First name again: ";
        cin >> user1.First_name;
    }

    cout << endl <<"Middle name: ";
    cin >> user1.Middle_name;

    while (!valid_name(user1.Middle_name))
    {
        cout << endl << "Incorrect Format!\nPlease enter your Middle name again: ";
        cin >> user1.Middle_name;
    }

    cout << endl << "Last name: ";
    cin >> user1.Last_name;

    while (!valid_name(user1.Last_name))
    {
        cout << endl << "Incorrect Format!\nPlease enter your Last name again: ";
        cin >> user1.Last_name;
    }

    cout << endl << "Enter your desired username: ";
    cin >> user1.username;

    while (valid_username(user1.username))
    {
        cout << endl << "Username is already taken!\nPlease enter a different Username ";
        cin >> user1.username;
    }

    cout << "Enter your desired password(Please make sure that your password is at least 12 characters, has at least 1 uppercase letter, 1 lowercase letter, 1 number and 1 special character): "<<endl;
    user1.password = Masking_password();
    // cout<<user1.password;
    while(true){
        if(Check_Password_Strength(user1.password)){
            break;
        }
        cout<<"Enter a strong password: "<<endl;
        user1.password = Masking_password();
        // cout<<user1.password;
    }
    cout<<"\nPlease enter the same password to verify if they're the same: "<<endl;
    verify_password = Masking_password();
    // cout<<verify_password;
    bool same=false;
    while(user1.password!=verify_password){
        cout<<"\nPlease enter the correct password: "<<endl;
        verify_password = Masking_password();
        // cout<<verify_password;
    }
    user1.password = Encrypt_password(user1.password);


    cout << endl << "Enter your Email address: ";
    cin >> user1.email;


    while (!valid_email(user1.email))
    {
        cout << endl << "Incorrect Format!\nPlease enter a different Email address: ";
        cin >> user1.email;
    }

    cout << endl << "Enter your phone number: ";
    cin >> user1.phone_number;

    while (!valid_phonenumber(user1.phone_number))
    {
        cout << endl << "Incorrect Format!\nPlease enter a different phone number: ";
        cin >> user1.phone_number;
    }
    users.push_back(user1);
}

int login(){
    string user_name, password, expectedEncryptedPassword;
    bool foundUsername = false;
    int userID = -1;
    while(true){
        while (!foundUsername){
            cout<<"Enter username: ";
            cin>>user_name;
            for(int i=0; i<users.size() && !foundUsername; i++){
                if(user_name == users[i].username){
                    foundUsername = true;
                    expectedEncryptedPassword = users[i].password;
                    userID = i;
                }
            }
            if(!foundUsername){
                cout << "The username you entered doesn't exist in the database. Please enter a valid username."<< endl;
            }
        }
        for (int i=0; i<3 ; i++){
            cout<<"Enter password: ";
            password = Masking_password();
            password = Encrypt_password(password);
            if(expectedEncryptedPassword == password){
                cout<<"\n\nLogin Successful!\n";
                cout<<"\nWelcome! "<<user_name<<endl;
                return userID;
            }
            if(i < 2){
                cout<<"\nWrong Password. Try Again\n\n";
            }
        }
        cout<<"Failed to Login! You Are Denied Access to System\n";
        return -1;
    }
}

void Login(){
    login();
}

void changePassword(){
    string newPassword, verifyNewPassword;
    cout<< "Please login first."<<endl;
    int userID = login();
    if(userID == -1){
        cout << "Login failed. You cannot change password. Goodbye" << endl;
        return;
    }
    cout << "Enter the newly desired password (Please make sure that your password is at least 12 characters, has at least 1 uppercase letter, 1 lowercase letter, 1 number and 1 special character): "<<endl;
    newPassword = Masking_password();
    while(true){
        if(Check_Password_Strength(newPassword)){
            break;
        }
        cout<<"Enter a strong password: "<<endl;
        newPassword = Masking_password();
    }
    cout<<"\nPlease enter the same password to verify that they're the same: "<<endl;
    verifyNewPassword = Masking_password();
    bool same=false;
    while(newPassword!=verifyNewPassword){
        cout<<"\nPlease enter the correct password: "<<endl;
        verifyNewPassword = Masking_password();
    }
    users[userID].password = Encrypt_password(newPassword);
    cout << "Password changed successfully." << endl;
}
