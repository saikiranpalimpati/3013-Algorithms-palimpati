#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std;

// Open a file containing words. Put the words in the dictionary on the specified word type
void intializeWordsDictionary(string filename, string wordType, map<string, vector<string> > &dictionary)
{
	ifstream file(filename.c_str());

	if (!file.is_open())
	{
		cout << "Error: '" << filename << "' failed to open for reading." << endl;
		exit(0);
	}

	// Extract each word from file and put it into the dictionary
	string word;

	while (file >> word)
		dictionary[wordType].push_back(word);

	file.close();
}

// Generate a crazy word using heuristics
string generateCrazyWord(string *wordTypes, int numWordTypes, 
	map <string, vector<string> > &heuristics, map <string, vector<string> > &dictionary)
{
	// Start at a random word type
	string wordType = wordTypes[rand() % numWordTypes];
	int numWordsGenerated = 1;
	string crazyWord = dictionary[wordType][rand() % dictionary[wordType].size()];

	while (true)
	{
		// Given the heuristics, we jump to the next word type
		wordType = heuristics[wordType][rand() % heuristics[wordType].size()];
		numWordsGenerated++;
		crazyWord += " " + dictionary[wordType][rand() % dictionary[wordType].size()];

		if (numWordsGenerated >= 5)
		{
			// We can stop if we got 5 words already
			break;
		}

		if (numWordsGenerated >= 3 && rand() % 2 == 0)
		{
			// We can stop if we got 3 words or continue
			break;
		}
	}

	return crazyWord;
}

// Start the program, we generate 10,000 words and save it to a file
// named tenthousandwords.txt
int main()
{
	// Seed the random generator to get random values for every call for a random value
	srand((unsigned int)time(0));
	
	// Lets create some possible heuristics for creating crazy words
	map <string, vector<string> > heuristics;

	// The heuristics is basically assigning what is the next possible type word after a type of word
	heuristics["adjective"].push_back("noun"); 
	heuristics["adjective"].push_back("animal");
	heuristics["noun"].push_back("adjective");
	heuristics["animal"].push_back("adjective");
	heuristics["verb"].push_back("adjective");
	heuristics["verb"].push_back("adverb");
	heuristics["adverb"].push_back("verb");
	
	// We load a dictionary of words
	map <string, vector<string> > dictionary;
	
	string wordFiles[] = { "adjectives.txt", "nouns.txt", "animals.txt", "adverbs.txt", "verbs.txt" };
	string wordTypes[] = { "adjective", "noun", "animal", "adverb", "verb" };

	for (int i = 0; i < 5; i++)
	{
		string wordFilePath = "./word_files/" + wordFiles[i];
		intializeWordsDictionary(wordFilePath, wordTypes[i], dictionary);
	}
	
	// Use the dictionary and heuristics to generate 10000 unique crazy words
	ofstream file("tenthousandwords.txt");
	map<string, string> generatedCrazyWords;

	while (generatedCrazyWords.size() < 10000)
	{
		string crazyWord = generateCrazyWord(wordTypes, 5, heuristics, dictionary);

		if (generatedCrazyWords.find(crazyWord) == generatedCrazyWords.end())
		{
			generatedCrazyWords[crazyWord] = crazyWord;
			file << crazyWord << endl;
		}
	}

	// We're done
	file.close();

	return 0;
}