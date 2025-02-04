#include <iostream>
#include <string>
using namespace std;

struct User
{
        string username;
        string password;
        string type;
       string wallet;
       string list;
};

struct Item
{
        string name;
        string price;
};

struct myAnbarData
{
        const int numberOfPeople = 5;
        User people[5];
        Item *itemsList = nullptr;
        int itemsCount = 0 ;
        
}; 




void showUserMenu(const string &inputN , User people[] , int size );
void showAdminMenu(const string &inputN , User people[ ] , int size);
void createUsers(User people[]);
void initializeItems(myAnbarData &anbar);
void login(User people[], int size);
void addItem(const string &item, int price);




void initializeItems ( myAnbarData & data ){ 

                  data.itemsCount=4;
                  data.itemsList = new Item[data.itemsCount];
                  
                   data.itemsList[0]= { " apple" , "50000"} ;
                   data.itemsList[1]= {"lemon" ,"60000"} ;
                   data.itemsList[2]= {" banana" , "100000"} ;
                   data.itemsList[3]= { "orange" , "80000"} ;
                   
}



void deleteItems(myAnbarData &data) {
    delete[] data.itemsList; 
     data.itemsList = nullptr;
     data.itemsCount=0;
    
    
}

void addItem(  const string &item ,const string & price , myAnbarData & data )
{        

          Item *newItemsList = new Item[data.itemsCount + 1] ;
          
            for(int i=0 ; i < data.itemsCount ; i++){ 
            
                newItemsList [i] = data.itemsList[i];
			}
             newItemsList[data.itemsCount] = {item, price};
             
    delete[] data.itemsList;
    
    data.itemsList = newItemsList;
    
    data.itemsCount++;
    
    cout << "item " << item << " added successfully." << endl;

    
}


 

Item removeItem(const string &item, myAnbarData & data){ 
    Item dlt;
    
    int index = -1;
    for (int i = 0; i < data.itemsCount; i++)
    {
        if (data.itemsList[i].name == item)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        cout << "Item " << item << " not found." << endl;
       
    } 
    else{ 
    
     dlt = data.itemsList[index];
    	
    Item *newItemsList = new Item[data.itemsCount - 1];
    
    for (int i = 0, j = 0; i < data.itemsCount; i++)
    {
        if (i != index)
        {
            newItemsList[j] = data.itemsList[i];
            j++;
        }
    }
    
    delete[] data.itemsList;
    data.itemsList = newItemsList;
    data.itemsCount--;
    cout << "item " << item << " removed successfully." << endl;
	}
	int choice;
	
	cout<< " Press 1 if you want to return the product :" << endl ;
	
	   cin >> choice;
	   
	if( choice == 1){ 
	
	  return( dlt );
  
  
  
  } 


void return( const Item & dlt , MyAnbarData & data){ 
          
            Item* newItemsList = new Item[data.itemsCount + 1];

    for (int i = 0; i < data.itemsCount; i++) {
        newItemsList[i] = data.itemsList[i];
    }

    newItemsList[data.itemsCount] = dlt ;
    
    data.itemsCount++;

    delete[] data.itemsList;
    data.itemsList = newItemsList;

    cout << "Product " << dlt << " restored successfully!" << endl;
          
 }     
 
 
       void rename( const string &name , myAnbarData &data){
	          for(int i=0 ; i< size ; i++){ 
	             if(data.itemsList[i] == name){ 
	               data.itemsList[i].name = name;
				 }
			  } 
             cout << " name updated !"<<endl;
	   } 


void changePrice( myAnbarData &data , string newPrice , const string  &name ){ 
for(int i=0 ; i< size ; i++){ 
    if(data.itemsList[i].name == name){
    	data.itemsList[i].price = newPrice ;
    	
	} 
}
          
	cout<< "price" << price << "updated to" <<newPrice << endl;
	
} 





 
void credit ( int price , string name , User people[ ] , int size ){ 
          for ( int i=0 ; i<size ; i++ ) { 
             if ( name == people[i].username ) { 
                people[i].wallet += price ;
			 }
		  } 	cout << " wallet " << name << price << " increased "  << endl ;

} 







void showAdminMenu(const string &inputN , User people[ ] , int size , myAnbarData &data  )
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
                
                removeItem ( item );
        } 
        else if (command == "rename "){ 
               string name;
               cin>>name ;
               rename(name , myAnbarData &data )
		}
        
        else if( command == "price"){
               string newPrice;
              cin>> newPrice;
              string name;
              cin >> name; 
              changePrice( myAnbarData &data ,newPrice ,name);
		} 
		 
		 else if(command == "credit"){ 
		       int increase ; string name;
		       cin >> increase;
		       cin >> name;
		       credit( increase , name , people , size );
		 }
        else
        {
                cout << "command not found" << endl;
        }
}




void showItem(myAnbarData &data ){ 
            for(int i=0 ; i< size ; i++){
            	cout<< data.itemsList[i];
			} 
			cout<< " What are you looking for?" <<endl
            string name;
              cin >> name;
              for(int i=0 ; i< size ; i++){
              	 if(data.itemsList[i].name == name){ 
              	    cout<< data.itemsList[i].name <<','<<data.itemsList[i].price <<endl ;
				   }
			  }

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
             
               showItem(myAnbarData &data);
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