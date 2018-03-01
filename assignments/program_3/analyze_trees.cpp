#include <iostream>
#include <fstream>
#include <string>
#include "BSTree.h"
#include "AVLTree.h"

using namespace std;

// Analyze the ten thousand words
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		// Make sure the file to analyze exists
		cout << "Usage: " << argv[0] << " <filename>" << endl;
		return 0;
	}

	// Put all words into a BST and AVL
	string wordFiles[] = { "adjectives.txt", "nouns.txt", "verbs.txt", "adverbs.txt", "animals.txt" };
	string wordTypes[] = { "Adjective", "Noun", "Animal", "Adverb", "Verb" };
	int wordTypeSizes[] = { 0, 0, 0, 0, 0 };

	BSTree bst;
	AVLTree avl;

	for (int i = 0; i < 5; i++)
	{
		string wordFilePath = "./word_files/" + wordFiles[i];
		ifstream dictionaryFile(wordFilePath.c_str());

		if (!dictionaryFile.is_open())
		{
			cout << "Error: '" << wordFiles[i] << "' failed to open for reading." << endl;
			return 0;
		}

		string word;

		while (dictionaryFile >> word)
		{
			bst.insert(word);
			avl.insert(word);
			wordTypeSizes[i]++;
		}

		dictionaryFile.close();
	}

	// After putting everything to the BST and AVL, we load the crazy words and search them in the BST and AVL
	// counting the total comparisons made
	ifstream crazyWordsFile(argv[1]);

	if (!crazyWordsFile.is_open())
	{
		cout << "Error: '" << argv[1] << "' failed to open for reading." << endl;
		return 0;
	}

	int bstComparisons = 0;
	int avlComparisons = 0;
	string crazyWord;

	while (crazyWordsFile >> crazyWord)
	{
		bstComparisons += bst.countComparisonsToSearch(crazyWord);
		avlComparisons += avl.countComparisonsToSearch(crazyWord);
	}

	crazyWordsFile.close();

	// Print out the analysis to an output file
	ofstream analysisFile("analysis.out");

	analysisFile << "BST Comparisons = " << bstComparisons << endl;
	analysisFile << "AVL Comparisons = " << avlComparisons << endl;
	
	for (int i = 0; i < 5; i++)
		analysisFile << "Number of " << wordTypes[i] << " = " << wordTypeSizes[i] << endl;

	analysisFile.close();
}