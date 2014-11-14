#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct _coord
{
	int row;
	int col;
}coord;

typedef struct _element
{
	int row;
	int col;
	int path_length;
	int lflag;//flag 0: before search, flag 1: after search
	int sflag;
	int rflag;
	int uflag;
	int dflag;
	char name;

	struct _element *up;
	struct _element *down;
	struct _element *right;
	struct _element *left;
}element;

