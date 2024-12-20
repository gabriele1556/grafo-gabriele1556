#include <iostream>
#include "Grafo.cpp" 

int main() {
    // Creazione del grafo
    Grafo<std::string> grafo;

    // Aggiunta dei nodi (nazioni)
    grafo.aggiungiNodo("Italia");
    grafo.aggiungiNodo("Francia");
    grafo.aggiungiNodo("Spagna");
    grafo.aggiungiNodo("Germania");
    grafo.aggiungiNodo("Polonia");

    // Aggiunta degli archi con i pesi (distanze tra le nazioni in km)
    grafo.aggiungiArco("Italia", "Francia", 1400);   // Distanza tra Italia e Francia (in km)
    grafo.aggiungiArco("Francia", "Spagna", 1200);   // Distanza tra Francia e Spagna
    grafo.aggiungiArco("Spagna", "Germania", 1500);  // Distanza tra Spagna e Germania
    grafo.aggiungiArco("Germania", "Polonia", 500);  // Distanza tra Germania e Polonia
    grafo.aggiungiArco("Polonia", "Italia", 1300);   // Distanza tra Polonia e Italia

    // Visualizzazione del grafo (matrice di adiacenza)
    grafo.stampa();

    // Verifica se un nodo esiste
    std::cout << "\nEsiste il nodo 'Francia'? " << (grafo.verificaNodo("Francia") ? "Sì" : "No") << "\n";
    std::cout << "Esiste il nodo 'Svizzera'? " << (grafo.verificaNodo("Svizzera") ? "Sì" : "No") << "\n";

    // Verifica se esiste un arco tra due nodi
    std::cout << "\nEsiste un arco tra Italia e Francia? " << (grafo.verificaArco("Italia", "Francia") ? "Sì" : "No") << "\n";
    std::cout << "Esiste un arco tra Germania e Polonia? " << (grafo.verificaArco("Germania", "Polonia") ? "Sì" : "No") << "\n";

    // Verifica la connessione tra due nodi
    std::cout << "\nSono connessi Italia e Francia? " << (grafo.sonoConnessi("Italia", "Francia") ? "Sì" : "No") << "\n";
    std::cout << "Sono connessi Italia e Germania? " << (grafo.sonoConnessi("Italia", "Germania") ? "Sì" : "No") << "\n";

    // Trova l'arco con il peso minore da Italia
    grafo.arcoMinimo("Italia");

    // Nodi adiacenti a Italia
    grafo.nodiAdiacenti("Italia");

    // Rimozione di un nodo e dei suoi archi
    grafo.rimuoviNodo("Polonia");
    std::cout << "\nDopo la rimozione della Polonia:\n";
    grafo.stampa();

    // Rimozione di un arco specifico
    grafo.rimuoviArco("Italia", "Francia");
    std::cout << "\nDopo la rimozione dell'arco Italia-Francia:\n";
    grafo.stampa();

    // Aggiunta di un nuovo nodo e arco
    grafo.aggiungiNodo("Svizzera");
    grafo.aggiungiArco("Svizzera", "Italia", 300); // Distanza tra Italia e Svizzera
    std::cout << "\nDopo l'aggiunta della Svizzera e l'arco Svizzera-Italia:\n";
    grafo.stampa();

    // Applicazione dell'algoritmo di Dijkstra (cammini minimi da Italia)
    grafo.dijkstra("Italia");

    return 0;
}
