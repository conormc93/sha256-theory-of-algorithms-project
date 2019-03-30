## Theory of Algorithms Project - sha256 
###### Written by Conor McGrath

Outlined below are instructions on how to use the project files contained within this repository.

### Thechnologies Used
The technologies I'm using in this project are:

    1. Visual Studio Code
    2. Windows Powershell
    3. Normal command prompt
---

# What is the SHA256 Hashing Algorithm? 
SHA-2 (Secure Hash Algorithm 2) is a set of cryptographic hash functions designed by the United States National Security Agency (NSA).

The standard for the algorithm can be found [here](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf).

# Setup/Install
To compile/run the program you can install a _C_ compiler from the below sites:

- Windows - `www.mingw.org`
- Linux - `sudo apt-get install build-essential`
- Solus - `sudo eopkg install -c system.devel`

# How to Run
1. Compile - `gcc -o SHA256.c SHA256`
2. Execute - `sha256.exe`

# Checking the result of the hashing algorithm
Before I ran the solution I went to check for the correct hash of a file before using my own algorithm, thus allowing me to compare and confirm the result. The steps included below are:

1. Open Windows Powershell and type - `Get-FileHash FULL-PATH-NAME-OF-FILE-HERE| Format-List`
    - This produces the correct hash for that using sha256.
##### Powershell sha256
![powershell](https://i.imgur.com/6vjeq5B.png)

2. Open a normal command prompt in the directory your `sha256.c` is located.
    - Follow the steps above to run my solution.
##### My solution for sha256
![sha256](https://i.imgur.com/djatNpV.png)

# Implementation
The project was done under the guidance of video lectures uploaded by __Dr. Ian McLoughlin__.

During the implementation of the project, research about the algorthim and it's standards was undertaken to try
and better understand the intricacies of the algorthim.


# Videos
* [Video - Part 1](https://web.microsoftstream.com/video/db7c03be-5902-4575-9629-34d176ff1366)
* [Video - Part 2](https://web.microsoftstream.com/video/2a86a2ac-aafb-46e0-a278-a3faa1d13cbf)
* [Video - Part 3](https://web.microsoftstream.com/video/78dc0c8d-a017-48c8-99da-0714866f35cb)
* [Video - Part 4](https://web.microsoftstream.com/video/9daaf80b-9c4c-4fdc-9ef6-159e0e4ccc13)
* [Video - Part 5](https://web.microsoftstream.com/video/200e71ec-1dc1-47a4-9de8-6f58781e3f38) 
* [Video - Part 6](https://web.microsoftstream.com/video/f823809a-d8df-4e12-b243-e1f8ed76b93f)

# Research
* [What is SHA256?](https://www.hashgains.com/wiki/s/what-is-sha-256)
* [How Does SHA256 Work?](https://www.youtube.com/watch?v=mbekM2ErHfM)
* [How secure is 256 bit security?](https://www.youtube.com/watch?v=mbekM2ErHfM)
* [What is a Bitcoin hash and SHA-256?](https://www.youtube.com/watch?v=9mNgeTA13Gc)
* [SHA256 and Bitcoin](https://www.mycryptopedia.com/sha-256-related-bitcoin)
* [Little Endian vs Big Endian](https://www.geeksforgeeks.org/little-and-big-endian-mystery/)
* [The Difference Between SHA-1,2 and 256](https://www.thesslstore.com/blog/difference-sha-1-sha-2-sha-256-hash-algorithms)
