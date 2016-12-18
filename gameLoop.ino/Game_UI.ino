#include "object.h"
#include "data.h"
#include "accel.h"

int gameWindow = 0;
const int welcomeWindow = 0; //uses startO + car + tree + rock objects 
const int menuWindow = 1; //uses menuO object
const int difficultyWindow = 2; //uses difficulty bitmap
const int playGameWindow = 3;
const int tutorial1Window = 4;
const int tutorial2Window = 5;
const int calibrationWindow = 6;
const int gameOverWindow = 7;
int flag = 0;
int tilting;
//-------menu && difficulty windows: variables && functions------//
int menuOption = 0;

const int maxDiffOption = 3;
const int easy = 2;
const int hard = 3;
int difficulty = 2;

const int playOption = 0;
const int difficultyOption = 1;
const int maxMenuOption = 1;//number of menu options in menuWindow

void moveTriangle(int option){
  switch (option){
    case playOption:
      OrbitOledClearBuffer();
      objectPrint(menuO,0,0);
      objectPrint(triangleO,5,7);
      OrbitOledUpdate();
      break;
    case difficultyOption:
      OrbitOledClearBuffer();
      objectPrint(menuO,0,0);
      objectPrint(triangleO,5,17);
      OrbitOledUpdate();
      break;
    case easy:
      OrbitOledClearBuffer();
      objectPrint(difficultyO,0,0);
      objectPrint(triangleO,0,18);
      OrbitOledUpdate();
      break;
    case hard:
      OrbitOledClearBuffer();
      objectPrint(difficultyO,0,0);
      objectPrint(triangleO,83,18);
      OrbitOledUpdate();
      break;
  }
}
//-----------------------------------------------//
//---------------playGameWindow functions && variables --------//
uint32_t score = 0;
int carLocation  = 2;
int carXLocs[] = {9,34,59,84,109};
int carYLoc = 23;
int treeXLocs[] = {9,34,59,84,109};
int rockXLocs[] = {7,32,57,82,107};
int spacing = 13;
int treeLocs[][2] = {{random(5),-11*spacing},{random(5),-10*spacing},{random(5),-5*spacing},{random(5),-3*spacing},{random(5),-2*spacing},{random(5),0}};
int rockLocs[][2] = {{random(5),-9*spacing},{random(5),-7*spacing},{random(5),-6*spacing},{random(5),-4*spacing},{random(5),-1*spacing},{random(5),8*spacing}};
int resetDiff = 12*spacing;
int initTreeLocs[] = {-99,-90,-45,-27,-18,0};
int initRockLocs[] = {-81,-63,-54,-36,-9,72};
int collision(struct object *o, int x1, int y1, struct object *q,int x2, int y2){
  if(x1 != x2){
    return 0;
  }
  if(y1+ o->height < y2){
    return 0;
  }
  if(y2 + q->height < y1){
    return 0;
  }
  return 1;
}
void resetGame(){
  score = 0;
  carLocation  = 2;
  carYLoc = 23;
  gameSpeed = 40000;
  for(int j = 0; j<5;j++){
    treeLocs[j][1] = initTreeLocs[j];
    rockLocs[j][1] = initRockLocs[j];
  }
  i = 0;
  when = random(5000,10000);
}
void animateExplosion(int n,int x, int y){
  
    objectPrint(explosions[n],x,(10-explosions[n]->height)/2+y);
    
}
int animationCount = 0;
//-------------------------------------------------------------//
void GameUIInit()
{
  OrbitOledInit();
  OrbitOledClear();
  OrbitOledClearBuffer();
  OrbitOledSetFillPattern(OrbitOledGetStdPattern(iptnSolid));
  OrbitOledSetDrawMode(modOledSet);
}

