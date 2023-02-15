#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <dos.h>
#include <tabulate/table.hpp>
#include <fstream>
#include <string.h>
#include <cstring>
#include<regex>

using namespace tabulate;
using Row_t = std::vector<variant<std::string, const char *, Table>>;
using namespace std;

string username;
const char FILENAME[] = "contact.txt";

struct Contact{
    char name[35];
    char pnum[35];
    char email[100];
    char address[100];
};


// Function Declaration
void HiddenCaret();

void ShowCaret();

void MoveCenter();

void HideMaxBtn();

void initLayout();

void Menu();

void AddContacts();

void ShowContacts();

void SearchContacts();

void DeleteContacts();

void UpdateContacts();

void EnterUser();

void color(int color){ //Change cmd text color
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y){
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

string PrintTab(int input){ //Returns a string of spaces
    string temp="";
    for(int i=0;i<input;i++){
        temp+=" ";
    }
    return temp;
}

string PrintBox(int input){ //Returns a string of new lines
    string temp="";
    for(int i=0;i<input;i++){
        temp+="\n";
    }
    return temp;
}

string PrintLine(int input){ //Returns a string of lines
    string temp="";
    for(int i=0;i<input;i++){
        temp+="--";
    }
    return temp;
}

bool isNumber(string input) //Check if the number that you entered is valid or not
{
    if(isdigit(input.at(0))==0){
            if(input.at(0) != '+'){
                if(input.at(0) != '('){
                    return false;
                }
            }
    }
    for (char const &c : input) {
        if(c!='-'){
                if(c != '('){
                     if(c != ')'){
                         if(c != '+'){
                            if (isdigit(c) == 0) {
                                return false;
                            }
                        }
                    }
                }
        }
    }
    return true;
}

bool isEmail(string input)
{
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(input,pattern);
}

bool hasSpace(string input){//Check if the string has spaces or not
    int cnt;
    for(int i=0;i<(signed)strlen(input.c_str());i++){
        if(input.at(i)==' '){
            cnt++;
        }
    }
    if(cnt>=1){
        return true;
    }
    return false;
}

string UpperCase(string input){
        input.at(0) = toupper(input.at(0));
        return input;
}

string LowerCase(string input){
        input.at(0) = tolower(input.at(0));
        return input;
}

int main(){// Main

    initLayout();
    EnterUser();
    return 0;

}

void initLayout(){//Compilation of functions that will modify the cmd layout
    system("chcp 65001  > nul");
    system("cls");
    HideMaxBtn();
    MoveCenter();
    HWND hwnd = GetConsoleWindow();
    SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE)&~WS_SIZEBOX);
}

