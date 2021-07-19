#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>
#include <xmmintrin.h>
#include "cl.h"
#include "cl_platform.h"

#define	LOCAL_SIZE		64
#define SSE_WIDTH		4

const char*	CL_FILE_NAME = { "first.cl" };

void Wait( cl_command_queue );
float SimdMulSum( float *a, int len, int shift );


int main( int argc, char *argv[ ] ){
	// see if we can even open the opencl kernel program
	// (no point going on if we can't):
	FILE *fp = fopen( "signal.txt", "r" );

	if( fp == NULL ){
		fprintf( stderr, "Cannot open file 'signal.txt'\n" );
		exit( 1 );
	}

	int Size;
	fscanf( fp, "%d", &Size );
	float *hA =     new float[ 2*Size ];
	float *hSums  = new float[ 1*Size ];

	for( int i = 0; i < Size; i++ ){
		fscanf( fp, "%f", &hA[i] );
		hA[i+Size] = hA[i];		// duplicate the array
	}
	fclose( fp );


	//********************************************//
	//****** Summation using NO parallelism ******//
	//********************************************//
	omp_set_num_threads(1);
	double time0 = omp_get_wtime();
	#pragma omp parallel for default(none), shared(hA, hSums, Size)
	for( int shift = 1; shift < Size; shift++ )
	{
		float sum = 0.;
		for( int i = 0; i < Size; i++ )
		{
			sum += hA[i] * hA[i + shift];
		}
		hSums[shift] = sum;	// note the "fix #2" from false sharing if you are using OpenMP
	}
	double time1 = omp_get_wtime();

	fprintf( stdout, "Base Performance: %10.3lf MegaMultsPerSecond\n", (double)(Size*Size)/(time1-time0)/1000000. );
	for(int i = 1; i <= 512; i++){
		printf("%10.5f ", hSums[i]);
		if(i%26 == 0) printf("\n");
	}
	printf("\n\n");

	memset(hSums, 0, Size*sizeof(float));


	//********************************************//
	//****** Summation using 4 cores openMP ******//
	//********************************************//
	omp_set_num_threads(4);
	time0 = omp_get_wtime();
	#pragma omp parallel for default(none), shared(hA, hSums, Size)
	for( int shift = 1; shift < Size; shift++ )
	{
		float sum = 0.;
		for( int i = 0; i < Size; i++ )
		{
			sum += hA[i] * hA[i + shift];
		}
		hSums[shift] = sum;	// note the "fix #2" from false sharing if you are using OpenMP
	}
	time1 = omp_get_wtime();

	fprintf( stdout, "OpenMP Performance: %10.3lf MegaMultsPerSecond\n", (double)(Size*Size)/(time1-time0)/1000000. );
	for(int i = 1; i <= 512; i++){
		printf("%10.5f ", hSums[i]);
		if(i%26 == 0) printf("\n");
	}
	printf("\n\n");

	memset(hSums, 0, Size*sizeof(float));


	//********************************************//
	//********* Summation using CPU SIMD *********//
	//********************************************//
	time0 = omp_get_wtime();
	for( int shift = 1; shift < Size; shift++ )
	{
		hSums[shift] = SimdMulSum(&hA[0], Size, shift);	// note the "fix #2" from false sharing if you are using OpenMP
	}
	time1 = omp_get_wtime();

	fprintf( stdout, "SIMD Performance: %10.3lf MegaMultsPerSecond\n", (double)(Size*Size)/(time1-time0)/1000000. );
	for(int i = 1; i <= 512; i++){
		printf("%10.5f ", hSums[i]);
		if(i%26 == 0) printf("\n");
	}
	printf("\n\n");

	memset(hSums, 0, Size*sizeof(float));



	//********************************************//
	//********** Summation using openCL **********//
	//********************************************//

	fp = fopen( CL_FILE_NAME, "r" );
	if( fp == NULL ){
		fprintf( stderr, "Cannot open OpenCL source file '%s'\n", CL_FILE_NAME );
		return 1;
	}

	cl_int status;		// returned status from opencl calls

	// get the platform id:

	cl_platform_id platform;
	status = clGetPlatformIDs( 1, &platform, NULL );
	if( status != CL_SUCCESS )
		fprintf( stderr, "clGetPlatformIDs failed (2)\n" );
	
	// get the device id:

	cl_device_id device;
	status = clGetDeviceIDs( platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL );
	if( status != CL_SUCCESS )
		fprintf( stderr, "clGetDeviceIDs failed (2)\n" );


	// 3. create an opencl context:

	cl_context context = clCreateContext( NULL, 1, &device, NULL, NULL, &status );
	if( status != CL_SUCCESS )
		fprintf( stderr, "clCreateContext failed\n" );

	// 4. create an opencl command queue:

	cl_command_queue cmdQueue = clCreateCommandQueue( context, device, 0, &status );
	if( status != CL_SUCCESS )
		fprintf( stderr, "clCreateCommandQueue failed\n" );

	// 5. allocate the device memory buffers:
	
	cl_mem dA = clCreateBuffer( context, CL_MEM_READ_ONLY,  2*Size*sizeof(cl_float), NULL, &status );
	if( status != CL_SUCCESS )
		fprintf( stderr, "clCreateBuffer failed (1)\n" );
		
	cl_mem dSums  = clCreateBuffer( context, CL_MEM_WRITE_ONLY, 1*Size*sizeof(cl_float), NULL, &status );
	if( status != CL_SUCCESS )
		fprintf( stderr, "clCreateBuffer failed (2)\n" );

    
	// 6. enqueue the 2 commands to write the data from the host buffers to the device buffers:

	status = clEnqueueWriteBuffer( cmdQueue, dA, CL_FALSE, 0, 2*Size*sizeof(cl_float), hA, 0, NULL, NULL );
	if( status != CL_SUCCESS )
		fprintf( stderr, "clEnqueueWriteBuffer failed (1)\n" );


	Wait( cmdQueue );

	// 7. read the kernel code from a file:

	fseek( fp, 0, SEEK_END );
	size_t fileSize = ftell( fp );
	fseek( fp, 0, SEEK_SET );
	char *clProgramText = new char[ fileSize+1 ];		// leave room for '\0'
	size_t n = fread( clProgramText, 1, fileSize, fp );
	clProgramText[fileSize] = '\0';
	fclose( fp );
	if( n != fileSize )
		fprintf( stderr, "Expected to read %d bytes read from '%s' -- actually read %d.\n", fileSize, CL_FILE_NAME, n );

	// create the text for the kernel program:

	char *strings[1];
	strings[0] = clProgramText;
	cl_program program = clCreateProgramWithSource( context, 1, (const char **)strings, NULL, &status );
	if( status != CL_SUCCESS )
		fprintf( stderr, "clCreateProgramWithSource failed\n" );
	delete [ ] clProgramText;

	// 8. compile and link the kernel code:

	char *options = { "" };
	status = clBuildProgram( program, 1, &device, options, NULL, NULL );
	if( status != CL_SUCCESS )
	{
		size_t size;
		clGetProgramBuildInfo( program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &size );
		cl_char *log = new cl_char[ size ];
		clGetProgramBuildInfo( program, device, CL_PROGRAM_BUILD_LOG, size, log, NULL );
		fprintf( stderr, "clBuildProgram failed:\n%s\n", log );
		delete [ ] log;
	}

	// 9. create the kernel object:

	cl_kernel kernel = clCreateKernel( program, "AutoCorrelate", &status );
	if( status != CL_SUCCESS )
		fprintf( stderr, "clCreateKernel failed\n" );

	// 10. setup the arguments to the kernel object:

	status = clSetKernelArg( kernel, 0, sizeof(cl_mem), &dA );
	if( status != CL_SUCCESS )
		fprintf( stderr, "clSetKernelArg failed (1)\n" );

	status = clSetKernelArg( kernel, 1, sizeof(cl_mem), &dSums );
	if( status != CL_SUCCESS )
		fprintf( stderr, "clSetKernelArg failed (2)\n" );


	// 11. enqueue the kernel object for execution:

	size_t globalWorkSize[3] = { Size, 1, 1 };
	size_t localWorkSize[3]  = { LOCAL_SIZE, 1, 1 };

	Wait( cmdQueue );

	time0 = omp_get_wtime( );

	status = clEnqueueNDRangeKernel( cmdQueue, kernel, 1, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL );
	if( status != CL_SUCCESS )
		fprintf( stderr, "clEnqueueNDRangeKernel failed: %d\n", status );

	Wait( cmdQueue );
	time1 = omp_get_wtime( );

	// 12. read the results buffer back from the device to the host:

	status = clEnqueueReadBuffer( cmdQueue, dSums, CL_TRUE, 0, Size*sizeof(cl_float), hSums, 0, NULL, NULL );
	if( status != CL_SUCCESS )
			fprintf( stderr, "clEnqueueReadBuffer failed\n" );

    
	fprintf( stdout, "openCL Performance: %10.3lf MegaMultsPerSecond\n", (double)(Size*Size)/(time1-time0)/1000000. );
	for(int i = 1; i <= 512; i++){
		printf("%10.5f\n", hSums[i]);
		/* if(i%26 == 0) printf("\n"); */
	}
	printf("\n\n");


	// 13. clean everything up:

	clReleaseKernel(        kernel   );
	clReleaseProgram(       program  );
	clReleaseCommandQueue(  cmdQueue );
	clReleaseMemObject(     dA  );
	clReleaseMemObject(     dSums  );

	delete [ ] hA;
	delete [ ] hSums;

	return 0;
}


void Wait( cl_command_queue queue ){
	cl_event wait;
	cl_int status;

	status = clEnqueueMarker( queue, &wait );
	if( status != CL_SUCCESS )
		fprintf( stderr, "Wait: clEnqueueMarker failed\n" );

	status = clWaitForEvents( 1, &wait );
	if( status != CL_SUCCESS )
		fprintf( stderr, "Wait: clWaitForEvents failed\n" );
}


float SimdMulSum( float *a, int len, int shift ){
	
	float sum[4] = { 0., 0., 0., 0. };
	int limit = ( len/SSE_WIDTH ) * SSE_WIDTH;
	register float *pa = a;

	__m128 ss = _mm_loadu_ps( &sum[0] );
	for( int i = 0; i < limit; i += SSE_WIDTH ){
		ss = _mm_add_ps( ss, _mm_mul_ps( _mm_loadu_ps( pa ), _mm_loadu_ps( pa + shift)));
		pa += SSE_WIDTH;
	}

	_mm_storeu_ps( &sum[0], ss );
	
	for( int i = limit; i < len; i++ ){
		sum[0] += a[ i ] * a[ i + shift ];
	}

	return sum[0] + sum[1] + sum[2] + sum[3];
}
