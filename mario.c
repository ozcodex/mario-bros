#include<stdio.h>
#include<stdlib.h>
#include<allegro.h>

#define pack_spr "images/sprites32.bmp" /*Aqui se puede definir q pack de sprites usar*/
//#define pack_spr "images/originales32.bmp"
#define tam_spr 32 /*Aqui se define el tamaño de los sprites*/

//Funcion que retorna la cantidad de \n para cada nivel
int select(int x);
//Esta Funcion carga el archivo en mat
void rellenar(FILE *arch, int d,char mat[][212]);
//Funcion que copia mat en mat2 donde a es la primera poscicion de la matriz
void inimat2(char mat2[][16],char mat[][212],int a);
//funcion que imprime mat2
void print_mat(char mat2[][16],BITMAP *buffer);
//funcion que imprime el menu y retorna el nivel seleccionado
int menu();
//Funcion principal de movimiento las coordenadas m son en la matriz y las a son las de animacion
void mueve_mario(char mat[][212],char mat2[][16]);
//funcion que dibuja al mario moviendose
void dibuja_mario(int xa, int ya, BITMAP *buffer);
//Funcion que hace q mario salte y devuelve su nueva poscicion en y
int salto(char mat[][212],char mat2[][16],int xa,int ya,BITMAP *buffer,int i);
//funcion que imprime el mensaje del final
void end();
//funcion que imprime el mensaje de ganar
void win();
//funcion que imprime los creditos
void creditos(BITMAP *win);


/*
############################
#                          #
#  M   M   AA   III  N  N  #
#  MM MM  A  A   I   NN N  #
#  M M M  AAAA   I   N NN  #
#  M   M  A  A  III  N  N  #
#                          #
############################
*/

main(){
       FILE *archivo;
       archivo=fopen("Mario.txt","r");
       char mat[14][212];
       char mat2[14][16];
       int x;
       
       allegro_init();
       set_color_depth(16);
       set_gfx_mode(GFX_AUTODETECT_WINDOWED,(16*tam_spr), (14*tam_spr), 0, 0);
       install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);/*SONIDO*/
       install_keyboard();
       
       x = menu();       
              
       rellenar(archivo,select(x),mat);
       mueve_mario(mat,mat2);
       end();
       allegro_exit();
       }END_OF_MAIN();
       
/*
############################
#                          #
#  M   M   AA   III  N  N  #
#  MM MM  A  A   I   NN N  #
#  M M M  AAAA   I   N NN  #
#  M   M  A  A  III  N  N  #
#                          #
############################
*/

//Funcion que retorna la cantidad de \n para cada nivel
int select(int x){
    if(x==1){
             return 0;}
    if(x==2){
             return 16;}
    if(x==3){
             return 30;}
    if(x==4){
             return 45;}
      }
      
//Esta Funcion carga el archivo en mat
void rellenar(FILE *arch, int d,char mat[][212]){
     int k=0, q=0, c=0, ban=0;
     fseek(arch, 0, 0);
     char caracter;
     while((caracter=fgetc(arch)) != EOF){
              if(caracter=='\n' && ban==0){
                                 c++;                                 
                                }
              if(c == d){
                  ban = 1;                     
                  if(caracter=='\n'){
                     k++;
                     if(k==15)
                              break;
                     q=0;
                     }
                  else{
                       mat[k][q]=caracter;
                       q++;
                       }    
                  }
          }
     }
     
//Funcion que copia mat en mat2
void inimat2(char mat2[][16],char mat[][212],int a){
     //system("cls");
     if(a>=0){
     int k, q;
     int b=a+16;
     for(k=0;k<14;k++){
         for(q=a;q<b;q++){
             mat2[k][q-a]=mat[k][q];         //Aqui estaba el problema con el -a que faltaba
             //printf("%c",mat2[k][q-a]);
             }
         //printf("\n");
         }
     //printf("variable a:%i\n",a);
     }    
     }

//funcion que imprime mat2
void print_mat(char mat2[][16],BITMAP *buffer){
     BITMAP *sprites;
     PALETTE palette;
     sprites = load_bitmap(pack_spr, palette);
     int fila=0,col=0;
     for(fila=0;fila<14;fila++){
     for(col=0;col<16;col++){
         masked_blit(sprites, buffer, 32*(int)(mat2[fila][col]), 0, 32*(col), 32*fila, 32, 32);
         //los sprits estan ordenados dependiendo del codigo ascii en el archivo y multiplicando
         //por 32 define la poscicion inicial de cada sprite
         }
    }
    destroy_bitmap(sprites);
    }

