#include "Biblio.hh"

Biblio::Biblio() {
  ulttext = false;
}

Biblio::~Biblio() {}

void Biblio::AfegirText(string titol){
	string autorbib;//llegim l'autor                  
  getline(cin, autorbib);
  string auxiaut;
  istringstream check1(autorbib);
  check1 >> auxiaut;
  if (auxiaut=="autor"){
  int p = autorbib.find_first_of('"');         
  autorbib.erase(0,p+1);
  int q = autorbib.find_last_of('"');
  autorbib.erase(q,autorbib.size()-1);

	vector< vector<string> > contingutbib; //llegim el contingut del text
  bool saltlin = true;            // indica si haurem d'insertar una nova linia
  string linia;
  getline(cin, linia);
  while (linia != "****") {         // llegim linies fins trobar els 4 asteriscs
    normalitzar (linia);
    istringstream issLinia(linia);
    string paraula;
    while (issLinia >> paraula) {   // anem paraula per paraula
      bool lastword = (paraula=="." || paraula=="?" || paraula=="!");
      // si cal afegir vector per desar les paraulas d'una linia nova
      if (saltlin) contingutbib.push_back(vector<string>());
      // desar paraula
      contingutbib[contingutbib.size()-1].push_back(paraula);
      // si la paraula acaba la linia, a la propera volta ficarem un vector nou a contingut
      saltlin = lastword;
    }
    getline(cin, linia);
  }
  Text a(titol, autorbib, contingutbib); //Creem el text
  map<string,map<string, Text> >::iterator checker = BiblioAutor.find(autorbib); //Comprovem que no es troba a la biblioteca un text amb el mateix títol i autor
  if (checker != BiblioAutor.end()){
    map<string, Text> titolsaux = checker->second;
    map<string, Text>::iterator checker2 = titolsaux.find(titol);
    if (checker2 != titolsaux.end()){
      cout << "error" <<endl; 
    }
    else BiblioAutor[autorbib][titol] = a;
  }
  else BiblioAutor[autorbib][titol] = a;
}
else {}
}


void Biblio::normalitzar (string& linia){
	size_t found = linia.find(".");
	while (found != string::npos){
		linia.replace(found, 1, " .");
		found =linia.find(".", found+2);
	}
	found = linia.find(",");
	while (found != string::npos){
		linia.replace(found, 1, " ,");
		found =linia.find(",", found+2);
	}
	found = linia.find(";");
	while (found != string::npos){
		linia.replace(found, 1, " ;");
		found =linia.find(";", found+2);
	}
	found = linia.find(":");
	while (found != string::npos){
		linia.replace(found, 1, " :");
		found =linia.find(":", found+2);
	}
	found = linia.find("?");
	while (found != string::npos){
		linia.replace(found, 1, " ?");
		found =linia.find("?", found+2);
	}
	found = linia.find("!");
	while (found != string::npos){
		linia.replace(found, 1, " !");
		found =linia.find("!", found+2);
	}
}

void Biblio::EliminarText(){
  string autortodl = ultxt.consulta_auto();
  string tltdel = ultxt.consulta_titol();
  map<string,map<string, Text> >::iterator todelate = BiblioAutor.find(autortodl);
  map<string,Text>::iterator it_aux = (todelate->second).find(tltdel);
  (todelate->second).erase(tltdel);
  if ((todelate->second).empty()){
    BiblioAutor.erase(autortodl);
  }
  ulttext = false; //el sistema deixa de tenir un text triat
  Text R;
  ultxt=R;
}

void Biblio::SubText(string paraula1, string paraula2){
	ultxt.substitueix(paraula1, paraula2);
}


