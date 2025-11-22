#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

int main() {

    string csvFilePath = "C:\\C++ code\\codebook.csv"; //输入密码本的地址

    map<string, char> decodeMap;

    ifstream file(csvFilePath);
    if (!file.is_open()) {
        cout << "无法打开文件: " << csvFilePath << endl;
        return 1;
    }

    string line;
    getline(file, line); // 跳过表头

    while (getline(file, line)) {
        stringstream ss(line);
        string character, code;

        getline(ss, character, ',');
        getline(ss, code, ',');

        if (character == "\\n") {
            decodeMap[code] = ' ';
        } else if (!character.empty()) {
            decodeMap[code] = character[0];
        }
    }
    file.close();

    if (decodeMap.empty()) {
        cout << "编码本为空或格式错误！" << endl;
        return 1;
    }

    cout << "请输入编码: ";
    string encoded;
    getline(cin, encoded);

    string decoded = "";
    string currentCode = "";

    for (char bit : encoded) {
        currentCode += bit;

        if (decodeMap.find(currentCode) != decodeMap.end()) {
            decoded += decodeMap[currentCode];
            currentCode = "";
        }
    }

    if (!currentCode.empty()) {
        cout << "警告: 存在无法解码的编码片段" << endl;
    }

    cout << "\n解码后的文本: " << decoded << endl;

    return 0;
}
