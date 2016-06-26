/** @file Biblio.hh
    @brief Especificació de la classe Biblioteca
*/
#ifndef BIBLIO_HH
#define BIBLIO_HH

#include "Text.hh"
#include "Cita.hh"

#ifndef NO_DIAGRAM
#include <set>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <list>
#endif
using namespace std;

/** @class Biblioteca
    @brief Representa una biblioteca de textos i cites. 
    
    Pot contenir textos i cites relatives a aquests, o a d'altres que han passat per la biblioteca. Els textos es poden afegir, eliminar, consultar i modificar. Passa gairebé igual amb les cites, però aquestes no es poden modificar.
*/

class Biblio{
  //Creem una estructura on guardarem tant els textos com les cites, en dues estructures de dades diferenciades.
  
	private:
	  
	  //Estructures dels textos
        
	    map<string,map<string, Text> > BiblioAutor; //Llibreria de textos. Es tracta d'un map<autor,map<títol, Text>>
        Text ultxt; //Guarda l'últim text per facilitar moltes funcions.
        bool ulttext; //Booleà que ens indica si hi ha un text triat per a facilitar la mostra d'errors al programa principal.
	
        
	  //Estructures de Cites
        map<string,set<string> >citesassoaut; //Map <autor, set<referència> >. Guardem les cites associades a cada autor per a facilitar les funcions de cerca. 
        map<string,Cita> mapcites; //Llibreria de cites, on la key és la referència d'aquesta.
        map<string, int> contador;//Estructura per dur el recompte de la id a afegir a les inicials dels autors i així crear la referència per a cada cita.
  
	public:
	
        //Constructores
        
    /** @brief Creadora per defecte. 

        S'executa automàticament al declarar una biblioteca.
        \pre <em>cert</em>
        \post el resultat és una biblioteca buida.
  */  
        Biblio();
        
        
        //Destructora
    /** @brief Destructora per defecte. 

        Esborra automàticament els objectes locals en sortir
        d'un àmbit de visibilitat.
  */         
        ~Biblio();
        
        //Modificadors de Textos
        
  /** @brief Afegeix un text a la biblioteca.
      \pre <em>cert.</em>
      \post Si l'autor ja existia, s'ha afegit aquest text com un més a la seva colecció de textos ordenats alfabèticament per títol. Si no hi era, es crea una nova entrada amb el nom de l'autor i se li afegeix aquest text.
      Si el text que s'intenta afegir coincideix en títol i autor amb un que ja és al sistema, es produeix un missatge d'error.
  */        
        void AfegirText(string titol);
	
  /** @brief Triem un text de la biblioteca.
      \pre <em>l'entrada és una seqüència de paraules.</em>
      \post si les paraules es troben a un text i a cap més, guardem l'últim text triat, si no, es produeix un missatge d'error.
  */
	    void TriarText(string paraules);
	
  /** @brief Normalitzem el contingut.
      \pre <em>l'entrada és cada una de les línies del contingut que anem llegint.</em>
      \post la frase normalitzada, és a dir, amb tots els signes de puntuació separats del text per a facilitar la introducció d'aquest a la nostra matriu.
  */	
    	void normalitzar (string &linia);

  /** @brief Eliminar text de la biblioteca.
      \pre <em>la biblioteca no és buida i s'ha seleccionat un text amb l'opció TriarText.</em>
      \post s'elimina del sistema l'últim text triat.
  */
	void EliminarText();
	
  /** @brief Substitueix paraules en el text.
      \pre <em>El sistema té un text triat.</em>
      \post canvia les aparicions de <em>paraula1</em> per <em>paraula2</em> en el contingut de l'últim text triat. Si no hi ha cap text triat, es produeix un missatge d'error.
  */
	void SubText(string paraula1, string paraula2);
	
        
        //Consultora de textos
        
  /** @brief Hi ha text triat.
      \pre <em>cert.</em>
      \post Ens indica si el sistema té un últim text triat.
  */
	bool hihatexttriat();
	
	
  /** @brief Mostrar els textos d'un autor.
      \pre <em>cert.</em>
      \post mostra tots els textos d'un determinat autor (només el títol de cada text) ordenats alfabèticament per títol. Si l'autor no es troba a la biblioteca, es genera un missatge d'error.
  */        
	void TextosAutor(string autor);

  /** @brief Mostrar els textos del sistema.
      \pre <em>cert.</em>
      \post mostra tots els textos enmagatzemats al sistema (només el títol i l'autor de cada text) ordenats alfabèticament per títol.
  */
	void TotsTextos();