void EnterUser(){
    system("color 1E");
    Table layout;
    Table clayout;
    Table sclayout;

    layout.format().border_color(Color::white);

    layout.add_row(Row_t{PrintTab(84)+"--- BLOA Phonebook Application ---"});
    layout[0]
        .format()
        .font_align(FontAlign::center)
        .font_color(Color(9))
        .font_background_color(Color::cyan);

    layout.add_row(Row_t{"Developed by Blue Team (Barias, Laud, Obejas and Ausan)\nBSIT-2D"});
    layout[1]
      .format()
      .font_align(FontAlign::center)
      .hide_border_top();

    sclayout.add_row(Row_t{PrintTab(109)+PrintBox(21)});

    clayout.add_row(Row_t{sclayout});

    layout.add_row(Row_t{clayout});
    layout[1]
      .format()
      .font_align(FontAlign::center)
      .font_color(Color::blue)
      .font_background_color(Color::white);
    cout<<layout;
    while(true){
        gotoxy(29,14);
        cout<<"Input the name of the User: ";
        getline(cin,username);
        if(username==""){
                gotoxy(56,15);
                cout<<PrintTab(40);
                gotoxy(56,15);
                color(79);
                cout<<"Please Input a Name!";
                color(31);
        }
        else{
            Menu();
        }
    }
}
void Menu(){//Phonebook  Application Menu
    system("color 1E");
    HiddenCaret();
    system("cls");
    Table layout;
    Table clayout;
    Table sclayout;

    layout.format().border_color(Color::white);

    layout.add_row(Row_t{PrintTab(84)+"--- BLOA Phonebook Application ---"});
    layout[0]
        .format()
        .font_align(FontAlign::center)
        .font_color(Color(9))
        .font_background_color(Color::cyan);

    layout.add_row(Row_t{"Developed by Blue Team (Barias, Laud, Obejas and Ausan)\nBSIT-2D"});
    layout[1]
      .format()
      .font_align(FontAlign::center)
      .hide_border_top();

    sclayout.add_row(Row_t{PrintTab(40)+PrintBox(21),PrintTab(66)+PrintBox(21)});

    clayout.add_row(Row_t{sclayout});

    layout.add_row(Row_t{clayout});
    layout[1]
      .format()
      .font_align(FontAlign::center)
      .font_color(Color::blue)
      .font_background_color(Color::white);
    cout<<layout;
    HiddenCaret();

    int Set[] = {249,31,31,31,31,31};
    int counter = 1;
    char key;

    gotoxy(4,5);
    color(249);
    cout<<" Hello "<<username<<"! ";

    //Selection Strings
    string s1=" → View All Contacts ";
    string s2="  Add Contacts";
    string s3="  Search Contacts";
    string s4="  Update Contacts";
    string s5="  Delete Contacts";
    string s6="  Exit";

    //Selection Message
    string m1="This function allows you to see";
    string m2="all your current contacts.";
    string m3="Thus it is helpful for knowing";
    string m4="how much contacts you have.";


    //Logo
    string l1="  ╦  ╦╦╔═╗╦ ╦  ╔═╗╦  ╦    ╔═╗╔═╗╔╗╔╔╦╗╔═╗╔═╗╔╦╗╔═╗";
    string l2="  ╚╗╔╝║║╣ ║║║  ╠═╣║  ║    ║  ║ ║║║║ ║ ╠═╣║   ║ ╚═╗";
    string l3="   ╚╝ ╩╚═╝╚╩╝  ╩ ╩╩═╝╩═╝  ╚═╝╚═╝╝╚╝ ╩ ╩ ╩╚═╝ ╩ ╚═╝";

    while(true){
        gotoxy(59,24);
        color(31);
        cout<<"Tip: Move the highlight selection using ↑";

        gotoxy(59,25);
        color(31);
        cout<<"     key to go up and ↓ key to go down.";

        gotoxy(56,9);
        color(28);
        cout<<l1;
        gotoxy(56,10);
        color(27);
        cout<<l2;
        gotoxy(56,11);
        color(31);
        cout<<l3;

        gotoxy(59,13);
        color(31);
        cout<<m1;
        gotoxy(59,15);
        color(31);
        cout<<m2;
        gotoxy(59,17);
        color(31);
        cout<<m3;
        gotoxy(59,19);
        color(31);
        cout<<m4;

        gotoxy(16,9);
        color(Set[0]);
        cout<<s1;

        gotoxy(16,12);
        color(Set[1]);
        cout<<s2;

        gotoxy(16,15);
        color(Set[2]);
        cout<<s3;

        gotoxy(16,18);
        color(Set[3]);
        cout<<s4;

        gotoxy(16,21);
        color(Set[4]);
        cout<<s5;

        gotoxy(16,24);
        color(Set[5]);
        cout<<s6;

        key = _getch();

        if(key == 72 && (counter > 1 && counter <= 6)){
            counter--;
        }
        else if(key == 80 && (counter >= 1 && counter < 6)){
            counter++;
        }
        if(key == '\r'){
            if(counter == 1){
                ShowContacts();
            }
            if(counter == 2){
                AddContacts();
            }
            if(counter == 3){
                SearchContacts();
            }
            if(counter == 4){
                UpdateContacts();
            }
            if(counter == 5){
                DeleteContacts();
            }
            if(counter == 6){
                exit(0);
            }
        }

        Set[0]=31;
        Set[1]=31;
        Set[2]=31;
        Set[3]=31;
        Set[4]=31;
        Set[5]=31;

        s1="  View All Contacts"+PrintTab(10);
        s2="  Add Contacts"+PrintTab(10);
        s3="  Search Contacts"+PrintTab(10);
        s4="  Update Contacts"+PrintTab(10);
        s5="  Delete Contacts"+PrintTab(10);
        s6="  Exit"+PrintTab(20);

        if(counter == 1){
            s1=" → View All Contacts ";
            Set[0]=249;

            l1="  ╦  ╦╦╔═╗╦ ╦  ╔═╗╦  ╦    ╔═╗╔═╗╔╗╔╔╦╗╔═╗╔═╗╔╦╗╔═╗";
            l2="  ╚╗╔╝║║╣ ║║║  ╠═╣║  ║    ║  ║ ║║║║ ║ ╠═╣║   ║ ╚═╗";
            l3="   ╚╝ ╩╚═╝╚╩╝  ╩ ╩╩═╝╩═╝  ╚═╝╚═╝╝╚╝ ╩ ╩ ╩╚═╝ ╩ ╚═╝";

            m1="This function allows you to see"+PrintTab(20);
            m2="all your current contacts."+PrintTab(20);
            m3="Thus it is helpful for knowing"+PrintTab(20);
            m4="how much contacts you have."+PrintTab(23);

        }
        if(counter == 2){
            s2=" → Add Contacts ";
            Set[1]=249;

            l1="   ╔═╗╔╦╗╔╦╗  ╔═╗╔═╗╔╗╔╔╦╗╔═╗╔═╗╔╦╗╔═╗"+PrintTab(12);
            l2="   ╠═╣ ║║ ║║  ║  ║ ║║║║ ║ ╠═╣║   ║ ╚═╗"+PrintTab(12);
            l3="   ╩ ╩═╩╝═╩╝  ╚═╝╚═╝╝╚╝ ╩ ╩ ╩╚═╝ ╩ ╚═╝"+PrintTab(12);

            m1="This function allows you to add"+PrintTab(16);
            m2="or save new 'contacts'. A contact is basically"+PrintTab(6);
            m3="a set of information pertaining to someone"+PrintTab(10);
            m4="which allows you to communicate with him or her."+PrintTab(5);

        }
        if(counter == 3){
            s3=" → Search Contacts ";
            Set[2]=249;

            l1="  ╔═╗╔═╗╔═╗╦═╗╔═╗╦ ╦  ╔═╗╔═╗╔╗╔╔╦╗╔═╗╔═╗╔╦╗╔═╗"+PrintTab(12);
            l2="  ╚═╗║╣ ╠═╣╠╦╝║  ╠═╣  ║  ║ ║║║║ ║ ╠═╣║   ║ ╚═╗"+PrintTab(12);
            l3="  ╚═╝╚═╝╩ ╩╩╚═╚═╝╩ ╩  ╚═╝╚═╝╝╚╝ ╩ ╩ ╩╚═╝ ╩ ╚═╝"+PrintTab(12);

            m1="A function that when a user inputs a query,"+PrintTab(13);
            m2="it provides him or her a"+PrintTab(23);
            m3="list of contacts that best match"+PrintTab(14);
            m4="which contact the user is trying to find."+PrintTab(10);

        }
        if(counter == 4){
            s4=" → Update Contacts ";
            Set[3]=249;

            l1="   ╦ ╦╔═╗╔╦╗╔═╗╔╦╗╔═╗  ╔═╗╔═╗╔╗╔╔╦╗╔═╗╔═╗╔╦╗╔═╗"+PrintTab(12);
            l2="   ║ ║╠═╝ ║║╠═╣ ║ ║╣   ║  ║ ║║║║ ║ ╠═╣║   ║ ╚═╗"+PrintTab(12);
            l3="   ╚═╝╩  ═╩╝╩ ╩ ╩ ╚═╝  ╚═╝╚═╝╝╚╝ ╩ ╩ ╩╚═╝ ╩ ╚═╝"+PrintTab(12);

            m1="Is a function that lets you edit a contact"+PrintTab(10);
            m2="to change some parts of the contact information"+PrintTab(6);
            m3="to something more up to date."+PrintTab(14);
            m4="Like changing the number etc. "+PrintTab(20);

        }
        if(counter == 5){
            s5=" → Delete Contacts ";
            Set[4]=249;

            l1="   ╔╦╗╔═╗╦  ╔═╗╔╦╗╔═╗  ╔═╗╔═╗╔╗╔╔╦╗╔═╗╔═╗╔╦╗╔═╗"+PrintTab(12);
            l2="    ║║║╣ ║  ║╣  ║ ║╣   ║  ║ ║║║║ ║ ╠═╣║   ║ ╚═╗"+PrintTab(12);
            l3="   ═╩╝╚═╝╩═╝╚═╝ ╩ ╚═╝  ╚═╝╚═╝╝╚╝ ╩ ╩ ╩╚═╝ ╩ ╚═╝"+PrintTab(12);

            m1="The function that allows the"+PrintTab(15);
            m2="user to remove a contact"+PrintTab(24);
            m3="which is deemed to be unnecessary."+PrintTab(22);
            m4=""+PrintTab(29);
        }
         if(counter == 6){
            s6=" → Exit ";
            Set[5]=249;

            l1="   ╔═╗═╗ ╦╦╔╦╗  ╔═╗╦═╗╔═╗╔═╗╦═╗╔═╗╔╦╗"+PrintTab(12);
            l2="   ║╣ ╔╩╦╝║ ║   ╠═╝╠╦╝║ ║║ ╦╠╦╝╠═╣║║║"+PrintTab(12);
            l3="   ╚═╝╩ ╚═╩ ╩   ╩  ╩╚═╚═╝╚═╝╩╚═╩ ╩╩ ╩"+PrintTab(12);

            m1="Choosing this function, the user will be"+PrintTab(15);
            m2="logged out of their current"+PrintTab(24);
            m3="session and closes the program."+PrintTab(22);
            m4=""+PrintTab(29);

        }
    }
}

