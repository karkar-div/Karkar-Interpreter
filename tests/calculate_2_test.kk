import "printf" from "libc.so.6" as "print";
import "scanf"  from "libc.so.6" as "scan";

function main():
	# get and process the first number from the user
	var int x = 0;
	print("enter the first number:%c",10);
	scan("%d",&x);

	# get and process the second number from the user
	var int y = 0;
	print("enter the second number:%c",10);
	scan("%d",&y);

	var int z = 0;
	print("+ - * / %c",10);
	scan("%s",&z);

	if z == '+':
		print("result: %c%d%c",10,x+y,10);
	if z == '-':
		print("result: %c%d%c",10,x-y,10);
	if z == '*':
		print("result: %c%d%c",10,x*y,10);
	if z == '/':
		print("result: %c%d%c",10,x/y,10);
