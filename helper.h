/**
    CSE355 optional project, helper.h
    Purpose: Helper functions that were cluttering the main class.

    @author Suhail Ghafoor
    @version 0.1 04/06/18
*/

#ifndef CODE_HELPER_H
#define CODE_HELPER_H

#include "Structs.h"
#include <fstream>
#include <sstream>

bool is_number(const std::string& s);

/**
 * Given a string returns a number. This is a good way to generate unique
 * numbers for states which are required for vis.js graph
 * @param s - String name
 * @return integer version of the string
 */
int stringToInt(string s){
    if(is_number(s)){
        return stoi(s);
    }

    auto n = s.length();
    int retValue = 0;
    for(unsigned int i = 0; i < n; i++){
        retValue += ((s[i]) * (i+ 1));
    }
    return retValue;
}

/**
 * Makes a js data file from a dfa tuple which is used in visualization
 * @param dfa DFA tuple from which the js is generated
 * @param fileName Name of the new filename
 */
void jsonPrint(DFA_flat_tuple * dfa, string fileName){
    ofstream jsFile;
    vector<string> nodeIds;

    string filePath = "../visualize/" + fileName;

    jsFile.open (filePath);

    bool acc, init;

    string initColor = "#FF7F32";
    string defColor = "#5C6670";
    string accColor = "#78BE20";
    string initAccColor = "#FF7F32";

    //start writing all nodes first
    jsFile << "var nodes = [\n";
    for(vector<string>::size_type z = 0; z != dfa->states.size(); z++){
        acc = init = false;
        jsFile << "\t{id: " << stringToInt(dfa->states[z]) << ", label: '" << dfa->states[z] << "'";
        for(vector<string>::size_type y = 0; y != dfa->finStates.size(); y++) {
            if (dfa->states[z] == dfa->finStates[y]) {
                acc = true;
            }
        }

        if(dfa->states[z] == dfa->initialState){
            init = true;
        }

        if(init && acc){
            jsFile << ", color: {background:'"<< initAccColor <<"', border:'green'}";
        } else if(init){
            jsFile << ", color: '"<< initColor <<"'";
        } else if(acc){
            jsFile << ", color: {background:'"<< accColor <<"', border:'green'}";
        } else{
            jsFile << ", color: '" << defColor <<"'";
        }

        jsFile << "}";

        if(dfa->states[z] != dfa->states.back()){
            jsFile << ",";
        }

        jsFile << "\n";
    }
    jsFile << "];\n\nvar edges = [\n";
    //done printing nodes

    vector<Flat_transition*> comboTransitions;
    bool found;

    for(vector<Flat_transition*>::size_type z = 0; z != dfa->transitions.size(); z++){
        found = false;
        for(vector<Flat_transition*>::size_type x = 0; x != comboTransitions.size(); x++){
            if(dfa->transitions[z]->initState == comboTransitions[x]->initState && dfa->transitions[z]->nState == comboTransitions[x]->nState){
                comboTransitions[x]->alphabet += ", " + dfa->transitions[z]->alphabet;
                found = true;
            }
        }

        if(!found){
            auto * ft = new Flat_transition();
            ft->initState = dfa->transitions[z]->initState;
            ft->nState = dfa->transitions[z]->nState;
            ft->alphabet = dfa->transitions[z]->alphabet;
            comboTransitions.push_back(ft);
        }

    }

    for(vector<Flat_transition*>::size_type z = 0; z != comboTransitions.size(); z++){
        jsFile << "\t{from: " << stringToInt(comboTransitions[z]->initState) << ", to:";
        jsFile << stringToInt(comboTransitions[z]->nState)  << ", arrows:'to', label: '";
        jsFile << comboTransitions[z]->alphabet << "', font: {align: 'top'}}";

        if(comboTransitions[z] != comboTransitions.back()){
            jsFile << ",";
        }

        jsFile << "\n";
    }

    jsFile << "];";
    jsFile.close();
}

/**
 * his function reads the input line by line and hands each line to
 * gives them to the parser object
 * @param p Parser one for system states
 * @param p2 Parser 2 for specification states
 */
void readLines(Parser * p, Parser * p2){
    string line;
    int type = -1;
    int automatonType = -1;

    while (getline(cin, line)) {
        if(line.empty()) break;
        if(line.find("Input alphabet") != string::npos){
            type = 0;
        } else if(line.find("Specification automaton") != string::npos){
            automatonType = 0;
        } else if(line.find("System automaton") != string::npos){
            automatonType = 1;
        } else if(line.find("Transition function") != string::npos){
            type = 1;
        } else if(line.find("Initial state") != string::npos){
            type = 2;
        } else if(line.find("Final states") != string::npos){
            type = 3;
        } else{
            switch(type){
                case 0:
                    p->addAlphabet(line);
                    p2->addAlphabet(line);
                    break;
                case 1:
                    if(automatonType == 0){
                        p->addTransitions(line);
                    } else if(automatonType == 1){
                        p2->addTransitions(line);
                    }
                    break;
                case 2:
                    if(automatonType == 0){
                        p->setInitial(line);
                    } else if(automatonType == 1){
                        p2->setInitial(line);
                    }
                    break;
                case 3:
                    if(automatonType == 0){
                        p->addFinalStates(line);
                    } else if(automatonType == 1){
                        p2->addFinalStates(line);
                    }
                    break;
                default:
                    ;
            }
        }
    }
}

/**
 * Given a DFA tuple prints out the DFA in the same format as the input
 * @param dfa Pointer to dfa tuple which is supposed to be printed
 */
void printMachine(DFA_flat_tuple * dfa){
    cout << "% Input alphabet" << endl;
    for(vector<string>::size_type z = 0; z != dfa->alphabet.size(); z ++) cout << dfa->alphabet[z] << endl;

    cout << "% Transition function" << endl;
    for(vector<Flat_transition*>::size_type z = 0; z != dfa->transitions.size(); z ++){
        cout << dfa->transitions[z]->initState + " ";
        cout << dfa->transitions[z]->alphabet + " ";
        cout << dfa->transitions[z]->nState << endl;
    }

    cout << "% Initial states" << endl;
    cout << dfa->initialState << endl;

    cout << "% Final states" << endl;
    for(vector<string>::size_type z = 0; z != dfa->finStates.size(); z++) cout << dfa->finStates[z] << endl;
}

/**
 * Helper function that checks if string is a number
 * @param s the input string
 * @return bool result, true is input is number
 */
bool is_number(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

#endif //CODE_HELPER_H
