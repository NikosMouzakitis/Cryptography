all:
	gcc xor.c
	./a.out 12345 input_file encrypted
	./a.out 12345 encrypted decrypted
	cat decrypted
clean:
	rm encrypted decrypted
	
