# colorshift

```colorshift``` copies color channels randomly. This is colorshifting, or rgb channnel shifting.

# Usage
```
  -i, --input [filename]               input file [jpg, png]
  -o, --output [filename]              output file [jpg, png]
  -n, --niter [integer]                number of iterations to performe
  -h, --horizontal [1=true/0=false]    shift horizontally
  -x, --hamount [number of pixes]      horizontal shift range +/- this many pixels
  -v, --vertical [1=true/0=false]      shift vertially
  -y, --vamount [number of pixes]      vertical shift range +/- this many pixels
  -r, --recursive [1=true/0=false]     recursive iterations (uses output as input)
```

# Example Usage
```./colorshift -i sample_input.png -o sample_output.png -n 5 -r 1 -h 1 -x 50 -v 1 -y 50```

# Sample Output
![colorshift input](https://raw.github.com/freemanjustin/colorshift/master/bin/sample_output.png)
