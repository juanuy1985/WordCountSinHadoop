// Trie.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include <istream>
#include <sstream>
#include <fstream>
#include <chrono>

using namespace std;

struct TrieNode
{
	int counters[26];
	TrieNode* links[26];

	TrieNode()
	{
		memset(&counters, 0, 26 * sizeof(int));
		memset(&links, 0, 26 * sizeof(TrieNode*));
	}

	~TrieNode()
	{
		for (int index = 0; index<26; index++)
			delete(links[index]);
	}
};

class Trie
{
private:
	TrieNode* root;
	char stop;

	bool insert(TrieNode** node, istream& input)
	{
		char c = input.get();

		if (c<'a' || c>'z')
			return true;

		if (*node == NULL)
			*node = new TrieNode();
		if (insert(&((*node)->links[c - 'a']), input))
			(*node)->counters[c - 'a']++;

		return false;
	}

	void print(TrieNode* node, char* buffer, int currentIndex)
	{
		if (node != NULL)
		{
			for (int index = 0; index<26; index++)
			{
				buffer[currentIndex] = (char)('a' + index);

				if (node->counters[index]>0) {
					buffer[currentIndex + 1] = 0;
					cout << buffer << ": " << node->counters[index] << endl;
				}

				if (node->links[index] != NULL)
				{
					print(node->links[index], buffer, currentIndex + 1);
				}
			}
		}
	}
public:
	Trie(char stop = ' ')
	{
		root = NULL;
		this->stop = stop;
	}

	~Trie()
	{
		delete(root);
	}

	void insert(istream& stream)
	{
		while (!stream.eof())
		{
			this->insert(&root, stream);
		}
	}

	void print()
	{
		char buffer[1024];
		print(root, buffer, 0);
	}
};

void proceso(Trie& trie, ifstream& file)
{
	trie.insert(file);
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc > 1)
	{
		Trie trie(0);

		ifstream file(argv[1]);

		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

		trie.insert(file);

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

		std::cout << "Proceso consume milisegundos => " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << std::endl;

		cout << "Proceso de conteo de palabras terminado, Imprimiendo palabras..." << endl;

		trie.print();
	}
	return 0;
}

