#ifndef GRAMMAR_HPP
#define GRAMMAR_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

class Grammar
{
private:
    /* data */
    string startSymbol;
    map<string, vector<string>> grammar;
    set<string> terminals;
    set<string> nonTerminals;

public:
    Grammar();
    Grammar(string filename);
    string getStartSymbol();
    string getAugmentedStartSymbol();
    map<string, vector<string>> getGrammarMap();
    void printMapInJSONFormat();
    // Getting augmented grammar
    map<string, vector<string>> getAugmentedGrammarMap();
    void printGrammar();
    void printAugmentedGrammar();
    void findTerminals();
    void findNonTerminals();
    void printTerminals();
    void printNonTerminals();
    // ~Grammar();
};

Grammar::Grammar()
{
}

Grammar::Grammar(string filename)
{
    ifstream fin(filename);
    if (!fin)
    {
        cout << "Error opening file!" << endl;
        return;
    }
    else
    {
        string line;
        while (getline(fin, line))
        {
            if (startSymbol == "")
                startSymbol = line.substr(0, line.find("->"));
            string key = line.substr(0, line.find("->"));
            string value = line.substr(line.find("->") + 2, line.length());
            grammar[key].push_back(value);
        }
    }
}

string Grammar::getStartSymbol()
{
    return startSymbol;
}

string Grammar::getAugmentedStartSymbol()
{
    return startSymbol + "\'";
}

map<string, vector<string>> Grammar::getGrammarMap()
{
    return grammar;
}

void Grammar::printMapInJSONFormat()
{
    cout << "{" << endl;
    for (auto it = grammar.begin(); it != grammar.end(); it++)
    {
        cout << "\t\"" << it->first << "\": [";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            if (it2 != it->second.end() - 1)
                cout << "\"" << *it2 << "\", ";
            else
                cout << "\"" << *it2 << "\"";
        }
        cout << "]," << endl;
    }
    cout << "}" << endl;
}

// Getting augmented grammar
map<string, vector<string>> Grammar::getAugmentedGrammarMap()
{
    map<string, vector<string>> augmentedGrammar = grammar;
    augmentedGrammar[startSymbol + "'"].push_back(startSymbol);
    return augmentedGrammar;
}

void Grammar::printGrammar()
{
    for (auto it = grammar.begin(); it != grammar.end(); it++)
    {
        cout << it->first << " -> ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            if (it2 != it->second.end() - 1)
                cout << *it2 << " | ";
            else
                cout << *it2;
        }
        cout << endl;
    }
}

void Grammar::printAugmentedGrammar()
{
    map<string, vector<string>> augmentedGrammar = getAugmentedGrammarMap();
    for (auto it = augmentedGrammar.begin(); it != augmentedGrammar.end(); it++)
    {
        cout << it->first << " -> ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            if (it2 != it->second.end() - 1)
                cout << *it2 << " | ";
            else
                cout << *it2;
        }
        cout << endl;
    }
}

void Grammar::findTerminals()
{
    for (auto it = grammar.begin(); it != grammar.end(); it++)
    {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            string value = *it2;
            for (int i = 0; i < value.length(); i++)
            {
                if (value[i] >= 'a' && value[i] <= 'z')
                {
                    string terminal = "";
                    terminal += value[i];
                    terminals.insert(terminal);
                }
            }
        }
    }
}

void Grammar::findNonTerminals()
{
    for (auto it = grammar.begin(); it != grammar.end(); it++)
    {
        nonTerminals.insert(it->first);
    }
}

void Grammar::printTerminals()
{
    for (auto it = terminals.begin(); it != terminals.end(); it++)
        cout << *it << " ";
    cout << endl;
}

void Grammar::printNonTerminals()
{
    for (auto it = nonTerminals.begin(); it != nonTerminals.end(); it++)
        cout << *it << " ";
    cout << endl;
}

#endif