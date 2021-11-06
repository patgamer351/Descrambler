//descrambler
#include <iostream>
#include <fstream>

#ifdef __WIN32
	#define CLEAR() system("cls")

#elif __APPLE__ || __unix__
		#define CLEAR() system("clear");
#else
		#define CLEAR()
		std::cout<<"Can't clear, but ima just test system(\"clear\")"<<std::endl;
		system("clear");
#endif

void search(std::string word, int length)
{
	std::string line, Alphabet = "abcdefghijklmnopqrstuvwxyz";
	int OtherWordList[Alphabet.length()], list[Alphabet.length()], arrsize = 0, LargestWordSize;
	std::string PossibleWords[arrsize];
	bool viability;
	std::ifstream file("words.txt");
	
	for(int i = 0; i < Alphabet.length(); i++) // creates an array for the users word
	{
		list[i] = 0;
	}
	for(int i = 0; i < word.length(); i++)
	{
		list[int(word.at(i))-97]++;
	}
	if(file.is_open())
	{
		while(getline(file, line))
		{
			viability = true;

			for(int i = 0; i < Alphabet.length(); i++) // creates/resets an array for the word in the list
			{
				OtherWordList[i] = 0;
			}
			for(int i = 0; i < line.length(); i++) // add the values onto the list
			{
				OtherWordList[int(line.at(i))-97]++;
			}

			for(int i = 0; i < Alphabet.length(); i++)
			{
				if(list[i] < OtherWordList[i]) // checks if it contains more letters than the word that the user gave it
				{
					viability = false;
					break;
				}
			}
			if(viability == true)
			{
				if(line.length() > LargestWordSize)
				{
					LargestWordSize = line.length();
				}

				std::string* TempArray = new std::string[arrsize + 1];
				std::copy(PossibleWords, PossibleWords + std::min(arrsize, arrsize + 1), TempArray);	
				delete[] PossibleWords;
				TempArray = PossibleWords;
				arrsize++;
				PossibleWords[arrsize] = line;
			}
		}
		for (int i = 0; i < LargestWordSize; i++)
		{
			for (int i = 0; i < arrsize; i++)
			{
				if(PossibleWords[i].length() == LargestWordSize - i)
				{
					std::cout<<PossibleWords[i];
				}
			}
			
		}
		
	}
	else
	{
		std::cout<<"Error opening file!";
		std::cin.ignore();
		std::cin.get();
	}
	file.close();
}

int main()
{
	std::string word, line;
	const std::string Alphabet = "abcdefghijklmnopqrstuvwxyz";
	bool viability;
	int list[Alphabet.length()], OtherWordList[Alphabet.length()];
	while(true)
	{
		CLEAR();
		std::cout<<"Enter your word: "; 
		std::cin>>word;

		for(int i = 0; i < word.length(); i++)
		{
			search(word, word.length()-i);
		}
		std::cin.ignore();
		std::cin.get();
	}
}
