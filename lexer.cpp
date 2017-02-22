/************************************************************************/
/* Class           : lexer.cpp						*/
/* Description     : Read stdin and create pile of symbole 		*/
/* Depend of files : 							*/
/* Date creation   : 15/02/2017						*/
/* Authors         : Aparicio Christopher and Nathan Haim		*/
/************************************************************************/

//---------- Réalisation de la classe Lexer (fichier Lexer.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <string>
#include <cctype>
#include <stdio.h>
#include <fstream>

using namespace std;

//------------------------------------------------------ Include personnel
#include "lexer.h"

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques



//----- Constructeur
Lexer::Lexer()
{
    
}
//----- Fin constructeur

Symbole* Lexer::getNext()
{
	if(this->lexed)
	{
		return this->stackSymbole.top();
	}
	else
	{
		return NULL;
	}
}

int Lexer::next()
{
	if(this->lexed)
	{
		this->stackSymbole.pop();
		if(this->stackSymbole.empty())
		{
			this->lexed = false;
		}
		return 0;
	}
	else
	{
		return -1;
	}
}


//----- playLexer
void Lexer::playLexer()
{
	string str;
	int c;
	std::ifstream is;
	bool lastWasDigit = false;
	while( c = getchar())
	{
		if(c==EOF)
		{

			break;
		}
		else if(c == TAB || c==SPACE || c==BACKSPACE) {			cout << "end of file" << endl; break;}
		else if ( c >= MIN_INT && c <= MAX_INT )//is int
		{	
			str = (char)c;	
			while(c = cin.peek())
			{
				if( c >= MIN_INT && c <= MAX_INT)
				{	
					getchar();
					str+= (char)c;
				}
				else
				{
					break;
				}
			}
			this->stackSymbole.push(new Number(stoi(str)));
			Symbole* s = this->stackSymbole.top();
			cout << "get info : "  << s->getInfo()<< endl;
			cout <<  str << endl;
			
		}
		else if (c == O_PARENTH || c == F_PARENTH || c== MULT || c == PLUS)
		{	
			switch(c)
			{
				case O_PARENTH: this->stackSymbole.push(new OuvrePar());break;
				case F_PARENTH: this->stackSymbole.push(new FermePar());break;
				case MULT: this->stackSymbole.push(new Mult());break;
				case PLUS: this->stackSymbole.push(new Plus());break;
			}
			str= (char)c;
			cout <<  str << endl;
		}
	}
	
	if(!this->stackSymbole.empty())
	{
		lexed = true;
	}
	else
	{
		lexed = false;
	}
	
}



//----- Destructeur
Lexer::~Lexer()
{}// Bloc vide
//----- Fin destructeur