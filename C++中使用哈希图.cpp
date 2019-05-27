

	#include "pch.h"
	#include <iostream>
	using namespace std;
	#define Length 10 // the number of the node

	struct node
	{
		int value;
		struct node* next;
	};//the node 

	struct hash_map {
		struct node** link_list; // use a pointer which point a pointer to ensure its a link list
		int count;
	};//the hash_map


	void init(hash_map *hashmap) {
		hashmap->link_list = (node**)malloc(Length * sizeof(node*)); 
		hashmap->count = Length;

		for (int i = 0; i < Length; i++) {
			hashmap->link_list[i] = (node*)malloc(Length * sizeof(node));
		
		}
		for (int i = 0; i < Length; i++) {
			hashmap->link_list[i]->value = NULL; // give a inital value of every node
			if (i != Length - 1)				//make the node array become a link list
				hashmap->link_list[i]->next = hashmap->link_list[i + 1];
			else
				hashmap->link_list[i]->next = nullptr;
		}
	}//init the hash_map

	int get_hash(int value,hash_map* hashmap) {
		return value % hashmap->count;
	}// get the hash value of a node 


	void enlargeSpace(hash_map* hashmap) {
		hashmap->count = 2 * hashmap->count;
		int *arr = (int*)malloc(hashmap->count * sizeof(int));
		for (int i = 0; i < hashmap->count; i++) {
			arr[i] = NULL;
		}
		int hash;
		for (int i = 0; i < hashmap->count / 2; i++) {
			hash = get_hash(hashmap->link_list[i]->value, hashmap);
			while (arr[hash] != NULL) {
				hash = get_hash(++hash, hashmap);
			}
			arr[hash] = hashmap->link_list[i]->value;
		}
		hashmap->link_list = (node**)malloc(hashmap->count*sizeof(node*));
		for (int i = 0; i < hashmap->count; i++) {
			hashmap->link_list[i] = (node*)malloc(sizeof(node));
			hashmap->link_list[i]->value = arr[i];
		}
		for (int i = 0; i < hashmap->count; i++) {
			if (i != hashmap->count - 1)				//make the node array become a link list
				hashmap->link_list[i]->next = hashmap->link_list[i + 1];
			else
				hashmap->link_list[i]->next = nullptr;
		}

	}// enlarge the space of the array

	int createHashMap(int data,hash_map* hashmap) {
		for(int i = 0;i<hashmap->count;i++)
			if(hashmap->link_list[i]->value==NULL)
				goto a;
		enlargeSpace(hashmap);
	a:
		int hash_value = get_hash(data,hashmap); // get the hash value of the node's value
		while (hashmap->link_list[hash_value]->value != NULL) { // if there is a value in the address, re-hash it
			hash_value = get_hash(++hash_value,hashmap);
		}
		hashmap->link_list[hash_value]->value = data; // store the value of the node in to the hash_map
		return 0;
	}//


	int find(hash_map* hashmap,int data) {
		int hash_value = get_hash(data,hashmap);
		int tempData = data;
		int first_hash_value = hash_value;
		while (hashmap->link_list[hash_value]->value != data) {
			tempData++;
			hash_value = get_hash(tempData,hashmap);
			if (hashmap->link_list[hash_value]->value == NULL || first_hash_value == hash_value)// if we do not find the data, return -1
				return -1;
		}
		return hash_value;

	}

	void removeNode(hash_map* hashmap, int hash_value) {
		if (hash_value == -1) // if the value is not in the link list
			return;
		/*
		hashmap->link_list[hash_value - 1].next = hashmap->link_list[hash_value].next;*/
		hashmap->link_list[hash_value - 1]->next = hashmap->link_list[hash_value]->next;
		hashmap->link_list[hash_value] = nullptr;
	}

	int main()
	{
		int arr[10] = { 1, 3, 4, 23, 64, 423,5643,543, 21, 123 };
		hash_map hashmap;
		node* head;

		head = (node*)malloc(sizeof(node));
	
		init(&hashmap);
		int j = 0;
		while (j < Length) {
			if (hashmap.link_list[j] != nullptr) {

				head = hashmap.link_list[j];
				break;
			}
			j++;
		}//ensure the head is the first one of the link list

		for (int i = 0; i < Length; i++)
			createHashMap(arr[i],&hashmap);
		for (int i = 300000; i < 300020; i++)
			createHashMap(i,&hashmap);
		printf("the init link list is:\n");

		while (head != nullptr) {
			printf("%d\t", head->value);
			head = head->next;
		}//print the link list before we remove anyone
		j = 0;

		while (j < Length) {
			if (hashmap.link_list[j] != nullptr) {

				head = hashmap.link_list[j];
				break;
			}
			j++;
		}//ensure the head is the first one of the link list


		removeNode(&hashmap, find(&hashmap, 423));
		removeNode(&hashmap, find(&hashmap, 1));

		printf("\n After remove a node:\n");
		while (head != nullptr) {
			if(head->value!=NULL)
				printf("%d\t", head->value);
			head = head->next;
		}//print the result of the link list after we remove 423 and 1

	}


