// Conor McGrath
// The secure hash algorithm, 256 bit version
// https://csrc.nist.ggov/csrc/media/publications/fips/180/4/final/documents/fips180-4-draft-aug2014.pdf

// Description
//	SHA-256 is one of the most common one way security hashes used.
//	SSL, SSH, PGP, and bitcoin all rely on this hash function. 

// The input/output header file
# include <stdio.h>
// For using fixed bit length integers
# include <stdint.h>
#include <stdlib.h>
#include <conio.h>

// every member variable is stored in the same memory location
// one varibale accesses 512 bits of memory
union msgblock {
    uint8_t e[64];  
    uint32_t t[16]; 
    uint64_t s[8];
};

// lets us know where we are in padding the message
enum status {
	READ,
	PAD0,
	PAD1,
	FINISH
};

// see sections 4.1.2 for definitions 
uint32_t sig0(uint32_t x);
uint32_t sig1(uint32_t x);

// see section 3.2 for definitions
uint32_t rotr(uint32_t x, uint32_t n);
uint32_t shr(uint32_t x, uint32_t n);

// see section 4.1.2 for definitions
uint32_t SIG0(uint32_t x);
uint32_t SIG1(uint32_t x);

// see section 4.1.2 for definitions
uint32_t Ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t Maj(uint32_t x, uint32_t y, uint32_t z);

// retrieve the next message block
// return 1 if there is another message block else return 0
// this function will complete based on the status
// the file and a message block chunk will be read
// nobits keep rtack of the number of bits read from the file 
int nextmsgblock(FILE *f, union msgblock *M, enum status *S, uint64_t *nobits);

// declare method
void sha256(FILE *f);

int main(int argc, char *argv[]){

	FILE *msg;
	//Storing file path
	char fnamer[100] = "";
	printf("\n\nEnter the full path of the file you want to hash: \n");
	scanf("%s",&fnamer);
	msg = fopen(fnamer,"r");

	if(msg == NULL)
	{
		printf("\n%s\" File NOT FOUND!",fnamer);
		getch();
		exit(1);
	}

	// Close the file
  	fclose(msg);

	sha256(msg);

} // end main

void sha256(FILE *msg){

	// Curr message block
	union msgblock M;

	// No of bits read from the file
	uint64_t nobits = 0;

	// Status of the message blocks
	enum status S = READ;

	// the K constants
	// defined in section 4.2.2
	uint32_t K[] = {
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
		0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 
		0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
		0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
		0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
		0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 
		0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
		0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
		0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, 
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
		0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
		0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
		0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
	};

	// message schedule (section 6.2)
	uint32_t W[64];

	// working variables (section 6.2)
	uint32_t a,b,c,d,e,f,g,h;

	// temporary vaiables (section 6.2)
	uint32_t T1, T2;

	// hash values (section 6.2)
	// the values come from (section 5.3.3)
	uint32_t H[8] = {
		0x6a09e667,
		0xbb67ae85,
		0x3c6ef372,
		0xa54ff53a,
		0x510e527f,
		0x9b05688c,
		0x1f83d9ab,
		0x5be0cd19,	
	};

	// for looping
	int i, t;


	while(nextmsgblock(msg, &M, &S, &nobits)){

		// from page 22, W[t] = M[t] for 0 <= t <=15
		for (t = 0; t < 16; t++){
			W[t] = M.t[t];
		}

		// from page 22, W[t] = ...
		for (t = 16; t < 64; t++){
			W[t] = sig1(W[t-2]) + W[t-7] + sig0(W[t-15]) + W[t-16];
		}

		// initialise a,b,c,d...h as per step 2 page 22
		a = H[0]; b = H[1]; c = H[2]; d = H[3]; e = H[4];
		f = H[5]; g = H[6]; h = H[7];

		// Step 3.
		// creating new values for working variables
		for(t = 0; t < 64; t ++){

			// Do the working variables operations as per NIST.
			T1 = h + SIG1(e) + Ch(e,f,g) + K[t] + W[t];
			T2 = SIG0(a) + Maj(a,b,c);
			h = g;
			g = f;
			f = e;
			e = d + T1; // Makes sure that we are still using 32 bits.
			d = c;
			c = b;
			b = a;
			a = T1 + T2; // Makes sure that we are still using 32 bits.

		}// end for

		
		// Step 4.
		// Add up all the working variables to each hash and make sure we are still
		// working with solely 32 bit variables.
		H[0] = a + H[0];
		H[1] = b + H[1];
		H[2] = c + H[2];
		H[3] = d + H[3];
		H[4] = e + H[4];
		H[5] = f + H[5];
		H[6] = g + H[6];
		H[7] = h + H[7];


	}

	printf("%08x %08x %08x %08x %08x %08x %08x %08x\n", H[0], H[1], H[2], H[3], H[4], H[5], H[6], H[7]);
	
}// end void sha265()

