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

    uint64_t nobits = 0;
    uint64_t nobytes;

    // file pointer
	FILE* f;
    f = fopen(argv[1], "r");

    // loop until end of file
    while(!feof(f)){

        //reading 64 bytes from the file
        nobytes = fread(M.e, 1, 64, f);

        nobits = nobits + (nobytes * 8);

        if(nobytes < 56){

            printf("I've found a block with less than 55 bytes!\n");
            M.e[nobytes] = 0x80;

            while(nobytes < 56){
                nobytes++;
                M.e[nobytes] = 0x00;
            } // end while
            M.s[7] = nobits;
        }// end if

    }// end while   

    fclose(f);
    
    return 0;
} // end main