#include<iostream>
#include<map>
#include<string>
#include<Windows.h>
#include <conio.h>
#include <cstdlib>
#include <vector>
#include <fstream>
#define manager "project"
#define Manager "PROJECT"
#define Password "20162017"
using namespace std;
struct product
{
	string name;
	double price;
	int quantity;
	float discount;
};
struct customer
{
	int id;
	string password;
	float money;
};
vector<customer> v;
float client_money;
void load_file(map<int, product>&m)
{
	ifstream load("ds_project.txt", ios::in);

	int id;
	product s;
	while (load)
	{
		load >> id;
		load.ignore();
		getline(load, s.name);
		load >> s.price;
		load >> s.discount;
		load >> s.quantity;
		m[id] = s;
	}

}
void login(map<int, product>m)
{
	int id;
	string pass;
	load_customer();
	system("cls");
	cout << "please enter your ID : ";
	cin >> id;
	cout << "please Enter your password : ";
	cin >> pass;

	vector<customer>::iterator i;
	for (i = v.begin(); i != v.end(); i++)
	{
		if ((i->id == id) && (i->password == pass))
		{
			client_money = i->money;
			customer_option(m);
			i->money = client_money;
			break;
		}
	}
	remove("customer_accounts.txt");
	save_customer();
}
void customer_option(map<int, product>m)
{
	system("cls");
	map<int, pair<int, product>>q;//to view all prodect list
	char xs;
	char x;
	map<int, product>::iterator it;
	cout << "==================================================================================================" << endl;
	cout << "P.No\t\tName  \t\t\t  Price  \t\tdiscount\t\tquantitiy " << endl;
	cout << "==================================================================================================" << endl;
	for (it = m.begin(); it != m.end(); it++)
	{
		cout << it->first << "\t\t";
		cout << it->second.name;
		for (int i = 0; i < (26 - it->second.name.size()); i++)
		{   cout << " ";	}
		cout << it->second.price << "  \t \t\t" << it->second.discount << "   \t\t\t" << it->second.quantity << endl;
	}
	map<int, product>::iterator g;//
	int Quantity ,id;
	do
	{
		cout << "please enter the Product number : ";
		cin >> id;
		g = m.find(id);
		cout << "please enter the Quantity : ";
		cin >> Quantity;
		while (Quantity > (g->second.quantity))
		   {
			      cout << "\nSorry Sir that number of products Are invaled Please Enter another Quantity \n\n";
			    cout << "New Quantity : ";
			   cin >> Quantity;
		      	if (Quantity <= (g->second.quantity))
			   {
		 		break;
			   }
		   }
		product nw;
		nw.name = g->second.name;
		nw.price = g->second.price;
		nw.discount = g->second.discount;
		nw.quantity = g->second.quantity;
		q[id] = make_pair(Quantity, nw);// kda ana b2ool en el prduct dah leeh el quantity deeh we el byanat el product el gdeed 
		cout << "\n\nDo You Want To Add Any Thing Else(y/n) : ";
		cin >> xs;
	} while (xs != 'n');
	cout << "\n\nDo you want to Delete any product sir ? (y/n) : ";
	cin >> x;
	if ((x == 'y') || (x == 'Y'))
	{
		remove_product(q);
	}
	cout << "\n\nDo you want to Modify any Product Sir ? (y/n) : ";
	cin >> x;
	if ((x == 'y') || (x == 'Y'))
	{
		//modify_product(q);
	}
	print_invoice(q);
}
void print_invoice(map<int, pair <int, product>>&p)
{
	map<int, pair <int, product > >::iterator it;
	float total = 0 , price_each_item ,final_price;
	cout << "*********************************INVOICE*********************************" << endl << endl;
	cout << "ID" << "\t\t" << "NAME" << "\t\t" << "QUANTITY" << "\t\t" << "DISCOUNT" << "t\t" << "FINAL_PRICE" << endl << endl;
	  for (it = p.begin(); it != p.end(); it++)
	{
		cout << it->first << "\t\t";
		cout << it->second.second.name << "\t\t";
		cout << it->second.first << "\t\t\t";	
		cout << it->second.second.discount << "\t\t\t";
		cout << it->second.second.price << endl;
	}
	for (it = p.begin(); it != p.end(); it++)
	{
		price_each_item = (it->second.second.price  * it->second.second.discount / 100) *it->second.first;//to clculata descount
		final_price = ((it->second.second.price)*(it->second.first)) - price_each_item;
		total += final_price;
	}
	cout << "\n\nThe Total Price is : " << total << endl;
	client_money =client_money-total;
	cout << "That price has been deduced from your account and your money now is : ";
	cout << client_money << endl << endl;
	Sleep(10000);
}
void load_customer()
{
	v.clear();
	customer x;
	string l;
	ifstream load("customer_accounts.txt", ios::in);

	while (load)
	{
		load >> x.id;
		load.ignore();
		load >> x.password;
		load >> x.money;
		v.push_back(x);
		load >> l;
	}

}
void save_customer()
{
	vector<customer>::iterator it;
	ofstream save("customer_accounts.txt", ios::out);
	string l = "---------------";
	for (it = v.begin(); it < v.end()-1;it++)
	{
		save << it->id << endl;
		save << it->password << endl;
		save << it->money << endl;
		save << l<<endl;
	}
}
void save_file(map<int, product>m)
{
	ofstream save("ds_project.txt", ios::out);
	map<int, product>::iterator it;
	for (it = m.begin(); it != m.end(); it++)
	{
		save << it->first << endl;
		save << it->second.name << endl;
		save << it->second.price << endl;
		save << it->second.discount << endl;
		save << it->second.quantity << endl;
	}
}
void addproduct(map<int,product> &m)
{
	system("cls");
	char y = 'y';
	do
	{
		system("cls");
		int id;
		product x;
		cout << "enter the id of the product :" << endl;
		cin >> id;
		cout << "enter the name of the product :" << endl;
		cin >> x.name;
		cout << "enter the price :" << endl;
		cin >> x.price;
		cout << "enter the discount :" << endl;
		cin >> x.discount;
		cout << "enter the quntity :" << endl;
		cin >> x.quantity;
		m[id] = x;// 3shan a5ly el id dah ysawy el product bta3y 3la tool
		cout << "DO YOU WANT CREATE ANY NEW PRODUCT ??" << endl;
		cin >> y;

	} while (y != 'n');
}
void query(map<int ,product>m)
{
	system("cls");
	char ch;
	map <int, product > ::iterator it;
	map <int, product > ::iterator index;
	int   count = 0,search_id;
	cout << "please enter the id to view \n";
	cin >> search_id;
	if (!m.empty())
	{
		for (it = m.begin(); it != m.end(); it++)
	 {  
		     	if (search_id == it->first)
			  {
				index = it;
				count++;
				break;
			 }
	 }
		if (count > 0)
		{
			cout << index->second.name << "\t" << index->second.price << "\t" << index->second.quantity << "\t" << index->second.discount << endl;
			Sleep(5000);
		}
		else
		{
			cout << "SoRRY THIS IS NOT FOUND DO YOU WANT TO SEARCH ABOUT ANOTHER ONE (y-n) !!? \n";
			Sleep(3000);
			cin >> ch;
			if ((ch == 'y') || (ch == 'Y'))
			{
				query(m);
			}
			else
				return;
		}

	}
	else
	{
		cout << "SORRY , UNFORTINATLY YOUR MAP IS EMPTY !! :'( \n";
	}
}
void view(map<int, product>m)
{
	system("cls");
	map<int, product>::iterator it;
	for (it = m.begin(); it != m.end(); it++)
	{
		cout<<"ID : "<< it->first << endl;
		cout <<"Name : "<<it->second.name << endl;
		cout <<"Price : "<< it->second.price << endl;
		cout <<"Quantity : "<<it->second.quantity << endl;
		cout <<"Discount : "<<it->second.discount << endl;
		Sleep(3000);
		cout << "--------------\n";
	}
}
void modify(map<int, product> &m)
{
	system("cls");
	map<int, product>::iterator it;
	cout << "which product you want to modfiy" << endl;
	int newID;
	cin >> newID;
	it = m.find(newID);
	if (it != m.end())
	{
		cout <<"ID : "<<it->first << endl;
		cout << "name : " <<it->second.name<< endl;
		cout << "price : " << it->second.price << endl;
		cout << "discount : " << it->second.discount << endl;
		cout << "quantity : " << it->second.quantity << endl;
		char character;
		do
		{
			cout << "  which thing do you want to modifiy if you want to change :   " << endl;
			cout << " - Name of product press 1 " << endl;
			cout << " - Price of product press 2 " << endl;
			cout << " - quantity of product press 3 " << endl;
			cout << " - discount of product press 4 " << endl;
			cout << " - if you won't change any thing press 5" << endl;
			int change_num;
			cin >> change_num;
			string newname;
			double newnum;
			if (change_num == 1)
			{
				cin >> newname;
				it->second.name = newname;
			}

			else if (change_num == 2)
			{
				cin >> newnum;
				it->second.price = newnum;
			}
			else if (change_num == 3)
			{
				cin >> newnum;
				it->second.quantity = newnum;
			}

			else if (change_num == 4)
			{
				cin >> newnum;
				it->second.discount = newnum;
			}
			else if (change_num == 5)
				break;
			else
				continue;
			cout << "do you to modify any thing else <n/y>" << endl;
			cin >> character;
		} while (character == 'y' || character == 'Y');

	}
}
void delete_product(map<int, product>&m)
{
	system("cls");
	int id;
	cout << "please enter the id of the product you want to delete : ";
	cin >> id;
	m.erase(m.find(id));
}
void admin_option(map<int, product>&m)
{
	system("cls");
	int c;
	do{
		system("cls");
		cout << "press 1 to Add product\n\n";
		cout << "press 2 to query product\n\n";
		cout << "press 3 to view product\n\n";
		cout << "press 4 to modify data\n\n";
		cout << "press 5 to delete data\n\n";
		cout << "press 6 to EXIT\n\n";
		cin >> c;
		switch (c)
		{
		case 1:
			addproduct(m);
			break;
		case 2:
			query(m);
			break;
		case 3:
			view(m);
			break;
		case 4:
			modify(m);
			break;
		case 5:
			delete_product(m);
			break;
		default:
			if (c == 6){ break; }
			else
			{
				cout << "please enter another number !!\n";
				Sleep(3000);
			}
		}
	} while (c != 6);

}
void password(map<int, product>&m)
{
	string password, username;//password that the user enter , user name that the user enter .
	char c = ' ';
	system("cls");
	cin.ignore();
	cout << "\n ENTER YOUR NAME PLEASE :";
	getline(cin, username);
	cout << " \nPlease Enter your PassWord : ";
	while (true)
	{
		c = _getch();// that used to make the user enter a number without be seen in the screen.
		if (isalpha(c) || isdigit(c))  //we use here ( isalpha() ) & ( isdigit() ) to make shore that the input in the password will be only a number or letter .
		{
			password += c; cout << "*";
		}
		else if (c == '\b' && !password.empty())
		{
			cout << "\b \b";
			password.pop_back();
		}
		else if (c == '\r'){ break; }
	}
	if (((password == Password) && (username == manager)) || ((password == Password) && (username == Manager)))
	{
		cout << "\n\n\t\t Welcome TO OUR PROJECT   !!";
		Sleep(1200);
		admin_option(m);
	}
	else
	{
		cout << "\a \n\n \t\t !! YOU ARE NOT THE ADMIN !! ";

	}
}
void view_my_cart(map<int, pair <int, product>>&p)
{
	cout << "\n\n\t\tHello this your cart  " << endl;
	map<int, pair <int, product > >::iterator it;
	cout << "ID" << "   " << "quantity" << "   " << "name " << "  " << "discout " << "  " << "price " << endl;
	cout << "==================================================================================================" << endl;
	for (it = p.begin(); it != p.end(); it++)
	{
		cout << it->first << "  ";
		cout << it->second.first;
		cout << "   ";
		cout << it->second.second.name << "  ";
		cout << it->second.second.discount << "  ";
		cout << it->second.second.price << endl;
	}
}

void remove_product(map<int, pair<int, product>>&ma)
{
	char c;
	int removeid;
	do{

		view_my_cart(ma);
		cout << "\n\nPlease enter the ID of the product You Want To Delete : ";
		cin >> removeid;
		ma.erase(ma.find(removeid));
		cout << "\n\nDo you want to remove any thing else ? (y/n)  : ";
		cin >> c;
	} while (c!='n');
}


int main()
{

	int x;
	map <int, product> m;

	load_file(m);

	do
	{
		system("cls");
		cout << "/ Main Menu\n\n";
		cout << "1. Customer\n\n";
		cout << "2.Manager\n\n";
		cout << "3.Exit\n\n ";
		cout << "please enter your option : " << endl;
		cin >> x;
		switch (x)
		{
		case 1: 
			login(m);//customer
			break;
		case 2:
			password(m);//manager
			break;
		case 3:
			break;
		default:
			cout << "That is an invaled input please enter an valed input .\n\n";
			continue;
		}
	}
	while (x != 3);
	remove("ds_project.txt");
	save_file(m);

	return 0;

}