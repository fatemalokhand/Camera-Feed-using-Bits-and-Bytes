# Camera-Feed-using-Bits-and-Bytes

Author: Fatema Lokhandwala

Program's Purpose:
The program simulates taking photos repeadtedly until no photos remain and then for each photo: it prints out the raw unpacked image, then packs the bits and prints out the packed bit representation of the photo. Finally it encodes the bits using Run Length Encoding and prints out the encoded representation of the photo. It also prints out the number of bytes required to store the image for each representation.

List of files:
- code.c: Contains all the code for the program to run.
- camera.o: An object file that contains the take_photo() implementation.
- README.md: Contains this description.

Compiling and Executing:
- Navigate to the folder that contains the source code and the camera.o object file.
- Use the command `gcc -o code code.c camera.o` to create the file `code` which can be executed. Make sure to link the camera.o object file alongside the source file.
- Use the command `./code` while in the folder containing the executable to run the program.

How to use the program:
Once the above steps are done correctly, the program will run printing out two different images three times and displaying the correct number of bytes needed to store each image. No user input is required to run the program.
