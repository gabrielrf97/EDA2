//
//  main.c
//  Lista1EDA2
//
//  Created by Gabriel on 15/03/2018.
//  Copyright © 2018 AppleDeveloperAcademyUCB. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define size_index_1 10
#define size_index_2 100
#define initialVectorSize 10000

int vectorSize

int* populate_data_vector(int size, float securityMargin, int* emptyPositionTracker);
int* populate_second_index_arr(int* dataArray);
int* populate_first_index_arr(int* index2);
void create_initial_menu(int* index1, int* index2, int* dataArray, int* emptyPositionTracker);
int* repopulate_vector(int* dataArray, int*  emptyPositionTracker, int* index1, int* index2);
int find_slot_for_value(int* index1, int* index2, int* dataArray, int number, int* second_index_position);
int find_value_position(int* index1, int* index2, int* dataArray, int value, int* second_index_position);
bool check_enough_space(int* emptyPositionTracker, int slotNumber);

int main(int argc, const char * argv[]) {
    
    vectorSize = initialVectorSize

    int *dataArray, *index2, *index1, *emptyPositionTracker  = calloc( 100 , sizeof(int));
    float securityMargin = 1.0;
    
    dataArray = populate_data_vector(initialVectorSize, securityMargin, emptyPositionTracker);
    index2 = populate_second_index_arr(dataArray);
    index1 = populate_first_index_arr(index2);
    
    create_initial_menu(index1, index2, dataArray);

    return 0;
}

void create_initial_menu(int* index1, int* index2, int* dataArray, int* emptyPositionTracker){
    void insert_element_at_position(int position, int value, int* dataArray);
    void remove_element_at_position(int position, int* dataArray);
    
    char userInput;
    int value, position;
    int second_index_position;

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

            position = find_slot_for_value(index1, index2, dataArray, value, &second_index_position);
            
            if (check_enough_space(int* emptyPositionTracker, int second_index_position)) {
                insert_element_at_position(position, value, dataArray);
                emptyPositionTracker[second_index_position] -= 1
            } else {
                dataArray = repopulateVector(dataArray, emptyPositionTracker, index1, index2)
                insert_element_at_position(position, value, dataArray);
                emptyPositionTracker[second_index_position] -= 1
            }
            
            break;
        case '2':
            printf("Insira o valor que deseja remover: ");
            scanf("%d", &value);
            position = find_value_position(index1, index2, dataArray, value, &second_index_position);
            if(position != -1){
                printf("Removendo elemento [%d] = %d\n", position, dataArray[position]);
                remove_element_at_position(position, dataArray); 
                emptyPositionTracker[second_index_position] += 1
            } 
            else{
                printf("%d não existe no vetor.\n", value);
            }

            break;
        case '3':
            printf("Insira o valor que deseja buscar: ");
            scanf("%d", &value);
            position = find_value_position(index1, index2, dataArray, value, &second_index_position);
            if(position != -1){
                printf("%d está na posição [%d]\n", value, position);
            }                                 
            else{
                printf("%d não existe no vetor.\n", value);
            }
            break;
       case '4':
            print_current_array_status(emptyPositionTracker)
            break;
        case '5':
            //do nothing
            break;
        default:
            printf ("wtf dude?\n\n");
        }
    }while(userInput != '5');
}

bool check_enough_space(int* emptyPositionTracker, int slotNumber) {
    return emptyPositionTracker[slotNumber] > 0 ? true : false
}

void print_current_array_status(int* emptyPositionTracker) {
    printf("Numero de itens vazios por slot: \n");
    for (int i = 0; i < 100; i++){
       printf("%d - %d", i+1, emptyPositionTracker[i]);
    }
}

