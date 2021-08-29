#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>



/* the Variant is A=40 and other variants are 6 1 5 6*/
int main(int argc, char *argv[])
{

    int i, N,j;

    struct timeval T1, T2;

    long delta_ms;

    N = atoi(argv[1]); /* N equals the first command-line parameter */

    //N = 10;

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
        for(j = 0; j < N; j++){
            M1[j] = pow((M1[j]/M_E),1.0/3);
            
        }
        /* operation in the M2 array*/
        double M2_temp[(int)(N/2)];
        
        for(j = 0; j < N/2; j++){
            M2_temp[j] = M2[j];
            
        }
        for(j = 0; j < N/2; j++){
            if(j==0) M2[j] = fabs(sin(M2[j]+0.0));
            else M2[j] = fabs(sin(M2[j]+M2_temp[j-1]));
        }
        /* Merge Stage.*/
        for(j = 0; j < N/2; j++){
            if(M1[j]<M2[j]) M2[j]=M1[j];
            
        }

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
//        printf("M2: ");
//        for(j = 0; j < N/2; j++){/* show the M2  using for test*/
//             printf(" %f ",M2[j]);
//        }
//      
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
