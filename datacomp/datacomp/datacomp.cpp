// datacomp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int dictsize = 9;
string dictionary = "AAAAAAAA";
string text = "ABRACADABRADABRACAB";
string textcpy = "ABRACADABRADABRACAB";
string lookahead;
vector <string> subsets;
vector <string> compressed;

void substrings(string str) {
	for (int i = 0; i <= str.length(); i++) {
		string s1 = str.substr(0, i); //get a substring of s from position with length j
		subsets.push_back(s1);
	}
	for (int i = 1;i < subsets.size();i++) {
		subsets[i - 1] = subsets[i];
	}
	subsets.erase(subsets.begin() + 4);
}

void compress() {
	lookahead = textcpy.substr(textcpy.length() - 4);
	substrings(lookahead);
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
			cout << "index of found: " << 7-index << " length of found: " << subsets[i].length() << endl;
		}
	}
	
	if (maxlen > 0) {//if match is found
		maxidx = 7 - maxidx;//reverse index since indexing in example is right to left
		cout << "(0," << maxidx << ","<< maxlen << ")" << endl; //output the compression
	}
	else {
		cout << "(1," << subsets[0] << ")" << endl; //if no match then cout new char
	}
}


int main(void)
{
	
	compress();


	cout << "subsets size: " << subsets.size() << endl;
	//for (int i = 0; i < 9; i++) {
	//cout << dictionary[i] << endl;
	//}
	//
	//for (int o = 0; o < 9; o++) {
	//	dictionary[o] = dictionary[o+1];
	//}

	//for (int p = 0; p < 9; p++) {
	//	cout << dictionary[p] << endl;
	//}

	system("pause");
	return 0;

}
