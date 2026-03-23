#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>

class Person {
private:
    int ID;
    std::string name;
    int age;
    std::string gender;
    std::string occupation;
    std::vector<int> listOfFriends;

public:

    Person(int ID, std::string name, int age, std::string gender,std::string occupation, std::vector<int> listOfFriends);


    int getId() const;
    const std::string & getName() const;
    int getAge() const;
    const std::string & getGender() const;
    const std::string & getOccupation() const;
    const std::vector<int> & getListOfFriends() const;

    void setId(int id);
    void setName(const std::string& name);
    void setAge(int age);
    void setGender(const std::string& gender);
    void setOccupation(const std::string& occupation);
    void setListOfFriends(const std::vector<int>& listOfFriends);
};

#endif // PERSON_H


