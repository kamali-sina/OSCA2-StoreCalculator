#include "parser.hpp"

vector<string> get_items_in_folder(string path){
    vector<string> result;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (path.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if (strcmp (ent->d_name,".") != 0 &&
                strcmp (ent->d_name,"..") != 0)
                result.push_back(ent->d_name);
        }
        closedir(dir);
    }else {
        cout<<"directory "<<path<<" did not exist" <<endl;
        exit(-1);
    }
    return result;
}

int date_to_timestamp(string date){
    date.erase(remove(date.begin(), date.end(), '/'), date.end());
    return stoi(date);
}

vector<int> parse_csv_line(string line, char split_by){
    vector<int> result;
    stringstream line_stream(line);
    string segment;
    int i = 0;
    while(getline(line_stream, segment, split_by))
    {
        if (i == 0)
            result.push_back(date_to_timestamp(segment));
        else
            result.push_back(stoi(segment));
        i++;
    }
    return result;
}

vector<string> parse_line(string line, char split_by){
    vector<string> result;
    stringstream line_stream(line);
    string segment;
    int i = 0;
    while(getline(line_stream, segment, split_by))
    {
        result.push_back(segment);
    }
    return result;
}

vector<vector<int>> parse_file(string path){
    vector<vector<int>> table;
    string line;
    fstream file;
    file.open(path, ios::in | ios::app);
    getline(file,line);
    while(getline(file,line)){
        table.push_back(parse_csv_line(line, ','));
    }
    return table;
}

string replace_char(string line,char replace, char orig){
    for (int i = 0; i < line.length(); i++){
        if (line[i] == orig){
            line[i] = replace;
        }
    }
    return line;
}