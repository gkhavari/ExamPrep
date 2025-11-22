#include "get_next_line.h"
char    *get_next_line(int fd)
{
    static char *buf = NULL;
    static int  filled = 0;
    static int  pos = 0;
    char        tmp[BUFFER_SIZE];
    int         r, i;

    if (fd < 0)
        return (NULL);

    /* Allocate the large internal buffer once */
    if (!buf)
    {
        buf = malloc(1000000);
        if (!buf)
            return (NULL);

        /* Repeatedly fill until EOF */
        while ((r = read(fd, tmp, BUFFER_SIZE)) > 0)
        {
            if (filled + r > 1000000)
                break;
            for (i = 0; i < r; i++)
                buf[filled + i] = tmp[i];
            filled += r;
        }
        if (filled == 0)
            return (free(buf), buf = NULL, NULL);
    }

    /* If we consumed all data */
    if (pos >= filled)
        return (NULL);

    /* Find end of current line */
    i = pos;
    while (i < filled && buf[i] != '\n')
        i++;

    int len = i - pos + (i < filled && buf[i] == '\n');
    char *line = malloc(len + 1);
    if (!line)
        return (NULL);

    for (int j = 0; j < len; j++)
        line[j] = buf[pos + j];
    line[len] = '\0';

    pos += len;
    return (line);
}