  /** @brief Mostrar tots els autors del sistema.
      \pre <em>cert.</em>
      \post mostra tots els autors amb textos en el sistema indicant per a cadascun el nombre de textos que hi consten, el nombre total de frases i de paraules del contingut dels seus textos (els autors apareixen ordenats alfabèticament).
  */	
	void TotsAutors();
    
  /** @brief Mostra informació de l'últim text triat. 
      \pre <em>cert.</em>
      \post mostra informació de l'últim text triat: autor, títol, nombre de frases, nombre de paraules i cites associades. Si no hi ha cap text triat, es produeix un missatge d'error.
  */
	void info();

  /** @brief Mostra l'autor de l'últim text triat. 
      \pre <em>cert.</em>
      \post mostra l'autor de l'últim text triat.Si no hi ha text triat, es produeix un missatge d'error.
  */	
	void autor();

  /** @brief Mostra el contingut de l'últim text triat. 
      \pre <em>cert.</em>
      \post mostra el contingut de l'últim text triat amb les seves frases numerades a partir de l'1. Si no hi ha cap text triat, es produeix un missatge d'error.
  */		
	void contingut();

  /** @brief Frases específiques. 
      \pre <em>Hi ha un text seleccionat.</em>
      \post mostra les frases entre la x-èssima i la y-èssima del contingut de l'últim text triat. Si no hi ha cap text triat, es produeix un missatge d'error.
  */		
	void frases(int x, int y);

  /** @brief Nombre de frases. 
      \pre <em>cert.</em>
      \post mostra el nombre de frases del contingut de l'últim text triat. Si no hi ha cap text triat, es produeix un missatge d'error.
  */	
	void nombrefrases();

  /** @brief Nombre de paraules. 
      \pre <em>cert.</em>
      \post mostra el nombre de paraules del contingut de l'últim text triat. Si no hi ha cap text triat, es produeix un missatge d'error.
  */	
	void nombreparaules();

  /** @brief Taula de freqüències.
      \pre <em>cert.</em>
      \post mostra totes les paraules de l'últim text triat ordenades decreixentment per freqüència. Si no hi ha cap text triat, es produeix un missatge d'error.
  */	
	void tauladefrecuencies();

  /** @brief Frases amb expressió concreta. 
      \pre <em>el símbol és "&" o "|" i com a mínim hi ha una expressió entre { }.</em>
      \post mostra les frases del contingut de l'últim text triat que compleixen l'expressió boleana determinada pel "símbol". Si no hi ha cap text triat, es produeix un missatge d'error.
  */        
	void frasesexpresio(string expresio);

  /** @brief Frases amb paraules concretes. 
      \pre <em>cert.</em>
      \post mostra les frases on hi apareix, consecutivament, obviant els signes de puntuació, la seqüència de paraules <em>paraula1</em>, <em>paraula2</em>...<em>paraulaN</em> en el contingut de l'últim text triat. Si no hi ha cap text triat, es produeix un missatge d'error.
  */ 	
	void frasesparaules(vector<string> paraules);

        //Modificadores de Cites
  /** @brief Afegeix cita.
      \pre <em>cert.</em>
      \post si no existia una cita amb el mateix nom i autor que la que s'està introduïnt, i l'interval de x i y està entre 1<=x<=y<=n, on n és el nombre total de frases, afegeix una cita al sistema basada en les frases que van de la x-èsima a la y-èsima del contingut del text triat. Altrament es produeix un error.Si no hi ha cap text triat, també es produeix un missatge d'error.
  */ 		
  void afegircita(int x, int y);

  /** @brief Elimina cita.
      \pre <em>cert.</em>
      \post si existeix, elimina la cita amb codi <em>referència</em> del sistema, altrament produeix un missatge d'error.
  */         
  void eliminarcita(const string &referencia);

	
        //Consultora de cites
  /** @brief Informació de la cita.
      \pre <em>cert.</em>
      \post si existeix, mostra informació de la cita: l'autor, el títol, el número de frase inicial i número de frase final, contingut de la frase o frases que la componen. Si no existeix, es genera un missatge d'error.
  */         
	void infocita(string referencia);
	
  /** @brief Cites d'un autor.
      \pre <em>cert.</em>
      \post mostra totes les cites d'un determinat autor ordenades per referència.
  */
	void citesAutor(string autor_cites);
 
  /** @brief Cites de l'últim text triat.
      \pre <em>cert.</em>
      \post mostra totes les cites de l'últim text triat ordenades per referència. Si no hi ha cap text triat, es produeix un missatge d'error.
  */	
	void cites();

  /** @brief Totes les cites del sitema.
      \pre <em>cert.</em>
      \post mostra totes les cites ordenades per referència.
  */		
	void totescites();
};
#endif

