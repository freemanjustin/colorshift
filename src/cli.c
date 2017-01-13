#include "cmappr.h"

void get_cli_args(e *E, int argc, char *argv[]){

  char  str[128];
  int             c;
  const char      *short_opt = "r:i:o:n:h:x:v:y:z";
  struct option   long_opt[] =
  {
     {"help",          no_argument,       NULL, 'z'},
     {"ipnut",          required_argument, NULL, 'i'},
     {"output",          required_argument, NULL, 'o'},
     {"niter",          required_argument, NULL, 'n'},
     {"horizontal",          required_argument, NULL, 'h'},
     {"vertical",          required_argument, NULL, 'v'},
     {"recursive",          required_argument, NULL, 'r'},
     {"hamount",          required_argument, NULL, 'x'},
     {"vamount",          required_argument, NULL, 'y'},
     {NULL,            0,                 NULL, 0  }
  };

  E->haveInput = FALSE;
  E->haveOutput = FALSE;
  E->haveNiter = FALSE;
  E->haveHorizontal = FALSE;
  E->haveVertical = FALSE;
  E->haveRecursive = FALSE;
  E->haveHs = FALSE;
  E->haveVs = FALSE;

  while((c = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1)
  {
    //printf("c = %c\n", c);
     switch(c)
     {
        case -1:       /* no more arguments */
        case 0:        /* long options toggles */
         break;

        case 'i':
          E->input_file = malloc((strlen(optarg)+1)*sizeof(char));
          strncpy(E->input_file, optarg, strlen(optarg));
          // fix the string
          E->input_file[strlen(optarg)] = '\x0';
          //printf("input file: %s\n", E->input_file);
          E->haveInput = 1;
          break;
        
        case 'o':
          E->output_file = malloc((strlen(optarg)+1)*sizeof(char));
          strncpy(E->output_file, optarg, strlen(optarg));
          // fix the string
          E->output_file[strlen(optarg)] = '\x0';
          //printf("output_file = %s\n", E->output_file);
          E->haveOutput = 1;
          break;

        case 'n':
          //E->tide_input = malloc((strlen(optarg)+1)*sizeof(char));
          //strncpy(E->tide_input, optarg, strlen(optarg));
          // fix the string
          //E->tide_input[strlen(optarg)] = '\x0';
          sscanf(optarg,"%d", &E->iterations);
          //printf("iterations = %d\n", E->iterations);
          E->haveNiter = 1;
          break;

        case 'r':
          sscanf(optarg,"%d", &E->recursiveIterations);
          //printf("recursive = %d\n", E->recursiveIterations);
          E->haveRecursive = 1;
          break;
        
        case 'h':
          sscanf(optarg,"%d", &E->shiftHorizontally);
          //printf("horizontal = %d\n", E->shiftHorizontally);
          E->haveHorizontal = 1;
          break;

        case 'v':
          sscanf(optarg,"%d", &E->shiftVertically);
          //printf("vertical = %d\n", E->shiftVertically);
          E->haveVertical = 1;
          break;

        case 'x':
          sscanf(optarg,"%d", &E->horizontalShiftAmount);
          //printf("hs = %d\n", E->horizontalShiftAmount);
          E->haveHs = 1;
          break;
        
        case 'y':
          sscanf(optarg,"%d", &E->verticalShiftAmount);
          //printf("vs = %d\n", E->verticalShiftAmount);
          E->haveVs = 1;
          break;

        case 'z':
          print_usage();
          exit(0);

        default:
          print_usage();
          exit(0);
     };
  };

  // check presence
  if(  E->haveInput == FALSE  ){
    fprintf(stderr,"no input file specified:\nI need one of these to run.\n");
    exit(1);
  }
  if(  E->haveOutput == FALSE ){
    fprintf(stderr,"no output file specified:\nI need one of these to run.\n");
    exit(1);
  }
  if(  E->haveNiter == FALSE ){
    E->iterations = 0;
  }
  if(  E->haveHorizontal == FALSE ){
    E->shiftHorizontally = FALSE;
  }
  if(  E->haveVertical == FALSE ){
      E->shiftVertically = FALSE;
  }
  if(  E->haveRecursive == FALSE ){
      E->recursiveIterations = FALSE;
  }
  
}





void print_usage(){
  printf("Usage: \n");
  printf("  -i, --input [filename]               input file [jpg, png]\n");
  printf("  -o, --output [filename]              output file [jpg, png]\n");
  printf("  -n, --niter [integer]                number of iterations to performe\n");
  printf("  -h, --horizontal [1=true/0=false]    shift horizontally\n");
  printf("  -x, --hamount [number of pixes]      horizontal shift range +/- this many pixels\n");
  printf("  -v, --vertical [1=true/0=false]      shift vertially\n");
  printf("  -y, --vamount [number of pixes]      vertical shift range +/- this many pixels\n");
  printf("  -r, --recursive [1=true/0=false]     recursive iterations (uses output as input)\n");
  printf("\n");
}

