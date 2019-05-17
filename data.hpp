#ifndef DATA_HPP_
#define DATA_HPP_
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

#define FILENAME1 "didymosl162_vertices.txt"
#define FILENAME2 "didymosl162_indices.txt"
#define FILENAME3 "testI.dat"

template <typename  T>	//Using a template in order to create an instance of the function for integers and one  for floats

void data(vector<vector< T > > &vec, int *N, int COLUMNS, int filenumber){
	fstream file;
    vector < T > rowVector(COLUMNS);							// vector to add into 'array' (represents a row)
    int row = 0;
    if (filenumber == 1)
    	file.open(FILENAME1 , ios::in);							// read vertices
    else if (filenumber == 2)
    	file.open(FILENAME2 , ios::in);							// read indices
    else
    	file.open(FILENAME3 , ios::in);							//contains data of the trajectory

    if (file.is_open()) {
        while (file.good()) {									// check for errors
        	vec.push_back(rowVector);							// add a new row
        	for (int col=0; col<COLUMNS; col++) {
        		file >> vec[row][col];							// fill the row with col elements
            }
        	row++;												// number of rows in my file
        }
    }

    else cout << "Unable to open file" << endl;
     file.close();
     *N = row;	//counting total rows recorded in the memory
 }

#endif /* DATA_HPP_ */
