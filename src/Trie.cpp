#include "Trie.h"
#include <string>


// Возвращает новый узел с пустыми детьми
TrieNode* getNewNode(void)
{
	struct TrieNode* pNode = new TrieNode;
	pNode->isEndOfWord = false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = nullptr;

	return pNode;
}

// Вставляет ключ в дерево, если его нет, 
// иначе если ключ явлется префксом узла дерева 
// помечает вкачестве литового т.е. конец слова

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

// Возвращает true если ключ есть в дереве, иначе false
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

// Возвращает true если root имеет лист, иначе false
bool isEmpty(TrieNode* root)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (root->children[i])
			return false;
	return true;
}

// Рекурсивная функция удаления ключа из дерева
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
		if (currentNode->children[i]) // если буква существует то:
		{
			//данная функция обрезает текст в буфере и вставляет его в массив под индексом word.
			//Сделана для тех случаев когда начало у слов одинаковое, но окончание разное.
			// После прохода первого слова на выходе из рекурсии меняется высота до момента развилки
			if (array[word] == "") 
			{
				array[word] = buffer.erase(height); //Выполняется обрезка буфера до текущей высоты (развилки)
			}
			////////////////////////////////////////

			buffer += 'a' + i; //формируем слово в буфере
			if (!currentNode->children[i]->isEndOfWord)
			{
				height++; //увеличиваем значение высоты на вход в рекурсию
				getWords(currentNode->children[i], array, word, buffer, height);
				height--; //на выходе из рекурсии уменьшаем высоту
			}
			else
			{
				array[word] = buffer; // добавляем итоговое слово из буфера в массив под индексом word
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
	//Проверяем наличие в библиотеке слова содержащего ввёденную строку
	for (int i = 0; i < n; i++)
	{
		int index = getCharIndex(uncompl[i]);

		// Если символ в узле не совпадает с символом в введённой строке выводим сообщение об отсутствии слова в бибилотеке и выходим из функции
		if (!currentNode->children[index])
		{
			std::cout << "There is no one words in library!\n";
			return;
		}
		// Если символ совпадает переходим на следующий
		currentNode = currentNode->children[index];
	}
	//Если у последнего символа введенной строки в дереве нет детей, то:
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
	//Если у последнего символа введенной строки в дереве есть дети, то определяем и выводим возможные варианты:
	else
	{
		std::string words[10];
		int wordCount = 0;
		std::string buf = uncompl;
		getWords(currentNode, words, wordCount, buf, n); //определяем и заносим в массив words
		std::cout << "Choose one of these words (enter number), or 0 to exit:\n";
		printArray(words, wordCount); //выводим массив words

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