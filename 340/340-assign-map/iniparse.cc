//Collen Larsne z1930118 
//CSCI 340-1 340-assign-map - iniparse.cc


// This will be compiled to iniparse.o and linked in when needed by make.

#include "settings.h"
#include "iniparse.h"
#include <sstream>
#include <iostream>
#include <algorithm>

/**
 * @brief Adds a section to the INI configuration.
 * 
 * @param config The INI_CONFIG to add the section to.
 * @param section The name of the section to add.
 */
void add_ini_section(INI_CONFIG & config, const std::string &section) {
    // If section does not exist, create it as an empty map
    config[section];
}

/**
 * @brief Removes a section from the INI configuration.
 * 
 * @param config The INI_CONFIG to remove the section from.
 * @param section The name of the section to remove.
 * @return int The number of sections removed (1 if successful, 0 otherwise).
 */
int remove_ini_section(INI_CONFIG & config, const std::string &section) {
    return config.erase(section);
}

/**
 * @brief Retrieves the value of a key from a specific section in the INI configuration.
 * 
 * @param config The INI_CONFIG to search within.
 * @param section The name of the section containing the key.
 * @param key The key whose value is to be retrieved.
 * @return std::string The value associated with the key, or an empty string if not found.
 */
std::string get_ini_key(const INI_CONFIG &config, const std::string &section, const std::string &key) {
    auto sec_it = config.find(section);
    if (sec_it != config.end()) {
        auto key_it = sec_it->second.find(key);
        if (key_it != sec_it->second.end()) {
            return key_it->second;
        }
    }
    return ""; // Key or section not found
}

/**
 * @brief Sets the value of a key in a specific section of the INI configuration.
 * 
 * @param config The INI_CONFIG to modify.
 * @param section The name of the section containing the key.
 * @param key The key whose value is to be set.
 * @param value The value to set for the key.
 */
void set_ini_key(INI_CONFIG &config, const std::string &section, const std::string &key, const std::string & value) {
    config[section][key] = value;
}

/**
 * @brief Removes a key from a specific section in the INI configuration.
 * 
 * @param config The INI_CONFIG to modify.
 * @param section The name of the section containing the key.
 * @param key The key to remove.
 * @return int The number of keys removed (1 if successful, 0 otherwise).
 */
int remove_ini_key(INI_CONFIG &config, const std::string &section, const std::string &key) {
    auto sec_it = config.find(section);
    if (sec_it != config.end()) {
        return sec_it->second.erase(key);
    }
    return 0;
}

/**
 * @brief Reads an INI configuration from an input stream.
 * 
 * @param input The input stream to read from.
 * @param verbosity The verbosity level for debug information.
 * @return INI_CONFIG The parsed INI configuration.
 */
INI_CONFIG read_ini(std::istream &input, int verbosity) {
    INI_CONFIG config;
    std::string line;
    std::string current_section;
    int line_num = 0;

    while (std::getline(input, line)) {
        ++line_num;

        // Trim leading and trailing whitespace
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        // Ignore empty lines or comments
        if (line.empty() || line[0] == ';') continue;

        if (verbosity >= 2) {
            std::cout << "Line " << line_num << ": " << line << std::endl;
        }

        // Section header
        if (line[0] == '[') {
            size_t close_bracket = line.find(']');
            if (close_bracket != std::string::npos) {
                current_section = line.substr(1, close_bracket - 1);
                if (verbosity >= 1) {
                    std::cout << "Starting section [" << current_section << "]" << std::endl;
                }
                add_ini_section(config, current_section);
            } else {
                std::cerr << "Error: Invalid section header on line " << line_num << std::endl;
            }
        }
        // Key-value pair
        else {
            size_t equals_pos = line.find('=');
            if (equals_pos != std::string::npos && !current_section.empty()) {
                std::string key = line.substr(0, equals_pos);
                std::string value = line.substr(equals_pos + 1);

                // Trim key and value
                key.erase(0, key.find_first_not_of(" \t"));
                key.erase(key.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t"));
                value.erase(value.find_last_not_of(" \t") + 1);

                if (verbosity >= 1) {
                    std::cout << "Detected key: " << key << " = " << value << " in section [" << current_section << "]" << std::endl;
                }

                set_ini_key(config, current_section, key, value);
            } else {
                std::cerr << "Error: Invalid key-value pair on line " << line_num << std::endl;
            }
        }
    }

    return config;
}

/**
 * @brief Writes an INI configuration to an output stream.
 * 
 * @param ost The output stream to write to.
 * @param config The INI_CONFIG to write.
 * @return true If the writing was successful.
 */
bool write_ini(std::ostream &ost, const INI_CONFIG &config) {
    for (const auto &section : config) {
        if (!section.second.empty()) {
            ost << "[" << section.first << "]\n";
            for (const auto &pair : section.second) {
                ost << pair.first << "=" << pair.second << "\n";
            }
            ost << "\n"; // Add a newline between sections
        }
    }
    return true;
}

/**
 * @brief Prints the INI configuration in a readable format.
 * 
 * @param ost The output stream to print to.
 * @param config The INI_CONFIG to print.
 */
void print_ini(std::ostream &ost, const INI_CONFIG &config) {
    if (config.empty()) {
        ost << "Configuration is empty. Nothing to print\n\n";  // Add an extra newline
        return;
    }

    for (const auto &section : config) {
        if (section.second.empty()) {
            ost << "Section \"" << section.first << "\" is empty\n";
        } else {
            for (const auto &pair : section.second) {
                // Add an extra space before the tab to match expected output format
                ost << section.first << "." << pair.first << " \t= \"" << pair.second << "\"\n";
            }
        }
    }
    ost << std::endl;
}

