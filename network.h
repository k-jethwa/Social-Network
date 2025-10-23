#ifndef NETWORK_H
#define NETWORK_H

#include "user.h"
#include <string>
#include <vector>

class Network {
private:
    std::vector<User*> users_;
public:
    // pre: none
    // post: creates an empty network
    Network();

    // pre: id is a valid index
    // post: returns a pointer to the user with the given id
    User* getUser(int id);

    // pre: u is not nullptr and user’s name/id is not already in the network
    // post: adds u to users_; number of users increases by one
    void addUser(User* u);

    // pre: s1 and s2 correspond to valid existing users and are not already connected
    // post: creates a connection between s1 and s2, returns 0 on success, -1 if not valid
    int addConnection(std::string s1, std::string s2);

    // pre: s1 and s2 correspond to valid existing users
    // post: removes the connection between s1 and s2 if it exists, returns 0 on success, -1 otherwise
    int deleteConnection(std::string s1, std::string s2);

    // pre: name is non-empty
    // post: returns id of user with the given name, or -1 if not found
    int getId(std::string name);

    // pre: none
    // post: returns total number of users in the network
    int numUsers();

    // pre: fname points to a valid file containing user data in correct format
    // post:  users_ added to network from file
    void readUsers(const char* fname);

    // pre: fname points to a writable file path
    // post: writes all user data to file
    void writeUsers(const char* fname);

    // pre: from and to are valid id numbers
    // post: returns a vector containing a shortest path of vertices from User from to user to
    std::vector<int> shortestPath(int from, int to);

    // pre: from is a valid user ID and distance is >= 0
    // post: returns the shortest path to user exact distance from user 'from' and sets 'to' to that user's ID, or -1 if such a user does not exist
    std::vector<int> distanceUser(int from, int& to, int distance);

    // pre: who is a valid user ID
    // post: returns a vector of users who have the most mutual friends with 'who'
    std::vector<int> suggestFriends(int who, int& score);

    // pre: none
    // post: returns vector of components, where each component is a vector of users who have a path to each other
    std::vector<std::vector<int>> groups();

    // pre: userID is valid, and visited[userID] is false
    // post: marks userID and all reachable unvisited users as visited and adds to the component
    void dfsHelper(int userId, std::vector<bool>& visited, std::vector<int>& component);

    
};


#endif