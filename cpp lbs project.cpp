#include<iostream>
#include<string.h>
#include<fstream>
#include<conio.h>
#include<stdlib.h>
using namespace std;
class Book{
	int bookid;
	float price;
	char title[20];
	public:
		Book(){
			bookid=0;
			price=0;
			strcpy(title,"No Title");
		}
		void getBookData(){
			cout<<"Give Book Id, Its price, & its Title :"<<endl;
			cin>>bookid>>price;
			cin.ignore();
			cin.getline(title,20);
			
		}
		void showdata(){
			cout<<"Book Description "<<endl;
			cout<<"Its Title: "<<title<<endl;
			cout<<"Book Id: "<<bookid<<endl;
			cout<<"Its price: "<<price<<endl;
			cout<<endl;
		}
		int storebook();
		void viewAllBook();
		void searchBook(char*);
		void deleteBook(char*); 
		void updateBook(char*); 
	
};
void Book::updateBook(char *x)
{    // We use fstream  cause' we want to read and write both operation
	fstream file;
	file.open("Mcknight.txt",ios::in|ios::out|ios::ate|ios::binary);
	file.seekg(0); 
	file.read((char*)this,sizeof(*this));
	while(!file.eof())
	{
		if(!strcmp(title,x)){
			getBookData();
			file.seekp(file.tellp()-sizeof(*this));
			file.write((char*)this,sizeof(*this));
		}
		file.read((char*)this,sizeof(*this));
	}
	file.close(); 	
}
void Book::deleteBook(char *x)
{
	ifstream fin;
	ofstream fout;
	fin.open("Mcknight.txt",ios::in|ios::binary);
	if(!fin){
	cout<<"File not Found"<<endl;
	return ;	
	}
	
	fout.open("Temp_Mcknight.txt",ios::out|ios::binary);
	fin.read((char*)this,sizeof(*this));
	while(!fin.eof()){
		if(strcmp(title,x))
		fout.write((char*)this,sizeof(*this));
		fin.read((char*)this,sizeof(*this)); 
	}
	
	fin.close();
	fout.close();

	remove("Mcknight.txt");
	
	rename("Temp_Mcknight.txt","Mcknight.txt");
}
void Book::searchBook(char* x){
	int p=0;
	ifstream Saurav;
	Saurav.open("Mcknight.txt",ios::in|ios::binary);
	if(!Saurav){
	cout<<"File not Found"<<endl;
	return ;	
	}
	Saurav.read((char*)this,sizeof(*this));
	while(!Saurav.eof()){
		if(!strcmp(x,title))
		{
		showdata(); p++;}
		Saurav.read((char*)this,sizeof(*this));
	}
	cout<<"The total no. of found element is: "<<p<<endl;
	Saurav.close();
}
int Book::storebook(){
	if(bookid==0&&price==0){
	
	cout<<"Book Data not initilize"<<endl;
	return 0;
	}
	else{
	
	ofstream Saurav;
	Saurav.open("Mcknight.txt",ios::out|ios::app|ios::binary);
	Saurav.write((char*)this,sizeof(*this));// *this means object
	Saurav.close();
	return 1;
    }
}
void Book::viewAllBook(){
	
	ifstream Saurav;
	Saurav.open("Mcknight.txt",ios::in|ios::binary);
	// In below function Mcknight calls its not function , as file is not found it returns 1;
	if(!Saurav){
	cout<<"File not Found"<<endl;
	return ;	 
	} 
	Saurav.read((char*)this,sizeof(*this));
	while(!Saurav.eof()){
		showdata();
		Saurav.read((char*)this,sizeof(*this));
	}
	Saurav.close();
}
int menu(){
	int choice;
	cout<<"Libraray Management System"<<endl<<endl;
	cout<<"______________________________________________________"<<endl;
	cout<<"1. Add a Book"<<endl;
	cout<<"2. Remove a Book"<<endl;
	cout<<"3. Search a Book"<<endl;
	cout<<"4. Print all Books"<<endl;
	cout<<"5. Update the description of the Book"<<endl;
	cout<<"6. For Exit"<<endl;
	cout<<endl<<"Enter Your choice: ";
	cin>>choice;
	return choice;
}	
	

int main()
{
	
	Book my_library;
	while(5){int x=menu();
	system("cls");
		switch(x)
		{
			
			case 1:
				cout<<"Give Book Decription:"<<endl;
				my_library.getBookData();
				my_library.storebook();
				break;
			case 2:
			{
			cout<<"Type Title of that book which you want to delete:";
			    
				char alpha[50];
				cin>>ws;
			    gets(alpha);
			    my_library.deleteBook(alpha);
			    break;
			}
			case 3: cout<<"Type Title of that book which you want to search:";
			    {
				char alpha[50];cin>>ws;
			    gets(alpha);
			    my_library.searchBook(alpha);
			    break;
			   }
			case 4: cout<<"All Books Descriptions"<<endl;
			    my_library.viewAllBook();
			    break;
			case 5: cout<<"Type Title of that book which you want to update:";
			   {
				 char alpha[50];cin>>ws;
			    gets(alpha);
			    my_library.updateBook(alpha);
			    break;}
			case 6: break;
			default: break;
			    
		}
		getch();
		system("cls");
		if(x<1||x>=6)
		break;
	}
	return 0;
}