void ShowContacts(){//Show Contacts Module
    system("color 1E");
    FILE *fp;
    fp=fopen(FILENAME,"a+");

    HiddenCaret();
    system("cls");

    struct Contact cont;

    int rows=0;

    char key;

    Table layout;
    Table column;
    Table embed;

    layout.format().border_color(Color::white);

    layout.add_row(Row_t{"View All Contacts"});
    layout[0]
        .format()
        .font_align(FontAlign::center);

  column.add_row(Row_t{PrintTab(16)+"NAME",PrintTab(13)+"PHONE NUMBER",PrintTab(16)+"EMAIL ADDRESS",PrintTab(16)+"ADDRESS"});
    column[0]
        .format()
        .font_align(FontAlign::center);
    while(fscanf(fp,"%s %s %s %s",cont.name,cont.pnum,cont.email,cont.address)!=EOF){
            stringstream s1;
            s1<<cont.name;
            string str1=s1.str();
            replace(str1.begin(),str1.end(),'_',' ' );

            stringstream s2;
            s2<<cont.pnum;
            string str2=s2.str();

            stringstream s3;
            s3<<cont.email;
            string str3=s3.str();

            stringstream s4;
            s4<<cont.address;
            string str4=s4.str();
            replace(str4.begin(),str4.end(),'_',' ' );


            column.add_row(Row_t{str1,str2,str3,str4});

            column
                .format()
                .font_align(FontAlign::center)
                .padding(0.7);


            rows++;
        }
        column[0][0].format().width(28);
        column[0][1].format().width(28);
        column[0][2].format().width(28);
        column[0][3].format().width(28);
        Table layoutc;
            layoutc.add_row(Row_t{"Number of Columns: 4 (NAME, PHONE NUMBER, EMAIL ADDRESS, ADDRESS)  |  ","Number of Rows: "+to_string(rows)+"  |  ","\tPress [ESC] to go back"});
            layoutc[0]
                .format()
                .font_align(FontAlign::center)
                .hide_border()
                .padding(0);
            layout.add_row(Row_t{layoutc});
            layout[1]
                .format()
                .font_align(FontAlign::right);
            embed.add_row(Row_t{layout});
            embed[0]
                .format()
                .font_align(FontAlign::center)
                .hide_border_top()
                .hide_border_left()
                .hide_border_right()
                .font_color(Color::blue)
                .font_background_color(Color::white);;
        if(rows>0){
            embed.add_row(Row_t{column});
            embed[1]
                .format()
                .font_align(FontAlign::center)
                .hide_border();
        }
        else{
            embed.add_row(Row_t{"No Results to Show!"});
            embed[1]
                .format()
                .font_align(FontAlign::center)
                .hide_border();
        }
            cout<<embed;

            gotoxy(5,1);
            color(249);
            cout<<" Hello "+username+"! ";

            fclose(fp);

    while(true){
        key=_getch();
        if(key==27){
            break;
        }
    }

    Menu();
}

