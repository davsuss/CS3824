
#ifndef MATRIXH
#define MATRIXH
template<typename T> 
class Matrix {
private:
	T ** array;
public:
	Matrix(int rows, int columns, T defaultvalue){
		array = new T*[rows];
		for (int i = 0; i < rows; i++)
		{
			array[i] = new T[columns];
			for (int y = 0; y < columns; y++)
			{
				array[i][y] = defaultvalue;
			}
		}
	}
	T get(int row, int column){
		return array[row][column];
	}
	void set(T value, int row, int column){
		array[row][column] = value;
	}
};

#endif