#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(set<Goat> trip);
void delete_goat(set<Goat> &trip);
void add_goat(set<Goat> &trip, string [], string []);
void display_trip(set<Goat> trip);
int main_menu();

// menu function
int main_menu() {
    int choice = 0;

    do {
        cout << endl;
        cout << "*** GOAT MANAGER 3001 ***" << endl;
        cout << " [1] Add a goat" << endl;
        cout << " [2] Delete a goat" << endl;
        cout << " [3] List goats" << endl;
        cout << " [4] Quit" << endl;
        cout << " Choice --> ";
        cin >> choice;

        if (choice < 1 || choice > 4) {
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice < 1 || choice > 4);

    return choice;   // was missing this brace "checked"
}                    

void add_goat(set<Goat> &trip, string names[], string colors[]) {
    // beloe creates a random goat using arrays
    string n = names[rand() % SZ_NAMES];
    string c = colors[rand() % SZ_COLORS];
    int a = rand() % MAX_AGE + 1;

    // creates and add Goat object
    Goat g(n, a, c);
    trip.insert(g);

    cout << n << " (" << c << ", " << a << ") added to the trip!" << endl;
}

    // below is the display trip funcion
void display_trip(list<Goat> trip) {
    if (trip.empty()) {
        cout << "No goats in the trip right now." << endl;
        return;
    }

    cout << "\nCurrent goats in the trip:\n";
    int i = 1;
    for (const Goat &g : trip) {
        cout << "[" << i++ << "] "
             << g.get_name() << " (" << g.get_color()
             << ", age " << g.get_age() << ")" << endl;
    }
}

// basically lets you choose which goat you want to delete later
int select_goat(list<Goat> trip) {
    display_trip(trip);
    if (trip.empty()) return -1;

    cout << "Enter goat number to delete: ";
    int num;
    cin >> num;
    return num;
}

// adding delete goat func
void delete_goat(list<Goat> &trip) {
    if (trip.empty()) {
        cout << "No goats to delete." << endl;
        return;
    }
    
    int num = select_goat(trip);
    if (num < 1 || num > trip.size()) {
        cout << "Invalid goat number." << endl;
        return;
    }

    auto it = trip.begin();
    advance(it, num - 1);
    cout << "Removing " << it->get_name() << "..." << endl;
    trip.erase(it);
}


// main function
int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();

    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // this is the goat trip list
    list<Goat> trip;
    int choice;

    // main menu loop (Replaced cout lines)
    do {
        choice = main_menu();
            switch (choice) {
        case 1:
            add_goat(trip, names, colors);
            break;
        case 2:
            delete_goat(trip);
            break;
        case 3:
            display_trip(trip);
            break;
        case 4:
            cout << "Goodbye :)" << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
    }

           
    } while (choice != 4);

    return 0;
}