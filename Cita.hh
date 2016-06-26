/** @file Cita.hh
    @brief Especificació de la classe Cita
*/
#ifndef CITA_HH
#define CITA_HH

#include "Text.hh"
#ifndef NO_DIAGRAM 
#include <string>
#include <vector>
#include <iostream>
#endif
using namespace std;
/** @class Cita
    @brief Representa una cita dins del tetx

    Conté identificador, contingut, text de procedència, frase inicial i final.
*/
class Cita{
     private:
       string id; //Guardem la referència de la cita
       vector <vector <string> >contingut_cita; //contingut de la cita 
       int _x; //línia inicial
       int _y; // línia final
       string titlprocedent; //títol del text de procedència
       string autrprocedent; //autor del text de procedència
     public:
         
        //Creadores
        
 /** @brief Creadora per defecte. 

        S'executa automàticament en declarar una cita.
        \pre <em>cert</em>
        \post el resultat és una cita buida
  */         
        
  Cita();
    /** @brief Creadora. 

        S'executa en declarar una cita.
        \pre <em>cert</em>
        \post el resultat és una cita amb un id = referencia, amb un contingut i un valor x (frase inicial) i un valor y (frase final) del text d'on procedeixen
  */           
  Cita(string referencia,const Text &proceden,int ini,int fi);

        
        //Consultores
        
        
  /** @brief Referència de la cita
      \pre <em>cert</em>
      \post retorna la referència de la cita.
  */          
  string referencia(); 

  /** @brief Text de procedència de la cita
      \pre <em>cert</em>
      \post retorna el text de procedència de la cita.
  */          
  string txt();

  /** @brief Frase inicial de la cita
      \pre <em>cert</em>
      \post retorna la frase inicial de la cita.
  */        
  int valor_x();

  /** @brief Frase final de la cita
      \pre <em>cert</em>
      \post retorna la frase final de la cita.
  */          
  int valor_y();
  
  /** @brief Autor Procedent
      \pre <em>cert</em>
      \post retorna el autor de procedència de la Cita.
  */
  
  string aut_procedent() const;
  
  /** @brief Títol Procedent 
      \pre <em>cert</em>
      \post retorna el títol de procedència de la Cita.
  */
  
  string tit_proc () const;
  
  /** @brief Imprimir contingut
      \pre <em>cert</em>
      \post Mostra per pantalla el contigut d'una Cita.
  */
  
  void imp_contingut();
};
#endif
  
