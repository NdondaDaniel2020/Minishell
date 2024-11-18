#include <term.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
#include <termios.h> 	
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/resource.h>

int	main(void)
{
	int 	i;
	char	alpha;

	i = 0;
	alpha = 'a';
	while (i < 26)
	{
		printf("%i - %c %c\n", i + 1, alpha, alpha - 32);
		alpha++;
		i++;
	}
    return (0);
}
