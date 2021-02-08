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
/* 格子世界の外 */
#ifndef OUTSIDE
#define OUTSIDE -10
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
 * 参照したい配列の添字が有効ならその添字を、無効なら最後の添字を返す
 */
int get_index(int i, int j){
  if(i<0 || i>WORLD_SIZE || j<0 || j>WORLD_SIZE) return WORLD_SIZE*WORLD_SIZE;
  return WORLD_SIZE*i + j;
}

/*
 * そのグリッドを埋めるか判断する
 */
int fillGrid(int *grid, int i, int j){
  if(*(grid+get_index(i,j)) != 0) return 1;
  // パターン分けによってグリッドを埋めるか決定する
  int p1=0, p2=0, p3=0, p4=0, total=0;
  if(*(grid + get_index(i-1,j)) == -1){p1++; p2++; total++;}
  if(*(grid + get_index(i,j+1)) == -1){p1++; p4++; total++;}
  if(*(grid + get_index(i,j-1)) == -1){p2++; p3++; total++;}
  if(*(grid + get_index(i+1,j)) == -1){p3++; p4++; total++;}
  if((total >= 3) ||
     (p1==2 && *(grid+get_index(i+1,j-1)) != -1) ||
     (p2==2 && *(grid+get_index(i+1,j+1)) != -1) ||
     (p3==2 && *(grid+get_index(i-1,j+1)) != -1) ||
     (p4==2 && *(grid+get_index(i-1,j-1)) != -1)){
       *(grid+get_index(i,j)) = -1;
       // そのグリッドが変化下なら、再帰的に周りのグリッドも埋めるか判断する
       fillGrid(grid, i+1, j);
       fillGrid(grid, i-1, j);
       fillGrid(grid, i, j+1);
       fillGrid(grid, i, j-1);
      return 0;
  }
  return 1;
}

/*
 * すべてのグリッドに fillGrid を適用させる
 */
int buryDeadend(int *battlefield){
  int i, j;
  for(i=0; i<WORLD_SIZE; i++){
    for(j=0; j<WORLD_SIZE; j++){
      fillGrid(battlefield, i, j);
    }
  }
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
int printWorld(int *battlefield, int message){
  if(message == ORIGINAL){
    printf("Original Map\n");
  }else if(message == BRUIED){
    printf("Dead ends buried\n");
  }

  int i, j;
  for(i=0; i<WORLD_SIZE; i++){
    for(j=0; j<WORLD_SIZE; j++){
      switch(*(battlefield+WORLD_SIZE*i+j)){
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
          fprintf(stderr, "%d\n", *(battlefield+WORLD_SIZE*i+j));
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

/*
 * 格子世界をコピーする
 */
int copyWorld(int *battlefield, int *buriedWorld){
  int i, j;
  for(i=0; i<WORLD_SIZE; i++){
    for(j=0; j<WORLD_SIZE; j++){
      *(buriedWorld+WORLD_SIZE*i+j) = *(battlefield+WORLD_SIZE*i+j);
    }
  }
  *(buriedWorld+WORLD_SIZE*WORLD_SIZE+1) = OUTSIDE;
  return 0;
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
  printWorld((int *)battlefield, ORIGINAL);

  // 変換した格子世界を格納する配列
  // 本来の配列より1大きいのが重要
  int buriedWorld[WORLD_SIZE*WORLD_SIZE+1];
  // 上の配列に格子世界をコピーする
  copyWorld((int *)battlefield, buriedWorld);

  buryDeadend(buriedWorld);

  // 最終的な出力
  printWorld(buriedWorld, BRUIED);

  return(0);
}