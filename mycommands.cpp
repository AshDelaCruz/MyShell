//
//  mycommands.cpp
//  Project_Phase2
//
//  Created by Earl Ashleigh M. Dela Cruz on 3/6/17.
//  Copyright © 2017 Earl Ashleigh M. Dela Cruz. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstring>
#include <dirent.h>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include "mycommands.hpp"
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/stat.h>

using namespace std;

int read(char **argv) {
    char *cstr;
    string arg;
    int argc = 0;
    
    while (cin >> arg) {
        if (quit(arg)) {
            exit(0);
        }
        
        cstr = new char[arg.size()+1];
        std::strcpy(cstr, arg.c_str());
        argv[argc] = cstr;
        argc++;
        if (cin.get() == '\n')
            break;
    }
    
    cout << "Command: " << argv[0] << endl;
    
    for(int i = 1; i < argc; i++) {
        cout << "Arg " << i << ": " << argv[i] << endl;
    }
    
    return argc;
}

void parse(int argc, char **argv) {
    string cmd = argv[0];
    
    if(cmd == "ls")
        system(*argv);
    
    if(cmd == "pwd")
        system(*argv);
    
    if(cmd == "env")
        system(*argv);
    
    if(cmd == "mkdir") {
        if(argv[1] != NULL) {
            mkdir(argv[1], ACCESSPERMS);
        } else {
            cout << "mkdir dirName: MISSING ARGS" << endl;
        }
    }
    
    if(cmd == "rmdir") {
        if(argv[1] != NULL) {
            rmdir(argv[1]);
        } else {
            cout << "rmdir dirName: MISSING ARGS" << endl;
        }
    }
    
    
    if(cmd == "cat") {
        if(argc == 2) {
            cat(argv);
        } else
            cout<< "cat fileName: MISSING ARGS" << endl;
    }
    
    if(cmd == "cp") {
        if(argc == 3) {
            cp(argv);
        } else
            cout << "cp fileName fileName: MISSING ARGS" << endl;
    }
    
    if(cmd == "grep") {
        if(argc >= 2) {
            grep(argv, argc);
        } else
            cout << "grep searchString fileName ...: MISSING ARGS" << endl;
    }
    
    if(cmd == "cd") {
        if(argc == 2) {
            chdir(argv[1]);
        } else
            cout << "cd pathName: MISSING ARGS" << endl;
    }
    
    if(cmd == "stat") {
        if(argc == 2) {
            stat(argv);
        } else
            cout << "stat fileOrDirName: MISSING ARGS" << endl;
    }
    
    if(cmd == "sleep") {
        if(argc == 2) {
            unsigned int time = atoi(argv[1]);
            sleep(time);
        } else
            cout << "sleep numSeconds: MISSING ARGS" << endl;
    }
    
    if(cmd == "kill") {
        if(argc == 3) {
            int sig = atoi(argv[1]);
            pid_t proc = atoi(argv[2]);
            kill(proc, sig);
        } else
            cout << "kill signal processID: MISSING ARGS" << endl;
    }
    
    if(cmd == "diff") {
        if(argc == 3) {
            diff(argv);
        } else
            cout << "diff fileName fileName: MISSING ARGS" << endl;
    }
    
    if(cmd == "timeout") {
        if(argc == 3) {
            timeout(argv, argc);
        } else
            cout << "timeout timeInSecs command: MISSING ARGS" << endl;
    }
    
    if(cmd == "wait") {
        if(argc == 2) {
            pid_t proc = atoi(argv[1]);
            wait(&proc);
        }
    }
        
}



bool quit(string s) {
    return (s == "exit");
}

/***************** SHELL COMMANDS *****************/

void cat(char** argv) {
    ifstream file(argv[1]);
    if(file.good()) {
        string temp;
        while(getline(file, temp))
            cout << temp << endl;
    } else
        cout << "ERR: NO SUCH FILE OR DIRECTORY" << endl;
    
}

