#pragma once
#include <string>
#include <stdexcept>
#include <map>
#include <vector>

using std::string;
using std::map, std::vector;
using std::invalid_argument;

/**
 * @brief
 *
 */
class Args {
private:
    static char const string_flag = '*';
    static char const int_flag = '#';
    map<char, bool> boolFlags;
    map<char, int> intFalgs;
    map<char, string> stringFlags;

    vector<string> split(const string& input, char delimiter) {
        vector<string> result;
        string substring;

        for (const char& c : input) {
            if (c == delimiter) {
                result.push_back(substring);
                substring.clear();
            } else
                substring += c;
        }

        // Adding the last substring after the loop
        result.push_back(substring);

        return result;
    }

    bool isBoolFlag(const char& flag) {
        return this->boolFlags.find(flag) != this->boolFlags.cend();
    }

    bool isStringFlag(const char& flag) {
        return this->stringFlags.find(flag) != this->stringFlags.cend();
    }

    bool isIntFlag(const char& flag) {
        return this->intFalgs.find(flag) != this->intFalgs.cend();
    }
public:
    Args(const string& schema, int nargs, char** args) : boolFlags{map<char, bool>{}}, intFalgs{map<char, int>{}}, stringFlags{map<char, string>{}} {
        // find flags in schema
        vector<string> split = this->split(schema, ',');

        // loop through flags and add them to their respective maps
        for (const string& str : split) {
            const char& flag = str.at(0);
            if (str.size() == 1) {
                boolFlags.insert({flag, false});
                continue;
            }
            switch (str.at(1)) {
            case string_flag:
                stringFlags.insert({flag, string()});
                break;
            case int_flag:
                intFalgs.insert({flag, 0});
                break;
            default:
                break;
            }
        }

        // initialize flags
        for (int i = 0; i < nargs; ++i) {
            string arg(args[i]);
            const char& flag = arg.at(1);
            const string value = arg.substr(2);
            if (this->isBoolFlag(flag))
                this->boolFlags.at(flag) = true;
            else if (this->isIntFlag(flag))
                this->intFalgs.at(flag) = std::stoi(value);
            else if (this->isStringFlag(flag))
                this->stringFlags.at(flag) = value;
        }
    }

    bool has(char flag) {
        if (this->isBoolFlag(flag))
            return true;
        if (this->isStringFlag(flag))
            return true;
        if (this->isIntFlag(flag))
            return true;
        return false;
    }

    bool getBoolean(char flag) {
        return this->boolFlags.at(flag);
    }

    string getString(char flag) {
        return this->stringFlags.at(flag);
    }

    int getInteger(char flag) {
        return this->intFalgs.at(flag);
    }
};