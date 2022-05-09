int get_1D_coord(int x, int y, int array_height)
{
	return x * array_height + y;
}

int getLeftUpperCornerAliveNeighboursCount(__global const int * source, int x, int y, int width, int height, bool withBorders)
{
	int numOfAliveNeighbours = 0;

	if(y + 1 < height && source[get_1D_coord(x, y+1, height)])
	{
		numOfAliveNeighbours++;
	}
	if(x + 1 < width && source[get_1D_coord(x+1, y, height)])
	{
		numOfAliveNeighbours++;
	}
	if(x+1 < width && y+1 < height && source[get_1D_coord(x+1, y+1, height)])
	{
		numOfAliveNeighbours++;
	}
	if(!withBorders)
	{
		if(source[get_1D_coord(width-1, height-1, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(x, height-1, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(width-1, y, height)])
		{
			numOfAliveNeighbours++;
		}
		if(x + 1 < width && source[get_1D_coord(x+1, height-1, height)])
		{
			numOfAliveNeighbours++;
		}
		if(y + 1 < height && source[get_1D_coord(width-1, y+1, height)])
		{
			numOfAliveNeighbours++;
		}
	}

	return numOfAliveNeighbours;
}

int getLeftBottomCornerAliveNeighboursCount(__global const int * source, int x, int y, int width, int height, bool withBorders)
{
	int numOfAliveNeighbours = 0;

	if(y - 1 > 0 && source[get_1D_coord(x, y-1, height)])
	{
		numOfAliveNeighbours++;
	}
	if(x + 1 < width && source[get_1D_coord(x+1, y, height)])
	{
		numOfAliveNeighbours++;
	}
	if(x+1 < width && y-1 > 0 && source[get_1D_coord(x+1, y-1, height)])
	{
		numOfAliveNeighbours++;
	}
	if(!withBorders)
	{
		if(source[get_1D_coord(width-1, 0, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(x, 0, height)])
		{
			numOfAliveNeighbours++;
		}
		if(x + 1 < width && source[get_1D_coord(x+1, 0, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(width-1, y, height)])
		{
			numOfAliveNeighbours++;
		}
		if(y - 1 > 0 && source[get_1D_coord(width-1, y-1, height)])
		{
			numOfAliveNeighbours++;
		}
	}

	return numOfAliveNeighbours;
}

int getLeftMiddleAliveNeighboursCount(__global const int * source, int x, int y, int width, int height, bool withBorders)
{
	int numOfAliveNeighbours = 0;

	if(source[get_1D_coord(x, y-1, height)])
	{
		numOfAliveNeighbours++;
	}
	if(source[get_1D_coord(x, y+1, height)])
	{
		numOfAliveNeighbours++;
	}
	if(x + 1 < width)
	{
		if(source[get_1D_coord(x+1, y-1, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(x+1, y+1, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(x+1, y, height)])
		{
			numOfAliveNeighbours++;
		}
	}
	if(!withBorders)
	{
		if(source[get_1D_coord(width-1, y-1, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(width-1, y, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(width-1, y+1, height)])
		{
			numOfAliveNeighbours++;
		}
	}

	return numOfAliveNeighbours;
}









int getRightUpperCornerAliveNeighboursCount(__global const int * source, int x, int y, int width, int height, bool withBorders)
{
	int numOfAliveNeighbours = 0;

	if(y + 1 < height && source[get_1D_coord(x, y+1, height)])
	{
		numOfAliveNeighbours++;
	}
	if(x - 1 > 0 && source[get_1D_coord(x-1, y, height)])
	{
		numOfAliveNeighbours++;
	}
	if(x-1 > 0 && y+1 < height && source[get_1D_coord(x-1, y+1, height)])
	{
		numOfAliveNeighbours++;
	}
	if(!withBorders)
	{
		if(x-1 > 0 && source[get_1D_coord(x-1, height-1, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(x, height-1, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(width-1, height-1, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(width-1, y, height)])
		{
			numOfAliveNeighbours++;
		}
		if(y + 1 < height && source[get_1D_coord(width-1, y+1, height)])
		{
			numOfAliveNeighbours++;
		}
	}

	return numOfAliveNeighbours;
}

int getRightBottomCornerAliveNeighboursCount(__global const int * source, int x, int y, int width, int height, bool withBorders)
{
	int numOfAliveNeighbours = 0;

	if(y - 1 > 0 && source[get_1D_coord(x, y-1, height)])
	{
		numOfAliveNeighbours++;
	}
	if(x - 1 > 0 && source[get_1D_coord(x-1, y, height)])
	{
		numOfAliveNeighbours++;
	}
	if(x-1 > 0 && y-1 > 0 && source[get_1D_coord(x+1, y-1, height)])
	{
		numOfAliveNeighbours++;
	}
	if(!withBorders)
	{
		if(source[get_1D_coord(0, 0, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(x, 0, height)])
		{
			numOfAliveNeighbours++;
		}
		if(x - 1 > 0 && source[get_1D_coord(x-1, 0, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(0, y, height)])
		{
			numOfAliveNeighbours++;
		}
		if(y - 1 > 0 && source[get_1D_coord(0, y-1, height)])
		{
			numOfAliveNeighbours++;
		}
	}

	return numOfAliveNeighbours;
}

int getRightMiddleAliveNeighboursCount(__global const int * source, int x, int y, int width, int height, bool withBorders)
{
	int numOfAliveNeighbours = 0;

	if(source[get_1D_coord(x, y-1, height)])
	{
		numOfAliveNeighbours++;
	}
	if(source[get_1D_coord(x, y+1, height)])
	{
		numOfAliveNeighbours++;
	}
	if(x - 1 > 0)
	{
		if(source[get_1D_coord(x-1, y-1, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(x-1, y+1, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(x-1, y, height)])
		{
			numOfAliveNeighbours++;
		}
	}
	if(!withBorders)
	{
		if(source[get_1D_coord(0, y-1, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(0, y, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(0, y+1, height)])
		{
			numOfAliveNeighbours++;
		}
	}

	return numOfAliveNeighbours;
}








int getUpperMiddleAliveNeighboursCount(__global const int * source, int x, int y, int width, int height, bool withBorders)
{
	int numOfAliveNeighbours = 0;

	if(source[get_1D_coord(x-1, y, height)])
	{
		numOfAliveNeighbours++;
	}
	if(source[get_1D_coord(x+1, y, height)])
	{
		numOfAliveNeighbours++;
	}
	if(y + 1 < height)
	{
		if(source[get_1D_coord(x-1, y+1, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(x+1, y+1, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(x, y+1, height)])
		{
			numOfAliveNeighbours++;
		}
	}
	if(!withBorders)
	{
		if(source[get_1D_coord(x-1, height-1, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(x+1, height-1, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(x, height-1, height)])
		{
			numOfAliveNeighbours++;
		}
	}

	return numOfAliveNeighbours;
}

int getBottomMiddleAliveNeighboursCount(__global const int * source, int x, int y, int width, int height, bool withBorders)
{
	int numOfAliveNeighbours = 0;

	if(source[get_1D_coord(x-1, y, height)])
	{
		numOfAliveNeighbours++;
	}
	if(source[get_1D_coord(x+1, y, height)])
	{
		numOfAliveNeighbours++;
	}
	if(y - 1 > 0)
	{
		if(source[get_1D_coord(x-1, y-1, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(x+1, y-1, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(x, y-1, height)])
		{
			numOfAliveNeighbours++;
		}
	}
	if(!withBorders)
	{
		if(source[get_1D_coord(x-1, 0, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(x+1, 0, height)])
		{
			numOfAliveNeighbours++;
		}
		if(source[get_1D_coord(x, 0, height)])
		{
			numOfAliveNeighbours++;
		}
	}

	return numOfAliveNeighbours;
}

int getMiddleMiddleAliveNeighboursCount(__global const int * source, int x, int y, int width, int height, bool withBorders)
{
	int numOfAliveNeighbours = 0;

	if(source[get_1D_coord(x-1, y-1, height)])
	{
		numOfAliveNeighbours++;
	}
	if(source[get_1D_coord(x-1, y, height)])
	{
		numOfAliveNeighbours++;
	}
	if(source[get_1D_coord(x-1, y+1, height)])
	{
		numOfAliveNeighbours++;
	}
	if(source[get_1D_coord(x, y-1, height)])
	{
		numOfAliveNeighbours++;
	}
	if(source[get_1D_coord(x, y+1, height)])
	{
		numOfAliveNeighbours++;
	}
	if(source[get_1D_coord(x+1, y-1, height)])
	{
		numOfAliveNeighbours++;
	}
	if(source[get_1D_coord(x+1, y, height)])
	{
		numOfAliveNeighbours++;
	}
	if(source[get_1D_coord(x+1, y+1, height)])
	{
		numOfAliveNeighbours++;
	}

	return numOfAliveNeighbours;
}

__kernel void gameOfLife(__global const int * source, __global int * destination, unsigned long width, unsigned long height, int withBorders)
{
	const int id = get_global_id(0);
	
	const int x = id / height;
	const int y = id - x * height;

	//destination[id] = 1;

	int numOfAliveNeighbours = 0;
	if(x == 0)
	{
		if(y == 0)
		{
			numOfAliveNeighbours += getLeftUpperCornerAliveNeighboursCount(source, x, y, width, height, withBorders);
		}
		else if(y == height - 1)
		{
			numOfAliveNeighbours += getLeftBottomCornerAliveNeighboursCount(source, x, y, width, height, withBorders);
		}
		else
		{
			numOfAliveNeighbours += getLeftMiddleAliveNeighboursCount(source, x, y, width, height, withBorders);
		}
	}
	else if(x == width - 1)
	{
		if(y == 0)
		{
			numOfAliveNeighbours += getRightUpperCornerAliveNeighboursCount(source, x, y, width, height, withBorders);
		}
		else if(y == height - 1)
		{
			numOfAliveNeighbours += getRightBottomCornerAliveNeighboursCount(source, x, y, width, height, withBorders);
		}
		else
		{
			numOfAliveNeighbours += getRightMiddleAliveNeighboursCount(source, x, y, width, height, withBorders);
		}
	}
	else
	{
		if(y == 0)
		{
			numOfAliveNeighbours += getUpperMiddleAliveNeighboursCount(source, x, y, width, height, withBorders);
		}
		else if(y == height - 1)
		{
			numOfAliveNeighbours += getBottomMiddleAliveNeighboursCount(source, x, y, width, height, withBorders);
		}
		else
		{
			numOfAliveNeighbours += getMiddleMiddleAliveNeighboursCount(source, x, y, width, height, withBorders);
		}
	}
	
	if(
		(source[get_1D_coord(x,y,width)] && (numOfAliveNeighbours == 2 || numOfAliveNeighbours == 3))
		||
		(!source[get_1D_coord(x,y,width)] && numOfAliveNeighbours == 3)
	)
	{
		destination[get_1D_coord(x,y,height)] = true;
	}
	else
	{
		destination[get_1D_coord(x,y,height)] = false;
	}
}