//funcion que imprime el menu y retorna el nivel seleccionado
int menu(){
    int tam_btm=32;
    int presstecla=0;
    int selectcursor=1;
    MIDI* soundmenu= load_midi("sound/smwintro.mid");
    BITMAP *fondomenu;
    PALETTE palette;
    fondomenu = load_bitmap("images/fondomenu.bmp", palette);
    BITMAP *botones;
    botones = load_bitmap("images/botones.bmp", palette);
    play_midi(soundmenu,TRUE);
    draw_sprite(screen,fondomenu,0,0);
    while(presstecla!=17165){  //ciclo Menu
            //MENU EN LA PANTALLA PARA QUE EL USUARIO ESCOJA EL MUNDO DESEADO
            //textprintf_ex (screen, font, 145, 270, makecol (255, 255,0),-1, "Select level :");
            
            blit(botones, screen, 0, 0, 100+tam_btm, 300, tam_btm, tam_btm);
            blit(botones, screen, tam_btm, 0, 100+tam_btm*3, 300, tam_btm, tam_btm);
            blit(botones, screen, tam_btm*2, 0, 100+tam_btm*5, 300, tam_btm, tam_btm);
            blit(botones, screen, tam_btm*3, 0, 100+tam_btm*7, 300, tam_btm, tam_btm);
            
            switch(selectcursor){
            case 1:
                 blit(botones, screen, tam_btm*4, 0, 100+tam_btm, 300, tam_btm, tam_btm);
                 break;
            case 2:
                 blit(botones, screen, tam_btm*4, 0, 100+tam_btm*3, 300, tam_btm, tam_btm);
                 break;
            case 3:
                 blit(botones, screen, tam_btm*4, 0, 100+tam_btm*5, 300, tam_btm, tam_btm);
                 break;
            case 4:
                 blit(botones, screen, tam_btm*4, 0, 100+tam_btm*7, 300, tam_btm, tam_btm);
                 break;          
            }
            presstecla = readkey();
            if (presstecla == 21248){
                      if(selectcursor<4){
                      selectcursor+=1;
                      }}
            if (presstecla == 20992){
                      if(selectcursor>1){
                      selectcursor-=1;
                      }}
            
            }  //CICLO DEL MENU
            destroy_bitmap(botones);
            destroy_bitmap(fondomenu);
            destroy_midi(soundmenu);
            return selectcursor;
}

/*
#############################
#                           #
#   FUNCION DE MOVIMIENTO   #
#                           #
#############################
*/


