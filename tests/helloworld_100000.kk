import "printf" from "libc.so.6" as "print";
import "malloc" from "libc.so.6" as "alloc";

function main():
	var int str_ptr = alloc(13+8);
	*(str_ptr+0) = 'H';
	*(str_ptr+1) = 'e';
	*(str_ptr+2) = 'l';
	*(str_ptr+3) = 'l';
	*(str_ptr+4) = 'o';
	*(str_ptr+5) = ' ';
	*(str_ptr+6) = 'w';
	*(str_ptr+7) = 'o';
	*(str_ptr+8) = 'r';
	*(str_ptr+9) = 'l';
	*(str_ptr+10) = 'd';
	*(str_ptr+11) = '!';
	*(str_ptr+12) = 10;
	var int x = 0;
	while x < 100000 :
		print(str_ptr);
		x = x + 1;