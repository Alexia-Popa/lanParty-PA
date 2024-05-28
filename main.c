#include "functii.h"

#define TASKS 5

int main(int argc, char *argv[]) {
    Team *head = NULL;
    int *task;
    int nr_echipe = 0;
    Team * StackTop8=NULL;
    FILE *fisier1, *fisier2, *ch;

    ch = fopen(argv[1], "r");
    fisier1 = fopen(argv[2], "r");
    fisier2 = fopen(argv[3], "w");
    

    task = (int *)malloc(sizeof(int) * TASKS);
    for (int i = 0; i < TASKS; i++)
		fscanf(ch, "%d", &task[i]);

    fclose(ch);

	citire_list(&head, &nr_echipe, fisier1);
	remove_newline_head(head); // reduce newline, space de la final.
	Team *top8 = NULL;
	Team *newTop8 = NULL;
    if (task[0] == 1 && task[1] == 0 ) {
        afisare(head, nr_echipe, fisier2);
    }
    
	if(task[1]==1) {
		elimina_echipe(&head,&nr_echipe);
        afisare(head,nr_echipe,fisier2);
    }
	if(task[2]==1)
   {
    top8 = desfasoara_turneu(head, fisier2);
	}

	if (task[3] == 1) {
		BSTNode *root = NULL;
		fprintf(fisier2, "\r\nTOP 8 TEAMS:\r\n");
		newTop8 = top8;
		while (top8 != NULL) {
			root= insertBST(root, top8);
			top8 = top8->next;
		}
		printBSTDesc(root, fisier2, &top8);
	}

	if (task[4] == 1) {
    ARB_ECHB *root = NULL;
    fprintf(fisier2, "\r\nTHE LEVEL 2 TEAMS ARE:\r\n");
    
    // Inverseaza ordinea
    while (top8 != NULL) { //parcurgere lista cu primele 8 echipe
        Team *team = malloc(sizeof(Team));
        team->nume_team = top8->nume_team;
        team->points = top8->points;
        team->next = newTop8;
        newTop8 = team;
        top8 = top8->next;
    }
    while (newTop8 != NULL) {
        root = insertARB_ECHB(root, newTop8);
        newTop8 = newTop8->next;
    }

    // Verifica daca arborele are cel putin 3 niveluri
    if (getMaxHeight(root) >= 3) {
        printLevel(root, 3, fisier2);
    } else {
        fprintf(fisier2, "Arborele nu are suficiente niveluri pentru a afișa echipele de pe nivelul 2.\r\n");
    }
}
    return 0;
}
