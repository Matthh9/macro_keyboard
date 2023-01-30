// scancode keyboard qwerty et correspondance azerty
// ---------------------------------------------------
//  ' ' est le symbole qui désigne un espace, il a la valeur 44
//  Alt Gr azerty                   €                                                                    ~  #  {  [  |  `  \  ^  @    ' '  ]  }  ¤       
//   Shift azerty       Q  B  C  D  E  F  G  H  I  J  K  L  ?  N  O  P  A  R  S  T  U  V  Z  X  Y  W  1  2  3  4  5  6  7  8  9  0    ' '  °  +  ¨  £  µ  No fr  M  %  NONE  .  /  §    >
//         azerty       q  b  c  d  e  f  g  h  i  j  k  l  ,  n  o  p  a  r  s  t  u  v  z  x  y  w  &  é  "  '  (  -  è  _  ç  à    ' '  )  =  ^  $  *  No fr  m  ù   ²    ;  :  !    <
//         qwerty       a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z  1  2  3  4  5  6  7  8  9  0    ' '  -  =  [  ]  \  No US  ;  '   `    ,  .  /   No US      
//       scancode       4, 5, 6, 7, 8, 9, 10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,  44, 45,46,47,48,49,  50,  51,52, 53,  54,55,56,  100}; 


#include <Keyboard.h>
#include <Mouse.h>

#define dureeAppuieLong 250 //définition de la durée d'un appuie long (en milliseconde)


//Variables globales
int dernierBoutonActive = 0 ; //cette variable va permettre de modifier le comportement de certaine touche comme la touche coller si on a appuyé sur opérator note juste avant
bool court_long = 0 ;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/***fonction de vérification d'un appuie long ou court
 * in : le port sur lequel on souhaite faire la vérification
 * out : bool : 0 = appuie court / 1 : appuie long
***/
bool appuie_court_long(int port){
  unsigned long debutAppuie = millis();
  unsigned long finAppuie;

  delay(50);
  
  while(digitalRead(port)==LOW){
    finAppuie = millis();
    if (finAppuie-debutAppuie>dureeAppuieLong){
      return 1;
    }
  }
  return 0;
}


/*** fonction permettant d'attendre qu'on relache le bouton et permettant de stocker la valeur du dernier bouton activé pour différencier les fonctionnement
 *  in : le port sur lequel on souhaite faire la vérification
 *  out : rien
 */
void fin_appuie(int port){
  while(digitalRead(port) == LOW);
  dernierBoutonActive=port;
  //court_long=0;
  Keyboard.releaseAll();
  Mouse.release();
  //pour éviter les derniers rebonds parasites
  delay(100);
}

/*** fonction permettant d'envoeyr les commandes pour fermer l'operator note
 *  in : rien
 *  out : rien
 */
