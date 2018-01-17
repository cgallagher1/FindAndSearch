#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <string>

using namespace std;

// A utility function to swap two elements
void swap(string* a, string* b)
{
	string t = *a;
	*a = *b;
	*b = t;
}


int partition(vector<string>& toSort, int low, int high)
{
	int pivot = high;    // pivot
	int i = (low - 1);  // Index of smaller element

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than or
		// equal to pivot
		if (toSort[j] <= toSort[pivot])
		{
			i++;    // increment index of smaller element
			swap(&toSort[i], &toSort[j]);
		}
	}
	swap(&toSort[i + 1], &toSort[high]);
	return (i + 1);
}

void quickSort(vector<string>& toSort, int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(toSort, low, high);

		// Separately sort elements before
		// partition and after partition
		quickSort(toSort, low, pi - 1);
		quickSort(toSort, pi + 1, high);
	}
}

bool turnarySearch(vector <string>& sortedVec, string temp)
{
	bool retval = false;
	int start = 0;
	int firstBreak = 0;
	int secondBreak = 0;
	int middle = 0;
	int end = sortedVec.size() - 1;
	middle = (start + end) / 2;
	firstBreak = middle / 2;
	secondBreak = middle + firstBreak;
	while (start <= end)
	{
		if (temp == sortedVec[firstBreak] || temp == sortedVec[secondBreak])
		{
			retval = true;
			break;
		}
		else if (temp < sortedVec[firstBreak])
		{
			end = firstBreak - 1;
			middle = ((end - start) / 2) + start;
			firstBreak = ((middle - start) / 2) + start;
			secondBreak = ((end - middle) / 2) + middle;
		}
		else if (temp > sortedVec[secondBreak])
		{
			start = secondBreak + 1;
			middle = ((end - start) / 2) + start;
			firstBreak = ((middle - start) / 2) + start;
			secondBreak = ((end - middle) / 2) + middle;
		}
		else
		{
			middle = secondBreak - firstBreak;
			start = firstBreak;
			end = secondBreak;
			firstBreak = ((middle - firstBreak) / 2) + firstBreak;
			secondBreak = ((secondBreak - middle) / 2) + middle;
		}
	}

	return retval;
}

//Used to tell whether or not words are already in the vector
bool binarySearch(vector <string>& sortedVec, string temp)
{
	bool retval = false;
	int start = 0;
	int middle = 0;
	int end = sortedVec.size() - 1;
	while (start <= end)
	{
		middle = (start + end) / 2;

		if (temp == sortedVec[middle])
		{
			{
				retval = true;
				break;
			}

		}

		else if (temp < sortedVec[middle])
		{
			end = middle - 1;
		}

		else
		{
			start = middle + 1;
		}
	}
	return retval;
}

int main()
{
	float startTime = clock();
	ifstream firstFileIn;
	ifstream secondFileIn;

	vector<string> firstFileWords;
	vector<string> secondFileWords;

	firstFileIn.open("C:/Users/chuck_000/Documents/Algorithms/FileComparison/COMMUNISM.txt");
	secondFileIn.open("C:/Users/chuck_000/Documents/Algorithms/FileComparison/ARTOFWAR.txt");

	if (!firstFileIn)
	{
		cerr << "Unable to open file one";
		exit(1);
	}

	if (!secondFileIn)
	{
		cerr << "Unable to open file two";
		exit(1);
	}

	while (firstFileIn.good())
	{
		string word;
		firstFileIn >> word;

		//Strip punctuation
		for (unsigned int j = 0; j < word.length(); j++)
		{
			if ((word[j] <= 64 || word[j] >= 91 && word[j] <= 96 || word[j] >= 123) && !(word[j] >= 48 && word[j] <= 57))
			{
				word.erase(j, 1);
				j--;
			}
		}

		//Lower case
		for (unsigned int j = 0; j < word.length(); j++)
		{

			if (word[j] >= 65 && word[j] <= 91)
			{
				word[j] += 32;
			}
		}

		firstFileWords.push_back(word);
	}

	while (secondFileIn.good())
	{
		string word;
		secondFileIn >> word;

		//Strip punctuation
		for (unsigned int j = 0; j < word.length(); j++)
		{
			if ((word[j] <= 64 || word[j] >= 91 && word[j] <= 96 || word[j] >= 123) && !(word[j] >= 48 && word[j] <= 57))
			{
				word.erase(j, 1);
				j--;
			}
		}


		//Lower case
		for (unsigned int j = 0; j < word.length(); j++)
		{

			if (word[j] >= 65 && word[j] <= 91)
			{
				word[j] += 32;
			}
		}

		secondFileWords.push_back(word);
	}

	//Sort FILE1
	quickSort(secondFileWords , 0, secondFileWords.size() - 1);

	//Search FILE1 for the words that appear in FILE2
	int counter = 0;
	for (int i = 0; i < firstFileWords.size(); i++)
	{
		if (turnarySearch(secondFileWords, firstFileWords[i]))
		{
			counter++;
		}
	}

	float endTime = clock();
	cout << counter << " words from the second file are contained in the first file." << endl;

	cout << "Computing this took " << (endTime - startTime)/CLOCKS_PER_SEC << " seconds" << endl;
	system("pause");
	return 0;
}