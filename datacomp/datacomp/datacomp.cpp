// datacomp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
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
	if (str.length() > 1) {
		for (int i = 0; i <= str.length(); i++) {
			string s1 = str.substr(0, i); //get a substring of s from from the start to index i
			subsets.push_back(s1);
		}
	}
	else {
		subsets.push_back(str);
	}
	if (subsets.size() > 1) {
		for (int i = 1; i < subsets.size(); i++) {
			subsets[i - 1] = subsets[i]; //since there's an empty space at the start shift all values left
		}
	}

}
void compress() {
	if (textcpy.length() >= 4) {
		lookahead = textcpy.substr(0, 4);
	}
	else {
		lookahead = textcpy.substr(0, textcpy.length());
	}
	substrings(lookahead);
	string output;
	int maxlen = 0;
	int maxidx = -1;
	for (int i = 0; i < subsets.size(); i++) {
		size_t index = dictionary.rfind(subsets[i]); //store index of found substring
													 //cout << "loop" << endl;
		if (dictionary.rfind(subsets[i]) != string::npos) { //if there is a match do this
			if (subsets[i].length()>maxlen) { //execute if substring is the longest so far
				maxlen = subsets[i].length();
				maxidx = index;
			}
			//cout << "index of found: " << 7 - index << " length of found: " << subsets[i].length() << endl;

		}
	}

	if (maxlen > 0) {//if match is found
		cout << "dict: " << dictionary << endl;
		//cout << "text: " << textcpy << endl;
		cout << "lookahead: " << lookahead << endl;
		maxidx = 7 - maxidx;//reverse index since indexing in example is right to left
		output = "0";
		output += to_string(maxidx);
		output += to_string(maxlen);
		cout << "(0,"<<maxidx<<","<<maxlen<<")" << endl;
		compressed.push_back(output);

		for (int i = 1; i <= maxlen; i++) {//shift the dictionary to the left by the length amount
			for (int i = 1; i < dictionary.length(); i++) {
				dictionary[i - 1] = dictionary[i]; //since there's an empty space at the start shift all values left
			}

		}
		dictionary.erase(8 - maxlen, maxlen);//remove as many ending characters as length of match
		dictionary.append(lookahead, 0, maxlen);
		textcpy.erase(0, maxlen);

	}
	else {
		cout << "dict: " << dictionary << endl;
		//cout << "text: " << textcpy << endl;
		cout << "lookahead: " << lookahead << endl;
		output = "1";
		output += subsets[0];
		cout <<"(1," <<subsets[0]<<")" << endl; //if no match then cout new char
		compressed.push_back(output);

		for (int i = 1; i < dictionary.length(); i++) {
			dictionary[i - 1] = dictionary[i]; //since there's an empty space at the start shift all values left
		}
		dictionary.erase(7);//remove last character
		dictionary.append(lookahead, 0, 1); //add the new char
		textcpy.erase(0, 1);
	}
}

string decompress(vector<string> compressedvec, string decompdict) {
	string decompressed;
	string lookaheadbuf;
	int size = compressedvec.size();
	int type;
	int offset;
	int length;
	string addedstring;
	for (int pos = 0; pos < compressedvec.size(); pos++) {
		type = compressedvec[pos][0] - 48;
		if (type == 0) {
			offset = compressedvec[pos][1] - 48;
			length = compressedvec[pos][2] - 48; 
				decompressed += decompdict.substr(7 - offset, length);//7 is the last index of dictionary, copy as many chars as the length of last output

			for (int i = 1; i <= length; i++) {//shift the dictionary to the left by the length amount
				for (int i = 1; i < decompdict.length(); i++) {
					decompdict[i - 1] = decompdict[i]; //since there's an empty space at the start shift all values left
				}
			}
			addedstring = decompressed.substr(decompressed.length() - length, length);
			decompdict.erase(8 - length, length);//remove as many ending characters as length of match
			decompdict.append(addedstring);
			//cout << "test" << endl;
		}
		else if (type == 1) {
			decompressed += compressedvec[pos][1]; //add the character to string
				for (int i = 1; i < decompdict.length(); i++) {
					decompdict[i - 1] = decompdict[i]; //since there's an empty space at the start shift all values left
				}

			addedstring = decompressed.substr(decompressed.length() - 1, 1);
			decompdict.erase(8 - 1, 1);//remove last char from dictionary
			decompdict.append(addedstring);
		}
	}
	return decompressed;
}

int main(void)
{
	ifstream fin("compress.txt"); //read line from file
	while (true) {
		getline(fin, textcpy);
		if (fin.eof())
			break;
	}
	fin.close();

	cout <<"string to be compressed: "<< textcpy << endl;
		cout << "dict: " << dictionary << endl;
		cout << "text: " << textcpy << endl;
		cout << "lookahead: " << lookahead << endl;
		while (textcpy.length() >= 1) {
			compress();
		}
		dictionary = "AAAAAAAA";
		cout << "decompressed string: " << decompress(compressed, dictionary) << endl;

		ofstream fout("decompressed.txt"); //save decompressed string to file
		fout << decompress(compressed, dictionary);
		fout.close();

		system("pause");
		return 0;

}
