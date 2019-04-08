/* This header depends on the headers "vector.h" and <std::string>. */

Vector<std::string> split(const std::string &code)
{
	Vector<std::string> v; std::string t = "";
	for(unsigned short int f = 1; f <= code.size(); f++)
	{
		if(code[f - 1] != ' ' && code[f - 1] != '\t') { t += code[f - 1]; }
		if((code[f] == ' ' || code[f] == '\t') && (code[f - 1] != ' ' && code[f - 1] != '\t')) { v.add(t); t = "";}
	}
	if(t != "" && t != "\t") { v.add(t); }
	return v;
}
