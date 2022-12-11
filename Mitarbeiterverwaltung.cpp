#include <iostream>
#include <string>
#include<string.h>

using namespace std;

class MITARBEITER
{
    private:
         string vorname;
         string nachname;
         string geburtsdatum;
         int genommenerUrlaub;
         int restlicherUrlaub;

    public:

        //leerer Konstruktor
        MITARBEITER(){};
        //Konstruktor mit Parametern für Vor/Nachname, Geburtstag und bereits genommener Urlaub
        MITARBEITER(string vname, string nname, string gdatum):vorname(vname),nachname(nname),geburtsdatum(gdatum){
        //Stellt sicher, dass man das Datum im korrekten Format (xx.yy.zzzz) angibt
        if(gdatum.length() != 10){
            cout<<"Dein Datum ist im falschen Format, bitte gib es so an: xx.yy.zzzz"<<endl;
        }

        //klärt ab, ob man 32 Tage oder 30 Tage Urlaub bekommt
        int jahr = stoi(geburtsdatum.substr(6,9));
        if((2022-jahr) > 50){
            restlicherUrlaub = 32;
            cout<<"Dir stehen 32 Tage Urlaub zu"<<endl;
        }else{
            restlicherUrlaub = 30;
            cout<<"Dir stehen 30 Tage Urlaub zu"<<endl;
        }

        };
        //Dekonstruktor
        ~MITARBEITER(){};

        //berechnet den restlichen Urlaub, wenn man sich freigenommen hat
        int berechneResturlaub(int tage){
            restlicherUrlaub -= tage;
            genommenerUrlaub += tage;
            return restlicherUrlaub;
        }

        //gibt alle Daten zu einem Mitarbeiter aus
        void zeigeDaten(){
            cout<<"-------"<<endl;
            cout<<"Vorname: "<<vorname<<endl;
            cout<<"Nachname: "<<nachname<<endl;
            cout<<"Geburtstdatum: "<<geburtsdatum<<endl;
            cout<<"Restlicher Urlaub: "<<restlicherUrlaub<<endl;
            cout<<"Genommener Urlaub: "<<genommenerUrlaub<<endl;
            cout<<"-------"<<endl;
        }

        //fragt den user nach dem Vornamen und gibt diesen zurück
        static string frageNachVorname(){
            cout<<"Vorname: ";
            string vorname1;
            cin>>vorname1;
            return vorname1;
        }

        //fragt den user nach dem Nachnamen und gibt diesen zurück
         static string frageNachNachname(){
            cout<<"Nachname: ";
            string nachname1;
            cin>>nachname1;
            return nachname1;
        }

        string getVorname(){
            return vorname;
        }

        string getNachname(){
            return nachname;
        }

        int getRestlicherUrlaub(){
            return restlicherUrlaub;
        }

};


int main()
{
    //Stellt array mit 500 Plätzen zur Speicheerung der Mitarbeiter zur Verfügung
    MITARBEITER alle[500];
    //zählt, wie viele Mitarbeiter es gibt
    static int zaehler = 0;

   while(true){

    //Erstellt ein Menü
    cout<<endl;
    cout<<"Hallo! Willkommen zur Mitarbeiterverwaltung. Was moechtest du tun?"<<endl;
    cout<<"[1] Mitarbeiter anlegen"<<endl;
    cout<<"[2] Mitarbeiter loeschen"<<endl;
    cout<<"[3] Urlaub nehmen"<<endl;
    cout<<"[4] Mitarbeiter suchen und Daten anzeigen lassen"<<endl;
    cout<<"[5] Alle Mitarbeiter anzeigen lassen"<<endl;
    cout<<"[6] Programm beenden"<<endl;

   int auswahl;
   cin>>auswahl;

    switch(auswahl){
    //erlaubt es einen neuen Mitarbeiter anzulegen
    case 1:{
        cout<<"Mitarbeiter anlegen: "<<endl;

        string vorname1 = MITARBEITER::frageNachVorname();

        string nachname1 = MITARBEITER::frageNachNachname();

        cout<<"Geburtsdatum (Format: xx.yy.zzzz): ";
        string geburtsdatum1;
        cin>>geburtsdatum1;

        if(zaehler <= 499){
            MITARBEITER neu = MITARBEITER(vorname1, nachname1, geburtsdatum1);
            alle[zaehler] = neu;
            zaehler++;
        }
        break;
    }
    //erlaubt es, einen Mitarbeiter zu löschen
    case 2:{

        cout<<"Welchen Mitarbeiter moechtest du loeschen?"<<endl;

        string vorname1 = MITARBEITER::frageNachVorname();

        string nachname1 = MITARBEITER::frageNachNachname();

        for(int i = 0; i<zaehler; i++){

            string vorname2 = alle[i].getVorname();
            string nachname2 = alle[i].getNachname();

            int res = vorname1.compare(vorname2);
            int res1 = nachname1.compare(nachname2);

            if((res == 0)&& (res1 == 0)){
               alle[i] = MITARBEITER();
               alle[i] = alle[i+1];
               zaehler--;
               cout<<"Mitarbeiter "<<vorname2<<" "<<nachname2<<" wurde geloescht!"<<endl;
            }else{
            cout<<"Dieser Mitarbeiter existiert nicht!"<<endl;
            }
        }

        break;
    }
    //Erlaubt es einem Mitarbeiter Urlaub zu nehmen
    case 3:{

        cout<<"Wer moechte Urlaub nehmen?"<<endl;

        string vorname1 = MITARBEITER::frageNachVorname();

        string nachname1 = MITARBEITER::frageNachNachname();

        cout<<"Wieviele Tage willst du frei nehmen?"<<endl;
        int anzahlFreieTage;
        cin>>anzahlFreieTage;

        for(int i = 0; i<zaehler; i++){

            string vorname2 = alle[i].getVorname();
            string nachname2 = alle[i].getNachname();

            int res = vorname1.compare(vorname2);
            int res1 = nachname1.compare(nachname2);

            if((res == 0)&& (res1 == 0)){
                alle[i].berechneResturlaub(anzahlFreieTage);
                cout<<"Du hast noch "<<alle[i].getRestlicherUrlaub()<<" freie Tage uebrig"<<endl;
            }else{
                cout<<"Mitarbeiter nicht gefunden!"<<endl;
            }
        }

        break;

    }
    //Erlaubt es, die Daten eines bestimmten Mitarbeiters anzuzeigen
    case 4:{

        cout<<"Wen suchst du?"<<endl;

        string vorname1 = MITARBEITER::frageNachVorname();

        string nachname1 = MITARBEITER::frageNachNachname();

        MITARBEITER gesucht;

        for(int i = 0; i<zaehler; i++){

            string vorname2 = alle[i].getVorname();
            string nachname2 = alle[i].getNachname();

            int res = vorname1.compare(vorname2);
            int res1 = nachname1.compare(nachname2);

            if((res == 0)&& (res1 == 0)){
               gesucht = alle[i];
               gesucht.zeigeDaten();
            }else{
                cout<<"Dieser Mitarbeiter existiert nicht!"<<endl;
            }
        }


        break;
    }
    //zeigt alle gespeicherten Mitarbeiterdaten an
    case 5:{
        for(int i = 0; i < zaehler; i++){
                alle[i].zeigeDaten();
        }
        break;
    }
    //beendet das Programm
    case 6:{
        exit(0);
        break;
    }
    //Fehlerbehandlung, fall keine Zahl zwischen 1 und 6 eingegeben wurde
    default:{
        cout<<"Gib eine gueltige Nummer ein"<<endl;
    }

    }

   }

    return 0;
}