void Biblio::TotsTextos(){
  map<string,map<string,Text> >::iterator it1;
  for (it1=BiblioAutor.begin();it1!=BiblioAutor.end();++it1){
    map<string,Text> aux=it1->second;
    map<string,Text>::iterator it2;
    string aut=it1->first;
    for (it2=aux.begin();it2!=aux.end();++it2){
      cout<<aut<<" "<<'"'<<it2->first<<'"'<<endl;
    }
  }
}
void Biblio::TriarText(string paraules){
  Text aux;
  bool trobat = false;
  bool error = false;
  if (paraules.length()==0){ //mirem si la string que ens passen a buscar les paraules és buida
    cout << "error" <<endl; 
    ulttext = false;
    Text l;
    ultxt=l;
  }
  else{
  istringstream issavect(paraules);
  vector <string> palabrasbuscar;
  while (issavect >> paraules) {
    palabrasbuscar.push_back(paraules);
  }
  map<string,map<string,Text> >::iterator it1;
  for (it1=BiblioAutor.begin();it1!=BiblioAutor.end();++it1){
    map<string, Text> textos = it1->second;
    map<string, Text>::iterator it2;
    it2 = textos.begin();
    while(not error and it2 != textos.end()){
      Text b = it2->second;
      bool auxiliar = b.conteParaules(palabrasbuscar);
      if (auxiliar and not trobat){
        trobat = true;
        aux = b;
      }
      else if (auxiliar and trobat) error = true;
      ++it2;
    }
  }
  if (error or not trobat) {
  	cout << "error" <<endl; 
  	ulttext = false;
    Text l;
    ultxt=l;
  }
  else{
    ulttext = true;
    ultxt = aux;
  }
}
}
bool Biblio::hihatexttriat(){
  return ulttext;
}
void Biblio::autor(){
  cout<<ultxt.consulta_auto()<<endl;
}

void Biblio::TotsAutors(){
  map<string,map<string,Text> >::iterator aux1;
  for (aux1=BiblioAutor.begin();aux1!=BiblioAutor.end();++aux1){
    cout<<aux1->first<<" "<<(aux1->second).size()<<" ";
    map<string,Text>::iterator aux2;
    int num_par_fi = 0;
    int num_fra_fi = 0;
    for (aux2=aux1->second.begin();aux2!=aux1->second.end();++aux2){
      num_par_fi+=aux2->second.num_par();
      num_fra_fi+=aux2->second.numero_frases();
    }
    cout<<num_fra_fi<<" "<<num_par_fi<<endl;	
  }
}

void Biblio::info(){
  cout<<ultxt.consulta_auto()<<" "<<'"'<<ultxt.consulta_titol()<<'"'<<" "<<ultxt.numero_frases()<<" "<<ultxt.num_par()<<endl;
  cout<<"Cites Associades:"<<endl;
  map<string,map<string,Text> >::iterator aux=BiblioAutor.find(ultxt.consulta_auto());
  map<string,Text>::iterator aux2=aux->second.find(ultxt.consulta_titol());
  set<string> citesu;
  aux2->second.conscitesasso(citesu);
  set<string>::iterator aux3;
  for (aux3=citesu.begin();aux3!=citesu.end();++aux3){
    map<string,Cita>::iterator aux4=mapcites.find(*aux3);
    cout<<(*aux3)<<endl;
    aux4->second.imp_contingut();
  }
}
void Biblio::contingut(){
  vector<vector<string> > auxcont=ultxt.consulta_contingut(); 
  for (int i=0;i<int(auxcont.size());++i){ //mecanisme per realitzar correctament l'impressió del contingut respectant l'estructura matricial que utilitzem per guardar el text
    bool primer = true;
    bool ultim = false;
    cout << i+1 << " ";
    for (int j=0;j<int(auxcont[i].size());++j){
      bool puntuacio =false;
      if (j == int(auxcont[i].size()-1)) {ultim = true;}
      if (auxcont[i][j] == "," or auxcont[i][j] == ";" or auxcont[i][j] == ":") puntuacio = true;
      if (primer){
        primer = false;
        cout << auxcont[i][j];
      }
      else if (ultim) cout << auxcont[i][j];
      else if (puntuacio) cout << auxcont[i][j];
      else cout<<" "<<auxcont[i][j];
    }
    cout <<endl;
  }
}

