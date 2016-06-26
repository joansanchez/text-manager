#include "Text.hh"

struct aparicions{
	int vegades;
    vector<int> files;
};

void normalitzarttl (string& linia){
	size_t found = linia.find(".");
	while (found != string::npos){
		linia.replace(found, 1, " . ");
		found =linia.find(".", found+2);
	}
	found = linia.find(",");
	while (found != string::npos){
		linia.replace(found, 1, " , ");
		found =linia.find(",", found+2);
	}
	found = linia.find(";");
	while (found != string::npos){
		linia.replace(found, 1, " ; ");
		found =linia.find(";", found+2);
	}
	found = linia.find(":");
	while (found != string::npos){
		linia.replace(found, 1, " : ");
		found =linia.find(":", found+2);
	}
	found = linia.find("?");
	while (found != string::npos){
		linia.replace(found, 1, " ? ");
		found =linia.find("?", found+2);
	}
	found = linia.find("!");
	while (found != string::npos){
		linia.replace(found, 1, " ! ");
		found =linia.find("!", found+2);
	}
}

bool comp(const pair<string, int>& elem1, const pair<string, int>& elem2){
	if (elem1.second == elem2.second){
		if (elem2.first.size() == elem1.first.size()){
			return elem2.first > elem1.first;
		}
		else return elem1.first.size() < elem2.first.size();
	}
	else return elem1.second > elem2.second;
}
Text::Text(){}
Text::Text(string titoltxt,string autortxt,vector<vector<string> > contingutaux){
    titol = titoltxt;
    autor = autortxt;
    contingut = contingutaux;
    string nomautor;
	istringstream issini(autortxt);
	while (issini >> nomautor){
		inicials_priv += nomautor[0];
	}

    string comanda = titoltxt;
    normalitzarttl(comanda);
	istringstream a1(comanda);
	while (a1 >> comanda){
		paraules.insert(comanda);
	}
	string autoraux = autortxt;
	istringstream a2(autoraux);
	while (a2 >> autoraux){
		paraules.insert(autoraux);
	}
	
	taulafrequs(contingutaux); //cridem a taula de freqüències per a deixar-la ja creada

} 	

Text::~Text(){}
 

void Text::taulafrequs (vector<vector<string> > continguttxt){//test this shit
	num_frases = 0;
	num_paraules = 0;
	map <string, aparicions > mapfreqaux;
    for (int i = 0; i < int(continguttxt.size()); ++i) {
        num_frases += 1;
	    for (int j = 0; j < int(continguttxt[i].size()); ++j){
		    string auxiliar = continguttxt[i][j];
		    if (auxiliar == ".");
		    else if (auxiliar == "," or auxiliar == ";" or auxiliar == ":" or auxiliar == "?" or auxiliar == "!"); 
		    else if (j == int(continguttxt[i].size()-1)){}
		    else {
		    	num_paraules += 1;
		    	map <string, aparicions>::iterator it = mapfreqaux.find(auxiliar) ;
		    	if (it != mapfreqaux.end()){
		   			mapfreqaux[auxiliar].vegades +=1;
		   			mapfreqaux[auxiliar].files.insert(i+1);

				}
		    	else {
		    		mapfreqaux[auxiliar].vegades = 1; 
		    		mapfreqaux[auxiliar].files.insert(i+1);
		    	}
		    	
		    }
		    
		    
		}
	}
	mapfreq = mapfreqaux; //ho passem a vector per a fer més ràpida la lectura en les seves pertinents funcions
	vector <pair<string,int> > taulafreqaux;
	for (map <string, aparicions >::iterator tfav = mapfreq.begin(); tfav != mapfreq.end(); ++tfav){
		taulafreqaux.push_back(make_pair(tfav->first,tfav->second.vegades));
	}
	taulafreq = taulafreqaux;
	sort (taulafreq.begin(), taulafreq.end(), comp);
}

