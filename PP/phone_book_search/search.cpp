#include<bits/stdc++.h>
#include<mpi.h>
#include<string.h>

using namespace std;

struct Contact{
  string name;
  string phone;
};


void send_message(string &msg, int receiver){
  int len = msg.size()+1;
  MPI_Send(&len,1,MPI_INT,receiver,0,MPI_COMM_WORLD);
  MPI_Send(msg.c_str(),len,MPI_CHAR,receiver,0,MPI_COMM_WORLD);
}

string receive_message(int source){
  int len;
  MPI_Recv(&len,1,MPI_INT,source,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
  char *buf = new char[len];
  MPI_Recv(buf,len,MPI_CHAR,source,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
  string msg(buf);
  delete[] buf;
  return msg;
}

string vector_to_string(vector<Contact>&contact, int start,int end){
  string res ="";
  for(int i=start;i<min(end,(int)contact.size());i++){
    res+=contact[i].name+" "+contact[i].phone+"\n";
  }
  return res;
}

vector<Contact> generate_contacts(string &text){
  vector<Contact> contact;
  istringstream ss(text);
  string line;
  while(getline(ss,line)){
    if(line.empty())continue;
    int pos = line.find(" ");
    if(pos == string::npos) continue;
    Contact c;
    c.name = line.substr(0,pos);
    c.phone = line.substr(pos+1);
    contact.push_back(c);
  }
  return contact;
}

string toLower(string s){
  string res="";
  for(char c:s){
    res+=tolower(c);
  }
  return res;
}

string check(const Contact &c, const string &query){
  string name = toLower(c.name);
  string search_lower = toLower(query);
  if(name.find(search_lower)!=string::npos){
    return c.name+" "+c.phone+"\n";
  }
  return "";
  
}

void read_file(const vector<string>&files,vector<Contact>&contacts){
  for(const string &file:files){
    ifstream f(file);
    string line;
    while(getline(f,line)){
      if(line.empty()) continue;
      int comma = line.find(" ");
      if(comma == string::npos) continue;
      Contact c;
      c.name = line.substr(0,comma);
      c.phone = line.substr(comma+1);
      contacts.push_back(c);
    }
  }
}

int main(int argc, char *argv[]){

  int rank,size;
  MPI_Init(&argc,&argv);
  
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  double start_time,end_time;

  if(argc<3){
    if(rank==0){
      cout<<"Usage: mpirun -np <num_processes> ./a.out <contact_file> <query>\n";
    }
    MPI_Finalize();
    return 0;
  }
  // last argument is query
  string query = argv[argc-1];
  
  // master process reads the files and distributes the contacts to worker processes
  if(rank == 0){
    // read all contacts from different files
    vector<string> files(argv+1,argv+argc-1);
    vector<Contact> all_contacts;
    read_file(files,all_contacts);
    // no of contacts and chunk size for each process
    int total=all_contacts.size();
    int chunk = (total+size-1)/size;
    start_time = MPI_Wtime();
    // distribute contacts to worker processes
    for(int i=1;i<size;i++){
      // convert contacts to string and send to worker process
      string msg = vector_to_string(all_contacts,i*chunk,(i+1)*chunk);
      send_message(msg,i);
    }
    // result
    string result;
    // master process also checks its own chunk of contacts
    for(int i=0;i<min(chunk,total);i++){
     string  res=check(all_contacts[i],query);
     if(!res.empty()){
       result+=res;
     }
    }

    end_time = MPI_Wtime();
    // receive results from worker processes
    for(int i=1;i<size;i++){
      string r=receive_message(i);
      if(!r.empty()){
        result+=r;
      }
    }

    ofstream out("result.txt");
    out<<result;
    out.close();
    printf("Time taken by process %d is %lf seconds\n",rank,end_time-start_time);

  } else{
    string msg = receive_message(0);
    vector<Contact> contacts = generate_contacts(msg);
    start_time = MPI_Wtime();
    string result;
    for(const Contact &c:contacts){
      string res = check(c,query);
      if(!res.empty()){
        result+=res;
      }
    }
    end_time = MPI_Wtime();
    send_message(result,0);
    printf("Time taken by process %d is %lf seconds\n",rank,end_time-start_time);

  }
  
  MPI_Finalize();
  return 0;
}



/*
    How to run:
    mpic++ -o search phonebook_search.cpp
    mpirun -np 4 ./search phonebook1.txt Bob

    time mpirun -np 8 --oversubscribe --bind-to core:overload-allowed --map-by core ./ps labtest_dataset1.txt Bob
    
*/
