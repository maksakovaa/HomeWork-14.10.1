#include "Trie.h"
using namespace std;


int main()
{
	TrieNode* library = new TrieNode{};
	insert(library, "apple");
	insert(library, "upload");
	insert(library, "bible");
	insert(library, "atom");
	insert(library, "brand");
	insert(library, "search");
	insert(library, "understand");
	insert(library, "hello");
	insert(library, "world");
	string words[9];

//	int wordNum = 0;
//	string buffer = "";
//	int height = 0;
//	getWords(library->children[1], words, wordNum, buffer, height);
//	int n = sizeof(words) / sizeof(words[0]);
//	printArray(words, n);
	string out = "";
	while (true)
	{
		system("cls");
		cout << "Current string is:\n" << out << endl;
		cout << "Enter the first letters of the word, or 0 to exit:\n";
		string temp = "";
		cin >> temp;
		if (temp == "0")
			break;
		autoComplete(library, temp, out);
	}

	delete library;
	return 0;
}