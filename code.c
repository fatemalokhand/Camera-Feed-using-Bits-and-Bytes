#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARR 5000

/*  Function: take_photo()
    Description: Simulates taking a photo as a black-and-white image represented by
                 an array of characters '1' and '0'. The photo is stored in the out[] array.

    Output: out[]   - an array of characters to store the photo data, as a string of 1 and 0 characters
    Output: rows    - an address to an integer to store the number of rows in the photo
    Output: cols    - an address to an integer to store the number of columns in the photo

    Returns: the total number of characters in the photo data OR 0 if no photo was taken
    
*/
int take_photo(unsigned char out[], int* rows, int* cols);

unsigned char get_bit(unsigned char byte, int bit);
unsigned char set_bit(unsigned char byte, int bit);
unsigned char clear_bit(unsigned char byte, int bit);
void print_raw(unsigned char raw_string[], int rows, int cols);
int pack_bits(unsigned char unpacked_string[], int num_chars, unsigned char packed_result[]);
void print_packed(unsigned char packed[], int rows, int cols);
int encode_bits(unsigned char packed[], int packed_size, unsigned char encoded_result[]);
void print_encoded(unsigned char encoded[], int encoded_size, int rows, int cols);


/*  Function: main()
    Description: Repeatedly taking photos, printing out the raw photo, packing the photo and printing out the packed photo, and finally encoding the photo 
    		 and printing out the encoded photo until no more images are available. 


    Returns: Returns 0 to indicate that the program has terminated successfully.
    
*/
int main() {

	unsigned char rawPhotoStringArr[MAX_ARR];
	int numRows;
	int numCols;
	int sizeImage;
	int no_of_bytes = 0;
	unsigned char packed_bits[MAX_ARR];
	unsigned char encoded_arr[MAX_ARR];
	
	while(1){
	
		sizeImage = take_photo(rawPhotoStringArr, &numRows, &numCols);
		
		if(sizeImage == 0){
		
			break;
		}
		
		printf("\n");
		
		printf("Raw photo: %d bytes\n", sizeImage);
		
		print_raw(rawPhotoStringArr, numRows, numCols);
		
		no_of_bytes = pack_bits(rawPhotoStringArr, sizeImage, packed_bits);
		
		printf("\n");
		
		printf("Packed photo: %d bytes\n", no_of_bytes);
		
		print_packed(packed_bits, numRows, numCols);
		
		no_of_bytes = encode_bits(packed_bits, no_of_bytes, encoded_arr);
		
		printf("\n");
		
		printf("Encoded photo: %d bytes\n", no_of_bytes);
		
		print_encoded(encoded_arr, no_of_bytes, numRows, numCols);
	}
	
	return 0;
}


/*  Function: pack_bits(unsigned char unpacked_string[], int num_chars, unsigned char packed_result[])
    Description: Looping over each character in the unpacked_string[]. If the character is a ‘0’, then clearing the correct bit in the correct byte in the packed result array.
    		 If the character is a ‘1’, then setting the correct bit in the correct byte in the packed result array. Once a byte is created, storing that byte in the packed result array.
    		 Incrementing the number of bytes once a byte has been created.
                 

    Input: unpacked_string[]   - an unpacked array of characters returned by the take_photo() function
    Input: num_chars    -  the number of characters in the unpacked_string[]
    Output: packed_result[]    - an array to store the new, packed bytes into.

    Returns: Returning the number of bytes that's in the packed_result[]
    
*/
int pack_bits(unsigned char unpacked_string[], int num_chars, unsigned char packed_result[]){

	int index_unpacked_arr = 0;
	int num_bytes = 0;
	int index_packed_arr = 0;
	unsigned char byte;
	
	while(index_unpacked_arr <= num_chars-1){
	
		byte = unpacked_string[index_unpacked_arr];
		
		for(int j=7; j>=0; j--){
		
			if(unpacked_string[index_unpacked_arr] == '0'){
				
				byte = clear_bit(byte, j);
			}
			else{
			
				byte = set_bit(byte, j);
			}
			index_unpacked_arr++;
		}
		packed_result[index_packed_arr] = byte;
		index_packed_arr++;
		num_bytes++;
	}
	
	return num_bytes;
}


/*  Function: print_packed(unsigned char packed[], int rows, int cols)
    Description: Looping through each byte in the packed byte array, and then getting each bit of that byte
		 If the bit is a 0, then printing out a period ‘.‘ If the bit is a 1, then printing out an asterisk ‘*’. 
		 printing out a new line if we are at the end of our row
                 

    Input: packed[]   - an array containing the packed data
    Input: rows    -  the number of rows that the printed image will have
    Input: cols    - the number of columns that the printed image will have

    
*/
void print_packed(unsigned char packed[], int rows, int cols){

	int index_packed_arr = 0;
	int p = 7;
	
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			
			int bit = get_bit(packed[index_packed_arr], p);
			
			if(bit == 0){
				printf(".");
			}
			else{
				printf("*");
			}
			
			p--;
			
			if(p < 0){
				index_packed_arr++;
				p = 7;
			}
		}
		
		printf("\n");
	}
	
}