void Biblio::frases(int x,int y){
    vector<vector<string> > auxcont=ultxt.consulta_contingut();
    if (x>0 and y>0 and x<=y and x<=ultxt.numero_frases() and y<=ultxt.numero_frases()){
      for (int i = x-1; i < y; ++i){
      bool primer = true;
      bool ultim = false;
      cout << i+1 << " ";
      for (int j=0;j<int(auxcont[i].size());++j){
        bool puntuacio =false;
        if (j == int(auxcont[i].size()-1)) {ultim = true;}
        if (auxcont[i][j] == "," or auxcont[i][j] == ";" or auxcont[i][j] == ":") puntuacio = true;
        if (primer){
          primer = false;
          cout << auxcont[i][j];
        }
        else if (ultim) cout << auxcont[i][j];
        else if (puntuacio) cout << auxcont[i][j];
        else cout<<" "<<auxcont[i][j];
      }
      cout <<endl;
    }
    }
    else cout << "error" <<endl;

}
void Biblio::nombrefrases(){
  cout<<ultxt.numero_frases()<<endl;
}

void Biblio::nombreparaules(){
  cout<<ultxt.num_par()<<endl;
}

void Biblio::tauladefrecuencies(){
  vector <pair<string,int> > auxiliar = ultxt.taulafreqs();
  for (int z = 0; z < int(auxiliar.size()); ++z){
    cout << auxiliar[z].first << " " << auxiliar[z].second << endl;
  }
}

void Biblio::frasesexpresio(string expresio){
  set <int> vect1 = ultxt.recursiva (expresio);
  vector<vector<string> > auxcont=ultxt.consulta_contingut();
  set<int>::iterator t;
  for (t = vect1.begin(); t != vect1.end(); ++t){//impressió de les frases
    bool primer = true;
    bool ultim = false;
    cout << *(t) << " ";
    for (int j=0;j<int(auxcont[*(t)-1].size());++j){
      bool puntuacio =false;
      if (j == int(auxcont[*(t)-1].size()-1)) {ultim = true;}
      if (auxcont[*(t)-1][j] == "," or auxcont[*(t)-1][j] == ";" or auxcont[*(t)-1][j] == ":") puntuacio = true;
      if (primer){
        primer = false;
        cout << auxcont[*(t)-1][j];
      }
      else if (ultim) cout << auxcont[*(t)-1][j];
      else if (puntuacio) cout << auxcont[*(t)-1][j];
      else cout<<" "<<auxcont[*(t)-1][j];
    }
    cout <<endl;
  } 
}



void Biblio::frasesparaules(vector<string> paraules){
  set<int> v1;
  ultxt.frasesparaules(paraules, v1);
}



void Biblio::TextosAutor(string autorta){
  map <string, map<string, Text> >::iterator autores = BiblioAutor.find(autorta);
  if (autores != BiblioAutor.end()){
    map<string,Text> comodin = autores->second;
    for (map<string, Text>::iterator it3 = comodin.begin(); it3 != comodin.end(); ++it3){
      cout <<'"'<< it3->first<<'"' << endl;
    }
  }
}