int* repopulate_vector(int* dataArray, int*  emptyPositionTracker, int* index1, int* index2) {

    int* auxArray = calloc (vectorSize * 1, sizeof(int));
    int* gappedArray = calloc (vectorSize * 1.1, sizeof(int));
    int currentNumbers = 0;
    int aux = 0;

    //Copiou o vetor
    for (int i = 0; i < vectorSize; i++){
        if (dataArray[i] != 0) {
            auxArray[currentNumbers] = dataArray[i];
            currentNumbers += 1; 
        }
    }

    for (int i = 0; i < vectorSize; i++, aux++){
        gappedArray[aux] = auxArray[i];
        if( i % currentNumbers/100 == 0) {
            aux += currentNumbers/100;
        }
    }

    free(auxArray);

    vectorSize *= 1.1;

    index2 = populate_second_index_arr(gappedArray);
    index1 = populate_first_index_arr(index2);

    return gappedArray;
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

int binarySearch(int* dataArray, int startPos, int endPos, int value){
    if(endPos >= initialVectorSize){
        endPos = initialVectorSize-1;
    }
    while(dataArray[endPos] == 0){
        endPos--;
    }
    int index = (startPos+endPos)/2;
    printf("DEBUG: Index: [%d] = %d\nInicio: [%d] = %d\nFim: [%d] = %d\n", index, dataArray[index], startPos, dataArray[startPos], endPos, dataArray[endPos]);
    if(dataArray[index] == value){
        return index;
    }
    if(endPos == startPos){
        return -1; //elemento não encontrado;
    }
    else{
        if(dataArray[index] > value){
            return binarySearch(dataArray, startPos, index-1, value);
        }
        else{
            return binarySearch(dataArray, index+1, endPos, value);
        }
    }
}

int find_value_position(int* index1, int* index2, int* dataArray, int value, int* second_index_position){
    int binarySearch(int* dataArray, int startPos, int endPos, int value);
    int get_first_index_position(int* index1, int number);
    int get_second_index_position(int* index2, int number, int first_index_position);

    int first_index_position = get_first_index_position(index1, value);
    *second_index_position = get_second_index_position(index2, value, first_index_position);
    int startPos = *second_index_position*100;
    int endPos = (*second_index_position + 1)*100;
    while(dataArray[endPos] == 0){
        endPos--;
    }
    return binarySearch(dataArray, startPos, endPos, value);
}

void remove_element_at_position(int position, int* dataArray){
    int buffer;
    do{
        buffer = dataArray[position+1];
        dataArray[position++] = buffer;
    }while(buffer != 0); 
}

//Criar index secundário, que vai apontar para o vetor original/pula de 100 em 100
int* populate_second_index_arr(int* dataArray){
    int *index2 = calloc( size_index_2 , sizeof(int));
    for(int i = 0; i < size_index_2; i++){   
        index2[i] = dataArray[i * 100];
    }
    return index2;
}

void insert_element_at_position(int position, int value, int* dataArray){
    int index = position;
    while(dataArray[index] != 0){
        index++;
    }
    while(index > position+1){
        dataArray[index] = dataArray[index-1];
        index--;
    }
    dataArray[position] = value;
}

//Criar index primário, que aponta para o vetor secundario, pula de 10 em 10
int* populate_first_index_arr(int* index2) {  
    int *index1 = calloc( size_index_1 , sizeof(int));  
    for(int i = 0; i < size_index_1; i++){
        index1[i] = index2[i * 10];
    }
    return index1;
}


int find_slot_for_value(int* index1, int* index2, int* dataArray, int number, int* second_index_position){
    int get_first_index_position(int* index1, int number);
    int get_second_index_position(int* index2, int number, int first_index_position);
    int get_position_in_data_vector(int* dataArray, int number, int second_index_position);

    int first_index_position = get_first_index_position(index1, number);
    *second_index_position = get_second_index_position(index2, number, first_index_position);
    int position = get_position_in_data_vector(dataArray, number, *second_index_position);
    printf("* DEBUG:\n* Valor: %d\n* Anterior: [%d] = %d\n* Próximo: [%d] = %d\n",number, position, dataArray[position], position+1, dataArray[position+1]);
    return position+1;
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
