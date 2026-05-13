#include "UserManager.h"
#include <fstream>

using namespace std;

UserManager::UserManager() : m_users(16) {
}

// Simple hash algorithm that generates a numeric string (max 10 characters)
string UserManager::hashPassword(const string& password) {
    unsigned int hash = 5381;
    for (int i = 0; i < password.length(); i++) {
        hash = ((hash << 5) + hash) + password[i]; // hash * 33 + character
    }

    
    return to_string(hash);
}

bool UserManager::loadUsers(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        return false;
    }

    string username, passHash, role;

    // Read word by word directly from the file (Format: user passHash role)
    while (file >> username >> passHash >> role) {

        // Skip comments if the line starts with '#'
        if (username[0] == '#') {
            string dummy;
            getline(file, dummy); // skip the rest of the line
            continue;
        }

        bool isAdmin = false;
        if (role == "admin" || role == "Admin") {
            isAdmin = true;
        }

        // Add to your custom HashMap
        m_users.put(username, UserData(passHash, isAdmin));
    }

    file.close();
    return true;
}

bool UserManager::registerUser(const string& username, const string& password) {
    // 1. Check if user already exists using your HashMap
    if (m_users.contains(username)) {
        return false;
    }

    // 2. Hash and add as a worker
    string hashedPass = hashPassword(password);
    m_users.put(username, UserData(hashedPass, false));

    // 3. Append to file
    ofstream file("users.txt", ios::app);
    if (file.is_open()) {
        file << "\n" << username << " " << hashedPass << " worker";
        file.close();
        return true;
    }
    return false;
}

bool UserManager::authenticate(const string& username, const string& password, bool& outIsAdmin) const {
    UserData data;

    // Find the username in the HashMap
    if (m_users.get(username, data)) {

        // Hash inputted password and check if it matches the stored numeric hash
        if (hashPassword(password) == data.passwordHash) {
            outIsAdmin = data.isAdmin;
            return true;
        }
    }
    return false;
}