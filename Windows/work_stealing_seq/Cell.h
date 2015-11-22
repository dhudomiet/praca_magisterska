/*
 * Cell.h
 *
 *  Created on: Aug 15, 2015
 *      Author: damian
 */

#ifndef CELL_H_
#define CELL_H_

class Cell {
public:
	Cell();
	Cell(int id, int idx_i, int idx_j, bool flag, int energy);
	virtual ~Cell();
	int get_id();
	void set_id(int id);
	int get_idx_i();
	void set_idx_i(int idx_i);
	int get_idx_j();
	void set_idx_j(int idx_j);
	bool get_flag();
	void set_flag(bool flag);
	Cell& operator=(const Cell &cell);
	int get_energy();
	void set_energy(int energy);
private:
	int id;
	int idx_i;
	int idx_j;
	bool flag;
	int energy;

};

#endif /* CELL_H_ */
