#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "game_aux.h"

/* ********** ASSERT ********** */

#define ASSERT(expr)                                                                        \
    do                                                                                      \
    {                                                                                       \
        if ((expr) == 0)                                                                    \
        {                                                                                   \
            fprintf(stderr, "[%s:%d] Assertion '%s' failed!\n", __FILE__, __LINE__, #expr); \
            abort();                                                                        \
        }                                                                                   \
    } while (0)

/* ********** TEST COMMUN ********** */

bool check_game(square *liste, game game_test){
    for (uint y = 0; y < DEFAULT_SIZE; y++)
    {
        for (uint x = 0; x < DEFAULT_SIZE; x++)
        {
            square carre = game_get_square(game_test, y, x);
            if (liste[x + DEFAULT_SIZE * y] != carre)
            {
                return false;
            }  
        }
    }
    return true;
}

/* ********** TEST game_new ********** */

bool test_game_new(){
    square array[DEFAULT_SIZE*DEFAULT_SIZE]= {
        S_BLANK,S_BLANK,S_BLACK1,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
        S_BLANK,S_BLANK,S_BLACK2,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACKU,S_BLACK2,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
        S_BLACK1,S_BLACKU,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACK2,S_BLANK,S_BLANK,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACKU,S_BLANK,S_BLANK
        };
    game game_test = game_new(array);

    square array_solution[DEFAULT_SIZE*DEFAULT_SIZE]= {S_LIGHTBULB | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLACK1,S_LIGHTBULB | F_LIGHTED, S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,
    S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED,S_BLACK2,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED,
    S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLACKU,S_BLACK2,
    S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED,
    S_BLACK1,S_BLACKU,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,
    S_LIGHTBULB | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLACK2,S_LIGHTBULB | F_LIGHTED,S_BLANK | F_LIGHTED,
    S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLACKU,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED};
    game g_test_sol = game_new(array_solution);

    square array_default[DEFAULT_SIZE*DEFAULT_SIZE]= {S_BLANK,S_BLANK,S_BLACK1,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACK2,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
    S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACKU,S_BLACK2,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
    S_BLACK1,S_BLACKU,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACK2,S_BLANK,S_BLANK,
    S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACKU,S_BLANK,S_BLANK};
    game game_test_default = game_new(array_default);
    
    ASSERT(check_game(array,game_test));
    ASSERT(check_game(array_solution,g_test_sol));
    ASSERT(game_equal(game_test_default,game_default()));
    return true;
}

/* ********** TEST GAME_NEW_EMPTY ********** */

bool test_game_new_empty(){
    // Création d'un jeu vide
    game game_test = game_new_empty();
    // Mon array de S_BLANK correspond à ce que devrai me renvoyé game_new_empty
    square array[DEFAULT_SIZE*DEFAULT_SIZE]= {
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK
        };
    // Cette array permet de vérifié un cas d'erreur
    square array_error[DEFAULT_SIZE*DEFAULT_SIZE]= {S_BLANK,S_BLANK,S_LIGHTBULB,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
    S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
    S_BLANK,S_BLANK,S_LIGHTBULB,S_BLANK,S_BLANK,S_BLACKU,S_BLANK,
    S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
    S_BLANK,S_BLANK,S_LIGHTBULB,S_LIGHTBULB,S_BLANK,S_BLANK,S_BLANK,
    S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
    S_BLANK,S_BLANK,S_BLACK2,S_BLANK,S_BLANK,S_BLANK,S_BLANK};
    
    ASSERT(check_game(array,game_test)); // Comparaison de mon array et du game
    ASSERT(check_game(array_error,game_test) == false);
    return true;
}

/* ********** TEST GAME_COPY ********** */

bool test_game_copy(){
    // Récupère deux game
    game game_test = game_default();
    game game_test_sol = game_default_solution();
    // Crée deux game avec game_copy
    game game_test_copy = game_copy(game_default());
    game game_test_copy_sol = game_copy(game_default_solution());

    ASSERT(game_test = game_test_copy); // Compare le jeu et sa copie 
    ASSERT(game_test_sol = game_test_copy_sol);
    return true;
}

/* ********** TEST GAME_EQUAL ********** */

bool test_game_equal(){
    // Je récupère 3 game deux identique et un différent
    game game_test1 = game_default(); 
    game game_test2 = game_default();
    game game_test3 = game_default_solution();

    ASSERT(game_equal(game_test1,game_test2)); // test si g1 = g2
    ASSERT(game_equal(game_test1,game_test3) == false); // Vérifie que game_default est bien différent de game_default_solution
    ASSERT(game_equal(game_test2,game_test3) == false);
    return true;
}

/* ********** TEST GAME_SET_SQUARE ********** */

bool test_game_set_square(){
    //Création d'un array de S_BLACK
    square array[DEFAULT_SIZE*DEFAULT_SIZE] = {
        S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,
        S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,
        S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,
        S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,
        S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,
        S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,
        S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK
        };
    //Création d'un jeu vide
    game game_test = game_new_empty();
    for (int x = 0; x < DEFAULT_SIZE; x++){
        for (int y = 0; y < DEFAULT_SIZE;y++){
            game_set_square(game_test,x,y,S_BLACK); //Modification de mon jeu en utilisant game_set_square
        }
    }
    ASSERT(check_game(array,game_test)); //test si le jeu g créer avec new_empty correspond à mon array de S_BLANK
    game_set_square(game_test,1,3,S_LIGHTBULB); //Met S_BLAK  en première pos de mon game
    //Création d'un array correspond à mon jeu modifié
    square array_two[DEFAULT_SIZE*DEFAULT_SIZE] = {
        S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,
        S_BLACK,S_BLACK,S_BLACK,S_LIGHTBULB,S_BLACK,S_BLACK,S_BLACK,
        S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,
        S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,
        S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,
        S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,
        S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK,S_BLACK
        };
    ASSERT(check_game(array_two,game_test));//Deuxième test avec S_BLACK en (0,0)

    //Modification du jeu en full S_BLACK
    for (int x = 0; x < DEFAULT_SIZE; x++){
        for (int y = 0; y < DEFAULT_SIZE;y++){
            game_set_square(game_test,x,y,S_BLANK);
        }
    }
    ASSERT(check_game(array,game_test) == false); // Compare un array de S_BLANK à un array de S_BLACK pour confirmé que set_square à bien marché
    return true;
}

/* ********** TEST GAME_GET_STATE ********** */

bool test_game_get_state(){
    //Création d'un array avec tout les squares
    square array[DEFAULT_SIZE*DEFAULT_SIZE]= {
        S_BLANK ,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,
        S_BLACKU,S_LIGHTBULB,S_MARK,S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED | F_ERROR ,S_MARK | F_LIGHTED ,S_BLANK,
        S_BLANK,S_BLANK,S_BLANK,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,
        S_BLACKU,S_LIGHTBULB,S_MARK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
        S_BLANK,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,
        S_BLACKU,S_LIGHTBULB,S_MARK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
        S_BLANK,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,
        };
    //Création du game
    game game_test = game_new(array);
    //Test si chaque square est correctement retourné
    ASSERT(game_get_state(game_test,0,0) == S_BLANK);
    ASSERT(game_get_state(game_test,0,1) == S_BLACK);
    ASSERT(game_get_state(game_test,0,2) == S_BLACK0);
    ASSERT(game_get_state(game_test,0,3) == S_BLACK1);
    ASSERT(game_get_state(game_test,0,4) == S_BLACK2);
    ASSERT(game_get_state(game_test,0,5) == S_BLACK3);
    ASSERT(game_get_state(game_test,0,6) == S_BLACK4);
    ASSERT(game_get_state(game_test,1,0) == S_BLACKU);
    ASSERT(game_get_state(game_test,1,1) == S_LIGHTBULB);
    ASSERT(game_get_state(game_test,1,2) == S_MARK);

    ASSERT(game_get_state(game_test,1,3) == S_BLANK);
    ASSERT(game_get_state(game_test,1,4) == S_LIGHTBULB);
    ASSERT(game_get_state(game_test,1,5) == S_MARK);
    return true;
}

/* ********** TEST GAME_IS_BLACK ********** */

bool test_game_is_black(){
    //Création de 2 array un avec tout les S_BLACK possibl et l'autre avec les squares not black
    square array [DEFAULT_SIZE*DEFAULT_SIZE]={
        S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,
        S_BLACK,S_BLACK,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,
        S_BLACK4,S_BLACKU,S_BLACK,S_BLACK,S_BLACK,S_BLACK0,S_BLACK1,
        S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,S_BLACK,S_BLACK,S_BLACK,
        S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,S_BLACK,
        S_BLACK,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,
        S_BLACKU,S_BLACK,S_BLACK,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK
        };

    square array_error [DEFAULT_SIZE*DEFAULT_SIZE]={
        S_BLANK,S_LIGHTBULB,S_MARK,S_MARK,S_BLANK,S_BLANK,S_BLANK,
        S_LIGHTBULB,S_BLANK,S_BLANK,S_LIGHTBULB,S_MARK,S_BLANK,S_BLANK,
        S_BLANK,S_BLANK,S_LIGHTBULB,S_BLANK,S_BLANK,S_LIGHTBULB,S_MARK,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_LIGHTBULB,S_BLANK,S_BLANK,
        S_LIGHTBULB,S_MARK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_LIGHTBULB,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_LIGHTBULB,
        S_BLANK,S_LIGHTBULB,S_MARK,S_BLANK,S_BLANK,S_BLANK,S_BLANK
        };
    
    game game_test = game_new(array);   //Création de mon jeu de S_BLACK
    game game_test_error = game_new(array_error);   //Création de mon jeu de error
    for (int x = 0; x < DEFAULT_SIZE; x++){
        for (int y = 0; y < DEFAULT_SIZE;y++){
            ASSERT(game_is_black(game_test,x,y));   //Test tout les squares de mon array et vérifie qu'ils sont black
            ASSERT( game_is_black(game_test_error,x,y) == false); //Test la fonction game_is_black avec des paramètre not black
        }
    }
    return true;
}

/* ********** TEST GAME_GET_BLACK_NUMBER ********** */

bool test_game_get_black_number(){
    //Création d'un array avec tout les S_BLACK
    square array [DEFAULT_SIZE*DEFAULT_SIZE]={
        S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,
        S_BLACK,S_BLACK,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,
        S_BLACK4,S_BLACKU,S_BLACK,S_BLACK,S_BLACK,S_BLACK0,S_BLACK1,
        S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,S_BLACK,S_BLACK,S_BLACK,
        S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,S_BLACK,
        S_BLACK,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,
        S_BLACKU,S_BLACK,S_BLACK,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK
        };
    // Création du jeu
    game game_test = game_new(array);
    /*
        Test qui vérifie que la fonction game_get_black retourne le numéro du wall
        Je ne savais pas si je devais tester get_black_number avec des square not black 
        exemple avec S_BLANK ou S_LIGHTBULB mais je ne sais pas ce que ça doit retourné
    */
    
    ASSERT(game_get_black_number(game_test,0,0) == 0);
    ASSERT(game_get_black_number(game_test,0,1) == 0);
    ASSERT(game_get_black_number(game_test,0,2) == 1);
    ASSERT(game_get_black_number(game_test,0,3) == 2);
    ASSERT(game_get_black_number(game_test,0,4) == 3);
    ASSERT(game_get_black_number(game_test,0,5) == 4);
    ASSERT(game_get_black_number(game_test,0,6) == -1);
    return true;
}

/* ********** TEST GAME_IS_MARKED********** */

bool test_game_is_marked(){
    //Création d'un array avec des S_MARK placé au hasard
    square array [DEFAULT_SIZE*DEFAULT_SIZE]={
        S_BLANK,S_LIGHTBULB,S_MARK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
        S_LIGHTBULB,S_BLANK,S_BLANK,S_LIGHTBULB,S_BLACK,S_MARK,S_BLANK,
        S_BLANK,S_BLANK,S_LIGHTBULB,S_BLANK,S_BLANK,S_LIGHTBULB,S_MARK,
        S_BLANK,S_BLANK,S_BLANK,S_MARK,S_LIGHTBULB,S_BLANK,S_BLANK,
        S_LIGHTBULB,S_MARK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_LIGHTBULB,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACK,S_BLACKU,S_MARK,
        S_BLACK,S_BLANK,S_BLACK,S_LIGHTBULB,S_MARK,S_BLACK,S_BLANK
        };
    //Création d'un array sans S_MARK mais avec tout les autres squares
    square array_error [DEFAULT_SIZE*DEFAULT_SIZE]={
        S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,
        S_BLACK,S_BLACK,S_BLANK,S_LIGHTBULB,S_BLACK,S_BLANK,S_BLANK,
        S_BLANK,S_BLANK,S_BLACK,S_BLACK,S_BLANK,S_LIGHTBULB,S_BLACK,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACK,S_BLACK,S_BLACK,
        S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,S_BLACK,
        S_BLACK,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,
        S_BLACKU,S_BLACK,S_BLACK,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK
    };
    //Création des 2 games
    game game_test = game_new(array);
    game game_test_error = game_new(array_error);
    for (int x = 0; x < DEFAULT_SIZE; x++){
        for (int y = 0; y < DEFAULT_SIZE;y++){
            ASSERT( game_is_marked(game_test_error,x,y) == false);  //Vérifie que tout les squares n'étant pas S_MARK return false
        }
    }
    // Plusieur test de S_MARK qui renvoie true 
    ASSERT(game_is_marked(game_test,0,2));
    ASSERT(game_is_marked(game_test,1,5));
    ASSERT(game_is_marked(game_test,2,6));
    ASSERT(game_is_marked(game_test,3,3));
    ASSERT(game_is_marked(game_test,4,1));
    ASSERT(game_is_marked(game_test,5,6));
    ASSERT(game_is_marked(game_test,6,4));
    return true;
}


/* ********** USAGE ********** */

void usage(int argc, char *argv[])
{
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

/* ********** MAIN ROUTINE ********** */

int main(int argc, char *argv[])
{
    if (argc == 1)
        usage(argc, argv);
    fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
    bool ok = false;

    if (strcmp("game_new", argv[1]) == 0)
        ok = test_game_new();
    else if (strcmp("game_new_empty", argv[1]) == 0)
        ok = test_game_new_empty();
    else if (strcmp("game_copy", argv[1]) == 0)
        ok = test_game_copy();
    else if (strcmp("game_equal", argv[1]) == 0)
        ok = test_game_equal();
    else if (strcmp("game_set_square", argv[1]) == 0)
        ok = test_game_set_square(); 
        else if (strcmp("game_get_state", argv[1]) == 0)
        ok = test_game_get_state(); 
    else if (strcmp("game_is_black", argv[1]) == 0)
        ok = test_game_is_black(); 
    else if (strcmp("game_get_black_number", argv[1]) == 0)
        ok = test_game_get_black_number(); 
    else if (strcmp("game_is_marked", argv[1]) == 0)
        ok = test_game_is_marked(); 

    else
    {
        fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if (ok)
    {
        fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
        return EXIT_SUCCESS;
    }
    else
    {
        fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
        return EXIT_FAILURE;
    }
}