void Biblio::afegircita(int x, int y){ 
  if (x>0 and y>0 and x<=ultxt.numero_frases() and y<=ultxt.numero_frases() and x<=y){
   	set<string> citesaux;
   	map<string,map<string, Text> >::iterator mapextern = BiblioAutor.find(ultxt.consulta_auto());
   	map <string, Text>::iterator mapintern = mapextern->second.find(ultxt.consulta_titol());
   	(mapintern->second).conscitesasso(citesaux);
   	set<string>::iterator verific = citesaux.begin();
   	bool trobat = false;
    while (not trobat and verific != citesaux.end()){
    	map<string,Cita>::iterator check = mapcites.find(*verific);
    	if (check != mapcites.end() and check->second.valor_x() == x and check->second.valor_y() == y) trobat=true;
    	++verific;
    }
    if(trobat == false){
    string inis = ultxt.consulta_inicials();
    int idnumeric = contador[inis];
    ++idnumeric;
    contador[inis] +=1;
    Cita auxcita (inis, ultxt, x, y);
    ostringstream reff;
    reff << idnumeric;
    inis += reff.str();
    mapcites[inis] = auxcita;
    map<string,map<string, Text> >::iterator mapextern1 = BiblioAutor.find(ultxt.consulta_auto());
    map <string, Text>::iterator mapintern1 = mapextern1->second.find(ultxt.consulta_titol());
    (mapintern1->second).afegircitaref(inis);

    map<string,set<string> >::iterator citautaux = citesassoaut.find(ultxt.consulta_auto());
    if (citautaux!= citesassoaut.end()){
    	citautaux->second.insert(inis);
    }
    else{
    	set <string> setaux;
    	setaux.insert(inis);
    	citesassoaut[ultxt.consulta_auto()]=setaux;
    }

	}
	else cout << "error" <<endl;
  } else cout << "error" <<endl;
}

void Biblio::eliminarcita(const string &referencia){
  map<string,Cita>::iterator aux=mapcites.find(referencia);
  if (aux!=mapcites.end()){
    map<string,set<string> >::iterator aux2=citesassoaut.find(aux->second.aut_procedent());
    if (aux2!=citesassoaut.end()){
      aux2->second.erase(referencia);
    }
    map<string,map<string,Text> >::iterator aux3=BiblioAutor.find(aux->second.aut_procedent());
    if (aux3!=BiblioAutor.end()){
      map<string,Text>::iterator aux4=aux3->second.find(aux->second.tit_proc());
      if (aux4!=aux3->second.end()){
        aux4->second.elim_cit_set(referencia);
      }
    }
    mapcites.erase(referencia);
  }
  else cout<<"error"<<endl;
}

void Biblio::infocita(string referencia){
  map<string,Cita>::iterator indice=mapcites.find(referencia);
  if (indice!=mapcites.end()){
    cout<<(indice->second).aut_procedent()<<" "<<'"'<<(indice->second).tit_proc()<<'"'<<endl;
    cout<<(indice->second).valor_x()<<"-"<<(indice->second).valor_y()<<endl;
    indice->second.imp_contingut();
  }
  else cout<< "error" <<endl;
}

void Biblio::totescites(){
  map<string,Cita>::iterator indice;
  if (mapcites.empty()){}
  else{
  for (indice=mapcites.begin();indice!=mapcites.end();++indice){
    if (indice != mapcites.end())cout<<(indice->first)<<endl;
    (indice->second).imp_contingut();
    cout<<(indice->second).aut_procedent()<<" "<<'"'<<(indice->second).tit_proc()<<'"'<<endl;
  }
  }
}

void Biblio::cites(){
  map<string,map<string,Text> >::iterator aux=BiblioAutor.find(ultxt.consulta_auto());
  map<string,Text>::iterator aux2=aux->second.find(ultxt.consulta_titol());
  set<string> citesu;
  aux2->second.conscitesasso(citesu);
  set<string>::iterator aux3;
  for (aux3=citesu.begin();aux3!=citesu.end();++aux3){
    map<string,Cita>::iterator aux4=mapcites.find(*aux3);
    cout<<(*aux3)<<endl;
    aux4->second.imp_contingut();
    cout<<ultxt.consulta_auto()<<" "<<'"'<<ultxt.consulta_titol()<<'"'<<endl;
  }
}	

void Biblio::citesAutor(string autor_cita){
  map<string,set<string> >::iterator citesautor=citesassoaut.find(autor_cita);
  if (citesautor!=citesassoaut.end()){
    set<string>::iterator iteaux;
    for (iteaux=citesautor->second.begin(); iteaux!=citesautor->second.end();++iteaux){
      map<string,Cita>::iterator aux2=mapcites.find(*iteaux);
      cout<<(*iteaux)<<endl;
      (aux2->second).imp_contingut();
      cout<<'"'<<aux2->second.tit_proc()<<'"'<<endl;
    }
  }
}

