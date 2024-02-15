#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// Definim un alias per a l'unordered_map que emmagatzemarà les traduccions
using TraduccionsMap = unordered_map<string, string>;

// Funció per llegir el fitxer de traduccions i emmagatzemar-les en un unordered_map
TraduccionsMap llegirFitxerTraduccions(const string& Traduccio) {
    TraduccionsMap traduccions;
    ifstream fitxer(Traduccio);
    if (!fitxer) {
        cerr << "Error en obrir el fitxer de traduccions: " << Traduccio << endl;
        return traduccions; // Retornem un map buit en cas d'error
    }

    string linia;
    while (getline(fitxer, linia)) {
        size_t pos = linia.find(' ');
        if (pos != string::npos) {
            string clau = linia.substr(0, pos);
            string valor = linia.substr(pos + 1);
            traduccions[clau] = valor;
        }
    }

    fitxer.close();
    return traduccions;
}

// Funció per mostrar un text utilitzant les traduccions proporcionades
void mostrarText(const string& text, const TraduccionsMap& traduccions) {
    auto it = traduccions.find(text);
    if (it != traduccions.end()) {
        cout << "Traduccio obtinguda: " << it->second << endl;
    }
    else {
        cout << "Traduccio no disponible per aquest idioma." << endl;
    }
}

// Funció per validar si un idioma és vàlid
bool idiomaValid(const string& idioma) {
    // Llista d'idiomes vàlids
    const vector<string> idiomes_valids = { "CA", "EU", "GL", "OC", "ES", "EN", "FR", "DE", "IT", "PT", "NL", "SV", "PL", "DA" };
    // Comprovació si l'idioma és a la llista d'idiomes vàlids
    return find(idiomes_valids.begin(), idiomes_valids.end(), idioma) != idiomes_valids.end();
}

string demanarText(string prompt) {
    string resposta;
    cout << "Introdueix " << prompt;
    getline(cin, resposta);
    return resposta;
}

int demanarNumero(string prompt) {
    int resposta;
    cout << "Si us plau, escriu el " << prompt;
    cin >> resposta;
    return resposta;
}

void explicarHistoria(string nom, string nomPlural, int numero, string partCos, string verb) {
    cout << "\nAqui tens la teva historia d'encaixar bojos:\n";
    cout << "En un regne molt llunya, " << nom << " va decidir aventurar-se pel bosc encantat.\n";
    cout << "Alla, van trobar un grup de " << nomPlural << " amigables.\n";
    cout << "Per sorpresa, els " << nomPlural << " van comencar a parlar i van demanar " << numero << " desitjos magics.\n";
    cout << "Amb molta emocio, " << nom << " va utilitzar la seva " << partCos << " per realitzar una dansa unica.\n";
    cout << "Al final, el bosc es va transformar en una terra encantada de " << verb << ", i tothom va viure felic per sempre.\n";
}

int main() {
    // Llegir fitxer de traduccions del narrador
    TraduccionsMap traduccionsNarrador = llegirFitxerTraduccions("Traduccio2.txt");
    // Demanar a l'usuari que seleccioni un idioma
    string idioma;
    cout << "Selecciona un idioma (CA, EU, GL, OC, ES, EN, FR, DE, IT, PT, NL, SV, PL, DA): ";
    cin >> idioma;

    // Validar l'idioma ingressat
    while (!idiomaValid(idioma)) {
        cout << "Idioma no valid. Si us plau, torna-ho a intentar: ";
        cin >> idioma;
    }

    // Mostrar presentació del narrador en l'idioma seleccionat
    mostrarText(idioma, traduccionsNarrador);

    cout << "Benvingut a Mad Libs. \n\n";
    cout << "Respon les seguents preguntes per ajudar a crear una nova historia.\n";

    // Obtenir les entrades de l'usuari
    string nom;
    string nomPlural;
    cout << "Si us plau, introdueix un nom: ";
    cin >> nom;
    cin.ignore(); // Netegem el buffer del salt de línia

    cout << "Si us plau, introdueix un nom en plural: ";
    getline(cin, nomPlural);

    string partCos = demanarText("una part del cos: ");
    string verb = demanarText("un verb: ");
    int numero = demanarNumero("un numero: ");

    // Mostrar la història de Mad Libs
    explicarHistoria(nom, nomPlural, numero, partCos, verb);

    return 0;
}