//
//  100r_theme.h
//  100r
//
//  Created by vs on 9/19/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef _100r_theme_h
#define _100r_theme_h

typedef struct
{
	double r;
	double g;
	double b;
	double a;
} HRColor16;

typedef struct
{
	HRColor16 bg;
	HRColor16 b_high, b_med, b_low, b_inv;
	HRColor16 f_high, f_med, f_low, f_inv;

	//	convenience, to put back in later
	//	HRColor16 colors[9];
	//	this all got dumped during the json->svg switch
	//int	 version;
	//int	 revision;
	//const char* author;
	//const char* path;
	//const char* name;
	//HRColor16 debug;
} HRPalette;

HRPalette* hr_palette_create(void);
HRPalette* hr_palette_load_by_path(const char* path);

/*
void      hr_palette_update_arr_to_names(HRPalette* pal);
void      hr_palette_update_names_to_arr(HRPalette* pal);
void      hr_palette_swap(HRPalette* pal);
int       hr_palette_save(HRPalette* pal);
*/

//HRPalette* r_palette_load_by_name(const char* name);

#endif /* _00r_theme_h */
