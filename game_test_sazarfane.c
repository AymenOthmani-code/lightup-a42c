#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "game_aux.h"
#include "game_test_commun.c"

/* ********** TEST game_new ********** */

bool test_game_new(){
    square array_default[DEFAULT_SIZE*DEFAULT_SIZE]= {
        S_BLANK,S_BLANK,S_BLACK1,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
        S_BLANK,S_BLANK,S_BLACK2,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACKU,S_BLACK2,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
        S_BLACK1,S_BLACKU,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACK2,S_BLANK,S_BLANK,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACKU,S_BLANK,S_BLANK
        };
    game game_test = game_new(array_default);

    square array_solution[DEFAULT_SIZE*DEFAULT_SIZE]= {S_LIGHTBULB | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLACK1,S_LIGHTBULB | F_LIGHTED, S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,
    S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED,S_BLACK2,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED,
    S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLACKU,S_BLACK2,
    S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED,
    S_BLACK1,S_BLACKU,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,
    S_LIGHTBULB | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLACK2,S_LIGHTBULB | F_LIGHTED,S_BLANK | F_LIGHTED,
    S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLACKU,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED};
    game game_test_sol = game_new(array_solution);

    square *array_all_values=create_array_all_values();
    game game_all_values = game_new (array_all_values);
    ASSERT(check_game(array_default,game_test));
    ASSERT(check_game(array_solution,game_test_sol));
    ASSERT(game_equal(game_test,game_default()));
    ASSERT(check_game(array_all_values,game_all_values));
    free(array_all_values);
    return true;
}

/* ********** TEST GAME_NEW_EMPTY ********** */

bool test_game_new_empty(){
    // Création d'un jeu vide
    game game_test = game_new_empty();
    // Mon array de S_BLANK correspond à ce que devrai me renvoyé game_new_empty
    square array_blank[DEFAULT_SIZE*DEFAULT_SIZE]= {
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
    
    ASSERT(check_game(array_blank,game_test)); // Comparaison de mon array et du game
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
    //Création d'un jeu vide
    game game_test = game_new_empty();
    //Récupération array_all_values
    square *array_all_values=create_array_all_values();
    //Remplir de game_test avec les valeurs de array_all_values
    for (int y = 0; y < DEFAULT_SIZE; y++){
        for (int x = 0; x < DEFAULT_SIZE;x++){
            for (int z = 0; z < 20;z++){
            game_set_square(game_test,x,y,array_all_values[z]);
            ASSERT(game_get_square(game_test,x,y) == array_all_values[z]); 
            }
        }
    }
    free(array_all_values);
    return true;
}

/* ********** TEST GAME_GET_STATE ********** */

bool test_game_get_state(){
    //Création d'un array avec tout les squares
    square array_with_all[DEFAULT_SIZE*DEFAULT_SIZE]= {
        S_BLANK ,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,
        S_BLACKU,S_LIGHTBULB,S_MARK,S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED | F_ERROR ,S_MARK | F_LIGHTED ,S_BLANK,
        S_BLACK0 | F_ERROR,S_BLACK1 | F_ERROR,S_BLACK2 | F_ERROR,S_BLACK3 | F_ERROR,S_BLACK4 | F_ERROR,S_BLACK | F_ERROR,S_BLACKU,
        S_BLACKU,S_LIGHTBULB,S_MARK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
        S_BLANK,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,
        S_BLACKU,S_LIGHTBULB,S_MARK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
        S_BLANK,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,
        };
    //Création du game
    game game_test = game_new(array_with_all);
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
    
    ASSERT(game_get_state(game_test,2,0) == S_BLACK0);
    ASSERT(game_get_state(game_test,2,1) == S_BLACK1);
    ASSERT(game_get_state(game_test,2,2) == S_BLACK2);
    ASSERT(game_get_state(game_test,2,3) == S_BLACK3);
    ASSERT(game_get_state(game_test,2,4) == S_BLACK4);
    ASSERT(game_get_state(game_test,2,5) == S_BLACK);
    return true;
}

/* ********** TEST GAME_IS_BLACK ********** */

bool test_game_is_black(){
    //Création de 2 array un avec tout les S_BLACK possibl et l'autre avec les squares not black
    square array_valid[14]={
        S_BLACK | F_ERROR,S_BLACK0 | F_ERROR,S_BLACK1 | F_ERROR,S_BLACK2 | F_ERROR,S_BLACK3 | F_ERROR,S_BLACK4 | F_ERROR,S_BLACKU | F_ERROR, 
        S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,
        };

    square array_invalid[6]={
        S_BLANK, S_LIGHTBULB, S_MARK, S_BLANK | F_LIGHTED, S_LIGHTBULB | F_LIGHTED | F_ERROR ,S_MARK | F_LIGHTED
        };

    game game_test = game_new_empty();
    
    for (int x = 0; x < DEFAULT_SIZE; x++){
        for (int y = 0; y < DEFAULT_SIZE;y++){
            for (int i = 0; i<6;i++){
                game_set_square(game_test,x,y,array_invalid[i]);
                ASSERT(!game_is_black(game_test,x,y));
            }
            for (int j = 0; j<14;j++){
                game_set_square(game_test,x,y,array_valid[j]);
                ASSERT(game_is_black(game_test,x,y)); 
            }
        }
    }
    return true;
}

/* ********** TEST GAME_GET_BLACK_NUMBER ********** */

bool test_game_get_black_number(){
    //Création d'un array avec tout les S_BLACK
    square array_black_number[DEFAULT_SIZE*DEFAULT_SIZE]={
        S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,
        S_BLACK,S_BLACK,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,
        S_BLACK4,S_BLACKU,S_BLACK,S_BLACK,S_BLACK,S_BLACK0,S_BLACK1,
        S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,S_BLACK,S_BLACK,S_BLACK,
        S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,S_BLACK,
        S_BLACK,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,
        S_BLACKU,S_BLACK,S_BLACK,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK
        };
    // Création du jeu
    game game_test = game_new(array_black_number);
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
    square array_valid[2]={
        S_MARK, S_MARK | F_LIGHTED
    };
    //Création d'un array sans S_MARK mais avec tout les autres squares
    square array_invalid[18]={
        S_BLANK ,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,
        S_BLACKU,S_LIGHTBULB,S_BLANK | F_LIGHTED,
        S_LIGHTBULB | F_LIGHTED | F_ERROR ,S_BLANK,S_BLACK0 | F_ERROR,S_BLACK1 | F_ERROR,S_BLACK2 | F_ERROR,S_BLACK3 | F_ERROR,S_BLACK4 | F_ERROR,S_BLACK | F_ERROR
    };
    //Création des 2 games
    game game_test = game_new_empty();
    
    for (int x = 0; x < DEFAULT_SIZE; x++){
        for (int y = 0; y < DEFAULT_SIZE;y++){
            for (int i = 0; i<18;i++){
                game_set_square(game_test,x,y,array_invalid[i]);
                ASSERT(!game_is_marked(game_test,x,y));
            }
            for (int j = 0; j<2;j++){
                game_set_square(game_test,x,y,array_valid[j]);
                ASSERT(game_is_marked(game_test,x,y)); 
            }
        }
    }
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
