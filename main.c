#include "edbg.h"

int main()
{

	g_ErrCL = init_emsg();	

	cast_emsg(ETYPE_CPU, "Process run time has expired");
	cast_emsg(ETYPE_MEM, "Not enough resources");

	print_emsg();
	cast_emsg(ETYPE_IO, "device not supported");

	print_emsg();

	flush_ErrCL(g_ErrCL);

	return 0;
}
