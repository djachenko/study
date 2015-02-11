#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

int sum = 0;

int main(int argc, char **argv) 
{
	using namespace std;
    
    // each iteration is for the array of i KB length
	for (int i = 1; i <= 1024; i++) 
	{
		int currentSize = i * 1024 / sizeof(int); 
	        int array[currentSize];

        	memset(array, 0, i * 1024);

        // parse command line arguement
	        switch (argv[1][0]) 
		{
            		case ('d') : 
			{
                //cout << "direct\n";
                		for (int j = 0; j < currentSize - 1; j++) 
				{
                    			array[j] = j + 1;
                		}
                		array[currentSize - 1] = 0;

                		break;
            		}
            		case ('b') : 
			{
                		//cout << "back\n";
                		for (int j = 0; j < currentSize - 1; j++) 
				{
                    			array[j + 1] = j;
                		}
                		array[0] = currentSize-1;
                
                		break;
            		}
            		case ('r') : 
			{
                		//cout << "random\n";
                		bool used[currentSize];
                		for (int j = 0; j < currentSize; j++) 
				{
		                    used[j] = false;
		                }

		                int i = 0;
                		int count = 0;
		                used[0] = true;

                		do 
				{
		                    int next = 0;
                    do {
                        next = rand() % currentSize;
                    } while (used[next]);
                    array[i] = next;
                    used[i] = true;
                    i = next;
                    count++;
                } while (count <= currentSize);
                array[i] = 0;

                break;
            }
        }
        
        // cache heating
        int j = 0;
        do {
            j = array[j];
        } while (j != 0);
        
        // actual time check
        // we do it triple, to have better statistics
        
        double resultTime = 0;

        for (int k = 0; k < 3; k++) {
            struct timespec start, end;

            clock_gettime(CLOCK_REALTIME, &start);

            int count = 0;
            j = 0;
            do {
                j = array[j];
                sum += j;
                count++;
            } while (count <= 10 * currentSize);

            clock_gettime(CLOCK_REALTIME, &end);

            double currentResult = 0;

            currentResult += 1000000 * (end.tv_sec - start.tv_sec);
            currentResult += 0.001 * (end.tv_nsec - start.tv_nsec);
            
            if (currentResult > 0 && (currentResult < resultTime || resultTime == 0)) { 
                resultTime = currentResult;
            }

        }
    
        if (sum == 0) {
            cout << sum << "\n";
        }

        cout << i << " " << resultTime / 10  << "\n";

    }

    return 0;
}
