#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
using namespace std;

map<char, set<char>> firstSet, followSet;
map<char, vector<string>> grammar;
set<char> nonTerminals, terminals;

void findFirst(char ch);
void findFollow(char ch);

void computeFirst() {
    for (auto nt : nonTerminals)
        findFirst(nt);
}

void computeFollow(char startSymbol) {
    for (auto nt : nonTerminals)
        findFollow(nt);

    followSet[startSymbol].insert('$');  // Assuming start symbol has '$' in its follow set
}

void findFirst(char ch) {
    if (!firstSet[ch].empty())  // If already calculated
        return;

    for (auto prod : grammar[ch]) {
        for (int i = 0; i < prod.length(); ++i) {
            char symbol = prod[i];
            if (isupper(symbol)) {
                findFirst(symbol);  // Recursive call for non-terminal
                firstSet[ch].insert(firstSet[symbol].begin(), firstSet[symbol].end());
                if (firstSet[symbol].find('ε') == firstSet[symbol].end())
                    break;
            } else {
                firstSet[ch].insert(symbol);  // Terminal or epsilon
                break;
            }
        }
    }
}

void findFollow(char ch) {
    if (!followSet[ch].empty())  // If already calculated
        return;

    for (auto& [lhs, productions] : grammar) {
        for (auto prod : productions) {
            for (int i = 0; i < prod.length(); ++i) {
                if (prod[i] == ch) {
                    if (i + 1 < prod.length()) {
                        char nextSymbol = prod[i + 1];
                        if (isupper(nextSymbol)) {
                            followSet[ch].insert(firstSet[nextSymbol].begin(), firstSet[nextSymbol].end());
                            followSet[ch].erase('ε');
                            if (firstSet[nextSymbol].find('ε') != firstSet[nextSymbol].end())
                                followSet[ch].insert(followSet[lhs].begin(), followSet[lhs].end());
                        } else {
                            followSet[ch].insert(nextSymbol);
                        }
                    } else {
                        followSet[ch].insert(followSet[lhs].begin(), followSet[lhs].end());
                    }
                }
            }
        }
    }
}

int main() {
    int n;
    char startSymbol;
    cout << "Enter the number of productions: ";
    cin >> n;
    cout << "Enter the productions (e.g., E -> E+T | T):\n";
    
    for (int i = 0; i < n; ++i) {
        char lhs;
        string rhs;
        cout << "Enter production " << i + 1 << ": ";
        cin >> lhs >> rhs;
        nonTerminals.insert(lhs);
        grammar[lhs].push_back(rhs);

        for (char c : rhs) {
            if (!isupper(c) && c != 'ε')  // Terminal symbols
                terminals.insert(c);
        }
    }
    
    cout << "Enter the start symbol: ";
    cin >> startSymbol;
    
    computeFirst();
    computeFollow(startSymbol);

    cout << "\nFirst Sets:\n";
    for (auto nt : nonTerminals) {
        cout << "First(" << nt << ") = { ";
        for (auto f : firstSet[nt])
            cout << f << " ";
        cout << "}\n";
    }

    cout << "\nFollow Sets:\n";
    for (auto nt : nonTerminals) {
        cout << "Follow(" << nt << ") = { ";
        for (auto f : followSet[nt])
            cout << f << " ";
        cout << "}\n";
    }

    return 0;
}
