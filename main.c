#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int mat_x = 0;
int mat_y = 0;
int mat_z = 0;

char *fichier_nom = NULL;
FILE *fichier_stream = NULL;
char *fichier_string = NULL;

float*** matrice = NULL;

void netoyage() {

  if (matrice) {
    for (int z = 0; z < mat_z; z++) {
      for (int x = 0; x < mat_x; x++) {
        free(matrice[z][x]);
      }
      free(matrice[z]);
    }
  free(matrice);
  }

  if (fichier_nom) {
    free(fichier_nom);
  }

  if (fichier_stream) {
    fclose(fichier_stream);
  }

  if (fichier_string) {
    free(fichier_string);
  }

}

int main(int argc, char* argv[]) {

  //
  // arguments
  //
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-x") == 0) {
      i++;
      mat_x = atoi(argv[i]);
    } else if (strcmp(argv[i], "-y") == 0) {
      i++;
      mat_y = atoi(argv[i]);
    } else if (strcmp(argv[i], "-z") == 0) {
      i++;
      mat_z = atoi(argv[i]);
    } else if (strcmp(argv[i], "-f") == 0) {
      i++;
      fichier_nom = malloc(strlen(argv[i]) * sizeof(char) + 1);
      strcpy(fichier_nom, argv[i]);
    }
  }

  printf("demare avec \n-x %i \n-y %i \n-z %i \n-f %s\n",
    mat_x, mat_y, mat_z, fichier_nom);

  //
  // ouverture fichier
  //
  fichier_stream = fopen(fichier_nom, "r");
  fseek(fichier_stream, 0, SEEK_END);
  long fichier_bytes = ftell(fichier_stream);
  fseek(fichier_stream, 0, SEEK_SET);
  fichier_string = malloc(sizeof(char) * fichier_bytes + 1);
  long lu = fread(fichier_string, sizeof(char), fichier_bytes, fichier_stream);

  if (lu != fichier_bytes) {
    fprintf(stderr, "erreur, aurai du lire %i bytes, n'en ai eu que %i\n",
                                                            fichier_bytes, lu);
    netoyage();
    exit(1);
  }

  //
  // création de la matrice 3x
  //
  matrice = malloc(sizeof(void*) * mat_z);
  for (int z = 0; z < mat_z; z++) {
    matrice[z] = malloc(sizeof(void*) * mat_x);
    for (int x = 0; x < mat_x; x++) {
      matrice[z][x] = malloc(sizeof(float) * mat_y);
      for (int y = 0; y < mat_y; y++) {
        matrice[z][x][y] = 0.0f;
      }
    }
  }

  netoyage();

  return 0;
}
