#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

struct Doctor
{
    std::string name;
    std::string speciality;
    bool available = true;  /// by default este true
    int start = 9;
    int finish = 17;
    std::vector<std::string> problems;
};

struct Pacient
{
    std::string name;
    std::string disease;
    int time;
    int priority;
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
    int duration;
    int _priority;
    std::string name, speciality;
    std::vector<Doctor> doctors;
    std::vector<Pacient> pacients;
    
    inFile >> no_problems;

    for (int i = 0; i < no_problems; i++) {
        inFile >> name;
        inFile >> speciality;
        inFile >> duration;
        inFile >> _priority;

        Pacient p;
        p.name = name;
        p.disease = speciality;
        p.time = duration;
        p.priority = _priority;
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

    /// sortam vectorul de pacienti in functie de prioritate
    sort(pacients.begin(), pacients.end(), [](const Pacient& pacient1, const Pacient& pacient2) {
        return pacient1.priority < pacient2.priority;
    });

    std::stack<Pacient> pacients_stack;
    for (auto& pacient : pacients)
        pacients_stack.push(pacient);

    while(!pacients_stack.empty()) {
        Pacient pacient = pacients_stack.top();

        auto it = find_if(doctors.begin(), doctors.end(), [&pacient](Doctor& doctor) {
            if (pacient.disease == doctor.speciality) {
                if (doctor.start + pacient.time <= 17) {
                    doctor.start += pacient.time;
                    return true;
                }
                else return false;  
            }
            else return false;
        });

        if (it != doctors.end()) {  /// daca a gasit in vectorul de doctori, pacientul respectiv
            (*it).problems.emplace_back(pacient.name);   /// pune in vectorul de probleme rezolvate al doctorului respectiv, problema rezolvata
        }

        pacients_stack.pop();
    }

    for (auto& doctor : doctors) {
        if (doctor.problems.size()) {
            std::cout << doctor.name << ' ' << doctor.problems.size() << ' ';

            for (auto& problem : doctor.problems)
                std::cout << problem << ' ';

            std::cout << '\n';
        }
    }

    return 0;
}