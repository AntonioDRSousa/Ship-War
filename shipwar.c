#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*
	ships has positions in polar coordenates (ro,teta)
	heavy ship  -> 4 life, 1 speed 
	medium ship -> 2 life, 2 speed
	light ship  -> 1 life , 4 speed
*/
typedef struct Ship{
	int type;
	
	int life;
	int speed;

	int ro;
	int teta;
}Ship;

void help(){
	printf("\n============================================================================================================\n");
	printf("                                                 HELP\n");
	printf("============================================================================================================\n\n");
	printf("\nOBJECTIVE : Sink all enemy ships.\n");
	printf("\nMAP : The map is polar coordenates with 0 to 359 degrees and 0 to 29 of circle.\n");
	printf("\nINITIAL STATE : The player have 1 ship and choose the number of enemy ships.\n");
	printf("\nThere's 3 TYPES of ships : \n");
	printf("\t* light ship with 1 life and 4 speed\n");
	printf("\t* medium ship with 2 life and 2 speed\n");
	printf("\t* heavy ship with 4 life and 1 speed\n");
	printf("\nSTATS OF SHIPS : ");
	printf("\t* LIFE : If a ship have 0 life then it will sink.\n");
	printf("\t* SPEED : How many steps you can sail in degrees or in circles.\n");
	printf("\nTURNS : \n");
	printf("\t* The player choose one of five actions : \n");
	printf("\t\t1 - move to out circle with number of steps less or equals to your speed.\n");
	printf("\t\t2 - move to inner circle with number of steps less or equals to your speed.\n");
    printf("\t\t3 - move in clockwise in degrees with number of steps less or equals to your speed.\n");
    printf("\t\t4 - move in anticlockwise in degrees with number of steps less or equals to your speed.\n");
    printf("\t\t5 - shot.\n");
	printf("\t* Each enemy ship choose one previous described actions randomly,\n");
    printf("\t  and act in the same way of actions that player made.\n");
	printf("\t  That's meaning : \n");
	printf("\t  Moves the parcicular enemy ship or shot in coordinate of player ship. \n");
	printf("\nSHOTS : \n");
	printf("\tParcticular in shot action, you choose a coordinate for hit, and shot can be hit point or fail in hit point.\n");
	printf("\tThe sucessefull of shot is decided by random.\n");
	printf("\tLet be D1 the distance between circle position of shot and ship that shots.\n");
	printf("\tLet be D2 the distance between degree position of shot and ship that shots.\n");
	printf("\tHow less is distance D1 and D2, more is probability of hit is sucessefull.\n");
	printf("\tIn details : \n");
	printf("\t\t1 - you random a number R2 between 0 and 30 and check if R1>D1.\n");
	printf("\t\t2 - you random a number R2 between 0 and 360 and check if R2>D2.\n");
	printf("\t\tIf your sucessefull hit shot in coordinates of a enemy ship, then you hit this ship.\n");
	printf("\t\tThe ship hitted lose 1 life.\n");
	printf("\nSINK : \n");
	printf("\t* If player ship life is equal to 0, then it's sink and player lose the game.\n");
	printf("\t* If enemy ship life is equal to 0, then it's sink and enemy ship is out of game.\n");
	printf("\t* If all enemy ship is out of game, then player wins the game.\n");
	printf("\n============================================================================================================\n");
}

void title(){
	printf("================================================\n");
	printf("!                 Ship War                     !\n");
	printf("================================================\n");
}
	
Ship createShip(int x, int ro, int teta){
	Ship s;
	s.type = x;
	s.ro = ro;
	s.teta = teta;
	
	if(x==1){
		s.life = 4;
		s.speed = 1;
	}
	else if(x==2){
		s.life = 2;
		s.speed = 2;
	}
	else if(x==3){
		s.life = 1;
		s.speed = 4;
	}
	
	return s;
}

Ship chooseShip(){
	while(1){
		printf("\n--------------------------------\n");
        printf("[1] - heavy ship ( life = 4 , speed = 1 )\n");
        printf("[2] - medium ship ( life = 2 , speed = 2 )\n");
        printf("[3] - light ship ( life = 1 , speed = 4 )\n");
        printf("--------------------------------\n");
		int type;
		scanf("%d",&type);
		if((type>=1)&&(type<=3)){
			return createShip(type,0,0);
		}
	}
}

int chooseQuantity(){
	while(1){
		printf("\n--------------------------------\n");
        printf("Write quantity of enemy ships(1-1000) : \n");
        printf("--------------------------------\n");
		int qtd;
		scanf("%d",&qtd);
		if((qtd>=1)&&(qtd<=1000)){
			return qtd;
		}
	}
}

int getSteps(int speed){
	int steps;
	while(1){
		printf("write number of moves: ");
		scanf("%d",&steps);
		if((steps>=1)&&(steps<=speed)){
			return steps;
		}
	}
}

void showShip(Ship s, int id){
	if(id<0){
		printf("Ship Player -> ");
	}
	else{
		printf("Ship %d -> ",id);
	}
	printf("(type %d , ",s.type);
	printf("life : %d , ",s.life);
	printf("speed : %d) ; ",s.speed);
	printf("(circle : %d , ",s.ro);
	printf("degree : %d)\n",s.teta);
}

void removeShip(Ship v[], int i, int qtd){
	int j;
	for(j=i;j<qtd;j++){
		v[j]=v[j+1];
	}
}

