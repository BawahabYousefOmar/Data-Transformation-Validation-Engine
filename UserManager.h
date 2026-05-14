#pragma once

#include <string>
#include "HashMap.h" // Your custom HashMap

using namespace std;

struct UserData {
    string passwordHash;
    bool isAdmin;

    UserData() : passwordHash(""), isAdmin(false) {}
    UserData(string pass, bool admin) : passwordHash(pass), isAdmin(admin) {}
};

class UserManager {
public:
    UserManager();

    bool loadUsers(const string& filePath);
    bool registerUser(const string& username, const string& password);

    bool authenticate(const string& username, const string& password, bool& outIsAdmin) const;

    // Fast, lightweight string hashing returning a short number string
    static string hashPassword(const string& password);

private:
    HashMap<UserData> m_users;
};