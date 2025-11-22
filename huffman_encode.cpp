#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <fstream>
using namespace std;

struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode *left, *right;

    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

void generateCodes(HuffmanNode* root, string code, map<char, string>& codes) {
    if (!root) return;

    if (!root->left && !root->right) {
        codes[root->ch] = code.empty() ? "0" : code;
        return;
    }

    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

int main() {
    string text;
    cout << "请输入文本（只含有英文字母和空格）: ";
    getline(cin, text);

    map<char, int> frequency;
    for (char c : text) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ') {
            frequency[c]++;
        }
    }

    if (frequency.empty()) {
        cout << "No valid characters found!" << endl;
        return 1;
    }

    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> minHeap;

    for (auto& pair : frequency) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top(); minHeap.pop();
        HuffmanNode* right = minHeap.top(); minHeap.pop();

        HuffmanNode* parent = new HuffmanNode('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        minHeap.push(parent);
    }

    HuffmanNode* root = minHeap.top();

    map<char, string> codes;
    generateCodes(root, "", codes);

    string encoded = "";
    for (char c : text) {
        if (codes.find(c) != codes.end()) {
            encoded += codes[c];
        }
    }

    cout << "\nEncoded text: " << encoded << endl;

    ofstream file("codebook.csv");
    file << "character,code\n";
    for (auto& pair : codes) {
        if (pair.first == ' ') {
            file << "\\n," << pair.second << "\n";
        } else {
            file << pair.first << "," << pair.second << "\n";
        }
    }
    file.close();

    cout << "Codebook saved to codebook.csv" << endl;

    return 0;
}
