#include "markov_machine.h"

#include <algorithm>
#include <cstring>

using namespace std;

MarkovMachine::MarkovMachine(istream& in) {
    vector<string> lines;
    while (!in.eof()) {
        lines.emplace_back();
        getline(in, lines.back());
    }
    for (auto& line : lines) {
        for (const auto& [delimiter, terminate] : { make_pair("->", false), make_pair("=>", true) }) {
            if (auto pos = line.find(delimiter); pos != std::string::npos) {
                string src = processString(line.substr(0, pos));
                string dst = processString(line.substr(pos + 2, line.length()));
                rules.emplace_back(Rule{src, dst, terminate});
                continue;
            }
        }
    }
}

void sleepOnEnter() {
    string s;
    getline(cin, s);
}

void MarkovMachine::apply(string& text) const {
    while (tryStep(text)) {
        //cout << text << endl;
        //sleepOnEnter();
    }
}

bool MarkovMachine::tryStep(string& text) const {
    for (const auto& rule : rules) {
        if (rule.tryApply(text)) {
            return !rule.terminate;
        }
    }
    return false;
}

string MarkovMachine::processString(const string& s) {
    string res;
    for (char ch : s) {
        if (ch == ' ') {
            continue;
        }
        if (ch == '\n') {
            continue;
        }
        if (ch == '\r') {
            continue;
        }
        res.push_back(ch);
    }
    return res;
}

bool MarkovMachine::Rule::tryApply(string& text) const {
    if (auto pos = text.find(src); pos != std::string::npos) {
        auto it = text.begin() + pos;
        text.erase(it, it + src.length());
        text.insert(it, dst.begin(), dst.end());
        return true;
    }
    return false;
}
