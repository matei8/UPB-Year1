# Steganography Using Images


The project involves hiding the information in .ppm type images and decode them in order to 
extract the hidden message from them. To work with images and change the RGB values of the 
pixels or use bitwise operations, encoding of the information will have to be done so that 
the resulting image is not different significantly, thus integrating the information as well 
as possible into the image data (bits of the pixels). Method approached for encoding the 
information will be LSB (Least Significant Bit), like this changing as little as possible 
of the quality of the original image.

### *Steps:*

    > 1. We choose the PPM image and the secret text we want to hide in the image.

    > 2. We convert the secret text to a string of bits. For example, the text
        "Hello!" can be converted to the bit string 01001000 01100101 01101100 
        01101100 01101111 00100001. Each sequence of 8 bits representing the 
        binary form of a character from the string.
    
    > 3. We choose the pixels in the image that we want to use
        to hide the secret text (by traversing the pixel array from
        left to right and top to bottom).
    
    > 4. For each selected pixel, I shift the least significant bit of the RGB 
        value by one bit from the ciphertext bitstring, in sequential order. E.g:

        > If the first bit in the secret text is 0, we will change the least
         significant bit of the RGB value of the first pixel selected with 0.

        > If the second bit in the secret text is 1, we will change the most
         least significant bit of the next RGB value of the first selected pixel
         with 1 and so on

        > The LSB of the last RGB value of the first pixel will be modified and then
         we will move to the next pixel until all the text is encoded.
    
    > 5. After changing the least significant bit of the value
        RGB for all selected pixels, we will get a modified image
        which contains the hidden secret text.
    
     > 6. To extract the secret text from the image, you just need to
        pick the selected pixels again and extract the least significant bit

### *Commands:*

Also, some commands for using the program were implemented:
- (-t) -> timestamp, the time when the file was modified will be displayed;
- (-l) -> log file, the time, date (of the last modification) and file name will be kept
- (-lc) -> log clear, the content of the log file is deleted
- (-s) -> file size given as parameter;
- (-h) -> the help menu will be displayed with a description of the options;
- (-c) -> encode the message
- (-d) -> decode the message

**For more info on the commands or how to use the program, type in a Linux terminal**
> _**./steg**_

**OR** 
> _**./steg -h**_ .
