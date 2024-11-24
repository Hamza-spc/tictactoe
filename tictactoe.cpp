#include <iostream>
using namespace std;

class Cellule
{
private:
    int joueur; // 0 pour vide, 1 pour joueur 1 (X), 2 pour joueur 2 (O)

public:
    // Constructeur par défaut, initialise la cellule à vide
    Cellule() : joueur(0) {};

    // Constructeur avec un joueur spécifié
    Cellule(int j) : joueur(j) {};

    // Affiche le symbole de la cellule : vide, X ou O
    string afficherCellule()
    {
        if (joueur == 0)
        {
            return " "; // Cellule vide
        }
        else if (joueur == 1)
        {
            return "X"; // Symbole pour joueur 1
        }
        else if (joueur == 2)
        {
            return "O"; // Symbole pour joueur 2
        }
        return " "; // Par sécurité, retourne un espace
    }

    // Déclaration de la classe Grille comme amie pour l'accès à la cellule
    friend class Grille;
};

class Grille
{
private:
    Cellule tab[3][3]; // Grille 3x3

public:
    // Affiche l'état actuel de la grille
    void afficherGrille()
    {
        cout << "-----------------" << endl;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << tab[i][j].afficherCellule(); // Affiche chaque cellule
                if (j < 2)
                    cout << " | "; // Ajoute un séparateur entre les cellules sauf à la fin de la ligne
            }
            cout << endl;
            if (i < 2)
                cout << "-----------------" << endl; // Séparation des lignes de la grille
        }
        cout << "-----------------" << endl;
    }

    // Fonction pour effectuer un coup
    bool jouer(int joueur_actuel)
    {
        int ligne, colonne;
        cout << "Joueur " << joueur_actuel << ", à vous de jouer!" << endl;
        cout << "Entrez la ligne (0-2): ";
        cin >> ligne;
        cout << "Entrez la colonne (0-2): ";
        cin >> colonne;

        // Vérifie si la cellule est déjà occupée
        if (tab[ligne][colonne].joueur != 0)
        {
            cout << "La cellule est déjà occupée, essayez une autre!" << endl;
            return false;
        }

        // Place le symbole du joueur dans la cellule
        tab[ligne][colonne].joueur = joueur_actuel;
        return true;
    }

    // Vérifie si un joueur a gagné
    bool verifierGagnant(int joueur)
    {
        // Vérifier les lignes et les colonnes
        for (int i = 0; i < 3; i++)
        {
            if ((tab[i][0].joueur == joueur && tab[i][1].joueur == joueur && tab[i][2].joueur == joueur) || // Ligne
                (tab[0][i].joueur == joueur && tab[1][i].joueur == joueur && tab[2][i].joueur == joueur))   // Colonne
            {
                return true;
            }
        }

        // Vérifier les diagonales
        if ((tab[0][0].joueur == joueur && tab[1][1].joueur == joueur && tab[2][2].joueur == joueur) || // Diagonale 1
            (tab[0][2].joueur == joueur && tab[1][1].joueur == joueur && tab[2][0].joueur == joueur))   // Diagonale 2
        {
            return true;
        }

        return false;
    }

    // Vérifie si la grille est pleine (match nul)
    bool estPleine()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (tab[i][j].joueur == 0) // Si une cellule est vide, la grille n'est pas pleine
                {
                    return false;
                }
            }
        }
        return true; // La grille est pleine
    }
};

int main()
{
    Grille grille;
    int joueur_actuel = 1; // Le joueur 1 commence (X)
    bool jeuFini = false;

    // Jeu principal
    while (!jeuFini)
    {
        grille.afficherGrille(); // Affiche la grille après chaque mouvement
        bool mouvementValide = false;

        // Demande au joueur de jouer tant que le mouvement est invalide
        while (!mouvementValide)
        {
            mouvementValide = grille.jouer(joueur_actuel); // Essaye de faire un mouvement
        }

        // Vérifie si le joueur actuel a gagné
        if (grille.verifierGagnant(joueur_actuel))
        {
            grille.afficherGrille();
            cout << "Le joueur " << joueur_actuel << " a gagné!" << endl;
            jeuFini = true;
        }
        else if (grille.estPleine()) // Vérifie si la grille est pleine (match nul)
        {
            grille.afficherGrille();
            cout << "C'est un match nul!" << endl;
            jeuFini = true;
        }

        // Change de joueur
        joueur_actuel = (joueur_actuel == 1) ? 2 : 1;
    }

    return 0;
}