//Funcion principal de movimiento las coordenadas m son en la matriz y las a son las de animacion
void mueve_mario(char mat[][212],char mat2[][16]){
     int xm=0;
     int ym=5;
     int xa=xm*tam_spr;
     int ya=ym*tam_spr; //variables posicion de mario
     int pos1_m2=0; //el iterador que recorre la matriz2
     int i=0;
     int variable;
     int monedas=0;
     //int presstecla=0;
     MIDI *world1=load_midi("sound/smwwd1.mid");
     MIDI *lose=load_midi("sound/smwlose.mid");
     play_midi(world1,TRUE);
     
     BITMAP *fondo;  //FONDO
     BITMAP *start;  //pANTALLAZO DE COMIENZO
     BITMAP *buffer;
     fondo = load_bitmap("images/fondo.bmp", NULL);
     start = load_bitmap("images/start.bmp", NULL);
     buffer=create_bitmap((16*tam_spr), (14*tam_spr));
     
     draw_sprite(screen,start,0,0);
     
     
     while(!key[KEY_ESC]){      //condicion de salida
          //presstecla=0;
          //presstecla=readkey();
          
          sleep(96);
          //readkey(); //Leemos una pulsacion de tecla y la almacenamos en el buffer de teclado
          
          if(key[KEY_RIGHT]){     //comparamos la ultima pulsacion de la tecla desde el buffer de tecla
                 if(mat[ym][xm+1]=='a' || mat[ym][xm+1]=='u' || mat[ym][xm+1]=='t' || mat[ym][xm+1]=='v' || mat[ym][xm+1]=='4' || mat[ym][xm+1]=='5' || mat[ym][xm+1]=='6' || mat[ym][xm+1]=='7' || mat[ym][xm+1]=='f'){
                         if(xm>6 && pos1_m2<196){           
                         pos1_m2++;
                         }
                         if(xm<212){
                           xm++;
                         }
                         }
                 }                
          if(key[KEY_LEFT]){       //comparamos la ultima pulsacion de la tecla desde el buffer de teclado
                 if(mat[ym][xm-1]=='a' || mat[ym][xm-1]=='u' || mat[ym][xm-1]=='t' || mat[ym][xm-1]=='v' || mat[ym][xm-1]=='4' || mat[ym][xm-1]=='5' || mat[ym][xm-1]=='6' || mat[ym][xm-1]=='7' || mat[ym][xm-1]=='f'){
                         if(xm>7 && xm>0){           
                         pos1_m2--;
                         }
                         if(xm>0){
                           xm--;
                         }
                         }
                 }
          if(key[KEY_UP]){
                
                ym=salto(mat,mat2,xm,ym,buffer,i);
                }
          
         /*PRUEBA      
         system("cls");
         printf("poscicion (xm,ym):(%i,%i)\n",xm,ym);
         printf("iterador matriz: %i\n",pos1_m2);
         */
         
         draw_sprite(buffer,fondo,0,0);   //El problema de la tecla retrasada era que imprimia y luego leia 
         inimat2(mat2,mat,pos1_m2);
         print_mat(mat2,buffer);
         
         if(mat[ym+1][xm]=='a'|| mat[ym+1][xm]=='u' || mat[ym+1][xm]=='t' || mat[ym+1][xm]=='v' || mat[ym+1][xm]=='4' || mat[ym+1][xm]=='5' || mat[ym+1][xm]=='6' || mat[ym+1][xm]=='7' || mat[ym+1][xm]=='f'){
             ym++;
         }else{
             i=1;
         }
         
         if(ym<=10){
         if(mat[ym+5][xm]=='a'|| mat[ym+5][xm]=='u' || mat[ym+5][xm]=='t' || mat[ym+5][xm]=='v' || mat[ym+5][xm]=='4' || mat[ym+5][xm]=='5' || mat[ym+5][xm]=='6' || mat[ym+5][xm]=='7' || mat[ym+5][xm]=='f'){
             i=0;
         }
         if(mat[ym-1][xm]=='^'|| mat[ym-1][xm]=='s' || mat[ym-1][xm]=='1' || mat[ym-1][xm]=='v' || mat[ym-1][xm]=='4' || mat[ym-1][xm]=='5' || mat[ym-1][xm]=='6' || mat[ym-1][xm]=='7' || mat[ym-1][xm]=='f'){
             i=0;
         }
         
         if(mat[ym+1][xm]=='^'|| mat[ym+1][xm]=='s' || mat[ym+1][xm]=='1' || mat[ym+1][xm]=='v' || mat[ym+1][xm]=='4' || mat[ym+1][xm]=='5' || mat[ym+1][xm]=='6' || mat[ym+1][xm]=='7' || mat[ym+1][xm]=='f'){
             i=1;
         }
         if(mat[ym+2][xm]=='^'|| mat[ym+2][xm]=='s' || mat[ym+2][xm]=='1' || mat[ym+2][xm]=='v' || mat[ym+2][xm]=='4' || mat[ym+2][xm]=='5' || mat[ym+2][xm]=='6' || mat[ym+2][xm]=='7' || mat[ym+2][xm]=='f'){
             i=1;
         }
         if(mat[ym+3][xm]=='^'|| mat[ym+3][xm]=='s' || mat[ym+3][xm]=='1' || mat[ym+3][xm]=='v' || mat[ym+3][xm]=='4' || mat[ym+3][xm]=='5' || mat[ym+3][xm]=='6' || mat[ym+3][xm]=='7' || mat[ym+3][xm]=='f'){
             i=1;
         }
         
         
         }
         
         dibuja_mario(xm,ym,buffer);
         draw_sprite(screen,buffer,0,0);
         textprintf_ex (screen, font, 15, 15, makecol (255, 255,255),-1, "Monedas: %i",monedas);
         
         //condicion de cojer monedas
         if(mat[ym][xm]=='f'){
            mat[ym][xm]='a';
            monedas++;
         }
         
         if(ym==13){
            play_midi(lose,FALSE);
            for(variable=0;variable<400;variable++){
            circlefill(buffer,7*32,13*32,variable*3,makecol(0,0,0));
            draw_sprite(screen,buffer,0,0);
            sleep(10);
            }
            break;  
         }
         //condicion de ganar por llegar al final del mundo
         if(xm==202){
            win();
            break;
         }
     }  //fin del while principal
     
     
     destroy_midi(lose);
     destroy_midi(world1);
     destroy_bitmap(buffer);
     destroy_bitmap(fondo);
     destroy_bitmap(start);
     }
     
/*
            break;  
#############################
#                           #
#   FUNCION DE MOVIMIENTO   #
#                           #
#############################
*/

     
//funcion que dibuja al mario moviendose
void dibuja_mario(int xa, int ya,BITMAP *buffer){
     int anim_spr;
     BITMAP *sprites;
     PALETTE palette;
     sprites = load_bitmap("images/spritesmario.bmp", palette);
     
     anim_spr=xa%2;
     
     if(xa<=6 && ya!=13){
          masked_blit(sprites, buffer, tam_spr*anim_spr, 0,xa*tam_spr,(ya*tam_spr)-10, tam_spr, 42);
     }else{
          if(ya!=13){ 
          masked_blit(sprites, buffer, tam_spr*anim_spr, 0, 7*tam_spr, (ya*tam_spr)-10, tam_spr, 42);
     }}
     
     if(ya==13){
         masked_blit(sprites, buffer, tam_spr*2, 0, 7*tam_spr, (ya*tam_spr)-10, tam_spr, 42);
         }
     
     destroy_bitmap(sprites);
     }
