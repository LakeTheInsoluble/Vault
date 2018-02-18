// Definition of Datastructure class, hw3 of TIE-20100/TIE-20106

#ifndef DATASTRUCTURE_HPP
#define DATASTRUCTURE_HPP

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <utility>
using std::pair;

#include <unordered_map>
#include <map>

#include <queue>

using PersonID = string;
PersonID const NO_ID = "";

using Salary = int;
Salary const NO_SALARY = -1;

using Cost = int;
Cost const NO_COST = -1;

struct Person {
    string name;
    string title;
    int salary;
    PersonID boss;
    vector<PersonID> underlings;
    bool usorted;
    std::map<PersonID, Cost> friends;
    bool visited;
    PersonID last;
    Cost cost;
    Cost distance;
};

// Dijkstran algoritmin prioriteettijonon vertailija
struct compare_costs {
    bool operator()(const pair<const PersonID, Person>* l, const pair<const PersonID, Person>* r) {
        return l->second.distance > r->second.distance;
    }
};

// Kruskalin algoritmissa käyttämäni structit.
struct edge {
    int cost;
    PersonID a;
    PersonID b;
};
struct compare_edges{
    bool operator()(const edge& l, const edge& r) {
        return l.cost > r.cost;
    }
};

class Datastructure
{
public:
    Datastructure();
    ~Datastructure();

    void add_person(string name, PersonID id, string title, Salary salary);
    void remove_person(PersonID id);

    string get_name(PersonID id);
    string get_title(PersonID id);
    Salary get_salary(PersonID id);
    vector<PersonID> find_persons(string name);
    vector<PersonID> personnel_with_title(string title);

    void change_name(PersonID id, string new_name);
    void change_salary(PersonID id, Salary new_salary);

    void add_boss(PersonID id, PersonID bossid);

    unsigned int size();
    void clear();

    vector<PersonID> underlings(PersonID id);
    vector<PersonID> personnel_alphabetically();
    vector<PersonID> personnel_salary_order();

    PersonID find_ceo();
    PersonID nearest_common_boss(PersonID id1, PersonID id2);
    pair<unsigned int, unsigned int> higher_lower_ranks(PersonID id);

    PersonID min_salary();
    PersonID max_salary();

    PersonID median_salary();
    PersonID first_quartile_salary();
    PersonID third_quartile_salary();

    // After this are the new operations of hw3
    void add_friendship(PersonID id, PersonID friendid, Cost cost);
    void remove_friendship(PersonID id, PersonID friendid);
    vector<pair<PersonID, Cost>> get_friends(PersonID id);
    vector<pair<PersonID, PersonID>> all_friendships();

    bool check_boss_hierarchy();
    vector<pair<PersonID, Cost>> shortest_friendpath(PersonID fromid, PersonID toid);
    vector<pair<PersonID, Cost>> cheapest_friendpath(PersonID fromid, PersonID toid);
    pair<unsigned int, Cost> leave_cheapest_friendforest();

private:
    // Add your implementation here

    std::unordered_map<string, Person> umap;

    vector<PersonID> alphalist;
    vector<PersonID> salarylist;

    PersonID ceo;

    bool asorted;
    bool ssorted;

    bool mst;
    bool hierarchy;

    // Laskee ylemmät ja alemmat työntekijät rekursiivisesti käyden läpi kaikki työntekijät ylhäältä alaspäin.
    void count_hlr(pair<unsigned int, unsigned int>& hlr, int current, int higher, PersonID person);

    // Dijkstran algoritmia varten uuden distancen laskeminen.
    void relax(PersonID s, PersonID t);

    // Syklien tarkastus kruskalin algoritmille.
    bool check_for_cycles(const PersonID &p);

};

#endif // DATASTRUCTURE_HPP
