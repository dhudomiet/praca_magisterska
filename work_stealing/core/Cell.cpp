/*
 * Cell.cpp
 *
 *  Created on: Aug 15, 2015
 *      Author: damian
 */

#include "Cell.h"

Cell::Cell() {
	idx_j = 0;
	idx_i = 0;
	id = 0;
	flag = false;

}

Cell::Cell(int id, int idx_i, int idx_j, bool flag) {
	this->id = id;
	this->idx_i = idx_i;
	this->idx_j = idx_j;
	this->flag = flag;
}

Cell::~Cell() {
	// TODO Auto-generated destructor stub
}

int Cell::get_id() {
	return id;
}

void Cell::set_id(int id) {
	this->id = id;
}

int Cell::get_idx_i() {
	return idx_i;
}

void Cell::set_idx_i(int idx_i) {
	this->idx_i = idx_i;
}

int Cell::get_idx_j() {
	return idx_j;
}

void Cell::set_idx_j(int idx_j) {
	this->idx_j = idx_j;
}

bool Cell::get_flag() {
	return flag;
}

void Cell::set_flag(bool flag) {
	this->flag = flag;
}

Cell Cell::operator =(Cell cell) {
	this->id = cell.id;
	this->idx_i = cell.idx_i;
	this->idx_j = cell.idx_j;
	this->energy = cell.energy;
	this->flag = cell.flag;
	return *this;

}

int Cell::get_energy() {
	return energy;
}

void Cell::set_energy(int energy) {
	this->energy = energy;
}
