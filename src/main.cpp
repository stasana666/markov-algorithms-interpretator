#include "markov_machine.h"

#include <algorithm>
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    ifstream markovAlgorithmDescription(argv[1]);
    MarkovMachine markovMachine(markovAlgorithmDescription);

    string text;
    getline(cin, text);

    markovMachine.apply(text);

    cout << text << endl;

    return 0;
}
