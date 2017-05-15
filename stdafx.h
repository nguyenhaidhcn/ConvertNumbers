// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include "Data.h"
#include "Processer.h"
#include <sstream>
#include <vector>

#define COPY_STR(dst,src) { wcscpy(dst,src); }

enum
{
	TWO_NUMBERS = 2,
	THREE_NUMBERS = 3,
	DECIMAL =10
};

// TODO: reference additional headers your program requires here