void SearchContacts(){//Search Contacts Module
    system("color 1E");
    FILE *fp;
    fp=fopen(FILENAME,"a+");

    system("cls");
    ShowCaret();
    struct Contact cont;

    int rows=0;

    string s1="Y";
    string s2="N";

    string name;

    int Set[]={249,31};

    char key;

    int counter=1;

    Table layout;
    Table column;
    Table embed;

    layout.format().border_color(Color::white);

    layout.add_row(Row_t{PrintTab(103)+"Search Contacts"});
    layout[0]
        .format()
        .font_align(FontAlign::center)
        .font_color(Color::blue)
        .font_background_color(Color::white);;
    layout.add_row(Row_t{PrintBox(3)});
    layout[1]
        .format()
        .font_align(FontAlign::center);
    cout<<layout;

    gotoxy(5,1);
    color(249);
    cout<<" Hello "+username+"! ";
    color(31);

    gotoxy(5,1);
    color(249);
    cout<<" Hello "+username+"! ";
    color(31);

    gotoxy(49,4);
    cout<<"Search for name: ";
    getline(cin, name);
    column.add_row(Row_t{PrintTab(16)+"NAME",PrintTab(13)+"PHONE NUMBER",PrintTab(16)+"EMAIL ADDRESS",PrintTab(16)+"ADDRESS"});
    column[0]
        .format()
        .font_align(FontAlign::center);
    while(fscanf(fp,"%s %s %s %s",cont.name,cont.pnum,cont.email,cont.address)!=EOF){
         stringstream s1;
        s1<<cont.name;
        string str1=s1.str();
        replace(str1.begin(),str1.end(),'_',' ' );;
        if((string(str1).find(name)!= std::string::npos) || (string(str1).find(UpperCase(name))!= std::string::npos) || (string(str1).find(LowerCase(name))!= std::string::npos)){

            stringstream s2;
            s2<<cont.pnum;
            string str2=s2.str();

            stringstream s3;
            s3<<cont.email;
            string str3=s3.str();

            stringstream s4;
            s4<<cont.address;
            string str4=s4.str();
            replace(str4.begin(),str4.end(),'_',' ' );


            column.add_row(Row_t{str1,str2,str3,str4});

            column
                .format()
                .font_align(FontAlign::center)
                .padding(0.7);


            rows++;
            }
        }
        column[0][0].format().width(28);
        column[0][1].format().width(27);
        column[0][2].format().width(28);
        column[0][3].format().width(28);
        Table layoutc;
            layoutc.add_row(Row_t{PrintTab(5)+"User Query: "+string(name)+"\nNumber of Search Results: "+to_string(rows)});
            layoutc[0]
                .format()
                .font_align(FontAlign::center)
                .hide_border();

        if(rows>0){
            layoutc.add_row(Row_t{column});
            layoutc[1]
                .format()
                .font_align(FontAlign::center)
                .hide_border();
            embed.add_row(Row_t{layoutc});
            embed[0]
                .format()
                .font_align(FontAlign::center);
        }
        else{
            embed.add_row(Row_t{PrintTab(5)+"User Query: "+string(name)});
            embed[0]
                .format()
                .font_align(FontAlign::center);
            embed.add_row(Row_t{PrintTab(98)+"No Results to Show! "});
            embed[1]
                .format()
                .font_align(FontAlign::center);
        }
            cout<<"\n"<<embed;

            fclose(fp);

    HiddenCaret();
    gotoxy(5,4);
    cout<<PrintTab(90);
    gotoxy(45,4);
    cout<<"Do you want to search again: ";
    while(true){
            gotoxy(75,4);
            color(Set[0]);
            cout<<s1;

            gotoxy(77,4);
            color(Set[1]);
            cout<<s2;

            key = _getch();

            if(key == 75 && (counter > 1 && counter <= 2)){
                counter--;
            }
            else if(key == 77 && (counter >= 1 && counter < 2)){
                counter++;
            }

            if(key == '\r'){
                if(counter == 1){
                    color(31);
                    SearchContacts();
                }
                if(counter == 2){
                    color(31);
                    Menu();
                }
            }

            Set[0]=31;
            Set[1]=31;

            s1="Y";
            s2="N";

            if(counter == 1){
                s1="Y";
                Set[0]=249;
            }
            if(counter == 2){
                s2="N";
                Set[1]=249;
            }
    }


}

