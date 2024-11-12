#include <iostream>
#include <fstream>
#include <string>
#include <vector>


struct Doctor
{
    std::string d_name;
    std::string d_speciality;
    bool available = true;  /// by default este true
};
struct Pacient
{
    std::string p_name;
    std::string p_speciality;
};

bool operator==(const Pacient& p1,const Doctor& d2) {
    if (p1.p_speciality == d2.d_speciality and d2.available == true) {
        return true;
    }
    else return false;
}

int main()
{
    std::ifstream inFile("input.txt");

    int no_problems, no_doctors;
    std::string name, speciality;
    std::vector<Doctor> doctors;
    std::vector<Pacient> pacients;
    
    inFile >> no_problems;

    for (int i = 0; i < no_problems; i++) {
        inFile >> name;
        inFile >> speciality;

        Pacient p;
        p.p_name = name;
        p.p_speciality = speciality;
        pacients.emplace_back(p);

        // cout << name << ' ' << speciality << '\n';
    }

    inFile >> no_doctors;

    for (int i = 0; i < no_doctors; i++) {
        inFile >> name;
        inFile >> speciality;

        Doctor d;
        d.d_name = name;
        d.d_speciality = speciality;
        doctors.emplace_back(d);

        // cout << name << ' ' << speciality << '\n';
    }

    for (auto& pacient : pacients) {
        auto it = find(doctors.begin(), doctors.end(), pacient);
        unsigned int pos = std::distance(doctors.begin(), it);

        if (it != doctors.end()) {
            doctors[pos].available = false;
            std::cout << doctors[pos].d_name << ' ' << doctors[pos].d_speciality << '\n';
        }
    }

    return 0;
}