void cp(char** argv) {
    ifstream in(argv[1]);
    if (in.good()) {
        ofstream out(argv[2]);
        string temp;
        while(getline(in, temp))
            out << temp << endl;
        out.close();
    } else
        cout << "ERR: NO SUCH FILE OR DIRECTORY" << endl;
    
}

void grep(char** argv, int argc) {
    string key = argv[1];
    string temp;
    
    for(int i = 2; i < argc; i++) {
        ifstream in(argv[i]);
        int count = 0;
        while(getline(in, temp)) {
            if(temp.find(key) != string::npos) {
                cout << argv[i] << ", line " << count << ": " << temp << endl;
            }
            count++;
        }
    }
}

void stat(char** argv) {
    struct stat buf;
    stat(argv[1], &buf);
    dev_t     deviceId = buf.st_dev;
    ino_t     inoNum = buf.st_ino;
    mode_t    typeMode = buf.st_mode;
    nlink_t   numLinks = buf.st_nlink;
    uid_t     ownerID = buf.st_uid;
    gid_t     groupID = buf.st_gid;
    dev_t     specialDeviceId = buf.st_rdev;
    off_t     size = buf.st_size;
    blksize_t blocksize = buf.st_blksize;
    blkcnt_t  numBlocks = buf.st_blocks;
    time_t accTime = buf.st_atime;
    time_t modTime = buf.st_mtime;
    time_t chaTime = buf.st_ctime;
    
    cout << "File name:                       " << argv[1] << endl;
    cout << "ID of device containing file:    " << deviceId << endl;
    cout << "Inode Number:                    " << inoNum << endl;
    cout << "File type and mode:              " << typeMode << endl;
    cout << "Number of hard links:            " << numLinks << endl;
    cout << "User ID of owner:                " << ownerID << endl;
    cout << "Group ID of owner:               " << groupID << endl;
    cout << "Device ID (if special file):     " << specialDeviceId << endl;
    cout << "Total size, in bytes:            " << size << endl;
    cout << "Blocksize for filesystem I/O:    " << blocksize << endl;
    cout << "Number of 512B blocks allocated: " << numBlocks << endl;
    struct tm at = *localtime(&accTime);
    printf( "Time of last access:             %d-%d-%d %d:%d:%d\n", at.tm_year + 1900, at.tm_mon + 1, at.tm_mday, at.tm_hour, at.tm_min, at.tm_sec);
    struct tm mt = *localtime(&modTime);
    printf( "Time of last modification:       %d-%d-%d %d:%d:%d\n", mt.tm_year + 1900, mt.tm_mon + 1, mt.tm_mday, mt.tm_hour, mt.tm_min, mt.tm_sec);
    struct tm ct = *localtime(&chaTime);
    printf( "Time of last change:             %d-%d-%d %d:%d:%d\n", ct.tm_year + 1900, ct.tm_mon + 1, ct.tm_mday, ct.tm_hour, ct.tm_min, ct.tm_sec);
}

void diff(char** argv) {
    ifstream in1(argv[1]);
    ifstream in2(argv[2]);
    string temp1, temp2;
    int lineNum = 0;
    if(in1.good() && in2.good()) {
        while(!in1.eof()) {
            getline(in1, temp1);
            getline(in2, temp2);
            if(std::strcmp(temp1.c_str(), temp2.c_str()) != 0) {
                cout << lineNum << endl;
                cout << "< " << temp1 << endl;
                cout << "---" << endl;
                cout << "> " << temp2 << endl;
            }
            lineNum++;
        }
    } else
        cout << "ERR: NO SUCH FILE OR DIRECTORY" << endl;
}

void timeout(char **argv, int argc) {
    double delay = atof(argv[1]);
    string cmd = argv[2];
    clock_t startTime = clock();
    
    argv[0] = NULL;
    argv[1] = NULL;
    argc -= 2;
    
    double secondsPassed;
    bool flag = true;
    while(flag)
    {
        secondsPassed = (clock() - startTime) / CLOCKS_PER_SEC;
        if(secondsPassed >= delay)
        {
            std::cout << secondsPassed << " seconds have passed" << std::endl;
            flag = false;
        }
    }
}
