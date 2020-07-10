//Strassen by Bahar- Recursive
#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <sstream>
using namespace std;

typedef int dataType ;
typedef vector< vector <dataType>> Matrix;
typedef vector<Matrix> matrixVector;
//Functions

//Print all elements of a Matrix
void display(Matrix &A , string matrixName);

//Add two Matrices
void addMatrices(Matrix &A , Matrix &B, Matrix &C);

//Brute force (standard) matrix multiplication for two Matrices of size 2x2
void bruteForceMultiply(Matrix &A , Matrix &B, Matrix &C);

//Recursive Strassen for multiplying two matrices of size nxn, where n is a power of 2
void recursiveStrassen( Matrix &A, Matrix &B, Matrix &C);

void combineMatrix(Matrix* C, Matrix* C00 , Matrix* C01 , Matrix* C10, Matrix* C11);

//Make a matrix of all zeros of size NxN
Matrix intitializeMatrix(int N);

//returns a matrix of the xth and yth quarter of A
void cornerMatrix(Matrix &A, Matrix &Axy,int x, int y);

void fillCornerMatrices(Matrix &A, vector<Matrix> &cornersA);

//Makes a vector containing four all zero matrices of size N
void initializeCornerMatrices (matrixVector & cornersVector, int N);

void displayCornerMatrices (matrixVector & cornersVector );

//Make a matrixVactor with 7 all 0 matrices (M1 to M7)
void initializeM1toM7Matrices (matrixVector & M1toM7Vector, int N);

//Displays the all matrices saved in a matrixVector
void displaMatrixVector (matrixVector & MVector );

//Subtract two Matrices
Matrix subtractMatrices(Matrix &A , Matrix &B);

//inserts Axy at x and y corner of A
void insertCornerMatrix(Matrix &A, Matrix &Axy,int x, int y);

//fills a given Matrix A with its corner matrices
void insertAllCornerMatrices(Matrix &A, matrixVector &cornersA);

//Main
int main()
{
    Matrix A = {{1, 2, 4,0}, {3 ,-1 ,1 , 0},{3, 0, -2, 1},{0 ,1 ,-2, 3}};
    Matrix B = {{-2,1 ,0 ,-1},{-1,3 ,2 ,1}, {2,1,0,-2}, {2, 3, 1, 0}};

    //Matrix A = {{1, 2}, {3 ,-1 }};
    //Matrix B = {{-2,1},{-1,3}};

    int N = A.size();

    //display(A, "A");
    //display(B, "B");

    Matrix C = intitializeMatrix(N);
    recursiveStrassen(A,B,C);
    display(C, "C by Strassen");

    Matrix D = intitializeMatrix(N);
    bruteForceMultiply(A,B,D);
    display(C, "C by Brute Force");

    /*Matrix D = intitializeMatrix(4);
    display(D, "D before");
    matrixVector cornersD =
    {
        {{1,2},{3,4}},
        {{5,6},{7,7}},
        {{9,10},{11,12}},
        {{13,14},{15,16}}
    };

    insertAllCornerMatrices(D,cornersD);
    display(D, "D after");*/

    return 0;
}


//Functions

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

//Add two Matrices
void addMatrices(Matrix &A , Matrix &B, Matrix &C) {
    int N = A.size();
     for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
           C[i][j] = A[i][j] + B[i][j];
        }
     }
}

//Add two Matrices
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

//Subtract two Matrices
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