//FUNCION END QU MUESTRA EL MENSAJE DE GAME OVER
void end(){
     MIDI *fin=load_midi("sound/smwend.mid"); 
     BITMAP *final;
     final=load_bitmap("images/end.bmp", NULL);
     play_midi(fin,FALSE);     
     blit(final,screen,0,0,0,0,512,448);
     sleep(5000);  
     destroy_bitmap(final);
     }
//EL MENSAJE DE GANAR
void win(){
     BITMAP *texto;
     MIDI *ganar=load_midi("sound/smwwin.mid"); 
     BITMAP *win;
     win=load_bitmap("images/win.bmp", NULL);
     texto=load_bitmap("images/texto.bmp", NULL);
     play_midi(ganar,TRUE);   
         blit(win,screen,0,0,0,0,512,448);
         sleep(2000);
         blit(win,screen,512,0,0,0,512,448);
         sleep(2000);
         blit(win,screen,0,0,0,0,512,448);
         masked_blit(texto,screen,0,0,0,0,512,448);
         /*
         textprintf_ex (screen, font, 75, 65, makecol (255, 255,255),-1, "Mario's adventure is over.");
         textprintf_ex (screen, font, 75, 105, makecol (255, 255,255),-1, "Mario,the Princess, Yoshi,");
         textprintf_ex (screen, font, 75, 145, makecol (255, 255,255),-1, "and his friends are going ");
         textprintf_ex (screen, font, 75, 185, makecol (255, 255,255),-1, "to take a vacation.");
         */
         
         sleep(10000);
         blit(win,screen,1024,0,0,0,512,448);
         sleep(5000);
         blit(win,screen,1536,0,0,0,512,448);
         creditos(win);
     
     destroy_midi(ganar);
     destroy_bitmap(win);
     return;
     }
     
int salto(char mat[][212],char mat2[][16],int xa,int ya,BITMAP *buffer,int i){
    
    if(
    //(mat[ya-1][xa]=='a' || mat[ya-1][xa]=='4' || mat[ya-1][xa]=='5' || mat[ya-1][xa]=='6' || mat[ya-1][xa]=='7') && 
    ya>1 && 
    i==1
    ){
                           
    ya-=2;
    
    }
    
    //condicion para romper los bloques
    if(mat[ya-1][xa]=='s'){
      mat[ya-1][xa]='1';                    
      mat[ya-2][xa]='f';
    
   }
    return ya;
    
}

void creditos(BITMAP *win){
     int i;
     for (i=0;i<400;i++){
        blit(win,screen,1536,0,0,0,512,448);
        textprintf_ex (screen, font, 160, 140-i, makecol (255, 255,255),-1, "      --- CREDITS ---     ");
        textprintf_ex (screen, font, 160, 160-i, makecol (255, 255,255),-1, "Produced by: Oscar Bernal");
        textprintf_ex (screen, font, 160, 170-i, makecol (255, 255,255),-1, " Sprites by: Oscar Bernal");
        textprintf_ex (screen, font, 160, 180-i, makecol (255, 255,255),-1, "  Sounds by: Oscar Bernal");
        textprintf_ex (screen, font, 160, 190-i, makecol (255, 255,255),-1, "   Director: Oscar Bernal");
        textprintf_ex (screen, font, 145, 200-i, makecol (255, 255,255),-1, "Post-Production: Oscar Bernal");
        textprintf_ex (screen, font, 160, 210-i, makecol (255, 255,255),-1, "  Edited by: Oscar Bernal");
        textprintf_ex (screen, font, 160, 220-i, makecol (255, 255,255),-1, "        Etc: Oscar Bernal");
        textprintf_ex (screen, font, 160, 230-i, makecol (255, 255,255),-1, " Checked by: Oscar Bernal");
        textprintf_ex (screen, font, 160, 240-i, makecol (255, 255,255),-1, "  Played by: Oscar Bernal");
        textprintf_ex (screen, font, 160, 250-i, makecol (255, 255,255),-1, "Disegned by: Oscar Bernal");
        textprintf_ex (screen, font, 160, 260-i, makecol (255, 255,255),-1, " Created by: Oscar Bernal");
        textprintf_ex (screen, font, 160, 270-i, makecol (255, 255,255),-1, "      BG by: Oscar Bernal");
        textprintf_ex (screen, font, 160, 300-i, makecol (255, 255,255),-1, "      Thanks Nintendo     ");
        
        sleep(100);
     }
     }
