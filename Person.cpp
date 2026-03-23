#include "Person.h"

Person::Person(int ID, std::string name, int age, std::string gender,std::string occupation, std::vector<int> listOfFriends)
{
    setId(ID);
    setName(name);
    setAge(age);
    setGender(gender);
    setOccupation(occupation);
    setListOfFriends(listOfFriends);
}

int Person::getId() const {
    return ID;
}

void Person::setId(int ID) {
    this->ID = ID;
}

const std::string & Person::getName() const {
    return name;
}

void Person::setName(const std::string& name) {
    this->name = name;
}

int Person::getAge() const {
    return age;
}

void Person::setAge(int age) {
    this->age = age;
}

const std::string & Person::getGender() const {
    return gender;
}

void Person::setGender(const std::string& gender) {
    this->gender = gender;
}
const std::string & Person::getOccupation() const {
    return occupation;
}

void Person::setOccupation(const std::string& occupation) {
    this->occupation = occupation;
}

const std::vector<int> & Person::getListOfFriends() const {
    return listOfFriends;
}

void Person::setListOfFriends(const std::vector<int>& listOfFriends) {
    this->listOfFriends = listOfFriends;
}
