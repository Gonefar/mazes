#include "head.h"
#include "func.c"

int main()
{
	element *mazes = Malloc(20 * 20 * sizeof(element));
	coord *init_size = Malloc(sizeof(coord));
	char sname = 'S', hname = 'H';
	element *horace = NULL, *snail = NULL;

	printf("Please input the row and col:\n");
	scanf("%d%d", &(init_size->row), &(init_size->col) );
	Init_Mazes(mazes, init_size);

	horace = Find_Object(mazes, init_size, hname);//error processed in the function
	snail = Find_Object(mazes, init_size, sname);

	printf("Horace:(%d, %d), snail:(%d, %d)\n", horace->row, horace->col, snail->row, snail->col);
	Search_Path(mazes, init_size, horace, snail);

}
