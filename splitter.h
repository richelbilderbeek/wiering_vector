/* This header depends on the headers "vector.h" and <std::string>. */

#include <cassert>

Vector<std::string> split(const std::string &code, char a = ' ', char b = '\t')
{
	Vector<std::string> v; std::string t = "";
	for(short int f = 1; f <= code.size(); f++)
	{
    assert(f - 1 >= 0);
    assert(f - 1 < static_cast<short int>(code.size()));
		if(code[f - 1] != a && code[f - 1] != b) { t += code[f - 1]; }
    assert(f >= 0);
    assert(f < static_cast<short int>(code.size()));
		if((code[f] == a || code[f] == b) && (code[f - 1] != a && code[f - 1] != b)) { v.add(t); t = "";}
	}
	if(t != "" && t != "\t") { v.add(t); }
	return v;
}
