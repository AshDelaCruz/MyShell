//
//  mycommands.hpp
//  Project_Phase2
//
//  Created by Earl Ashleigh M. Dela Cruz on 3/6/17.
//  Copyright © 2017 Earl Ashleigh M. Dela Cruz. All rights reserved.
//

#ifndef mycommands_hpp
#define mycommands_hpp

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int read(char **);
void parse(int, char **);
bool quit(std::string);

void cat(char **);
void cp(char **);
void grep(char**, int);
void stat(char**);
void diff(char **);
void timeout(char **, int);


#endif /* mycommands_hpp */
