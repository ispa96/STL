#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
struct Doctor
{
    string d_name;
    string d_speciality;
};
struct Pacient
{
    string p_name;
    string p_speciality;
};

bool operator==(const Pacient& p1,const Doctor& d2) {
    if (p1.p_speciality == d2.d_speciality)
        return true;
    else return false;
}

int main()
{
    ifstream inFile("input3.txt");

    int no_problems, no_doctors;
    string name, speciality;
    std::vector<Doctor> doctors;
    std::vector<Pacient> pacients;
    
    inFile >> no_problems;

    for (int i = 0; i < no_problems; i++)
    {
        inFile >> name;
        inFile >> speciality;

        Pacient p;
        p.p_name = name;
        p.p_speciality = speciality;
        pacients.emplace_back(p);

        // cout << name << ' ' << speciality << '\n';
    }

    inFile >> no_doctors;

    for (int i = 0; i < no_doctors; i++)
    {
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
        if (it == doctors.end())
            std::cout << pacient.p_name << ' ' << "Respins\n";
        else std::cout << pacient.p_name << ' ' << "Acceptat\n";  
    }

    return 0;
}