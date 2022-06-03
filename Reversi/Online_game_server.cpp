#include <iostream>

#include "Online_game_server.h"
#include "Gaming_field.h"
#include "Competitor.h"

using namespace std;

string Online_game_server::start_game() {
	int width, height;
	input_sizeof_field(width, height);

	Gaming_field* field = new Gaming_field(width, height, vis);
	Competitor* server_competitor;

	Type_of_turn type_of_turn = input_type_of_turn();
	if (type_of_turn == Game::ByArrows)
		server_competitor = new Player_ByArrows();
	else if (type_of_turn == Game::ByCoordinates)
		server_competitor = new Player_ByCoordinates();
	else
		abort();

	for (int cc = 0; !field->is_end(); cc++) {
		try {
			if (cc % 2 == 0)
				first_competitor->make_turn(field, Gaming_field::Red);
			else
				second_competitor->make_turn(field, Gaming_field::Black);
		}
		catch (Bad_turn e) { // Неправильный ход
			vis->write(String_functions::char_to_str(e.what()) + "\n", Black, Red);
			cc--;
		}
		catch (Visualiser::Bad_integers_input e) { // не разобрали введенных координат
			vis->write(String_functions::char_to_str(e.what()) + "\n", Black, Red);
			cc--;
		}
	}

	Score score = field->count_score();

	return write_end_information(score);
}