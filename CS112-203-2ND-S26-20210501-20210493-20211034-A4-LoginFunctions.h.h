#include <iostream>
#include <map>
#include <vector>
#include <regex>
#include<sstream>
#include <fstream>

using namespace std;

struct Users_info;
string to_string(Users_info user1);
void write_content_to_db();
void read_content_to_db();
bool valid_name(string& n);
bool valid_email(string& e);
bool valid_phonenumber(string& n);
bool Check_Password_Strength(string password);
void Enter_info();
string Encrypt_pass(string word);
int login();
void Login();
void changePassword();
