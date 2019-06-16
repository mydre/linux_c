int	 execl(const char * __path, const char * __arg0, ...) __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
execel函数会让一个可执行程序运行并替换本进程，那么这个可执行程序就应该有创建一个文件的功能。
可以用2-1-1实验中的file_creat.c编译产生的可执行文件file_creat来作为该可执行程序。
exec函数族会在一个进程中启动另一个程序执行，并用它来取代原调用进程的数段、代码段和堆栈段。
在执行完exec函数调用后，原调用进程的内容除了进程号之外，其他全部被新的进程替换了。
