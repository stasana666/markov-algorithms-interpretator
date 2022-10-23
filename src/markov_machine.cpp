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

void MarkovMachine::apply(string& text) const {
    while (tryStep(text));
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
    bool isEscaping = false;
    for (char ch : s) {
        if (isEscaping) {
            if (ch == 'n') {
                res.push_back('\n');
            }
            isEscaping = false;
        } else {
            if (ch == ' ' || ch == '\n' || ch == '\r') {
                continue;
            }
            if (ch == '\\') {
                isEscaping = true;
                continue;
            }
            res.push_back(ch);
        }
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
