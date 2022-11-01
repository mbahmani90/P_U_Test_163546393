
#include <stdio.h>
#include "stdbool.h"

// int A[12][5]         = {{0}, {0}, {0}, {0}, {0}, {2 , 4}, {0}, {0}, {0}, {0}, {5 , 3}, {0}};
// int sizeItemA[12]    = { 0 ,  0 ,  0 ,  0 ,  0 ,  2     ,  0 ,  0 ,  0 ,  0 ,  2     ,  0 };
// int isParent [12][5] = {{0}, {0}, {0}, {0}, {0}, {0 , 0}, {0}, {0}, {0}, {0}, {1 , 0}, {0}};
// int B[12]            = {5 , 10};
// int sizeA            = 11;
// int sizeB            = 2;
// int root             = 10;

// int test_array[10][2]      = {{4 , 3} , {4 , 2} , {2 , 3}};
// int test_array_size        = 3;

int A[1002][1002]      = {{0}};
int sizeItemA[1002]    = { 0 };
int B[1002]            = { 0 };
int sizeA            = 0;
int sizeB            = 0;
int root             = 0;

int test_array[1000002][2] = {{}};
int test_array_size        = 0;

int route_array[10][10]    = {{0}};
int route_array1[10][10]   = {{0}};
int route_array2[10][10]   = {{0}};

int route_array_size[10]   = { 0 };
int route_array_size1[10]  = { 0 };
int route_array_size2[10]  = { 0 };

void scan_route(int current , int target , int route_array_index , int size, int *temp_route_array[10] , int *array_size);
void scan_route1(int current , int target , int route_array_index , int size);
void scan_route2(int current , int target , int route_array_index , int size);
int  are_branches_of_same_node(int current, int target , int *new_current , int *new_target);

void append_to_B(int value){
    
    if(sizeB == 0){
        B[sizeB] = value;
        sizeB++;
    }else{
        int is_in_B = false;
        for(int j = 0 ; j < sizeB ; j++){
            
            if(value == B[j]){
                is_in_B = true;
                break;
            }
            
        }
        if(!is_in_B){
            B[sizeB] = value;
            sizeB++;
        }
    }
    
}

void get_values(){
    
    int number_of_nodes = 0;
    int input_array[1000][3];
    
    printf("Please Enter The Number Of Nodes: "); 
    scanf("%d", &number_of_nodes);
    
    if(number_of_nodes < 3){
        printf("Number of Nodes Should Be Greater Than 3\n\n\n");
        get_values();
        return;
    }
    for(int i = 0 ; i < number_of_nodes ; i++){
        
        printf("N%d: " , (i + 1)); 
        scanf("%d %d %d", &input_array[i][0] , &input_array[i][1] , &input_array[i][2]);    

    }
    
    for(int i = 0 ; i < number_of_nodes ; i++){
        
        if(input_array[i][0] == input_array[i][1]){
            root = input_array[i][0];
        }else{
            int temp_index = input_array[i][1];
            A[temp_index][sizeItemA[temp_index]] = input_array[i][0];
            sizeItemA[temp_index]++;
            
            if( (temp_index + 1) > sizeA){
                sizeA = temp_index + 1;
            }
        }
        
        if(input_array[i][2] == 1){
            append_to_B(input_array[i][0]);
        }
        
    }
    
    printf("B={");
    for(int i = 0 ; i < sizeB ; i++){
        if(i < sizeB - 1){
            printf("%d," , B[i]);    
        }else{
            printf("%d" , B[i]); 
        }
        
    } 
    printf("}\n");
    
    printf("A={");
    for(int i = 0 ; i < sizeA ; i++){
        printf("{");
        for(int j = 0 ; j < sizeItemA[i] ; j++){
            if(j < sizeItemA[i] - 1){
                printf("%d," , A[i][j]);    
            }else{
                printf("%d" , A[i][j]); 
            }
            
        }
        printf("}");
        
    }
    printf("}\n");
    
    printf("root = %d\n" , root);
    printf("sizeA = %d\n" , sizeA);
    printf("sizeB = %d\n" , sizeB);
    printf("sizeItemA={");
    for(int i = 0 ; i < sizeA ; i++){
        if(i < sizeA - 1){
            printf("%d," , sizeItemA[i]);    
        }else{
            printf("%d" , sizeItemA[i]); 
        }
        
    } 
    printf("}\n");  
    
    printf("Please Enter The Number Of Tests: "); 
    scanf("%d", &test_array_size);    
    
    for(int i = 0 ; i < test_array_size ; i++){
        printf("T%d: " , (i + 1)); 
        scanf("%d %d", &test_array[i][0] , &test_array[i][1]); 
        
    }
    
}

