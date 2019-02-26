// Conor McGrath
// The secure hash algorithm, 256 bit version
// https://csrc.nist.ggov/csrc/media/publications/fips/180/4/final/documents/fips180-4-draft-aug2014.pdf

// The input/output header file
# include <stdio.h>
// For using fixed bit length integers
# include <stdint.h>

// declare method
void sha256();

// see sections 4.1.2 for definitions 
uint32_t sigma_0(uint32_t x);
uint32_t sigma_1(uint32_t x);

uint32_t Ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t Maj(uint32_t x, uint32_t y, uint32_t z);

uint32_t rotr(uint32_t x, uint32_t n);
uint32_t shr(uint32_t x, uint32_t n);


int main(int argc, char *argv[]){
	
	printf("Hello World");
	sha256();

} // end main

void sha256(){
	// message schedule (section 6.2)
	uint32_t W[64];

	// working variables (section 6.2)
	uint32_t a,b,c,d,e,f,g,h;

	// temporary vaiables
	uint32_t T1, T2;

	// hash values
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
	
	// the current message block
	uint32_t M[16];

	// for looping
	int t;

	// from page 22, W[t] = M[t] for 0 <= t <=15
	for (t = 0; t < 16; t++){
		W[t] = M[t];
	}

	// from page 22, W[t] = ...
	for (t = 16; t < 64; t++){
		sigma_1(W[t-2]) + W[t-7] + sigma_0(W[t-15]) + W[t-16];
	}

	// initialise a,b,c,d...h as per step 2 page 22
	a = H[0]; b = H[1]; c = H[2]; d = H[3]; e = H[4];
	f = H[5]; g = H[6]; h = H[7];

	// Step 3.
	// creating new values for working variables
	for(t = 0; t < 64; t ++){

		T1 = h + sigma_1(e) + Ch(e,f,g) + K[t] + W[t];
		T2 = sigma_0(a) + Maj(a,b,c);
		h = g;
		g = f;
		f = e;
		e = d + T1;
		d = c;
		c = b;
		b = a;
		a = T1 + T2;

	}// end for
	
	// Step 4.
	H[0] = a + H[0];
	H[1] = b + H[1];
	H[2] = c + H[2];
	H[3] = d + H[3];
	H[4] = e + H[4];
	H[5] = f + H[5];
	H[6] = g + H[6];
	H[7] = h + H[7];
	
}// end void sha265()

// see sections 3.2 for definitions
uint32_t rotr(uint32_t x, uint32_t n){
	return (x >> n) | (x << (32-n));
}

uint32_t shr(uint32_t x, uint32_t n){
	return (x >> n);
}

// see sections 4.1.2 for definitions
uint32_t sigma_0(uint32_t x){
	return (rotr(7,x) ^ rotr(18,x) ^ shr(3,x));
}

uint32_t sigma_1(uint32_t x){
	return (rotr(17,x) ^ rotr(19,x) ^ shr(10,x));
}

uint32_t Ch(uint32_t x, uint32_t y, uint32_t z){
	return ((x & y) ^ ((!x) & z));
}

uint32_t Maj(uint32_t x, uint32_t y, uint32_t z){
	return ((x & y) ^ (x & z) ^ (y & z));
}