void DeleteContacts(){//Delete Contacts Module
    system("color 1E");
    FILE *fp, *fp1;
    fp=fopen(FILENAME,"a+");

    system("cls");
    ShowCaret();
    struct Contact cont;

    int rows=0;

    string s1="Y";
    string s2="N";

    string name;

    int Set[]={249,31};

    char key;

    int counter=1;

    Table layout;
    Table column;
    Table embed;

    layout.format().border_color(Color::white);

    layout.add_row(Row_t{PrintTab(103)+"Delete Contacts"});
    layout[0]
        .format()
        .font_align(FontAlign::center)
        .font_color(Color::blue)
        .font_background_color(Color::white);;
    layout.add_row(Row_t{PrintBox(3)});
    layout[1]
        .format()
        .font_align(FontAlign::center);
    cout<<layout;

    gotoxy(5,1);
    color(249);
    cout<<" Hello "+username+"! ";
    color(31);

    gotoxy(3,4);
    cout<<"Input the Full Name of the record that you want to delete: ";
    getline(cin, name);
    column.add_row(Row_t{PrintTab(16)+"NAME",PrintTab(13)+"PHONE NUMBER",PrintTab(16)+"EMAIL ADDRESS",PrintTab(16)+"ADDRESS"});
    column[0]
        .format()
        .font_align(FontAlign::center);
    while(fscanf(fp,"%s %s %s %s",cont.name,cont.pnum,cont.email,cont.address)!=EOF){
        stringstream s1;
        s1<<cont.name;
        string str1=s1.str();
        replace(str1.begin(),str1.end(),'_',' ' );;
        if(string(str1)==name){

            stringstream s2;
            s2<<cont.pnum;
            string str2=s2.str();

            stringstream s3;
            s3<<cont.email;
            string str3=s3.str();

            stringstream s4;
            s4<<cont.address;
            string str4=s4.str();
            replace(str4.begin(),str4.end(),'_',' ' );


            column.add_row(Row_t{str1,str2,str3,str4});

            column
                .format()
                .font_align(FontAlign::center)
                .padding(0.7);


            rows++;
            }
        }
        column[0][0].format().width(28);
        column[0][1].format().width(27);
        column[0][2].format().width(28);
        column[0][3].format().width(28);
        Table layoutc;
            layoutc.add_row(Row_t{PrintTab(5)+"User Query: "+string(name)});
            layoutc[0]
                .format()
                .font_align(FontAlign::center)
                .hide_border();

        fclose(fp);
                if(rows>0){
            layoutc.add_row(Row_t{column});
            layoutc[1]
                .format()
                .font_align(FontAlign::center)
                .hide_border();
            embed.add_row(Row_t{layoutc});
            embed[0]
                .format()
                .font_align(FontAlign::center);
        }
        else{
            embed.add_row(Row_t{PrintTab(5)+"User Query: "+string(name)});
            embed[0]
                .format()
                .font_align(FontAlign::center);
            embed.add_row(Row_t{PrintTab(98)+"No Results to Show! "});
            embed[1]
                .format()
                .font_align(FontAlign::center);
        }

            cout<<"\n"<<embed;
        if(rows>=1){
            HiddenCaret();
            gotoxy(3,4);
            cout<<PrintTab(120);
            gotoxy(28,4);
            cout<<"Are you sure you want to delete this record: ";
            while(true){
                    gotoxy(74,4);
                    color(Set[0]);
                    cout<<s1;

                    gotoxy(76,4);
                    color(Set[1]);
                    cout<<s2;

                    key = _getch();

                    if(key == 75 && (counter > 1 && counter <= 2)){
                        counter--;
                    }
                    else if(key == 77 && (counter >= 1 && counter < 2)){
                        counter++;
                    }

                    if(key == '\r'){
                        if(counter == 1){
                                fp=fopen(FILENAME,"r+");
                                fp1=fopen("temp.txt","w");

                                while(fscanf(fp,"%s %s %s %s",cont.name,cont.pnum,cont.email,cont.address)!=EOF){
                                          stringstream s1;
                                          s1<<cont.name;
                                          string str1=s1.str();
                                          replace(str1.begin(),str1.end(),'_',' ' );;
                                      if(string(str1)==name){
                                        continue;
                                      }
                                    fprintf(fp1,"%s %s %s %s\n",cont.name,cont.pnum,cont.email,cont.address);
                                }

                                fclose(fp);
                                fclose(fp1);
                                fp=fopen("contact.txt","w");
                                fp1=fopen("temp.txt","r+");

                                 while(fscanf(fp1,"%s %s %s %s",cont.name,cont.pnum,cont.email,cont.address)!=EOF){
                                    fprintf(fp,"%s %s %s %s\n",cont.name,cont.pnum,cont.email,cont.address);
                                }
                                fclose(fp);
                                fclose(fp1);
                                remove("temp.txt");

                                gotoxy(40,5);
                                color(46);
                                cout<<"--- Record is deleted successfully! ---";

                                color(31);
                                gotoxy(5,4);

                                counter=1;
                                cout<<PrintTab(80);
                                gotoxy(45,4);
                                cout<<"Do you want to retry again: ";

                                while(true){
                                    gotoxy(74,4);
                                    color(Set[0]);
                                    cout<<s1;

                                    gotoxy(76,4);
                                    color(Set[1]);
                                    cout<<s2;

                                    key=_getch();

                                       if(key == 75 && (counter > 1 && counter <= 2)){
                                            counter--;
                                        }
                                        else if(key == 77 && (counter >= 1 && counter < 2)){
                                            counter++;
                                        }
                                    if(key == '\r'){
                                        if(counter == 1){
                                            color(31);
                                            DeleteContacts();
                                        }
                                        if(counter == 2){
                                            color(31);
                                            Menu();
                                        }
                                    }

                                    Set[0]=31;
                                    Set[1]=31;

                                    s1="Y";
                                    s2="N";

                                    if(counter == 1){
                                        s1="Y";
                                        Set[0]=249;
                                    }
                                    if(counter == 2){
                                        s2="N";
                                        Set[1]=249;
                                    }
                                }
                                }
                                if(counter == 2){
                                counter=1;
                                color(31);
                                gotoxy(28,4);
                                cout<<PrintTab(80);
                                gotoxy(45,4);
                                cout<<"Do you want to retry again: ";
                                counter++;
                                while(true){
                                    gotoxy(74,4);
                                    color(Set[0]);
                                    cout<<s1;

                                    gotoxy(76,4);
                                    color(Set[1]);
                                    cout<<s2;

                                    key=_getch();

                                       if(key == 75 && (counter > 1 && counter <= 2)){
                                            counter--;
                                        }
                                        else if(key == 77 && (counter >= 1 && counter < 2)){
                                            counter++;
                                        }

                                    if(key == '\r'){
                                        if(counter == 1){
                                            color(31);
                                            DeleteContacts();
                                        }
                                        if(counter == 2){
                                            color(31);
                                            Menu();
                                        }
                                    }

                                    Set[0]=31;
                                    Set[1]=31;

                                    s1="Y";
                                    s2="N";

                                    if(counter == 1){
                                        s1="Y";
                                        Set[0]=249;
                                    }
                                    if(counter == 2){
                                        s2="N";
                                        Set[1]=249;
                                    }
                                    }
                                }
                    }

                    Set[0]=31;
                    Set[1]=31;

                    s1="Y";
                    s2="N";

                    if(counter == 1){
                        s1="Y";
                        Set[0]=249;
                    }
                    if(counter == 2){
                        s2="N";
                        Set[1]=249;
                    }
            }
        }
            else{
                                HiddenCaret();
                                gotoxy(3,4);
                                cout<<PrintTab(80);
                                gotoxy(28,4);
                                counter=1;
                                cout<<PrintTab(80);
                                gotoxy(45,4);
                                cout<<"Do you want to retry again: ";

                                while(true){
                                    gotoxy(74,4);
                                    color(Set[0]);
                                    cout<<s1;

                                    gotoxy(76,4);
                                    color(Set[1]);
                                    cout<<s2;

                                    key=_getch();

                                       if(key == 75 && (counter > 1 && counter <= 2)){
                                            counter--;
                                        }
                                        else if(key == 77 && (counter >= 1 && counter < 2)){
                                            counter++;
                                        }
                                    if(key == '\r'){
                                        if(counter == 1){
                                            color(31);
                                            DeleteContacts();
                                        }
                                        if(counter == 2){
                                            color(31);
                                            Menu();
                                        }
                                    }

                                    Set[0]=31;
                                    Set[1]=31;

                                    s1="Y";
                                    s2="N";

                                    if(counter == 1){
                                        s1="Y";
                                        Set[0]=249;
                                    }
                                    if(counter == 2){
                                        s2="N";
                                        Set[1]=249;
                                    }
                                }
                }


}

