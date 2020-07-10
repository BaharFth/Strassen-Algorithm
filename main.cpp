//Strassen Algorithm Implementation
//Approach 1
//by Bahar Fathi
//July 2020
#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <sstream>

using namespace std;

//define data types
typedef int dataType ;  //can be modified to other types like float, double etc.
typedef vector< vector <dataType>> Matrix;
typedef vector<Matrix> matrixVector;

//Functions------------------------------------------------------------------

//Recursive Strassen for multiplying two matrices of size NxN, where N is a power of 2
//This function uses a recursive algorithm, where matrices A and B are each broken into
//four matrices containing their four quarters (corner matrices).
void recursiveStrassen( Matrix &A, Matrix &B, Matrix &C);

//Print all elements of a Matrix
void display(Matrix &A , string matrixName);

//Add two Matrices
void addMatrices(Matrix &A , Matrix &B, Matrix &C);

//Brute force (standard) matrix multiplication
void bruteForceMultiply(Matrix &A , Matrix &B, Matrix &C);

//Recursive Strassen for multiplying two matrices of size NxN, where n is a power of 2
void recursiveStrassen( Matrix &A, Matrix &B, Matrix &C);

//Make a matrix of all zeros of size NxN
Matrix intitializeMatrix(int N);

//returns a matrix of the xth and yth quarter of A
void cornerMatrix(Matrix &A, Matrix &Axy,int x, int y);

//Combines the four corner matrices (N/2 * N/2) into Matrix A of size N*N
void fillCornerMatrices(Matrix &A, vector<Matrix> &cornersA);

//Makes a vector containing four all zero matrices of size N
void initializeCornerMatrices (matrixVector & cornersVector, int N);

//Displays corner Matrices of A
void displayCornerMatrices (matrixVector & cornersVector );

//Make a matrixVactor with 7 all 0 matrices (M1 to M7)
void initializeM1toM7Matrices (matrixVector & M1toM7Vector, int N);

//Displays all matrices saved in a matrixVector
void displaMatrixVector (matrixVector & MVector );

//Subtract two Matrices
Matrix subtractMatrices(Matrix &A , Matrix &B);

//inserts Axy at x and y corner of A
void insertCornerMatrix(Matrix &A, Matrix &Axy,int x, int y);

//fills a given Matrix A with its corner matrices
void insertAllCornerMatrices(Matrix &A, matrixVector &cornersA);


//Main---------------------------------------------------------------------
int main()
{
    Matrix A = {{1, 2, 4,0}, {3 ,-1 ,1 , 0},{3, 0, -2, 1},{0 ,1 ,-2, 3}};
    Matrix B = {{-2,1 ,0 ,-1},{-1,3 ,2 ,1}, {2,1,0,-2}, {2, 3, 1, 0}};

    //Matrix A = {{1, 2}, {3 ,-1 }};
    //Matrix B = {{-2,1},{-1,3}};

    int N = A.size();

    //C=A*B is calculated by two algorithms 1. Strassen 2. Standard (brute force)
    //The results are printed for comparison

    // There should be a way around the need to initializing a Matrix in advance
    // Not sure why my code does not compile without this initialization. tried
    // different strategies, need to look into it when there is time
    Matrix C = intitializeMatrix(N);
    recursiveStrassen(A,B,C);
    display(C, "C by Strassen");

    Matrix D = intitializeMatrix(N);
    bruteForceMultiply(A,B,D);
    display(C, "C by Brute Force");

    return 0;
}


//Functions--------------------------------------------------------

//Print all elements of a Matrix
void display(Matrix &A, string matrixName) { // Display a Vector
    //cout<<"size = "<<A.size()<<endl;
    cout << matrixName<< " = " <<endl;
   for(int i =0 ; i< A.size();i++)
   {
        for(int j =0 ; j< A[0].size();j++)
        {
            cout << A[i][j]<<"     ";
        }
        cout<<endl;
   }
    cout<<endl;
}

//Add two Matrices, void
void addMatrices(Matrix &A , Matrix &B, Matrix &C) {
    int N = A.size();
     for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
           C[i][j] = A[i][j] + B[i][j];
        }
     }
}

//Add two Matrices, return a Matrix
Matrix addMatrices(Matrix &A , Matrix &B) {
    int N = A.size();
    Matrix C = intitializeMatrix(N);
     for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
           C[i][j] = A[i][j] + B[i][j];
        }
     }
     return C;
}

