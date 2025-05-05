#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

int __mat_x = 0;
int __mat_y = 0;
int __mat_z = 0;
char *__fichier_nom = NULL;
FILE *__fichier_stream = NULL;
char *__fichier_string = NULL;
float ***__matrice = NULL;

void nettoyage()
{
  if (__matrice) {
    for (int z = 0; z < __mat_z; z++) {
      for (int x = 0; x < __mat_x; x++) {
        free(__matrice[z][x]);
      }
      free(__matrice[z]);
    }
    free(__matrice);
  }

  if (__fichier_nom) free(__fichier_nom);
  if (__fichier_stream) fclose(__fichier_stream);
  if (__fichier_string) free(__fichier_string);
}

void nettoyage_et_quite(int status)
{
  nettoyage();
  exit(status);
}

int main(int argc, char* argv[])
{

  //
  // arguments
  //
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-h") == 0) {
      printf("usage: monapp -z NOMBRE_DE_COUCHES -f NOM_FICHIER\n");
      nettoyage_et_quite(0);
    } else if (strcmp(argv[i], "-z") == 0) {
      i++;
      __mat_z = atoi(argv[i]);
    } else if (strcmp(argv[i], "-f") == 0) {
      i++;
      __fichier_nom = strdup(argv[i]);
    }
  }

  if (__fichier_nom == NULL) {
    fprintf(stderr, "il manque le nom de fichier (-f)");
    nettoyage_et_quite(1);
  }

  printf("on demare avec z=%i et fichier %s\n", __mat_z, __fichier_nom);

  //
  // chargement du fichier
  //
  __fichier_stream = fopen(__fichier_nom, "r");
  fseek(__fichier_stream, 0, SEEK_END);
  long fichier_taille = ftell(__fichier_stream);
  fseek(__fichier_stream, 0, SEEK_SET);
  __fichier_string = malloc(sizeof(char) * fichier_taille + 1);
  long lu = fread(__fichier_string, sizeof(char), fichier_taille, __fichier_stream);

  if (lu != fichier_taille) {
    fprintf(stderr, "erreur, aurai du lire %i bytes, n'en ai eu que %i\n",
      fichier_taille, lu);
    nettoyage_et_quite(1);
  }

  //
  // on determine les x sur la première ligne
  //
  int line_size = strcspn(__fichier_string, "\n");
  __mat_x = 1;
  for (int i = 0; i < line_size; i++) {
    if (__fichier_string[i] == ',') {
      __mat_x++;
    }
  }

  if (__mat_x == 0) {
    fprintf(stderr, "mat x est zero\n");
    nettoyage_et_quite(1);
  }

  //
  // on determine les y en comptant les newlines
  //
  __mat_y = 0;
  for (int i = 0; i < fichier_taille; i++) {
    if (__fichier_string[i] == '\n') {
      __mat_y++;
    }
  }

  if (__mat_y == 0) {
    fprintf(stderr, "mat y est zero\n");
    nettoyage_et_quite(1);
  }

  //
  // création de la __matrice 3x
  //
  __matrice = malloc(sizeof(void*) * __mat_z);
  for (int z = 0; z < __mat_z; z++) {
    __matrice[z] = malloc(sizeof(void*) * __mat_y);
    for (int y = 0; y < __mat_y; y++) {
      __matrice[z][y] = malloc(sizeof(float) * __mat_x);
      for (int x = 0; x < __mat_x; x++) {
        __matrice[z][y][x] = 0.0f;
      }
    }
  }

  //
  // initialization de la première couche
  //
  char *save_a, *save_b;
  char *tok_row = __fichier_string;
  for (int y = 0; y < __mat_y; y++) {
    char *tok_cell  = strtok_r(tok_row, "\n",&save_a); tok_row = NULL;
    for (int x = 0; x < __mat_x; x++) {
      char *cell = strtok_r(tok_cell, ",", &save_b); tok_cell = NULL;
      __matrice[0][y][x] = atol(cell);
    }
  }

  //
  // print premiere couche
  //
  for (int y = 0; y < __mat_y; y++) {
    for (int x = 0; x < __mat_x; x++) {
      printf("%f   ", __matrice[0][y][x]);
    }
    printf("\n");
  }

  //
  // Ici on itère et on mouline
  //
  for (int z = 0; z < __mat_z; z++) {
    for (int y = 0; y < __mat_y; y++) {
      for (int x = 0; x < __mat_x; x++) {
        // LA LOGIQUE VIENT ICI
        // LA LOGIQUE VIENT ICI
        // LA LOGIQUE VIENT ICI
        // LA LOGIQUE VIENT ICI
        __matrice[z][y][x] += 1.0f;
        // LA LOGIQUE VIENT ICI
        // LA LOGIQUE VIENT ICI
        // LA LOGIQUE VIENT ICI
        // LA LOGIQUE VIENT ICI
      }
    }
  }

  //
  // fin du programme
  //

  nettoyage();
  return 0;
}
