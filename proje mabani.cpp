#include <iostream>

using namespace std ;
  
  struct anbar { 
              User people[5];
              
         creatusers ( people ) ;
         
          Item * itemlist = new Item [];
          
  } ;
  
struct User { 
        string name;
        string password;
        string type;
} ;

struct Item { 
       string name ;
       double price ;
       
} ;
 

void adminMenu(){ 
         cout<<"  "
}
void creatusers (User people[]) { 

        people[0] =  { "ali","1234","admin" }  ;
        people[1] =  { "nava","4321","admin" } ;
        people[2] =  { "user","7777","user" }  ;
        people[3] =  { "user", "4444","user" } ;
	    people[4] =  { "user","5555","user" }  ;
  
}

void login ( User people[] , int size ) { 
	
 

             string inputN ;
             string inputP ;
             string type ;
  
     cout<< " enter your name: " <<endl<< " *if you are admin enter youre name , and if you are user enter user * " <<endl ;
      cin>> inputN ;
     cout<< " enter youre password:"<<endl ;
      cin>> inputP ;
     
              bool login = false ;
     for ( int i=0 ; i<5 ; i++ ){ 
         if ( inputN == people[i].name && inputP == people[i].password ) { 
            login = true ;
            type = people[i].type ;
           break;
            
		 }
	 } 
	 
	     if (login == true ) { 
        	cout<<" YOU ARE "<< type << endl; 
        	
        	if (type == "admin"){ 
        	   adminMenu();
        	    
			}
	
	 } 
	     else { 
	       cout<<" Failed login" << endl;
	 }
   
} 
void menu () { 
        int choice ;
        cout<< " welcome !  to login press 1 ,  to exit press other key . " <<endl;
         cin>> choice;
     
       if (choice == 1) {  
         login ( people , 5) ;
         
	 } 
	   else { 
	      cout<<"goodbye!"<<endl;
	 }
} 
 

int main () { 
        
         menu();
         
       

}

