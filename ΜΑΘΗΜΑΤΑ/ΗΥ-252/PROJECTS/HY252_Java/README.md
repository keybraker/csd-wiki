**Disclaimer[1]:**
> CUDA version is done, wuth testing already done, C/C++ version is done, testing is yet to be conducted.

***

# A fast implementation of machine learning classification; packaged in a small API
This API is written in C/C++ and the equivalent acceleration has been done with Nvidia CUDA

> Both versions offer the same functionallity, the difference between them is that the prior one is written in C/C++ and only uses a single thread of the computer it is run on. Whereas CUDA implements the highest of GPU accelerations to speed up the proccess.
> <br>Future work:
> * Implementation of a multithreaded C/C++ version
> * New classification algorithms

### Version Selection
* [C-C++](#c-c)
* [CUDA](#cuda)

***
## Structure for interprentation

```text
│
├── source code
|   |
|   ├── c_cpp
|   |   |
|   |   ├── multi_thread
|   |   |   |	
|   |   |   ├── aiModular.cpp	
|   |   |   ├── aiModular.hpp	
|   |   |   ├── gpBars.cpp		
|   |   |   ├── gpBars.pph		
|   |   |   ├── gpFlags.cpp		
|   |   |   ├── gpFlags.hpp		
|   |   |   ├── gpHelp.cpp		
|   |   |   ├── gpHelp.hpp		
|   |   |   ├── gpModular.cpp	
|   |   |   └── gpModular.hpp		
|   |   |
|   |   └── single_thread
|   |       |	
|   |       ├── aiModular.cpp	
|   |       ├── aiModular.hpp	
|   |       ├── gpBars.cpp		
|   |       ├── gpBars.pph		
|   |       ├── gpFlags.cpp		
|   |       ├── gpFlags.hpp		
|   |       ├── gpHelp.cpp		
|   |       ├── gpHelp.hpp		
|   |       ├── gpModular.cpp	
|   |       └── gpModular.hpp		
|   |
|   └── cuda
|       |	
|       ├── aiModular.cu	
|       ├── aiModular.h	
|       ├── gpBars.cu		
|       ├── gpBars.h		
|       ├── gpFlags.cu		
|       ├── gpFlags.h		
|       ├── gpHelp.cu		
|       ├── gpHelp.h		
|       ├── gpModular.cu	
|       ├── gpModular.h	
|       └── Makefile		
|
├── datasets
|   |
|   └── dataset.bin
|
├── benchmarks
|   |
|   ├── timer.sh
|   └── timerPipe.sh
|
└── gpgpu_classification_API.md
```

***

## C-C++
* [aiModular.cpp](#aimodularcpp)
* [gpFlags.cpp / gpFlags.hpp](#gpflagscpp--gpflagshpp)
* [gpBars.cpp / gpBars.hpp](#gpbarscpp--gpbarshpp)
* [gpHelp.cpp / gpHelp.hpp](#gphelpcpp--gphelphpp)
* [gpModular.cpp / gpModular.hpp](#gpmodularcpp--gpmodularhpp)

***

## aiModular.cpp
aiModular is the core of the program. It holds the main and the function of every implementation (currently on a fully connected implementation has been done)

* [classification_version_one](#classification_version_one)
* [main](#main)

### classification_version_one
> * Input:
<br>Gets all generated and given through arguments
> * Output:
<br>true/false, if file was freed successfully or not
> * Functionallity:
<br>Implementation of a Fully connected classification

### main
> * Input:
<br>Arguments
> * Output:
<br>true/false, if file was freed successfully or not
> * Functionallity:
<br>Core of program

## gpFlags.cpp / gpFlags.hpp
gpBars has a single function that emulates a loading bar to show progress

* [readFlags](#readflags)
* [prntFlags](#prntflags)

### readFlags
> * Input:
<br>Reads all args from terminal
> * Output:
<br>none
> * Functionallity:
<br>Prints all given flags and more

### prntFlags
> * Input:
<br>Reads all stored flags
> * Output:
<br>none
> * Functionallity:
<br>Emulates a loading bar to show progress

## gpBars.cpp / gpBars.hpp
gpBars has a single function that emulates a loading bar to show progress

* [progressBar](#progressbar)

### progressBar
> * Input:
<br>currt	: current time
<br>finalt	: final time
<br>name	: task name
<br>actn	: current action name
> * Output:
<br>none
> * Functionallity:
<br>Emulates a loading bar to show progress

## gpHelp.cpp / gpHelp.hpp
gpHelp is a collection of functions that help in a variety of algorithms, by reduting repeating code

* [freeDevicesMemory](#freedevicesmemory)
* [printBench](#printbench)
* [printTime](#printtime)
* [readBinary](#readbinary)
* [fileOpener](#fileopener)
* [readArray](#readarray)
* [matrixPrint](#matrixprint)
* [matrixPrintTwo](#matrixprinttwo)

***

### freeDevicesMemory
> * Input:
<br>All allocated pointers from main
> * Output:
<br>none
> * Functionallity:
<br>Prints time stats

### printBench
> * Input:
<br>Time stamps from every part of execution
> * Output:
<br>none
> * Functionallity:
<br>Prints time stats

### printTime
> * Input:
> * Output:
<br>none
> * Functionallity:
<br>Prints benchmark time stats

### readBinary
> * Input:
<br>file: file pointer
<br>nimgc: number of images in file
<br>nmem: number of members in image
<br>nbyt: number of bytes in member
<br>vrbs: verbose
> * Output:
<br>An array containing all the data from bin file in uint8_t
> * Functionallity:
<br>This function reads nming RGB
<br>images from file and returns
<br>the pointer to the stored data

### fileOpener
> * Input:
<br>fname: name of file
<br>type: type of file I/O
<br>vrbs: verbose
> * Output:
<br>Returns the opened file in FILE pointer type
> * Functionallity:
<br>Opens file and returns a pointer
<br>to the open file

### readArray
> * Input:
<br>file: file pointer
<br>x: x axis size of image in file
<br>y: y axis size of image in file
<br>array: array to store data from file
<br>buffer_size: buffer size of lines in file
> * Output:
<br>none
> * Functionallity:
<br>Reads the file images with given specifications

### matrixPrint
> * Input:
<br>name: name of array to print
<br>array: array of int type
<br>x: x axis size of image in file
<br>y: y axis size of image in file
<br>z: z axis size of image in file
> * Output:
<br>none
> * Functionallity: Prints given array

### matrixPrintTwo
> * Input:
<br>name: name of array to print
<br>array: array of int type
<br>x: x axis size of image in file
<br>y: y axis size of image in file
<br>nimgc: number
<br>nRGB: z axis size of image in file
> * Output:
<br>none
> * Functionallity:
<br>Prints given array with nimg and nRGB

## gpModular.cpp / gpModular.hpp
gpModular is the source code of all machine learning classification funcitons
* [matrixCleaner](#matrixcleaner)
* [matrixConvolution](#matrixconvolution)
* [matrixPolling](#matrixpolling)
* [matrixFullyConnected](#matrixfullyconnected)

***

### matrixCleaner
> * Input:
<br>matrix pointer with its dimenssions
> * Output:
<br>none
> * Functionallity:
<br>Cleans the whole matrix by setting all of its block values to zero

```sh
...
pos_in	= 	(i * M_in)
		+ (j)
		+ (k * (N_in*M_in))
		+ (l * (N_in*M_in*nRGB));

x_cpu[pos_in] = 0;
...
```

### matrixConvolution
> * Input:
<br>input matrix pointer with its dimenssions,
<br>convoluter  matrix pointer with its dimenssions,
<br>convoluted  matrix pointer with its dimenssions
> * Output:
<br>none
> * Functionallity:
<br>Convolutes input and convoluter matrices to create the convoluted matrix

```sh
...
pos_cd = (i*M_cd)+j;
				
for(int n=0; n<N_cr; n++)
{
	for(int m=0; m<M_cr; m++)
	{
		// Convoluter array axis calculated
		pos_cr = (n*M_cr) + m;
		// Convoluted array axis calculated
		pos_in =
			((n*N_in))
			+ (m+j)
			+ (k * (N_in*M_in))
			+ (nimgc * (N_in*M_in*nRGB))
			;

			cd_cpu[pos_cd] += in_cpu[pos_in] * cr_cpu[pos_cr];
...
```

### matrixPolling
> * Input:
<br>convoluted  matrix pointer with its dimenssions,
<br>pooled  matrix pointer with its dimenssions,
<br>pooler dimenssions
> * Output:
<br>none
> * Functionallity:
<br>Pools upon the generated convoluted matrix with pooler dimensions,
<br>generating a pooled matrix from the max number at every pooler dimension fragment

```sh
...
pos_pd = (i*M_pd) + j
	//+ (i * (N_pd*M_pd)) + (nimgc * (N_pd*M_pd*nRGB));
	;

for(int n=0; n<N_pr; n++)
{
	for(int m=0; m<M_pr; m++)
	{
		// Convoluted array axis calculated
		pos_cd =
			(
			((n*M_pr)+i)
			+ (m+j)
			+ (k * (N_pr*M_pr))
			+ (nimgc * (N_pr*M_pr*nRGB))
			);

		maxSave(&pd_cpu[pos_pd], cd_cpu[pos_cd]);
...
```
* maxSave function replaces value of given pointer if it's smaller than input

### matrixFullyConnected
> * Input:
<br>fully connected matrix pointer with its dimenssions,
<br>wheights matrix pointer with its dimenssions,
<br>pooled matrix pointer with its dimenssions
> * Output:
<br>none
> * Functionallity:
<br>Generates the fully connected matrix from the pooled matrix and the wheigh matrix

```sh
...
for(int j=0; j<M_pd; j++)
{
	// Convoluted array axis calculated
	idf =
		(
			(i*M_pd)
			+ j
			+ (k * (N_pd*M_pd))
			+ (nimgc * (N_pd*M_pd*nRGB))
		);
	idp =
		(
			(i*M_pd)
			+ j
			+ (k * (N_pd*M_pd))
			+ (nimgc * (N_pd*M_pd*nRGB))
		);

	for(int m=0; m<M_wh; m++)
	{
		// Convoluted array axis calculated
		idw =
			(
				(i*M_pd)
				+ j
				+ m
				+ (k * (N_pd*M_pd))
				+ (nimgc * (N_pd*M_pd*nRGB))
			);

		fc_cpu[idf] += wh_cpu[idw] * pd_cpu[idp];
	}
}
...
```

***



















## CUDA
* [aiModular.cu](#aimodularcu)
* [gpFlags.cu / gpFlags.h](#gpflagscu--gpflagsh)
* [gpBars.cu / gpBars.h](#gpbarscu--gpbarsh)
* [gpHelp.cu / gpHelp.h](#gphelpcu--gphelph)
* [gpModular.cu / gpModular.h](#gpmodularcu--gpmodularh)

***

## aiModular.cu
aiModular is the core of the program. It holds the main and the function of every implementation (currently on a fully connected implementation has been done)

* [classification_version_one](#classification_version_one-cu)
* [main](#main-cu)

### classification_version_one (cu)
> * Input:
<br>Gets all; generated and given through arguments
> * Output:
<br>true/false, if file was freed successfully or not
> * Functionallity:
<br>Implementation of a Fully connected classification

### main (cu)
> * Input:
<br>Arguments
> * Output:
<br>true/false, if file was freed successfully or not
> * Functionallity:
<br>Core of program

## gpFlags.cu / gpFlags.h
gpBars has a single function that emulates a loading bar to show progress

* [readFlags](#readflags-cu)
* [prntFlags](#prntflags-cu)

### readFlags (cu)
> * Input:
<br>Reads all args from terminal
> * Output:
<br>none
> * Functionallity:
<br>Prints all given flags and more

### prntFlags (cu)
> * Input:
<br>Reads all stored flags
> * Output:
<br>none
> * Functionallity:
<br>Emulates a loading bar to show progress

## gpBars.cu / gpBars.h
gpBars has a single function that emulates a loading bar to show progress

* [progressBar](#progressbar-cu)

### progressBar (cu)
> * Input:
<br>currt	: current time
<br>finalt	: final time
<br>name	: task name
<br>actn	: current action name
> * Output:
<br>none
> * Functionallity:
<br>Emulates a loading bar to show progress

## gpHelp.cu / gpHelp.h
gpHelp is a collection of functions that help in a variety of algorithms, by reduting repeating code

* [freeDevicesMemory](#freedevicesmemory-cu)
* [printBench](#printbench-cu)
* [printTime](#printtime-cu)
* [readBinary](#readbinary-cu)
* [fileOpener](#fileopener-cu)
* [readArray](#readarray-cu)
* [matrixPrint](#matrixprint-cu)
* [matrixPrintTwo](#matrixprinttwo-cu)

***

### freeDevicesMemory (cu)
> * Input:
<br>All allocated pointers from main
> * Output:
<br>none
> * Functionallity:
<br>Prints time stats

### printBench (cu)
> * Input:
<br>Time stamps from every part of execution
> * Output:
<br>none
> * Functionallity:
<br>Prints time stats

### printTime (cu)
> * Input:
> * Output:
<br>none
> * Functionallity:
<br>Prints benchmark time stats

### readBinary (cu)
> * Input:
<br>file: file pointer
<br>nimgc: number of images in file
<br>nmem: number of members in image
<br>nbyt: number of bytes in member
<br>vrbs: verbose
> * Output:
<br>An array containing all the data from bin file in uint8_t
> * Functionallity:
<br>This function reads nming RGB
<br>images from file and returns
<br>the pointer to the stored data

### fileOpener (cu)
> * Input:
<br>fname: name of file
<br>type: type of file I/O
<br>vrbs: verbose
> * Output:
<br>Returns the opened file in FILE pointer type
> * Functionallity:
<br>Opens file and returns a pointer
<br>to the open file

### readArray (cu)
> * Input:
<br>file: file pointer
<br>x: x axis size of image in file
<br>y: y axis size of image in file
<br>array: array to store data from file
<br>buffer_size: buffer size of lines in file
> * Output:
<br>none
> * Functionallity:
<br>Reads the file images with given specifications

### matrixPrint (cu)
> * Input:
<br>name: name of array to print
<br>array: array of int type
<br>x: x axis size of image in file
<br>y: y axis size of image in file
<br>z: z axis size of image in file
> * Output:
<br>none
> * Functionallity: Prints given array

### matrixPrintTwo (cu)
> * Input:
<br>name: name of array to print
<br>array: array of int type
<br>x: x axis size of image in file
<br>y: y axis size of image in file
<br>nimgc: number
<br>nRGB: z axis size of image in file
> * Output:
<br>none
> * Functionallity:
<br>Prints given array with nimg and nRGB

## gpModular.cu / gpModular.h
gpModular is the source code of all machine learning classification functions
* [matrixCleaner](#matrixcleaner-cu)
* [matrixConvolution](#matrixconvolution-cu)
* [matrixPolling](#matrixpolling-cu)
* [matrixFullyConnected](#matrixfullyconnected-cu)

***

### matrixCleaner (cu)
> * Input:
<br>matrix pointer with its dimenssions
> * Output:
<br>none
> * Functionallity:
<br>Cleans the whole matrix by setting all of its block values to zero

```sh
...
pos_in = ((threadIdx.x) * M_in)
	+ (threadIdx.y)
	+ (i * (N_in*M_in))
	+ (nimgc * (N_in*M_in*nRGB));
in_gpu[pos_in] = 0;
...
```

### matrixConvolution (cu)
> * Input:
<br>input matrix pointer with its dimenssions,
<br>convoluter  matrix pointer with its dimenssions,
<br>convoluted  matrix pointer with its dimenssions
> * Output:
<br>none
> * Functionallity:
<br>Convolutes input and convoluter matrices to create the convoluted matrix

```sh
...
pos_cd = (blockIdx.x*M_cd) + blockIdx.y
	+ (i * (N_cd*M_cd))
	+ (nimgc * (N_cd*M_cd*nRGB));
pos_in = ((threadIdx.x + blockIdx.x) * M_in)
	+ (threadIdx.y + blockIdx.y)
	+ (i * (N_in*M_in))
	+ (nimgc * (N_in*M_in*nRGB));
pos_cr = (threadIdx.x*M_cr)
	+ threadIdx.y;

atomicAdd_block( &cd_gpu[pos_cd] , in_gpu[pos_in] * cr_gpu[pos_cr] );
...
```

### matrixPolling (cu)
> * Input:
<br>convoluted  matrix pointer with its dimenssions,
<br>pooled  matrix pointer with its dimenssions,
<br>pooler dimenssions
> * Output:
<br>none
> * Functionallity:
<br>Pools upon the generated convoluted matrix with pooler dimensions,
<br>generating a pooled matrix from the max number at every pooler dimension fragment

```sh
...
if(N_pd == 1 || M_pd == 1)
{
	pos_pd = (blockIdx.x * M_pd)
		+ blockIdx.y
		+ (i)
		+ (nimgc * (nRGB));
	pos_cd = ((threadIdx.x + blockIdx.x) * M_cd)
		+ (threadIdx.y + blockIdx.y)
		+ (i * (N_cd*M_cd)) + (nimgc * (N_cd*M_cd*nRGB));
}
else if(N_pd != M_pd)
{
	if(N_pd > M_pd)
	{
		pos_pd = (blockIdx.x * M_pd)
			+ blockIdx.y
			+ (i * (M_pd*M_pd)) + (nimgc * (M_pd*M_pd*nRGB));
		pos_cd = ((threadIdx.x + blockIdx.x) * M_cd)
			+ (threadIdx.y + blockIdx.y)
			+ (i * (N_cd*M_cd)) + (nimgc * (N_cd*M_cd*nRGB));
	}
	else
	{
		pos_pd = (blockIdx.x * N_pd)
				+ blockIdx.y
				+ (i * (N_pd*N_pd)) + (nimgc * (N_pd*N_pd*nRGB));
		pos_cd = ((threadIdx.x + blockIdx.x) * M_cd)
				+ (threadIdx.y + blockIdx.y)
				+ (i * (N_cd*M_cd)) + (nimgc * (N_cd*M_cd*nRGB));
		}
	}
	else if(N_pd == M_pd)
	{
		pos_pd = (blockIdx.x * M_pd)
			+ blockIdx.y
			+ (i * (N_pd*M_pd)) + (nimgc * (N_pd*M_pd*nRGB));
		pos_cd = ((threadIdx.x + blockIdx.x) * M_cd)
			+ (threadIdx.y + blockIdx.y)
			+ (i * (N_cd*M_cd)) + (nimgc * (N_cd*M_cd*nRGB));
	}
}
...
```
* maxSave function replaces value of given pointer if it's smaller than input

### matrixFullyConnected (cu)
> * Input:
<br>fully connected matrix pointer with its dimenssions,
<br>wheights matrix pointer with its dimenssions,
<br>pooled matrix pointer with its dimenssions
> * Output:
<br>none
> * Functionallity:
<br>Generates the fully connected matrix from the pooled matrix and the wheigh matrix

```sh
...
idf = (blockIdx.x*N_pd)
	+ blockIdx.y
	+ (i * (N_pd*M_pd)) + (nimgc * (N_pd*M_pd*nRGB));
idp = (threadIdx.x*N_pd)
	+ threadIdx.y
	+ (i * (N_pd*M_pd)) + (nimgc * (N_pd*M_pd*nRGB));
idw = ((blockIdx.x*N_wh)
	+ blockIdx.y
	+ ((threadIdx.x*N_wh + threadIdx.y)*M_wh));

atomicAdd_block(&fc_gpu[idf], wh_gpu[idw] * pd_gpu[idp]);
...
```

***

## Authors

* **Ioannis Tsiakkas** - *(Keybraker)* - [Keybraker](https://github.com/keybraker)