//Recursive Strassen for multiplying two matrices of size nxn, where n is a power of 2
void recursiveStrassen( Matrix &A, Matrix &B, Matrix &C)
{
    cout<<"recursiveStrassen():"<<endl;
    //display(A, "A");
    //display(B, "B");
    //display(C, "C");
    //Matrix Size
    int N = A.size();

    if (N == 2)
    {
        bruteForceMultiply(A , B, C);
        //display(C, "C");
    }

    else
    {
        // matrixVectors to save corners of Matrices A, B, C,
        matrixVector cornersA, cornersB, cornersC;

        //Initialize corner matrices with all zeros
        //Fill the corner matrices with corresponding elements
        initializeCornerMatrices (cornersA, N);
        fillCornerMatrices(A, cornersA);
        //cout<<"corners of A:"<<endl;
        //displayCornerMatrices(cornersA);

        initializeCornerMatrices (cornersB, N);
        fillCornerMatrices(B, cornersB);
        //cout<<"corners of B:"<<endl;
        //displayCornerMatrices(cornersB);

        initializeCornerMatrices (cornersC, N);
        //cout<<"corners of C:"<<endl;
        //displayCornerMatrices(cornersC);

        //Make a matrixVactor with 7 all 0 matrices (M1 to M7)
        matrixVector    M1toM7Vector;
        initializeM1toM7Matrices (M1toM7Vector, N);
        //Displays the all matrices saved in a matrixVector
        //displaMatrixVector (M1toM7Vector);

        Matrix S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14;
        S1 = addMatrices(cornersA[0] , cornersA[3]);
        S2 = addMatrices(cornersB[0],cornersB[3]);
        S3= addMatrices(cornersA[2], cornersA[3]);
        S4= cornersB[0];
        /*display(S1, "S1");
        display(S1, "S2");*/
        recursiveStrassen(S1,S2,M1toM7Vector[1]);

        /*display(S3, "S3");
        display(S4, "S4");*/

        recursiveStrassen(S3,S4, M1toM7Vector[2]);

        S5 = cornersA[0];
        S6 = subtractMatrices(cornersB[1],cornersB[3]);
        recursiveStrassen(S5,S6,M1toM7Vector[3]);

        S7 = cornersA[3];
        S8 = subtractMatrices(cornersB[2],cornersB[0]);
        recursiveStrassen(S7,S8,M1toM7Vector[4]);

        S9 = addMatrices(cornersA[0],cornersA[1]);
        S10 = cornersB[3];
        recursiveStrassen (S9, S10, M1toM7Vector[5]);

        S11= subtractMatrices(cornersA[2], cornersA[0]);
        S12= addMatrices(cornersB[0],cornersB[1]);
        recursiveStrassen(S11,S12,M1toM7Vector[6]);

        S13= subtractMatrices(cornersA[1],cornersA[3]);
        S14= addMatrices(cornersB[2],cornersB[3]);
        recursiveStrassen(S13,S14,M1toM7Vector[7]);


        // pauses the rest of the function until the above threads finish
        /*
        M1Thread.join();
        M2Thread.join();
        M3Thread.join();
        M4Thread.join();
        M5Thread.join();
        M6Thread.join();
        M7Thread.join();
        */

        // Calculate the result matrix
        Matrix P1 = addMatrices(M1toM7Vector[1] , M1toM7Vector[4]);
        Matrix P2 = addMatrices(M1toM7Vector[5] , M1toM7Vector[7]);
        Matrix P3 = subtractMatrices(M1toM7Vector[1],M1toM7Vector[2]);
        Matrix P4 = addMatrices(M1toM7Vector[3],M1toM7Vector[6]);
        cornersC[0]= subtractMatrices(P1, P2);
        cornersC[1]= addMatrices(M1toM7Vector[3],M1toM7Vector[5]);
        cornersC[2]= addMatrices(M1toM7Vector[2],M1toM7Vector[4]);
        cornersC[3]= addMatrices(P3,P4);
        insertAllCornerMatrices(C, cornersC);

    }
    for (int i = 0; i<N; i++)
    {
        cout<<"-";
    }
    cout<<endl;
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
void cornerMatrix(Matrix &A, Matrix &Axy,int x, int y)
{
     //cout<<"Corner Matrix"<<endl;
     int N = A.size();
     for(int i =0; i< N/2; i++)
     {
         //cout<<"i = "<<i<<endl;
         for(int j= 0; j< N/2; j++)
         {
             //cout<<"j = "<<j<<endl;
             //cout<<A[i+ x*(N/2)][j+y*(N/2)]<<endl;
             Axy[i][j] = A[i+ x*(N/2)][j+y*(N/2)];
         }

     }
}
//Makes a vector containing four all zero matrices of size N/2
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

    /*for (int i= 0; i <4 ; i++)
    {
        stringstream stream;
        stream << "corner[" << i<<"] , ["<<j;
        display(cornersVector[i], "Corner Matrix");
    }*/
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

    //display(C, "C = intitializeMatrix(N)");

    //bruteForceMultiply(A , B, C);
    //display(C, "C = bruteForceMultiply(A , B, C)= ");

    //addMatrices(A , B, C);
    //display(C, "C = addMatrices(A , B, C)");

    //Matrix A00, A01, A10, cornersA[3];
    //vector <Matrix> cornersA;

    //initializeCornerMatrices (cornersA, N);
    //displayCornerMatrices (cornersA);

    //fillCornerMatrices(A, cornersA);
    //displayCornerMatrices (cornersA);

    //display(A00, "A00 = cornerMatrix");
