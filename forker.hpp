#ifndef H_FORKER
#define H_FORKER
#include "parser.hpp"

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h> 

#define NAMEDPIPE "./namedpipes/"

using namespace std;

int fork_main(string line, string asset_dir);

#endif