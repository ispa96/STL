#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Doctor
{
    std::string name;
    std::string speciality;
    bool available = true;  /// by default este true
    unsigned int start = 9;
    unsigned int finish = 17;
    std::vector<std::string> problems;
};

struct Pacient
{
    std::string name;
    std::string disease;
    unsigned int duration;
};

bool operator==(const Pacient& p1,const Doctor& d2) {
    if (p1.disease == d2.speciality and d2.available == true) {
        return true;
    }
    else return false;
}

int main()
{
    std::ifstream inFile("input4_bonus.txt");

    int no_problems, no_doctors, _duration;
    std::string name, speciality;
    std::vector<Doctor> doctors;
    std::vector<Pacient> pacients;
    
    inFile >> no_problems;

    for (int i = 0; i < no_problems; i++) {
        inFile >> name;
        inFile >> speciality;
        inFile >> _duration;

        Pacient p;
        p.name = name;
        p.disease = speciality;
        p.duration = _duration;
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
        auto lam = std::find_if(doctors.begin(), doctors.end(), [&](Doctor& doc) {
            if (doc.speciality == pacient.disease) {
                if (doc.start + pacient.duration <= doc.finish) {
                    doc.start += pacient.duration;
                    doc.problems.emplace_back(pacient.name);
                    return true;
                }
            }
        });
    }

    for (auto& doctor : doctors) {
        std::cout << doctor.name << ' ' << doctor.problems.size() << ' ';

        for (auto& problem : doctor.problems)
            std::cout << problem << ' ';

        std::cout << '\n';
    }

    return 0;
}