void Text::substitueix(string paraula1, string paraula2){
	for (int i=0;i<int(contingut.size());++i){
		for (int j=0;j<int(contingut[i].size());++j){
			if (contingut[i][j] == paraula1){
				contingut[i][j] = paraula2;
			}
		}
	}
	taulafrequs(contingut);//tornem a passar la taula de freqüències per deixar plasmats els canvis realitzats
}

bool Text::conteParaules(vector <string>paraulesbuscar){
	int conter = 0;
	for(int s = 0; s < int(paraulesbuscar.size()); ++s){
		if (mapfreq.find(paraulesbuscar[s]) != mapfreq.end() or  paraules.find(paraulesbuscar[s]) != paraules.end() ){
			conter += 1;
		}
	}
	if(conter == int(paraulesbuscar.size())) return true;
	else return false;
} 
void Text::afegircitaref(string ref){
	citesassoci.insert(ref);
}

void Text::conscitesasso(set<string>& citesu){
	citesu = citesassoci;
}

string Text::consulta_inicials()const{
		return inicials_priv;
	}

string Text::consulta_auto()const{
	    return autor;
	}

string Text::consulta_titol() const{
	  return titol;
	}

vector<vector<string> > Text::consulta_contingut()const{
    return contingut;
}

int Text::num_par(){
	return num_paraules;
}

int Text::numero_frases(){
	return num_frases;
}

vector <pair<string,int> > Text::taulafreqs(){
	return taulafreq;		
}
void normalitzar(string &base){
	size_t found = base.find("{");
	while (found != string::npos){
		base.replace(found, 1, " ");
		found = base.find("{", found+3);
	}
	found = base.find("}");
	while (found != string::npos){
		base.replace(found, 1, " ");
		found =base.find("}", found+3);
	}
}

char operacio (string expre, int &i){
	while (expre[i] != '|' and expre[i] != '&')++i;
	if (expre[i] == '|') return '|';
	else if (expre[i] == '&') return '&';
	else return 0;
}

string extra_expre (string expre, int &i){

	int parent = 0;
	int claudator = 0;
	while(expre[i] != '(' and expre[i] != '{')++i;
	if (i!=0)expre.erase(0,i);
	i=0;
	if (expre[i] == '('){
		++parent;
		++i;
		while(parent != 0){
			if (expre[i]=='(')++parent;
			else if (expre[i]==')')--parent;
			++i;
		}
		string retornar = expre.substr(0,i);
		return retornar;
	}
	else if (expre[i]=='{'){
		++claudator;
		++i;
		while(claudator != 0){
			if (expre[i]=='{')++claudator;
			else if (expre[i]=='}')--claudator;
			++i;
		}
		string retornar = expre.substr(0,i);
		return retornar;
	}
	else return 0;
	
}

set<int> Text::recursiva (string  frase){
	int i = 0;
	while (frase[i]==' ')++i;
	frase.erase(0, i);
	i = 0;
	if (frase[i]=='{'){
		normalitzar (frase);
		bool primer = true;
		set<int> vect1;
		expremin(frase, vect1, primer);
		return vect1;
	}
	else {
		frase.erase(0,1);//eliminar el (
		string fraseizq = extra_expre(frase, i);
		frase.erase(0,i);
		i = 0;
		char op = operacio(frase, i); //guardem l'operació
		frase.erase(0,i);
		i = 0;
		string frasedere = extra_expre(frase, i);
		set<int> izquierda = recursiva(fraseizq);
		set <int> derecha = recursiva(frasedere);
		if (op=='|') unio(izquierda, derecha);
		else if (op=='&') interseccio(izquierda,derecha);
		return izquierda;

	}
		
}

