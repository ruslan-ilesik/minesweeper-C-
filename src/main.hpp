#include <string>

int random(int min, int max);

int random(int min, int max)
{
	static bool first = true;
	if (first)
	{
		srand(time(NULL));
		first = false;
	}
	return min + rand() % ((max + 1) - min);
}

void loop();
void generate_map();
void set_numbers();
void game_over(std::string t);
void open_all_zero_around(int x, int y);
void check_win();