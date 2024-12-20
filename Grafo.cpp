#include <iostream>

#define MAX_NODI 100
#define INF 1000000000 // Rappresenta l'assenza di connessione

template <typename T>
class Grafo {
private:
    T nodi[MAX_NODI]; // Array dei nodi
    int matriceAdiacenza[MAX_NODI][MAX_NODI]; // Matrice di adiacenza
    bool esisteNodo[MAX_NODI]; // Indica se un nodo esiste
    int numeroNodi = 0; // Numero attuale di nodi

public:
    // Costruttore
    Grafo() {
        for (int i = 0; i < MAX_NODI; ++i) {
            esisteNodo[i] = false;
            for (int j = 0; j < MAX_NODI; ++j) {
                matriceAdiacenza[i][j] = INF;
            }
            matriceAdiacenza[i][i] = 0; // La distanza da un nodo a se stesso è 0
        }
    }

    // Aggiunge un nodo al grafo
    void aggiungiNodo(const T& nodo) {
        if (numeroNodi >= MAX_NODI) {
            std::cout << "Errore: numero massimo di nodi raggiunto.\n";
            return;
        }
        for (int i = 0; i < numeroNodi; ++i) {
            if (esisteNodo[i] && nodi[i] == nodo) {
                std::cout << "Errore: il nodo esiste già.\n";
                return;
            }
        }
        nodi[numeroNodi] = nodo;
        esisteNodo[numeroNodi] = true;
        numeroNodi++;
    }

    // Aggiunge un arco tra due nodi
    void aggiungiArco(const T& sorgente, const T& destinazione, int peso) {
        int indiceSorgente = trovaIndice(sorgente);
        int indiceDestinazione = trovaIndice(destinazione);

        if (indiceSorgente == -1 || indiceDestinazione == -1) {
            std::cout << "Errore: uno o entrambi i nodi non esistono.\n";
            return;
        }
        matriceAdiacenza[indiceSorgente][indiceDestinazione] = peso;
    }

    // Rimuove un nodo e tutti i suoi archi
    void rimuoviNodo(const T& nodo) {
        int indice = trovaIndice(nodo);
        if (indice == -1) {
            std::cout << "Errore: il nodo non esiste.\n";
            return;
        }
        esisteNodo[indice] = false;
        for (int i = 0; i < MAX_NODI; ++i) {
            matriceAdiacenza[indice][i] = INF;
            matriceAdiacenza[i][indice] = INF;
        }
    }

    // Rimuove un arco
    void rimuoviArco(const T& sorgente, const T& destinazione) {
        int indiceSorgente = trovaIndice(sorgente);
        int indiceDestinazione = trovaIndice(destinazione);

        if (indiceSorgente == -1 || indiceDestinazione == -1) {
            std::cout << "Errore: uno o entrambi i nodi non esistono.\n";
            return;
        }
        matriceAdiacenza[indiceSorgente][indiceDestinazione] = INF;
    }

    // Verifica se due nodi sono connessi
    bool sonoConnessi(const T& nodo1, const T& nodo2) {
        int indice1 = trovaIndice(nodo1);
        int indice2 = trovaIndice(nodo2);
        if (indice1 == -1 || indice2 == -1) return false;

        // Se esiste un arco diretto tra i due nodi
        return matriceAdiacenza[indice1][indice2] != INF;
    }

    // Trova l'arco con il peso minore tra gli archi uscenti da un nodo
    void arcoMinimo(const T& nodo) {
        int indice = trovaIndice(nodo);
        if (indice == -1) {
            std::cout << "Errore: il nodo non esiste.\n";
            return;
        }

        int minPeso = INF;
        int minIndice = -1;
        for (int i = 0; i < numeroNodi; ++i) {
            if (matriceAdiacenza[indice][i] != INF && matriceAdiacenza[indice][i] < minPeso) {
                minPeso = matriceAdiacenza[indice][i];
                minIndice = i;
            }
        }

        if (minIndice != -1) {
            std::cout << "L'arco con peso minore uscenti da " << nodo << " è " << nodi[minIndice] << " (peso: " << minPeso << ")\n";
        } else {
            std::cout << "Non ci sono archi uscenti da " << nodo << ".\n";
        }
    }

    // Dijkstra per il cammino minimo da un nodo di partenza
    void dijkstra(const T& nodoPartenza) {
        int indicePartenza = trovaIndice(nodoPartenza);
        if (indicePartenza == -1) {
            std::cout << "Nodo di partenza non esistente.\n";
            return;
        }

        int distanze[MAX_NODI];
        bool visitato[MAX_NODI];
        
        // Inizializzo le distanze con INF e i nodi come non visitati
        for (int i = 0; i < numeroNodi; ++i) {
            distanze[i] = INF;
            visitato[i] = false;
        }
        distanze[indicePartenza] = 0;

        for (int i = 0; i < numeroNodi; ++i) {
            int nodoMinimo = -1;
            // Trovo il nodo con la distanza minima non visitato
            for (int j = 0; j < numeroNodi; ++j) {
                if (!visitato[j] && (nodoMinimo == -1 || distanze[j] < distanze[nodoMinimo])) {
                    nodoMinimo = j;
                }
            }

            if (distanze[nodoMinimo] == INF) break; // Tutti i nodi raggiungibili sono stati visitati

            visitato[nodoMinimo] = true;

            // Aggiorno le distanze dei nodi adiacenti
            for (int j = 0; j < numeroNodi; ++j) {
                if (matriceAdiacenza[nodoMinimo][j] != INF) {
                    int nuovaDist = distanze[nodoMinimo] + matriceAdiacenza[nodoMinimo][j];
                    if (nuovaDist < distanze[j]) {
                        distanze[j] = nuovaDist;
                    }
                }
            }
        }

        // Stampa i cammini minimi
        std::cout << "Cammini minimi da " << nodoPartenza << ":\n";
        for (int i = 0; i < numeroNodi; ++i) {
            if (distanze[i] == INF) {
                std::cout << nodi[i] << ": INFINITO\n";
            } else {
                std::cout << nodi[i] << ": " << distanze[i] << "\n";
            }
        }
    }

    // Stampa la matrice di adiacenza
    void stampa() const {
        std::cout << "Matrice di Adiacenza:\n";
        for (int i = 0; i < numeroNodi; ++i) {
            if (!esisteNodo[i]) continue;

            for (int j = 0; j < numeroNodi; ++j) {
                if (!esisteNodo[j]) continue;

                if (matriceAdiacenza[i][j] == INF) {
                    std::cout << "INF ";
                } else {
                    std::cout << matriceAdiacenza[i][j] << " ";
                }
            }
            std::cout << "\n";
        }
    }

    // Verifica se un nodo esiste
    bool verificaNodo(const T& nodo) const {
        return trovaIndice(nodo) != -1;
    }

    // Verifica se un arco esiste
    bool verificaArco(const T& sorgente, const T& destinazione) const {
        int indiceSorgente = trovaIndice(sorgente);
        int indiceDestinazione = trovaIndice(destinazione);

        if (indiceSorgente == -1 || indiceDestinazione == -1) {
            return false;
        }
        return matriceAdiacenza[indiceSorgente][indiceDestinazione] != INF;
    }

private:
    // Trova l'indice di un nodo
    int trovaIndice(const T& nodo) const {
        for (int i = 0; i < numeroNodi; ++i) {
            if (esisteNodo[i] && nodi[i] == nodo) {
                return i;
            }
        }
        return -1;
    }
};

