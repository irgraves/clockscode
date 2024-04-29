/*
| Author: Ian Graves
| Date: March 21, 2024
*/

#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;
// abstract base class for the clock
class Clock {
protected:
    int hours;
    int minutes;
    int seconds;

public:
    // this constructor is used to initialize the variables
    Clock(int h, int m, int s) : hours(h), minutes(m), seconds(s) {}
    // method to set the time below
    virtual void setTime(int h, int m, int s) {
        hours = h;
        minutes = m;
        seconds = s;
    }
    
    virtual string getTime() = 0; // virtual function to display the time
    // the three methods that follow are used to add seconds, minutes, and hours
    void addHour() {
        hours = (hours + 1) % 24;
    }

    void addMinute() {
        minutes = (minutes + 1) % 60;
        if (minutes == 0) addHour();
    }

    void addSecond() {
        seconds = (seconds + 1) % 60;
        if (seconds == 0) addMinute();
    }
};
// derived from the base class, this is the class for the 12 hour clock
class Clock12 : public Clock {
    bool isAm; //true if am, false if pm
    // constructor
public:
    Clock12(int h, int m, int s, bool isAm = true) : Clock(h, m, s), isAm(isAm) {}
    // added this to ensure the 12 hour clock returned to 12 at 0
        void setTime(int h, int m, int s, bool isAm = true) {
            Clock::setTime(h, m, s);
            this->isAm = isAm;
        }
    void addHour() {
        hours = (hours + 1) % 12;
        if (hours == 0) {
            hours = 12;
            isAm = !isAm; // AM to PM flip, and vise versa
        }
    }
    // ensures that 60 minutes wont force the hour over 12
    void addMinute() {
        minutes = (minutes + 1) % 60;
        if (minutes == 0) {
            addHour(); //respects AM to PM flip via minutes
        }
    }
    // ensures that 60 seconds wont force the hour over 12
    void addSecond() {
        seconds = (seconds + 1) % 60;
        if (seconds == 0) {
            addMinute(); 
        }
    }
    

    //override to display the time on the 12 hour clock
    string getTime() override {
        stringstream ss;
        ss << setfill('0') << setw(2) << hours << ":" << setw(2) << minutes << ":" << setw(2) << seconds << (isAm ? " AM" : " PM");
        return ss.str();
    
    }
};
// derived from the base class, this is the class for the 24 hour clock
class Clock24 : public Clock {
    // constructor
public:
    Clock24(int h, int m, int s) : Clock(h, m, s) {}
    // override to display the 24 hour clock
    string getTime() override {
        stringstream ss;
        ss << setfill('0') << setw(2) << hours << ":" << setw(2) << minutes << ":" << setw(2) << seconds;
        return ss.str();
    }
};

int main() {
    //creates instances of both the 12 and 24 hour clocks, at 0, the 12 hour clock will display 12
    Clock12 clock12(12, 0, 0);
    Clock24 clock24(0, 0, 0);

    int choice;
    do {
        //menu that prompts the user to add to the clock
        cout << "***********************\n";
        cout << "* 1 - Add One Hour    *\n";
        cout << "* 2 - Add One Minute  *\n";
        cout << "* 3 - Add One Second  *\n";
        cout << "* 4 - Exit            *\n";
        cout << "***********************\n";
        cout << "Enter your choice: ";
        cin >> choice;
        //switch loop that allows the user to add hours, minutes, and seconds to both clocks
        switch (choice) {
        case 1:
            clock12.addHour();
            clock24.addHour();
            break;
        case 2:
            clock12.addMinute();
            clock24.addMinute();
            break;
        case 3:
            clock12.addSecond();
            clock24.addSecond();
            break;
        case 4:
            cout << "Exiting...Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
        // display time for both clocks
        cout << "**********************    *********************\n";
        cout << "*   12-hour clock    *    *   24-hour clock   *\n";
        cout << "*    " << clock12.getTime() << "     *    *     " << clock24.getTime() << "      *\n";
        cout << "**********************    *********************\n";
    } while (choice != 4);// continue until the user types 4, which is the exit case.

    return 0;
}
