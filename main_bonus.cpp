#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Doctor
{
    std::string d_name;
    std::string d_speciality;
    bool available = true;  /// by default este true
    unsigned int start = 9;
    unsigned int finish = 17;
    std::vector<std::string> problems;
};

struct Pacient
{
    std::string p_name;
    std::string p_speciality;
    unsigned int duration;
};

bool operator==(const Pacient& p1,const Doctor& d2) {
    if (p1.p_speciality == d2.d_speciality and d2.available == true) {
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
        p.p_name = name;
        p.p_speciality = speciality;
        p.duration = _duration;
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
        auto lam = std::find_if(doctors.begin(), doctors.end(), [&](Doctor& doc) {
            if (doc.d_speciality == pacient.p_speciality) {
                if (doc.start + pacient.duration <= doc.finish) {
                    doc.start += pacient.duration;
                    doc.problems.emplace_back(pacient.p_name);
                    return true;
                }
            }
        });
    }

    for (auto& doctor : doctors) {
        std::cout << doctor.d_name << ' ' << doctor.problems.size() << ' ';

        for (auto& problem : doctor.problems)
            std::cout << problem << ' ';

        std::cout << '\n';
    }

    return 0;
}
