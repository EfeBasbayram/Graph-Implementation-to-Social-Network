#ifndef UNTITLED_GRAPH_H
#define UNTITLED_GRAPH_H
#include "Person.h"

class Graph {

private:
    std::vector<std::pair<int, Person>> people;
public:
    void addPerson(int ID , const Person &person); // done
    const Person* getPerson(int ID) const ; // done
    friend std::ostream& operator<<(std::ostream& os, const Graph& graph); // done
    [[nodiscard]] std::vector<int> suggestFriends(int person_id, int mode) const; // done
    std::vector<int> suggestFriendsByCommonFriends(const Person *person) const; // done
    std::vector<int> suggestFriendsByOccupation(const Person *person) const; // done
    std::vector<int> suggestFriendsByAge(const Person *person) const; // done
    [[nodiscard]] int getSize() const; // done
    void degreeCentrality() const; // done
    [[nodiscard]] double clusteringCoefficient(int id) const; // done
    [[nodiscard]] std::vector<std::pair<int, Person>> getGraph() const;
    std::vector<std::vector<int>> girvanNewman(int iterations);
    double edgeWeight(const Graph &graph, int u, int v) const;
    void removeFriendship(int id1, int id2);
    [[nodiscard]] const std::vector<std::pair<int, Person>> &getPeople() const; // done
    void setPeople(const std::vector<std::pair<int, Person>> &people); // done
};


#endif //UNTITLED_GRAPH_H
