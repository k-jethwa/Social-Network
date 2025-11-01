using namespace std;
#include <iostream>
#include <sstream>
#include "network.h"
#include "user.h"


int main(int argc, char *argv[]) {

    Network myNetwork;

    myNetwork.readUsers(argv[1]);
    myNetwork.readPosts(argv[2]);


    while(true) {
        cout << "1. Add a user" << endl;
        cout << "2. Add friend connection" << endl;
        cout << "3. Delete friend connection" << endl;
        cout << "4. Write user date to file" << endl;
        cout << "5. View recent posts" << endl;
        cout << "6. Exit" << endl;

        cout << "Input number to select: ";

        int num;
        cin >> num;
        cin.ignore();

        if (num == 1) {
            cout << "Enter new users full name, birth year, and zip code" << endl;
            string line;
            getline(cin, line);
            
            stringstream ss(line);
            string firstName, lastName;
            int year, zip;
            
            ss >> firstName >> lastName >> year >> zip;
            string fullName = firstName + " " + lastName;
            
            set<int> emptyFriends;
            int newId = myNetwork.numUsers();
            User* newUser = new User(newId, fullName, year, zip, emptyFriends);
            myNetwork.addUser(newUser);

        } else if (num == 2) {
            cout << "Provide two full names to add friend connection." << endl;
            string line;
            getline(cin, line);
            
            stringstream ss(line);
            string first1, last1, first2, last2;
            ss >> first1 >> last1 >> first2 >> last2;

            string name1 = first1 + " " + last1;
            string name2 = first2 + " " + last2;

            int result = myNetwork.addConnection(name1, name2);

            if (result == -1) {
                cout << "One or both users do not exist." << endl;
            }

        } else if (num == 3) {
            cout << "Enter two full names to delete friend connection" << endl;
            string line;
            getline(cin, line);
            
            stringstream ss(line);
            string first1, last1, first2, last2;
            ss >> first1 >> last1 >> first2 >> last2;

            string name1 = first1 + " " + last1;
            string name2 = first2 + " " + last2;

            int result = myNetwork.deleteConnection(name1, name2);

            if (result == -1) {
                cout << "One or both users do not exist." << endl;
            }
        } else if (num == 4) {
            cout << "Enter file name" << endl;
            string filename;
            getline(cin, filename);
            
            myNetwork.writeUsers(filename.c_str());
            cout << myNetwork.numUsers() << " users written to " << filename << endl;
        } else if (num == 5){
            cout << "Enter user's full name and number of posts to view" << endl;
            string line;
            getline(cin, line);
            stringstream ss(line);
            string firstName, lastName;
            int howMany;
            ss >> firstName >> lastName >> howMany;
            string fullName = firstName + " " + lastName;
            
            int userId = myNetwork.getId(fullName);
            if (userId == -1) {
                cout << "User does not exist." << endl;
            } else {
                string postsString = myNetwork.getPostsString(userId, howMany);
                if (postsString.empty()) {
                    cout << "No posts available for this user." << endl;
                } else {
                    cout << postsString << endl;
                }
            }
        } else {
            cout << "Exiting program" << endl;
            break;
        }
    }



}