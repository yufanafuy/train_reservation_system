#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>
using namespace std;

// User-defined functions START
void addTrain(string train_name, string source, string destination, string time, string ETA, string price);
void deleteTrain(string train_name, char withCustInfo);
void bookTicket(string train_name, string name, string phone_number, string id, int coach, int seat);
void viewTrains();
void viewSeats(string train_name, int coach);
void adminViewCustInfo(string train_name);
void main_menu();
void ticket_menu();
void admin_menu();
string getTrainName(string train_id);
int getCoach(string train_name, int &n);
int getSeat(string train_name, int coach);
void adminDeleteTrain();
void adminViewCust();
void adminlogin();
//User-defined functions END

int main()
{
    main_menu();
}

void addTrain(string train_name, string source, string destination, string time, string ETA, string price)
{
  ofstream train_seats;
  string filename = train_name + "-" + source + "-" + destination + "-" + time + "-" + ETA + "-" + price;
  train_seats.open(filename);
  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 40; j++)
    {
      train_seats << "0";
    }
    train_seats << "\n";
  }
  train_seats.close();

  ofstream custInfo;
  string filename2 = train_name + "-" + source + "-" + destination + "-" + time + "-Customers Information";
  custInfo.open(filename2);
  custInfo.close();

  ofstream trainlist;
  trainlist.open("Train List", ios::app);
  trainlist << filename + "\n";
  trainlist.close();
}

void deleteTrain(string train_name, char withCustInfo)
{
  //Delete Files
  char filename[train_name.size() + 1];
  strcpy(filename, train_name.c_str());

  string train_name2 = train_name + "-Customers Information";
  char filename2[train_name2.size() + 1];
  strcpy(filename2, train_name2.c_str());

  if (withCustInfo == '0')
  {
    remove(filename);
  }
  else
  {
    remove(filename);
    remove(filename2);
  }

  //Update Train list
  string line;
  ifstream readFile;
  readFile.open("Train List");
  ofstream temp;
  temp.open("temp");

  while(getline (readFile, line))
  {
    if (line != filename)
    {
      temp << line <<endl;
    }
  }
  temp.close();
  readFile.close();
  remove("Train List");
  rename("temp", "Train List");
}

void viewTrains()
{
  ifstream viewTrains;
  viewTrains.open("Train List");
  string list;
  system("CLS");
  time_t currentTime;
    time(&currentTime);
    cout<<"\n \t\t\t\t"<<ctime(&currentTime);
    cout<<"-------------------------- High Speed Train Reservation System ----------------------------------------------\n\n";
    cout<<" Train\t\t"<<" Source\t\t   "<<"    Destination\t"<<"   Departure Time   "<<" Arrival Time\t"<<"Price"<<"\n";

  while(getline(viewTrains, list, '-'))
  cout << list << "\t\t";
}

void viewSeats(string train_name, int coach)
{
  ifstream viewSeats;
  viewSeats.open(train_name);
  char seats[10][40];
  while(!viewSeats.eof())
  {
    for(int i = 0; i < 10; i++)
    {
        for (int j = 0; j<40; j++)
        {
            viewSeats >> seats[i][j];
        }
    }
  }
  for (int j = 0; j<40; j++)
      {
          if (j%4 == 0 && seats[coach][j] == '0')
          {
            cout << endl << endl;
            cout << j+1 << "\t";
          }
          else if (j%4 != 0 && seats[coach][j] == '0')
          {
            cout << j+1 << "\t";
          }
          else if(j%4 == 0 && seats[coach][j] == '1')
          {
            cout << endl << endl;
            cout << "X" << "\t";
          }
          else if (j%4 != 0 && seats[coach][j] == '1')
          {
            cout << "X" << "\t";
          }
      }
      cout << endl;

  viewSeats.close();
}

