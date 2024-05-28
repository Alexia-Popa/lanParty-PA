#include "functii.h"
//task1
// Funcție pentru citirea jucătorilor
void citire_players(Player *players, int nr_players, FILE *fisier1) {
    char firstnm[50], secnm[50];
    int puncte;
    for (int i = 0; i < nr_players; i++) {
        fscanf(fisier1, "%s %s %d", firstnm, secnm, &puncte);
        players[i].nume = (char *)malloc((strlen(firstnm) + 1) * sizeof(char));
        players[i].prenume = (char *)malloc((strlen(secnm) + 1) * sizeof(char));
        strcpy(players[i].nume, firstnm); //copierea numelui jucatorului in memoria alocata
        strcpy(players[i].prenume, secnm); //copierea prenumelui jucatorului in memoria alocata
        players[i].puncte = puncte; //salvarea punctajului jucatorului
    }
}
// Funcție pentru citirea echipelor
void citire_echipe(Team **head, char *nume_team, int nr_players, FILE *fisier1) {
   
    Team *newteam = (Team *)malloc(sizeof(Team));
    newteam->nr_players = nr_players;
    newteam->nume_team = (char *)malloc((strlen(nume_team) + 1) * sizeof(char));
    strcpy(newteam->nume_team, nume_team);
    newteam->players = (Player *)malloc(nr_players * sizeof(Player));
    citire_players(newteam->players, nr_players, fisier1); //citirea datelor despre jucatorii echipei
    newteam->points = calcul_punctaj_echipa(newteam);
    newteam->next = *head; //adaugarea echipei la inceput de lista
    *head = newteam;
}

// Funcție pentru citirea listei de echipe
void citire_list(Team **head, int *nr_echipe, FILE *fisier1) {
    int n = 0;
    fscanf(fisier1, "%d", &n);
    *nr_echipe = n;
    int nr_players;
    char nume_team[50];
    for (int i = 0; i < n; i++) {
        fscanf(fisier1, "%d", &nr_players);
        fgetc(fisier1);
        fgets(nume_team, 50, fisier1);
        citire_echipe(head, nume_team, nr_players, fisier1); //adaugarea echipei in lista
    }
}

// Funcție pentru afișarea echipelor
void afisare(Team *head, int nr_echipe, FILE *fisier2) {
    for (int i = 0; i < nr_echipe; i++) {
        fprintf(fisier2, "%s\r\n", head->nume_team);
        head = head->next;
    }
}
//task2
// Funcție pentru calcularea punctajului unei echipe
float calcul_punctaj_echipa(Team *team) {
    int total_points = 0;
    for (int i = 0; i < team->nr_players; i++) {
        total_points += team->players[i].puncte;
    }
    return (float)total_points / team->nr_players; //media punctajului
}

// Funcție pentru verificarea dacă un număr este putere a lui 2
int este_putere_a_lui_2(int n) {
    return (n > 0) && !(n & (n - 1));
}

// Funcție pentru ștergerea jucătorilor dintr-o echipă
void sterge_jucatori(Team *team) {
    if (team == NULL || team->players == NULL) {
        return;
    }
    for (int i = 0; i < team->nr_players; i++) {
        free(team->players[i].nume); //eliberare mem
        free(team->players[i].prenume);
    }
    free(team->players);
    team->players = NULL;
    team->nr_players = 0; //eliberam memoria si resetam nr de jucatori ai echipei
}


