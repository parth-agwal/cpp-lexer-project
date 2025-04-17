#include<iostream>
#include<fstream>
#include<cctype>
#include<unordered_set>
#include<vector>
using namespace std;

// Set of C++ keywords
const unordered_set<string>keywords={
    "int","float","char","double","if","else","for","while","do",
    "return","switch","case","break","continue","void","class","public", 
    "private","protected","static","struct","typedef","using","namespace"
};

// Set of operators
const unordered_set<string> operators={"+","-","*","/","=","==","!=","<",">","<=",">=","&&","||"};

// Set of delimiters
const unordered_set<char> delimiters={';','(',')','{','}','[',']',',','.'};

// Function to check if a word is a keyword
bool isKeyword(const string &word) 
{
    return keywords.find(word)!=keywords.end();
}

// Function to check if a character is an operator
bool isOperator(char ch) 
{
    return operators.find(string(1, ch))!=operators.end();
}

// Function to check if a character is a delimiter
bool isDelimiter(char ch) 
{
    return delimiters.find(ch)!=delimiters.end();
}

// Function to process and extract tokens
vector<string> tokenize(const string &filename) 
{
    ifstream file(filename);
    if(!file) 
    {
        cout<<"Error opening file: "<<filename<<endl;
        return {};
    }
    vector<string>tokens;
    string word;
    char ch;
    bool inComment=false;
    bool inString=false;
    while(file.get(ch)) 
    {
        // Handle preprocessor directives (e.g., #include <iostream>)
        if (ch == '#') 
        {
            string directive;
            directive+=ch;
            while(file.get(ch)&&(isalnum(ch)||ch=='<'||ch=='>'||ch=='.'))
            directive+=ch;
            tokens.push_back("PREPROCESSOR("+directive+")");
            continue;
        }

        // Handle string literals
        if(ch=='"') 
        {
            string strLit;
            strLit+=ch;
            while(file.get(ch)&&ch!='"')
            strLit+=ch;
            strLit+=ch;  // Include the closing quote
            tokens.push_back("STRING_LITERAL("+strLit+")");
            continue;
        }

        // Handle character literals ('A')
        if(ch=='\'') 
        {
            string charLit;
            charLit+=ch;
            if(file.get(ch)&&file.peek()=='\'') 
            {
                charLit+=ch;
                file.get(ch);  // Consume closing quote
                charLit+=ch;
                tokens.push_back("CHAR_LITERAL("+charLit+")");
            }
            continue;
        }

        // Handle single-line comments (//)
        if(ch=='/'&&file.peek()=='/') 
        {
            while(file.get(ch)&&ch!='\n');  // Skip to the end of the line
            continue;
        }

        // Handle multi-line comments (/* ... */)
        if(ch=='/'&&file.peek()=='*') 
        {
            inComment=true;
            file.get(ch); // Skip '*'
            continue;
        }
        if(inComment) 
        {
            if(ch=='*'&&file.peek()=='/') 
            {
                inComment=false;
                file.get(ch); // Skip '/'
            }
            continue;
        }

        // Handle identifiers and keywords
        if(isalnum(ch)||ch=='_') 
        {
            word+=ch;
        }
        else 
        {
            if(!word.empty()) 
            {
                if(isKeyword(word)) 
                {
                    tokens.push_back("KEYWORD("+word+")");
                } 
                else if(isdigit(word[0])) 
                {
                    tokens.push_back("NUMBER("+word+")");
                } 
                else 
                {
                    tokens.push_back("IDENTIFIER("+word+")");
                }
                word.clear();
            }

            // Handle multi-character operators (e.g., >=, <=, ==, !=, &&, ||)
            if (isOperator(ch)) 
            {
                string op(1,ch);
                if (isOperator(file.peek())) 
                {
                    file.get(ch);
                    op+=ch;
                }
                tokens.push_back("OPERATOR("+op+")");
            }
            // Handle delimiters
            else if (isDelimiter(ch)) 
            {
                tokens.push_back("DELIMITER("+string(1,ch)+")");
            }
        }
    }

    file.close();
    return tokens;
}

int main() {
    string filename="input.txt";  // Change this to your input file
    vector<string> tokens=tokenize(filename);
    cout << "Tokens:\n";
    for (const auto &token : tokens) {
        cout<<token<<endl;
    }

    return 0;
}