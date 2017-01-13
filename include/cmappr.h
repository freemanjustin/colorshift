#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>
#include <getopt.h>


#define TRUE 1
#define FALSE 0


typedef struct {
    double r;       // percent
    double g;       // percent
    double b;       // percent
} rgb;

    typedef struct {
    double h;       // angle in degrees
    double s;       // percent
    double v;       // percent
} hsv;

typedef struct{

  unsigned char  *data;  // image data
  int   h;  // height
  int   w;  // width
  int   n;  // number of color components

}image;

typedef struct{

  char*   input_file;
  char*   output_file;

  image  in_image;  // image data struct
  image  out_image;  // output colormap sample image
  image  font_gray;
  image  scaled;//
  image  cs;    // rgb color shifted

  int   block_size;
  int   gray_value;
  int   alpha_blend;
  float alpha;

  int iterations;

  // use result image as new source for iterations
  int recursiveIterations;

  // shift the image vertically true/false
  int shiftVertically;

  // shift the image horizontally true/false
  int shiftHorizontally;

  int horizontalShiftAmount;
  int verticalShiftAmount;

  int haveInput;
  int haveOutput;
  int haveNiter;
  int haveHorizontal;
  int haveVertical;
  int haveRecursive;
  int haveHs;
  int haveVs;

}e;



// prototypes

void get_cli_args(e *E, int argc, char *argv[]);
void print_usage();

void get_command_line_arg_as_string(char **variable, char *cli_input);
void get_command_line_arg_as_int(int *variable, char *cli_input);