void elimina_echipe(Team **head, int *nr_echipe) {
     if (*head == NULL) {
        printf("Lista de echipe este goală!\n");
        return;
    }
     
    while (!este_putere_a_lui_2(*nr_echipe)) {
       Team *prev = NULL, *current = *head, *min_team = *head, *min_prev = NULL;
       float min_punctaj = current->points; //initializarea punctajului  minim cu punctajul primei echipe din lista

       while (current != NULL) {
            float punctaj = current->points; //punctajul echipei curente
            if (punctaj < min_punctaj) {
                min_punctaj = punctaj;
                min_team = current;
                min_prev = prev;
            }
            prev = current;
            current = current->next;
       }
        if (min_team == *head) { //verificare daca echipa minima este prima din lista
			*head = (*head)->next;	
		} else {
			min_prev->next = min_team->next; //eliminare echipa min din lista
					}
        
        sterge_jucatori(min_team);
        free(min_team->nume_team);
        free(min_team); //eliberare memorie

        (*nr_echipe)--; // actualizare nr echipe
    } 
}
//TASK3
//formare coada
Queue* createQueue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, Team *team1, Team *team2) {
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->team1 = team1;
    temp->team2 = team2;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

Node* dequeue(Queue *q) {
    if (q->front == NULL)
        return NULL;
    Node *temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    return temp;
}
//stiva
Stack *createStack() {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

void push(Stack *stack, Team *team) {
    StackNode *node = (StackNode*)malloc(sizeof(StackNode));
    node->team = team;
    node->next = stack->top;
    stack->top = node;
}

Team* pop(Stack *stack) {
    if (stack->top == NULL)
        return NULL;
    StackNode *temp = stack->top;
    stack->top = stack->top->next;
    Team *team = temp->team;
    free(temp);
    return team;
}
//formare meciuri
void formare_meciuri(Queue *q, Team *head) {
    Team *current = head;
    while (current != NULL && current->next != NULL) { //trecerea prin lista pana la penultima echipa
        enqueue(q, current, current->next); //adaugarea meciului format de 2 echipe consecutive in coada
        current = current->next->next;
    }
}
//turneu

void sterge_invinsi(Stack *invinsi) {
    while (invinsi->top != NULL) {
        Team *team = pop(invinsi);
        sterge_jucatori(team);
        free(team->nume_team);
        free(team);
    }
}
//functie pt afisarea meciurilor dintr-o runda
void print_round(FILE *fisier2, Queue *meciuri, int round_no) {
    fprintf(fisier2, "\r\n--- ROUND NO:%d\r\n", round_no);
    Node *current = meciuri->front; //pointer dus la inceput de lista
    while (current != NULL) {// cat timp exista meciuri in coada
        fprintf(fisier2, "%-32s - %32s\r\n", current->team1->nume_team, current->team2->nume_team);
        current = current->next;
    }
}
//functie pt eliminarea caracterului newline dintr-un sir de caractere
void remove_newline(char *str) {
    size_t len = strlen(str); //determina lungimea sirului
    if (len > 0 && (str[len-3] == ' ')) {
        str[len-3] = '\0'; //elimina caracterul newline
		return;
    }
	str[len-2] = '\0'; //elimina caracterul newline
}
//functie pt eliminarea caracterului newline din numele tututor echipelor din lista
void remove_newline_head(Team *head) {
	while (head != NULL) {
		remove_newline(head->nume_team); //elimina caracterul newline din numele echipei
		head = head->next;
	}
}
//functie pt afisarea castigatorilor unei runde
void print_winners(FILE *fisier2, Stack *castigatori, int round_no) {
    fprintf(fisier2, "\r\nWINNERS OF ROUND NO:%d\r\n", round_no);
    StackNode *current = castigatori->top;
    while (current != NULL) {
        fprintf(fisier2, "%-33s -  %.2f\r\n", current->team->nume_team, current->team->points);
        current = current->next;
    }
}
//functie pt desfasurarea turneului si returnarea unei liste cu ultimele 8 echipe
Team *desfasoara_turneu(Team *head, FILE *fisier2) {
    Queue *meciuri = createQueue(); //coada meciuri
    Stack *castigatori = createStack();//stiva castigatori
    Stack *invinsi = createStack();//stiva invinsi
	Stack *tempStack = createStack();
	Team *temp = head;
	Team *top8=NULL;

	int nr_echipe = 0;
	int round_no = 1;
//calcul nr echipe
    while (temp != NULL) {
		(nr_echipe)++;
     	temp = temp->next;
     }
//desfasurarea turneului pana ramane o singura echipa
    while (nr_echipe > 1) {
        formare_meciuri(meciuri, head); //formam meciuri si le adaugam in coada
        print_round(fisier2, meciuri, round_no);
        while (meciuri->front != NULL) { //exista meciuri in coada
            Node *match = dequeue(meciuri);
            Team *team1 = match->team1;
            Team *team2 = match->team2; //bagam 2 echipe in meci
            free(match);

            if (team1->points > team2->points) {
                push(castigatori, team1);
                push(invinsi, team2);
                team1->points += 1;
            } else if (team1->points <= team2->points) {
                push(castigatori, team2);
                push(invinsi, team1);
                team2->points += 1;
            }
        }

        print_winners(fisier2, castigatori, round_no); //afisam castigarii rundei
        round_no++;

        sterge_invinsi(invinsi); //eliminarea invinsilor la final de runda

		head = NULL;
		while(castigatori->top != NULL) {
			push(tempStack, pop(castigatori)); //transferul castigatorilor intr-o stiva temporara
		}

        while (tempStack->top != NULL) {
            Team *team = pop(tempStack); //extrage echipa din stiva
            team->next = head;// adauga echipa la inceputul listei
            head = team;//actualizarea inceputului de lista
        }
        temp = head; //pointer la incept de lista
		nr_echipe = 0; //resetare nr
        while (temp != NULL) { //cat timp exista echipe in lista
            (nr_echipe)++;
            temp = temp->next;
        }

		if (nr_echipe == 8) { // verificam daca nr echipelor este 8, daca da, cream o lista noua cu ele si o returnam
			temp = head;
        	while (temp != NULL) {
            	Team *team = malloc(sizeof(Team));
				team->nume_team = malloc(sizeof(char) * strlen(temp->nume_team));
				strcpy(team->nume_team, temp->nume_team);
				team->points = temp->points;
				team->next = top8; // adaugarea echipei in lista de 8
				top8 = team;
				
				temp=temp->next;
        	}
		}
    }

    sterge_invinsi(invinsi);
    free(meciuri);
   	free(castigatori);
    free(invinsi);
//eliberare mem
	return top8;
}
//task4
BSTNode* createBSTNode(Team *team) {
    BSTNode *node = (BSTNode*)malloc(sizeof(BSTNode));
    if (!node) {
        printf("Memory allocation failed for BSTNode\n");
        exit(1);//iesirea din program cu cod de eroare
    }
    node->team = team; //nod=echipa data
    node->left = node->right = NULL;//fii=null
    return node;
}

BSTNode* insertBST(BSTNode *root, Team *team) {
    if (root == NULL) {
        return createBSTNode(team);
    }
    if (team->points > root->team->points) { //verificam daca punctajul echipei este mai mare decat pnctajul echipei din nodul curent
        root->left = insertBST(root->left, team); //inserare in subarborele stang
    } else if (team->points < root->team->points) {////verificam daca punctajul echipei este mai mic decat pnctajul echipei din nodul curent
        root->right = insertBST(root->right, team);//inserare in subarborele drept
    } else {
        // În cazul în care punctajul este egal, sortăm după nume în ordine descrescătoare
        if (strcmp(team->nume_team, root->team->nume_team) > 0) {
            root->left = insertBST(root->left, team);
        } else {
            root->right = insertBST(root->right, team);
        }
    }
    return root;
}
//functie pentru afisarea arborelui binar BST in ordine descrescatoare si actualizarea listei cu top8 echipe din arbore
    void printBSTDesc(BSTNode *root, FILE *fout, Team **top8) {
    if (root != NULL) {
        printBSTDesc(root->left, fout, top8);
        fprintf(fout, "%-33s -  %.2f\r\n", root->team->nume_team, root->team->points);
        //crearea unei noi echipe si actualizarea top8
		Team *team = malloc(sizeof(Team));
		team->nume_team = root->team->nume_team;
		team->points = root->team->points;
		team->next=*top8;
		*top8=team;
		printBSTDesc(root->right, fout, top8);
    }
}
//task5
ARB_ECHB* creare_arb_ech(Team *team) {
    ARB_ECHB *node = (ARB_ECHB*)malloc(sizeof(ARB_ECHB));
    if (!node) {
        printf("Memory allocation failed for ARB_ECHB\n");
        exit(1); //iesire program cu cod de eroare
    }
    node->team = team;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}
// functie pentru determinarea inaltimii unui nod intr-un arbore AVL
int height(ARB_ECHB *node) {
    if (node == NULL)
        return 0;
    return node->height;
}
//functie pt obtinerea factorului de echilibru al unui nod intr-un arbore AVL
int getBalance(ARB_ECHB *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right); //diferenta dintre subarbori
}
//functie pt rotirea la dreapta
ARB_ECHB* rightRotate(ARB_ECHB *y) {
    ARB_ECHB *x = y->left;
    ARB_ECHB *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}
//functie pt rotirea la stanga
ARB_ECHB* leftRotate(ARB_ECHB *x) {
    ARB_ECHB *y = x->right;
    ARB_ECHB *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}
//functie pt inserarea uni nod intr-un arbore AVL
ARB_ECHB* insertARB_ECHB(ARB_ECHB *node, Team *team) {
    if (node == NULL)
        return creare_arb_ech(team);
//comparama punctajele echipelor pentru a determina pozitia de inserare in arbore
    if (team->points > node->team->points)
        node->left = insertARB_ECHB(node->left, team);
    else if (team->points < node->team->points)
        node->right = insertARB_ECHB(node->right, team);
    else { //in cazul in care punctajele sunt egale, comparam numele echipelor
        if (strcmp(team->nume_team, node->team->nume_team) > 0)
            node->left = insertARB_ECHB(node->left, team);
        else
            node->right = insertARB_ECHB(node->right, team);
    }
// Actualizarea inaltimii nodului curent
node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

// Calcularea factorului de echilibru al nodului curent
int balance = getBalance(node);

// Cazul Left Left
// Daca factorul de echilibru este mai mare de 1 si punctele echipei sunt mai mici decat punctele echipei din nodul stang sau daca punctele sunt egale si numele echipei este mai mare decat numele echipei din nodul stang
if (balance > 1 && (team->points < node->left->team->points || 
                   (team->points == node->left->team->points && strcmp(team->nume_team, node->left->team->nume_team) > 0))) {
    // Realizeaza rotirea spre dreapta
    return rightRotate(node);
}

// Cazul Right Right 
// Daca factorul de echilibru este mai mic de -1 si punctele echipei sunt mai mici decat punctele echipei din nodul drept sau daca punctele sunt egale si numele echipei este mai mic decat numele echipei din nodul drept
if (balance < -1 && (team->points < node->right->team->points ||
                    (team->points == node->right->team->points && strcmp(team->nume_team, node->right->team->nume_team) < 0))) {
    // Realizeaza rotirea spre stanga
    return leftRotate(node);
}

// Cazul Left Right 
// Daca factorul de echilibru este mai mare de 1 si punctele echipei sunt mai mari decat punctele echipei din nodul stang sau daca punctele sunt egale si numele echipei este mai mic decat numele echipei din nodul stang
if (balance > 1 && (team->points > node->left->team->points ||
                   (team->points == node->left->team->points && strcmp(team->nume_team, node->left->team->nume_team) < 0))) {
    // Realizeaza rotirea spre stanga pe subarborele stang
    node->left = leftRotate(node->left);
    // Realizeaza rotirea spre dreapta
    return rightRotate(node);
}

// Cazul Right Left 
// Daca factorul de echilibru este mai mic de -1 si punctele echipei sunt mai mici decat punctele echipei din nodul drept sau daca punctele sunt egale si numele echipei este mai mare decat numele echipei din nodul drept
if (balance < -1 && (team->points < node->right->team->points ||
                    (team->points == node->right->team->points && strcmp(team->nume_team, node->right->team->nume_team) > 0))) {
    // Realizeaza rotirea spre dreapta pe subarborele drept
    node->right = rightRotate(node->right);
    // Realizeaza rotirea spre stanga
    return leftRotate(node);
}


return node;
}
   
void printLevel(ARB_ECHB *root, int level, FILE *fisier2){
    if (root == NULL)
        return;
    if (level == 1) {
        fprintf(fisier2, "%s\r\n", root->team->nume_team); //daca nivelul este 1, imprimam numele echipei
    } else if (level > 1) {
        printLevel(root->left, level - 1, fisier2);//recursiv, apelam functia pt subarborele stang
        printLevel(root->right, level - 1, fisier2);//recursiv, apelam functia pt subarborele drept
    }
}

int getMaxHeight(ARB_ECHB *root) {
    if (root == NULL) 
        return 0;
    int leftHeight = getMaxHeight(root->left);//inaltimea maxima subarbore stang
    int rightHeight = getMaxHeight(root->right);//inaltimea maxima subarbore drept
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;//returnam inaltimea maxima
}