// see sections 3.2 for definitions
uint32_t rotr(uint32_t x, uint32_t n){
	return (x >> n) | (x << (32-n));
}

uint32_t shr(uint32_t x, uint32_t n){
	return (x >> n);
}

// see sections 3.2 & 4.1.2 for definitions
uint32_t sig0(uint32_t x){
	return (rotr(7,x) ^ rotr(18,x) ^ shr(3,x));
}

uint32_t sig1(uint32_t x){
	return (rotr(17,x) ^ rotr(19,x) ^ shr(10,x));
}

uint32_t SIG0(uint32_t x){
	return (rotr(2,x) ^ rotr(13,x) ^ rotr(22,x));
}

uint32_t SIG1(uint32_t x){
	return (rotr(6,x) ^ rotr(11,x) ^ rotr(25,x));
}

uint32_t Ch(uint32_t x, uint32_t y, uint32_t z){
	return ((x & y) ^ ((!x) & z));
}

uint32_t Maj(uint32_t x, uint32_t y, uint32_t z){
	return ((x & y) ^ (x & z) ^ (y & z));
}

int nextmsgblock(FILE *msg, union msgblock *M, enum status *S, uint64_t *nobits){


	// number of bytes we get from fread
    uint64_t nobytes;

    // looping varriables
    int i;

    // If we have finished all the message blocks, then s should be finished
    if(*S == FINISH){
      return 0;
    }

    // Otherwise, check if we need another block full of padding
    if (*S == PAD0 || *S == PAD1){
        // Set the first 56 bytes to all zero bits
        for (i = 0;i<56;i++){
            M->e[i] = 0x00;
        }
        // Set the last 64 bits to the number of bits in the file (should be big endian)
        M->s[7] = *nobits;
        // Tell S we are finished
        *S = FINISH;

        if (*S == PAD1){
          M->e[0] = 0x80;
        }
        return 1;
    }
    
    // IF WE HEY DOWN HERE, WE HAVNT FINISHED READING THE FILE (S == READ)
    nobytes = fread(M->e, 1, 64, msg);
    
    // Keep track of the number of bites wev read
    *nobits = *nobits + (nobytes * 8);
	
	// If i read a message block with less than 55 bytes, pad the current block
	if(nobytes < 56){

		// the first byte in M, that has not been written over
		// Add one bit 
		M->e[nobytes] = 0x80;

		// leave 8 bytes at the end where I can write a 64bit big endian integer
		// we do this by padding all the other bytes with 0's
		while(nobytes < 56){
			nobytes = nobytes + 1;
			M->e[nobytes] = 0x00;
		} // end while

		// Write in the number of bits of the original message or
		// Append the file size in bits as an unsigned 64 bit integer
		// NEED TO DETERMINE WHETHER THIS IS GOING IN AS A BIG ENDIAN INTEGER
		M->s[7] = *nobits;
		*S = FINISH;
	}// end if

	// if I have read between 56 & 64 bytes
	// I have to have an extra message block full of padding
	// there is no room to append a 1 and add a 64 bit integer to the original message block
	else if (nobytes < 64)
	{
		// We need another message block
		// with padding but no one bit.
		*S = PAD0;
		M->e[nobytes] = 0x80;

		// add some padding to the current message block
		// append the 1 and fill the rest with 0's
		// we can then have another message block to pad out and send the 0's
		while(nobytes < 64){
			nobytes = nobytes + 1;
			M->e[nobytes] = 0x00;
		}// end while 
	}

	// If I have finished reading everything from the file and it was 512 bits in length
	// i.e I kept reading 64 bytes from the file & the last time I read from the file
	// I read 64 bytes and it brought me to the exact end of the file
	else if (feof(msg)){
		*S = PAD1;
	} 

     // If we get this far
	 // then return 1 so that the function is called again
    return 1;
} // end main