void bookTicket(string train_name, string name, string phone_number, string id, int coach, int seat)
{
  string coach_string = to_string(coach);
  string seat_string = to_string(seat);
  ofstream file;
  string filename = train_name + "-Customers Information";
  file.open(filename, ios::app);
  file << name + "#" + phone_number + "#" + id + "#" + coach_string + "#" + seat_string + "\n";
  file.close();

  //Update Seats file
  string line;
  ifstream readFile;
  readFile.open(train_name);
  ofstream temp;
  temp.open("temp", ios::app);

  char seats[10][40];
  while(!readFile.eof())
  {
    for(int i = 0; i < 10; i++)
    {
        for (int j = 0; j<40; j++)
        {
            readFile >> seats[i][j];
        }
    }
  }

  seats[coach][seat-1] = '1';

  for(int i = 0; i < 10; i++)
  {
      for (int j = 0; j<40; j++)
      {
          temp << seats[i][j];
      }
      temp << "\n";
  }


  char train_name_file[train_name.size() + 1];
  strcpy(train_name_file, train_name.c_str());
  temp.close();
  readFile.close();
  remove(train_name_file);
  rename("temp", train_name_file);
  cout<<"Booking completed successfully! Press ENTER to continue";
  getchar();
  system("CLS");

}

void adminViewCustInfo(string train_name)
{ char ch;
  ifstream custInfo;
  custInfo.open(train_name + "-Customers Information");
  string line;
  cout<<endl;
  cout<<"Customer's Name\t"<<"       Phone Number\t\t"<<" ID Number\t"<<"      Coach\t"<<"       Seat"<<endl;
  while(getline (custInfo, line, '#'))
  {
    cout << line << "\t\t";
  }
  cout<<endl;
  cout<<"Continue viewing? (y/n)";
  cin>>ch;
  if(ch == 'y')
    {
      system("CLS");
      adminViewCust();
    }
  else
    {
      system("CLS");
      admin_menu();
    }

}

// Main Menu START
void main_menu()
{
  time_t currentTime;
  time(&currentTime);
  cout<<"\n \t\t\t\t"<<ctime(&currentTime);
  cout<<"-------------------------- High Speed Train Reservation System ----------------------------------------------\n\n";
  cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Welcome User >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n";
  cout << "1) Book Ticket" <<endl;
  cout << "2) Exit" <<endl;
  char choice;
  cout<<endl;
  cout<<"Choice: ";
  cin >> choice;
  if (choice == '1')
      ticket_menu();
  else if (choice == '9')
      adminlogin();
  else
      exit(0);
}
 // Main Menu END

void ticket_menu()
{
    viewTrains();
    cout << endl;
    cout << "Enter train ID: ";
    string train_id, train_name;
    cin.ignore();
    getline(cin, train_id);
    if(getTrainName(train_id) != "0")
        train_name = getTrainName(train_id);
    else
    {
        cout<< "Train does not exist!" << endl;
        cout<<"Continue? (y/n) ";
        char choice;
        cin>>choice;
        if(choice == 'y')
        {
          system("CLS");
          ticket_menu();
        }
        else
        {
          system("CLS");
          main_menu();
        }
    }
    system("CLS");
    time_t currentTime;
    time(&currentTime);
    cout<<"\n \t\t\t\t"<<ctime(&currentTime);
    cout<<"--------------------------High Speed Train Reservation System----------------------------------------------\n\n";
    cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Welcome User >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n";
    int amount;
    cout << "Number of seats to buy (Maximum 10): "; cin >> amount;
    if(amount <=10)
    {
      int count = 0;
      while(count < amount)
      {
        int coach = 0;
        cout << "Ticket: " << count + 1<<endl<<" Press Enter to continue..." << endl;
        getchar();
        getCoach(train_name, coach);
        int seat = getSeat(train_name, coach);
        string name, phone_number, id;
        system("CLS");
        cin.ignore();
        cout << "Name: "; getline(cin, name);
        cout << "Phone Number: "; getline(cin, phone_number);
        cout << "ID: "; getline(cin, id);
        bookTicket(train_name, name, phone_number, id, coach, seat);
        count++;
    }
  }
    else
    {
        cout << "You are not allowed to buy more than 10 tickets. Press ENTER to continue." << endl;
        cin.ignore();
        getchar();
        ticket_menu();
    }
    system("CLS");
    main_menu();
}

