#include "forker.hpp"

int make_namedpipe(string name){
    mkfifo(name.c_str(), 0666);
    return 0;
}

int write_to_namedpipe(int number, string path){
    path = replace_char(path, '.','/');
    string name = NAMEDPIPE + path;
    string message = to_string(number);
    int fd; 
    fd = open(name.c_str(), O_WRONLY);
    write(fd, message.c_str(), message.length() + 1); 
    close(fd);
    return 0;
}

int ready_read_namedpipe(string path){
    path = replace_char(path, '.', '/');
    string name = NAMEDPIPE + path;
    make_namedpipe(name);
    int fd = open(name.c_str(), O_RDONLY); 
    return fd;
}

int read_from_namedpipe(int fd){
    char buff[200];
    read(fd, buff, 200);
    string message = buff;
    close(fd);
    return stoi(message);
}

int send_to_parent(vector<int> results, vector<string> dupped_message){
    string path = dupped_message[1];
    vector<string> dupped_command = parse_line(dupped_message[0],' ');
    if (results.size() == 0){
        write_to_namedpipe(-1,path);
    }else{
        int result = results[0];
        for (int i = 1; i < results.size(); i++){
            if (dupped_command[0] == "MAX"){
                if (result < results[i])
                    result = results[i];
            }else{
                if (result > results[i])
                    result = results[i];
            }
        }
        write_to_namedpipe(result,path);
    }
    return 0;
}

int do_op(string line){
    vector<string> dupped_message = parse_line(line, '|');
    string path = dupped_message[1];
    vector<vector<int>> store_file = parse_file(dupped_message[1]);
    vector<string> dupped_command = parse_line(dupped_message[0], ' ');
    string command = dupped_command[0];
    int fileid = stoi(dupped_command[1]);
    int start_date = date_to_timestamp(dupped_command[2]);
    int end_date = date_to_timestamp(dupped_command[3]);
    vector<vector<int>> lines_we_want;
    for (int i = 0; i < store_file.size(); i++) {
        if ((store_file[i][0] >= start_date) && (store_file[i][0] <= end_date) && (store_file[i][1] == fileid)) {
            lines_we_want.push_back(store_file[i]);
        }
    }
    if (lines_we_want.size() == 0){
        write_to_namedpipe(-1,path);
    }else{
        int result = lines_we_want[0][2];
        for (int i = 1; i < lines_we_want.size(); i++){
            if (command == "MAX"){
                if (result < lines_we_want[i][2])
                    result = lines_we_want[i][2];
            }else{
                if (result > lines_we_want[i][2])
                    result = lines_we_want[i][2];
            }
        }
        write_to_namedpipe(result,path);
    }
    return 0;
}

/* 
line is a coded string of command|cur_path
count is used for the recursive handling of the code
*/
int forker(string line, int count){
    vector<string> dupped_message = parse_line(line, '|');
    vector<string> folders = get_items_in_folder(dupped_message[1]);
    vector<int> results;
    if (folders.size() == 0){
        cout<<"warning: folder "<< dupped_message[1] <<" was empty"<<endl;
        send_to_parent(results, dupped_message);
    }
    for (int i = 0 ; i < folders.size() ; i++){
        int pipefd[2];
        pipe(pipefd);
        int pid = fork();
        if (pid == -1){
            cout<<"error: something's wrong, fork failed"<<endl;
            return -1;
        }else if (pid == 0){
            char baboole[200];
            read(pipefd[0], &baboole, 200);
            string message = baboole;
            if (count >= MAXDEPTH)
                do_op(message);
            else
                forker(message, count+1);
            exit(-1);
        }else{
            //send message to child
            string message = line + "/" + folders[i];
            string path = dupped_message[1] + "/" + folders[i];
            write(pipefd[1], message.c_str(),message.length() + 1);
            int fd = ready_read_namedpipe(path);
            wait(&pid);
            int result = read_from_namedpipe(fd);
            if (result != -1)
                results.push_back(result);
        }
    }
    send_to_parent(results, dupped_message);
    return 0;
}

/* 
used for forking the main process to handle a command.
line is the command
asset_dir is the path to the asset directory
*/
int fork_main(string line, string asset_dir){
    int result = -1;
    int state;
    int pipefd[2];
    pipe(pipefd);
    int pid = fork();
    if (pid == -1){
        cout<<"error: something's wrong, fork failed"<<endl;
        exit(-1);
    }else if (pid == 0){
        sleep(0.1);
        char baboole[200];
        string message;
        read(pipefd[0], &baboole, 200);
        message = baboole;
        forker(message,0);
        exit(-1);
    }else{
        string message = line + "|./" + asset_dir;
        write(pipefd[1], message.c_str(),message.length() + 1);
        string path = "./" + asset_dir;
        int fd = ready_read_namedpipe(path);
        wait(&pid);
        result = read_from_namedpipe(fd);
    }
    return result;
}