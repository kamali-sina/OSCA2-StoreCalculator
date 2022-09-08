#include "parser.hpp"
#include "forker.hpp"

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
    ofstream ofile;
    ofile.open("./result.out");
    yourfile.open(commands_path, ios::in | ios::app);
    while(getline(yourfile,line)){
        int result = fork_main(line, asset_dir);
        cout<<"result was: "<<result<<endl;
        ofile<<result<<endl;
    }
    ofile.close();
    yourfile.close();
    return 0;
}