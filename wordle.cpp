#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
// Helper function prototype
void wordleHelper(string& current, const string& in, string remaining_floating, const set<string>& dict, set<string>& results, size_t pos);

// Definition of primary wordle function
std::set<std::string> wordle( const std::string& in, const std::string& floating, const std::set<std::string>& dict)
{
     set<string> results;
    string current = in;
    
    // Call recursive helper function starting at position 0
    wordleHelper(current, in, floating, dict, results, 0);
    
    return results;
}

// Recursive helper function to generate all possible words
void wordleHelper(string& current, const string& in, string remaining_floating, const set<string>& dict, set<string>& results, size_t pos){
    
    if (pos == in.length()) {
        
        if (dict.find(current) != dict.end()) {
            results.insert(current);
        }
        return;
    }
    
    
    if (in[pos] != '-') {
        wordleHelper(current, in, remaining_floating, dict, results, pos + 1);
        return;
    }
    
   
    size_t blanks_remaining = 0;
    for (size_t i = pos; i < in.length(); i++) {
        if (in[i] == '-') {
            blanks_remaining++;
        }
    }
    
   
    for (char c = 'a'; c <= 'z'; c++) {
      
        current[pos] = c;
        
       
        size_t float_index = remaining_floating.find(c);
        string new_remaining = remaining_floating;
        
        if (float_index != string::npos) {
            
            new_remaining.erase(float_index, 1);
        }
        
        
        if (new_remaining.length() <= blanks_remaining - 1) {
            wordleHelper(current, in, new_remaining, dict, results, pos + 1);
        }
    }
    
   
    current[pos] = '-';
}