//Subtract two Matrices, return a Matrix
Matrix subtractMatrices(Matrix &A , Matrix &B) {
    int N = A.size();
    Matrix C = intitializeMatrix(N);
     for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
           C[i][j] = A[i][j] - B[i][j];
        }
     }
     return C;
}

//find all corner matrices of a given Matrix A
void fillCornerMatrices(Matrix &A, vector<Matrix> &cornersA)
{
    int k = 0;
    for (int i = 0; i<2; i++)
    {
        for (int j = 0; j<2; j++)
        {
            cornerMatrix(A, cornersA[k], i, j);
            k++;
        }
    }

}
//Brute force (standard) matrix multiplication for two Matrices of size 2x2
void bruteForceMultiply(Matrix &A , Matrix &B, Matrix &C) {  //Calculating A*B->C
     int N = A.size();
     for(int i=0; i<N; i++)
     {
        for(int j=0; j<N; j++)
        {
           C[i][j] = 0;
           for(int t=0; t<N; t++)
           {
              C[i][j] = C[i][j] + A[i][t]*B[t][j];
           }
        }
     }
}


//Recursive Strassen for multiplying two matrices of size NxN, where N is a power of 2
void recursiveStrassen( Matrix &A, Matrix &B, Matrix &C)
{
    //Matrix Size
    int N = A.size();
    //cout<<"Strassen, Matrix size = "<<N<<endl;

    //If the matrices are down to size 2, use standard algorithm
    if (N == 2)
    {
        bruteForceMultiply(A , B, C);
        //cout<<"Base Case"<<endl;
        //cout<<endl;
    }

    //else, use Strassen calculations
    else
    {
        //cout<<"Entered Recursion"<<endl;
        //cout<<endl;

        // three matrixVectors to save corners of Matrices A, B, C,
        matrixVector cornersA, cornersB, cornersC;

        //Initialize corner matrices with all zeros
        //Fill the corner matrices with corresponding elements
        initializeCornerMatrices (cornersA, N);
        fillCornerMatrices(A, cornersA);
        initializeCornerMatrices (cornersB, N);
        fillCornerMatrices(B, cornersB);
        initializeCornerMatrices (cornersC, N);

        //Make a matrixVactor containing 7 all-zero matrices (M1 to M7)
        matrixVector    M1toM7Vector;
        initializeM1toM7Matrices (M1toM7Vector, N);

        // S1 to S7  save Matrices that would then be passed to calculate M1 to M7
        // No need to make these vectors. I only had to make them because
        // otherwise my IDE gives me an error. Need to take care of it
        // when there is time
        Matrix S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14;
        S1 = addMatrices(cornersA[0] , cornersA[3]);
        S2 = addMatrices(cornersB[0],cornersB[3]);
        S3 = addMatrices(cornersA[2], cornersA[3]);
        S4 = cornersB[0];
        S5 = cornersA[0];
        S6 = subtractMatrices(cornersB[1],cornersB[3]);
        S7 = cornersA[3];
        S8 = subtractMatrices(cornersB[2],cornersB[0]);
        S9 = addMatrices(cornersA[0],cornersA[1]);
        S10 = cornersB[3];
        S11= subtractMatrices(cornersA[2], cornersA[0]);
        S12= addMatrices(cornersB[0],cornersB[1]);
        S13= subtractMatrices(cornersA[1],cornersA[3]);
        S14= addMatrices(cornersB[2],cornersB[3]);

        //run 7 threads for Strassen Matrices M1 to M7
        thread M1Thread (recursiveStrassen, ref(S1), ref(S2), ref(M1toM7Vector[1]));
        thread M2Thread (recursiveStrassen, ref(S3),ref(S4), ref(M1toM7Vector[2]));
        thread M3Thread (recursiveStrassen, ref(S5), ref(S6), ref(M1toM7Vector[3]));
        thread M4Thread (recursiveStrassen, ref(S7), ref(S8), ref(M1toM7Vector[4]));
        thread M5Thread (recursiveStrassen, ref(S9), ref(S10), ref(M1toM7Vector[5]));
        thread M6Thread (recursiveStrassen, ref(S11), ref(S12), ref(M1toM7Vector[6]));
        thread M7Thread (recursiveStrassen, ref(S13), ref(S14), ref(M1toM7Vector[7]));

        //Make all other threads to wait until the above threads are complete
        M1Thread.join();
        M2Thread.join();
        M3Thread.join();
        M4Thread.join();
        M5Thread.join();
        M6Thread.join();
        M7Thread.join();

        // Calculate the result matrix
        // Again I had to define intermediate matrices due to
        // IDE compilation issue. Need to figure out a way.
        Matrix P1 = addMatrices(M1toM7Vector[1] , M1toM7Vector[4]);
        Matrix P2 = addMatrices(M1toM7Vector[5] , M1toM7Vector[7]);
        Matrix P3 = subtractMatrices(M1toM7Vector[1],M1toM7Vector[2]);
        Matrix P4 = addMatrices(M1toM7Vector[3],M1toM7Vector[6]);

        //find the four corner matrices of C and combine them to make C
        cornersC[0]= subtractMatrices(P1, P2);
        cornersC[1]= addMatrices(M1toM7Vector[3],M1toM7Vector[5]);
        cornersC[2]= addMatrices(M1toM7Vector[2],M1toM7Vector[4]);
        cornersC[3]= addMatrices(P3,P4);
        insertAllCornerMatrices(C, cornersC);

    }

}


