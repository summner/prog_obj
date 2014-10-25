#include <QCoreApplication>
#include <iostream>
#include <time.h>
#include <queue>

class Human {
  protected:
    std::string first_name;
    std::string last_name;

  public:
    Human(const char *first_name, const char *last_name) {
        this->first_name = std::string(first_name);
        this->last_name = std::string(last_name);
    }
    Human(std::string first_name, std::string last_name) {
        this->first_name = first_name;
        this->last_name = last_name;
    }

    virtual std::string get_name() {
        return first_name + " " + last_name;
    }

    virtual bool drink(int) = 0;
};

class Student: public Human {
    using Human::Human;
    bool drink(int) { return true; }
};


class Teacher: public Human {
    using Human::Human;
    bool drink(int) { return false; }
    virtual std::string get_name() {
        return std::string("Dr. ") + Human::get_name();
    }
};



int main(int argc, char *argv[])
{
    srand (time(NULL));
    std::vector<std::string> firstNames = {"Pawel", "Michal", "Jakub", "Robert", "Janusz", "Jacek"};
    std::vector<std::string> lastNames = { "Dzedziczny", "Hermetyczny", "Abstrakcyjny", "Iksinski"};

    std::deque<Human*> queue;
    for (int i=0; i<5; i++) {
        int nameIndex = rand() % (firstNames.size());
        int lastNameIndex = rand() % (lastNames.size());

        queue.push_back(
            (Human *)new Student(firstNames[nameIndex], lastNames[lastNameIndex])
        );
    }

    for (int i=0; i<5; i++) {
        int nameIndex = rand() % (firstNames.size());
        int lastNameIndex = rand() % (lastNames.size());

        queue.push_back(
            (Human *)new Teacher(
                     firstNames[nameIndex],
                     lastNames[lastNameIndex]
                )
        );
    }

    for(auto human: queue) {
        std::string drinkStatus = (human->drink(1))?"drinks": "doesn't drink";
        std::cout << human->get_name() << " " << drinkStatus << std::endl;
    }
    return 0;
}
