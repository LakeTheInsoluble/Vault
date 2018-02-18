// Henri Laakso 240062 henri.m.laakso@student.tut.fi

// Definition of Datastructure class, hw3 of TIE-20100/TIE-20106

#include "datastructure.hpp"

// For debug
#include <iostream>
using std::cerr;
using std::endl;

// Helper function to return a random (enough) number in range start-end
// I.e. random_in_range(1,4) produces a random number between 1, 2, 3, or 4.
template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = rand() % range;
    return static_cast<Type>(start+num);
}

Datastructure::Datastructure()
{
    size_ = 0;
    asorted_ = false;
    ssorted_ = false;
}

Datastructure::~Datastructure()
{
}

void Datastructure::add_person(std::string name, int salary)
{
    Person p;
    p.name = name;
    p.salary = salary;
    list_.push_back(p);
    salarylist_.push_back(&list_.back());
    alphalist_.push_back(&list_.back());
    size_ += 1;
    asorted_ = false;
    ssorted_ = false;
}

unsigned int Datastructure::size()
{
    return size_;
}

void Datastructure::clear()
{
    salarylist_.clear();
    alphalist_.clear();
    list_.clear();
    size_ = 0;
}

vector<Person *> Datastructure::personnel_alphabetically()
{
    if(asorted_)
    {
        return alphalist_;
    }
    else
    {
        alphasort(0, size_ - 1);
        asorted_ = true;
        return alphalist_;
    }
}

vector<Person *> Datastructure::personnel_salary_order()
{
    if(ssorted_)
    {
        return salarylist_;
    }
    else
    {
        salarysort(0, size_ - 1);
        ssorted_ = true;
        return salarylist_;
    }
}

Person* Datastructure::min_salary()
{
    if(ssorted_ == true)
    {
        return salarylist_.front();
    }
    else
    {
        int min = 0;
        for(unsigned int i = 1; i < list_.size(); i++)
        {
            if(salarylist_[min]->salary > salarylist_[i]->salary)
            {
                min = i;
            }
        }
        return salarylist_[min];
    }
}

Person* Datastructure::max_salary()
{
    if(ssorted_ == true)
    {
        return salarylist_.back();
    }
    else
    {
        int max = 0;
        for(unsigned int i = 1; i < salarylist_.size(); i++)
        {
            if(salarylist_[max]->salary < salarylist_[i]->salary)
            {
                max = i;
            }
        }
        return salarylist_[max];
    }
}

Person* Datastructure::median_salary()
{
    if(not ssorted_)
    {
        salarysort(0, size_ - 1);
        ssorted_ = true;
    }
    if(size_ == 0)
    {
        return nullptr;
    }
    else if(size_ < 3)
    {
        return salarylist_.front();
    }
    else
    {
        return salarylist_[size_ / 2];
    }
}

Person* Datastructure::first_quartile_salary()
{
    if(not ssorted_)
    {
        salarysort(0, size_ - 1);
        ssorted_ = true;
    }
    if(size_ == 0)
    {
        return nullptr;
    }
    else if(size_ < 3)
    {
        return salarylist_.front();
    }
    else
    {
        return salarylist_[size_ / 4];
    }
}

Person* Datastructure::third_quartile_salary()
{
    if(not ssorted_)
    {
        salarysort(0, size_ - 1);
        ssorted_ = true;
    }
    if(size_ == 0)
    {
        return nullptr;
    }
    else if(size_ < 2)
    {
        return salarylist_.back();
    }
    else
    {
        return salarylist_[3 * size_ / 4];
    }
}

// Quicksort molemmille vektoreille.
// Olisi nämä kaksi sorttausfunktiota saanut tungettua yhteen,
// mutta mielestäni tämä toteutus on paljon miellyttävämpi,
// vaikka tämä toteutus sisältää hieman toistoa.

void Datastructure::salarysort(int left, int right)
{
    int i = left, j = right;
    Person* tmp;
    int pivot = (*salarylist_[(left + right) / 2]).salary;

    while (i <= j)
    {
        while ((*(salarylist_[i])).salary < pivot)
        {
            i++;
        }
        while ((*salarylist_[j]).salary > pivot)
        {
            j--;
        }
        if (i <= j)
        {
            tmp = salarylist_[i];
            salarylist_[i] = salarylist_[j];
            salarylist_[j] = tmp;
            i++;
            j--;
        }
    }
    if (left < j)
    {
        salarysort(left, j);
    }
    if (i < right)
    {
        salarysort(i, right);
    }
}

void Datastructure::alphasort(int left, int right)
{
    int i = left, j = right;
    Person* temp;
    string pivot = (*alphalist_[(left + right) / 2]).name;

    while (i <= j)
    {
        while ((*(alphalist_[i])).name < pivot)
        {
            i++;
        }
        while ((*alphalist_[j]).name > pivot)
        {
            j--;
        }
        if (i <= j)
        {
            temp = alphalist_[i];
            alphalist_[i] = alphalist_[j];
            alphalist_[j] = temp;
            i++;
            j--;
        }
    }
    if (left < j)
    {
        alphasort(left, j);
    }
    if (i < right)
    {
        alphasort(i, right);
    }
}
