
// just putting this here
// has nothing to do with the content
// but this is the command to use when making movies on lust
//
// avconv -r 20 -i window%04d.png -b:v 10000k test.mp4
#ifndef STB_HEADERS
#define STB_HEADERS

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

#endif
#include "cmappr.h"

void abort_(const char * s, ...)
{
    va_list args;
    va_start(args, s);
    vfprintf(stderr, s, args);
    fprintf(stderr, "\n");
    va_end(args);
    abort();
}


void get_command_line_arg_as_string(char **variable, char *cli_input){

	*variable = malloc((strlen(cli_input)+1)*sizeof(char));
	strncpy(*variable, cli_input, strlen(cli_input));
	// fix the string
	*(&(*variable)[strlen(cli_input)]) = '\x0';
}

void get_command_line_arg_as_int(int *variable, char *cli_input){

	sscanf(cli_input,"%d",variable);
}

float randInRange(float min, float max)
{
  if (min==max) return 0.0;
  else return (float)( min + (rand() / (float) (RAND_MAX + 1.0) * (max - min)));
}

// ported from the processing script
void copyChannel(image *in, image *out, int sourceY, int sourceX, int sourceChannel, int targetChannel){

    int x, y;

    int sourceYOffset;
    int sourceXOffset;

    int sourceRed;
    int sourceGreen;
    int sourceBlue;

    int targetRed;
    int targetGreen;
    int targetBlue;

    int sourceChannelValue;

    // starting at the sourceY and pointerY loop through the rows
    for(y = 0; y < out->h; y++)
    {
        // add y counter to sourceY
        sourceYOffset = sourceY + y;

        // wrap around the top of the image if we've hit the bottom
        if(sourceYOffset >= out->h)
          sourceYOffset -= out->h;

        // starting at the sourceX and pointerX loop through the pixels in this row
        for(x = 0; x < out->w; x++)
        {
            // add x counter to sourceX
            sourceXOffset = sourceX + x;

            // wrap around the left side of the image if we've hit the right side
            if(sourceXOffset >= out->w)
              sourceXOffset -= out->w;

            // get the RGB values of the source pixel
            sourceRed = in->data[(sourceYOffset * in->w  + sourceXOffset) * in->n + 0]; //red(sourcePixel);
            sourceGreen = in->data[(sourceYOffset * in->w  + sourceXOffset) * in->n + 1]; //green(sourcePixel);
            sourceBlue = in->data[(sourceYOffset * in->w  + sourceXOffset) * in->n + 2]; //blue(sourcePixel);

            // create a variable to hold the new source RGB channel value
            sourceChannelValue = 0;
            // assigned the source channel value based on sourceChannel random number passed in
            switch(sourceChannel){
              case 0:
                // use red channel from source
                sourceChannelValue = sourceRed;
                break;
              case 1:
                // use green channel from source
                sourceChannelValue = sourceGreen;
                break;
              case 2:
                // use blue channel from source
                sourceChannelValue = sourceBlue;
                break;
            }

            // assigned the source channel value to a target channel based on targetChannel random number passed in
            switch(targetChannel)
            {
              case 0:
                // assign source channel value to target red channel
                out->data[(y * out->w  + x) * out->n + 0] = sourceChannelValue;
                break;
              case 1:
                // assign source channel value to target green channel
                out->data[(y * out->w  + x) * out->n + 1] = sourceChannelValue;
                break;
              case 2:
                // assign source channel value to target blue channel
                out->data[(y * out->w  + x) * out->n + 2] = sourceChannelValue;
                break;
            }
        }
    }
    //stbi_write_png("colorshifted.png", out->w, out->h, out->n, out->data, 0);
    //exit(0);
}

void copy_image(image *src, image *dest){

    int i, j;

    // no error checking! asusmes that the src and destination are allocated and the same size!!!!
    for(i=0;i<src->h;i++){
        for(j=0;j<src->w;j++){
            dest->data[(i * dest->w  + j) * dest->n + 0] = src->data[(i * src->w  + j) * src->n + 0];
            dest->data[(i * dest->w  + j) * dest->n + 1] = src->data[(i * src->w  + j) * src->n + 1];
            dest->data[(i * dest->w  + j) * dest->n + 2] = src->data[(i * src->w  + j) * src->n + 2];
            dest->data[(i * dest->w  + j) * dest->n + 3] = src->data[(i * src->w  + j) * src->n + 3];
        }
    }
}


