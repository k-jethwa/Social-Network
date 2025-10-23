#include "network.h"
#include "user.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>


Network::Network() {
    users_ = std::vector<User*>();

}

User* Network::getUser(int id) {
    if (id < 0) {
        return nullptr;
    }
    return users_[id];
}

void Network::addUser(User* u) {
    users_.push_back(u);
}

int Network::getId(std::string name) {
    for (int i = 0; i < users_.size(); i++) {
        if (users_[i]->getName() == name) {
            return i;
        }
    }
    return -1;
}


int Network::addConnection(std::string s1, std::string s2) {
    int id1 = getId(s1);
    int id2 = getId(s2);

    if (id1 == -1 || id2 == -1) {
        return -1;
    }

    users_[id1] -> addFriend(id2);
    users_[id2] -> addFriend(id1);

    return 0;

}

int Network::deleteConnection(std::string s1, std::string s2) {
    int id1 = getId(s1);
    int id2 = getId(s2);

    if (id1 == -1 || id2 == -1) {
        return -1;
    }

    users_[id1] -> deleteFriend(id2);
    users_[id2] -> deleteFriend(id1);

    return 0;
}

int Network::numUsers() {
    return users_.size();
}

void Network::readUsers(const char* fname) {
    std::ifstream fileIn(fname);
    std::string line;
    
    int numUsers;
    fileIn >> numUsers;
    std::getline(fileIn, line);

    for (int i = 0; i < numUsers; i++) {
        int id;
        std::string name;
        int year, zip;
        std::set<int> friends;
        
        fileIn >> id;
        std::getline(fileIn, line);
        
        std::getline(fileIn, name);
        name = name.substr(1);
        
        std::getline(fileIn, line);
        year = std::stoi(line.substr(1));
        
        std::getline(fileIn, line);
        zip = std::stoi(line.substr(1));
        
        std::getline(fileIn, line);
        std::stringstream ss(line);
        int friendId;
        while (ss >> friendId) {
            friends.insert(friendId);
        }
        
        User* newUser = new User(id, name, year, zip, friends);
        addUser(newUser);
    }
    
    fileIn.close();

}

void Network::writeUsers(const char* fname) {
    std::ofstream fileOut(fname);
    
    fileOut << users_.size() << std::endl;
    
    for (int i = 0; i < users_.size(); i++) {
        User* user = users_[i];
        
        fileOut << user->getId() << std::endl;
        fileOut << "\t" << user->getName() << std::endl;
        fileOut << "\t" << user->getYear() << std::endl;
        fileOut << "\t" << user->getZip() << std::endl;
        fileOut << "\t";

        std::set<int>& friends = user->getFriends();
        for (int friendId : friends) {
            fileOut << friendId << " ";
        }

        fileOut << std::endl;
    }
    
    fileOut.close();
}

std::vector<int> Network::shortestPath(int from, int to) {
    if (from < 0 || from >= users_.size() || to < 0 || to >= users_.size()) {
        return std::vector<int>();
    }

    if (from == to) {
        return std::vector<int>{from};
    }

    std::queue<int> q;
    std::vector<bool> visited(users_.size(), false);
    std::vector<int> dist(users_.size(), -1);

    visited[from] = true;
    q.push(from);

    while(!q.empty()) {
        int cur = q.front();
        q.pop();

        if (cur == to) { // If user 'to' has been reached
            std::vector<int> path;
            int track = to;
            while(track != -1) { // backtrack through parent vector to get the path
                path.push_back(track);
                track = dist[track];
            }
            std::reverse(path.begin(), path.end()); // reverse the path to get the path from user 'from' to user 'to'
            return path;
        }

        std::set<int> friends = users_[cur] -> getFriends();
        for (int friendID : friends) { // explore all friends of current user
            if (!visited[friendID]) {
                visited[friendID] = true;
                dist[friendID] = cur; // store current user in connection to friendID
                q.push(friendID);
            }
        }
    } 
    return std::vector<int>();

}

std::vector<int> Network::distanceUser(int from, int& to, int distance) {
    if (from < 0 || from >= users_.size() || distance < 0) {
        to = -1;
        return std::vector<int>();
    }

    if (distance == 0) {
        to = from;
        return std::vector<int>{from};
    }

    std::queue<int> q;
    std::vector<bool> visited(users_.size(), false);
    std::vector<int> parent(users_.size(), -1);
    std::vector<int> dist(users_.size(), -1);

    q.push(from);
    visited[from] = true;
    dist[from] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        
        if (dist[current] == distance) { // found a user at target distance
            to = current;

            std::vector<int> path;
            int node = current;
            while (node != -1) { // reconstruct path by backtracking through parent vector
                path.push_back(node);
                node = parent[node];
            }
            std::reverse(path.begin(), path.end()); // reverse path because it was built backwards
            return path;
        }

        if (dist[current] > distance) {
            break;
        }

        // explore all friends of current user
        std::set<int>& friends = users_[current]->getFriends();
        for (int friendId : friends) {
            if (!visited[friendId]) {
                visited[friendId] = true;
                parent[friendId] = current; // track parent for path reconstruction
                dist[friendId] = dist[current] + 1;
                q.push(friendId); 
            }
        }
    }

    to = -1;
    return std::vector<int>();

}

std::vector<int> Network::suggestFriends(int who, int& score) {
    if (who < 0 || who >= users_.size()) {
        score = -1;
        return std::vector<int>();
    }

    std::set<int>& userFriends = users_[who] -> getFriends();
    std::map<int, int> friendScores;

    for (int f: userFriends) {
        std::set<int> friendsOfFriend = users_[f] -> getFriends();
        // evaluate each friend of friend as a potential suggestion
        for (int fr: friendsOfFriend) {
            if (fr == who) {
                continue;
            }
            if (userFriends.count(fr)) {
                continue;
            }
            friendScores[fr]++;
        }
    }

    if (friendScores.empty()) {
        score = -1;
        return std::vector<int>();
    } 

    int maxScore = 0;
    std::vector<int> res;
    // find the max score
    for (auto& it: friendScores) {
        if (maxScore < it.second) {
            maxScore = it.second;
        }
    } 
    // add users with the max score
    for (const auto& pair: friendScores) {
        if (pair.second == maxScore) {
            res.push_back(pair.first);
        }
    }

    score = maxScore;
    return res;

}

std::vector<std::vector<int>> Network::groups() {
    std::vector<std::vector<int>> components;
    std::vector<bool> visited(users_.size(), false);
    
    // starting DFS from each unvisited user
    for (int i = 0; i < users_.size(); i++) {
        if (!visited[i]) {
            std::vector<int> component;
            dfsHelper(i, visited, component); // explore entire component using DFS helper function
            components.push_back(component);
        }
    }
    
    return components;
}

void Network::dfsHelper(int userId, std::vector<bool>& visited, std::vector<int>& component) {
    visited[userId] = true;
    
    component.push_back(userId);

    std::set<int>& friends = users_[userId]->getFriends(); // get all friends of current user
    for (int friendId : friends) {
        if (!visited[friendId]) {
            dfsHelper(friendId, visited, component); // recursively visit all unvisited friends
        }
    }
}