void gameLoop(){
  switch(gameWindow){
    case welcomeWindow://-----------------//
      if(!flag){
        OrbitOledClearBuffer();
        objectPrint(startO,0,0);
        objectPrint(car, 55,20);
        objectPrint(tree, 20,20);
        objectPrint(rock, 90, 20);
        OrbitOledUpdate();
        flag = 1;
      }
      
     
      if(b_press(b1) || b_press(b2)){
        OrbitOledClear();
        gameWindow = menuWindow;
        flag = 0;
      }
      break;
    case menuWindow://-------------------//
      if(!flag){
        menuOption = 0;
        objectPrint(menuO,0,0);
        objectPrint(triangleO,5,7);
        OrbitOledUpdate();
        flag = 1;
      }
      if(b_presst(up)){
        menuOption--;
        if(menuOption < 0)menuOption = maxMenuOption;
        moveTriangle(menuOption);
      }
      if(b_presst(down)){
        menuOption++;
        if(menuOption > maxMenuOption)menuOption = 0;
        moveTriangle(menuOption);
      }
      if(b_press(b2)||b_press(b1)){
        switch(menuOption){
          case playOption://===========//
            OrbitOledClear();
            gameWindow = tutorial1Window;
            flag = 0;
            break;
          case difficultyOption://=====//
            OrbitOledClear();
            gameWindow = difficultyWindow;
            flag = 0;
            break;
        }
      }
      break;
    case difficultyWindow://----------------//
      if(!flag){
        menuOption = 2;
        objectPrint(difficultyO,0,0);
        objectPrint(triangleO,0,18);
        OrbitOledUpdate();
        flag = 1;
      }
      if(b_presst(up)){
        menuOption--;
        if(menuOption < 2)menuOption = maxDiffOption;
        moveTriangle(menuOption);
      }
      if(b_presst(down)){
        menuOption++;
        if(menuOption > maxDiffOption)menuOption = 2;
        moveTriangle(menuOption);
      }
      if(b_press(b2)||b_press(b1)){
        difficulty = menuOption;
        switch(menuOption){
          case easy://===========//
            difficulty = easy;
            OrbitOledClear();
            gameWindow = menuWindow;
            flag = 0;
            break;
          case hard://=====//
            difficulty = hard;
            OrbitOledClear();
            gameWindow = menuWindow;
            flag = 0;
            break;
        }
      }
      break;
    case tutorial1Window://----------------------//
      if(!flag){
        objectPrint(tutorial1O,0,0);
        OrbitOledUpdate();
        flag = 1;
      }
      if(b_press(b1) || b_press(b2)){
        OrbitOledClear();
        gameWindow = tutorial2Window;
        flag = 0;
      }
      break; 
      case tutorial2Window://----------------------//
      if(!flag){
        objectPrint(tutorial2O,0,0);
        OrbitOledUpdate();
        flag = 1;
      }
      if(b_press(b1) || b_press(b2)){
        OrbitOledClear();
        gameWindow = playGameWindow;
        flag = 0;
      }
      break;
      /*case calibrationWindow://----------------------//
      if(!flag){
        objectPrint(calibrationO,0,0);
        OrbitOledUpdate();
        flag = 1;
      }
      if(b_press(b1) || b_press(b2)){
        OrbitOledClear();
        gameWindow = playGameWindow;
        flag = 0;
        counter =0;
      }
      break;   */
      case playGameWindow://---------------------------//
      if(!flag){
        gameSpeed = 40000*2/difficulty;
        flag = 1;
      }
      i++;
      getData();
      if(i==1){
         when = random(5000,10000);
         Serial.println(when);
      }
      if (shake_f()){
        
      }else {
      counter++;
      
      OrbitOledClearBuffer();
      objectPrint(car, carXLocs[carLocation], carYLoc);
      if(i%100==0){
        score++;
      }
      for(int j= 0; j<5;j++){
        if(treeLocs[j][1] >= 0){
          objectPrint(tree, treeXLocs[treeLocs[j][0]], treeLocs[j][1]);
        }
        if(rockLocs[j][1] >= 0){
          objectPrint(rock, rockXLocs[rockLocs[j][0]], rockLocs[j][1]);
        }
      }
      OrbitOledUpdate();
      tilting =tilt();
      //Serial.println(tilting);
      if(tilting == 2){//go left
        if(carLocation>0){
          carLocation--;
        }
        
      }
      else if(tilting ==3){//go right
        if(carLocation<4){
          carLocation++;
        }
      }
      if(counter >= gameSpeed/1000){
        for(int j= 0; j<5;j++){
          treeLocs[j][1]++;
          rockLocs[j][1]++;
          if(treeLocs[j][1] >= 32){
            treeLocs[j][1]-=resetDiff;
            treeLocs[j][0] = random(5);
            rockLocs[j][1]-=resetDiff;
            rockLocs[j][0] = random(5);
          }
          counter = 0;
        }
      }
      for(int j =0;j<5;j++){
        if(collision(car,carLocation,carYLoc,tree,treeLocs[j][0],treeLocs[j][1])||collision(car,carLocation,carYLoc,rock,rockLocs[j][0],rockLocs[j][1])){
          for(int k = 0; k<explosionsSize;k++){
            OrbitOledClearBuffer();
            animateExplosion(k,carXLocs[carLocation],carYLoc);
            OrbitOledUpdate();
            delay(50);
          }
          
          OrbitOledClear();
          checkScore(score);
          gameWindow = gameOverWindow;
          flag = 0;
        }
      }
      }
      break;
      case gameOverWindow://----------------------------------------------------//
      if(!flag){
        OrbitOledClearBuffer();
        objectPrint(gameOverO,0,0);
        printScore(score, 43,21);
        printScore(highscore,104,21);
        OrbitOledUpdate();
        flag = 1;
      }
      if(b_press(b1) || b_press(b2)){
        OrbitOledClear();
        gameWindow = menuWindow;
        resetGame();
        flag = 0;
      }
      break;
  }
  
}

