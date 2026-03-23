#include <iostream>
#include "Graph.h"
#include "utils.h"
#include <vector>

int main() {
    Graph graph = readData("C:\\social_network.csv");
    int choice;
    do {
        std::cout << "Social Network Options" << std::endl;
        std::cout << "1. Display network" << std::endl;
        std::cout << "2. Suggest friends for users based on common friends, similar occupation, or similar age" << std::endl;
        std::cout << "3. Calculate degree centrality for each user" << std::endl;
        std::cout << "4. Calculate clustering coefficient for each user" << std::endl;
        std::cout << "5. Detect communities using the Girvan-Newman algorithm" << std::endl;
        std::cout << "6. Exit the program" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::cout << graph << std::endl;
        }
        else if (choice == 2) {
            int personID, mode;
            std::cout << "Enter person ID: ";
            std::cin >> personID;
            std::cout << "Enter mode: \n1.Common Friends \n2.Similar Occupation\n3.Similar Age ";
            std::cin >> mode;
            std::vector<int> suggestedFriends = graph.suggestFriends(personID, mode);
            std::cout << "Suggested friends: ";
            for (int friendID: suggestedFriends) {
                std::cout << friendID << " ";
            }
            std::cout << std::endl;
        }
        else if (choice == 3) {
            graph.degreeCentrality();
        }
        else if (choice == 4) {
            for (const auto &person: graph.getPeople()) {
                int id = person.first;
                double coefficient = graph.clusteringCoefficient(id);
                std::cout << "Person " << id << ": Clustering coefficient: " << coefficient << std::endl;
            }
        }
        else if (choice == 5) {
            int iterations;
            std::cout << "Enter number of iterations: ";
            std::cin >> iterations;

            std::vector<std::vector<int>> communities = graph.girvanNewman(iterations);

            std::cout << "Communities: " << std::endl;
            for (const auto &community: communities) {
                std::cout << "Community: ";
                for (int member: community) {
                    std::cout << member << " ";
                }
                std::cout << std::endl;
            }
        }
        else if (choice == 6) {
            std::cout << "Exiting " << std::endl;
        }
        else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }

    } while (choice != 6);

    return 0;
}