void shotPlayer(Ship player, Ship ships[], int * qtd, int c, int d){
	int r1 = rand()%360;
	int r2 = rand()%30;
	int i;
	for(i=0;i<(*qtd);i++){
		Ship s = ships[i];
		int dro = abs(s.ro-player.ro);
		int dteta = abs(s.teta-player.teta);
		if((r2>dro)&&(r1>dteta)&&(c==s.ro)&&(d==s.teta)){
			printf("You Hit a Ship.\n");
			s.life--;
			ships[i]=s;
			if(s.life==0){
				(*qtd)--;
				removeShip(ships,i,*qtd);
			}
			break;
		}
		else if(i==((*qtd)-1)){
			printf("Shot Fail.\n");
		}
	}
}

void makeShot(Ship player, Ship ships[], int qtd){
	while(1){
		int c, d;
		printf("write coordenates: \n");
		printf("circle(0-29) = ");
		scanf("%d",&c);
		printf("degree(0-359) = ");
		scanf("%d",&d);
		if((c>=0)&&(c<=29)&&(d>=0)&&(d<=359)){
			shotPlayer(player, ships, &qtd, c, d);
		}
		else{
			printf("Invalid Shot .....\n");
			continue;
		}
		break;
	}
}

int moveDegree(int teta, int steps){
	teta += steps;
	if(steps>=0){
		teta %= 359;
	}
	else{
		if(teta<0){
			teta += 360;
		}
	}
	return teta;
}


Ship playShips(Ship player, Ship ships[], int qtd){
	int i, new, r1, r2, r, v;
	for(i=0;i<qtd;i++){
		Ship s = ships[i];
		while(1){
			r = (rand()%5)+1;
			v = (rand()%s.speed)+1;
			switch(r){
				case 1:
					new = s.ro+v;
					if(new<30){
						s.ro=new;
						printf("Ship %d move %d steps in out circle.\n",i,v);
					}
					else{
						continue;
					}
					break;
				case 2:
					new = s.ro-v;
					if(new>0){
						s.ro=new;
						printf("Ship %d move %d steps in inner circle.\n",i,v);
					}
					else{
						continue;
					}
					break;
				case 3:
					s.teta = moveDegree(s.teta,v);
					printf("Ship %d move %d degrees.\n",i,v);
					break;
				case 4:
					s.teta = moveDegree(s.teta,-v);
					printf("Ship %d move -%d degrees.\n",i,v);
					break;
				case 5:
					r1 = rand()%360;
					r2 = rand()%30;
					if((r2>abs(s.ro-player.ro))&&(r1>abs(s.teta-player.teta))){
						printf("Ship %d hit your ship.\n",i);
						player.life--;
					}
					else{
						printf("Ship %d fail to hit your ship.\n",i);
					}
					break;
			}
			ships[i] = s;
			break;
		}
	}
	return player;
}

void game(Ship player, Ship ships[], int qtd){
	printf("\n=====================================================\n");
	
	while(1){
		printf("\n**********************************\n");
			int i;
		for(i=0;i<qtd;i++){
			showShip(ships[i],i);
		}
		printf("\n**********************************\n");
		printf("\n++++++++++++++++++++++++++++++++++\n");
		showShip(player,-1);
		printf("++++++++++++++++++++++++++++++++++\n");
		
		printf("----------------------\n");
		printf("[0] - list navy\n");
        printf("[1] - move to out circle\n");
        printf("[2] - move to inner circle\n");
        printf("[3] - move in clockwise\n");
        printf("[4] - move in anticlockwise\n");
        printf("[5] - shot\n");
        printf("----------------------\n");
		int op;
		scanf("%d",&op);
		int new;
		switch(op){
			case 1:
				new = player.ro+getSteps(player.speed);
				if(new<30){
					player.ro=new;
				}
				else{
					printf("Invalid move to out circle. Max 30.\n");
					continue;
				}
				break;
			case 2:
				new = player.ro-getSteps(player.speed);
				if(new>0){
					player.ro=new;
				}
				else{
					printf("Invalid move to inner circle. Min 0.\n");
					continue;
				}
				break;
			case 3:
				player.teta = moveDegree(player.teta,getSteps(player.speed));
				break;
			case 4:
				player.teta = moveDegree(player.teta,-getSteps(player.speed));
				break;
			case 5:
				makeShot(player, ships, qtd);
				break;
			default:
				printf("Error......\n");
				continue;
		}
		
		if(qtd==0){
			printf("YOU WIN .....\n");
			break;
		}
		player = playShips(player,ships,qtd);
		if(player.life<=0){
			printf("YOU LOSE .....\n");
			break;
		}
	}
	printf("\n=====================================================\n");
	
}

void new_game(){
	Ship s = chooseShip();
	int qtd = chooseQuantity();
	
	Ship ships[1000];
	
	int i;
	for(i=0;i<qtd;i++){
		int tp = (rand()%3)+1;
		int ro = (rand()%30);
		int tt = (rand()%360);
		ships[i] = createShip(tp,ro,tt);
	}
	
	game(s,ships,qtd);
}


void menu(){
	while(1){
		printf("------------------------------------\n");
		printf("[1] - New Game\n");
		printf("[2] - Help\n");
		printf("[3] - Quit\n");
		printf("------------------------------------\n");
		int op;
		scanf("%d",&op);
		switch(op){
			case 1:
				new_game();
				break;
			case 2:
				help();
				break;
			case 3:
				exit(0);
				break;
			default:
				continue;
		}
	}
}

int main(){
	system("@echo off");
	system("title Ship War");
	title();
	menu();
	system("pause");
	return 0;
}