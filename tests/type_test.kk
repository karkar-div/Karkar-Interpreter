import "malloc" from "libc.so.6" as "alloc";
import "printf" from "libc.so.6" as "print";

function max(int x,int y):
	if x > y:
		return x;
	if y > x:
		return y;
	return x;

function hello_str() => int :
	var int str_ptr = alloc(13);
	*(str_ptr+0) = 'H';
	*(str_ptr+1) = 'e';
	*(str_ptr+2) = 'l';
	*(str_ptr+3) = 'l';
	*(str_ptr+4) = 'o';
	*(str_ptr+5) = 0;
	return str_ptr;

function main():
	if max(1,2) == 2:
		print(hello_str());


