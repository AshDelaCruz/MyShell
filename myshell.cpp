//
//  main.cpp
//  Project_Phase2
//
//  Created by Earl Ashleigh M. Dela Cruz on 3/6/17.
//  Copyright © 2017 Earl Ashleigh M. Dela Cruz. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include "mycommands.hpp"

using namespace std;

int main(int argc, char * argv[]) {

    
    while(true) {
        cout << "\nMyShell$ ";
        
        argc = read(argv);
        parse(argc, argv);
        
        for(int i = 0; i < argc; i++)
            argv[i] = NULL;
    }
    return 0;
}
