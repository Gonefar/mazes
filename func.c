void *Malloc(int size)
{
	void *temp = malloc(size);

	if(temp == NULL)
		{
			printf("Allocate address error\n");
			return NULL;
		}
	return temp;
}

void Print_Node(element *ele)
{
	if(ele != NULL)
		{
			printf("(%d, %d)-->", ele->row, ele->col);
		}
	else
		{
			printf("node is NULL\n");
		}
}

void Show_Path(element *horace)
{
	
	
	
	if(horace->name == 'S')
		{
			printf("(%d, %d)\n", horace->row, horace->col);
			return;
		}
	
	Print_Node(horace);
	if(horace->left != NULL && horace->left->rflag == 1)
		{

			horace = horace->left;
			Show_Path(horace);
			return;
		}
	else if(horace->up != NULL && horace->up->dflag == 1)
		{
			horace = horace->up;
			Show_Path(horace);
			return;
		}
	else if(horace->right != NULL && horace->right->lflag == 1)
		{
			horace = horace->right;
			Show_Path(horace);
			return;
		}
	else if(horace->down != NULL && horace->down->uflag == 1)
		{
			horace = horace->down;
			Show_Path(horace);
			return;
		}

}
void Set_Node_Relation(element *ele, coord *init_size)
{
	element *temp = ele;
	if( (temp->row == 0) && (temp->col == 0) )
		{
				temp->left = NULL;
				temp->up   = NULL;
				temp->right = temp + 1;
				temp->down = temp + init_size->col;
								
		}
	else if( (temp->row == 0 ) && (temp->col == init_size->col-1) )
		{
				temp->left = temp - 1;
				temp->up   = NULL;
				temp->right = NULL;
				temp->down = temp + init_size->col;
														
		}
	else if( (temp->row == init_size->row -1) && (temp->col == 0) )
		{
				temp->left = NULL;
				temp->up	= temp - init_size->col;
				temp->right = temp + 1;
				temp->down = NULL;
							
	
		}
	else if( (temp->row == init_size->row -1) && (temp->col == init_size->col-1) )
		{
				temp->left = temp - 1;
				temp->up   = temp - init_size->col;
				temp->right = NULL;
				temp->down = NULL;
													
		}
	else if( temp->row == 0)
		{
				temp->left = temp - 1;
				temp->up   = NULL;
				temp->right = temp + 1;
				temp->down = temp + init_size->col;
													
		}
	else if( temp->row == init_size->row -1)
		{
				temp->left = temp - 1;
				temp->up   = temp - init_size->col;
				temp->right = temp + 1;
				temp->down = NULL;
													
		}
	else if( temp->col == 0)
		{
				temp->left = NULL;
				temp->up   = temp - init_size->col;
				temp->right = temp + 1;
				temp->down = temp + init_size->col;
													
		}
	else if( temp->col == init_size->col-1)
		{
				temp->left = temp - 1;
				temp->up   = temp - init_size->col;
				temp->right = NULL;
				temp->down = temp + init_size->col;
													
		}
	else
		{
				temp->left = temp - 1;
				temp->up   = temp - init_size->col;
				temp->right = temp + 1;
				temp->down = temp + init_size->col;
													
		}

}

int Init_Mazes(element *mazes, coord *size)
{
	int i, j;
	element *temp = mazes;
	
	for( i = 0; i < size->row; i++)
		{
			for( j = 0; j < size->col; j++)
				{
					scanf("%c", &(temp->name));
					while(temp->name == '\n')
						{
							scanf("%c", &(temp->name));
						}
					temp->row = i;
					temp->col = j;
					temp->sflag = 0;
					temp->lflag = 0;
					temp->rflag = 0;
					temp->uflag = 0;
					temp->dflag = 0;
					temp->path_length = 0;
					temp++;
				}
		}

	temp = mazes;
	for( i = 0; i < size->row; i++ )
		{
			for( j = 0; j < size->col; j++ )
				{
					Set_Node_Relation(temp, size);
					temp++;
				}
		}

	/*temp = mazes;
	for( i = 0; i < size->row; i++ )
		{
			for( j = 0; j < size->col; j++ )
				{
					Print_Node(temp);
					temp++;
				}
		}*/
	
	return 0;

}

