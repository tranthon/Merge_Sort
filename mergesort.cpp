// Thong Tran
//CS350

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <chrono>

void randomize(int *, int);

void randomize(int * arr, int length) {
    for(int i = 0; i < length; ++i) {
        arr[i] = rand() % length;
    }
}


void copy_array(int *, int *, int, int);

void copy_array(int * arrA, int * arrB, int start, int end) {
    int j = 0;
    for(int i = start; i < end; ++i) {
        arrB[j] = arrA[i];
        ++j;
    }
}

void copy_array(int *, int *, int, int, int);

void copy_array(int * arrA, int * arrB, int startA, int endA, int startB) {
    int j = startB;
    for(int i = startA; i < endA; ++i) {
        arrB[j] = arrA[i];
        ++j;
    }
}

void print_array(int *, int);

void print_array(int * arr, int length) {
    for(int i = 0; i < length; ++i) {
        std::cout << arr[i] << std::endl;
    }
}
void merge(int *, int *, int *, int, int, int);

void merge(int * arrB, int * arrC, int * arrA, int lengthB, int lengthC, int lengthA) {
    //i, j, k are the index positions we're currently working with in the 3 arrays
    int i, j, k;
    i = 0;
    j = 0;
    k = 0;
    
    while(i < lengthB && j < lengthC) {
        //Here, we check which subarray contains the smaller leading element
        if(arrB[i] <= arrC[j]) {
            arrA[k] = arrB[i];
            ++i;
        }
        else {
            arrA[k] = arrC[j];
            ++j;
        }
        ++k;
    }
    if(i == lengthB) {
        copy_array(arrC, arrA, j, lengthC, k);
    }
    else {
        copy_array(arrB, arrA, i, lengthB, k);
    }
}

void mergesort(int *, int);

void mergesort(int * arrA, int length) {
    // If length > 1, we run the mergesort.
    // If length == 1, the array is already sorted
    if(length > 1) {
        //Divide by 2 to get the division index
        int left_size = length / 2;
        int right_size = length - left_size;
        
        //Create two arrays to hold the values from the left
        //and right of the division index.
        int * arrB = new int[left_size];
        int * arrC = new int[right_size];
        
        //Copy the values in array A from indices 0 to n/2 - 1 into array B
        copy_array(arrA, arrB, 0, left_size);
        
        //Copy the values in array A from indices n/2 to n-1 into array B
        copy_array(arrA, arrC, left_size, length);
        
        //Run mergesort on the divided arrays (Divide and conquer!)
        mergesort(arrB, left_size);
        mergesort(arrC, right_size);
        
        //Merge the sorted arrays together together
        merge(arrB, arrC, arrA, left_size, right_size, length);
    }
}

void test_randomize(int *, int);

int main(int argc, char * argv[]) {
  const int SIZE = atoi(argv[1]);
  int * arr = new int[SIZE];
  std::ofstream myfile;

  randomize(arr, SIZE);
  std::cout << "Merge Sort Starting" << std::endl;
  auto t_start = std::chrono::high_resolution_clock::now();
  mergesort(arr, SIZE);
  auto t_end = std::chrono::high_resolution_clock::now();

  std::cout << "The size of the array is: " << SIZE << std::endl;
  //Using the chrono library to allow us to work with milliseconds much easier
  std::cout << "Elapsed time: "
            << std::chrono::duration<double, std::milli>(t_end-t_start).count()
            << " ms\n";
  //Writing the results out to a text file made it easier to automate the whole testing process
  myfile.open(argv[2], std::fstream::out | std::fstream::app);
  myfile << std::chrono::duration<double, std::milli>(t_end-t_start).count() << '\n';
  return 0;
}
