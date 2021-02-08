#include <stdio.h>
#include <string.h>

/* 格子世界のサイズ */
#ifndef WORLD_SIZE
#define WORLD_SIZE 8
#endif
/* 捕食者の数値表現 */
#ifndef PREDATOR
#define PREDATOR 1
#endif
/* 獲物の数値表現 */
#ifndef PREY
#define PREY 10
#endif
/* 障害物の数値表現 */
#ifndef OBSTACLE
#define OBSTACLE -1
#endif
/* 自由格子の数値表現 */
#ifndef FREE
#define FREE 0
#endif

/* オリジナルのマップ */
#ifndef ORIGINAL
#define ORIGINAL 0
#endif
/* 加工したマップ */
#ifndef BRUIED
#define BRUIED 1
#endif

/*======ここから本題============================================================*/
/*
 * 参照したい配列の添字が有効か判断する
 */
int index(int i, int j){
  if(i<0 || i>WORLD_SIZE || j<0 || j>WORLD_SIZE) return WORLD_SIZE*WORLD_SIZE;
  return WORLD_SIZE*i + j;
}

/*======ここから本題とは関係ない部分===============================================*/
/* 
 * 格子世界を読み込む関数 
 */
int readBattlefield(int battlefield[WORLD_SIZE][WORLD_SIZE], char *filename){
  FILE *fp;
  int i, j;

  fp = fopen(filename, "r");
  if(fp == NULL){
    return(1);
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
/*
 * 格子世界を出力する関数
 */
int printWorld(int battlefield[WORLD_SIZE][WORLD_SIZE], int message){
  if(message == ORIGINAL){
    printf("Original Map\n");
  }else if(message == BRUIED){
    printf("Dead ends buried\n");
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
          fprintf(stderr, "Ececution Error! \n");
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
  // コマンドライン引数で読み込むファイルを変更できるように
  int battlefield[WORLD_SIZE][WORLD_SIZE];
  char filename[256];
  strcpy(filename, "battlefield.dat");
  if(argc == 2){
    strncpy(filename, argv[1], 256);
  }

  // ファイルから格子世界の読み込み
  if(readBattlefield(battlefield, filename) == 1){
    fprintf(stderr, "File read failed\n");
    return(1);
  }

  // 初期状態の格子世界を出力
  printWorld(battlefield, ORIGINAL);

  return(0);
}