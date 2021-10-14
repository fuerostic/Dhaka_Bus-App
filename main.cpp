#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <term.h>
#include <chrono>

using namespace std;

map<string, vector<string>>BusName;

map<string, vector<string >>Places;

bool regist;

void gotoxy(int x,int y)
{
    printf("%c[%d;%df",0x1B,y,x);
}

void centerstring(string s)
{
   int l=s.length();
   int pos=(int)((80-l)/2);
   for(int i=0;i<pos;i++)
    cout<<" ";

   cout<<s;
}

void showLogo()
{
    //system("clear");
    cout<<endl;
    centerstring("                   █▀▀▄ █░░█ █▀▀█ █░█ █▀▀█   █▀▀▄ █░░█ █▀▀");
    cout<<endl;
    centerstring("                   █░░█ █▀▀█ █▄▄█ █▀▄ █▄▄█   █▀▀▄ █░░█ ▀▀█");
    cout<<endl;
    centerstring("                   ▀▀▀░ ▀░░▀ ▀░░▀ ▀░▀ ▀░░▀   ▀▀▀░ ░▀▀▀ ▀▀▀");
    cout<<endl<<endl;
    centerstring("A Bus Finding App");
    cout<<endl<<endl;
}
bool fexists(string filename) {
  ifstream ifile("loginInfo//"+filename + ".txt");
  return (bool)ifile;
}

class signup
{
    string username,pass,confPass;

public:

    void reg()
    {
        //system("clear");
        system("clear");
        showLogo();
        cout<<endl;
        cout<<right<<setw(40)<<"Enter your username(without space): ";
        //gotoxy(35,12);
        cin>> username;
        cout<<endl;

        if(fexists(username))
        {
            centerstring("Username already exists");
            cout<<endl;
            regist = false;
            cin.ignore();
            cin.ignore();
            return;
        }

        cout<<right<<setw(40)<<"Enter your password:";
        cin>> pass;
        cout<<endl;

        ofstream file;

        file.open("loginInfo//"+username + ".txt");

        file << username << endl << pass<<endl;

        file.close();

        centerstring("Thank you for signing up. You can log in now.");

        cin.ignore();

        cout<<endl;

        regist = true;

        ofstream f;

        f.open("history//"+username + "set.txt");
        f << 100;

        f.close();

        cin.ignore();

        system("clear");

    }
};

class login: signup
{
    string pass,us,pw;

public:

    string username;

    bool isLoggedIn()
    {
        system("clear");
        showLogo();
        cout<<endl<<endl;
        cout<<right<<setw(40)<<"USERNAME:";
        //cout<<setw(16)<<left;
        //gotoxy(35,12);
        cin>> username;
        cout<<endl;

        cout<<right<<setw(40)<<"PASSWORD:";
        //cout<<setw(16)<<left;
        //gotoxy(35,15);
        cin>>pass;
        cout<<endl;

        ifstream read("loginInfo//"+username+".txt");

        getline(read,us);
        getline(read,pw);

        if(us==username && pw==pass)
        {
            return true;
        }
        else
            return false;
    }

    void resetPassword()
    {
        system("clear");
        showLogo();
        if(isLoggedIn())
        {
            cout<<right<<setw(40)<<"Enter your new password: ";

            //gotoxy(35,15);
            cin>> pass;

            cout<<endl;

            ofstream file;

            file.open("loginInfo//"+username + ".txt");

            file << username << endl << pass<<endl;

            file.close();

            cout<<"Password reset successful!";

            cin.ignore();
        }
        else
        {
            centerstring("Error password reset");
            cout<<endl;
            cin.ignore();
        }
    }

    friend void showTime(login );

};
void showTime(login l)
{
     // declaring argument of time()
    time_t my_time = time(NULL);

    // ctime() used to give the present time
    system("clear");
    cout<<"user: "<<left<<setw(20)<<l.username<<right<<setw(52)<< ctime(&my_time)<<endl;
}

string timeStamp()
{
    time_t my_time = time(NULL);

    return ctime(&my_time);
}



class findBus:virtual login
{
public:

    string from,to;

    void info(string s)
    {
        username = s;
    }

