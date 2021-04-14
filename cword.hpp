// ======================================================================================
// File Name: cword.h
// Group Members: Cooper Santillan
// Date Created: February 11, 2021 10:00PM
// Date Modified: March 04, 2021 11:15PM
// Program Name: Assignment 01
// Program Description:
// 
//
// 
// ======================================================================================
#include <cctype>
#include <cstdlib>


enum TOKENS {KEYWORDS, IDENTITFIER, SEPARATORS, OPERATORS, REALNUM, INTEGER, UNKNOWN};
const char reservedWords[21][10] = {"int", "float", "bool", "True", "False", "if", "else", 
                                    "then", "endif", "endelse", "while", "whileend", "do", 
                                    "enddo", "for", "endfor", "STDinput", "STDoutput", 
                                    "and", "or", "not"};


typedef union {
    char index;
    int iVal;
    float fVal;
} DataStore;

struct CWord {
    CWord(std::FILE *outputf, char &entity, const char* wordString);
    // ~CWord();
    const char* showToken();
    const char* showLexemes();
    DataStore m_value;
    char *m_identifier;
    int m_token;
};

// CWord::~CWord()
// {
//     if(m_identifier != NULL)
//     {
//         // cout << m_identifier << endl;
//         delete m_identifier;
//     }
// }

CWord::CWord(std::FILE *outputf, char &entity, const char* wordString)
{
    this -> m_identifier = NULL;
    this -> m_value.index = 0;
    if (isInteger(wordString))
    {
        this -> m_token = INTEGER;
        this -> m_value.iVal = atoi(wordString);
    }
    else if (isRealNumber(wordString))
    {
        this -> m_token = REALNUM;
        this -> m_value.fVal = atof(wordString);
    }
    else if (isKeyword(wordString))
    {
        int counter = 0;
        for(const char* i :reservedWords)
        {
            if((strcmp(i, wordString)) == 0)
            {
                this -> m_token = KEYWORDS;
                this -> m_value.index = counter;
                return;
            }
            counter++;
        }
    }
    else if (isIdentifier(wordString))
    {
        this -> m_token = IDENTITFIER;
        this -> m_identifier = new char[strlen(wordString) + 1];
        strcpy(this -> m_identifier, wordString);
    }
    if (isOperator(entity))
    {
        this -> m_token = OPERATORS;
        this -> m_value.index = entity;
    }
    else if (isSeperator(entity))
    {
        this -> m_token = SEPARATORS;
        this -> m_value.index = entity;
    }
}

const char* CWord::showToken()
{
    switch (this -> m_token)
    {
        case KEYWORDS:
            return "KEYWORD";
            break;
        case IDENTITFIER:
            return "IDENTITFIER";
            break;
        case SEPARATORS:
            return "SEPARATOR";
            break;
        case OPERATORS:
            return "OPERATOR";
            break;
        case INTEGER:
            return "INTEGER";
            break;
        case REALNUM:
            return "REAL NUMBER";
            break;
        default:
            return "UNKNOWN TOKEN";
    }
}

const char* CWord::showLexemes()
{
    switch (this -> m_token)
    {
        case KEYWORDS:
            return reservedWords[(int)m_value.index];
            break;
        case INTEGER:
            return std::to_string(m_value.iVal).c_str();
            break;
        case REALNUM:
            return std::to_string(m_value.fVal).c_str();
            break;
        case OPERATORS:
        case SEPARATORS:
            return &m_value.index;
            break;
        case UNKNOWN:
            return " ";
            break;
        default:
            return m_identifier;
    }

}