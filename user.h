#ifndef USER_H
#define USER_H

#include <set>
#include <string>

class User {
private:
    int id_;
    std::string name_;
    int year_;
    int zip_;
    std::set<int> friends_;

public:
    // pre: none
    // post: creates a user with default values
    User();

    // pre: none
    // post: creates a user with the given id, name, year, zip, and set of friends
    User(int id, std::string name, int year, int zip, std::set<int> friends);

    // pre: none
    // post: returns current user's id
    int getId();

    // pre: none
    // post: returns current user's name
    std::string getName();

    // pre: none
    // post: returns current user's birth year
    int getYear();

    // pre: none
    // post: returns current user's zip code
    int getZip();

    // pre: none
    // post: returns a reference to the set of current user's friends
    std::set<int>& getFriends();

    // pre: id is valid and not already in this user's friends_ set
    // post: adds id to this user's friends_ set
    void addFriend(int id);

    // pre: id exists in this user's friends_ set
    // post: removes id from this user's friends_ set
    void deleteFriend(int id);
};

#endif