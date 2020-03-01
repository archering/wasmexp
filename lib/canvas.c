#include <stdio.h>
#include <emscripten.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CIRCLES 60

//c struct data 
struct Circle {
    int x;  // coodirnate x
    int y;  // coodirnate y 
    int r;  // radious
    int cr;  //color red 
    int cb;  // color blur 
    int cg;   // color green
};

// animate data
struct Animate {
    int x;  // coodirnate x
    int y;  // coodirnate y 
    int r;  // radious
    int xv;  // x 移动的步长
    int yv; // y 移动的步长
    int xd; // x 移动的方向  1 向左， 0 向右 
    int yd; // y 移动的方向  1 向下， 0 向上
};

//define a typed array for store Circle
struct Circle circles[NUM_CIRCLES]; 

// define a typed array for animate data
struct Animate animates[NUM_CIRCLES];

int getRand(int MAX){
    return (rand() % MAX);// 使用 stdlib.h 的函数
}

int main() {
    printf("wasm has loaded");

    //为了让 rand 能运行，需要 有一个seed 随机数，
    srand(time(NULL));

    // loop generate circle data and store it
    for (int i = 0; i<NUM_CIRCLES; i++){

        //随机获得一个circle 的 半径
        int radious = getRand(50);        
        //x 坐标    canvas 画布的 宽度是 600
        int x = getRand(600) + radious;
        //y 坐标   canvas 画布的 宽度是 800
        int y = getRand(300) + radious;

        //animate 数据
        animates[i].x = x;
        animates[i].y = y;
        animates[i].r = radious;
        animates[i].xv = getRand(10);
        animates[i].yv = getRand(10);
        animates[i].xd = 1;
        animates[i].yd = 1;   

        //存在数组里
        circles[i].x = x;
        circles[i].y = y;
        circles[i].r = radious;
        circles[i].cr = getRand(255);
        circles[i].cb = getRand(255);
        circles[i].cg = getRand(255);
    }

    //  没办法给 js 函数传递参数
    // emscripten_run_script("render()");

    // 可以传递参数
    EM_ASM({ render($0);  }, NUM_CIRCLES * 6);
}

//typed array
struct Circle * getCircles(int canvasWidth, int canvasHeight){

    for(int i =0 ;i<NUM_CIRCLES;i++){

        if( (animates[i].x + animates[i].r) >= 1200) {
            animates[i].xd = 0;
        }
        if( (animates[i].x - animates[i].r) <= 0) {
            animates[i].xd = 1;
        }  

         if( (animates[i].y + animates[i].r) >= 600) {
            animates[i].xd = 0;
        }
        if( (animates[i].y - animates[i].r) <= 0) {
            animates[i].xd = 1;
        }     

        // 根据 方向，重新计算坐标位置
        if(animates[i].xd == 1) {
            animates[i].x = animates[i].x + animates[i].xv;
        } else {
            animates[i].x = animates[i].x - animates[i].xv;
        }   

        if(animates[i].yd == 1) {
            animates[i].y = animates[i].y + animates[i].yv;
        }else {
            animates[i].y = animates[i].y - animates[i].yv;
        }    

        circles[i].x = animates[i].x;
        circles[i].y = animates[i].y;          

    }


    return circles;
}