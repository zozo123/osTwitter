//
//  twitUser.h
//  twitClient

#ifndef twitClient_twitUser_h
#define twitClient_twitUser_h

#include <map>
#include <iostream>
#include <string>

using namespace std;
class user {
    string username;
    map<string,bool> followers;
    map<string,bool> following;
    string name;
    
    
public:
    
    user(string username):username(username) {
        followers [username] = false;
        following [username] = false;
    }
   
    bool removeFollower (string friendName);
    bool addFollower(string friendName);
    bool stopFollowing(string friendName);
    bool startFollowing(string friendName);
   
    const map<string,bool>::const_iterator getFollowers() const{
        
        return followers.begin();
        
    }
    
    const map<string,bool>::const_iterator getFollowing() const {
        
        return following.begin();
        
    }
    
    
};


#endif
