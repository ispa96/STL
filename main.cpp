#include <iostream>
#include <fstream>
#include <string>
#include <vector>


struct Doctor
{
    std::string name;
    std::string speciality;
    bool available = true;  /// by default este true
};
struct Pacient
{
    std::string name;
    std::string disease;
};

bool operator==(const Pacient& p1,const Doctor& d2) {
    if (p1.disease == d2.speciality and d2.available == true) {
        return true;
    }
    else return false;
}

int main()
{
    std::ifstream inFile("input3.txt");

    int no_problems, no_doctors;
    std::string name, speciality;
    std::vector<Doctor> doctors;
    std::vector<Pacient> pacients;
    
    inFile >> no_problems;

    for (int i = 0; i < no_problems; i++) {
        inFile >> name;
        inFile >> speciality;

        Pacient p;
        p.name = name;
        p.disease = speciality;
        pacients.emplace_back(p);

        // cout << name << ' ' << speciality << '\n';
    }

    inFile >> no_doctors;

    for (int i = 0; i < no_doctors; i++) {
        inFile >> name;
        inFile >> speciality;

        Doctor d;
        d.name = name;
        d.speciality = speciality;
        doctors.emplace_back(d);

        // cout << name << ' ' << speciality << '\n';
    }

    for (auto& pacient : pacients) {
        auto it = find_if(doctors.begin(), doctors.end(), [&pacient](const Doctor& doc) {
            if (doc.speciality == pacient.disease and doc.available == true)
                return true;
            else return false;
        });

        if (it != doctors.end()) {
            (*it).available = false;    /// devine ocupat
            std::cout << (*it).name << ' ' << (*it).speciality << '\n';
        }
    }



    return 0;
}