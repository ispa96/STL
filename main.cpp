/// problema bonus

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
// #include <map>

struct Doctor
{
    std::string name;
    int start;
    int finish;
    int no_specialities;
    std::vector<std::string> specialities;
    std::vector<std::string> solved;
    std::vector<int> hours;

    Doctor() {
        start = 9;
        finish = 17;
    }
};

struct Pacient
{
    std::string name;
    std::string disease;
    int arrival_time, duration, priority;
};

int main()
{
    std::ifstream inFile("input4_bonus.txt");

    int no_problems, no_doctors;
    std::vector<Pacient> pacients;
    std::vector<Doctor> doctors;

    int _arrival, _duration, _priority;
    std::string _problem, _speciality;

    int _no_specialities;
    std::string _name;

    inFile >> no_problems;

    for (int i = 0; i < no_problems; i++) {
        inFile >> _problem >> _speciality >> _arrival >> _duration >> _priority;

        Pacient p;
        p.name = _problem;
        p.disease = _speciality;
        p.arrival_time = _arrival;
        p.duration = _duration;
        p.priority = _priority;

        pacients.emplace_back(p);
    }

    inFile >> no_doctors;

    for (int i = 0; i < no_doctors; i++) {
        inFile >> _name >> _no_specialities;

        Doctor d;
        d.name = _name;
        d.no_specialities = _no_specialities;

        for (int j = 0; j < _no_specialities; j++)
            inFile >> _speciality, d.specialities.emplace_back(_speciality);

        doctors.emplace_back(d);
    }

    /// sortez vectorul de pacienti dupa arrival_time, apoi dupa priority
    sort(pacients.begin(), pacients.end(), [](const auto& p1, const auto& p2) {
        if (p1.arrival_time < p2.arrival_time)
            return true;
        else if (p1.arrival_time == p2.arrival_time) {
            if (p1.priority > p2.priority)
                return true;
            else return false;
        }
        else return false;
        });

   /* for (const auto& pacient : pacients)
        std::cout << pacient.name << ' ' << pacient.arrival_time << ' ' << pacient.priority << '\n';*/

    /// luam fiecare pacient si vedem daca putem sa l luam sa l tratam
    for (const auto& pacient : pacients) {
        // std::cout << pacient.name << '\n';

        for (auto& doctor : doctors) {  /// cautam in vectorul de doctori sa vedem daca poate vreunul sa rezolve pacientul respectiv
            /// daca doctorul are specialitatea necesara si timpul necesar, atunci poate sa l rezolve

            auto it = std::find(doctor.specialities.begin(), doctor.specialities.end(), pacient.disease);

            if (it != doctor.specialities.end() and pacient.arrival_time + pacient.duration <= doctor.finish and pacient.arrival_time >= doctor.start) {  /// a gasit la doctorul respectiv specializarea potrivita si are si timp
                doctor.hours.emplace_back(pacient.arrival_time);    /// pune ora la care a rezolvat problema
                doctor.solved.emplace_back(pacient.name);   /// pune problema pe care a rezolvat o
                doctor.start = pacient.arrival_time + pacient.duration; /// actualizeaza ora de la care este disponibil doctorul

                break;  /// iesim deoarece am rezolvat deja acest pacient
            }
            /// daca nu, continuam sa cautam
        }

       /* for (const auto& doctor : doctors) {
            std::cout << doctor.name << ' ' << doctor.start << '\n';
        }
        std::cout << '\n';*/
    }

    for (const auto& doctor : doctors) {
        if (!doctor.solved.empty()) {
            std::cout << doctor.name << ' ';
            std::cout << doctor.solved.size() << ' ';

            for (int i = 0; i < doctor.solved.size(); i++)
                std::cout << doctor.solved[i] << ' ' << doctor.hours[i] << ' ';

            std::cout << '\n';
        }
    }

    return 0;
}