element *Find_Object(element *mazes, coord *size, char name)
{
	int i, j;
	element *temp = mazes;
	for( i = 0; i < size->row; i++)
		{
			for( j = 0; j < size->col; j++)
				{
					if(temp->name == name)
						{
							//printf("Find it\n");
							return temp;
						}
					
					temp++;
				}
		}
	printf("No such object in the mazes\n");
	return NULL;
}

int Judge_element(element *ele)
{

	if(ele == NULL)
		{
			return -1;
		}
	else 
		{
			if(ele->name == '.')
				{
					return 0;
				}
			else if(ele->name == 'S')
				{
					return 1;
				}
			else
				{
					return -1;
				}
		}

	
}

int Search_Path(element *mazes, coord *size, element *horace, element *snail)
{

	element *temp = NULL;
	//Print_Node(horace);
	horace->sflag = 1;
	if( Judge_element(horace->left) == 0)
		{
			
			if( (horace->lflag == 0) && (horace->left->sflag == 0) )
				{
					horace->left->path_length = horace->path_length + 1;
					horace->left->rflag = 1;
					//horace->lflag = 1;
					Search_Path(mazes, size, horace->left, snail);
					horace->left->path_length = 0; //recover node after search
					horace->left->rflag = 0;
					//horace->lflag = 0;
				}
			else
				{
					//return -1;
				}
		}
	else if( Judge_element(horace->left) == 1 )
		{
			printf("\nFind the snail! the path length is %d\n", horace->path_length + 1);
			//printf("row:%d, col:%d--", horace->row, horace->col);
			horace->sflag = 0;
			horace->left->rflag = 1;
			temp = Find_Object(mazes, size, 'H');
			Show_Path(temp);
			horace->left->rflag = 0;
			return 0;
		}

	if( Judge_element(horace->up) == 0 )
		{
			if( (horace->uflag == 0) && (horace->up->sflag == 0) )
				{
					horace->up->path_length = horace->path_length + 1;
					horace->up->dflag = 1;
					//horace->uflag = 1;
					Search_Path(mazes, size, horace->up, snail);
					horace->up->path_length = 0;
					horace->up->dflag = 0;
					//horace->uflag = 0;
				}
			else
				{
					//return -1;
				}
		}
	else if( Judge_element(horace->up) == 1 )
		{
			printf("\nFind the snail! the path length is %d\n", horace->path_length + 1);
			//printf("row:%d, col:%d--", horace->row, horace->col);
			//*returnFlag = 1;
			horace->sflag = 0;
			horace->up->dflag = 1;
			temp = Find_Object(mazes, size, 'H');
			Show_Path(temp);
			horace->up->dflag = 0;
			return 0;
		}

	if( Judge_element(horace->right) == 0)
		{
			if( (horace->rflag == 0) && (horace->right->sflag == 0) )
				{
					horace->right->path_length = horace->path_length + 1;
					horace->right->lflag = 1;
					//horace->rflag = 1;
					Search_Path(mazes, size, horace->right, snail);
					horace->right->path_length = 0;
					horace->right->lflag = 0;
					//horace->rflag = 0;
				}
			else
				{
					//return -1;
				}
		}
	else if( Judge_element(horace->right) == 1 )
		{
			printf("\nFind the snail! the path length is %d\n", horace->path_length + 1);
			//printf("row:%d, col:%d--", horace->row, horace->col);
			horace->sflag = 0;
			horace->right->lflag = 1;
			temp = Find_Object(mazes, size, 'H');
			Show_Path(temp);
			horace->right->lflag = 0;
			return 0;
		}

	if( Judge_element(horace->down) == 0)
		{
			if( (horace->dflag == 0) && (horace->down->sflag == 0) )
				{
					horace->down->path_length = horace->path_length + 1;
					horace->down->uflag = 1;
					//horace->dflag = 1;
					Search_Path(mazes, size, horace->down, snail);
					horace->down->path_length = 0;
					horace->down->uflag = 0;
					//horace->dflag = 0;
				}
			else
				{
					//return -1;
				}
		}
	else if( Judge_element(horace->down) == 1 )
		{
			printf("\nFind the snail! the path length is %d\n", horace->path_length + 1);
			//printf("row:%d, col:%d--", horace->row, horace->col);
			horace->sflag = 0;
			horace->down->uflag = 1;
			temp = Find_Object(mazes, size, 'H');
			Show_Path(temp);
			horace->down->uflag = 0;
			return 0;
		}

	horace->sflag = 0;
}

