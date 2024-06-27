#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

vector<string> generateAdjacentWords(string& word, unordered_set<string>& wordSet) {
    vector<string> adjacentWords;
    for (size_t i = 0; i < word.size(); ++i) {
        for (char letter = 'a'; letter <= 'z'; ++letter) {
            if (letter != word[i]) {
                string newWord = word;
                newWord[i] = letter;
                if (wordSet.find(newWord) != wordSet.end()) {
                    adjacentWords.push_back(newWord);
                }
            }
        }
    }
    return adjacentWords;
}

unordered_map<string, vector<string>> buildAdjacencyList(vector<string>& words) {
    unordered_set<string> wordSet(words.begin(), words.end());
    unordered_map<string, vector<string>> adjacencyList;
    for (string& word : words) {
        adjacencyList[word] = generateAdjacentWords(word, wordSet);
    }
    return adjacencyList;
}

vector<string> bfs(unordered_map<string, vector<string>>& adjacencyList, string& start, string& end) {
    if (adjacencyList.find(start) == adjacencyList.end() || adjacencyList.find(end) == adjacencyList.end()) {
        cout << "The word was not found in the dictionary";
        return {};
    }
    queue<vector<string>> queue;
    unordered_set<string> visited;

    queue.push({start});
    visited.insert(start);

    while (!queue.empty()) {
        vector<string> way = queue.front();
        queue.pop();
        string currentWord = way.back();

        if (currentWord == end) {
            return way;
        }

        for (const string& neighbor : adjacencyList.at(currentWord)) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                vector<string> newPath = way;
                newPath.push_back(neighbor);
                queue.push(newPath);
            }
        }
    }
    cout << "The chain does not exist";
    return {};
}

int main() {
    string startWord, endWord;
    cin >> startWord >> endWord;
    double start_time = clock();
    vector<string> words;
    ifstream file;
    file.open("english_words.txt");
    while (!file.eof()) {
        string word;
        file >> word;
        words.push_back(word);
    }
    unordered_map<string, vector<string>> adjList = buildAdjacencyList(words);
    vector<string> chain = bfs(adjList, startWord, endWord);
    if (!chain.empty()) {
        cout << startWord << " ---> " << endWord << ":\n" << "Chain:";
        for (string& word : chain) {
            cout << " -> " << word;
        }
        cout << std::endl;
    }
    double end_time = clock();
    cout << "Program execution time: " << end_time - start_time << " seconds\n";
    file.close();
    return 0;
}
