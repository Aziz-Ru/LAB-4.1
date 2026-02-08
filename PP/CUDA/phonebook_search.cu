
%%writefile phonebook_search.cu
#include<bits/stdc++.h>
#include<cuda_runtime.h>

using namespace std;

struct Contact{
  char name[100];
  char number[45];
};

// substring search
__device__ bool check(char *a, char *b, int len){
  // a = phone number থেকে search করবে
  // b = query (যা খুঁজছি)
  // len = query এর length (null terminator ছাড়া)
  
  for(int i=0; a[i]!='\0'; i++){  //  পুরো string শেষ পর্যন্ত
    int j=0;
    while(a[i+j]!='\0' && b[j]!='\0' && a[i+j]==b[j]){
      j++;
    }
    if(j==len-1){  //  actual length match (null terminator বাদে)
      return true;
    }
  }
  return false;
  
}

__global__ void search(Contact *phonebook, int num_contact, char *query, int query_length){

  int id = threadIdx.x+blockIdx.x*blockDim.x;
  if(id<num_contact){
      if(check(phonebook[id].number,query,query_length)){
        printf("%s %s\n",phonebook[id].name,phonebook[id].number);
      }
    }
}


int main(int argc, char *argv[]){
  if(argc!=5){
    cerr<<"Usage:"<<argv[0]<< " "<<"\n";
    return 1;
  }
  string query = string(argv[1])+" "+argv[2]+" "+argv[3];
  int num_threads=atoi(argv[4]);

  string file_name = "/content/phonebook.txt";

  vector<Contact> phonebook;

  ifstream file(file_name);
  if(!file.is_open()){
    cerr<<"Error opening file"<<endl;
    return 1;
  }else{
    Contact contact;
    string line;
      while(getline(file,line)){
        if(line.empty())continue;
        int pos = line.find(",");
        if(pos==string::npos) continue;
        string raw_name = line.substr(0,pos);
        string raw_number = line.substr(pos+1);
        string name = raw_name.substr(1,(int)raw_name.size()-2);
        string number = raw_number.substr(1,(int)raw_number.size()-2);
        strcpy(contact.name,name.c_str());
        strcpy(contact.number,number.c_str());
        phonebook.push_back(contact);
      }
      file.close();


    }
    int num_contact = phonebook.size();
    cout<<"Total contact:"<<num_contact<<endl;
    cout<<"Query:"<<query<<endl;
    cout<<"Fist Name: "<<phonebook[0].name<<endl;
    cout<<"Phone Number: "<<phonebook[0].number<<endl;
    Contact *d_phonebook;
    cudaMalloc(&d_phonebook,num_contact*sizeof(Contact));
    cudaMemcpy(d_phonebook,phonebook.data(),num_contact*sizeof(Contact),cudaMemcpyHostToDevice);
    char *d_query;
   int query_length = query.size()+1;
    cudaMalloc(&d_query,query_length);
    cudaMemcpy(d_query,query.c_str(),query_length,cudaMemcpyHostToDevice);
    
    for(int i=0;i<num_contact;i+=num_threads){
      int current_batch = min(num_contact-i,num_threads);
      search<<<1,current_batch>>>(d_phonebook+i,current_batch,d_query,query_length);
      cudaDeviceSynchronize();
    }
    cudaFree(d_phonebook);
    cudaFree(d_query);
  return 0;
}
// !nvcc -gencode arch=compute_75,code=sm_75 phonebook_search.cu -o ps
// !time ./ps 011 72 866 100
