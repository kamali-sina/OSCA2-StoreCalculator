// #include "forker.hpp"

// int fork_town(string line){
//     vector<string> dupped_message = parse_line(line, '|');
//     vector<string> folders = get_items_in_folder(dupped_message[1]);
//     vector<int> results;
//     if (folders.size() == 0){
//         cout<<"folder "<< dupped_message[1] <<" was empty"<<endl;
//         return -1;
//     }
//     for (int i = 0 ; i < folders.size() ; i++){
//         int pipefd[2];
//         pipe(pipefd);
//         int pid = fork();
//         if (pid == -1){
//             cout<<"something's wrong, I can feel it"<<endl;
//             return -1;
//         }else if (pid == 0){
//             char baboole[200];
//             read(pipefd[0], &baboole, 200);
//             string message = baboole;
//             do_op(message);
//             exit(-1);
//         }
//         //send message to child
//         string message = line + "/" + folders[i];
//         string path = dupped_message[1] + "/" + folders[i];
//         write(pipefd[1], message.c_str(),message.length() + 1);
//         int fd = ready_read_namedpipe(path);
//         wait(&pid);
//         int result = read_from_namedpipe(fd);
//         if (result != -1)
//             results.push_back(result);
//     }
//     send_to_parent(results, dupped_message);
//     return 0;
// }

// int fork_provinence(string line){
//     vector<string> dupped_message = parse_line(line, '|');
//     vector<string> folders = get_items_in_folder(dupped_message[1]);
//     vector<int> results;
//     if (folders.size() == 0){
//         cout<<"folder "<< dupped_message[1] <<" was empty"<<endl;
//         return -1;
//     }
//     for (int i = 0 ; i < folders.size() ; i++){
//         int pipefd[2];
//         pipe(pipefd);
//         int pid = fork();
//         if (pid == -1){
//             cout<<"something's wrong, I can feel it"<<endl;
//             return -1;
//         }else if (pid == 0){
//             char baboole[200];
//             read(pipefd[0], &baboole, 200);
//             string message = baboole;
//             fork_town(message);
//             exit(-1);
//         }
//         //send message to child
//         string message = line + "/" + folders[i];
//         string path = dupped_message[1] + "/" + folders[i];
//         write(pipefd[1], message.c_str(),message.length() + 1);
//         int fd = ready_read_namedpipe(path);
//         wait(&pid);
//         int result = read_from_namedpipe(fd);
//         if (result != -1)
//             results.push_back(result);
//     }
//     send_to_parent(results, dupped_message);
//     return 0;
// }

// int fork_assets(string line){
//     vector<string> dupped_message = parse_line(line, '|');
//     vector<string> folders = get_items_in_folder(dupped_message[1]);
//     vector<int> results;
//     if (folders.size() == 0){
//         cout<<"folder "<< dupped_message[1] <<" was empty"<<endl;
//         return -1;
//     }
//     for (int i = 0 ; i < folders.size() ; i++){
//         int pipefd[2];
//         pipe(pipefd);
//         int pid = fork();
//         if (pid == -1){
//             cout<<"something's wrong, I can feel it"<<endl;
//             return -1;
//         }else if (pid == 0){
//             char baboole[200];
//             read(pipefd[0], &baboole, 200);
//             string message = baboole;
//             fork_provinence(message);
//             exit(-1);
//         }
//         //send message to child
//         string message = line + "/" + folders[i];
//         string path = dupped_message[1] + "/" + folders[i];
//         write(pipefd[1], message.c_str(),message.length() + 1);
//         int fd = ready_read_namedpipe(path);
//         wait(&pid);
//         int result = read_from_namedpipe(fd);
//         if (result != -1)
//             results.push_back(result);
//     }
//     send_to_parent(results, dupped_message);
//     return 0;
// }