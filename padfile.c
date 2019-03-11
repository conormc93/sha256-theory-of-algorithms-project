// The input/output header file
# include <stdio.h>
// For using fixed bit length integers
# include <stdint.h>

// every member variable is stored in the same memory location
// one varibale accesses 512 bits of memory
union msgblock {
    uint8_t e[64];  
    uint32_t t[16]; 
    uint64_t s[8];
};

int main(int argc, char *argv[]){

    printf("Hello");
    union msgblock M;

    uint64_t nobytes;

    // file pointer
	FILE* f;
    f = fopen(argv[1], "r");

    // loop until end of file
    while(!feof(f)){

        //reading 64 bytes from the file
        nobytes = fread(M.e, 1, 64, f);
        printf("%llu\n", nobytes);

    }

    fclose(f);
    
    return 0;
} // end main