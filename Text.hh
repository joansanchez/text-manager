/** @file Text.hh
    @brief Especificació de la classe Text 
*/
#ifndef TEXT_HH
#define TEXT_HH

#ifndef NO_DIAGRAM
#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <algorithm>
#include <sstream>
#endif
using namespace std;
/** @class Text
    @brief Representa un text i les seves propietats. 
    
    Permet operar amb un text i retornar valors de consulta fàcilment.
*/
class Text{
	private:
	struct aparicions{
        int vegades;
        set<int> files;
    };
    string titol; //títol del text
    string autor; //autor del text
    vector< vector<string> > contingut; //contingut del text ja dividit
    int num_frases;
    int num_paraules;
    set <string> citesassoci; //estructura per guardar les cites associades d'un text
    map <string, aparicions > mapfreq; //estructura que guarda totes les paraules del contingut del text amb el nombre d'aparicions i les línies on apareixen.
    vector <pair<string,int> > taulafreq; //taula de freqüències en forma de vector per facilitar la lectura d'aquesta.
    set <string> paraules; //estructura per guardar les paraules del títol i l'autor
    string inicials_priv; //guardar inicials
	
	public:
  
	//Constructores 
	  
 /** @brief Creadora per defect. 

      
      \pre <em>cert</em>
      \post el resultat és un text buit
  */ 	  
	  Text();
	  
  /** @brief Creadora de textos. 

      \pre <em>cert</em>
      \post el resultat és un text amb titol = titoltxt, autor = autortxt i contingut = vector <string> continguttxt, on a cada posició del vector hi haurà una frase del text.
        TaulaFreq s'inicialitza i s'omple ara per a fer més ràpid "void taulafreq();"
  */ 
	Text(string titoltxt,string autortxt,vector<vector<string> > contingutaux); 

	
        
	//Destructores
  /** @brief Destructora de textos. 

      esborra automàticament els objectes locals en sortir d'un àmbit de visibilitat
  */ 	
	~Text();
	
        
        //Modificadores
  /** @brief Substitueix paraules. 
      
      \pre <em>cert.</em>
      \post  canvia totes les aparicions de <paraula1> per <paraula2> en el contingut del paràmetre implicit.
  */         
  void substitueix(string paraula1, string paraula2);
  
  /** @brief Afegir referència de la cita
      
      \pre <em>cert</em>
      \post Afegeix la referencia d'una nova Cita associada al set cites associades a un text.
  */
  
  void afegircitaref(string ref);
  
  /** @brief Copiador de cites associades
      \pre <em>cert</em>
      \post retorna una copia del set citesassoci per poder treballar més facilment des de fora la classe.
  */

  void conscitesasso(set<string>& citesu);
  
  /** @brief Calcula la taula de freqüències
      \pre <em>cert</em>
      \post Taula de freqüències queda guardada en un vector per la seva fàcil lectura, i en un map per a les funcions de cerca .
  */

  void taulafrequs (vector<vector<string> > continguttxt);
            
        //Consultores
  /** @brief Comprovador de presència. 

      Mira si al text es troben les paraules desitjades
      \pre <em>cert</em>
      \post  retorna cert si es troba en el paràmetre implícit totes les paraules contingudes al vector, altrament, retorna fals.
  */         
	bool conteParaules(vector <string>paraulesbuscar);

  /** @brief Consulta autor. 

      \pre <em>cert.</em>
      \post  retorna l'autor del paràmetre implícit.
  */         
	string consulta_auto()const;
	
	/** @brief Consulta inicials.
      \pre <em>cert.</em>
      \post retorna les inicials del autor del paràmetre implícit.
  */
	
  string consulta_inicials()const;
  
  /** @brief Consulta títol.
      \pre <em>cert.</em>
      \post retorna el titol del paràmetre implícit.
  */

	string consulta_titol() const;

  /** @brief Contingut. 

      \pre <em>cert.</em>
      \post mostra el contingut del paràmetre implicit amb les seves frases numerades a partir de l'1.
  */            
	vector<vector<string> > consulta_contingut() const;

  /** @brief Frases. 

      \pre <em>cert.</em>
      \post mostra les frases entre la x-èssima i la y-èssima del contingut del paràmetre implícit.
  */ 
	void frases(int x,int y);

  /** @brief Número de frases. 

      \pre <em>cert.</em>
      \post mostra el nombre de frases del contingut del paràmetre implícit.
  */ 
	int numero_frases();

  /** @brief Número de paraules. 

      \pre <em>cert.</em>
      \post mostra el nombre de paraules del contingut del paràmetre implícit.
  */         
	int num_par();

  /** @brief Taula de freqüències. 

      \pre <em>cert</em>
      \post  Trenca el contingut paraula per paraula i conta les aparicions de cada una d'elles en el transcurs del text.
  */           
	vector <pair<string,int> > taulafreqs();

  /** @brief Funció recursiva per frases amb expressió. 

      \pre <em>cert.</em>
      \post  mostra les frases del contingut del paràmetre implícit que compleixen l'expressió boleana determinada pel "símbol".
  */        
	set<int> recursiva(string expre);
	
	/** @brief Expressión minima. 

      \pre <em>cert</em>
      \post  Funció empleada per tractar els casos base de la funció recursiva.
  */
	
	void expremin(string expres, set<int> &vect1, bool &primer);
	

  /** @brief Frases seqüència de paraules. 

      \pre <em>cert</em>
      \post  mostra les frases on hi apareix, consecutivament, obviant els signes de puntuació, la seqüència de paraules <em>paraula1</em>, <em>paraula2</em>...<em>paraulaN</em> en el contingut del paràmetre implícit

  */          
	void frasesparaules(vector<string> paraulests, set<int> &vect1);
	
	/** @brief Intersecio. 

      \pre <em>cert</em>
      \post  Fució que busca els elements comuns dels dos sets d'apuntadors de frases.

  */
	
	void interseccio (set<int> &vec1, set<int> &vec2);
	
	/** @brief Unió. 

      \pre <em>cert</em>
      \post  Funció que unifica el contingut dels dos sets d'auntadors a frases.

  */
	
	void unio (set<int> &vec1, set<int> &vec2);
	
	/** @brief Elimina Cita Set. 

      \pre <em>cert</em>
      \post  Elimina la referencia de la Cita que te com ha referencia el parametre imclicit del set citesassoci.

  */
	
	void elim_cit_set(const string &referencia);
};
#endif
