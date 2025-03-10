#include <stdio.h>
#define getOne(X,bit) ((X>>bit) & 0x01)  
#define getTwo(X,i) (X>>(i-1)& 3UL) 

//the mappings from L1-coord to its L1-code
char CHM[4][2][2] = { 0,1,3,2,0,3,1,2,2,3,1,0,2,1,3,0 };
//the mappings from L1-coord to its Ln-state
char CSM[4][2][2] = { 1,0,3,0,0,2,1,1,2,1,2,3,3,3,0,2 };
//the mappings from L1-code to its L1-coord
char HCM[4][4] = { 0,1,3,2,0,2,3,1,3,2,0,1,3,1,0,2 };
//the mappings from L1-code to its Ln-state
char HSM[4][4] = { 1,0,0,3,0,1,1,2,3,2,2,1,2,3,3,0 };

// This function is used to get the CHM_k and CSM_K for different K orders, where K can be custom modified.
void EN_K(int k) {
	int resKey = 0 , max = (1 << k);
	unsigned bitX = 0, bitY = 0;
	char nType = 0;	
	for (char i = 0; i < 4; i++)//four types
	{
		for (int x = 0; x < max; x++)
		{
			for (int y = 0; y < max; y++)
			{
                		resKey = 0;
				nType = i;	
				for (int j = k - 1; j >= 0; j--)//K times
				{
					bitX = getOne(x, j);
					bitY = getOne(y, j);
					resKey = (resKey << 2) | CHM[nType][bitX][bitY];
					nType = CSM[nType][bitX][bitY];
				}
				printf("type:%u,\t X:%u,\t Y:%u,\t CHM:%u,CSM:%u\n", i, x, y, resKey, nType);			
			}
		}
	}
}

//// This function is used to get the HCM_K and HSM_K for different K orders, where K can be custom modified.
void DE_K(int k) {
	char nType = 0;
	int posKey = 0 , max = (1 << (k * 2));
	unsigned bitsZ = 0 , Lat, Lon ;
	for (char i = 0; i < 4; i++)//four types
	{
		for (int H_value = 0; H_value < max; H_value++)//(1 << (k * 2))values
        	{      
			nType = i;
			Lat = 0, Lon = 0;
            		for (int j = k - 1; j >= 0; j--)//K times
            		{
				bitsZ = getTwo(H_value, (2 * j + 1));
				posKey = HCM[nType][bitsZ];
				Lat = (Lat << 1) | (posKey & 0x1);//y
				Lon = (Lon << 1) | (posKey >> 1 & 0x1);//x
				nType = HSM[nType][bitsZ];
            		}
			printf("type:%u,\t H_value:%u,\t H_X:%u,\t H_Y:%u,\tHSM:%u\n",i, H_value, Lon, Lat, nType);
        	}
	}
}

int main()
{
	//YOU CAN CHANGE THE K VALUE
	// ENCODE AND DECODE
	//EN_K(K);
	//DE_K(K);
	 return 0;
}
