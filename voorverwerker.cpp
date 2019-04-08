#include <iostream>
#include <fstream>
#include "vector.h"
#include "splitter.h"
using namespace std;
//#include "splitterTEMP.h"

typedef unsigned short int kint;

bool ontbeest = 1, in_commentaar = false;

void log(string tekst) { if(ontbeest) { cout << tekst << endl; } }

bool LegeLijn(string lijn)
{
	for(kint i = 0; i < lijn.size(); i++)
	{
		if(lijn[i] != ' ' && lijn[i] != '\t') { return false; }
	}
	return true;
}

bool ZitHerErin(string lijn, string argument)
{
	for(kint i = 0, j = 0; i < lijn.size(); i++)
	{
		if(lijn[i] == argument[j]) { j++; if(j == argument.size()){ return true; } }
		else { j = 0; }
	}
	return false;
}

string NegeerCommentaar(string lijn)
{
	string nieuwe_lijn = "";
	bool in_citaat = false;
	
	for(kint i = 0; i < lijn.size(); i++)
	{
		if(lijn[i] == '"' && !in_commentaar) { in_citaat ? in_citaat = false: in_citaat = true; nieuwe_lijn += lijn[i]; }
		else if(in_citaat) { nieuwe_lijn += lijn[i]; }
		else if(lijn[i] == '/' && lijn[i+1] == '/') { return nieuwe_lijn; }
		else if(lijn[i] == '/' && lijn[i+1] == '*') { in_commentaar = true; }
		else if(lijn[i] == '*' && lijn[i+1] == '/') { in_commentaar = false; i++; }
		else if(!in_commentaar) { nieuwe_lijn += lijn[i]; }
	}
	
	return nieuwe_lijn;
}

string GeefDeelString(string lijn, kint beginpunt, kint eindpunt)
{
	if(beginpunt > eindpunt) { kint x = beginpunt; beginpunt = eindpunt; eindpunt = x; }
	string nieuwe_lijn = "";
	for(kint i = beginpunt; i <= eindpunt; i++)
	{
		nieuwe_lijn += lijn[i];
	}
	return nieuwe_lijn;
}

struct definieer
{
	definieer(string a = "", string b = "") { trefwoord = a; vervang_door = b; }
	string trefwoord, vervang_door;
};

string VindEnVervang(string lijn, definieer doosje)
{
	string trefwoord = doosje.trefwoord;
	string vervang_door = doosje.vervang_door;
	
	if(lijn.size() < trefwoord.size()) { return lijn; }
	
	string nieuwe_lijn = "";
	for(int i = 0; i <= lijn.size(); i++)
	{
		//cout << "i: " << i << "\tlijn[i]: " << lijn[i] << endl;
		if(lijn[i] == trefwoord[0] && lijn[i+trefwoord.size()-1] == trefwoord[trefwoord.size()-1])
		{
			string s = GeefDeelString(lijn, i, i+trefwoord.size()-1);
			//cout << "s is " << s << endl;
			if(s == trefwoord) { nieuwe_lijn += vervang_door; i += trefwoord.size()-1; }
			else { nieuwe_lijn += lijn[i]; }
		}
		else { nieuwe_lijn += lijn[i]; }
	}
	
	return nieuwe_lijn;
}


string VindEnVervang(string lijn, string trefwoord, string vervang_door)
{
	if(lijn.size() < trefwoord.size()) { return lijn; }
	
	string nieuwe_lijn = "";
	for(int i = 0; i <= lijn.size(); i++)
	{
		//cout << "i: " << i << "\tlijn[i]: " << lijn[i] << endl;
		if(lijn[i] == trefwoord[0] && lijn[i+trefwoord.size()-1] == trefwoord[trefwoord.size()-1])
		{
			string s = GeefDeelString(lijn, i, i+trefwoord.size()-1);
			//cout << "s is " << s << endl;
			if(s == trefwoord) { nieuwe_lijn += vervang_door; i += trefwoord.size()-1; }
			else { nieuwe_lijn += lijn[i]; }
		}
		else { nieuwe_lijn += lijn[i]; }
	}
	
	return nieuwe_lijn;
}

int main(int argc, char* argv[])
{
	if(argc >= 2) { ontbeest = atoi(argv[1]); }
	
	Vector<definieer> doosje;
	
	while(!cin.eof())
	{
		string code = "";
		cout << "Geef een tekst: ";
		getline(cin, code);
		code = NegeerCommentaar(code);
		if(ZitHerErin(code, "#define"))
		{
			log("if(ZitHerErin(code, \"#define\"))");
			Vector<string> rij = split(code);
			log("Vector<string> rij = split(code);");
			if(rij.index(0) == "#define" && rij.size() == 3)
			{ doosje.add(definieer(rij.index(1),rij.index(2))); continue; }
		}
		else if(ZitHerErin(code, "#include"))
		{
			Vector<string> rij = split(code);
			log("Komt de code hier?");
			if(rij.index(0) == "#include" && rij.size() == 2)
			{
				string lijn = "";
				cout << "string lijn = \"\";" << endl;
				ifstream bestand(rij.get(1));
				cout << "ifstream bestand(rij.get(1));" << endl;
				if(bestand.is_open())
				{
					while(getline(bestand, lijn)) { cout << lijn << endl; }
					bestand.close();
				}
				else { cout << "Kon " << rij.get(1) << " niet vinden!" << endl; }
			}
		}
		
		if(!LegeLijn(code))
		{
			for(kint i = 0; i < doosje.size(); i++)
			{ code = VindEnVervang(code, doosje.get(i).trefwoord, doosje.get(i).vervang_door); }
			
			cout << code << endl;
		}
		
		
	}
	
	while(!cin.eof())
	{
		string s = "";
		cout << "Geef een tekst: ";
		getline(cin, s);
		s = NegeerCommentaar(s);
		if(!LegeLijn(s))
		{ cout << VindEnVervang(s, "Willem", "Sjaak") << endl << endl; }
	}
	//cout << GeefDeelString(s, 0, 4) << endl;
	
	return 0;
}
