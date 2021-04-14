#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <locale>
#include <vector>

#include "main.hpp"
#include "cword.hpp"

#define G_FILE_EXTENSION ".txt"

int main(int argc, char* argv[])
{
	char entity;

    std::string current_exec_name = argv[0]; // Name of the executable
    std::string filename;
    std::FILE* outputf = stdout;
    if(argc > 1)
    {
        // Later will need to support flags
        // "-o" lets you output into a file instead of stdout
        // should redesign later to support something like "-owd" or "-o -w -d" <- bit toggle flags
        for(int i = 1; i < (argc - 1); ++i)
        {
            if(0 == strcmp(argv[i], "-o"))
            {
                if((i+1) == (argc-1))
                {
                    printf("You did not provide a valid output file... try again!\n");
                    exit(EXIT_FAILURE);
                }
                outputf = fopen(argv[i+1], "w"); 
                break;
            }
        }

        // Name of the requested file
        filename = argv[argc - 1];
        size_t found = filename.find_last_of(".");
        if(filename.substr(found) != G_FILE_EXTENSION)
        {
            printf("\"%s\" was not an acceptable file extension. \nPlease parse a file with an acceptable file extension.\n", filename.substr(found).c_str());
            exit(EXIT_FAILURE);
        }
    } 
    else 
    {
        printf("You forgot the file!\n");
        exit(EXIT_FAILURE);
    }

    std::ifstream inputf(filename);
    if(!inputf)
    {
        printf("Failed to open the input file...\n");
        exit(EXIT_FAILURE);
    }

	fprintf(outputf, "%-15s   %-15s\n\n", "TOKENS", "Lexemes");

	std::vector<char> word; // this will push characters into a vector for when word is being processed...
	bool wordFormulation = false; // this will be a sentry value to check if word formulation is being done, default false.
    std::vector<CWord> lexemes;
	while (inputf.eof() == false) // go through input.txt and read each word.
	{
		inputf >> entity;
		if (entity == '!')
		{
			ignoreComment(entity, inputf);
			continue;
		}
		if (isOperator(entity))
		{
			fprintf(outputf, "%-15s = %-15c\n", "OPERATOR", entity);
            lexemes.push_back(CWord(outputf, entity, ""));
		}
		else if (isSeperator(entity))
		{
			fprintf(outputf, "%-15s = %-15c\n", "SEPERATOR", entity);
            lexemes.push_back(CWord(outputf, entity, ""));
		}
		else do //most likely a word or number, start building the word using characters
		{
			wordFormulation = true;
			word.push_back(entity);
			inputf >> std::noskipws >> entity;
		} while (!isOperator(entity) && !isSeperator(entity) && entity != ' ' && entity != '\n' && inputf.eof() == false); // keep looping until a seperator, operator or whitespace is encountered....

		if(wordFormulation == true) 
		{
			std::string wordString(word.begin(), word.end()); //convert character vector to string for reading in functions
            lexemes.push_back(CWord(outputf, entity, wordString.c_str()));
			word.clear(); // clear word
			wordFormulation = false;
			inputf >> std::skipws; // re-enable whitespace skipping for next iteration
		}
	}

    lexemes.begin();
    for (unsigned long int cooper : lexemes.size())
    {
        printf("%s\n", lexemes[cooper].showLexemes());
    }

	inputf.close();
	return 0;
}