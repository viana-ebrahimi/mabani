#include <iostream>
#include <string>
using namespace std;

struct User
{
        string username;
        string password;
        string type;
        float wallet;
};

struct Item
{
        string name;
        double price;
};

struct myAnbarData
{
        const int numberOfPeople = 5;
        User people[5];
        Item *itemsList = nullptr;
        int itemesCount=0;
};

void showUserMenu(const string &inputN , User people[] , int size );
void showAdminMenu(const string &inputN , User people[ ] , int size);
void createUsers(User people[]);
void login(User people[], int size);
void addItem(const string &item, int price);



void addItem(const string &item, int price)
{
        cout << "item : " << item << "price: " << price << "added " << endl;
//        itemesCount++;
        //todo
} 
void removeItem(const string &item, int price){ 
            cout << "item : " << item << "price: " << price << "removed " << endl;
//todo
}
void changePrice(int price , int newPrice){
	cout<< "price" << price << "updated to" <<newPrice << endl;
	//todo
}
 
void wallet( int price , string name , User people[ ] , int size){ 
          for(int i=0 ; i<size ; i++){ 
             if( name == people[i].username  ){ 
                people[i].wallet += price;
			 }
		  } 	cout<< "wallet " << name << price << " increased"  << endl;
		  
	
	       
	       	//todo
}
void showAdminMenu(const string &inputN , User people[ ] , int size)
{
        cout << "\nList of all admin commands:\n";
        cout << "  add        \n";
        cout << "  remove     \n";
        cout << "  rename     \n";
        cout << "  price      \n";
        cout << "  credit     \n";
        cout << "Enter command: " << endl;
        string command;
        cin >> command;
        
        if (command == "add")
        {
                string item;
                cin >> item;
                int price;
                cin >> price;
                addItem(item, price);
        }
        else if (command == "remove")
        {
                string item;
                cin >> item;
                int price;
                cin >> price;
                removeItem(item, price);
        } 
        else if( command == "price"){
              int price; int newPrice;
              cin>>price;
              cin>> newPrice;
              changePrice(price,newPrice);
		} 
		 
		 else if(command == "credit"){ 
		       int increase ; string name;
		       cin >> increase;
		       cin >> name;
		       wallet( increase , name , people , size );
		 }
        else
        {
                cout << "command not found" << endl;
        }
}
void showItem(string name){ 
//            for(int i=0 ; i < size ; i++) {
//               cout << itemeslist[i].name << endl; 
//               
//			   } 
//			  
//			   if( itemeslist[i].name == name){
//			   	cout<< name << ','<< itemesList[i].price;
//			   }
//			} todo
} 
void buyItem( string name ){ 
         //todo
} 
void showBalance( const string &inputN , User people [ ] , int size ){ 
                for(int i=0 ; i< 5 ; i++){ 
                if(inputN == people[i].username ){
                	 
                	  cout << inputN << " youre current balance is:" << people[i].wallet << endl ;
				}
				}
} 

void help( string name){ 
  if(name == "show item"){ 
    cout<< " Show you availible items  and you can search your item ."<<endl;
    
  } 
  else if(name == "buy item"){ 
  cout<< "Can you buy your item"<<endl;
  } 
  else if( name == "balance"){ 
          cout<< " You can see your wallet inventory ."<<endl;
  } 
  else if( name == " help"){ 
  cout<< "To help you. "<<endl;
  } 

}

void showUserMenu( const string &inputN , User people[ ] , int size ){ 
             cout << "\nList of all admin commands:\n";
        cout << "  show item      \n";
        cout << "  buy item     \n";
        cout << "  balance    \n";
        cout << "  help    \n";
    
        cout << "Enter command: " << endl;
        string command;
        cin >> command;
            if(command == "show item"){ 
               string name;
               cin>> name ;
               showItem(name);
} 

else if( command == " buy item") { 
       string name;
       cin>>name;
       buyItem(name);
} 

else if (command == "balance") { 
     showBalance (inputN , people , 5 );
	} 

  
else if ( command == "help") { 
      showUserMenu( inputN , people ,  size);
      string name;
      
    cin>>name;
    help(name);

	}}



void createUsers(User people[])
{
        people[0] = {"ali", "1234", "admin" , };
        people[1] = {"nava", "4321", "admin" ,};
        people[2] = {"user1", "7777", "user" , };
        people[3] = {"user2", "4444", "user" ,  };
        people[4] = {"user3", "5555", "user" , };
}

void login(User people[], int size)
{
        string inputN;
        string inputP;
        string type;
        int s =5;
       
        cout << "Enter your username: " << endl;
        cout << "*If you are admin enter your name, and if you are user enter 'user'*" << endl;
        cin >> inputN;
        cout << "Enter your password:" << endl;
        cin >> inputP;
        bool loggedIn = false;
        for (int i = 0; i < size; i++)
        {
                if (inputN == people[i].username && inputP == people[i].password)
                {
                        loggedIn = true;
                        type = people[i].type;
                        
                        
                        break;
                }
        }
        if (loggedIn)
        {
                cout << "YOU ARE " << type << endl;
                if (type == "admin")
                {
                        showAdminMenu( inputN , people , size);
                }
                else if (type == "user")
                {
                        showUserMenu(inputN , people , size);
                }
        }
        else
        {
                cout << "Failed login" << endl;
        }
}

void startProgram()
{
        const int numberOfUsers = 5;
        myAnbarData anbar;
        createUsers(anbar.people);
        login(anbar.people, numberOfUsers);
}

int main()
{
        startProgram();
        return 0;
}