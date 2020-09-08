#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct place {
    int code, pop, intercode;
    char * state, * name;
    float lat, lgt, dist, area;
};

struct place * make_place(int code, char * state, char * name, int pop, float area, float lat, float lgt, int intercode, float dist) {
    struct place * p = (struct place *)malloc(sizeof(struct place));
    p -> code = code;
    p -> state = state;
    p -> name = name;
    p -> pop = pop;
    p -> area = area;
    p -> lat = lat;
    p -> lgt = lgt;
    p -> intercode = intercode;
    p -> dist = dist;
    return p;
};

struct node {
    struct node * next;
    struct place * data;
};

struct node * make_node(struct place * p) {
    struct node * n = (struct node *)malloc(sizeof(struct node));
    n -> next = NULL;
    n -> data = p;
    return n;
};

void add(struct place * p, struct node ** list) {
    struct node * n  = make_node(p);
    if (*list == NULL) {
        *list = n;
        return;
    }
    n -> next = *list;
    *list = n;
}

char * substr(char * s, int pos, int len) {
    char * ptr;
    int i;

    ptr = malloc(len+1);

    for (i = 0; i < len; i++) {
        ptr[i] = s[i+pos-1];
    }

    ptr[i] = '\0';

    return ptr;
}

void display(struct place * p) {
    printf("All info: %d, %s, %s, %d, %f, %f, %f, %d, %f\n", p->code,p->state,p->name,p->pop,p->area,p->lat,p->lgt,p->intercode,p->dist);
    return;
}

char * trim(char * s) {
    char * end;
    end = s + strlen(s) - 1;

    while(isspace((char)*end)) end--;
    end[1] = '\0';
    return s;
}

void interactive(struct node * list) {
    while(1) {
        char n[51];
        char st[4];
        struct node * ptr;
        struct node * templist = NULL;
        int found = 0;

        printf("Enter place name, 'end' to terminate: ");
        fgets(n,51,stdin);
        n[strlen(n)-1] = '\0';
        if(strcmp(n,"end")==0)
            return;

        ptr = list;
        while(ptr != NULL) {
            if (strcmp(ptr->data->name,n) == 0){
                printf("%s\n",ptr->data->state);
                add(ptr->data, &templist);
                found = 1;
            }
            ptr = ptr -> next;
        }
        if(!found) {
            printf("No such place\n");
            continue;
        }
        printf("Enter which state: ");
        fgets(st,4,stdin);
        st[strlen(st)-1] = '\0';
        ptr = templist;
        while(ptr != NULL) {
            if (strcmp(ptr->data->state,st) == 0) {
                display(ptr->data);
                break;
            }
            ptr = ptr -> next;
        }

    }
}

int main() {
    struct node * list = NULL;
    FILE * fin;

    char buff[255];
    char * state, *name;
    int code, pop, intercode;
    float area,lat,lgt,dist;

    struct place * p;

    fin = fopen("/home/www/class/een318/named-places.txt", "r");
    if (fin == NULL) {
        printf("file does not exist\n");
        exit(1);
    }

    while (1) {
        char * n = fgets(buff, 255, fin);
        if (n == NULL)
            break;

        code = atoi(substr(buff,1,8));
        state = substr(buff,9,2);
        name = trim(substr(buff, 11, 49));
        pop = atoi(substr(buff,61,7));
        area = atof(substr(buff,68,14));
        lat = atof(substr(buff,83,10));
        lgt = atof(substr(buff,94,11));
        intercode = atoi(substr(buff,106,5));
        dist = atof(substr(buff,112,8));

        p = make_place(code,state,name,pop,area,lat,lgt,intercode,dist);
        add(p,&list);
    }

    fclose(fin);

    interactive(list);
}