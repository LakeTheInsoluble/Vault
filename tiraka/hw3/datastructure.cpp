// Definition of Datastructure class, hw3 of TIE-20100/TIE-20106

#include "datastructure.hpp"

#include <algorithm>
#include <deque>
#include <limits>
#include <queue>

// For debug
#include <iostream>
using std::cerr;
using std::endl;

#include <random>
using std::minstd_rand;
using std::uniform_int_distribution;

minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

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

        mst = false;
        hierarchy = false;

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
        for(auto it : umap[id].friends) {
            umap[it.first].friends.erase(id);
        }
        // Poistetaan itse työntekijä listoilta.
        salarylist.erase(remove(salarylist.begin(), salarylist.end(), id), salarylist.end());
        alphalist.erase(remove(alphalist.begin(), alphalist.end(), id), alphalist.end());
        umap.erase(id);
    }
    mst = false;
    hierarchy = false;
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
    //PersonID temp = bossid;
    if(umap.find(id) != umap.end() && umap.find(bossid) != umap.end()) {
//        while(umap[temp].boss != NO_ID && temp != id) {
//            temp = umap[temp].boss;
//        }
//        if(temp != id) {
//            umap[id].boss = bossid;
//            umap[bossid].underlings.push_back(id);
//            umap[bossid].usorted = false;
//        }
        umap[id].boss = bossid;
        umap[bossid].underlings.push_back(id);
        umap[bossid].usorted = false;
    }
    hierarchy = false;
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
    // return NO_ID;
    // Replace this with the actual implementation, if any
    // If you do not implement this, leave this return value as it is.

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
    // return {0, 0};
    // Replace this with the actual implementation, if any
    // If you do not implement this, leave this return value as it is.

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

// hw2 additional functions

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

// After this are the new operations of hw3
// NOTE!!! Add all your new hw3 code here below these comments (to keep it
// separated from old hw2 code).
void Datastructure::add_friendship(PersonID id, PersonID friendid, Cost cost)
{
    if(umap.find(id) != umap.end() && umap.find(friendid) != umap.end() && cost >= 0) {
        if(umap.find(id) != umap.end() && umap.find(friendid) != umap.end()) {
            umap[id].friends[friendid] = cost;
            umap[friendid].friends[id] = cost;
        }
    }
    mst = false;
}

void Datastructure::remove_friendship(PersonID id, PersonID friendid)
{
    if(umap.find(id) != umap.end() && umap.find(friendid) != umap.end()) {
        umap[id].friends.erase(friendid);
        umap[friendid].friends.erase(id);
    }
    mst = false;
}

vector<pair<PersonID, Cost>> Datastructure::get_friends(PersonID id)
{
    //return {}; // Replace this with the actual implementation
    if(umap.find(id) != umap.end()) {
        vector<pair<PersonID, Cost>> ret;
        for(auto it : umap[id].friends) {
            pair<PersonID, Cost> p;
            p.first = it.first;
            p.second = it.second;
            ret.push_back(p);
        }
        return ret;
    }
    return {};
}

vector<pair<PersonID, PersonID>> Datastructure::all_friendships()
{
    //return {}; // Replace this with the actual implementation
    vector<PersonID> ids = personnel_alphabetically();
    vector<pair<PersonID, PersonID>> edges;
    for(auto idit1 : ids) {
        for(auto idit2 : umap[idit1].friends){
            pair<PersonID, PersonID> edge;
            if(idit1 < idit2.first) {
                edge.first = idit1;
                edge.second = idit2.first;
                edges.push_back(edge);
            }
        }
    }
    sort(edges.begin(), edges.end(), [](const std::pair<PersonID,PersonID> &left, const std::pair<PersonID,PersonID> &right) {
        if(left.first < right.first) {
            return true;
        } else if (left.first == right.first) {
            return left.second < right.second;
        }
        return false;
    });
    return edges;
}

vector<pair<PersonID, Cost> > Datastructure::shortest_friendpath(PersonID fromid, PersonID toid) {
    //return {}; // Replace this with the actual implementation
    std::deque<PersonID> que;
    PersonID temp;
    for(auto it : umap) {
        umap[it.first].visited = false;
    }
    umap[fromid].visited = true;
    umap[fromid].last = NO_ID;
    que.push_back(fromid);
    while(!que.empty()) {
        temp = que.front();
        que.pop_front();
        if(temp == toid) {
            vector<pair<PersonID, Cost>> path;
            while(umap[temp].last != NO_ID) {
                pair<PersonID, Cost> p;
                p.first = temp;
                p.second = umap[temp].cost;
                path.push_back(p);
                temp = umap[temp].last;
            }
            reverse(path.begin(), path.end());
            return path;
        }
        for(auto it : umap[temp].friends) {
            if(!umap[it.first].visited) {
                umap[it.first].visited = true;
                umap[it.first].last = temp;
                umap[it.first].cost = it.second;
                que.push_back(it.first);
            }
        }
    }
    return {};
}

