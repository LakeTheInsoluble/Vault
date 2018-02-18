// Henri Laakso, 240062, henri.m.laakso@student.tut.fi

// Definition of Datastructure class, hw2 of TIE-20100/TIE-20106

#include "datastructure.hpp"

#include <algorithm>

// For debug
#include <iostream>
using std::cerr;
using std::endl;

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
}

Datastructure::~Datastructure()
{
}

void Datastructure::add_person(string name, PersonID id, string title, Salary salary)
{
    Person p;

    if(umap.find(id) == umap.end()) {
        p.name = name;
        p.title = title;
        p.salary = salary;
        p.usorted = false;

        umap[id] = p;
        salarylist.push_back(id);
        alphalist.push_back(id);

        ssorted = false;
        asorted = false;

        ceo = NO_ID;
    }
}

void Datastructure::remove_person(PersonID id)
{
    if(umap.find(id) != umap.end()){
        if(umap[id].boss != NO_ID) {
            umap[umap[id].boss].underlings.erase(
                        remove(umap[umap[id].boss].underlings.begin(),
                        umap[umap[id].boss].underlings.end(), id));
            if(umap[id].underlings.size() > 0) {
                // Lisätään alaiset pomon alaisiksi.
                for(auto it : umap[id].underlings) {
                    umap[it].boss = umap[id].boss;
                }
                umap[umap[id].boss].underlings.insert(umap[umap[id].boss].underlings.end(),
                        umap[id].underlings.begin(), umap[id].underlings.end());
            }
            umap[umap[id].boss].usorted = false;
        } else {
            for(auto it : umap[id].underlings) {
                umap[it].boss = NO_ID;
            }
        }
        // Poistetaan itse työntekijä listoilta.
        salarylist.erase(remove(salarylist.begin(), salarylist.end(), id), salarylist.end());
        alphalist.erase(remove(alphalist.begin(), alphalist.end(), id), alphalist.end());
        umap.erase(id);
    }
}

string Datastructure::get_name(PersonID id)
{
    if(umap.find(id) != umap.end()) {
        return umap[id].name;
    } else {
        return "";
    }
}

string Datastructure::get_title(PersonID id)
{
    if(umap.find(id) != umap.end()) {
        return umap[id].title;
    } else {
        return "";
    }
}

Salary Datastructure::get_salary(PersonID id)
{
    if(umap.find(id) != umap.end()) {
        return umap[id].salary;
    } else {
        return NO_SALARY;
    }
}

vector<PersonID> Datastructure::find_persons(string name)
{
    vector<PersonID> vec;
    for(auto it : umap) {
        if(it.second.name == name) {
            vec.push_back(it.first);
        }
    }
    sort(vec.begin(), vec.end());
    return vec;
}

vector<PersonID> Datastructure::personnel_with_title(string title)
{
    vector<PersonID> vec;
    for(auto it : umap) {
        if(it.second.title == title) {
            vec.push_back(it.first);
        }
    }
    sort(vec.begin(), vec.end());
    return vec;
}

void Datastructure::change_name(PersonID id, string new_name)
{
    if(umap.find(id) !=  umap.end()) {
        asorted = false;
        umap[id].name = new_name;
    }
}

void Datastructure::change_salary(PersonID id, Salary new_salary)
{
    // Sallitaan negatiiviset palkat.
    if(umap.find(id) !=  umap.end()) {
        ssorted = false;
        umap[id].salary = new_salary;
    }
}

void Datastructure::add_boss(PersonID id, PersonID bossid)
{
    PersonID temp = bossid;
    if(umap.find(id) != umap.end() && umap.find(bossid) != umap.end()) {
        while(umap[temp].boss != NO_ID && temp != id) {
            temp = umap[temp].boss;
        }
        if(temp != id) {
            umap[id].boss = bossid;
            umap[bossid].underlings.push_back(id);
            umap[bossid].usorted = false;
        }
    }
}

unsigned int Datastructure::size()
{
    return umap.size();
}

void Datastructure::clear()
{
    alphalist.clear();
    salarylist.clear();
    umap.clear();
}

vector<PersonID> Datastructure::underlings(PersonID id)
{
    if(umap.find(id) != umap.end()){
        if(!umap[id].usorted) {
            sort(umap[id].underlings.begin(),umap[id].underlings.end());
            umap[id].usorted = true;
        }
        return umap[id].underlings;
    } else {
        return {};
    }
}

vector<PersonID> Datastructure::personnel_alphabetically()
{
    if(asorted) {
        return alphalist;
    } else {
        sort(alphalist.begin(), alphalist.end(), [this](const PersonID a, const PersonID b) {
            return umap[a].name < umap[b].name;
        });
        return alphalist;
    }
}

vector<PersonID> Datastructure::personnel_salary_order()
{
    if(ssorted) {
        return salarylist;
    } else {
        sort(salarylist.begin(), salarylist.end(), [this](const PersonID a, const PersonID b) {
            return umap[a].salary < umap[b].salary;
        });
        ssorted = true;
        return salarylist;
    }
}

