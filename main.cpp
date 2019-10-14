#include <iostream>
#include <string>
#include <vector>

using namespace std;

int in_vector(string str, vector<string> &v){
    for (int i = 0; i < v.size(); ++i){
        if(str == v[i]){
            return 1;
        }
    }

    return 0;
}

void variations(string &str, vector<string> &v){
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
            cout << aux << endl;
            variations(aux, v);
        }
    }
}

void generate(vector<string> &keywords, size_t max_len, vector<string> &cur){
	if(cur.size() == max_len) {
		return;
	}
	else {
		for(auto c : keywords) {
			vector<string> next;

			for (int i = 0; i < cur.size(); ++i){
				next.push_back(cur[i]);
			}
			next.push_back(c);

			string str;
			if (next.size() == max_len){
				for (int i = 0; i < next.size(); i++){
					cout << next[i];
					str += next[i];
				}
				cout << endl;
			}

			vector<string> v;
			variations(str, v);

			generate(keywords, max_len, next);
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

	cout << "=========================================================" << endl;
    cout << "=                                                       =" << endl;
    cout << "=                  Wordlist Generator                   =" << endl;
   	cout << "=                                                       =" << endl;
   	cout << "=========================================================" << endl << endl;
	
	string skeywords;
	cout << "Enter the keywords: ";
	cin  >> skeywords;
	cout << endl;

	vector<string> keywords = explode(skeywords, ';');
	vector<string> cur;
	
	for (int i = 1; i <= keywords.size(); ++i){
		generate(keywords, i, cur);
	}

	return 0;
}