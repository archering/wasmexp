#include <emscripten.h>
#include <stdio.h>


EM_JS(void,jsMain,(int n), {

    console.log("number is ",n);

});

int main(){

    printf("WASM IS ready! \n");

    emscripten_run_script(" console.log('hello from c! powered by emscripten'); ");

    emscripten_async_run_script(" alert('hello from async  C ') ",1500);

    int jsVal = emscripten_run_script_int("getNum()");

    printf("i just got a number from js getNum: %d\n",jsVal);

     char *  name = emscripten_run_script_string("yourname()");

     printf("i just know your name is : %s\n",name);

     jsMain(2900);

    return 1;

}