/*  Function: print_raw(unsigned char raw_string[], int rows, int cols)
    Description: Looping through each character in the raw_string[].
    		 If the character is a ‘0’, then printing out a period ‘.‘.
    		 If the character is ‘1’, then printing out an asterisk ‘*’. 
    		 printing out a new line if we are at the end of our row
                 

    Input: raw_string[]   - an array of characters returned by take_photo()
    Input: rows    -  the number of rows that the printed image will have
    Input: cols    - the number of columns that the printed image will have

*/
void print_raw(unsigned char raw_string[], int rows, int cols) {

	int index = 0;
	
	for(int i=0; i<rows; i++){
	
		for(int j=0; j<cols; j++){
			
			if(raw_string[index] == '0'){
				printf(".");
			}
			else{
				printf("*");
			}
			index++;
		}
		printf("\n");
	}

}


/*  Function: encode_bits(unsigned char packed[], int packed_size, unsigned char encoded_result[])
    Description: Encodes the bits that are in the packed[] using run length encoding starting with the number of consecutive 1s followed by the number of consecutive 0s

    Input: packed[]   - an array that contains the packed bytes
    Input: packed_size    - number of bytes in the packed array
    Output: encoded_result[]    - an array that contains the new, encoded bytes

    Returns: the number of bytes that are in the encoded_result[]
    
*/
int encode_bits(unsigned char packed[], int packed_size, unsigned char encoded_result[]){

	int index_encoded_arr = 0;
	int index_packed_arr = 0;
	int num_bytes = 0;
	
	int count = 0;
	int current_bit = 1;
	
	while(index_packed_arr <= packed_size - 1){
	
		for(int p=7; p>=0; p--){
		
			int next_bit = get_bit(packed[index_packed_arr], p);
			
			if(next_bit == current_bit){
			
				count = count + 1;
			}
			else{
			
				encoded_result[index_encoded_arr] = count;
				num_bytes++;
				index_encoded_arr++;
				current_bit = next_bit;
				count = 1;
			}
		}
		
		index_packed_arr++;
	}
	
	encoded_result[index_encoded_arr] = count;
	num_bytes++;
	
	return num_bytes;
}

/*  Function: print_encoded(unsigned char encoded[], int encoded_size, int rows, int cols)
    Description: The function takes in the array of encoded bytes and prints the 1s as asterisks (‘*’) and the 0s as periods (‘.‘)

    Input: encoded[]   - an array that contains the encoded bytes
    Input: encoded_size    - the size of the encoded[]
    Input: rows    - the number of rows that the printed image will have
    Input: cols    - the number of columns that the printed image will have
    
    
*/
void print_encoded(unsigned char encoded[], int encoded_size, int rows, int cols){

	int index = 0;
	int total_no_of_times_to_print = encoded[index];
	int no_of_times_printed = 0;
	
	for(int i=0; i<rows; i++){
	
		for(int j=0; j<cols; j++){
		
			if(total_no_of_times_to_print == 0){
			
				index++;
				total_no_of_times_to_print = encoded[index];
			}
			
			if(index % 2 == 0){
			
				printf("*");
				no_of_times_printed++;
				
				if(no_of_times_printed == total_no_of_times_to_print){
				
					index++;
					total_no_of_times_to_print = encoded[index];
					no_of_times_printed = 0;
				}
			}
			else{
			
				printf(".");
				no_of_times_printed++;
				
				if(no_of_times_printed == total_no_of_times_to_print){
				
					index++;
					total_no_of_times_to_print = encoded[index];
					no_of_times_printed = 0;
				}
			}
		}
		
		printf("\n");
	}
	
}

/*  Function: get_bit(unsigned char byte, int bit)
    Description: Gets the bit from the given byte at the specified bit position

    Input: byte   - the byte that contains the bit that we want to get
    Input: bit    - the position of the bit in the byte

    Returns: the bit that is located at the specified bit position
    
*/
unsigned char get_bit(unsigned char byte, int bit) {
    return (byte >> bit) & 1;
}

/*  Function: set_bit(unsigned char byte, int bit)
    Description: Sets the bit from the given byte at the specified bit position

    In/out: byte   - the byte that contains the bit that we want to set
    Input: bit    - the position of the bit in the byte

    Returns: the set bit that is located at the specified bit position
    
*/
unsigned char set_bit(unsigned char byte, int bit) {
    return byte | (1 << bit);
}

/*  Function: clear_bit(unsigned char byte, int bit)
    Description: Clears the bit from the given byte at the specified bit position

    In/out: byte   - the byte that contains the bit that we want to clear
    Input: bit    - the position of the bit in the byte

    Returns: the cleared bit that is located at the specified bit position
    
*/
unsigned char clear_bit(unsigned char byte, int bit) {
    return byte & ~(1 << bit);
}
