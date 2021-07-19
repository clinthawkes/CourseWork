#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <omp.h>

#define XMIN        -1.
#define XMAX        1.
#define YMIN        -1.
#define YMAX        1.
#define N           4

#ifndef NUMT
#define NUMT        1
#endif

#ifndef NUMNODES 
#define NUMNODES    10
#endif


float Height( int, int );

int main( int argc, char *argv[ ] ){

    omp_set_num_threads(NUMT); 
    
	// the area of a single full-sized tile:
	float fullTileArea = (  ( ( XMAX - XMIN )/(float)(NUMNODES-1) )  *
				( ( YMAX - YMIN )/(float)(NUMNODES-1) )  );

    double maxPerformance = 0;
    double volume; 
        
    for(int i = 0; i < 10; i++){ 
        
        volume = 0; 
            
        double time0 = omp_get_wtime(); 
        
        // sum up the weighted heights into the variable "volume"
        // using an OpenMP for loop and a reduction:
        #pragma omp parallel for default(none),shared(fullTileArea),reduction(+:volume)
        for( int i = 0; i < NUMNODES*NUMNODES; i++ ){
            
            int iu = i % NUMNODES;
            int iv = i / NUMNODES;
            float z = 2. * Height( iu, iv );
           
            if((iu == 0 || iu == (NUMNODES - 1)) && (iv == 0 || iv == (NUMNODES - 1))){
                volume += 0.25 * fullTileArea * z;
            }else if(iu == 0 || iu == (NUMNODES - 1) || iv == 0 || iv == (NUMNODES - 1)){
                volume += 0.5 * fullTileArea * z;
            }else{
                volume += fullTileArea * z;
            }
        }
            
        double time1 = omp_get_wtime(); 
        double megaVolumeCalcs = (double)NUMNODES * NUMNODES / (time1 - time0) /1000000;
        if(megaVolumeCalcs > maxPerformance) maxPerformance = megaVolumeCalcs; 
    } 

    printf("MegaVolumeCalcs/sec = %8.2lf\n", maxPerformance); 
    printf("Volume = %8.2lf\n", volume); 
    
}


float Height( int iu, int iv ){
	float x = -1.  +  2.*(float)iu /(float)(NUMNODES-1);	// -1. to +1.
	float y = -1.  +  2.*(float)iv /(float)(NUMNODES-1);	// -1. to +1.

	float xn = pow( fabs(x), (double)N );
	float yn = pow( fabs(y), (double)N );
	float r = 1. - xn - yn;
	if( r < 0. )
	        return 0.;
	float height = pow( 1. - xn - yn, 1./(float)N );
	return height;
}