bool Datastructure::check_boss_hierarchy()
{
    // return false; // Replace this with the actual implementation

    if(umap.size() < 3 || hierarchy) {
        return true;
    }
    unsigned int size = 0;
    std::deque<PersonID> que;
    PersonID temp = (*(umap.begin())).first;
    for(auto it : umap) {
        umap[it.first].visited = false;
        umap[temp].last = NO_ID;
    }
    que.push_back(temp);
    while(!que.empty()) {
        temp = que.front();
        que.pop_front();
        if(umap[temp].visited == true) {
            return false;
        }
        umap[temp].visited = true;
        size++;
        for(auto it : umap[temp].underlings) {
            if(it != umap[temp].last) {
                umap[it].last = temp;
                que.push_back(it);
            }
        }
        if(umap[temp].boss != NO_ID && umap[temp].boss != umap[temp].last) {
            umap[umap[temp].boss].last = temp;
            que.push_back(umap[temp].boss);
        }
    }

    if(size == umap.size()) {
        hierarchy = true;
        return true;
    }
    return false;

}

vector<pair<PersonID, Cost>> Datastructure::cheapest_friendpath(PersonID fromid, PersonID toid)
{
    // return {}; // Replace this with the actual implementation

    std::priority_queue<pair<const PersonID, Person>*, vector<pair<const PersonID, Person>*>, compare_costs> pq;
    pair<const PersonID, Person>* ptr;
    PersonID temp;

    for(auto it : umap) {
        umap[it.first].visited = false;
        umap[it.first].last = NO_ID;
        umap[it.first].distance = std::numeric_limits<int>::max();
    }
    umap[fromid].visited = true;
    umap[fromid].distance = 0;
    pq.push(&*umap.find(fromid));

    while(!pq.empty()) {
        ptr = pq.top();
        temp = ptr->first;
        pq.pop();
        if(temp == toid) {
            while(umap[temp].last != NO_ID) {
                vector<pair<PersonID, Cost>> path;
                while(umap[temp].last != NO_ID) {
                    pair<PersonID, Cost> p;
                    p.first = temp;
                    p.second = umap[temp].cost;
                    path.push_back(p);
                    temp = umap[temp].last;
                }
                reverse(path.begin(), path.end());
                while(!pq.empty()) {
                    pq.pop();
                }
                return path;
            }
        }
        for(auto it : umap[temp].friends) {
            if(umap[it.first].visited == false) {
                umap[it.first].visited = true;
                umap[it.first].cost = umap[temp].friends[it.first];
                pq.push(&*umap.find(it.first));
            }
            relax(temp, it.first);
        }
    }
    return {};
}

void Datastructure::relax(PersonID s, PersonID t) {
    if(umap[t].distance > umap[s].distance + umap[s].friends[t]) {
        umap[t].distance = umap[s].distance + umap[s].friends[t];
        umap[t].last = s;
        umap[t].cost = umap[t].friends[s];
    }
}

pair<unsigned int, Cost> Datastructure::leave_cheapest_friendforest()
{
    // return {}; // Replace this with the actual implementation

    Cost cost = 0;
    unsigned int edges = 0;
    if(!mst) {
        std::priority_queue<edge, vector<edge>, compare_edges> pq;
        edge temp;
        for(auto it1 : umap) {
            for(auto it2 : umap[it1.first].friends) {
                // Tällä kikalla jokainen reuna tulee vain kerran.
                if(it1.first < it2.first) {
                     edge e;
                     e.cost = umap[it1.first].friends[it2.first];
                     e.a = it1.first;
                     e.b = it2.first;
                     pq.push(e);
                }
            }
        }
        for(auto it : umap) {
            umap[it.first].friends.clear();
        }
        while(!pq.empty()) {
            temp = pq.top();
            pq.pop();
            umap[temp.a].friends[temp.b] = temp.cost;
            umap[temp.b].friends[temp.a] = temp.cost;
            edges++;
            if(check_for_cycles(temp.a)) {
                umap[temp.a].friends.erase(temp.b);
                umap[temp.b].friends.erase(temp.a);
                edges--;
            }
        }
    } else {
        for(auto it1 : umap) {
            for(auto it2 : umap[it1.first].friends) {
                if(it1.first < it2.first) {
                    edges++;
                }
            }
        }
    }
    mst = true;
    for(auto it1 : umap) {
        for(auto it2 : umap[it1.first].friends) {
            if(it1.first < it2.first) {
                cost += umap[it1.first].friends[it2.first];
            }
        }
    }
    pair<unsigned int, Cost> p;
    p.first = umap.size()-edges;
    p.second = cost;

    return p;
}

bool Datastructure::check_for_cycles(const PersonID& p) {
    std::deque<PersonID> que;
    PersonID temp = p;
    for(auto it : umap) {
        umap[it.first].visited = false;
        umap[temp].last = NO_ID;
    }
    que.push_back(temp);
    while(!que.empty()) {
        temp = que.front();
        que.pop_front();
        if(umap[temp].visited == true) {
            return true;
        }
        umap[temp].visited = true;
        for(auto it : umap[temp].friends) {
            if(it.first != umap[temp].last) {
                umap[it.first].last = temp;
                que.push_back(it.first);
            }
        }
    }
    return false;
}