    void findRoute()
    {
        system("clear");
        showLogo();
        //cout<<endl<<endl;
        cin.ignore();

        cout<<right<<setw(40)<<"Enter the starting point: ";
        //cout<<endl;
        //gotoxy(32,15);
        getline(cin,from);

        cout<<endl;

        cout<<right<<setw(40)<<"Enter the destination: ";
        //cout<<endl;
        //gotoxy(32,19);
        getline(cin,to);

        cout<<endl;
        system("clear");
        showLogo();

        string bus1,bus2;

        ofstream file;

        file.open("history//"+username + ".txt",ios::app);

        file <<timeStamp()<< from << endl << to<<endl;

        file.close();

        bool route = false;

        map<string,int >bus;

        for(int  i=0; i!=Places[from].size(); i++)
        {
            bus1 = Places[from][i];

            for(int j=0; j!=Places[to].size(); j++)
            {
                bus2 = Places[to][j];

                if(bus1==bus2)
                {
                    //centerstring(bus1);
                    bus[bus1]=0;
                    cout<<endl;
                    route  = true;
                }
            }

        }

        if(!route)
            centerstring("No direct route found");
        else
        {
            for(auto it:bus)
            {
                auto i = find(BusName[it.first].begin(),BusName[it.first].end(),from);
                auto j = find(BusName[it.first].begin(),BusName[it.first].end(),to);

                bus[it.first] = abs(i-j);
            }

            cout<<"########## Busname ############ Distance(unit) ########## Fare(Estimated) ######"<<endl;
            int counter=1;
            for(auto it:bus)
            {
                cout<<right<<setw(5)<<counter<<". "<<left<<setw(35)<<it.first<<right<<setw(2)<<it.second<<right<<setw(25)<<it.second*1.6<<endl;
                counter++;
            }
            cout<<"################################################################################"<<endl;
        }
        cout<<endl;

        cin.ignore();

    }



};

class history:virtual login
{
public:

    void info(string s)
    {
        username = s;
    }
    void showHistory()
    {
        //cout<<username<<endl;
        showLogo();
        //cout<<username<<endl;
        ifstream read("history//"+username+".txt");

        ifstream file("history//"+username + "set.txt");

        int  n;

        file>> n;

        int t=1;

        //cout<< n<<endl;
        while(!read.eof() && t<=n)
        {
            string searched,from;
            getline(read,searched);

            //from.push_back('0'+t);

            from+=searched;
            from+=" ";

            getline(read,searched);

            if(searched=="")
                break;
            from += " FROM: ";
            from+=searched;

            getline(read,searched);

            from+= " TO: ";
            from+=searched;
            from.push_back(' ');

            cout<<right<<setw(10)<<t<<". "<<from<<endl;
            //cout<<endl;
            t++;

        }

        cin.ignore();
    }

    void deleteAllHistory()
    {
        system("clear");
        showLogo();
        if(isLoggedIn())
        {
            ofstream ofs("history//"+username+".txt");

            centerstring("All history deleted successfully");
            cout<<endl;
            cin.ignore();
            cin.ignore();
        }

        else
        {
            centerstring("Sorry, Password Mismatched.");
            cout<<endl;
            cin.ignore();
            cin.ignore();
        }
    }

    void showResultDensity()
    {
        int n;
        system("clear");
        showLogo();
        cout<<right<<setw(40)<<"Maximum number of search history: ";
        cin>>n;
        cout<<endl;

        ofstream file;

        file.open("history//"+username + "set.txt");
        file << n;

        file.close();

        centerstring("Maximum number of history result changed successfully");
        cout<<endl;
        cin.ignore();
        cin.ignore();

    }
    void historySetting()
    {
        string choice ;

        while(1)
        {
            system("clear");
            showLogo();

            centerstring("1. Delete all history\n\n");
            centerstring("2. Change maximum number of history result\n\n");
            centerstring("3. Back\n\n");

            cin>>choice;

            if(choice=="1")
            {
                deleteAllHistory();
            }
            else if(choice=="2")
            {
                showResultDensity();
            }
            else if(choice=="3")
            {
                break;
            }
            else
            {
                centerstring("Invalid input\n");
                cin.ignore();
            }

        }
    }

};

class settings:public findBus, public history
{
    public:

        void info(string s)
        {
            history:: info(s);
        }

};

class busData
{
public:

    void showBusdata()
    {
        while(1)
        {
            system("clear");
            showLogo();
            int i=1,num;
            cout<<right<<setw(25)<<0<<". Back"<<endl;
            for(auto it:BusName)
            {
                if(it.first=="")
                    continue;
                cout<<right<<setw(25)<<i<<". "<<it.first<<endl;
                i++;
            }
            i=0;

            cout<<right<<setw(30)<<"Enter your choice: ";

            cin>> num;

            cout<<endl;

            if(num==0)
                break;
            else
            {
                for(auto it: BusName)
                {


                    if(it.first=="")
                        continue;

                    i++;

                    if(i==num)
                    {
                        system("clear");
                        showLogo();
                        centerstring(it.first);
                        cout<<endl<<endl;

                        centerstring("The route covers the following areas:\n");

                        for(auto j: BusName[it.first])
                        {
                            centerstring(j);
                            cout<<endl;
                        }

                        cin.ignore();
                        cin.ignore();

                        break;
                    }

                }
            }
        }
    }
};

