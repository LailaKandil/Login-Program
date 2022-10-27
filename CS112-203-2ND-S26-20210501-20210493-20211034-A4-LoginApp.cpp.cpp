// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Login System.cpp
// Last Modification Date: 16/5/2022
// Author1 and ID and Group: Laila Hesham Mohamed Kandil-20210501-S25/S26
// Author2 and ID and Group: Doaa Eli Elsayed Mohamed-20211034-S25/S26
// Author3 and ID and Group: Salma Gamal Ezzat AbdelRazak-20210493-S25/S26
// Teaching Assistant: Mahmoud Fateaha
// Purpose:This program can make you register your information such as:Name,username,password,email and phone number and can login into the program.
#include <iostream>
#include "function.cpp"

using namespace std;

int main(){
    int choice;
    cout<<"Welcome to Login Application Program!"<<endl;
    read_content_to_db();
    while (true){
        cout<<"Please choose whether you want to:\n"
        "(1) Register\n(2) Login \n(3) Change Password \n (4) Exit.\n";
        cin>>choice;
        if (choice==1){
            //register
            Enter_info();
            write_content_to_db();
        }
        else if(choice==2){
            //login
            Login();
        }
        else if(choice==3){
            changePassword();
            write_content_to_db();
        }
        else if(choice==4){
            //exit
            break;
        }
    }
}