void Text::expremin(string expres, set<int> &vect1, bool &primer){
	string word;
	istringstream anali (expres);
	bool falta = false;

	while (anali >> word and not falta){
		set <int> vect2;
		map<string, aparicions>::iterator tosearch = mapfreq.find(word);
		if (tosearch == mapfreq.end()){
			if (word == "&"){}
			else {
				falta = true;
				vect1.clear(); //en el caso que la palabra no este, borramos el vector a devolver
			}
		}
		else {
			vect2 = tosearch->second.files;
			if (primer){
				unio(vect1, vect2);
				primer = false;
			}
			else interseccio(vect1, vect2);
		}
	}
}
void Text::frasesparaules(vector<string> paraulests, set<int> &vect1){
	bool falta = false;
	bool primer = true;
	int d = 0;
	while (d < int(paraulests.size()) and not falta){
		map <string, aparicions >::iterator freqit = mapfreq.find(paraulests[d]);
		if (freqit == mapfreq.end())falta = true;
		
		else{
			set<int> vect2 = freqit->second.files;
			if (primer) {
				unio(vect1, vect2);
				primer = false;
			}
			else interseccio(vect1, vect2);
		}
		++d;
	}
	if (falta) vect1.clear();
	else {
		set<int>::iterator t;
		for (t = vect1.begin(); t != vect1.end(); ++t){//lectura del vetor que indica las frases a buscar
			int l = 0; //lincado con paraulests -> todas las palabras a buscar
			int m = 0; //lincado con contingut
			bool erroni = false;
			bool primerapara = false;
			while (l < int(paraulests.size()) and m < int(contingut[*(t)-1].size()) and not erroni){
				char caux = contingut[*(t)-1][m][0];
				if (caux == '.' or caux == ',' or caux == ';' or caux == '?' or caux == '!') {
					++m;
				}
				else if (contingut[*(t)-1][m] != paraulests[l] and not primerapara) ++m;
				else if (contingut[*(t)-1][m] != paraulests[l] and primerapara) {
					l=0;
					primerapara=false;
				}
				else if (contingut[*(t)-1][m] == paraulests[l]){
					primerapara = true;
					++l;
					++m;
				}
			}
			//imprimim
			if (l < int(paraulests.size())) erroni = true;
			if (not erroni) {
				bool primertp = true;
			    bool ultimtp = false;
			    cout << *(t) << " ";
			    for (int p = 0; p < int(contingut[*(t)-1].size()); ++p){
			      bool puntuacio =false;
			      if (p == int(contingut[*(t)-1].size()-1)) {ultimtp = true;}
			      if (contingut[*(t)-1][p] == "," or contingut[*(t)-1][p] == ";" or contingut[*(t)-1][p] == ":") puntuacio = true;
			      if (primertp){
			        primertp = false;
			        cout << contingut[*(t)-1][p];
			      }
			      else if (ultimtp) cout << contingut[*(t)-1][p];
			      else if (puntuacio) cout << contingut[*(t)-1][p];
			      else cout<<" "<<contingut[*(t)-1][p];
			    }
			    cout <<endl;
			}
		}
	}
}

void Text::interseccio (set<int> &vec1, set<int> &vec2){
  set<int> v3;
  set<int>::iterator i = vec1.begin();
  set<int>::iterator j = vec2.begin();
  while (i != vec1.end() and j != vec2.end()){
    if (*(i) < *(j)) ++i;
    else if (*(i) > *(j)) ++j;
    else if (*(i) == *(j)){
      v3.insert(*(i));
      ++i;
      ++j;
    }
  }
  vec1 = v3;
}

void Text::unio (set<int> &vec1, set<int> &vec2){
  set<int> v3;
  set<int>::iterator i = vec1.begin();
  set<int>::iterator j = vec2.begin();
  while (i != vec1.end() and j != vec2.end()){
    if (*(i) < *(j)) {
      v3.insert(*(i));
      ++i;
    }
    else if (*(i) > *(j)){
      v3.insert(*(j));
      ++j;
    }
    else if (*(i) == *(j)){
      v3.insert(*(i));
      ++i;
      ++j;
    }
  }
  if (i == vec1.end() and j != vec2.end()){
    while (j != vec2.end()){
    	v3.insert(*(j));
    	++j;
    }  
  }
  else if (i != vec1.end() and j == vec2.end()){
    while (i != vec1.end()){
    	v3.insert(*(i));
    	++i;
    } 
  }
  vec1 = v3; 
}

void Text::elim_cit_set(const string &referencia){
	citesassoci.erase(referencia);
}
