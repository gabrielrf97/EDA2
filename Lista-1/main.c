//
//  main.c
//  Lista1EDA2
//
//  Created by Gabriel on 15/03/2018.
//  Copyright © 2018 AppleDeveloperAcademyUCB. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define size_index_1 10
#define size_index_2 100
#define initialVectorSize 10000

int* populate_data_vector(int size, float securityMargin, int* emptyPositionTracker);
int* populate_second_index_arr(int* dataArray);
int* populate_first_index_arr(int* index2);
void create_initial_menu(int* index1, int* index2, int* dataArray);
int find_slot_for_value(int* index1, int* index2, int* dataArray, int number);

int main(int argc, const char * argv[]) {
    
    int *dataArray, *index2, *index1, *emptyPositionTracker  = calloc( 100 , sizeof(int));
    float securityMargin = 1.0;
    
    //Checka esses & ai
    dataArray = populate_data_vector(initialVectorSize, securityMargin, emptyPositionTracker);
    index2 = populate_second_index_arr(dataArray);
    index1 = populate_first_index_arr(index2);
    
    create_initial_menu(index1, index2, dataArray);

    return 0;
}

void create_initial_menu(int* index1, int* index2, int* dataArray){
    char userInput;
    int value;
    do{
        printf("*****************************\n");
        printf("* Escolha sua ação:         *\n");
        printf("******************+**********\n");
        printf("* 1 - Inserir um numero     *\n");
        printf("* 2 - Remover um numero     *\n");
        printf("* 3 - Buscar um numero      *\n");
        printf("* 4 - Itens vazios por slot *\n");
        printf("* 5 - Encerrar              *\n");
        printf("*****************************\n");
        do{
            userInput = getchar();
        }while(userInput == '\n');
        switch (userInput) {
        case '1':
                printf("Insira o valor que deseja inserir: ");
                scanf("%d", &value);
                find_slot_for_value(index1, index2, dataArray, value);  
            break;
//        case '2':
//                 mesma coisa do alg anterior, so que da shiftback, e tem que ver se o numero existe ou remover pelo index dele( a segunda é mais facil)
//            break;
//        case '3':
//                 parecido com o case 1, so que sem validar se tem espaço e sem dar shift, obviamente
//            break;
//        case '4':
                    //printa o emptyPositionTracker
        case '5':
            //do nothing
            break;
        default:
            printf ("wtf dude?\n\n");
        }
    }while(userInput != '5');
}

//Criar vetor aleatorio, com 11000 posições, sendo que das 11000, só 10000 terão valores
int* populate_data_vector(int size, float securityMargin, int* emptyPositionTracker){
    
    int fullSize = (int) size * securityMargin;
    int *vector = calloc( fullSize , sizeof(int));            
    //Populating the 10000 first positions
    for (int i = 0; i < fullSize ; i++){
        //Left a black space in vector
        if (i % 90 == 0 && i + 10 <= fullSize)
            i += 10;
        if(i < fullSize)
            vector[i] = i * 5;
       
    }
    
    //Populate Empty position tracker
    for (int i = 0; i < 100; i++) {
        emptyPositionTracker[i] = 10;
    }

    return vector;
}

//Criar index secundário, que vai apontar para o vetor original/pula de 100 em 100
int* populate_second_index_arr(int* dataArray){
    int *index2 = calloc( size_index_2 , sizeof(int));
    for(int i = 0; i < size_index_2; i++){   
        index2[i] = dataArray[i * 100];
    }
    return index2;
}

//Criar index primário, que aponta para o vetor secundario, pula de 10 em 10
int* populate_first_index_arr(int* index2) {  
    int *index1 = calloc( size_index_1 , sizeof(int));  
    for(int i = 0; i < size_index_1; i++){
        index1[i] = index2[i * 10];
    }
    return index1;
}


int find_slot_for_value(int* index1, int* index2, int* dataArray, int number){
    int get_first_index_position(int* index1, int number);
    int get_second_index_position(int* index2, int number, int first_index_position);
    int get_position_in_data_vector(int* dataArray, int number, int second_index_position);

    int first_index_position = get_first_index_position(index1, number);
    int second_index_position = get_second_index_position(index2, number, first_index_position);
    int position = get_position_in_data_vector(dataArray, number, second_index_position);
    //printf("* DEBUG:\n* Valor: %d\n* Anterior: [%d] = %d\n* Próximo: [%d] = %d\n",number, position, dataArray[position], position+1, dataArray[position+1]);
    return position;
}

int get_first_index_position(int* index1, int number){
    int position = -1;
    for(int i = 0; i < size_index_1-1; i++){
        if(position == -1 && number < index1[i+1]){
            position = i;
        }
    }
    if(position == -1){ //Number is higher than others.
        position = size_index_1-1; // fit it on the last index
    }
    return position;
}

int get_second_index_position(int* index2, int number, int first_index_position){
    int position = -1;
    for(int i = first_index_position*10; i < (first_index_position + 1)*10; i++){
        if(position == -1 && number < index2[i+1]){
            position = i;
        }
    }
    if(position == -1){
        position = (first_index_position + 1)*10-1;
    }
    return position;
}


int get_position_in_data_vector(int* dataArray, int number, int second_index_position){
    int startPos = second_index_position*100;
    int endPos = (second_index_position + 1)*100;
    int position = startPos;
    for(int i = startPos; number > dataArray[i] && i < initialVectorSize; i++){
        if(number < dataArray[i+1] || dataArray[i+1] == 0){
            position = i;
        }
    }
    while(dataArray[position] == 0 && position > 0){
        position--;
    }
    return position;
}