void admin_menu()
{   cout<<"-------------------------- High Speed Train Reservation System --------------------------------------------------------\n\n";
	cout<<"           <<<<<<<<<<<<<<< Welcome Admin >>>>>>>>>>>>>>>\n";
	cout<< endl << endl;
    cout << "1) Add Train" << endl;
    cout << "2) Delete Train" << endl;
    cout << "3) View Customer Information" << endl;
    cout << "4) Back"<<endl;
    cout<<endl;
    cout<<"Choice: ";
    char choice;
    cin >> choice;
    if (choice == '1')
    {
      system("CLS");
      cout<<"-------------------------- High Speed Train Reservation System --------------------------------------------------------\n\n";
      cout<<"           <<<<<<<<<<<<<<< Welcome Admin >>>>>>>>>>>>>>>\n\n";
      string train_name, source, destination, time, ETA, price;
      cin.ignore();
      cout << "Train name: "; getline(cin, train_name);
      cout << "Source: "; getline(cin, source);
      cout << "Destination: "; getline(cin, destination);
      cout << "Time Of Departure: "; getline(cin, time);
      cout << "Estimated Time Of Arrival: "; getline(cin, ETA);
      cout << "Price: "; getline(cin, price);
      price = "RM " + price;
      cout <<endl;
      cout <<"Confirm add '"<<train_name<<"' ? (y/n)";
      char choice;
      cin>>choice;
      if(choice=='y')
      {
        addTrain(train_name, source, destination, time, ETA, price);
        cout<<train_name<<" added successfully! Press Enter to continue...";
        cin.ignore();
        getchar();
        system("CLS");
        admin_menu();
      }
      else
        {
          cout<<"Operation Canceled! Press ENTER to continue...";
          cin.ignore();
          getchar();
          system("CLS");
          admin_menu();
        }
    }
    else if (choice == '2')
        adminDeleteTrain();
    else if (choice == '3')
        adminViewCust();
    else if (choice == '4')
        {
          system("CLS");
          main_menu();
        }
    else
    {
        cout << "Invalid choice! Please try again! Press ENTER to continue...";
        cin.ignore();
        getchar();
        admin_menu();
    }
}

string getTrainName(string train_id)
{
    ifstream readFile;
    readFile.open("Train List");
    string line;
    while(getline(readFile, line))
    {
        size_t found = line.find(train_id);
        if (found != string::npos)
            return line;
    }
    return "0";
}

int getCoach(string train_name, int &n)
{
    system("CLS");
    time_t currentTime;
    time(&currentTime);
    cout<<"\n \t\t\t\t"<<ctime(&currentTime);
    cout<<"-------------------------- High Speed Train Reservation System ----------------------------------------------\n\n";
    cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Welcome User >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n";
    cout << endl << "Coach: " << n+1 << endl;
    viewSeats(train_name, n);
    cout << endl;
    cout << "1) Select this coach" << endl;
    cout << "2) Next coach " << endl;
    cout << "3) Previous coach " << endl;
    cout << "4) Main Menu" << endl;
    char choice;
    cout << endl << "Choice: " << endl;
    cin >> choice;
    switch(choice)
    {
      case '1':
          return n;
          break;
      case '2':
        if (n < 9)
        {
            n++;
            getCoach(train_name, n);
        }
        else
        {
            cout << "This is the last coach! Press ENTER to continue..." << endl;
            cin.ignore();
            getchar();
            getCoach(train_name, n);
        }
        break;
      case '3':
        if (n > 0)
        {
            n--;
            getCoach(train_name, n);
        }
        else
        {
            cout << "This is the first coach! Press ENTER to continue..." << endl;
            cin.ignore();
            getchar();
            getCoach(train_name, n);
        }
      case '4':
        system("CLS");
        main_menu();
        break;
      default:
        cout << "Invalid choice! Please try again! Press ENTER to continue..." << endl;
        cin.ignore();
        getchar();
        getCoach(train_name, n);
    }
}

