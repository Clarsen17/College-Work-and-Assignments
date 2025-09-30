#include <iostream>
#include <cstring>

bool starts_with(const char* s, const char* prefix) 
{
    // Calculate the length of the strings
    size_t s_len = strlen(s);
    size_t prefix_len = strlen(prefix);

    // If the prefix is longer than the string, it cannot be a prefix
    if (prefix_len > s_len) 
	{
        return false;
    }

    // Compare the beginning of 's' with 'prefix'
    // strncmp returns 0 if the two strings are equal for the first 'prefix_len' characters
    return strncmp(s, prefix, prefix_len) == 0;
}
