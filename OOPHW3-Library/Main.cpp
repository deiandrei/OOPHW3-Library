#include <iostream>

#include "Utils.h"
#include "User.h"
#include "Library.h"

bool gIsLogged; int gID;
std::vector<User*> users;
Library* library;

void PrintMenu() {
	system("cls");
	std::cout << "----- Alegeti o varianta -----\n";
	if (gIsLogged) {
		std::cout << "1. Cauta dupa ID\n";
		std::cout << "2. Cauta dupa Nume\n";
		std::cout << "3. Cauta dupa Valoare\n";
		std::cout << "4. Cauta dupa Text\n\n\n";
		std::cout << "5. Adauga\n";
		std::cout << "6. Sterge dupa ID\n";
		std::cout << "7. Sterge dupa Nume\n\n\n";
	}
	else {
		std::cout << "1. Autentificare\n";
	}
	std::cout << "0. Inchidere\n\n";
	std::cout << "Alegere: ";
}

bool Parse(const std::string& input) {
	int val = atoi(input.c_str());
	if (val == 0) {
		if (gIsLogged) library->Save(std::to_string(gID) + ".userdbtxt");
		return 0;
	}

	if (gIsLogged) {
		std::cout << "\n\n\n\n";

		if (val == 1) {
			int id = -1;
			std::cout << "Introdu ID: "; std::cin >> id;

			id = library->FindByID(id);
			if (id != -1) library->Print(id);
			else std::cout << "Nu am gasit ID-ul introdus!";
		}
		else if (val == 2) {
			int id = -1;
			std::string temp;
			std::cout << "Introdu Nume: "; std::cin >> temp;

			id = library->FindByName(temp);
			if (id != -1) library->Print(id);
			else std::cout << "Nu am gasit Numele introdus!";
		}
		else if (val == 5) {
			std::string name;
			std::cout << "Introduceti un Nume (nu e obligatoriu, pentru a lasa numele gol treceti -): "; std::cin >> name;
			if (name == "") name = "-";

			int type;
			std::cout << "Introduceti tipul de date (1 = Text, 2 = Numar, 3 = Numar complex, 4 = Locatie): "; std::cin >> type;

			if (type == 1) {
				std::string temp;
				std::cout << "Introduceti textul (fara spatii): "; std::cin >> temp;

				library->Add(name, Variant(temp));
			}
			else if (type == 2) {
				double temp;
				std::cout << "Introduceti numarul: "; std::cin >> temp;

				library->Add(name, Variant(temp));
			}
			else if (type == 3) {
				float f1, f2;
				std::cout << "Introduceti partea reala si partea imaginara: "; std::cin >> f1 >> f2;

				library->Add(name, Variant(ComplexNum(f1, f2)));
			}
			else if(type == 4) {
				std::string temp;
				std::cout << "Introduceti adresa (fara spatii): "; std::cin >> temp;

				library->Add(name, Variant(Location(temp)));
			}

			std::cout << "Datele au fost adaugate cu succes!";
		}
		else if (val == 3) {
			double temp; std::cout << "Introdu valoarea cautata: "; std::cin >> temp;

			std::vector<int> vals = library->FindByValue(temp);
			if (vals.size()) {
				std::cout << "Valoarea introdusa a fost gasita la ID-urile: ";
				for (int i = 0; i < vals.size(); ++i) {
					std::cout << library->Get(vals[i])->ID << " ";
				}
			}
			else std::cout << "Nu am gasit valoarea cautata!";
		}
		else if (val == 4) {
			std::string temp; std::cout << "Introdu textul cautat: "; std::cin >> temp;

			std::vector<int> vals = library->FindByText(temp);
			if (vals.size()) {
				std::cout << "Textul introdus a fost gasita la ID-urile: ";
				for (int i = 0; i < vals.size(); ++i) {
					std::cout << library->Get(vals[i])->ID << " ";
				}
			}
			else std::cout << "Nu am gasit textul cautat!";
		}
		else if (val == 6) {
			int id; std::cout << "Introdu ID-ul de sters: "; std::cin >> id;
			
			id = library->FindByID(id);
			if (id != -1) library->Delete(id);
		}
		else if (val == 7) {
			std::string name; std::cout << "Introdu Numele de sters: "; std::cin >> name;

			int id = library->FindByName(name);
			if (id != -1) library->Delete(id);
		}

		std::cout << "\n";
		system("pause");
	}
	else {
		if (val == 1) {
			system("cls");
			std::string user, pass;
			std::cout << "User: "; std::cin >> user;
			std::cout << "Pass: "; std::cin >> pass;

			for (unsigned int i = 0; i < users.size(); ++i) 
				if (user == users[i]->GetName() && pass == users[i]->GetPass()) {
					gIsLogged = true;
					gID = i;
					library = new Library(std::to_string(gID) + ".userdbtxt");
				}

				if (!gIsLogged) std::cout << "\n\n\nAti introdus datele gresit!\n", system("pause");
		}
	}

	return 1;
}

int main(int argc, char** argv) {
	gIsLogged = false;
	Utils::LoadDB("users.dbtxt", users);

	bool running = true;
	std::string input;
	while (running) {
		PrintMenu();
		std::cin >> input;

		running = Parse(input);
	}

	return 0;
}
