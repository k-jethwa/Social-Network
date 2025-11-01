#ifndef POST_H
#define POST_H

#include <string>


class Post {
private:
    int messageId_;
    int profileId_;
    int authorId_;
    std::string message_;
    int likes_;

public:
    // pre: none
    // post: creates a Post with messageId_ = -1
    Post();

    // pre: profileID >= 0, authorID >= 0, likes >= 0
    // post: creates a Post with given values and messageId_ = -1
    Post(int profileID, int authorID, std::string message, int likes);

    // pre: none
    // post: returns the messageId_
    int getMessageId();

    // pre: id >= 0
    // post: sets messageId_ to id
    void setMessageId(int id);

    // pre: none
    // post: returns the profileId_
    int getProfileId();

    // pre: none
    // post: returns the authorId_
    int getAuthorId();

    // pre: none
    // post: returns the message_
    std::string getMessage();

    // pre: none
    // post: returns the likes_
    int getLikes();

    // pre: none
    // post: returns empty string for regular Post
    virtual std::string getURL();

    // pre: none
    // post: returns string representation: "message (X likes)"
    virtual std::string toString();

};


class LinkPost: public Post {
private:
    std::string url_;
public:

    // pre: none
    // post: creates a LinkPost with default Post values and empty url_
    LinkPost();

    // pre: profileId >= 0, authorId >= 0, likes >= 0
    // post: creates a LinkPost with given values including url
    LinkPost(int profileId, int authorId, std::string message, int likes, std::string url);

    // pre: none
    // post: returns the url_
    std::string getURL();

    // pre: none
    // post: returns string representation: "message (url: URL) (X likes)"
    std::string toString();

};

#endif