#pragma once
#include <iostream>
#define ALPHABET_SIZE 26

// Структура узла дерева
struct TrieNode
{
	struct TrieNode* children[ALPHABET_SIZE];
	bool isEndOfWord;
	int freq = 0;
};

TrieNode* getNewNode(void);
void insert(TrieNode*, std::string);
bool search(TrieNode*, std::string);
bool isEmpty(TrieNode*);
TrieNode* remove(TrieNode*, std::string, int depth = 0);
void findMinPrefixes(TrieNode*, char[], int, std::string&);
void getWords(TrieNode*, std::string array[], int& word, std::string& buffer, int& height);
int getCharIndex(const char text);
void autoComplete(TrieNode* lib, std::string& uncompl, std::string& out);
void printArray(std::string arr[], int n);