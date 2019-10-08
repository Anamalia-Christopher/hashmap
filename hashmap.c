
/*
Hashmaps have a key value pair. My hastmap is going to be an object. 
This object is going to contain items that contain information about the hashmap. 
But most importantly, contains the array that has the key value pair. 

When one wants to put in a key pair, 
it hashes the key and then uses the hash to get an index for keeping it in the hash list. 

functions 

hash 
put 
get 
delete ** - tentative 
collision detection - tentative 

Object 
Hashmap
    -size
    - hash list
        - Object hash position
            -size 
            -array 

Example hashmap object 

Hashmap{
    size:5
    hashlist:[(object-Hashposition), (object-Hashposition), (object-Hashposition)]
                        |
                        |
                        ->Hashposition{
                            size:1
                            array:["hashmap", "quite a nice data structure"]
                        }

}


*/


#include <stdio.h>
#include <stdlib.h>

#define HASH_PRIME 51;
#define CONSTANT_OF_HASH_FUNCTION 21

void put(char *, char *);
void update(char *, char *);
void* get(char *);
void swap(char * , char * , char *, char * );

//object for key-vaue pair 
typedef struct{
    int size;
    char *key_value_pair[10];
}pair_array;

// hashmap object
typedef struct{
    int size;
    int current_size;
    pair_array hashmap[10];
}Hashmap;


////////////////////////
/*HASHMAP INSTANCE*/
Hashmap hashmap;



///////////////////////

// converts the string to unsigned long
// O(n)
int numerify(char* s, int sum){
    if (*s=='\0'){
        return sum;
    }
    sum = sum + (int)*s;
    ++s;

    return numerify(s, sum);
}

// O(1) = for the arithmetic 
// n is the number of key value pair to be considered in the hashmap
int hash(char *key, unsigned int n){
    int hasher = (CONSTANT_OF_HASH_FUNCTION * numerify(key, 0))%HASH_PRIME;
    return hasher % n ;
}

void put(char *key, char *value){
    hashmap.current_size++;

    int position = hash(key,hashmap.size);
    // printf("This is the number of element in the value pair %d \n",hashmap.hashmap[position].size);
    pair_array *arr =  &hashmap.hashmap[position];
    
    // printf("%d\n", arr->size);
    arr->key_value_pair[arr->size*2] = key;
    arr->key_value_pair[arr->size*2 + 1] = value;
    arr->size++;
    // printf("%d\n", arr->size);
    
}

void update(char *key , char *value){
    int position = hash(key,hashmap.size);

    pair_array *arr =  &hashmap.hashmap[position];
   
    for(unsigned int i=0; i<=arr->size; i++){

        if (arr->key_value_pair[i*2] == key){
            arr->key_value_pair[i*2+1] = value;
        }
    }
}


void* get(char *key){
    // hash the key and get the corresponding position
    int position = hash(key,hashmap.size);

    // get the pair array object that stores the key value pair for the particular key hash 
    pair_array *arr =  &hashmap.hashmap[position];
    
    // search the array to find the key in the array 
    for(unsigned int i=0; i<arr->size; i++){

        if (arr->key_value_pair[i*2] == key){
            // return the corresponding  value of the key provided
            return arr->key_value_pair[i*2+1];

        }
    }
// if not item is found, return a null
    return NULL;

}


void delete(char *key){
    // hash the key and get the corresponding position
    int position = hash(key,hashmap.size);

    // get the pair array object that stores the key value pair for the particular key hash 
    pair_array *arr =  &hashmap.hashmap[position];
    
    // search the array to find the key in the array 
    for(unsigned int i=0; i<arr->size; i++){

        if (arr->key_value_pair[i*2] == key){
            // return the corresponding  value of the key provided
             if (arr->size == 1){
                 
                arr->size--;


                return;
             }
             else
             {
                 swap(arr->key_value_pair[i*2], arr->key_value_pair[i*2], arr->key_value_pair[(arr->size-1)*2], arr->key_value_pair[(arr->size-1)*2+1]);
                 arr->size--;
                 printf("check like ejob oo\n");
             }
             

        }
    }
// if not item is found, return a null


    return;
}

void swap(char * old_key, char * old_value, char *new_key, char * new_value){
    *old_key = *old_key ^ *new_key;
    *new_key = *old_key ^ *new_key;
    *old_key = *old_key ^ *new_key;

    *old_value = *old_value ^ *new_value;
    *new_value = *old_value ^ *new_value;
    *old_value = *old_value ^ *new_value;

    
}


int main() {
    hashmap.size = 10;
   put("chris", "anamalia");
   put("sammy", "ashesi");
   put("something", "earlier is better");
   put("this", "ok lets us figure it out");
   get("chris");
   get("sammy");
   delete("chris");
   delete("chris");
   get("something");
   char *c = get("this");

    printf("%s\n", c);
   update("sammy", "kind of done with the assignment");
   get("sammy");

    return 0;
}
