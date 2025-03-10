#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
typedef unsigned long long bitmask_t;
typedef unsigned long halfmask_t;

#define ones(T,k) ((((T)1) << (k)) - 1) 
#define getBit(X,i,k) (X>>(i-k+1)& ones(bitmask_t,k))  

std::vector<uint16_t> CHM;
std::vector<uint8_t> CSM;
std::vector<uint16_t> HCM;
std::vector<uint8_t> HSM;

/*
	en_FVFG, the virtual-filling based group encoding algorithm.
	X: the first coordinate component
	Y: the second coordinate component
    	Z: the third coordinate component
	order: the number of orders
	groupSize: group size
*/
void en_FVFG(bitmask_t& hcode, halfmask_t X, halfmask_t Y, halfmask_t Z, int order, int groupSize)
{
	halfmask_t groupX = 0, groupY = 0, groupZ = 0;
	hcode = 0;
	int pos = 0;

	int groupNum = (order - 1) / groupSize + 1;
	int startPos = groupNum * groupSize - 1;
	int dimSize = 1 << groupSize;
	unsigned state = (groupSize * groupNum - order) % 2 ? 5 : 0;

	for (short i = groupNum - 1; i >= 0; i--)
	{
		groupX = getBit(X, startPos, groupSize);
		groupY = getBit(Y, startPos, groupSize);
		groupZ = getBit(Z, startPos, groupSize);
		startPos -= groupSize;

		pos = state * dimSize * dimSize * dimSize + groupX * dimSize * dimSize + groupY * dimSize + groupZ;
		hcode = (hcode << (3 * groupSize)) | CHM[pos];
		state = CSM[pos];
	}
}

/*
	de_FVFG, the virtual-filling based group decoding algorithm.
	X: the first coordinate component
	Y: the second coordinate component
    	Z: the third coordinate component
	order: the number of orders
	groupSize: group size
*/
void de_FVFG(bitmask_t hcode, halfmask_t& X, halfmask_t& Y, halfmask_t& Z, int order, int groupSize) {
	X = Y = Z = 0;
	unsigned bitZ = 0;
	halfmask_t posKey = 0;
	int groupNum = (order - 1) / groupSize + 1;
	int dimSize = 1 << groupSize;
	int startPos = 3 * groupNum * groupSize - 1;
	halfmask_t mask = ones(halfmask_t, groupSize);
	unsigned char state = (groupSize * groupNum - order) % 2 ? 5 : 0;
	int pos = 0;

	for (int i = groupNum - 1; i >= 0; i--) {
		bitZ = getBit(hcode, startPos, 3 * groupSize);
		startPos -= 3 * groupSize;
		pos = state * dimSize * dimSize * dimSize + bitZ;
		posKey = HCM[pos];

		Z = (Z << groupSize) | (posKey & mask);
		Y = (Y << groupSize) | ((posKey >> groupSize) & mask);
		X = (X << groupSize) | ((posKey >> (2 * groupSize)) & mask);

		// 更新状态为下一个组的状态
		state = HSM[pos];
	}
}

/*
reading the state-views from files
*/
template <typename T>
vector<T> readSVs(const string& filename) {
	ifstream inFile(filename, ios::binary);
	size_t size;
	inFile.read(reinterpret_cast<char*>(&size), sizeof(size));
	vector<T> array(size);
	inFile.read(reinterpret_cast<char*>(array.data()), size * sizeof(T));
	inFile.close();
	return array;
}


int main()
{
	int n = 2;//the number of orders of the input data. This value should be between 1 to 32.
	int g = 4; // group size. Do not change this value unless you have generated the state-views for the specific g. 
	unsigned endVal = 1 << n;// we simply test the first endVal*endVal input data here.This value can be changed, however, it should be less than 1<<n.
	bitmask_t hcode ;// Hilbert code
	halfmask_t x, y, z;//coordinate

	cout << "_________Reading the state views_____________" << endl;
	CHM = readSVs<uint16_t>("CHM4.bin");
	CSM = readSVs<uint8_t>("CSM4.bin");
	HCM = readSVs<uint16_t>("HCM4.bin");
	HSM = readSVs<uint8_t>("HSM4.bin");

	cout << "_________Encoding_____________" << endl;
	cout << endl << "Start test en_FVFG:" << endl;
	for (z = 0; z < endVal; z++)
	{
		for (y = 0; y < endVal; y++)
		{
			for (x = 0; x < endVal; x++)
			{
				en_FVFG(hcode, x, y, z, n, g);
				cout << "The Hilbert code of coordinate (" << x << "," << y << "," << z << ") is: " << hcode << endl;
			}
		}
	}

	cout << "_________Decoding_____________" << endl;
	cout << endl << "Start test de_FVFG:" << endl;
	for (hcode = 0; hcode < endVal * endVal * endVal; hcode++)
	{
		x = 0;
		y = 0;
		z = 0;
		de_FVFG(hcode, x, y, z, n, g);
		cout << "The coordinate of Hilbert code " << hcode << " is: (" << x << "," << y << "," << z << ")" << endl;
	}
	return 0;
}
