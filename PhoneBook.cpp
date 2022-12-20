#include <bits/stdc++.h>
using namespace std;

//-----------------------CONTACT OPERATIONS----------------------------------------------------

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
fstream fio;
int changes = 0;
void message(string s);
//--------------------------------MAIN MENU--------------------------------------------
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
	if(changes > 0)
		cout << "\n\t\t[6] Save Changes(Not saved yet!)";
	cout << "\n\t\t[0] Exit";
	cout << "\n\t\t=========================";
	cout << "\n\t\tEnter your choice: ";

}
//----------------------------SMALL FUNCTIONS & MESSAGES-------------------------------/

void message(string s)					//	display simple message
{
	string se(s.size(), '-');
	cout << "\n\t\t" << se << flush;
	cout << "\n\t\t" << s << flush;
	cout << "\n\t\t" << se << flush;
}

void get(string dis, string &s)			//	get line input with displayed instruction
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
		message(" Empty Names are not saved! ");
		return;
	}
	get("\t\tPhone No.: ", c.ph);
	get("\t\tAddress: ", c.add);
	get("\t\tEmail: ", c.email);
}

void display(contact &c)			//	display contact
{
	cout << "\n\t\tName:\t  \t" << c.name << "\n\t\tPhone No.:\t" << c.ph << "\n\t\tAddress:\t" << c.add << "\n\t\tEmail:\t \t" << c.email << "\n\t\t=======================================\n" << flush;
}

void ending()					//	consious ending 
{
	cout << "\n\n" << flush;
	system("pause");
}

//-----------------------------------TRIE-DATA-STUCTURE---------------------------------------------

struct node
{
	char data = '?';	
	contact c;

	map < char, node * > v;
	bool end = false;

	node(){}
	node(char val)
	{
		data = val;
	}
};

struct TRIE
{
	node root;
	int cnt = 0;
	
	bool insert(contact &c)
	{
		node *cur = &root;
		for(int i = 0; i < c.name.size(); i++)
		{
			if(cur->v[c.name[i]] == NULL)
				cur->v[c.name[i]] = new node(c.name[i]);

			cur = cur->v[c.name[i]];
		}
		if(cur->end == true)			//	--> it already existed
			return false;

		cur->c = c;
		cur->end = true;

		cnt++;
		return true;
	}
	//								/----------------------------------/

	void list_all(string name, node *cur, void (*func)(contact &c))
	{
		if(cur->end == true)
		{
			func(cur->c);
			// display(cur->c);
		}

		for(auto next : cur->v)
			if(next.second != NULL)
				list_all(name + cur->data, next.second, func);

		return;
	}
	//								/----------------------------------/

	int search(string &s, int exact = 0)	//	by default = prefix search
	{
		node *cur = &root;
		int n = s.length();
		int found = 0;
		for(int i = 0; i < n; i++)
		{
			if(cur->v[s[i]] != NULL)
				cur = cur->v[s[i]];
			else
				return false;
		}
		//	some prefix is found
		found = 1;

		if((cur->end == true) && exact == 1)
		{
			display(cur->c);
			found = 2;				//	exact name is found
		}
		if(not exact)
			list_all(s, cur, display);

		return found;
	}
	//								/----------------------------------/

	void del(string &s)
	{
		node *cur = &root;
		node *st = &root;
		int pf = 0;
		for(int i = 0; i < s.size(); i++)
		{
			if(cur->v[s[i]] == NULL)
				return;

			if(cur->end == true)
				pf = i + 1, st = cur->v[s[i]];
			
			cur = cur->v[s[i]];
		}

		//	remove contact also
		cur->end = false;
		cur->c.name = "";
		cur->c.ph = "";
		cur->c.add = "";
		cur->c.email = "";
		cnt--;

		for(auto next : cur->v)
			if(next.second != NULL)
				return;

		while(pf < s.size())
		{
			node *t = st;
			st = st->v[pf++];
			delete t;
		}
		delete st;
	}

} trie;

//--------------------------------------USER OPERATIONS---------------------------/
void add()
{
	cin.ignore();
	cout << "\n\t\t\tAdd a new Contact\n\n\t\t==================================\n\n" << flush;
	
	contact c;
	get_new_contact(c);

	if(c.name.size() != 0)
	{
		if(trie.insert(c))
			message(" Added to Buffer! "), changes++;
		else
			message(" Name already exists, try different Name ");
	}
	ending();
}
//-------------------------------------------------/
void view()
{
	cout << "\n\t\t\tList of All Contacts[" << trie.cnt << "]\n\t\t=======================================" << endl;
	trie.list_all("", &trie.root, &display);
	ending();
}
//-------------------------------------------------/
void find()
{
	cin.ignore();
	string req;
	get("\n\t\t\tContact Search\n\n\t\t[Name]: ", req);
	cout << "\n\t\t=======================================\n" << flush;
	
	int found = trie.search(req);
	if(found == 0)
		message(" No such contact found ");
	
	ending();
}
//-------------------------------------------------/

void edit()
{
	cin.ignore();
	string req;	
	get("\n\t\t\tEdit Contact\n\n\t\t[Name]: ", req);
	cout << "\n\t\t=======================================\n" << flush;
	
	contact c;
	if(trie.search(req, 1) == 2)
	{
		get_new_contact(c);

		if(c.name.size() == 0)
			;
		else if(c.name == req)
		{
			trie.del(req);
			trie.insert(c);
			message(" Edited in Buffer "), changes++;
		}
		else
		{
			if(trie.insert(c))
			{
				trie.del(req);
				message(" Edited in Buffer "), changes++;
			}
			else
				message(" Name already exists, try different Name ");
		}
	}
	else
		message(" No such contact found ");

	ending();
}
//-------------------------------------------------/

void del()
{
	cin.ignore();

	string req;
	get("\n\t\t\tDelete Contact\n\n\t\t[Name]: ", req);
	cout << "\n\t\t=======================================\n\n\t\t\tContact to be Deleted: " << endl;
	
	if(trie.search(req, 1) == 2)
	{
		string ch = "n";
		cout << "\n\t\tPress y to confirm: " << flush;
		cin >> ch;
		if(ch == "Y" or ch == "y")
		{
			trie.del(req);
			message(" Deleted from Buffer "), changes++;
		}
	}
	else
		cout << "\n\t\t\tNOT FOUND!!" << flush;

	ending();
}
//--------------------------------------------------------------------

void load()
{
	fio.open("contacts.dll", ios::in);
	
	contact c;
	fio >> c;

	while(not fio.eof())
	{
		trie.insert(c);
		fio >> c;
	}
	fio.close();
}
//								/----------------------------------/
void unload()
{
	fio.open("contacts.dll", ios::out|ios::trunc);

	trie.list_all("", &trie.root, [](contact &c){fio << c;});
	
	fio.close();
}
//								/----------------------------------/
void reload()
{
	unload();
	message(" Saved Successfully! ");
	ending();
	load();
	changes = 0;
}

//--------------------------------------------------------------------

int32_t main()
{
	string ch = "X";		// choice
	load();
	while(ch != "0")
	{
		ShowMainMenu();
		cin >> ch;

		system("cls");

		if(ch == "1")		//	add new contact
			add();

		else if(ch == "2")	//	list all contacts
			view();
		
		else if(ch == "3")	//	search a contact
			find();

		else if(ch == "4")	// edit a contact
			edit();

		else if(ch == "5")	// delete a contact
			del();

		else if(ch == "6")	//	save all changes
			reload();
	}
	unload();
}