void AddContacts(){//Add Contacts Module

    int Set[]={249,31};

    FILE *fp;
    fp=fopen(FILENAME,"a+");

    FILE *fp2;
    fp2=fopen(FILENAME,"a+");

    FILE *fp1;
    fp1=fopen(FILENAME,"a+");

    ShowCaret();
    system("cls");

    struct Contact cont;


    Table mlayout;

    mlayout.format().border_color(Color::white);


    mlayout.add_row(Row_t{PrintTab(107)+"Add Contacts"});
    mlayout[0]
        .format()
        .font_align(FontAlign::center)
        .font_color(Color::blue)
        .font_background_color(Color::white);
    mlayout.add_row(Row_t{PrintBox(27)});
    cout<<mlayout;

    gotoxy(5,1);
    color(249);
    cout<<" Hello "+username+"! ";
    color(31);

    string a="Input Name: ";
    string b="Input Phone Number: ";
    string c="Input Email Address: ";
    string d="Input Address: ";
    string e="Do you want to enter another phone record:";

    string name;
    string pnum;
    string email;
    string address;

    char key;

    int counter=1;

    int dup;

     //Selection Strings
    string s1="Y";
    string s2="N";
    gotoxy(18,5);
    cout<<PrintLine(40);
    gotoxy(18,15);
    cout<<PrintLine(40);
    while(true){
        gotoxy(18,7);
        cout<<a;

        gotoxy(18,9);
        cout<<b;

        gotoxy(18,11);
        cout<<c;

        gotoxy(18,13);
        cout<<d;

        while(true){
            fp1=fopen(FILENAME,"a+");
            dup=0;
            ShowCaret();
            gotoxy(30,7);
            color(31);
            getline(cin, name);
            replace(name.begin(),name.end(), ' ', '_' );
              while(fscanf(fp1,"%s",cont.name)!=EOF){
                    if(string(cont.name)==name){
                            dup++;
                            fclose(fp1);
                            break;
                        }
              }
            if(dup==0){
                if(name==""){
                    gotoxy(29,8);
                    cout<<PrintTab(40);
                    gotoxy(29,8);
                    color(79);
                    cout<<"Please Input a Name!";
                }
                else{
                    strcpy(cont.name, name.c_str());
                    gotoxy(29,8);
                    cout<<PrintTab(40);
                    fclose(fp1);
                    fclose(fp1);
                    break;
                }
            }
            else{
                gotoxy(29,8);
                cout<<PrintTab(40);
                gotoxy(29,8);
                color(79);
                cout<<"Name is already enrolled!";
                gotoxy(30,7);
                color(31);
                cout<<PrintTab(40);
            }
        }

        while(true){
            fp2=fopen(FILENAME,"a+");
            dup=0;
            gotoxy(38,9);
            color(31);
            getline(cin, pnum);
            if(pnum==""){
                        gotoxy(37,10);
                        cout<<PrintTab(40);
                        gotoxy(37,10);
                        cout<<PrintTab(40);
                        gotoxy(37,10);
                        color(79);
                        cout<<"Please Input a Phone Number!";
                        continue;
            }
            if(hasSpace(pnum)){
                        gotoxy(37,10);
                        cout<<PrintTab(40);
                        gotoxy(38,9);
                        cout<<PrintTab(40);
                        gotoxy(37,10);
                        color(79);
                        cout<<"Please avoid in inputting a whitespace!";
                        continue;
            }
            while(fscanf(fp2,"%s",cont.pnum)!=EOF){
                 if(string(cont.pnum)==pnum){
                    dup++;
                    fclose(fp2);
                    break;
                }
            }
            if(dup==0){
                if(isNumber(pnum)==false){
                    gotoxy(37,10);
                    cout<<PrintTab(40);
                    gotoxy(37,10);
                    color(79);
                    cout<<"Invalid Phone Number!";
                    gotoxy(38,9);
                    color(31);
                    cout<<PrintTab(40);
                }
                else{
                        strcpy(cont.pnum, pnum.c_str());
                        gotoxy(37,10);
                        cout<<PrintTab(40);
                        fclose(fp2);
                        break;
                }
            }
            else{
                gotoxy(37,10);
                cout<<PrintTab(40);
                gotoxy(37,10);
                color(79);
                cout<<"Phone Number is already enrolled!";
                gotoxy(38,9);
                color(31);
                cout<<PrintTab(40);
            }
        }

        while(true){
        gotoxy(39,11);
        color(31);
        getline(cin, email);
            if(hasSpace(email)){
                gotoxy(39,11);
                cout<<PrintTab(70);
                gotoxy(39,12);
                color(79);
                cout<<"Please avoid in inputting a whitespace!";
            }
            else if(email==""){
                gotoxy(38,12);
                cout<<PrintTab(70);
                gotoxy(38,12);
                color(79);
                cout<<"Please Input a Email Address!";
            }
            else if(isEmail(email)==false){
                gotoxy(39,11);
                cout<<PrintTab(70);
                gotoxy(39,12);
                color(79);
                cout<<"Please Input a Valid Email Address!"<<PrintTab(5);
            }
            else{
                strcpy(cont.email, email.c_str());
                gotoxy(38,12);
                cout<<PrintTab(70);
                break;
            }
        }

        while(true){
        gotoxy(33,13);
        color(31);
        getline(cin, address);
        replace(address.begin(),address.end(), ' ', '_' );
            if(address==""){
                gotoxy(33,14);
                color(79);
                cout<<"Please Input a Address!";
            }
            else{
                strcpy(cont.address, address.c_str());
                gotoxy(33,14);
                cout<<PrintTab(40);
                break;
            }
        }

        fflush(stdin);
        fprintf(fp,"%s %s %s %s\n",cont.name,cont.pnum,cont.email,cont.address);
        fclose(fp);
        break;
    }

        color(46);
        gotoxy(36,17);
        cout<<"-- Phone Record is saved successfully! --";

        color(31);
        HiddenCaret();
        gotoxy(32,19);
        cout<<e;

        gotoxy(27,18);
        cout<<PrintLine(29);
        gotoxy(27,20);
        cout<<PrintLine(29);
        while(true){
            gotoxy(75,19);
            color(Set[0]);
            cout<<s1;

            gotoxy(77,19);
            color(Set[1]);
            cout<<s2;

            key = _getch();

            if(key == 75 && (counter > 1 && counter <= 2)){
                counter--;
            }
            else if(key == 77 && (counter >= 1 && counter < 2)){
                counter++;
            }

            if(key == '\r'){
                if(counter == 1){
                    color(31);
                    AddContacts();
                }
                if(counter == 2){
                    color(31);
                    Menu();
                }
            }

            Set[0]=31;
            Set[1]=31;

            s1="Y";
            s2="N";

            if(counter == 1){
                s1="Y";
                Set[0]=249;
            }
            if(counter == 2){
                s2="N";
                Set[1]=249;
            }
    }
}

