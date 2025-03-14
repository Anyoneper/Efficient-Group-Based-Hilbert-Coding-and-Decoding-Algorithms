#include <stdio.h>
#include <iostream>
#define getOne(X,bit) ((X>>bit) & 0x01)  
#define getthree(X,i) (X>>i & 7UL) 
using namespace std;

char CHM[24][2][2][2] = {
    {0, 1, 3, 2, 7, 6, 4, 5},
    {0, 1, 7, 6, 3, 2, 4, 5},
    {0, 3, 1, 2, 7, 4, 6, 5},
    {0, 7, 1, 6, 3, 4, 2, 5},
    {0, 3, 7, 4, 1, 2, 6, 5},
    {0, 7, 3, 4, 1, 6, 2, 5},
    {2, 1, 3, 0, 5, 6, 4, 7},
    {6, 1, 7, 0, 5, 2, 4, 3},
    {2, 3, 1, 0, 5, 4, 6, 7},
    {6, 7, 1, 0, 5, 4, 2, 3},
    {4, 3, 7, 0, 5, 2, 6, 1},
    {4, 7, 3, 0, 5, 6, 2, 1},
    {2, 1, 5, 6, 3, 0, 4, 7},
    {6, 1, 5, 2, 7, 0, 4, 3},
    {2, 3, 5, 4, 1, 0, 6, 7},
    {6, 7, 5, 4, 1, 0, 2, 3},
    {4, 3, 5, 2, 7, 0, 6, 1},
    {4, 7, 5, 6, 3, 0, 2, 1},
    {2, 5, 1, 6, 3, 4, 0, 7},
    {6, 5, 1, 2, 7, 4, 0, 3},
    {2, 5, 3, 4, 1, 6, 0, 7},
    {6, 5, 7, 4, 1, 2, 0, 3},
    {4, 5, 3, 2, 7, 6, 0, 1},
    {4, 5, 7, 6, 3, 2, 0, 1}
};

char CSM[24][2][2][2] = {
    {5, 1, 13, 0, 13, 22, 5, 0} ,
    {3, 0, 7, 23, 7, 1, 3, 1},
    {4, 19, 3, 2, 19, 4, 16, 2},
    {1, 9, 2, 17, 9, 1, 3, 3},
    {2, 21, 21, 2, 5, 4, 10, 4},
    {0, 15, 15, 0, 4, 11, 5, 5},
    {6, 7, 12, 11, 6, 20, 11, 12},
    {21, 6, 1, 9, 7, 7, 9, 1},
    {8, 18, 9, 10, 8, 10, 14, 18},
    {15, 3, 8, 7, 9, 7, 9, 3},
    {8, 23, 23, 8, 10, 10, 4, 11},
    {6, 17, 17, 6, 11, 5, 11, 10},
    {12, 13, 12, 18, 6, 17, 17, 6},
    {19, 12, 13, 13, 0, 15, 15, 0},
    {14, 20, 14, 16, 15, 16, 8, 20},
    {9, 5, 15, 13, 14, 13, 15, 5},
    {14, 22, 16, 16, 22, 14, 2, 17},
    {12, 11, 17, 3, 11, 12, 17, 16},
    {18, 18, 19, 12, 8, 23, 23, 8},
    {13, 19, 18, 19, 2, 21, 21, 2},
    {20, 20, 14, 22, 21, 6, 22, 14},
    {7, 21, 4, 19, 20, 21, 19, 4},
    {20, 22, 16, 22, 16, 0, 20, 23},
    {18, 23, 10, 1, 10, 23, 18, 22}
};

char HCM[24][8] =
{
    {0, 1, 3, 2, 6, 7, 5, 4},
    {0, 1, 5, 4, 6, 7, 3, 2},
    {0, 2, 3, 1, 5, 7, 6, 4},
    {0, 2, 6, 4, 5, 7, 3, 1},
    {0, 4, 5, 1, 3, 7, 6, 2},
    {0, 4, 6, 2, 3, 7, 5, 1},
    {3, 1, 0, 2, 6, 4, 5, 7},
    {3, 1, 5, 7, 6, 4, 0, 2},
    {3, 2, 0, 1, 5, 4, 6, 7},
    {3, 2, 6, 7, 5, 4, 0, 1},
    {3, 7, 5, 1, 0, 4, 6, 2},
    {3, 7, 6, 2, 0, 4, 5, 1},
    {5, 1, 0, 4, 6, 2, 3, 7},
    {5, 1, 3, 7, 6, 2, 0, 4},
    {5, 4, 0, 1, 3, 2, 6, 7},
    {5, 4, 6, 7, 3, 2, 0, 1},
    {5, 7, 3, 1, 0, 2, 6, 4},
    {5, 7, 6, 4, 0, 2, 3, 1},
    {6, 2, 0, 4, 5, 1, 3, 7},
    {6, 2, 3, 7, 5, 1, 0, 4},
    {6, 4, 0, 2, 3, 1, 5, 7},
    {6, 4, 5, 7, 3, 1, 0, 2},
    {6, 7, 3, 2, 0, 1, 5, 4},
    {6, 7, 5, 4, 0, 1, 3, 2}
};

