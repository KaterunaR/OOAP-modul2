#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
using namespace std;

// мешканець кімнати
class Resident {
public:
    string name;
    tm birthDate;
    string faculty;
    string group;
    string studyForm;

    Resident(string name, string birthDateStr, string faculty, string group, string studyForm)
        : name(name), faculty(faculty), group(group), studyForm(studyForm) {

        stringstream ss(birthDateStr);
        ss >> get_time(&birthDate, "%d-%m-%Y");  //дата народження
    }

    void showInfo() const {
        cout << name << ", "
            << setfill('0') << setw(2) << birthDate.tm_mday << "-"
            << setfill('0') << setw(2) << birthDate.tm_mon + 1 << "-"
            << birthDate.tm_year + 1900 << ", "
            << faculty << ", "
            << group << ", "
            << studyForm << endl;
    }
};

// кімеата
class Room {
public:
    virtual Room* clone() const = 0;  

    virtual void addResident(const Resident& resident) = 0; 
    virtual void generateReport() const = 0; 

    virtual ~Room() {}
};

// двохкімнатна
class DoubleRoom : public Room {
private:
    vector<Resident> residents;
    double rentFee = 2000; 

public:
    DoubleRoom() {}

    Room* clone() const override {
        return new DoubleRoom(*this);  
    }

    void addResident(const Resident& resident) override {
        if (residents.size() < 2) {
            residents.push_back(resident);
        }
        else {
            cout << "The room is full!" << endl;
        }
    }

    void generateReport() const override {
        cout << "Type of room: Double" << endl;
        cout << "Number of residents: " << residents.size() << endl;
        for (const auto& resident : residents) {
            resident.showInfo();
            cout << "Rent: " << rentFee << " UAH" << endl;
        }
    }
};

// трьохкімнатна
class TripleRoom : public Room {
private:
    vector<Resident> residents;
    double rentFee = 1200; 

public:
    TripleRoom() {}

    Room* clone() const override {
        return new TripleRoom(*this);  
    }

    void addResident(const Resident& resident) override {
        if (residents.size() < 3) {
            residents.push_back(resident);
        }
        else {
            cout << "The room is full!" << endl;
        }
    }

    void generateReport() const override {
        cout << "Type of room: Triple" << endl;
        cout << "Number of residents: " << residents.size() << endl;
        for (const auto& resident : residents) {
            resident.showInfo();
            cout << "Rent: " << rentFee << " UAH" << endl;
        }
    }
};

// менеджер кімнат
class Hostel {
private:
    vector<Room*> rooms;  

public:
    void addRoom(Room* room) {
        rooms.push_back(room);
    }

    void showHostelReport() const {
        for (const auto& room : rooms) {
            room->generateReport();
            cout << "---------------------------------" << endl;
        }
    }


    ~Hostel() {
        for (auto room : rooms) {
            delete room;
        }
    }
};


int main() {
    Resident resident1("Ivan", "07-12-2004", "Computer Science", "KN-21", "state funding");
    Resident resident2("Vika", "30-03-2005", "Software Engineering", "IPZ-31", "self-financed");
    Resident resident3("Maria", "22-05-2005", "Information Technology", "IST-22", "state funding");
    Resident resident4("Stasya", "13-05-2004", "Information Technology", "IST-22", "state funding");

    DoubleRoom room1;
    TripleRoom room2;

    room1.addResident(resident1);
    room1.addResident(resident2);
    room1.addResident(resident4);

    room2.addResident(resident3);

    Hostel hostel;
    hostel.addRoom(&room1);
    hostel.addRoom(&room2);

    hostel.showHostelReport();

    return 0;
}

