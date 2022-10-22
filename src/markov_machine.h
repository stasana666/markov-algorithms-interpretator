#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class MarkovMachine {
public:
    MarkovMachine(std::istream& in);

    void apply(std::string& text) const;

    bool tryStep(std::string& text) const;

private:
    std::string processString(const std::string& s);

    struct Rule {
        std::string src;
        std::string dst;
        bool terminate;

        bool tryApply(std::string& text) const;
    };

    std::vector<Rule> rules;
};
