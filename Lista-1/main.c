//
//  main.c
//  Lista1EDA2
//
//  Created by Gabriel on 15/03/2018.
//  Copyright © 2018 AppleDeveloperAcademyUCB. All rights reserved.
//

#include <stdio.h>

void populate_data_vector(int* vector, int size, float securityMargin, int* emptyPositionTracker);
void populate_second_index_arr(int* index2, int* dataArray);
void populate_first_index_arr(int* index1, int* index2);
void create_initial_menu();

int main(int argc, const char * argv[]) {
    
    int* dataArray, index2, index1, emptyPositionTracker;
    int initialVectorSize = 10000;
    float securityMargin = 1.1;
    
    //Checka esses & ai
    populate_data_vector(&dataArray, initialVectorSize, securityMargin, &emptyPositionTracker);
    populate_second_index_arr(&index2, &dataArray);
    populate_first_index_arr(&index1, &index2);
    
    create_initial_menu();

    return 0;
}

void create_initial_menu() {
    //do{
        printf("*****************************\n");
        printf("* Escolha sua ação:         *\n");
        printf("******************+**********\n");
        printf("* 1 - Inserir um numero     *\n");
        printf("* 2 - Remover um numero     *\n");
        printf("* 3 - Buscar um numero      *\n");
        printf("* 4 - Itens vazios por slot *\n");
        printf("* 5 - Encerrar              *\n");
        printf("*****************************\n");
        //char userInput = getc()
//    switch (userInput) {
//        case 1:
    //            chama o alg de busca (primeiro, pesquisa no primeiro index:
                    //algo do tipo (for, de 0 até tamanho do index 1 - 1)
                        //se num < index1[i]
                            //busca no index2, das posicoes i*10 até (1*10) + 10
                                //achou o slot do numero? ve se tem vaga, consultando a posição
                                //do emptyPositionTracker
                                //Tem vaga, da shift em todos os elementos e insere na posicao que ele tem que ficar
//            break;
//        case 2:
//                 mesma coisa do alg anterior, so que da shiftback, e tem que ver se o numero existe ou remover pelo index dele( a segunda é mais facil)
//            break;
//        case 3:
//                 parecido com o case 1, so que sem validar se tem espaço e sem dar shift, obviamente
//            break;
                    //printa o emptyPositionTracker
//        case 5:
    //               return 0;
//            break;
//        default:
                //printa (usuario burro)
//            break;
//    }
    //}while(userInput != 4)
}

//Criar vetor aleatorio, com 11000 posições, sendo que das 11000, só 10000 terão valores
void populate_data_vector(int* vector, int size, float securityMargin, int* emptyPositionTracker){
    
    int fullSize = (int) size * securityMargin;
    vector = calloc( fullSize , sizeof(int));
    
    //Populating the 10000 first positions
    for (int i = 0; i < fullSize ; i++){
        //Left a black space in vector
        if (i % 100 == 0)
            i += 10;
        vector[i] = i * 5;
    }
    
    //Populate Empty position tracker
    for (int i = 0; i < 100; i++) {
        emptyPositionTracker[i] = 10;
    }
}

//Criar index secundário, que vai apontar para o vetor original/pula de 100 em 100
void populate_second_index_arr(int* index2, int* dataArray){
    
    int size_index_2 = 100;
    
    for(int i = 0; i < size_index_2; i++){
        index2[i] = dataArray[i * 100];
    }
}

//Criar index primário, que aponta para o vetor secundario, pula de 10 em 10
void populate_first_index_arr(int* index1, int* index2) {
    int size_index_1 = 10;
    
    for(int i = 0; i < size_index_1; i++){
        index1[i] = index2[i * 10];
    }
}



