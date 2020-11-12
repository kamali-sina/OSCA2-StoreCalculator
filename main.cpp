#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include <fstream>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 

using namespace std;

int main(int argc, char* argv[]){
    if (argc < 3){
        cout<<"Not enough arguments were provided\n";
        exit(0);
    }
    string line;
    string commands_path = argv[1];
    string asset_dir = argv[2];
    fstream yourfile;
    yourfile.open(commands_path, ios::in | ios::app);
    while (getline(yourfile,line)){
        cout<<line<<endl;
        //fork main thing here with line and asset_dir
    }
    return 0;
}

/* 
unnamed pipe:

int pipefd[2];
pipe(pipefd);
write(pipefd[1], "kossssss",strlen("kossssss") + 1);
char baboole[100];
read(pipefd[0], &baboole, strlen("kossssss") + 1);
*/

/*
named pipe:

char buf[100];
int fd; 
char myfifo[] = "./myfifo"; 
mkfifo(myfifo, 0666);
fd = open(myfifo, O_WRONLY);
write(fd, "ya ya ya", strlen("ya ya ya") + 1); 
cout<<"wrote shit"<<endl;
close(fd);
fd = open(myfifo, O_RDONLY); 
read(fd, buf, sizeof("ya ya ya") + 1);
cout<<"read shit"<<endl;
cout << "read: "<<buf<<endl;
*/