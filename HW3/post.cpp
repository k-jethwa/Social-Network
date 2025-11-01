#include "post.h"
#include <string>


Post::Post() {
    messageId_ = -1;
}

Post::Post(int profileID, int authorID, std::string message, int likes) {
    profileId_ = profileID;
    authorId_ = authorID;
    message_ = message;
    likes_ = likes;
    messageId_ = -1;

}
int Post::getMessageId() {
    return messageId_;
}
void Post::setMessageId(int id) {
    messageId_ = id;
}
int Post::getProfileId() {
    return profileId_;
}
int Post::getAuthorId() {
    return authorId_;
}
std::string Post::getMessage() {
    return message_;
}
int Post::getLikes() {
    return likes_;
}
std::string Post::getURL() {
    return "";
}

std::string Post::toString() {
    return message_ +  " (" + std::to_string(likes_) + " likes)"; 
}

LinkPost::LinkPost() : Post() {
    
}

LinkPost::LinkPost(int profileId, int authorId, std::string message, int likes, std::string url) : Post(profileId, authorId, message, likes) {
    url_ = url;
}
    
std::string LinkPost::getURL() {
    return url_;
}
std::string LinkPost::toString() {
    return getMessage() + " (url: " + getURL() + ") (" + std::to_string(getLikes()) + " likes)";
}
