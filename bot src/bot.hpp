#include <iostream>
#include <vector>

void move();
void move()
{
	int possibilities[map_size_y][map_size_x];

	//find 100% and prepare possibilities
	for (int x = 0; x < map_size_x; x++)
	{
		for (int y = 0; y < map_size_y; y++)
		{
			possibilities[y][x] = 9999;
		}
	}

	for (int x = 0; x < map_size_x; x++)
	{
		for (int y = 0; y < map_size_y; y++)
		{
			int clear_place[2] = { -1, 0 };
			int clear_amount = 0;
			int bombs_founded = 0;

			if (map_view[y][x] < 9 && map_view[y][x] > -1)
			{
				for (auto i : ways)
				{
					if (x - i[0] >= 0 && x - i[0] < map_size_x && y - i[1] >= 0 && y - i[1] < map_size_y)
					{
						if ((map_view[y - i[1]][x - i[0]] == 10))
						{

							clear_amount++;
							clear_place[0] = x - i[0];
							clear_place[1] = y - i[1];
						}
						else if (map_view[y - i[1]][x - i[0]] == 9)
						{
							bombs_founded++;
						}
					}
				}
				if (clear_amount == map_view[y][x] - bombs_founded && clear_place[0] != -1)
				{

					click(clear_place[0], clear_place[1], false);

					return;
				}
				else if (clear_amount != 0 && map_view[y][x] - bombs_founded == 0)
				{
					click(clear_place[0], clear_place[1], true);
					return;
				}
				//possibilities

				if (clear_amount)
				{
					int chance = ((float)(map_view[y][x] - bombs_founded) / float(clear_amount)) * 100.0;
					if (chance != 0)
					{
						for (auto i : ways)
						{
							if (x - i[0] >= 0 && x - i[0] < map_size_x && y - i[1] >= 0 && y - i[1] < map_size_y)
							{
								if (map_view[y - i[1]][x - i[0]] == 10)
								{
									if (possibilities[y - i[1]][x - i[0]] == 9999)
									{
										possibilities[y - i[1]][x - i[0]] = chance;
									}
									else
									{
										possibilities[y - i[1]][x - i[0]] += chance;
									}
								}
							}
						}
					}
				}
				else
				{
					possibilities[y][x] = 9999999;
				}
			}
		}
	}

	//not 100%
	//find smallest posible;
	int min = 9999999;
	int pos[2];
	for (int x = 0; x < map_size_x; x++)
	{
		for (int y = 0; y < map_size_y; y++)
		{
			if (min > possibilities[y][x])
			{
				min = possibilities[y][x];
				pos[0] = x;
				pos[1] = y;
			}
		}
	}
	//std::cout << pos[0] << " " << pos[1] << " " << min << " " << map_view[pos[1]][pos[0]] << std::endl;
	click(pos[0], pos[1], true);
}
