/*

This file contains the (desired) sync version of viewstamped.jumps.c

*/

INIT(){
    int view = 0;
    int vround = STARTVIEWCHANGE;
    int opnumber = 0;
    int nround = PREPARE;
}

VIEWCHANGE(){
}

NORMALOP(){

    PREPARE{
        SEND(){
            ...
        }

        UPDATE(mbox){
            ...
            if(jump_viewchange(mbox)){
                VIEWCHANGE();
            }
        }
    }

    PREPAREOK{
        SEND(){
            ...
        }

        UPDATE(mbox){
            ...
            if(jump_viewchange(mbox)){
                VIEWCHANGE();
            }
        }
    }


}