//Make a matrix of all zeros of size NxN
Matrix intitializeMatrix(int N)
{
    Matrix C;
    vector<int> C0 = {};
    for(int i =0 ; i< N; i++) C.push_back (C0);
   for(int i =0 ; i< N; i++)
   {
        for(int j =0 ; j< N;j++)
        {
            C[i].push_back(0);
        }
   }
    return C;
}

//fills a given corner of the matrix
void insertCornerMatrix(Matrix &A, Matrix &Axy,int x, int y)
{
     int N = A.size();
     for(int i =0; i< N/2; i++)
     {
         for(int j= 0; j< N/2; j++)
         {
             A[i+ x*(N/2)][j+y*(N/2)] = Axy[i][j];
         }
     }
}

//fills a given Matrix A with its corner matrices
void insertAllCornerMatrices(Matrix &A, matrixVector &cornersA)
{
    int k = 0;
    for(int i =0; i< 2; i++)
    {
        for(int j= 0; j< 2; j++)
        {
            insertCornerMatrix(A, cornersA[k], i, j);
            k++;
        }
    }
}

//Finds a corner Matrix of A
void cornerMatrix(Matrix &A, Matrix &Axy,int x, int y)
{
     int N = A.size();
     for(int i =0; i< N/2; i++)
     {
         for(int j= 0; j< N/2; j++)
         {
             Axy[i][j] = A[i+ x*(N/2)][j+y*(N/2)];
         }

     }
}

//Makes a vector containing four all-zero matrices of size N/2
void initializeCornerMatrices (matrixVector & cornersVector, int N)
{
    Matrix temp = intitializeMatrix(N/2);
    for (int i= 0; i <4 ; i++)
    {
        cornersVector.push_back(temp);
    }
}

//Make a matrixVactor with 7 all 0 matrices (M1 to M7)
void initializeM1toM7Matrices (matrixVector & M1toM7Vector, int N)
{
    Matrix temp = intitializeMatrix(N/2);
    //The vector will include 7 matrices, but the Matrix at 0 will not be used
    Matrix dummy = {{}};
    M1toM7Vector.push_back(dummy);
    for (int i= 0; i <7 ; i++)
    {
        M1toM7Vector.push_back(temp);
    }
}

//Displays the four matrices saved in a matrixVector
void displayCornerMatrices (matrixVector & cornersVector )
{
    int k = 0;
    for (int i = 0; i<2; i++)
    {
        for (int j = 0; j<2; j++)
        {
            //cornerMatrix(A, cornersA[k], i, j);
            stringstream stream;
            stream << "corner[" << i<<"]["<<j<<"]";
            display(cornersVector[k], stream.str());
            k++;
        }
    }
}

//Displays the all matrices saved in a matrixVector
void displaMatrixVector (matrixVector & MVector )
{
    for (int i= 0; i < MVector.size() ; i++)
    {
        stringstream stream;
        stream << "matrixVector[" << i<<"]";
        display(MVector[i], stream.str());
    }
}