int getSeat(string train_name, int coach)
{
    system("CLS");
    cout << endl << "Coach: " << coach+1 << endl;
    viewSeats(train_name, coach);
    cout << endl << "Enter seat number: ";
    int seat; cin >> seat;
    cout<<"Confirm seat number: "<<seat<<" ? (y/n)";
    cout<<endl;
    char choice;
    cin>>choice;
    if(choice == 'y')
        {
            if (seat >= 1 && seat <=40)
                return seat;
            else
            {
                cout << "Invalid seat number! Please try again!"<< endl;
                cout << "Press ENTER to continue..." << endl;
                cin.ignore();
                getchar();
                getSeat(train_name, coach);
            }
        }
    else
        {
            system("CLS");
            main_menu();
        }
}

void adminDeleteTrain()
{
  system("CLS");
  cout<<"-------------------------- High Speed Train Reservation System --------------------------------------------------------\n\n";
	cout<<"           <<<<<<<<<<<<<<< Welcome Admin >>>>>>>>>>>>>>>" << endl;
	cout<<endl<<endl;
  string train_id, train_name;
  cout << "1) Delete train only" << endl;
  cout << "2) Delete train along with its customers' information" << endl;
  char choice;
  cin >> choice;
  if (choice == '1')
    {
      viewTrains();
      cout <<endl<< "Enter train ID: ";
      cin.ignore();
      getline(cin, train_id);
      train_name = getTrainName(train_id);
      cout<<"Confirm delete "<<train_id<<" ?(y/n)"<<endl;
      char choice;
      cin>>choice;
      if(choice=='y')
      {
        deleteTrain(train_name, '0');
        cout<<"Train "<<train_id<<" deleted successfully! Press Enter to continue...";
        cin.ignore();
        getchar();
        system("CLS");
        admin_menu();
      }
      else
      {
        cout<<"Train deletion fail! Press Enter to continue...";
        cin.ignore();
        getchar();
        system("CLS");
        admin_menu();
      }
  }
  else if (choice == '2')
    {
      viewTrains();
      cout << endl <<  "Enter train ID: ";
      cin.ignore();
      getline(cin, train_id);
      train_name = getTrainName(train_id);
      cout<<"Confirm delete "<<train_id<<" ?(y/n)"<<endl;
      char choice;
      cin>>choice;
      if(choice=='y')
          {
            deleteTrain(train_name, '1');
            cout<<"Train "<<train_id<<" and it's records are deleted successfully! Press ENTER to continue...";
            cin.ignore();
            getchar();
            system("CLS");
            admin_menu();
          }
      else
          {
            cout<<"Train deletion fail! Press Enter to continue...";
            cin.ignore();
            getchar();
            system("CLS");
            admin_menu();
          }

    }
    else
    {
      cout << "Invalid choice! Please try again! Press ENTER to continue...";
      cin.ignore();
      getchar();
      system("CLS");
      adminDeleteTrain();
    }
}

void adminViewCust()
{
    string train_id, train_name;
    viewTrains();
    cin.ignore();
    cout << endl << "Enter train ID: ";
    getline(cin, train_id);
    train_name = getTrainName(train_id);
    adminViewCustInfo(train_name);
}

//-----------------------------Admin Login Function ----------------------------------
void adminlogin()
{
    string password = "admin12345";
	string input;
	cout << endl << "<< Admin Login >>" <<endl;
	cout<<"Enter Password: ";
    cin.ignore();
    getline(cin, input);
    int attempts = 0;
	while(input != password)
    {
        if (attempts < 3)
        {
            attempts++;
            cout<<"Incorrect password! Please try again! \n";
            getline(cin, input);
        }
        else
        {
            cout << "Too many attempts! " <<endl;
            getchar();
            main_menu();
        }
	}
    cout<<"<< LOGGED IN >>" << endl << "Press ENTER to continue ...";
	getchar();
	system("CLS");
	admin_menu();
}
