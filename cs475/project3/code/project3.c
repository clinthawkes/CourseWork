#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#define M_PI           3.14159265358979323846  /* pi */

    
float Ranf(unsigned int*, float, float);
float SQR(float);
void GrainDeer();
void Grain();
void Watcher();
void MyAgent();

const float GRAIN_GROWS_PER_MONTH =		9.0;
const float ONE_DEER_EATS_PER_MONTH =	1.0;
const float AVG_PRECIP_PER_MONTH =		7.0;			// average
const float AMP_PRECIP_PER_MONTH =		6.0;			// plus or minus
const float RANDOM_PRECIP =				2.0;			// plus or minus noise
const float AVG_TEMP =					60.0;	        // average
const float AMP_TEMP =					20.0;	// plus or minus
const float RANDOM_TEMP =				10.0;	// plus or minus noise
const float MIDTEMP =					40.0;
const float MIDPRECIP =					10.0;

int	NowYear;		    // 2020 - 2025
int	NowMonth;		    // 0 - 11
int	NowNumDeer;	    // number of deer in the current population
float NowPrecip;	    // inches of rain per month
float NowTemp;		    // temperature this month
float NowHeight;	    // grain height in inches
float NowFire;		    // percent on fire
unsigned int seed = 0;  // a thread-private variable


int main(int argc, char *argv[]){
        
    // starting date and time:
    NowMonth =    0;
    NowYear  = 2020;

    // starting state (feel free to change this if you want):
    NowNumDeer = 1;
    NowHeight =  1.;
    NowFire = 1.; 
    
    float ang = (30. * (float)NowMonth + 15.) * (M_PI / 180.);

    float temp = AVG_TEMP - AMP_TEMP * cos( ang );
    NowTemp = temp + Ranf( &seed, -RANDOM_TEMP, RANDOM_TEMP );
    NowTemp = (5./9.)*(NowTemp - 32); 

    float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
    NowPrecip = precip + Ranf( &seed,  -RANDOM_PRECIP, RANDOM_PRECIP );
    NowPrecip *= 2.54; 
    if( NowPrecip < 0. ) NowPrecip = 0.;
    
    
    seed = (int)time(NULL); 
        
    omp_set_num_threads( 4 );	// same as # of sections
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            GrainDeer( );
        }

        #pragma omp section
        {
            Grain( );
        }

        #pragma omp section
        {
            Watcher( );
        }

        #pragma omp section
        {
            MyAgent( );	// your own
        }
    }       // implied barrier -- all functions must return in order
        
    return 0;  
} 


void GrainDeer(){
    while(NowYear < 2026){
        int tempNumber = NowNumDeer;
        int fireScaler; 
        
        if(NowFire < 1){
            fireScaler = 2; 
        }
            
        if(tempNumber > NowHeight){
            tempNumber -= fireScaler;
        }else if(tempNumber < NowHeight){
            tempNumber++;
        }
        
        
        
        if(tempNumber < 0) tempNumber = 0; 
        
        // DoneComputing barrier:
        #pragma omp barrier
        
        NowNumDeer = tempNumber; 
        
        // DoneAssigning barrier:
        #pragma omp barrier

        // DonePrinting barrier:
        #pragma omp barrier
    }
}


void Grain(){
    while(NowYear < 2026){
        float fTemp = (NowTemp * (9./5.)) + 32;
        float iPrec = NowPrecip/2.54;  
        float tempFactor = exp(-SQR((fTemp - MIDTEMP)/10.));
        float precipFactor = exp(-SQR((iPrec - MIDPRECIP)/10.));
	    float tempHeight = NowHeight / 2.54;

        tempHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
        tempHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;
        if(tempHeight < 0.) tempHeight = 0.; 
        tempHeight *= 2.54; 
        tempHeight *= NowFire; 
	   
        // DoneComputing barrier:
        #pragma omp barrier

        NowHeight = tempHeight;
       
        // DoneAssigning barrier:
        #pragma omp barrier

        // DonePrinting barrier:
        #pragma omp barrier
    }
}


void Watcher(){
    printf("NowYear NowMonth NowNumDeer NowHeight NowPrecip NowTemp NowFire\n"); 
    
    while(NowYear < 2026){
        
        // DoneComputing barrier:
        #pragma omp barrier

        // DoneAssigning barrier:
        #pragma omp barrier
        printf("%d\t%d\t%d\t%.3f\t%.3f\t%.3f\t%.3f\n", NowYear, NowMonth, NowNumDeer, NowHeight, NowPrecip, NowTemp, NowFire); 
        //printf("NowFire: %.3f\n", NowFire);        
        NowMonth++;
        if(NowMonth%12 == 0) NowYear++;
        
        float ang = (30. * (float)NowMonth + 15.) * (M_PI / 180.);

        float temp = AVG_TEMP - AMP_TEMP * cos( ang );
        NowTemp = temp + Ranf( &seed, -RANDOM_TEMP, RANDOM_TEMP );
        NowTemp = (5./9.)*(NowTemp - 32); 

        float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
        NowPrecip = precip + Ranf( &seed,  -RANDOM_PRECIP, RANDOM_PRECIP );
        NowPrecip *= 2.54; 
        if( NowPrecip < 0. ) NowPrecip = 0.;
        
        // DonePrinting barrier:
        #pragma omp barrier
    }
}


void MyAgent(){
    while(NowYear < 2026){
	   
	    float tempFire = 1;
	    float tempHeat = NowTemp - 15.;
	    float tempRain = 28. - NowPrecip;
        //printf("tempHeat: %.3f   tempRain: %.3f\n", tempHeat, tempRain); 
	    if((tempHeat + tempRain) > 0) {
		    tempFire -= SQR((tempHeat + tempRain)) / 2000.;
            //printf("tempFire = %.3f\n", tempFire); 
	    }
        // DoneComputing barrier:
        #pragma omp barrier

	    NowFire = tempFire;

        // DoneAssigning barrier:
        #pragma omp barrier

        // DonePrinting barrier:
        #pragma omp barrier
    }
}


float SQR( float x ){
    return x*x;
}


float Ranf(unsigned int *seedp,  float low, float high){
        float r = (float) rand_r( seedp );              // 0 - RAND_MAX
        return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}