class places
{
public:

    void showPlaces()
    {

        int i=0;
        system("clear");
        showLogo();

        centerstring("All places covered in this app: ");
        cout<<endl<<endl;

        for(auto it: Places)
        {
            if(it.first=="")
                continue;
            i++;
            cout<<right<<setw(25)<<i<<". "<<it.first<<endl;
        }

        cin.ignore();
        cin.ignore();

    }

};


int main()
{


    ifstream input("resource//info.txt");

    int n;

    while(!input.eof())
    {
        input>>n;
        input.ignore();
        if(n==0)
            break;

        string busname,place;

        getline(input,busname);

        for(int i=0; i<n; i++)
        {
            getline(input,place);

            BusName[busname].emplace_back(place);
            Places[place].emplace_back(busname);
        }

        //cout<< busname << " "<<place<<endl;
    }


    input.close();

    login l;

    signup reg;

    bool ex = false;

    while(1)
    {
        cout<<endl;
        system("clear");
        showLogo();
        cout<<endl<<endl;
        centerstring("1.Register");
        cout<<endl<<endl;
        centerstring("2.Login");
        cout<<endl<<endl;
        centerstring("3.Exit");
        cout<<endl<<endl;

        string choice;

        cin>>choice;

        if(choice=="1")
        {
            reg.reg();
        }
        if((choice=="2" )|| (choice=="1"  && regist))
        {
            bool status = l.isLoggedIn();

            if(!status)
            {
                system("clear");
                showLogo();
                centerstring("Error login");
                cout<<endl;
                cin.ignore();
                cin.ignore();
                //  system("PAUSE");

            }
            else
            {
                showTime(l);
                showLogo();
                centerstring("Successfully logged in");
                cout<<endl;

                string  choice;

                while(1)
                {
                    showTime(l);
                    showLogo();
                    centerstring("1.Find bus");
                    cout<<endl<<endl;
                    centerstring("2.History");
                    cout<<endl<<endl;
                    centerstring("3.Bus Data");
                    cout<<endl<<endl;
                    centerstring("4.All Places");
                    cout<<endl<<endl;
                    centerstring("5.Settings");
                    cout<<endl<<endl;
                    centerstring("6.About this app");
                    cout<<endl<<endl;
                    centerstring("7.Log out");
                    cout<<endl;

                    cin>> choice;

                    if(choice=="1")
                    {
                        showTime(l);
                        findBus fb;

                        fb.info(l.username);

                        fb.findRoute();

                        //cin.ignore();
                    }
                    else if(choice=="2")
                    {
                        showTime(l);
                        history hs;

                        string s = l.username;

                        hs.info(l.username);

                        hs.showHistory();

                        cin.ignore();

                       // cin.ignore();
                    }
                    else if(choice =="3")
                    {
                        showTime(l);
                        busData b;

                        b.showBusdata();
                    }
                    else if(choice =="4")
                    {
                        showTime(l);
                        places p;

                        p.showPlaces();


                    }
                    else if(choice=="5")
                    {
                        settings st;

                        while(1)
                        {
                            showTime(l);
                            showLogo();
                            centerstring("1. Reset Password\n\n");
                            centerstring("2. History Setting\n\n");
                            centerstring("3. Back\n");

                            string choice;

                            cin>> choice;

                            if(choice=="1")
                            {
                                showTime(l);
                                l.resetPassword();
                            }
                            else if(choice=="2")
                            {
                                showTime(l);
                                st.info(l.username);
                                st.historySetting();
                            }
                            else if(choice=="3")
                            {
                                break;
                            }
                            else
                            {

                                centerstring("Invalid Input");
                                cout<<endl;
                                cin.ignore();
                            }
                        }


                    }
                    else if(choice=="6")
                    {
                        showTime(l);
                        showLogo();
                        centerstring("DHAKA BUS is an informative application to find buses on a certain route.\n");
                        centerstring("This application provides the buses available in desired routes. Many people\n");
                        centerstring("in Dhaka relies on public bus transport because it is the cheapest and reliable\n");
                        centerstring("way of transportation. This application is helpful to find suitable busses\n");
                        centerstring("on the desired route of destination.\n");
                        cout<<endl;
                        centerstring("DHAKA BUS application is designed by Mohtasim Fuad,CSE,KUET 2k17.\n");
                        cin.ignore();
                        cin.ignore();
                    }

                    else if(choice=="7")
                    {
                        break;
                    }

                    else
                    {
                        cout<<"invalid input"<<endl;
                        cin.ignore();
                    }
                }

              //  return 1;
            }
        }

        if(choice=="3")
        {
            system("clear");
            centerstring("Thank you for using this app.");
            cout<<endl;
            break;
        }
    }

    return 0;
}
