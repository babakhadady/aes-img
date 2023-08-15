# AES and Chaos System Image Encryption
Image encryption utilizing AES and chaos system key generation

## AES
This project contains an implementation of image encryption and decryption utilizing the Advanced Encryption Standard (AES), also known as Rijndael. Currently in use is an implentation of AES 128, which encrypts 128 bit blocks utilizing a 128 bit key.
Since AES is a block cipher, encrypted images are transformed into blocks of 128 bit plaintexts, where each pixels RGBA values are converted into a single byte represented through hexadecimal. Each block is thus encrypted individually, containing exactly 4 pixels (16 bytes).

#### Bit Padding
The current implementation utilizes Bit Padding for images that once encoded as plaintexts, do not result in a multiple of 128 bits. This results in the padding method appending 0x80 followed by 0x00 until 16 bytes (128 bits) are reached. Since each pixel is represented as exactly one byte, padding is always possible as we will always have a multiple of bytes, which is always a multiple of 8 bits.

#### ECB vs. CBC

Electronic Codebook (ECB) is a simple and obsolete mode of encryption. Since AES is a block cipher, each block is encrypted individually. ECB lacks diffusion, since identical plaintext blocks will be identical as ciphertext blocks, thus data patterns are not hidden well. Initially, with the very naive implementation of ECB, we see this shortfall on images with large areas of uniform colour. Although each individual pixel becomes encrypted, a general pattern is still present and the original image is very easily discerned.








## References

[1] J. Huang, “On the internal structure of the advanced encryption standard and two AES-based cryptographic constructions,” dissertation, 2012 

[2] A. Arab, M. J. Rostami, and B. Ghavami, “An image encryption method based on Chaos System and AES algorithm,” The Journal of Supercomputing, vol. 75, no. 10, pp. 6663–6682, 2019. doi:10.1007/s11227-019-02878-7 

[3] “Advanced encryption standard,” Wikipedia, https://en.wikipedia.org/wiki/Advanced_Encryption_Standard# (accessed Aug. 15, 2023). 

[4] A. Kak, “Lecture 8: AES: The Advanced Encryption Standard,” in Lecture Notes on “Computer and Network Security” 
