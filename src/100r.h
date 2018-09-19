//
//  100r.h
//  100r
//
//  Created by vs on 9/19/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef _100r_h
#define _100r_h


#include <stdio.h>
#include <stdlib.h>

//	https://stackoverflow.com/questions/1638207/how-to-store-a-version-number-in-a-static-library

#define HR_VERSION "0.0.2"
#define HR_VERSION_MAJOR 0
#define HR_VERSION_MINOR 0
#define HR_VERSION_PATCH 2

#define HR_VERSION_CHECK(maj, min) ((maj == HR_VERSION_MAJOR) && (min <= HR_VERSION_MINOR))

#define HR_PRESENT

int   HR_check_version_match(const char* str);
int   HR_check_version_match222(const char* str);
int   HR_check_compat_match(const char* str);
char* HR_get_version_string(void);
char* HR_get_compat_string(void);

static inline void HR_version_check(int major, int minor)
{
	if (!HR_VERSION_CHECK(major, minor))
	{
		fprintf(stderr, "ERROR: incompatible library version\n");
		exit(-1);
	}
	printf("libHR is compatible (%s)\n", HR_VERSION);
}

static inline char* HR_get_compat_string_header(void)
{
	char* buf = (char*)calloc(256, sizeof(char));
	sprintf(buf, "%d_%d", HR_VERSION_MAJOR, HR_VERSION_MINOR);
	return buf;
}

static inline char* HR_get_version_string_header(void)
{
	char* buf = (char*)calloc(256, sizeof(char));
	sprintf(buf, "%d.%d.%d", HR_VERSION_MAJOR, HR_VERSION_MINOR,
		HR_VERSION_PATCH);
	return buf;
}

#endif /* _00r_h */