char HSM[24][8] =
{
    {5, 1, 0, 13, 5, 0, 22, 13},
    {3, 0, 1, 7, 3, 1, 23, 7},
    {4, 3, 2, 19, 4, 2, 16, 19},
    {1, 2, 3, 9, 1, 3, 17, 9},
    {2, 5, 4, 21, 2, 4, 10, 21},
    {0, 4, 5, 15, 0, 5, 11, 15},
    {11, 7, 6, 12, 11, 6, 20, 12},
    {9, 6, 7, 1, 9, 7, 21, 1},
    {10, 9, 8, 18, 10, 8, 14, 18},
    {7, 8, 9, 3, 7, 9, 15, 3},
    {8, 11, 10, 23, 8, 10, 4, 23},
    {6, 10, 11, 17, 6, 11, 5, 17},
    {17, 13, 12, 6, 17, 12, 18, 6},
    {15, 12, 13, 0, 15, 13, 19, 0},
    {16, 15, 14, 20, 16, 14, 8, 20},
    {13, 14, 15, 5, 13, 15, 9, 5},
    {14, 17, 16, 22, 14, 16, 2, 22},
    {12, 16, 17, 11, 12, 17, 3, 11},
    {23, 19, 18, 8, 23, 18, 12, 8},
    {21, 18, 19, 2, 21, 19, 13, 2},
    {22, 21, 20, 14, 22, 20, 6, 14},
    {19, 20, 21, 4, 19, 21, 7, 4},
    {20, 23, 22, 16, 20, 22, 0, 16},
    {18, 22, 23, 10, 18, 23, 1, 10},
};

void EN_K(int k) {
    int resKey = 0, max = (1 << k);
    unsigned bitX = 0, bitY = 0, bitZ = 0;
    int nType = 0;
    int num = 0;
    std::cout << "{" << std::endl;
    for (char i = 0; i < 24; i++)//24 types
    {
        std::cout << "{";
        for (int x = 0; x < max; x++)
        {
            for (int y = 0; y < max; y++)
            {
                for (int z = 0; z < max; z++)
                {
                    resKey = 0;
                    nType = i;
                    num++;
                    for (int j = k - 1; j >= 0; j--)//K times
                    {
                        bitX = getOne(x, j);
                        bitY = getOne(y, j);
                        bitZ = getOne(z, j);
                        resKey = (resKey << 3) | CHM[nType][bitX][bitY][bitZ];
                        nType = CSM[nType][bitX][bitY][bitZ];
                    }
                    std::cout << resKey;//nType
                    int num = (1 << k) - 1;
                    if (!(x == num && y == num && z == num))
                    {
                        std::cout << ", ";
                    }
                }
            }
        }
        i == 23 ? std::cout << "}" << std::endl : std::cout << "}," << std::endl;
    }
    std::cout << "}" << std::endl;
}

void DE_K(int k) {
    int nType = 0;
    int posKey = 0, max = (1 << (k * 3));
    int group = 0, z = 0, y = 0, x = 0;
    std::cout << "{" << std::endl;
    for (char i = 0; i < 24; i++)//24 types
    {
        std::cout << "{";
        for (int H_value = 0; H_value < max; H_value++)//(1 << (k * 4))values
        {
            nType = i;
            z = y = x = 0;
            for (int j = k - 1; j >= 0; j--)//K times
            {
                group = getthree(H_value, 3 * j);
                posKey = HCM[nType][group];
                z = (z << 1) | (posKey & 0x1);//z
                y = (y << 1) | (posKey >> 1 & 0x1);//y
                x = (x << 1) | (posKey >> 2 & 0x1);//x
                nType = HSM[nType][group];
            }
            H_value == max - 1 ? std::cout << (x << 2 * k | y << k | z) : std::cout << (x << 2 * k | y << k | z) << ",";//nType
        }
        i == 23 ? std::cout << "}" << std::endl : std::cout << "}," << std::endl;
    }
    std::cout << "}" << std::endl;
}


//int main() {
//    EN_K(2);
//    //DE_K(2);
//    return 0;
//}
