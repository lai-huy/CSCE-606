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
 */
class Args {
private:
    /**
     * @brief The character marking a flag as a string value
     */
    static char const string_flag = '*';

    /**
     * @brief The character marking a flag as an integer value
     */
    static char const int_flag = '#';

    /**
     * @brief A std::map holding all boolean flags and their respective values
     */
    map<char, bool> boolFlags;

    /**
     * @brief A std::map holding all integer flags and their respective values
     */
    map<char, int> intFalgs;

    /**
     * @brief A std::map holding all string falgs and their respective values
     */
    map<char, string> stringFlags;

    /**
     * @brief Split a string input by a specified delimiter
     *
     * @param input string to split
     * @param delimiter character to split by
     * @return vector<string> the string split by a specified delimiter
     */
    vector<string> split(const string& input, char delimiter) {
        vector<string> result{};
        string substring{};

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

    /**
     * @brief Adds flags specified in the schema to the std::map
     *
     * @param schema schema specified
     */
    void addFlagToMap(const string& schema) {
        // find flags in schema
        vector<string> split = this->split(schema, ',');

        // loop through flags and add them to their respective maps
        for (const string& str : split) {
            const char& flag = str.at(0);
            if (str.size() == 1) {
                boolFlags.insert({flag, bool{}});
                continue;
            }
            switch (str.at(1)) {
            case string_flag:
                stringFlags.insert({flag, string{}});
                break;
            case int_flag:
                intFalgs.insert({flag, int{}});
                break;
            default:
                throw invalid_argument("Invalid flag type");
            }
        }
    }

    /**
     * @brief Initialize flag values specified in args
     *
     * @param nargs the number of arguments
     * @param args the arguments
     */
    void initializeFlags(int nargs, char** args) {
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
            else
                throw invalid_argument("The flag " + string(1, flag) + " was not specified in the schema.");
        }
    }

    /**
     * @brief Determines if a flag is a boolean flag
     *
     * @param flag flag to determine the type
     * @return true is the flag is a boolean flag
     * @return false otherwise
     */
    bool isBoolFlag(const char& flag) {
        return this->boolFlags.find(flag) != this->boolFlags.cend();
    }

    /**
     * @brief Determines if a flag is a boolean flag
     *
     * @param flag flag to determine the type
     * @return true is the flag is a string flag
     * @return false otherwise
     */
    bool isStringFlag(const char& flag) {
        return this->stringFlags.find(flag) != this->stringFlags.cend();
    }

    /**
     * @brief Determines if a flag is a boolean flag
     *
     * @param flag flag to determine the type
     * @return true is the flag is a integer flag
     * @return false otherwise
     */
    bool isIntFlag(const char& flag) {
        return this->intFalgs.find(flag) != this->intFalgs.cend();
    }
public:
    /**
     * @brief Construct a new Args object. Bilds the argument parser for the given schema and parses the given arguments.
     *
     * @param schema the schema to parse
     * @param nargs the number of args passed in
     * @param args the arguments
     * @throws std::invalid_argument if args contains a flag not specified by the schema
     */
    Args(const string& schema, int nargs, char** args) : boolFlags{map<char, bool>{}}, intFalgs{map<char, int>{}}, stringFlags{map<char, string>{}} {
        this->addFlagToMap(schema);
        this->initializeFlags(nargs, args);
    }

    /**
     * @brief Determines if the schema contains a specified flag
     *
     * @param flag flag to check in the schema
     * @return true if and only if the specified flag was present in the arguments
     * @return false otherwise
     */
    bool has(char flag) {
        if (this->isBoolFlag(flag))
            return true;
        if (this->isStringFlag(flag))
            return true;
        if (this->isIntFlag(flag))
            return true;
        return false;
    }

    /**
     * @brief returns the value (expected to be of boolean type) of the specified flag.
     *
     * @param flag flag of the boolean value to retreive
     * @return true or false depending on the value of the flag
     * @throw std::out_of_range if the flag is not defined by the schema to be a boolean
     */
    bool getBoolean(char flag) {
        return this->boolFlags.at(flag);
    }

    /**
     * @brief returns the value (expected to be of string type) of the specified flag.
     *
     * @param flag flag of the string value to retreive
     * @return string value of the flag
     * @throw std::out_of_range if the flag is not defined by the schema to be a string.
     */
    string getString(char flag) {
        return this->stringFlags.at(flag);
    }

    /**
     * @brief returns the value (expected to be of integer type) of the specified flag
     *
     * @param flag flag of the integer value to retreive
     * @return int value of the flag
     * @throw std::out_of_range if the flag is note defined by the schema to be a string.
     */
    int getInteger(char flag) {
        return this->intFalgs.at(flag);
    }
};
