#include <bits/stdc++.h>
using namespace std;

struct contact
{
	string name, ph, add, email;
};
fstream &operator << (fstream &file, contact &c)
{
	file << c.name << '\n' << c.ph << '\n' << c.add << '\n' << c.email << '\n';
	return file;
}
fstream &operator >> (fstream &file, contact &c)
{
	getline(file, c.name);
	getline(file, c.ph);
	getline(file, c.add);
	getline(file, c.email);
	return file;
}
fstream fio, tio;

void ShowMainMenu()
{
	system("cls");
	cout << "\n\t  | --- YOUR PERSONAL PHONE BOOK! ---- |\n\n";
	cout << "\n\n\t\t\tMAIN MENU";
	cout << "\n\t\t=========================";
	cout << "\n\t\t[1] Add a new Contact";
	cout << "\n\t\t[2] List all Contacts";
	cout << "\n\t\t[3] Search for a Contact";
	cout << "\n\t\t[4] Edit a Contact";
	cout << "\n\t\t[5] Delete a Contact";
	cout << "\n\t\t[0] Exit";
	cout << "\n\t\t=========================";
	cout << "\n\t\tEnter your choice: ";

}
//-------------------------------------------------/

void no_name()
{
	cout << "\n\t\t----------------------------" << flush;
	cout << "\n\t\t Empty Names are not saved! " << flush;
	cout << "\n\t\t----------------------------" << flush;
}

void get(string dis, string &s)
{
	cout << dis << flush;
	getline(cin, s);
}

void get_new_contact(contact &c)
{
	cout << "\n\t\tEnter new Contact details: \n" << endl;
	get("\t\tName: ", c.name);
	if(c.name.size() == 0)
	{
		no_name();
		return;
	}
	get("\t\tPhone No.: ", c.ph);
	get("\t\tAddress: ", c.add);
	get("\t\tEmail: ", c.email);
}

void display(contact &c)
{
	cout << "\n\t\tName:\t  \t" << c.name << "\n\t\tPhone No.:\t" << c.ph << "\n\t\tAddress:\t" << c.add << "\n\t\tEmail:\t \t" << c.email << "\n\t\t==================================\n" << flush;
}

void ending()
{
	cout << "\n\n" << flush;
	system("pause");
}

void add()
{
	fio.open("contacts.dll", ios::app);
	cin.ignore();

	contact c;
	cout << "\n\t\t\tAdd a new Contact\n\n\t\t=================================================\n\n" << flush;
	
	get_new_contact(c);

	if(c.name.size() == 0)
		ending();
	
	else
		fio << c;

	fio.close();
}
//-------------------------------------------------/
void view()
{
	fio.open("contacts.dll", ios::in);
	cout << "\n\t\t\tList of All Contacts\n\t\t==================================" << endl;

	contact c;
	fio >> c;
	while(not fio.eof())
	{
		display(c);
		fio >> c;
	}

	fio.close();
	ending();
}
//-------------------------------------------------/

void find()
{
	fio.open("contacts.dll", ios::in);
	cin.ignore();
	string req;
	get("\n\t\t\tContact Search\n\n\t\t[Name]: ", req);
	cout << "\n\t\t==================================\n" << flush;
	
	int found = 0;
	contact c;
	fio >> c;
	while(not fio.eof())
	{
		if(c.name != req)
		{
			fio >> c;
			continue;
		}
		found = 1;
		display(c);
		fio >> c;
	}
	
	if(not found)
		cout << "No such contact found" << endl;
	
	fio.close();
	ending();
}
//-------------------------------------------------/

void edit()
{
	fio.open("contacts.dll", ios::in);
	tio.open("temp.dat", ios::out);
	cin.ignore();

	string req;	
	get("\n\t\t\tEdit Contact\n\n\t\t[Name]: ", req);
	cout << "\n\t\t==================================\n" << flush;
	
	contact c;
	fio >> c;
	while(not fio.eof())
	{
		if(c.name == req)
		{
			display(c);
			get_new_contact(c);
			if(c.name.size() == 0)
				c.name = req;
		}

		tio << c;
		fio >> c;
	}
	
	fio.close();
	tio.close();

	remove("contacts.dll");
	rename("temp.dat", "contacts.dll");

	ending();
}
//-------------------------------------------------/

void del()
{
	fio.open("contacts.dll", ios::in);
	tio.open("temp.dat", ios::out);
	cin.ignore();

	string req;
	get("\n\t\t\tDelete Contact\n\n\t\t[Name]: ", req);
	cout << "\n\t\t==================================\n\n\t\t\tDeleted Contact: " << endl;
	
	contact c;
	fio >> c;
	while(not fio.eof())
	{
		if(c.name != req)
			tio << c;
		else
			display(c);

		fio >> c;
	}
	fio.close();
	tio.close();

	remove("contacts.dll");
	rename("temp.dat", "contacts.dll");

	ending();
}

int main()
{
	int ch = -1;		// choice
	while(ch != 0)
	{
		ShowMainMenu();
		cin >> ch;

		system("cls");

		if(ch == 1)		//	add new contact
			add();

		else if(ch == 2)	//	list all contacts
			view();
		
		else if(ch == 3)	//	search a contact
			find();

		else if(ch == 4)	// edit a contact
			edit();

		else if(ch == 5)	// delete a contact
			del();
	}
}