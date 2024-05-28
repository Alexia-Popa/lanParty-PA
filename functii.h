#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct player {
    char *nume;
    char *prenume;
    int puncte;
    struct player *next;
};typedef struct player Player;


struct team {
    int nr_players;
    char *nume_team;
    struct player *players;
    float points;
    struct team *next;
};typedef struct team Team;

typedef struct Node {
    Team *team1;
    Team *team2;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *front;
    Node *rear;
} Queue;

typedef struct StackNode {
    Team *team;
    struct StackNode *next;
} StackNode;

typedef struct Stack {
    StackNode *top;
} Stack;

typedef struct BSTNode {
    Team *team;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;
typedef struct ARB_ECHB {
    Team *team;
    struct ARB_ECHB *left;
    struct ARB_ECHB *right;
    int height;
} ARB_ECHB;

void* allocate_memory(size_t size);

void citire_players(Player* Players, int nr_players, FILE* fisier1);
void citire_echipe(Team** head, char* nume_team, int nr_players, FILE* fisier1);
void citire_list(Team** head, int* nr_echipe,FILE* fisier1);
void afisare(Team* head, int nr_echipe, FILE* fisier2);

float calcul_punctaj_echipa(Team *team); 
int este_putere_a_lui_2(int n);
void sterge_jucatori(Team *team) ;
void elimina_echipe(Team **head, int *nr_echipe);

Queue* createQueue() ;
void enqueue(Queue *q, Team *team1, Team *team2) ;
Node* dequeue(Queue *q);
Stack* createStack();
void push(Stack *stack, Team *team);
void formare_meciuri(Queue *q, Team *head) ;
void sterge_jucatori(Team *team);
void sterge_invinsi(Stack *invinsi);
void print_round(FILE *fisier2, Queue *meciuri, int round_no);
void print_winners(FILE *fisier2, Stack *castigatori, int round_no);
Team *desfasoara_turneu(Team *head, FILE *fisier2);
void remove_newline(char *str);
void remove_newline_head(Team *head);
BSTNode* createBSTNode(Team *team);
BSTNode* insertBST(BSTNode *root, Team *team);
void printBSTDesc(BSTNode *root, FILE *fout, Team **top8);
ARB_ECHB* creare_arb_ech(Team *team);
int height(ARB_ECHB *node);
int getBalance(ARB_ECHB *node);
ARB_ECHB* rightRotate(ARB_ECHB *y);
ARB_ECHB* leftRotate(ARB_ECHB *x);
ARB_ECHB* insertARB_ECHB(ARB_ECHB *node, Team *team);
void printLevel(ARB_ECHB *root, int level, FILE *fisier2);
int getMaxHeight(ARB_ECHB *root);
