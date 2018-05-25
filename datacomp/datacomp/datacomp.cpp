// datacomp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int dictsize = 9;
string dictionary = "AAAAAAAA";
string text = "ABABCDABCABCDCADABCA";
string textcpy = text;
string lookahead;
vector <string> subsets;
vector <string> compressed;

void substrings(string str) {
	subsets.erase(subsets.begin(), subsets.end());
	for (int i = 0; i <= str.length(); i++) {
		string s1 = str.substr(0, i); //get a substring of s from from the start to index i
		subsets.push_back(s1);
	}
	for (int i = 1;i < subsets.size();i++) {
		subsets[i - 1] = subsets[i]; //since there's an empty space at the start shift all values left
	}
	subsets.erase(subsets.begin() + 4);//delete last entry because now it is empty
}

void compress() {
	lookahead = textcpy.substr(0, 4);
	substrings(lookahead);
	string output = "(";
	int maxlen = 0;
	int maxidx = -1;
	for (int i = 0; i < subsets.size(); i++) {
		size_t index = dictionary.rfind(subsets[i]); //store index of found substring 
													 //cout << "loop" << endl;
		if (dictionary.rfind(subsets[i]) != string::npos) { //if there is a match do this
															//cout << "ifentered" << endl;
			if (subsets[i].length()>maxlen) { //execute if substring is the longest so far 
				maxlen = subsets[i].length();
				maxidx = index;
			}
			//cout << "index of found: " << 7 - index << " length of found: " << subsets[i].length() << endl;

		}
	}

	if (maxlen > 0) {//if match is found
		cout << "dicc: " << dictionary << endl;
		cout << "text: " << textcpy << endl;
		cout << "lookahead: " << lookahead << endl;
		maxidx = 7 - maxidx;//reverse index since indexing in example is right to left
		output += "0,";
		output += to_string(maxidx);
		output += ",";
		output += to_string(maxlen);
		output += ")";
		cout << output << endl;
		compressed.push_back(output);

		for (int i = 1;i <= maxlen;i++) {//shift the dictionary to the left by the length amount
			for (int i = 1;i < dictionary.length();i++) {
				dictionary[i - 1] = dictionary[i]; //since there's an empty space at the start shift all values left
			}
			
		}
		dictionary.erase(8 - maxlen, maxlen);//remove as many ending characters as length of match
		dictionary.append(lookahead, 0, maxlen);
		textcpy.erase(0, maxlen);

	}
	else {
		cout << "dicc: " << dictionary << endl;
		cout << "text: " << textcpy << endl;
		cout << "lookahead: " << lookahead << endl;
		output += "1,";
		output += subsets[0];
		output += ")";
		cout << output << endl; //if no match then cout new char
		compressed.push_back(output);

		for (int i = 1;i < dictionary.length();i++) {
			dictionary[i - 1] = dictionary[i]; //since there's an empty space at the start shift all values left
		}
		dictionary.erase(7);//remove last character
		dictionary.append(lookahead, 0, 1); //add the new char
		textcpy.erase(0, 1);
	}
}


int main(void)
{

	cout << "dicc: " << dictionary << endl;
	cout << "text: " << textcpy << endl;
	cout << "lookahead: " << lookahead << endl;
	while (textcpy.length() > 3) {
		compress();
	}

	system("pause");
	return 0;

}
