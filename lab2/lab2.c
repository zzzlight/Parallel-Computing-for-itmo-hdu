#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <fwBase.h>
#include <fwSignal.h>

/* the Variant is A=40 and other variants are 6 1 5 6*/
int main(int argc, char *argv[])
{

    int i, N,j,M;

    struct timeval T1, T2;

    long delta_ms;

    N = atoi(argv[1]); /* N equals the first command-line parameter */
	M = atoi(argv[2]);			/* M is the number of threads */
	
    //N = 10;
    //M=2
	fwSetNumThreads(M);
	
    gettimeofday(&T1, NULL); /* remember the current time T1 */

    unsigned int seed = 0;

    for (i = 0; i < 50; i++) /* 50 experiments50 experiments */
    {
        double M1[N] ,M2[(int)(N/2)];
        srand(i); /*  initialize the initial value of the RNG*/
        int A = 40;
        for(j = 0; j < N; j++){/* Fill the initial data array with size N */
            M1[j] = rand_r(&seed)%A;
            while(M1[j]==0.0){
                M1[j] = rand_r(&seed)%A;
            }
            
        }
        for(j = 0; j < N/2; j++){
            M2[j] =rand_r(&seed) %(A*10);
            
        }
        /*  Complete the task, fill in the array with the results */
        /* Map Stage.  */
        fwsDivC_64f(M1,M_E,M1,N);
        fwsPowx_64f_A50(M1,1.0/3,M1,N); 
        
        /* operation in the M2 array*/
        
        double M2_temp[(int)(N/2)+1];
        M2_temp[0] = 0;
        fwsCopy_64f(M2, &M2_temp[1], N/2);
        
        fwsAdd_64f(M2, M2_temp, M2_temp, N/2);
        fwsSin_64f_A50(M2,M2,N/2);
        fwsAbs_64f(M2,M2,N/2);
        fwsPowx_64f_A50(M2_temp, 3, M2, N/2);
        
        /* Merge Stage.*/
        fwsMin_64f(M1,N/2,M2);

        /*  Sort the array with the results by the specified method */
        /* Insert sort */
        for(int j=1;j<(int)N/2;j++)
        {
            double key=M2[j];
            int i=j-1;
            while(i>=0&&M2[i]>key)
            {
                M2[i+1]=M2[i];
                i--;
            }
            M2[i+1]=key;
        }

        
        /* Reduce Stage. determining parity */
        double min = M2[0];
       // printf("M2: ");
     //   for(j = 0; j < N/2; j++){/* show the M2  using for test*/
//             printf(" %f ",M2[j]);
      //  }
      
        double sum = 0;
        for(j = 0; j < N/2; j++){
            int tmp = (int)(M2[j]/min);
            if(tmp%2==0.0)
                sum = sum + sin(M2[j]);  
        }
       // printf("X: %f\n",sum);
	
    }
    

    gettimeofday(&T2, NULL);

    /* remember the current time T2 */

    delta_ms = 1000 * (T2.tv_sec - T1.tv_sec) + (T2.tv_usec - T1.tv_usec) / 1000;

    printf("\nN=%d. Milliseconds passed: %ld\n", N, delta_ms); /* T2 -T1 */
    return 0;
}
