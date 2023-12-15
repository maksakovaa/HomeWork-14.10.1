#include "Trie.h"
#include <string>


// ���������� ����� ���� � ������� ������
TrieNode* getNewNode(void)
{
	struct TrieNode* pNode = new TrieNode;
	pNode->isEndOfWord = false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = nullptr;

	return pNode;
}

// ��������� ���� � ������, ���� ��� ���, 
// ����� ���� ���� ������� �������� ���� ������ 
// �������� ��������� �������� �.�. ����� �����

void insert(TrieNode* root, std::string key)
{
	TrieNode* currentNode = root;
	int n = static_cast<int>(key.size());
	for (int i = 0; i < n; i++)
	{
		int index = key[i] - 'a';

		if (!currentNode->children[index])
			currentNode->children[index] = getNewNode();

		currentNode->children[index]->freq++;
		currentNode = currentNode->children[index];
	}
	currentNode->isEndOfWord = true;
}

// ���������� true ���� ���� ���� � ������, ����� false
bool search(struct TrieNode* root, std::string key)
{
	TrieNode* node = root;
	for (int i = 0; i < key.length(); i++)
	{
		int index = getCharIndex(key[i]);
		if (!node->children[index])
			return false;

		node = node->children[index];
	}

	return (node != nullptr && node->isEndOfWord);
}

// ���������� true ���� root ����� ����, ����� false
bool isEmpty(TrieNode* root)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (root->children[i])
			return false;
	return true;
}

// ����������� ������� �������� ����� �� ������
TrieNode* remove(TrieNode* root, std::string key, int depth)
{
	if (!root)
		return nullptr;
	if (depth == key.size()) {
		if (root->isEndOfWord)
			root->isEndOfWord = false;
		if (isEmpty(root)) {
			delete (root);
			root = nullptr;
		}
		return root;
	}

	int index = key[depth] - 'a';
	root->children[index] = remove(root->children[index], key, depth + 1);
	if (isEmpty(root) && root->isEndOfWord == false) {
		delete (root);
		root = nullptr;
	}
	return root;
}

void findMinPrefixes(TrieNode* root, char buf[], int ind, std::string& res)
{
	if (root == NULL) return;

	if (root->freq == 1)
	{
		res += buf;
		res += ' ';
		std::cout << res << '\n';
		return;
	}

	for (int i = 0; i < ALPHABET_SIZE; ++i)
	{
		if (root->children[i] != nullptr)
		{
			buf[ind] = i + 'a';
			buf[ind + 1] = '\0';
			findMinPrefixes(root->children[i], buf, ind + 1, res);
		}
	}
}

void getWords(TrieNode* root, std::string array[], int& word, std::string& buffer, int& height)
{
	if (!root)
	{
		std::cout << "ERROR: Library is empty!" << std::endl;
		return;
	}

	TrieNode* currentNode = root;

	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (currentNode->children[i]) // ���� ����� ���������� ��:
		{
			//������ ������� �������� ����� � ������ � ��������� ��� � ������ ��� �������� word.
			//������� ��� ��� ������� ����� ������ � ���� ����������, �� ��������� ������.
			// ����� ������� ������� ����� �� ������ �� �������� �������� ������ �� ������� ��������
			if (array[word] == "") 
			{
				array[word] = buffer.erase(height); //����������� ������� ������ �� ������� ������ (��������)
			}
			////////////////////////////////////////

			buffer += 'a' + i; //��������� ����� � ������
			if (!currentNode->children[i]->isEndOfWord)
			{
				height++; //����������� �������� ������ �� ���� � ��������
				getWords(currentNode->children[i], array, word, buffer, height);
				height--; //�� ������ �� �������� ��������� ������
			}
			else
			{
				array[word] = buffer; // ��������� �������� ����� �� ������ � ������ ��� �������� word
				word++;
			}
		}
	}
}

int getCharIndex(const char text)
{
	return text - 'a';
}

void printArray(std::string arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		std::cout << i+1 << " - " << arr[i] << std::endl;
	}
}

void autoComplete(TrieNode* lib, std::string& uncompl, std::string& out)
{
	TrieNode* currentNode = lib;
	int n = uncompl.length();
	int temp = -1;
	//��������� ������� � ���������� ����� ����������� �������� ������
	for (int i = 0; i < n; i++)
	{
		int index = getCharIndex(uncompl[i]);

		// ���� ������ � ���� �� ��������� � �������� � �������� ������ ������� ��������� �� ���������� ����� � ���������� � ������� �� �������
		if (!currentNode->children[index])
		{
			std::cout << "There is no one words in library!\n";
			return;
		}
		// ���� ������ ��������� ��������� �� ���������
		currentNode = currentNode->children[index];
	}
	//���� � ���������� ������� ��������� ������ � ������ ��� �����, ��:
	if (isEmpty(currentNode))
	{
		std::cout << "Only this word exists in library:\n" << uncompl << "\nAccept? 1 - yes, other - no" << std::endl;
		std::cin >> temp;
		if (temp == 1)
		{
			out.append(uncompl.append(" "));
		}
		else
		{
			return;
		}
	}
	//���� � ���������� ������� ��������� ������ � ������ ���� ����, �� ���������� � ������� ��������� ��������:
	else
	{
		std::string words[10];
		int wordCount = 0;
		std::string buf = uncompl;
		getWords(currentNode, words, wordCount, buf, n); //���������� � ������� � ������ words
		std::cout << "Choose one of these words (enter number), or 0 to exit:\n";
		printArray(words, wordCount); //������� ������ words

		std::cin >> temp;
		if (temp == 0)
		{
			return;
		}
		if (temp >= 1 && temp <= wordCount)
		{
			out.append(words[temp-1].append(" "));
		}
	}
}