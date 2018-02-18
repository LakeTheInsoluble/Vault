// Definition of Datastructure class, hw1 of TIE-20100/TIE-20106

#ifndef DATASTRUCTURE_HPP
#define DATASTRUCTURE_HPP

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <list>
using std::list;

struct Person
{
    string name;
    int salary;
};

//void quicksort(int left, int right, vector<Person *>, auto (*f)(auto));

class Datastructure
{
public:
    Datastructure();
    ~Datastructure();

    void add_person(string name, int salary);

    unsigned int size();
    void clear();

    vector<Person*> personnel_alphabetically();
    vector<Person*> personnel_salary_order();

    Person* min_salary();
    Person* max_salary();

    Person* median_salary();
    Person* first_quartile_salary();
    Person* third_quartile_salary();

private:
    // Add your implementation here

    list<Person> list_;
    vector<Person*> alphalist_;
    vector<Person*> salarylist_;

    bool asorted_;
    bool ssorted_;

    void salarysort(int left, int right);
    void alphasort(int left, int right);

    unsigned int size_;
};

#endif // DATAfSTRUCTURE_HPP
