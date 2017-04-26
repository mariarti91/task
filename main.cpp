#include <iostream>
#include <stdlib.h>

using namespace std;

#define MAX_SIZE 200

bool islatin(char c)
{
	return (('A' <= c) && (c <= 'z'));
}

char toLower(char c)
{
	if (('A' <= c) && (c <= 'Z')) c += ('a'-'A');
	return c;
}

int index(char c)
{
	return toLower(c) - 'a';
}

char letter(int i)
{
	return (char)i + 'a';
}

class MyList
{
public:
	MyList(){ begin = new wordCount(); };
	void insert(const int& count, const char* word)
	{
		wordCount *record = new wordCount();
		record->count = count;
		int l = 0;
		const char *q = word;
		while (*q++) ++l;
		q = word;
		record->word = new char[l];
		char *p = record->word;
		while (*p++ = *q++);
		_insert(begin, record);
	}
	void printList()
	{
		wordCount* current = begin->next;
		while (current != NULL)
		{
			cout << current->word << " " << current->count << endl;
			current = current->next;
		}
	}
private:
	struct wordCount
	{
		char *word;
		int count;
		wordCount *next;
		wordCount() :word(NULL), count(0), next(NULL){};
	};
	void _insert(wordCount* list, wordCount* record)
	{
		if (list->next == NULL)
		{
			list->next = record;
		}
		else if (list->next->count >= record->count)
		{
			_insert(list->next, record);
		}
		else
		{
			record->next = list->next;
			list->next = record;
		}
	}

	wordCount* begin;
};

class MyTree
{
public:
	MyTree()
	{
		root = new node();
		current = root;
	};
	~MyTree(){/*TODO*/}
	void processingString(char *s)
	{
		for (s; *s; ++s)
		{
			if (islatin(*s))
			{
				this->insert(*s);
			}
			else
			{
				this->endWord();
			}
		}
		this->endWord();
	}
	void insert(char c)
	{
		int i = index(c);
		if (current->childs[i] == NULL) current->childs[i] = new node();
		current = current->childs[i];
	};
	void endWord()
	{
		++(current->count);
		current = root;
	};
	void convertToList(MyList* list)
	{
		char* buf = new char[MAX_SIZE]{'\0'};
		current = root;
		_convertToList(root, list, buf, 0);
		delete buf;
	}
private:
	struct node
	{
		int count;
		node** childs;
		node() :count(0), childs(new node*[26]{NULL}){};
	};
	node* root;
	node* current;
	void _convertToList(node* current, MyList* list, char *prefix, int prefLength)
	{
		for (int i = 0; i < 26; ++i)
		{
			if (current->childs[i] == NULL) continue;
			prefix[prefLength++] = letter(i);
			if (current->childs[i]->count)
			{
				list->insert(current->childs[i]->count, prefix);
			}
			_convertToList(current->childs[i], list, prefix, prefLength);
			prefix[prefLength--] = '\0';
		}
	}
};

int main()
{
	MyTree *tree = new MyTree();
	char *b = new char[MAX_SIZE];
	cin.getline(b, MAX_SIZE);
	tree->processingString(b);
	MyList *list = new MyList();
	tree->convertToList(list);
	delete tree;
	list->printList();
	delete list;
	system("pause");
	return 0;
}