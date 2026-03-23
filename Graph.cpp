#include "Graph.h"
#include <iostream>
#include <algorithm>


void Graph::addPerson(int ID , const Person &person){
    people.emplace_back(ID, person);
}

const Person* Graph::getPerson(int ID) const {
    for(const auto & p : people){
        if (p.first == ID) return &(p.second);
    }
    throw std::runtime_error("Person with given id not found.");
}

std::ostream& operator<<(std::ostream& os, const Graph& graph) {
    for (const auto& pair : graph.people) {
        os << "ID: " << pair.first << ", Name: " << pair.second.getName() << ", Age: " << pair.second.getAge()
           <<  ", Gender: " << pair.second.getGender() << ", Occupation: " << pair.second.getOccupation() << ", Friends: [";
        const auto& friends = pair.second.getListOfFriends();
        for (int i = 0; i < friends.size(); ++i) {
            os << friends[i];
            if (i != friends.size() - 1) {
                os << ", ";
            }
        }
        os << "]" << std::endl;
    }
    return os;
}

std::vector<int> Graph::suggestFriends(int person_id, int mode) const {
    const Person* person = getPerson(person_id);
    if (mode == 1 ) return suggestFriendsByCommonFriends( person );
    else if (mode == 2) return suggestFriendsByOccupation( person );
    else if (mode == 3 ) return suggestFriendsByAge( person ) ;
    else
    {
        std::cout<<"Invalid mode"<<std::endl;
        return{};
    }
}

std::vector<int> Graph::suggestFriendsByCommonFriends(const Person *person) const
{
    std::vector<int> suggestedFriends;
    std::vector<int> currentFriends = person->getListOfFriends();
    std::vector<int> tempFriends;
    for(const auto & p : people)
    {
        if (person->getId() != p.first && std::find(p.second.getListOfFriends().begin(), p.second.getListOfFriends().end(), person->getId()) == p.second.getListOfFriends().end())
        {
            tempFriends = p.second.getListOfFriends();
            for( int i : tempFriends )
            {
                if (std::find(currentFriends.begin(),currentFriends.end(), i) != currentFriends.end())
                {
                    suggestedFriends.emplace_back(p.first);
                    break;
                }
            }
        }
    }
    return suggestedFriends;
}

std::vector<int> Graph::suggestFriendsByOccupation(const Person *person) const {
    std::vector<int> suggestedFriends;
    std::string occupation = person->getOccupation();
    for (const auto &p : people) {
        if (person->getId() != p.first && occupation == p.second.getOccupation() && std::find(p.second.getListOfFriends().begin(), p.second.getListOfFriends().end(), person->getId()) == p.second.getListOfFriends().end()) {
            suggestedFriends.push_back(p.first);
        }
    }
    return suggestedFriends;
}


std::vector<int> Graph::suggestFriendsByAge(const Person *person) const
{
    std::vector<int> suggestedFriends;
    int currentAge = person->getAge()  , ageDifferance;
    for(const auto & p : people)
    {
        if (person->getId() != p.first && std::find(p.second.getListOfFriends().begin(), p.second.getListOfFriends().end(), person->getId()) == p.second.getListOfFriends().end())

        {
            ageDifferance = std::abs(currentAge - p.second.getAge());
            if ( ageDifferance >= 0 && ageDifferance <=3 ) suggestedFriends.emplace_back(p.first);
        }
    }
    return suggestedFriends;
}

int Graph::getSize() const{
    return people.size();
}

void Graph::degreeCentrality() const {
    for(const auto & p : people)
    {
        std::cout << "Person " << p.first << ": Degree centrality : " << p.second.getListOfFriends().size() << std::endl;
    }
}

double Graph::clusteringCoefficient(int id) const
{
    int degree = getPerson(id)->getListOfFriends().size();
    std::vector<int> currentNeighboors = getPerson(id)->getListOfFriends();
    int links = 0;

    for (int i = 0; i < degree; ++i) {
        const std::vector<int>& neighborNeighbors = getPerson(currentNeighboors[i])->getListOfFriends();
        for (int j = i + 1; j < degree; ++j) {
            if (std::find(neighborNeighbors.begin(), neighborNeighbors.end(), currentNeighboors[j]) != neighborNeighbors.end()) links++;
        }
    }
    return (2.0 * links) / (degree * (degree - 1));
}

std::vector<std::pair<int, Person>> Graph::getGraph() const {
    return people;
}


std::vector<std::vector<int>> Graph::girvanNewman(int iterations)  {
    std::vector<std::vector<int>> communities;
    Graph copyGraph = *this;

    for (int i = 0; i < iterations; i++) {
        double maxWeight = 0.0;
        std::vector<int> maxWeightEdges;

        for (const auto& pair : copyGraph.people) {
            int u = pair.first;
            for (const auto& friendID : pair.second.getListOfFriends()) {
                int v = friendID;
                double weight = edgeWeight(copyGraph, u, v);
                if (weight > maxWeight) {
                    maxWeight = weight;
                    maxWeightEdges = {u, v};
                }
            }
        }

        if (!maxWeightEdges.empty()) {
            copyGraph.removeFriendship(maxWeightEdges[0], maxWeightEdges[1]);
        }
    }

    int minID = copyGraph.people.begin()->first;
    int maxID = copyGraph.people.rbegin()->first;

    std::vector<int> community(maxID - minID + 1, -1);
    int currentCommunity = 0;

    for (const auto& pair : copyGraph.people) {
        if (community[pair.first - minID] == -1) {
            std::vector<int> members;
            members.push_back(pair.first);
            community[pair.first - minID] = currentCommunity;

            for (const auto& friendID : pair.second.getListOfFriends()) {
                if (community[friendID - minID] == -1) {
                    members.push_back(friendID);
                    community[friendID - minID] = currentCommunity;
                }
            }

            communities.push_back(members);
            currentCommunity++;
        }
    }

    return communities;
}

double Graph::edgeWeight(const Graph &graph, int u, int v) const {
    std::vector<int> personOneFriends = graph.getPerson(u)->getListOfFriends();
    std::vector<int> personTwoFriends = graph.getPerson(v)->getListOfFriends();
    int intersections = 0;
    for ( int i : personOneFriends)
    {
        for (int j : personTwoFriends )
        {
            if ( i == j ) intersections++;
        }
    }
    return intersections;
}

void Graph::removeFriendship(int id1, int id2)
{
    Person* personOne = const_cast<Person*>(getPerson(id1));
    std::vector<int> listToUpdate = personOne->getListOfFriends();
    std::vector<int> emptyList1;
    std::vector<int> emptyList2;

    for (int i : listToUpdate )
    {
        if ( i != id2) emptyList1.emplace_back(i);
    }
    personOne->setListOfFriends(emptyList1);

    Person* personTwo = const_cast<Person*>(getPerson(id2));
    listToUpdate = personTwo->getListOfFriends();
    for (int i : listToUpdate )
    {
        if ( i != id1) emptyList2.emplace_back(i);
    }
    personTwo->setListOfFriends(emptyList2);
}

const std::vector<std::pair<int, Person>> &Graph::getPeople() const {
    return people;
}

void Graph::setPeople(const std::vector<std::pair<int, Person>> &people) {
    Graph::people = people;
}






