运行程序时可以看到，程序会停一秒然后分别打印出父子进程的ID
也就是说子进程进来就阻塞一秒，但也没有先去运行父进程
总结：调用fork函数产生的父子进程运行顺序是不定的
而调用vfork函数产生的父子进程必定是子进程先运行完，父进程才会开始运行