void fermer_operator_note(){
  Keyboard.press(KEY_TAB);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void setup() {
  // put your setup code here, to run once:
  for (int i = 2; i <= 9; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  Serial.begin(9600);

  Keyboard.begin();
  Mouse.begin();
}


void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(2) == LOW){
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press('a');
    Keyboard.releaseAll();
    delay(700);
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('q');
    Keyboard.releaseAll();

    court_long = appuie_court_long(2);
    
    while( (digitalRead(2) == LOW) and court_long){
      if (digitalRead(5) == LOW){
        Keyboard.press(KEY_RIGHT_ALT);
        Keyboard.press('3');
        Keyboard.releaseAll();
        Keyboard.print("GC ");
        fin_appuie(5);
      }
      if (digitalRead(6) == LOW){
        Keyboard.press(KEY_RIGHT_ALT);
        Keyboard.press('3');
        Keyboard.releaseAll();
        Keyboard.print("FG");
        fermer_operator_note();
        fin_appuie(6);
      }
      if (digitalRead(7) == LOW){
        Keyboard.press(KEY_RIGHT_ALT);
        Keyboard.press('3');
        Keyboard.releaseAll();
        Keyboard.print("PRG");
        fermer_operator_note();
        fin_appuie(7);
      }
      if (digitalRead(8) == LOW){
        Keyboard.press(KEY_RIGHT_ALT);
        Keyboard.press('3');
        Keyboard.releaseAll();
        Keyboard.print("TTL 6 ");
        fin_appuie(8);
      }
      if (digitalRead(9) == LOW){
        Keyboard.press(KEY_RIGHT_ALT);
        Keyboard.press('3');
        Keyboard.releaseAll();
        Keyboard.print("NP 6 ");
        fin_appuie(9);
      }
    }

    fin_appuie(2);
  }
  
  if (digitalRead(3) == LOW){
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press('t');
    Keyboard.releaseAll();
    fin_appuie(3);
  }

  if (digitalRead(4) == LOW){
    court_long = appuie_court_long(4);
    if (not(court_long)){
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('v');
      fin_appuie(4);
      //associate TT
    } else{ //create TT
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('a');
    }
    Keyboard.releaseAll();
    fin_appuie(4);
  }
  
  //select all et si appuie long select all temip
  if (digitalRead(5) == LOW){
    court_long = appuie_court_long(5);
    if (not(court_long)){
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('q');
    } else{
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('q');
    }
    Keyboard.releaseAll();
    fin_appuie(5);
  }
  
  if (digitalRead(6) == LOW){
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('c');
    Keyboard.releaseAll();
    court_long = appuie_court_long(6);
    if (court_long){
      fermer_operator_note();
    }
    fin_appuie(6);
  }
  
  if (digitalRead(7) == LOW){
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('v');
    Keyboard.releaseAll();
    court_long = appuie_court_long(7);
    if (court_long){
      fermer_operator_note();
    }
    fin_appuie(7);
  }
  
  if (digitalRead(8) == LOW){
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('s');
    Keyboard.releaseAll();
    fin_appuie(8);
  }
  
  if (digitalRead(9) == LOW){
    court_long = appuie_court_long(9);

    if(not(court_long)){
      Mouse.press(MOUSE_LEFT);
    }

    //fonctions spéciales si on reste appuyé sur la touche
    while( (digitalRead(9) == LOW) and court_long){
      //fonction de navigation sur GIR
      if (digitalRead(2) == LOW){
        //déplacement et écriture de 5 - JO
        Keyboard.press(KEY_TAB);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.print("5");
        Keyboard.releaseAll();
        Keyboard.print("6jo");
        delay(150);

        //déplacement et écriture de  mineur
        Keyboard.press(KEY_TAB);
        Keyboard.print(";ineure");
        Keyboard.releaseAll();
        
        Keyboard.press(KEY_TAB);
        Keyboard.releaseAll();
        
        fin_appuie(2);
      }

      if (digitalRead(3) == LOW){
        //déplacement et écriture de 5 - JO
        Keyboard.press(KEY_TAB);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.print("24");
        Keyboard.releaseAll();
        Keyboard.print("6h");
        delay(150);

        //déplacement et écriture de  mineur
        Keyboard.press(KEY_TAB);
        Keyboard.print(";qjeur");
        Keyboard.releaseAll();

        //déplacement et mettre oui pour impact
        Keyboard.press(KEY_TAB);
        Keyboard.print("oui");
        Keyboard.releaseAll();

        Keyboard.press(KEY_TAB);
        Keyboard.releaseAll();
        fin_appuie(3);
      }
      
      //fonction loggin
      if (digitalRead(6) == LOW){
        Keyboard.print("");//loggin
        Keyboard.releaseAll();
        Keyboard.press(KEY_TAB);
        Keyboard.releaseAll();
        fin_appuie(6);
      }
      if (digitalRead(7) == LOW){
        //implémentation du mot de passe
        Keyboard.releaseAll();
        fin_appuie(7);
      }
    }

    fin_appuie(9);
  }

}