int main()
{

    get_values();
    
    for(int i = 0 ; i < test_array_size ; i++){
        
        route_array1[i][0] = test_array[i][0];
        route_array_size1[i] = 1;
        scan_route1(route_array1[i][0] , root , i , route_array_size1[i]);
        route_array2[i][0] = test_array[i][1];
        route_array_size2[i] = 1;
        scan_route2(route_array2[i][0] , root , i , route_array_size2[i]);
    } 
    
    // for(int i = 0; i < test_array_size ; i++){
    //     for(int j = 0 ; j < route_array_size1[i] ; j++){
    //         printf("%d " , route_array1[i][j]);
    //     }
    //     printf("\n");
    //     for(int j = 0 ; j < route_array_size2[i] ; j++){
    //         printf("%d " , route_array2[i][j]);
    //     }
    //     printf("\n\n");
        
    // }
    
    for(int i = 0; i < test_array_size ; i++){
        
        int index1 = 0;
        int index2 = 0;
        
        bool is_common_node_found = false; 
        for(int j = 0 ; j < route_array_size1[i] ; j++){
            
            for(int k = 0 ; k < route_array_size2[i]; k++){
    
                if(route_array1[i][j] == route_array2[i][k]){
                    index1 = j;
                    index2 = k;
                    is_common_node_found = true;
                    break;
                }    
    
            }
            
            if(is_common_node_found){
                break;
            }
            
        }
        
        // printf("i1 = %d   i2 = %d \n" , index1 , index2);
        
        for(int j = 0 ; j <= index1 ;j++ ){
            route_array[i][j] = route_array1[i][j];
            route_array_size[i]++;
        }
        for(int j = 0 ; j < index2 ;j++){
            route_array[i][index1 + j + 1] = route_array2[i][index2 - j - 1];
            route_array_size[i]++;
        }
        
    }
    
    for(int i = 0; i < test_array_size ; i++){
        
        for(int j = 0 ; j < route_array_size[i] ; j++){
            printf("%d " , route_array[i][j]);
        }
        printf("\n");
        
    }

    return 0;
}


void scan_route1(int current , int target , int route_array_index , int size){
    
    int new_current = 0;
    int new_target  = 0;
    int temp_size = size;
    int result = are_branches_of_same_node(current , target , &new_current , &new_target);
    if(result == 2){
        route_array1[route_array_index][temp_size] = new_current;
        temp_size++;
        route_array_size1[route_array_index] = temp_size;
    }else if(result == 1){
        route_array1[route_array_index][temp_size] = new_current;
        temp_size++;
        scan_route1(new_current , new_target , route_array_index , temp_size);       
    }
    
}

void scan_route2(int current , int target , int route_array_index , int size){
    
    int new_current = 0;
    int new_target  = 0;
    int temp_size = size;
    int result = are_branches_of_same_node(current , target , &new_current , &new_target);
    if(result == 2){
        route_array2[route_array_index][temp_size] = new_current;
        temp_size++;
        route_array_size2[route_array_index] = temp_size;
    }else if(result == 1){
        route_array2[route_array_index][temp_size] = new_current;
        temp_size++;
        scan_route2(new_current , new_target , route_array_index , temp_size);       
    }
    
}

int are_branches_of_same_node(int current, int target , int *new_current , int *new_target){
    
    int index = 0;
    
    for(int i = 0 ; i < sizeB ; i++){
        
        for(int j = 0 ; j < sizeItemA[B[i]] ; j++){
            
            if(current == A[B[i]][j]){
                
                index = B[i];
                break;
                
            }
            
        }
        
    }
    
    if(index == root){
        *new_current = index;
        *new_target = target;
        return 2;        
    }
    
    for(int i = 0 ; i < sizeItemA[index] ; i++){
        
        if(target == A[index][i]){
            *new_current = index;
            *new_target = target;
            return 2;
        }
    }
    
    *new_current = index;
    *new_target = target;        
    return 1;
    
}