void UpdateContacts(){//Update Contacts Module

    int Set[]={249,31};

    FILE *fp;
    fp=fopen(FILENAME,"a+");

    FILE *fp2;
    fp2=fopen(FILENAME,"a+");

    FILE *fp1;
    fp1=fopen(FILENAME,"a+");

    ShowCaret();
    system("cls");

    struct Contact cont;

    Table layout;
    Table column;
    Table embed;


    layout.format().border_color(Color::white);

    layout.add_row(Row_t{PrintTab(103)+"Update Contacts"});
    layout[0]
        .format()
        .font_align(FontAlign::center)
        .font_color(Color::blue)
        .font_background_color(Color::white);;

    layout.add_row(Row_t{PrintBox(27)});
    cout<<layout;

    gotoxy(5,1);
    color(249);
    cout<<" Hello "+username+"! ";
    color(31);

    string a="";
    string b="";
    string c="";
    string d="";
    string e="";

    string updname;

    string name;
    string pnum;
    string email;
    string address;

    char key;

    int counter=1;

    int rows=0;

    int dup;
     //Selection Strings
    string s1="Y";
    string s2="N";
    while(true){

        gotoxy(18,7);
        cout<<a;

        gotoxy(18,9);
        cout<<b;

        gotoxy(18,11);
        cout<<c;

        gotoxy(18,13);
        cout<<d;

        gotoxy(11,4);
        cout<<"Input the Full Name of the record that you want to update: ";
        getline(cin, updname);

        column.add_row(Row_t{PrintTab(16)+"NAME",PrintTab(13)+"PHONE NUMBER",PrintTab(16)+"EMAIL ADDRESS",PrintTab(16)+"ADDRESS"});
        column[0]
        .format()
        .font_align(FontAlign::center);
    while(fscanf(fp,"%s %s %s %s",cont.name,cont.pnum,cont.email,cont.address)!=EOF){
        stringstream s1;
        s1<<cont.name;
        string str1=s1.str();
        replace(str1.begin(),str1.end(),'_',' ' );;
        if(string(str1)==updname){

            stringstream s2;
            s2<<cont.pnum;
            string str2=s2.str();

            stringstream s3;
            s3<<cont.email;
            string str3=s3.str();

            stringstream s4;
            s4<<cont.address;
            string str4=s4.str();
            replace(str4.begin(),str4.end(),'_',' ' );


            column.add_row(Row_t{str1,str2,str3,str4});

            column
                .format()
                .font_align(FontAlign::center)
                .padding(0.7);


            rows++;
            }
        }
        column[0][0].format().width(28);
        column[0][1].format().width(27);
        column[0][2].format().width(28);
        column[0][3].format().width(28);
        Table layoutc;
            layoutc.add_row(Row_t{PrintTab(5)+"User Query: "+string(name)});
            layoutc[0]
                .format()
                .font_align(FontAlign::center)
                .hide_border();

        fclose(fp);
    if(rows>0){
            a="Input Name: ";
            b="Input Phone Number: ";
            c="Input Email Address: ";
            d="Input Address: ";
            e="Do you want to enter another phone record:";

            gotoxy(18,7);
            cout<<a;

            gotoxy(18,9);
            cout<<b;

            gotoxy(18,11);
            cout<<c;

            gotoxy(18,13);
            cout<<d;

            gotoxy(11,5);
            cout<<PrintLine(50);
            gotoxy(11,15);
            cout<<PrintLine(50);

            while(true){
            fp1=fopen(FILENAME,"a+");
            dup=0;
            ShowCaret();
            gotoxy(30,7);
            color(31);
            getline(cin, name);
            if(string(updname)!=name){
            replace(name.begin(),name.end(), ' ', '_' );
              while(fscanf(fp1,"%s",cont.name)!=EOF){
                   if(string(cont.name)==name){
                        dup++;
                        fclose(fp1);
                        break;
                    }
              }
            }
            else{
                replace(name.begin(),name.end(), ' ', '_' );
                dup=0;
            }
            if(dup==0){
                if(name==""){
                    gotoxy(29,8);
                    color(79);
                    cout<<"Please Input a Name!";
                }
                else{
                    strcpy(cont.name, name.c_str());
                    gotoxy(29,8);
                    cout<<PrintTab(40);
                    fclose(fp1);
                    break;
                }
            }
            else{
                gotoxy(29,8);
                color(79);
                cout<<"Name is already enrolled!";
                gotoxy(30,7);
                color(31);
                cout<<PrintTab(40);
            }
        }

        while(true){
            fp2=fopen(FILENAME,"a+");
            dup=0;
            gotoxy(38,9);
            color(31);
            getline(cin, pnum);
            if(pnum==""){
                        gotoxy(37,10);
                        cout<<PrintTab(40);
                        gotoxy(37,10);
                        cout<<PrintTab(40);
                        gotoxy(37,10);
                        color(79);
                        cout<<"Please Input a Phone Number!";
                        continue;
            }
            if(hasSpace(pnum)){
                        gotoxy(37,10);
                        cout<<PrintTab(40);
                        gotoxy(38,9);
                        cout<<PrintTab(40);
                        gotoxy(37,10);
                        color(79);
                        cout<<"Please avoid in inputting a whitespace!";
                        continue;
            }
            fclose(fp2);
            fp2=fopen(FILENAME,"a+");
            dup=0;
            while(fscanf(fp2,"%s",cont.pnum)!=EOF){
                if(string(cont.pnum)==pnum){
                        dup++;
                        fclose(fp2);
                        break;
                }
            }
            if(dup==0){
                if(isNumber(pnum)==false){
                    gotoxy(37,10);
                    cout<<PrintTab(40);
                    gotoxy(37,10);
                    color(79);
                    cout<<"Invalid Phone Number!";
                    gotoxy(38,9);
                    color(31);
                    cout<<PrintTab(40);
                }
                else{
                        strcpy(cont.pnum, pnum.c_str());
                        gotoxy(37,10);
                        cout<<PrintTab(40);
                        fclose(fp2);
                        break;
                }
            }
            else{
                gotoxy(37,10);
                cout<<PrintTab(40);
                gotoxy(37,10);
                color(79);
                cout<<"Phone Number is already enrolled!";
                gotoxy(38,9);
                color(31);
                cout<<PrintTab(40);
            }
        }

        while(true){
        gotoxy(39,11);
        color(31);
        getline(cin, email);
            if(hasSpace(email)){
                gotoxy(39,11);
                cout<<PrintTab(70);
                gotoxy(39,12);
                color(79);
                cout<<"Please avoid in inputting a whitespace!";
            }
            else if(email==""){
                gotoxy(38,12);
                cout<<PrintTab(70);
                gotoxy(38,12);
                color(79);
                cout<<"Please Input a Email Address!";
            }
            else if(isEmail(email)==false){
                gotoxy(39,11);
                cout<<PrintTab(70);
                gotoxy(39,12);
                color(79);
                cout<<"Please Input a Valid Email Address!"<<PrintTab(5);
            }
            else{
                strcpy(cont.email, email.c_str());
                gotoxy(38,12);
                cout<<PrintTab(70);
                break;
            }
        }

        while(true){
        gotoxy(33,13);
        color(31);
        getline(cin, address);
        replace(address.begin(),address.end(), ' ', '_' );
            if(address==""){
                gotoxy(33,14);
                color(79);
                cout<<"Please Input a Address!";
            }
            else{
                strcpy(cont.address, address.c_str());
                gotoxy(33,14);
                cout<<PrintTab(40);
                break;
            }
        }

            fp=fopen(FILENAME,"r+");
            fp1=fopen("temp.txt","w");

            while(fscanf(fp,"%s %s %s %s",cont.name,cont.pnum,cont.email,cont.address)!=EOF){
                stringstream s1;
                s1<<cont.name;
                string str1=s1.str();
                replace(str1.begin(),str1.end(),'_',' ' );;
                if(string(str1)==updname){
                    fprintf(fp1,"%s %s %s %s\n",name.c_str(),pnum.c_str(),email.c_str(),address.c_str());
                }
                else{
                    fprintf(fp1,"%s %s %s %s\n",cont.name,cont.pnum,cont.email,cont.address);
                }
                }

                fclose(fp);
                fclose(fp1);
                fp=fopen("contact.txt","w");
                fp1=fopen("temp.txt","r+");

                while(fscanf(fp1,"%s %s %s %s",cont.name,cont.pnum,cont.email,cont.address)!=EOF){
                    fprintf(fp,"%s %s %s %s\n",cont.name,cont.pnum,cont.email,cont.address);
                }
                fclose(fp);
                fclose(fp1);
                remove("temp.txt");
            color(46);
            gotoxy(36,17);
            cout<<"-- Phone Record is updated successfully! --";

            color(31);
            HiddenCaret();
            gotoxy(32,19);
            cout<<e;

            gotoxy(27,18);
            cout<<PrintLine(29);
            gotoxy(27,20);
            cout<<PrintLine(29);
            while(true){
                gotoxy(75,19);
                color(Set[0]);
                cout<<s1;

                gotoxy(77,19);
                color(Set[1]);
                cout<<s2;

                key = _getch();

                if(key == 75 && (counter > 1 && counter <= 2)){
                    counter--;
                }
                else if(key == 77 && (counter >= 1 && counter < 2)){
                    counter++;
                }

                if(key == '\r'){
                    if(counter == 1){
                        color(31);
                        UpdateContacts();
                    }
                    if(counter == 2){
                        color(31);
                        Menu();
                    }
                }

                Set[0]=31;
                Set[1]=31;

                s1="Y";
                s2="N";

                if(counter == 1){
                    s1="Y";
                    Set[0]=249;
                }
                if(counter == 2){
                    s2="N";
                    Set[1]=249;
                }
        }
    }
        else{
            e="Do you want to retry again:";
            embed.add_row(Row_t{PrintTab(5)+"User Query: "+string(updname)});
            embed[0]
                .format()
                .font_align(FontAlign::center);
            embed.add_row(Row_t{PrintTab(98)+"No Results to Show! "});
            embed[1]
                .format()
                .font_align(FontAlign::center);
            cout<<embed;
              HiddenCaret();
            gotoxy(42,12);
            gotoxy(42,12);
            cout<<e;

            gotoxy(27,11);
            cout<<PrintLine(32);
            gotoxy(27,13);
            cout<<PrintLine(32);
            while(true){
                gotoxy(70,12);
                color(Set[0]);
                cout<<s1;

                gotoxy(72,12);
                color(Set[1]);
                cout<<s2;

                key = _getch();

                if(key == 75 && (counter > 1 && counter <= 2)){
                    counter--;
                }
                else if(key == 77 && (counter >= 1 && counter < 2)){
                    counter++;
                }

                if(key == '\r'){
                    if(counter == 1){
                        color(31);
                        UpdateContacts();
                    }
                    if(counter == 2){
                        color(31);
                        Menu();
                    }
                }

                Set[0]=31;
                Set[1]=31;

                s1="Y";
                s2="N";

                if(counter == 1){
                    s1="Y";
                    Set[0]=249;
                }
                if(counter == 2){
                    s2="N";
                    Set[1]=249;
                }

            }
        }

            cout<<"\n"<<embed;
    }
}