int main(int argc, char **argv)
{
    e   *E;
    int i,j;

    int sourceChannel;
    int targetChannel;

    // malloc E;
    E = malloc(sizeof(e));
    if(E==NULL){
        fprintf(stderr,"malloc failed\n");
        exit(1);
    }

    // parse command line arguments
	if(argc < 3){
        print_usage();
		//fprintf(stderr,"args: [input file] [output file]\n");
        exit(1);
	}
	else{
       // get_command_line_arg_as_string(&E->input_file, argv[1]);
	//	get_command_line_arg_as_string(&E->output_file, argv[2]);
        get_cli_args(E, argc, argv);
	}

    // init random number generator
    srand(time(NULL));

    //printf("working on %s...\n", E->input_file);
    //read_png_file(argv[1]);
    // read input image
    E->in_image.data = stbi_load(E->input_file, &E->in_image.w, &E->in_image.h, &E->in_image.n, 0);

    //printf("input image data: width = %d, height = %d, components = %d\n",
    //E->in_image.w, E->in_image.h, E->in_image.n);

    
    // get our colorshifted pixel space ready
    E->cs.w = E->in_image.w;
    E->cs.h = E->in_image.h;
    E->cs.n = 4;
    E->cs.data = (unsigned char*)malloc(E->cs.w*E->cs.h*E->cs.n*sizeof(unsigned char));
    // copy input image into colorshifted data array for messing with later
    copy_image(&E->in_image, &E->cs);

    // setup parameters for color shifting
    // repeat the process this many times
    //int iterations = 5;

    // use result image as new source for iterations
    //int recursiveIterations = FALSE;

    // shift the image vertically true/false
    //int shiftVertically = TRUE;

    // shift the image horizontally true/false
    //int shiftHorizontally = TRUE;

    // now sample from the original image into our colorshifted space
    // repeat the process according
    // to the iterations variable
    for(i = 0; i < E->iterations; i++){
        // generate random numbers
        // for which channels to swap
        sourceChannel = (int)randInRange(0,3);
        //sourceChannel = 1;    // i sometimes set this manually
        do{
            targetChannel = (int)randInRange(0,3);
            //targetChannel = 0;    // i sometimes set this manually
        }while(targetChannel == sourceChannel);

        printf("sourceChannel = %d, targetChannel = %d\n", sourceChannel, targetChannel);

        // start with no horizontalShift
        int horizontalShift = 0;

        // if shiftHorizontally is true, generate a random number to shift horizontally by
        if(E->shiftHorizontally){
            horizontalShift = (int)randInRange(0,E->cs.w);
            // tiny horizontal displacements
            if(E->haveHs == TRUE){
                do{
                    horizontalShift = (int)randInRange(-E->horizontalShiftAmount,E->horizontalShiftAmount); // i sometimes set this manually
                }while(horizontalShift == 0);
            }
            printf("horizontalShift = %d\n", horizontalShift);
        }

        // start with no verticalShift
        int verticalShift = 0;

        // if shiftVertically is true, generate a random number to shift vertically by
        if(E->shiftVertically){
            verticalShift = (int)randInRange(0,E->cs.h);
            // tiny displacements
            if(E->haveVs == TRUE){
                do{
                    verticalShift = (int)randInRange(-E->verticalShiftAmount,E->verticalShiftAmount); // i sometimes set this manually
                }while(verticalShift == 0);
            }
            printf("shifting vertically by %d pixels\n", verticalShift);
        }

        // shift the channel
        copyChannel(&E->in_image, &E->cs, verticalShift, horizontalShift, sourceChannel, targetChannel);

        // use the target as the new source for the next iteration
        if(E->recursiveIterations){
            // copy the target to the source
            // copy_image(src, destination)
            printf("recursive is true ... doing copy_image()\n");
            copy_image(&E->cs, &E->in_image);
        }
    }

    // save an output image and quit
    if(E->cs.w > 192000){   // if you want to rescale the make this test something sane
        E->scaled.w = E->cs.w*0.25;
        E->scaled.h = E->cs.h*0.25;
        E->scaled.n = E->cs.n;

        E->scaled.data = (unsigned char *) malloc(E->scaled.w*E->scaled.h*E->scaled.n*sizeof(unsigned char));


        stbir_resize_uint8((const void *)E->cs.data, E->cs.w, E->cs.h , 0,
                                    (const void *)E->scaled.data, E->scaled.w, E->scaled.h, 0, E->scaled.n);
        stbi_write_png(E->output_file, E->scaled.w, E->scaled.h, E->scaled.n, (const void *)E->scaled.data, 0);
    }
    else{
        stbi_write_png(E->output_file, E->cs.w, E->cs.h, E->cs.n, (const void *)E->cs.data, 0);
    }

    return 0;
}
