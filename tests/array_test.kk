import "malloc" from "libc.so.6" as "alloc";
import "printf" from "libc.so.6" as "print";
import "scanf"  from "libc.so.6" as "scan";
import "free"   from "libc.so.6" as "delete";

function print_char(int chr):
	print(&chr);

function get_int_format_for_print() => int :
	var int h = alloc(16);
	*(h+0) = '%';
	*(h+1) = 'd';
	return h;

function main ():
	var int my_format = get_int_format_for_print();
	var int x = 0;
	scan(my_format,&x);
	print(my_format,x*1000);
	print_char(10);
	delete(my_format);