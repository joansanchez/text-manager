#include "Biblio.hh"
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
using namespace std;


void normalitzaciottlaut(string &expre){
  size_t found = expre.find('"');
  while (found != string::npos){
    expre.replace(found, 1, " ");
    found = expre.find('"', found+2);
  }
  while (found != string::npos){
    expre.replace(found, 1, " . ");
    found =expre.find(".", found+3);
  }
  found = expre.find("?");
  while (found != string::npos){
    expre.replace(found, 1, " ? ");
    found =expre.find("?", found+3);
  }
  found = expre.find("!");
  while (found != string::npos){
    expre.replace(found, 1, " ! ");
    found = expre.find("!", found+3);
  }
  found = expre.find("}");
  while (found != string::npos){
    expre.replace(found, 1, " ");
    found = expre.find("}", found+3);
  }
}

int main() {
  Biblio gestor;
  string comanda, op, m;
  getline(cin, comanda);
    while (comanda!="sortir"){
      cout << comanda << endl;
	    istringstream iss(comanda);
	    iss >> op;
      if (op == "afegir") {
        iss >> op;
        if (op == "text") {
         int p = comanda.find_first_of('"');         
         comanda.erase(0,p+1);
         int q = comanda.find_last_of('"');
         comanda.erase(q,comanda.size()-1);

         gestor.AfegirText(comanda);
          }
         
        else if (op == "cita") {
          string x1,y1;
          int x, y;
          comanda.erase(0,11);
          istringstream com(comanda);
          bool erroni = false;
          com >> x1 ;
          int ite = 0;
          if (x1.empty())erroni = true;
          while (ite<x1.size() and not erroni){
            if (x1[ite]<'0' or x1[ite]>'9') erroni = true;
            ++ite;
          }
          ite = 0;
          com >> y1;
            if (y1.empty()) erroni = true;
            while (ite<y1.size() and not erroni){ 
              if (y1[ite]<'0' or y1[ite]>'9') erroni = true;
              ++ite;
            }
          if (not erroni){
            x = stoi(x1);
            y = stoi (y1);
            if (gestor.hihatexttriat()){
              gestor.afegircita(x,y);
            }
            else cout << "error" << endl; 
            
          }
          else cout << "error" <<endl; 
        }
      }
      else if (op == "triar"){
        iss>>op;
		    if (op == "text"){
          int ini = comanda.find_first_of('{');
          int fin = comanda.find_last_of('}');
          string comanda2 = comanda.substr(ini+1,fin-1);
          normalitzaciottlaut(comanda2);
          if (comanda2.empty())cout<<"error"<<endl;
          else gestor.TriarText(comanda2);
		    }
      }
      else if (op == "eliminar"){
        iss >> op;
        if (op == "text") {
          if (gestor.hihatexttriat()){
            gestor.EliminarText();
          }
          else cout << "error" << endl;
          
        }
        else if (op == "cita") {
          comanda.erase(0,13);
          normalitzaciottlaut(comanda);
          string referencia;
          istringstream issref(comanda);
          issref >> referencia;
          issref >> op;
          gestor.eliminarcita(referencia);
        }
      }
      else if (op == "substitueix"){
        iss >> op;
        op.erase(0,1);
        op.erase(op.length()-1);
        string paraula1 = op;
        iss >> op;
        iss >> op;
        op.erase(0,1);
        op.erase(op.length()-1);
        string paraula2 = op;
        if (gestor.hihatexttriat()){
          gestor.SubText(paraula1, paraula2);
        }
        else cout << "error" << endl;
      }
      else if (op == "textos"){
		    iss>>op;
		    if (op =="autor"){
		      string autor;   
          int i = comanda.find_first_of('"');
          comanda.erase(0,i);
          int y = comanda.find_last_of('"');
          autor = comanda.substr(1,y-1);
          comanda.erase(0,y+1);
          istringstream issAutor(autor);
          vector <string> autvectr;
          string autaux;
           while (issAutor >> autaux){
            autvectr.push_back(autaux);
           }
           bool primer = true;
           for (int j=0;j<int(autvectr.size());++j){
              bool puntuacio =false;
              if (autvectr[j] == "." or autvectr[j] == "?" or autvectr[j] == "!") puntuacio = true;
              if (primer){
                primer = false;
                autor = autvectr [j];
              }
              else if (puntuacio) autor += autvectr[j];
              else {
                autor +=" ";
                autor += autvectr[j];
              }
            }
          istringstream tocheck (comanda);
          tocheck >> op;
          if (op == "?"){
            gestor.TextosAutor(autor);
          }
		    } 
      }
      else if (op == "tots"){
        iss >> op;
        if (op == "textos") {
		      iss >> op;
          if (op == "?"){
            gestor.TotsTextos();
          }
        }
        else if (op == "autors") {
		      iss >> op;
          if (op == "?"){
            gestor.TotsAutors();
          }
        }
      }
      else if (op == "info"){
        iss >> op;
        if (op == "?") {
          if (gestor.hihatexttriat()){
            gestor.info();
          }
          else cout << "error" << endl;
        }
        else if (op == "cita") {
          comanda.erase(0,10);
          normalitzaciottlaut(comanda);
          string referencia;
          istringstream issref(comanda);
          issref >> referencia;
          issref >> op;
          if (op == "?"){
            gestor.infocita(referencia);
          }

        }
      }
      else if (op == "autor"){
		    iss >> op;
		    if (op == "?"){
          if (gestor.hihatexttriat()){
            gestor.autor();
          }
          else cout << "error" << endl;
		    }
      }
      else if (op == "contingut"){
		    iss>>op;
		    if (op == "?"){
          if (gestor.hihatexttriat()){
            gestor.contingut();
          }
          else cout << "error" << endl;
		    }
      }
      else if (op == "frases"){
        iss >> op;
        if (op[0] == '(' or op[0] =='{'){
          comanda.erase(0,7);
          int aux = comanda.size()-1;
          char aux2 = comanda[aux];
          if (aux2 == '?'){
            comanda.erase(comanda.length()-2, comanda.length()-1);
          if (gestor.hihatexttriat()){
              gestor.frasesexpresio(comanda);
            }
            else cout << "error" << endl;
          }
        }
        else if (op[0] == '"'){
          comanda.erase(0,7);
          int aux = comanda.size()-1;
          char aux2 = comanda[aux];
          if (aux2 == '?'){
            normalitzaciottlaut(comanda);
            comanda.erase(comanda.length()-2, comanda.length()-1);
            istringstream com(comanda);
            vector<string> paraules;
            while (com >> comanda){
              paraules.push_back(comanda);
            }
            if (gestor.hihatexttriat()){
              gestor.frasesparaules(paraules);
            }
            else cout << "error" << endl;  
          }
        }
        else {
		    string x1,y1;
		    int x, y;
        comanda.erase(0,7);
        istringstream com(comanda);
		    bool erroni = false;
		    com >> x1 ;
		    int ite = 0;
        if (x1.empty())erroni = true;
		    while (ite<x1.size() and not erroni){
          if (x1[ite]<'0' or x1[ite]>'9') erroni = true;
		      ++ite;
		    }
		    ite = 0;
        com >> y1;
          if (y1.empty()) erroni = true;
          while (ite<y1.size() and not erroni){ 
            if (y1[ite]<'0' or y1[ite]>'9') erroni = true;
            ++ite;
          }
		    if (not erroni){
		      com >> op;
		      x = stoi(x1);
		      y = stoi (y1);
		      if (op == "?"){
          if (gestor.hihatexttriat()){
            gestor.frases(x, y);
          }
          else cout << "error" << endl; 
		      }
		    }
		    else cout << "error" <<endl; 
      }
      }
      else if (op == "nombre"){
		    iss >> op;
		    if (op == "de"){
			   iss >> op;
			   if (op == "frases"){
				  iss >> op;
          if (op == "?"){
            if (gestor.hihatexttriat()){
              gestor.nombrefrases();
            }
            else cout << "error" << endl;
          }
			   }
			   else if (op == "paraules"){
				  iss >> op;
          if (op == "?"){
            if (gestor.hihatexttriat()){
              gestor.nombreparaules();
            }
            else cout << "error" << endl;
          }
			   }
		    }
      }

      else if (op == "taula"){
        iss >> op;
        if (op == "de"){
          iss >> op;
          if (op == "frequencies"){
            iss >> op;
            if (op == "?"){
              if (gestor.hihatexttriat()){
                gestor.tauladefrecuencies();
              }
              else cout << "error" << endl;

            }
          }
        }
      }

      else if (op == "cites") {
		    iss >> op;
		    if (op == "autor"){
          string autor;    
          int i = comanda.find_first_of('"');
          comanda.erase(0,i);
          int y = comanda.find_last_of('"');
          autor = comanda.substr(1,y-1);
          comanda.erase(0,y+1);
          istringstream issAutor(autor);
          vector <string> autvectr;
          string autaux;
           while (issAutor >> autaux){
            autvectr.push_back(autaux);
           }
           bool primer = true;
           for (int j=0;j<int(autvectr.size());++j){
              bool puntuacio =false;
              if (autvectr[j] == "." or autvectr[j] == "?" or autvectr[j] == "!") puntuacio = true;
              if (primer){
                primer = false;
                autor = autvectr [j];
              }
              else if (puntuacio) autor += autvectr[j];
              else {
                autor +=" ";
                autor += autvectr[j];
              }
            }
          istringstream tocheck (comanda);
          tocheck >> op;
          if (op == "?"){
            gestor.citesAutor(autor);
          }
		    }
		    else if (op == "?"){
          if (gestor.hihatexttriat()){
            gestor.cites();
          }
          else cout<<"error"<<endl;
		    }
	     }
       else if (op == "totes"){
        iss >> op;
        if (op == "cites"){
          iss >> op;
          if (op == "?"){
            gestor.totescites();
          }
        }

       }
       
    getline(cin, comanda);
    while (comanda.empty()){
      getline(cin, comanda);
    }
    cout<<endl;
  }
}

