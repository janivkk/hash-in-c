/* 

    https://www.youtube.com/watch?v=2Ti5yvumFTU&t=309s
    
    Understanding and Implementation -> Hash Tables in C

    by Jacob Sorber

    written by Janek Snieg

 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10
#define DELETED_NODE (Person*)(0xFFFFFFFFFFFFFFFFUL)

typedef struct {
    char name[MAX_NAME];
    int age;
} Person;

/*Declared functions and its arguments.*/
Person * hash_table[TABLE_SIZE];

unsigned int hash(char* name);

void init_hash_table();

void print_hash_table();

bool hash_table_insert(Person *p);

Person *hash_table_lookup(char* name);

Person *hash_table_delete(char *name);

int main() {
    init_hash_table();
    print_hash_table();

    Person janek = {.name = "Janek", .age = 64};
    Person agata = {.name = "Agata", .age = 128};
    Person martin = {.name = "Martin", .age = 256};

    hash_table_insert(&janek);
    hash_table_insert(&agata);
    hash_table_insert(&martin);

    print_hash_table();

    Person *tmp = hash_table_lookup("anthony");

    if (tmp == NULL) { printf("Not found!\n"); }
    else { printf("Found! %s\n", tmp->name); }

    printf("Deleted!\n");
    hash_table_delete("Janek");

    print_hash_table();

    return 0;
}

/*Initialisation of the functions and their actual functionaility.*/

unsigned int hash(char* name) {
    int length = strnlen(name, MAX_NAME);

    unsigned int hash_value = 0;

    for (int i = 0; i < length; i++) {
        hash_value += name[i]; 
        hash_value = (hash_value * name[i]) % TABLE_SIZE; 
    }
    return hash_value;
}

void init_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
    //  table is empty
}

void print_hash_table() {
    printf("Start\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] == NULL ) { 
            printf("\t%i\t-----\n", i); 
        } else if (hash_table[i] == DELETED_NODE) {
            printf("\t%i\t<deleted>\n", i);
        } else {
            printf("\t%i\t%s\n", i, hash_table[i]->name);
        } 
    }
    printf("End\n");
}

bool hash_table_insert(Person *p) {
    if (p == NULL) { return false; }
    int index = hash(p->name);
    for (int i = 0; i < TABLE_SIZE; i++) {

        int try = (i + index) % TABLE_SIZE;
        
        if (hash_table[try] == NULL || hash_table[try] == DELETED_NODE) {
            hash_table[try] = p;
            return true;
        }
    }
    return false;
}

Person *hash_table_lookup(char* name) {
    int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int try = (index + i) % TABLE_SIZE;

        if (hash_table[try] == NULL) return false;

        if (hash_table[try] == DELETED_NODE) continue; 

        if (strncmp(hash_table[try]->name, name, TABLE_SIZE) == 0) {
            return hash_table[try];
        }
    }
    return NULL;
}

Person *hash_table_delete(char *name) {
    int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; i++) {

        int try = (index + i) % TABLE_SIZE;

        if (hash_table[try] == NULL) { return NULL; }

        if (hash_table[try] == DELETED_NODE) { continue; }

        if (strncmp(hash_table[try]->name, name, TABLE_SIZE) == 0) {
            Person *tmp = hash_table[try];
            hash_table[try] = DELETED_NODE;
            return tmp;
        }
    }    
    return NULL; 
}
