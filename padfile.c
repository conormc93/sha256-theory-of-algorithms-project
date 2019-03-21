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

// lets us know where we are in padding the message
enum status {READ, PAD0, PAD1, FINISH};



int main(int argc, char *argv[]){

    printf("Hello");
    union msgblock M;

    uint64_t nobits = 0;

    // number of bytes that fread returns
    uint64_t nobytes;

    enum status S = READ;

    // file pointer
	FILE* f;
    f = fopen(argv[1], "r");

    // loop until end of file
    while( S == READ ){

        //reading 64 bytes from the file
        nobytes = fread(M.e, 1, 64, f);
        printf("Read %2llu bytes\n", nobytes);
        nobits = nobits + (nobytes * 8);

        // If i read a message block with less than 55 bytes, pad the current block
        if(nobytes < 56){

            printf("I've found a block with less than 55 bytes!\n");

            // the first byte in M, that has not been written over
            M.e[nobytes] = 0x80;

            // leave 8 bytes at the end where I can write a 64bit big endian integer
            // we do this by padding all the other bytes with 0's
            while(nobytes < 56){
                nobytes = nobytes + 1;
                M.e[nobytes] = 0x00;
            } // end while

            // write in the number of bits of the original message
            // NEED TO DETERMINE WHETHER THIS IS GOING IN AS A BIG ENDIAN INTEGER
            M.s[7] = nobits;
            S = FINISH;
        }// end if

        // if I have read between 56 & 64 bytes
        // I have to have an extra message block full of padding
        // there is no room to append a 1 and add a 64 bit integer to the original message block
        else if (nobytes < 64)
        {
            S = PAD0;
            M.e[nobytes] = 0x80;

            // add some padding to the current message block
            // append the 1 and fill the rest with 0's
            // we can then have another message block to pad out and send the 0's
            while(nobytes < 64){
                nobytes = nobytes + 1;
                M.e[nobytes] = 0x00;
            }// end while 
        }

        // If I have finished reading everything from the file and it was 512 bits in length
        // i.e I kept reading 64 bytes from the file & the last time I read from the file
        // I read 64 bytes and it brought me to the exact end of the file
        else if (feof(f)){
            S = PAD1;
        }
    }// end while   

    // add a block of padding where first 448 bits are 0's
    // in the last block, put in the 64 bit big endian integer
    // which represents the number of bits in the original message
    if (S == PAD0 || S == PAD1) {
        for(int i = 0; i < 56; i++)
            M.e[i] = 0x00;
        M.s[7] = nobits; 
    } 

    if (S == PAD1) {
        M.e[0] = 0x80;
    }

    fclose(f);

    for(int i = 0; i < 64; i++)
        printf("%x ", M.e[i]);

    printf("\n");

    
    
    return 0;
} // end main