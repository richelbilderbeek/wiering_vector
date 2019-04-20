#include <iostream>
#include <fstream>
#include "vector.h"
#include "splitter.h"
using namespace std;
//#include "splitterTEMP.h"

typedef unsigned short int kint;

bool ontbeest = 1, in_commentaar = false, negeren = false;
string VindEnVervang(string, string, string);

void log(string tekst) { if(ontbeest) { cout << tekst << endl; } }

bool LegeLijn(string lijn)
{
	for(kint i = 0; i < lijn.size(); i++)
	{
		if(lijn[i] != ' ' && lijn[i] != '\t') { return false; }
	}
	return true;
}

bool ZitHetErin(string lijn, string argument)
{
	for(kint i = 0, j = 0; i < lijn.size(); i++)
	{
		if(lijn[i] == argument[j]) { j++; if(j == argument.size()){ return true; } }
		else { j = 0; }
	}
	return false;
}

string MacroWaarde(string s)
{
	string macrowaarde = "";
	bool binnen = false;
	for(kint i = 0; i < s.size(); i++)
	{
		if(s[i] == '(') { binnen = true; continue; }
		else if(s[i] == ')') { binnen = false; break; }
		else if(binnen) { macrowaarde += s[i]; }
	}
	
	return macrowaarde;
}

