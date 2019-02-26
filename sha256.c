// Conor McGrath
// The secure hash algorithm, 256 bit version
// https://csrc.nist.ggov/csrc/media/publications/fips/180/4/final/documents/fips180-4-draft-aug2014.pdf

// The input/output header file
# include <stdio.h>
// For using fixed bit length integers
# include <stdint.h>

void sha256();

int main(int argc, char *argv[]){
	
	sha256();

}

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
}


