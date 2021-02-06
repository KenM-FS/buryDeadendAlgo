#include <stdio.h>
#include <string.h>

/* 格子世界のサイズ */
#ifndef WORLD_SIZE
#define WORLD_SIZE 8
#endif

#ifndef PREDATOR
#define PREDATOR 1
#endif

#ifndef PREY
#define PREY 10
#endif

#ifndef OBSTACLE
#define OBSTACLE -1
#endif

#ifndef FREE
#define FREE 0
#endif

#ifndef ORIGINAL
#define ORIGINAL 0
#endif

#ifndef BRUIED
#define BRUIED 1
#endif

/* 
 * 格子世界を読み込む関数 
 * 講義で配布されたものを使用
 */
int readBattlefield(int battlefield[WORLD_SIZE][WORLD_SIZE], char *filename){
  FILE *fp;
  int i, j;

  fp = fopen(filename, "r");
  if(fp == NULL){
    return(1)
  }else{
    for(i=0; i<WORLD_SIZE; i++){
      for(j=0; j<WORLD_SIZE; j++){
        if(EOF == fscanf(fp, "%d", &battlefield[i][j])){
          return(1);
        }
      }
    }
    fclose(fp);
    return(0);
  }
}

int printWorld(int battlefield[WORLD_SIZE][WORLD_SIZE], int message){
  if(message == ORIGINAL)}
    printf("Original Map\n");
  }else if(message == BRUIED){
    printf("Dead ends buried\n")
  }

  int i, j;
  for(i=0; i<WORLD_SIZE; i++){
    for(j=0; j<WORLD_SIZE; j++){
      switch(battlefield[i][j]){
        case FREE:
          printf(".");
          break;
        case OBSTACLE:
          printf("#");
          break;
        case PREDATOR:
          printf("@");
          break;
        case PREY:
          printf("*");
          break;
        default:
          fprintf(stderr, "%d\n", battlefield[i][j]);
          printff(stderr, "Ececution Error! \n");
          return(1);
          break;
      }
    }
    printf("\n");
  }
  printf("\n");
  return(0);
}

int main(int argc, char *argv[]){
  int battlefield[WORLD_SIZE][WORLD_SIZE];
  char filename[256];
  strcpy(filename, "battlefield.dat");
  if(argc == 1){
    strncpy(filename, argv[1], 256)
  }

  if(readBattlefield(battlefield, filename) == 1){
    fprintf(stderr, "File read failed\n");
    return(1);
  }

  printWorld(battlefield, ORIGINAL);
  
  return(0);
}