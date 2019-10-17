#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

int in_vector(string str, vector<string> &v){
    for (int i = 0; i < v.size(); ++i){
        if(str == v[i]){
            return 1;
        }
    }

    return 0;
}

void variations(string &str, vector<string> &v, ofstream &file, size_t &nP){
    for (int i = 0; i < str.size(); i++){
        string aux = str;

        switch(aux[i]){
            case 'a':
                aux[i] = '@';
                break;
            case 'b':
                aux[i] = '3';
                break;
            case 's':
                aux[i] = '5';
                break;
            case 'i':
                aux[i] = '1';
                break;
            case 'e':
                aux[i] = '&';
                break;
            case 'o':
                aux[i] = '0';
                break;
        }

        if(!in_vector(aux, v) && aux != str){
            v.push_back(aux);
            file << aux << endl;
            nP++;
            variations(aux, v, file, nP);
        }
    }
}

void generate(vector<string> &keywords, size_t len, vector<string> &cur, ofstream &file, size_t &nP){
	if(cur.size() == len) {
		return;
	}
	else {
		for(string c : keywords) {
			vector<string> next;

			for (int i = 0; i < cur.size(); ++i){
				next.push_back(cur[i]);
			}
			next.push_back(c);
	
			string str;
			for (int i = 0; i < next.size(); i++){
				str += next[i];
			}
			
			file << str << endl;
			nP++;

			vector<string> v;
			variations(str, v, file, nP);

			generate(keywords, len, next, file, nP);
		}
	}
}

vector<string> explode(string w, char delimiter){
	vector<string> vkeywords;
	string keyword;

	for (int i = 0; i < w.size(); i++)
	{
		if(w[i] == delimiter){
			vkeywords.push_back(keyword);
			keyword.clear();
		}else {
			keyword += w[i];
		}
	}
	vkeywords.push_back(keyword);

	return vkeywords;
}


int main(int argc, char **argv){

	cout << " =========================================================" << endl;
    cout << " =                                                       =" << endl;
    cout << " =                  Wordlist Generator                   =" << endl;
   	cout << " =                                                       =" << endl;
   	cout << " =========================================================" << endl << endl;
	
	string skeywords;
	cout << "ENTER THE KEYWORDS: ";
	cin  >> skeywords;

	vector<string> keywords = explode(skeywords, ';');
	vector<string> cur;

	ofstream file;
	file.open("wordlist.txt",  ios::out);

	cout << endl;
	cout << "- Generating wordlist..." << endl;
	
	clock_t t = clock();
	size_t nP = 0;

	generate(keywords, keywords.size(), cur, file, nP);
	file.close();
	
	cout << "- Generated wordlist!" << endl;
	cout << "  Elapsed time " << (float)(clock() - t)/CLOCKS_PER_SEC << "s" << endl;
	cout << "  Total passwords " << nP << endl;

	return 0;
}