PersonID Datastructure::find_ceo()
{
    int bossless = 0;
    if(ceo != NO_ID) {
        return ceo;
    }
    for(auto it : umap) {
        if(it.second.boss == NO_ID) {
            ceo = it.first;
            bossless += 1;
        }
    }
    if(bossless == 1) {
        return ceo;
    } else {
        ceo = NO_ID;
        return ceo;
    }
}

PersonID Datastructure::nearest_common_boss(PersonID id1, PersonID id2)
{
    // return NO_ID; // If you do not implement this, leave this return value as it is.

    vector<PersonID> id1_bosses;
    vector<PersonID> id2_bosses;
    PersonID temp1 = id1;
    PersonID temp2 = id2;
    PersonID common_boss = NO_ID;

    unsigned int higher1 = 0;
    unsigned int higher2 = 0;

    if(umap.find(id1) == umap.end() || umap.find(id2) == umap.end()) {
        return NO_ID;
    }

    if(umap[id1].boss == NO_ID || umap[id2].boss == NO_ID) {
        return NO_ID;
    }

    while(umap[temp1].boss != NO_ID) {
        temp1 = umap[temp1].boss;
        higher1 += 1;
        id1_bosses.push_back(temp1);
    }

    while(umap[temp2].boss != NO_ID) {
        temp2 = umap[temp2].boss;
        higher2 += 1;
        id2_bosses.push_back(temp2);
    }

    while( higher1 > 0 && higher2 > 0
           && id1_bosses[higher1-1] == id2_bosses[higher2-1]) {
        common_boss = id1_bosses[higher1-1];
        higher1 -= 1;
        higher2 -= 1;
    }

    return common_boss;
}

pair<unsigned int, unsigned int> Datastructure::higher_lower_ranks(PersonID id)
{
    // return {0, 0}; // If you do not implement this, leave this return value as it is.

    if(umap.find(id) == umap.end()) {
        return {0, 0};
    }
    pair<unsigned int, unsigned int> hlr = {0, 0};
    int higher = 0;
    int current = 0;

    while(umap[id].boss != NO_ID) {
        id = umap[id].boss;
        higher += 1;
    }

    count_hlr(hlr, current, higher, id);

    return hlr;
}

PersonID Datastructure::min_salary()
{
    if(salarylist.size() == 0) {
        return NO_ID;
    }
    if(ssorted) {
        return salarylist.front();
    } else {
        return *min_element(salarylist.begin(), salarylist.end(), [this](const PersonID& a, const PersonID& b) {
            return umap[a].salary < umap[b].salary;
        });
        return salarylist.front();
    }
}

PersonID Datastructure::max_salary()
{
    if(salarylist.size() == 0) {
        return NO_ID;
    }
    if(ssorted) {
        return salarylist.back();
    } else {
        return *max_element(salarylist.begin(), salarylist.end(), [this](const PersonID& a, const PersonID& b) {
            return umap[a].salary < umap[b].salary;
        });
        return salarylist.back();
    }
}

PersonID Datastructure::median_salary()
{
    if(salarylist.size() == 0) {
        return NO_ID;
    }
    if(ssorted) {
        return salarylist[salarylist.size() / 2];
    } else {
        nth_element(salarylist.begin(), salarylist.begin() + salarylist.size() / 2, salarylist.end(), [this](const PersonID& a, const PersonID& b) {
            return umap[a].salary < umap[b].salary;
        });
        return salarylist[salarylist.size() / 2];
    }
}

PersonID Datastructure::first_quartile_salary()
{
    if(salarylist.size() == 0) {
        return NO_ID;
    }
    if(ssorted) {
        return salarylist[salarylist.size() / 4];
    } else {
        nth_element(salarylist.begin(), salarylist.begin() + salarylist.size() / 4, salarylist.end(), [this](const PersonID& a, const PersonID& b) {
            return umap[a].salary < umap[b].salary;
        });
        return salarylist[salarylist.size() / 4];
    }
}

PersonID Datastructure::third_quartile_salary()
{
    if(salarylist.size() == 0) {
        return NO_ID;
    }
    if(ssorted) {
        return salarylist[salarylist.size() * 3 / 4];
    } else {
        nth_element(salarylist.begin(), salarylist.begin() + salarylist.size() * 3 / 4, salarylist.end(), [this](const PersonID& a, const PersonID& b) {
            return umap[a].salary < umap[b].salary;
        });
        return salarylist[salarylist.size() * 3 / 4];
    }
}

void Datastructure::count_hlr(pair<unsigned int, unsigned int>& hlr,
                              int current, int higher, PersonID person) {
    if(current < higher) {
        hlr.first += 1;
    } else if(current > higher) {
        hlr.second += 1;
    }

    for(auto it : umap[person].underlings) {
        count_hlr(hlr, current + 1, higher, it);
    }
}
