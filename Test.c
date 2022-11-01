
#include <stdio.h>
#include "stdbool.h"

// int node[12][5]       = {{0}, {0}, {0}, {0}, {0}, {2 , 4}, {0}, {0}, {0}, {0}, {5 , 3}, {0}};
// int sizeNodeItem[12]  = { 0 ,  0 ,  0 ,  0 ,  0 ,  2     ,  0 ,  0 ,  0 ,  0 ,  2     ,  0 };
// int parent[12]        = {5 , 10};
// int sizeNode          = 11;
// int sizeParent        = 2;
// int root              = 10;
// int test_array[10][2] = {{4 , 3} , {4 , 2} , {3 , 2} , {2 , 3}};
// int test_array_size   = 4;

int node[1002][1002]       = {{0}};
int sizeNodeItem[1002]     = { 0 };
int parent[1002]           = { 0 };
int sizeNode               = 0;
int sizeParent             = 0;
int root                   = 0;
int test_array[1000002][2] = {{}};
int test_array_size        = 0;

int route_array [1002][1002] = {{0}};
int route_array1[1002][1002] = {{0}};
int route_array2[1002][1002] = {{0}};

int route_array_size [1002]  = { 0 };
int route_array_size1[1002]  = { 0 };
int route_array_size2[1002]  = { 0 };

void scan_route(int current , int target , int route_array_index , int size, int (*temp_route)[1002] , int *temp_route_size);
int  are_branches_of_same_node(int current, int target , int *new_current , int *new_target);

void append_to_parent_array(int value){
    
    if(sizeParent == 0){
        parent[sizeParent] = value;
        sizeParent++;
    }else{
        int is_in_parent = false;
        for(int j = 0 ; j < sizeParent ; j++){
            
            if(value == parent[j]){
                is_in_parent = true;
                break;
            }
            
        }
        if(!is_in_parent){
            parent[sizeParent] = value;
            sizeParent++;
        }
    }
    
}

void get_values(){
    
    int number_of_nodes = 0;
    int input_array[1002][3];
    
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
            node[temp_index][sizeNodeItem[temp_index]] = input_array[i][0];
            sizeNodeItem[temp_index]++;
            
            if( (temp_index + 1) > sizeNode){
                sizeNode = temp_index + 1;
            }
        }
        
        if(input_array[i][2] == 1){
            append_to_parent_array(input_array[i][0]);
        }
        
    }
    
    printf("Parent = {");
    for(int i = 0 ; i < sizeParent ; i++){
        if(i < sizeParent - 1){
            printf("%d," , parent[i]);    
        }else{
            printf("%d" , parent[i]); 
        }
        
    } 
    printf("}\n");
    
    printf("Node={");
    for(int i = 0 ; i < sizeNode ; i++){
        printf("{");
        for(int j = 0 ; j < sizeNodeItem[i] ; j++){
            if(j < sizeNodeItem[i] - 1){
                printf("%d," , node[i][j]);    
            }else{
                printf("%d" , node[i][j]); 
            }
            
        }
        printf("}");
        
    }
    printf("}\n");
    
    printf("Root = %d\nNode Size = %d\nParent Size = %d\n" , root , sizeNode, sizeParent);

    printf("Node Item Size = {");
    for(int i = 0 ; i < sizeNode ; i++){
        if(i < sizeNode - 1){
            printf("%d," , sizeNodeItem[i]);    
        }else{
            printf("%d" , sizeNodeItem[i]); 
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
        scan_route(route_array1[i][0] , root , i , route_array_size1[i], route_array1 , route_array_size1);
        route_array2[i][0] = test_array[i][1];
        route_array_size2[i] = 1;
        scan_route(route_array2[i][0] , root , i , route_array_size2[i], route_array2 , route_array_size2);
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


void scan_route(int current , int target , int route_array_index , int size, int (*temp_route)[1002] , int *temp_route_size){
    
    int new_current = 0;
    int new_target  = 0;
    int temp_size = size;
    int result = are_branches_of_same_node(current , target , &new_current , &new_target);
    if(result == 2){
        temp_route[route_array_index][temp_size] = new_current;
        temp_size++;
        temp_route_size[route_array_index] = temp_size;
    }else if(result == 1){
        temp_route[route_array_index][temp_size] = new_current;
        temp_size++;
        scan_route(new_current , new_target , route_array_index , temp_size , temp_route , temp_route_size);       
    }
    
}

int are_branches_of_same_node(int current, int target , int *new_current , int *new_target){
    
    int index = 0;
    
    for(int i = 0 ; i < sizeParent ; i++){
        
        for(int j = 0 ; j < sizeNodeItem[parent[i]] ; j++){
            
            if(current == node[parent[i]][j]){
                
                index = parent[i];
                break;
                
            }
            
        }
        
    }
    
    if(index == root){
        *new_current = index;
        *new_target = target;
        return 2;        
    }
    
    *new_current = index;
    *new_target = target;        
    return 1;
    
}

