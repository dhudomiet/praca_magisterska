#include "GrainGrow.h"


GrainGrow::GrainGrow(void)
{
	initialize_space();
}


GrainGrow::~GrainGrow(void)
{
}

void GrainGrow::initialize_space(){
	space_of_cells = new int*[HEIGHT];
	old_space = new int*[HEIGHT];
	for(int i=0;i<HEIGHT;i++){
		space_of_cells[i] = new int[WIDTH];
		old_space[i] = new int[WIDTH];
	}
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			space_of_cells[i][j] = 0;
		}
	}
	int m = 1;
	for (int i = 0; i < HEIGHT; i+=5) {
		for(int j = 0; j < WIDTH; j+=5){
			space_of_cells[i][j] = (m++);
		}
	}
}

void GrainGrow::copy_spaces(int** space, int** source_space){
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			space[i][j] = source_space[i][j];
		}
	}
}

void GrainGrow::executeGrainGrow(int** space, int** old_space){
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (old_space[i][j] == 0) {
				int tab[2];
				if (is_neighbor(i, j, tab, old_space)) {
					space[i][j] = old_space[tab[0]][tab[1]];
				}
			}
		}
	}
}
void GrainGrow::draw_space(){
	cout<<endl;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			std::cout<<space_of_cells[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
}
void GrainGrow::grain_grow_algorithm(){
	cout<<"start execute grain grow..."<<endl;
	Time start (boost::posix_time::microsec_clock::local_time());
	for(int i=0;i<100;i++) {
		copy_spaces(old_space, space_of_cells);
		executeGrainGrow(space_of_cells,old_space);
	}
	Time stop (boost::posix_time::microsec_clock::local_time());
	TimeDuraction time = stop - start;
	cout<<"time of execution : "<<time.total_milliseconds()<<endl;
	//draw_space();
}
bool GrainGrow::is_fill_all(){
	int count = 0;
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			if(space_of_cells[i][j] !=0){
				count++;
			}
		}
	}
	if(count == WIDTH*HEIGHT){
		return true;
	}else{
		return false;
	}
}

bool GrainGrow::is_neighbor(int idx_i, int idx_j, int *tab, int **space_of_cells){
	if (idx_i == 0 && idx_j == 0) {
		for (int i = idx_i; i < idx_i + 2; i++) {
			for (int j = idx_j; j < idx_j + 2; j++) {
				if (i == 0 && j == 0)
					continue;
				if (space_of_cells[i][j] != 0) {
					tab[0] = i;
					tab[1] = j;
					return true;
				}
			}
		}
		return false;
	} else if (idx_i == 0 && idx_j == WIDTH - 1) {
		for (int i = idx_i; i < idx_i + 2; i++) {
			for (int j = idx_j - 1; j < idx_j + 1; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				if (space_of_cells[i][j] != 0) {
					tab[0] = i;
					tab[1] = j;
					return true;
				}
			}
		}
		return false;
	} else if (idx_i == HEIGHT - 1 && idx_j == 0) {
		for (int i = idx_i - 1; i < idx_i + 1; i++) {
			for (int j = idx_j; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				if (space_of_cells[i][j] != 0) {
					tab[0] = i;
					tab[1] = j;
					return true;
				}
			}
		}
		return false;
	} else if (idx_i == HEIGHT - 1 && idx_j == WIDTH - 1) {
		for (int i = idx_i - 1; i < idx_i + 1; i++) {
			for (int j = idx_j - 1; j < idx_j + 1; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				if (space_of_cells[i][j] != 0) {
					tab[0] = i;
					tab[1] = j;
					return true;
				}
			}
		}
		return false;
	} else if (idx_i > 0 && idx_i < HEIGHT - 1 && idx_j == 0) {
		for (int i = idx_i - 1; i < idx_i + 2; i++) {
			for (int j = idx_j; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				if (space_of_cells[i][j] != 0) {
					tab[0] = i;
					tab[1] = j;
					return true;
				}
			}
		}
		return false;
	} else if (idx_i > 0 && idx_i < HEIGHT - 1 && idx_j == WIDTH - 1) {
		for (int i = idx_i - 1; i < idx_i + 2; i++) {
			for (int j = idx_j - 1; j < idx_j + 1; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				if (space_of_cells[i][j] != 0) {
					tab[0] = i;
					tab[1] = j;
					return true;
				}
			}
		}
		return false;
	} else if (idx_j > 0 && idx_j < WIDTH - 1 && idx_i == 0) {
		for (int i = idx_i; i < idx_i + 2; i++) {
			for (int j = idx_j - 1; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				if (space_of_cells[i][j] != 0) {
					tab[0] = i;
					tab[1] = j;
					return true;
				}
			}
		}
		return false;
	} else if (idx_j > 0 && idx_j < WIDTH - 1 && idx_i == HEIGHT - 1) {
		for (int i = idx_i - 1; i < idx_i + 1; i++) {
			for (int j = idx_j - 1; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				if (space_of_cells[i][j] != 0) {
					tab[0] = i;
					tab[1] = j;
					return true;
				}
			}
		}
		return false;
	} else {
		for (int i = idx_i - 1; i < idx_i + 2; i++) {
			for (int j = idx_j - 1; j < idx_j + 2; j++) {
				if (i == idx_i && j == idx_j)
					continue;
				if (space_of_cells[i][j] != 0) {
					tab[0] = i;
					tab[1] = j;
					return true;
				}
			}
		}
		return false;
	}

}