bool IsMacro(string s)
{
	bool haakje_geopend = false, haakje_gesloten = false;
	int p = 0;
	if(s[0] == '(' || s[0] == ')') { return false; }
	
	for(kint i = 1; i < s.size(); i++)
	{
		if(s[i] == '(') { haakje_geopend = true; p++; }
		else if(s[i] == ')' && haakje_geopend && i == s.size() - 1) { haakje_gesloten = true; p--; }
	}
	
	if(haakje_geopend && haakje_gesloten && p == 0) { return true; }
	else { return false; }
	
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

string ZuiverMacrowoord(string s)
{
	string nieuw_woord = "";
	
	for(kint i = 0; i < s.size(); i++)
	{
		nieuw_woord += s[i];
		if(s[i] == '(') { break; }
	}
	
	return nieuw_woord;
}

struct definieer
{
	definieer(string a = "", string b = "") { trefwoord = a; vervang_door = b; }
	string trefwoord, vervang_door;
};

bool Vind(string lijn, string w)
{
	for(kint i = 0, j = 0; i < lijn.size(); i++)
	{
		if(lijn[i] == w[j]) { j++; if(j == w.size()){ return true; break; } }
		else { j = 0; }
	}
	return false;
}

string VerkrijgMacrowoord(string lijn, string macrowoord)
{
	string nieuw_woord = macrowoord;
	kint eindpositie = 0;
	
	for(kint i = 0, j = 0; i < lijn.size(); i++)
	{
		if(lijn[i] == nieuw_woord[j]) { j++; if(j == nieuw_woord.size()){ eindpositie = i+1; break; } }
		else { j = 0; }
	}
	if(eindpositie == 0) { return ""; }
	
	for(kint i = eindpositie; i < lijn.size() ; i++)
	{
		nieuw_woord += lijn[i];
		if(lijn[i] == ')') { break; }
	}
	
	return nieuw_woord;
}

string VindEnVervang(string lijn, definieer doosje)
{
	string trefwoord = doosje.trefwoord;
	string vervang_door = doosje.vervang_door;
	
	if(lijn.size() < trefwoord.size()) { return lijn; }
	
	string nieuwe_lijn = "";
	for(kint i = 0; i < lijn.size(); i++)
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
	for(kint i = 0; i < lijn.size(); i++)
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

void print(string lijn, string uitvoerbestand)
{
	ofstream uitvoer(uitvoerbestand);
	uitvoer << lijn << endl;
	uitvoer.close();
}

string Omdraaier(string zin)
{
	string nieuwe_zin = "";
	for(int i = zin.size() - 1; i >= 0; i--)
	{
		nieuwe_zin += zin[i];
		if(i == 0) { break; }
	}
	return nieuwe_zin;
}

string ZuivereNaam(string s)
{
	string nw = "";
	for(int i = s.size() - 1; i >= 0; i--)
	{
		if(s[i] == '/') { break; }
		nw += s[i];
		if(i == 0) { break; }
	}
	nw = Omdraaier(nw);
	return nw;
}

string VerwijderExtensie(string s)
{
	string nw = "";
	for(kint i = 0; i < s.size(); i++)
	{
		if(s[i] == '.') { break; }
		nw += s[i];
	}
	return nw;
}

int main(int argc, char* argv[])
{
	string invoerbestand = "negeercommentaar.cpp", uitvoerbestand = "test.txt", lijn = "";
	if(argc >= 3) { invoerbestand = argv[1]; uitvoerbestand = argv[2]; }
	
	
	Vector<definieer> doosje;
	Vector<definieer> doosje2;
	Vector<string> gedefinieerd;
	
	string invoercode = ZuivereNaam(invoerbestand);
	//cout << "invoercode: " << invoercode << endl;
	invoercode = VerwijderExtensie(invoercode);
	//cout << "invoercode: " << invoercode << endl;
	
	string uitvoercode = ZuivereNaam(uitvoerbestand);
	//cout << "uitvoercode: " << uitvoercode << endl;
	uitvoercode = VerwijderExtensie(uitvoercode);
	//cout << "uitvoercode: " << uitvoercode << endl;
	
	ofstream uitvoer(uitvoerbestand);
	ifstream bestand(invoerbestand);
	
	if(bestand.is_open())
	{
		while(getline(bestand, lijn))
		{
			string macrowoord = "", code = lijn;
			code = NegeerCommentaar(code);
			if(ZitHetErin(code, "#define"))
			{
				Vector<string> rij = split(code);
				if(rij.index(0) == "#define" && rij.size() >= 2)
				{
					gedefinieerd.add_unique(rij.index(1));
				}
				
				if(rij.index(0) == "#define" && IsMacro(rij.index(1)))
				{
					rij.remove(0);
				
					string lichaam = "";
					for(kint i = 1; i < rij.size(); i++)
					{ lichaam += rij.index(i) + " "; }
				
					doosje2.add(definieer(rij.index(0), lichaam));
				}
				else if(rij.index(0) == "#define" && rij.size() == 3)
				{ doosje.add(definieer(rij.index(1),rij.index(2))); }
				continue;
			}
			else if(ZitHetErin(code, "#undef"))
			{
				Vector<string> rij = split(code);
				if((rij.index(0) == "#undef" || rij.index(0) == "#undefine") && rij.size() == 2)
				{
					for(kint i = 0; i < doosje.size(); i++)
					{ if(doosje.index(i).trefwoord == rij.index(1)) { doosje.remove(i); } }
					
					for(kint i = 0; i < doosje2.size(); i++)
					{ if(doosje2.index(i).trefwoord == rij.index(1)) { doosje2.remove(i); } }
					
					gedefinieerd.removeAll(rij.index(1));
				}
				continue;
			}
			else if(ZitHetErin(code, "#ifdef"))
			{
				Vector<string> rij = split(code);
				if(rij.index(0) == "#ifdef" && rij.size() == 2)
				{
					if(! gedefinieerd.contains(rij.index(1))) { negeren = true; }
				}
				continue;
			}
			else if(ZitHetErin(code, "#ifndef"))
			{
				Vector<string> rij = split(code);
				if(rij.index(0) == "#ifndef" && rij.size() == 2)
				{
					if(gedefinieerd.contains(rij.index(1))) { negeren = true; }
				}
				continue;
			}
			else if(ZitHetErin(code, "#endif")) { negeren = false; continue; }
			else if(ZitHetErin(code, "#include"))
			{
				Vector<string> rij = split(code);
				if(rij.index(0) == "#include" && rij.size() == 2)
				{
					string lijn = "";
					ifstream bestand2(rij.get(1));
					if(bestand2.is_open())
					{
						while(getline(bestand2, lijn)) { uitvoer << lijn << endl; }
						bestand2.close(); continue;
					}
					else { cerr << "Kon " << rij.get(1) << " niet vinden!" << endl; }
				}
			}
			else if(ZitHetErin(code, "public class " + invoercode))
			{
				//cout << "Komt de code hier ooit?" << endl;
				code = VindEnVervang(code, "public class " + invoercode, "public class " + uitvoercode);
			}
		
			if(!LegeLijn(code))
			{
				for(kint i = 0; i < doosje.size(); i++)
				{ code = VindEnVervang(code, doosje.get(i).trefwoord, doosje.get(i).vervang_door); }
				
				for(kint i = 0; i < doosje2.size(); i++)
				{
					string macronaam = ZuiverMacrowoord(doosje2.index(i).trefwoord);
					if(Vind(code, macronaam))
					{
						string verkregen_macro = VerkrijgMacrowoord(code, macronaam);
						string verkregen_macro_argumenten = MacroWaarde(verkregen_macro);
						Vector<string> argumenten = split(verkregen_macro_argumenten, ' ', ',');
						
						string onze_macro = doosje2.index(i).trefwoord;
						string onze_macro_argumenten = MacroWaarde(onze_macro);
						Vector<string> onze_argumenten = split(onze_macro_argumenten, ' ', ',');
						
						string lichaam = doosje2.index(i).vervang_door;
						if(argumenten.size() == onze_argumenten.size())
						{
							for(kint i = 0; i < argumenten.size(); i++)
							{
								lichaam = VindEnVervang(lichaam, onze_argumenten.index(i), argumenten.index(i));
							}
						}
						
						code = VindEnVervang(code, verkregen_macro, lichaam);
					}
				}
				//cout << "UITVOER: " << code << endl;
				//uitvoer << code << endl;
				if(!negeren) { uitvoer << code << endl; }
			}
		}
		bestand.close();
		uitvoer.close();
	}
	else
	{
		cout << "Kon " << invoerbestand << " niet vinden!" << endl;
	}
	
	return 0;
}
