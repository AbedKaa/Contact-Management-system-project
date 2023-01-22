#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <fstream>

using namespace std;

class contact {
private:
	char fname[20], lname[20], address[50], email[20];
	long long phNo;

public:
	void createContact();
	void showcontact();
	void writeonfile();
	void readfromfile();
	void searchonfile();
	void deletfromfile();
	void editcontact();
};

void contact::createContact() {
	cout << "\nEnter your First Name:" << endl;
	cin.ignore();
	cin.getline(fname, 20);

	cout << "\nEnter Your Last Name:" << endl;

	cin.getline(lname, 20);

	cout << "\nEnter Your Phone Number:" << endl;
	cin.ignore();
	cin >> phNo;

	cout << "\nEnter Your Address:" << endl;
	cin.ignore();
	cin.getline(address, 50);

	cout << "\nEnter Your Email:" << endl;
	cin.ignore();
	cin.getline(email, 20);

}

void contact::showcontact() {
	cout << "\nYour First Name:" << fname << endl;
	cout << "\nYour Last Name:" << lname << endl;
	cout << "\nYour Phone Number:" << phNo << endl;
	cout << "\nYour Address:" << address << endl;
	cout << "\nYour Email:" << email << endl;
}

void contact::writeonfile() {
	char ch;
	ofstream f1;
	f1.open("CMS.txt", ios::binary | ios::app);

	do {
		createContact();
		f1.write(reinterpret_cast<char*>(this), sizeof(*this));
		cout << "\nDo You Have Next Data?(Y/N)" << endl;
		cin >> ch;
	} while ((ch == 'y') || (ch == 'Y'));
	cout << "Contact Has Been Sucessfullt Created...";
	f1.close();
}

void contact::readfromfile() {
	ifstream f2;
	f2.open("CMS.txt", ios::binary);

	cout << "\n=============================================================================\n";
	cout << "\n============================== LIST OF CONTACT ==============================\n";
	cout << "\n=============================================================================\n";

	while (!f2.eof()) {
		if (f2.read(reinterpret_cast<char*>(this), sizeof(*this))) {
			showcontact();
			cout << "\n=============================================================================\n";
		}
	}
	f2.close();
}

void contact::searchonfile() {
	ifstream f3;
	long long phone;
	cout << "Enter Pone no.";
	cin >> phone;
	f3.open("CMS.txt", ios::binary);

	while (!f3.eof()) {
		if (f3.read(reinterpret_cast<char*>(this), sizeof(*this))) {
			if (phone == phNo) {
				showcontact();
				return;
			}
		}
	}
	cout << "\n\nNo Record Found";
	f3.close();
}

void contact::deletfromfile() {
	long long phone;
	int flag = 0;
	ofstream f4;
	ifstream f5;

	f5.open("CMS.txt", ios::binary);
	f4.open("temp.txt", ios::binary);

	cout << "\nEnter Phone No. To Delete:: " << endl;
	cin >> phone;

	while (!f5.eof()) {
		if (f5.read(reinterpret_cast<char*>(this), sizeof(*this))) {
			if (phNo != phone) {
				f4.write(reinterpret_cast<char*>(this), sizeof(*this));
			}
			else
				flag = 1;
		}
	}
	f5.close();
	f4.close();
	remove("CMS.txt");
	rename("temp.txt", "CMS.txt");

	flag == 1 ?
		cout << "\tContact Deleted..." :
		cout << "\tContact Not Found...";
}

void contact::editcontact() {
	long long phone;
	fstream f6;

	cout << "Edit contact:";
	cout << "\n=============================================================================\n";
	cout << "\nEnter the phone number to be edit:";
	cin >> phone;

	f6.open("CMS.txt", ios::binary | ios::out | ios::in);

	while (!f6.eof()) {
		if (f6.read(reinterpret_cast<char*>(this), sizeof(*this))) {
			if (phone == phNo) {
				cout << "Enter new record\n";
				createContact();

				int pos = -1 * sizeof(*this);
				f6.seekp(pos, ios::cur);
				f6.write(reinterpret_cast<char*>(this), sizeof(*this));
				cout << endl << endl << "\tContact Successfully Updated...";
				return;
			}
		}
	}
	cout << "\nNo Record Found!";
	f6.close();
}

int main() {
	system("cls");
	system("Color 04");

	cout << "\n\n\n\n\n\n\n\n\n\n\t\t * WELCOME TO THE CONTACT MANAGMENT SYSTEM *";
	_getch();

	while (1) {
		contact c1;
		int choice;

		system("cls");
		system("Color 04");

		cout << "\nCONTACT MANAGMENT SYSTEM";
		cout << "\n\nMAIN MENU";
		cout << "\n=============================================================================\n";
		cout << "[1] Add A New Contact\n";
		cout << "[2] List All Contact\n";
		cout << "[3] Search For Contact\n";
		cout << "[4] Delete A Contact\n";
		cout << "[5] Edit A Contact\n";
		cout << "[0] Exit";
		cout << "\n=============================================================================\n";
		cout << "Enter Your Choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			system("cls");
			c1.writeonfile();
			break;
		case 2:
			system("cls");
			c1.readfromfile();
			break;
		case 3:
			system("cls");
			c1.searchonfile();
			break;
		case 4:
			system("cls");
			c1.deletfromfile();
			break;
		case 5:
			system("cls");
			c1.editcontact();
			break;
		case 0:
			system("cls");
			cout << "\n\n\n\t\t\t***Thank You For Using CMS.***" << endl << endl;
			exit(0);
			break;
		default:
			continue;
		}
		int opt;
		cout << "\n\n..::Enter The Choice:\n[1] MAIN MENU\t\t[0] Exit\n";
		cin >> opt;

		switch (opt)
		{
		case 0:
			system("cls");
			cout << "\n\n\n\t\t\tThank You For Using CMS." << endl << endl;
			exit(0);
			break;
		default:
			continue;
		}
	}
	return 0;
}