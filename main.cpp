#include "std_lib_facilities.h"

using namespace std;

int InputOpt();  //  input option

void ManageList(vector<string>& wordList);  //  manage list page
void PrintWords(vector<string> wordList);  //  print wordList
void AddWord(vector<string>& wordList);  //  add new word in wordList

void SolvePuzzle(vector<string> wordList);  //  solve puzzle page
vector<string> NewPuzzleList(vector<string> wordList, int mode);  //  make new wordlist for puzzle. mode 1: easy, mode 2: hard
void PlayPuzzle(vector<string> puzzleList, int swapTime, int guess);  //  swapTime: # of swaps, guess: # of guesses
void SelectMode(vector<string> wordList, int mode, int swapTime, int guess);  //  func NewPuzzleList + func PlayPuzzle
string JumbleWord(string word, int swapTime);  //  make a jumbled word
string CompareAnswer(string rightAnswer, string answer);  //  compare answer is right

int main()
{
	vector<string> wordList = {
		"drift", "professional", "midnight", "scatter", "relevance", 
		"visit", "disaster", "commerce", "progress", "shift", 
		"spell", "veil", "desk", "gown", "umbrella", 
		"gregarious", "craftsman", "wriggle", "score", "deliver", 
		"vote", "dirty", "chain", "road", "charter", 
		"feign", "duck", "highway", "add", "van", 
		"mutual", "bang", "table", "venture", "deficiency", 
		"depend", "dimemsion", "holliday", "scrap", "unlike", 
		"coast", "command", "base", "recommend", "spit", 
		"corner", "huge", "economic", "sight", "coincide"
	};

	while (1)
	{
		cout << "<<< WORD JUMBLE >>>" << endl;
		cout << "1. Manage List" << endl;
		cout << "2. Solve Puzzle" << endl;
		cout << "3. Exit" << endl << endl;

		switch (InputOpt())
		{
		case 1:
			ManageList(wordList);
			break;
			
		case 2:
			SolvePuzzle(wordList);
			break;

		case 3:
			cout << endl << "Good bye!!!" << endl;
			return 0;
		}
	}
}

int InputOpt()
{
	int option = -1;

	while (option <= 0 || option > 3)
	{
		cout << "Choose an option (1-3): ";
		cin >> option;
	}

	return option;
}

void ManageList(vector<string>& wordList)
{
	while (1)
	{
		cout << endl << "[ MANAGE LIST ]" << endl;
		cout << "1. Print Words" << endl;
		cout << "2. Add Word" << endl;
		cout << "3. Return" << endl << endl;

		switch (InputOpt())
		{
		case 1:
			PrintWords(wordList);
			break;

		case 2:
			AddWord(wordList);
			break;

		case 3:
			cout << endl;
			return;
		}
	}
}

void PrintWords(vector<string> wordList)
{
	cout << endl << "A total of " 
		<< wordList.size() << " words are available:" << endl;

	sort(wordList);

	for (string word : wordList)
	{
		cout << word << endl;
	}
}

void AddWord(vector<string>& wordList)
{
	string word;

	cout << endl << "Input a new word: ";
	cin >> word;
	if (find(wordList, word) == wordList.end())
	{
		wordList.push_back(word);
		cout << "The word " << "\'" + word + "\'"
			<< " has been successfully inserted in the list." << endl;
	}
	else
	{
		cout << "The word " << "\'" + word + "\'"
			<< " already exists in the list." << endl;
	}
	
}

void SolvePuzzle(vector<string> wordList)
{
	while (1)
	{
		cout << endl << "[ SOLVE PUZZLE ]" << endl;
		cout << "1. Easy mode" << endl;
		cout << "2. Hard mode" << endl;
		cout << "3. Return" << endl << endl;

		switch (InputOpt())
		{
		case 1:
			SelectMode(wordList, 1, 2, 3);  //  Easy Mode
			break;

		case 2:
			SelectMode(wordList, 2, 4, 5);  //  Hard Mode
			break;

		case 3:
			cout << endl;
			return;
		}
	}
}

vector<string> NewPuzzleList(vector<string> wordList, int mode)
{
	vector<string> puzzleList;

	if (mode == 1)
	{
		for (string word : wordList)
		{
			if (word.size() <= 5)
			{
				puzzleList.push_back(word);
			}
		}
	}
	else  //  mode == 2
	{
		for (string word : wordList)
		{
			if (word.size() >= 5)
			{
				puzzleList.push_back(word);
			}
		}
	}

	return puzzleList;
}

void PlayPuzzle(vector<string> puzzleList, int swapTime, int guess)
{
	int index = randint(puzzleList.size());
	string rightAnswer = puzzleList[index];
	string jumbleWord = JumbleWord(rightAnswer, swapTime);
	string answer;

	cout << "I give you a jumbled word " 
		<< "\'" + jumbleWord + "\'." << endl;
	
	for (int i = 0; i != guess; ++i)
	{
		cout << "[" << i + 1 << "/" << guess << "] "
			<< "Guess the original word: ";
		cin >> answer;
		cout << ">> " << CompareAnswer(rightAnswer, answer)
			<< endl << endl;

		if (answer.size() == rightAnswer.size() && answer == rightAnswer)
		{
			cout << "Congratulation! You got the answer right!" 
				<< endl << endl;

			break;
		}
		else if (i + 1 == guess)  //  && answer != rightAnswer
		{
			cout << "Oops! You failed to solve the puzzle..." << endl;
			cout << "The correct answer is " 
				<< "\'" + rightAnswer + "\'" << endl;
		}
	}
}

void SelectMode(vector<string> wordList, int mode, 
	int swapTime, int guess)
{
	vector<string> puzzleList = NewPuzzleList(wordList, mode);
	PlayPuzzle(puzzleList, swapTime, guess);
}

string JumbleWord(string word, int swapTime)
{
	for (int i = 0; i != swapTime; ++i)
	{
		int index1 = randint(word.size());
		int index2 = randint(word.size());

		swap(word[randint(index1)], word[randint(index2)]);
	}

	return word;
}

string CompareAnswer(string rightAnswer, string answer)
{
	string correctParts = string(rightAnswer.size(), '-');

	if (rightAnswer.size() > answer.size())
	{
		answer += string(rightAnswer.size() - answer.size(), ' ');
	}

	for (int i = 0; i != rightAnswer.size(); ++i)
	{
		if (rightAnswer[i] == answer[i])
		{
			correctParts[i] = rightAnswer[i];
		}
	}

	return "[" + correctParts + "]";
}