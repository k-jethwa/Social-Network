#include "user.h"


User:: User()  {
    id_ = 1;
    year_ = 1;
    zip_ = 1;
    name_ = "Jane Doe";

}

User::User(int id, std::string name, int year, int zip, std::set<int> friends) {
    id_ = id;
    name_ = name;
    year_ = year;
    zip_ = zip;
    friends_ = friends;
}

int User::getId() {
    return id_;
}

std::string User::getName() {
    return name_;
}
int User::getYear() {
    return year_;
}
int User::getZip() {
    return zip_;
}
std::set<int>& User::getFriends() {
    return friends_;
}

void User::addFriend(int id) {
    if (!friends_.count(id)) {
        friends_.insert(id);
    }
}

void User::deleteFriend(int id) {
    if (friends_.count(id)) {
        friends_.erase(id);
    }
}
