#include <xmmintrin.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>
#define SSE_WIDTH		4

#ifndef ARR_SIZE
#define ARR_SIZE        16384 
#endif

float A[ARR_SIZE];
float B[ARR_SIZE];


float SimdMulSum( float *a, float *b, int len ){
	float sum[4] = { 0., 0., 0., 0. };
	int limit = ( len/SSE_WIDTH ) * SSE_WIDTH;
	register float *pa = a;
	register float *pb = b;

	__m128 ss = _mm_loadu_ps( &sum[0] );
	for( int i = 0; i < limit; i += SSE_WIDTH )
	{
		ss = _mm_add_ps( ss, _mm_mul_ps( _mm_loadu_ps( pa ), _mm_loadu_ps( pb ) ) );
		pa += SSE_WIDTH;
		pb += SSE_WIDTH;
	}
	_mm_storeu_ps( &sum[0], ss );

	for( int i = limit; i < len; i++ )
	{
		sum[0] += a[i] * b[i];
	}

	return sum[0] + sum[1] + sum[2] + sum[3];
}


int main(int argc, char *argv[]){
    
    double mySum0; 
    double mySum1; 
    double maxSIMD = 0., maxREG = 0.; 
    
    for(int i = 0; i < ARR_SIZE; i++){
        A[i] = 1.;
        B[i] = 2.;
    }        
    
    for(int j = 0; j < 10; j++){ 
        mySum0 = 0.; 
        mySum1 = 0.; 
        
        double time0 = omp_get_wtime();

        mySum0 = (double)SimdMulSum(&A[0], &B[0], ARR_SIZE);     

        double time1 = omp_get_wtime();
        
        double megaMultSum = (double)ARR_SIZE / (time1 - time0) / 1000000;    
        if(megaMultSum > maxSIMD) maxSIMD = megaMultSum; 
        
        
        time0 = omp_get_wtime();
        
        for(int i = 0; i < ARR_SIZE; i++){
            mySum1 += (double)(A[i] * B[i]);
        }
        
        time1 = omp_get_wtime();
        
        megaMultSum = (double)ARR_SIZE / (time1 - time0) / 1000000;    
        if(megaMultSum > maxREG) maxREG = megaMultSum; 
    } 
    double speedup = maxSIMD/maxREG; 
    
    printf("SIMD_performance: %.2lf\n", maxSIMD); 
    printf("Non-SIMD_performance: %.2lf\n", maxREG); 
    printf("Speedup: %.2lf\n\n", speedup);  
    
    
    return 0;
}