void HiddenCaret(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursoInfo;
    CursoInfo.dwSize = 1;
    CursoInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &CursoInfo);
}

void ShowCaret(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursoInfo;
    CursoInfo.dwSize = 1;
    CursoInfo.bVisible = true;
    SetConsoleCursorInfo(hConsole, &CursoInfo);
}

void MoveWindow(int posx, int posy)
{
    RECT rectClient, rectWindow;
    HWND hWnd = GetConsoleWindow();
    GetClientRect(hWnd, &rectClient);
    GetWindowRect(hWnd, &rectWindow);
    MoveWindow(hWnd, posx, posy, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);
}

void MoveCenter()
{
    RECT rectClient, rectWindow;
    HWND hWnd = GetConsoleWindow();
    GetClientRect(hWnd, &rectClient);
    GetWindowRect(hWnd, &rectWindow);
    int posx, posy;
    posx = GetSystemMetrics(SM_CXSCREEN) / 2 - (rectWindow.right - rectWindow.left) / 2,
    posy = GetSystemMetrics(SM_CYSCREEN) / 2 - (rectWindow.bottom - rectWindow.top) / 2,
    MoveWindow(hWnd, posx, posy, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);
}

void HideMaxBtn(){
    HWND hwnd = GetConsoleWindow();
    DWORD style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~WS_MAXIMIZEBOX;
    SetWindowLong(hwnd, GWL_STYLE, style);
    SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE|SWP_FRAMECHANGED);
}
