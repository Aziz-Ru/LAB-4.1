// this code is for matrix multiplication using cuda in colab
%%writefile matrix_mul.cu
#include<bits/stdc++.h>
#include<cuda_runtime.h>

using namespace std;

__global__ void matrix_mul(float *A,float *B, float *C, int M,int N,int P,int offset){
  int k = threadIdx.x+offset;
  float *a = A+k*M*N;
  float *b = B+k*N*P;
  float *c = C+k*M*P;

  for(int i=0;i<M;i++){
    for(int j=0;j<N;j++){
      for(int l=0;l<P;l++){
        c[i*P+l]+=a[i*N+j]*b[j*P+l];
      }
    }
  }

}

void printOneMatrix(float* A, int k, int M, int N) {
    cout << "Matrix index = " << k << endl;
    float* base = A + k * M * N;

    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++) {
            cout << base[i * N + j] << " ";
        }
        cout << endl;
    }
}

int main(int argc,char *argv[]){

  int noOfThread = atoi(argv[1]);
  int noOfMatrix = atoi(argv[2]);
  

  int M=3,N=3,P=3;
  // 1 Dim arrays
  int sizeA=M*N*noOfMatrix;
  int sizeB=N*P*noOfMatrix;
  int sizeC=M*P*noOfMatrix;
  // memory allocation in cpu
  float *h_a =new float[sizeA];
  float *h_b =new float[sizeB];
  float *h_c =new float[sizeC];
//  memset(h_c, 0, sizeC * sizeof(float));

  // memory allocation in gpu
  float *d_a;
  cudaMalloc(&d_a,sizeA*sizeof(float));
  float *d_b;
  cudaMalloc(&d_b,sizeB*sizeof(float));
  float *d_c;
  cudaMalloc(&d_c,sizeC*sizeof(float));

  for(int i=0;i<sizeA;i++){
    h_a[i]=rand()%10;
  }
  for(int i=0;i<sizeB;i++){
    h_b[i]=rand()%10;
  }
  // copy from host to device
  cudaMemcpy(d_a,h_a,sizeA*sizeof(float),cudaMemcpyHostToDevice);
  cudaMemcpy(d_b,h_b,sizeB*sizeof(float),cudaMemcpyHostToDevice);

  // kernel launch
  int offset =0;
  int a=noOfMatrix;
  while(a>0){
    int currentBatch = min(a,noOfThread);
    matrix_mul<<<1,currentBatch>>>(d_a,d_b,d_c,M,N,P,offset);
    cudaDeviceSynchronize(); 
    a-=currentBatch;
    offset+=currentBatch;

  }

  cudaMemcpy(h_c,d_c,sizeC*sizeof(float),cudaMemcpyDeviceToHost);

  for(int k = 0; k < 3; k++) {
      cout << "\n=== MATRIX SET " << k << " ===\n";

      cout << "A[" << k << "]\n";
      printOneMatrix(h_a, k, M, N);

      cout << "B[" << k << "]\n";
      printOneMatrix(h_b, k, N, P);

      cout << "C[" << k << "]\n";
      printOneMatrix(h_c, k, M, P);
  }

  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);
  free(h_a);
  free(h_b);
  free(h_c);

  cout<<"ALL OPERATION DONT\n";

  return 0;
}

// !nvcc -gencode arch=compute_75,code=sm_75 matrix_mul.cu -o ma
// !time ./ma 1 10