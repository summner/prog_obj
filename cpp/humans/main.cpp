#include <iostream>
#include <time.h>
#include <queue>

class Human {
  protected:
    std::string first_name;
    std::string last_name;

  public:
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

    virtual std::string get_name() {
        return this->last_name;
    }
};

class Teacher: public Human {
    using Human::Human;
    bool drink(int) { return false; }
};

std::string random_name(std::vector<std::string> names){
    int nameIndex = rand() % (names.size());
    return names[nameIndex];
}


int main(int, char**)
{
    srand ( time(NULL) );
    std::cout << "Dlugosc kolejki ";
    int queueLen;
    std::cin >> queueLen;

    std::vector<std::string> firstNames = {"Pawel", "Michal", "Jakub", "Robert", "Janusz", "Jacek"};
    std::vector<std::string> lastNames = { "Dzedziczny", "Hermetyczny", "Abstrakcyjny", "Iksinski"};

    std::deque<Human*> queue;
    for (int i=0; i<queueLen; i++) {
        if (rand()%2 == 0){
            queue.push_back(
                (Human *)new Student(random_name(firstNames), random_name(lastNames))
            );
        } else {
            queue.push_back(
                (Human *)new Teacher(random_name(firstNames), random_name(lastNames))
            );
        }
    }

    for(auto human: queue) {
        std::string drinkStatus = (human->drink(1))?"pije 1 i więcej": "nie pije w ogóle";
        std::cout << human->get_name() << " " << drinkStatus << std::endl;
    }
    return 0;
}
