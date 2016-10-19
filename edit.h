
#define EX	40	//number of horizontal images
#define EY	8	//number of vertical images

struct Edit
{
	Uint16 t[EX][EY];
	Uint16 sel; //select what is
	
	void Load (); //load the list of images to the editor
	void Draw (SDL_Surface *im, SDL_Surface *ecran); //display images from the editor
	void Draw (SDL_Surface *im, SDL_Surface *ecran, Uint16 x, Uint16 y); //display images from the editor
	void Select (Uint16 x, Uint16 y); //selection
};
typedef struct Edit Edit;

void Edit::Select (Uint16 x, Uint16 y) //selection
{
	if (x < EX && y < EY)
	{
		sel = t[x][y];
	}
}

void Edit::Load ()
{
	char tamp[256];
	MakeName("edit.txt", tamp, RESOURCES, 256);
	FILE *f = fopen(tamp,"r");
	if (f)
	{
		char tamp[256];
		int x,y;
		const char *ptr = tamp;
		for (y=0;y<EY;y++)
		{
			//printf("reading line %d...\n",y);
			if (!readline(f, tamp, 256))
			{
				break;
			}
			ptr = tamp;
			//printf("%s\n",tamp);
			for (x=0;x<DIMX;x++)
			{
				ptr = findnum (ptr, &t[x][y]);
				if (!ptr && x!=DIMX-1)
				{
					printf("Attention : line %d incomplete (%d/%d) !\n",y,x,DIMX);
				}
			}
		}
		sel = 0;
		fclose(f);
	}else
	{
		fprintf(stderr,"Editor file can't be opened !!!\n");
	}
}

void Edit::Draw (SDL_Surface *im, SDL_Surface *ecran, Uint16 x, Uint16 y)
{
	SDL_Rect src, pos;
	src.x = CX*(t[x][y]%10);
	src.y = CY*(t[x][y]/10);
	src.w = CX;
	src.h = CY;
	pos.x = x*CX;
	pos.y = (y+DIMY)*CY;
	SDL_BlitSurface(im, &src, ecran, &pos);
}

void Edit::Draw (SDL_Surface *im, SDL_Surface *ecran)
{
	Uint16 x,y;
	for (y=0;y<EY;y++)
	{
		for (x=0;x<EX;x++)
		{
			if (t[x][y])
				Draw(im, ecran, x, y);
		}
	}
}
