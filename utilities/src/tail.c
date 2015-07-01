#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFSIZE 4096

char buf[BUFSIZE];

size_t locate(int fd, int line);
void write_lines(int fd, off_t start, int line);

int main(int argc, char* argv[])
{
    int fd;
    int line;
    size_t start;

    if(argc != 4)
    {
        printf("Usage: tail_me -n LINE FILENAME\n");
        exit(0);
    }

    line = strtol(argv[2], NULL, 10);

    if( (fd = open(argv[3], O_RDONLY)) == -1 )
        perror(argv[3]);

    start = locate(fd, line);

    write_lines(fd, start, line);

    exit(0);
}

size_t locate(int fd, int line)
{
    size_t siz;
    
    off_t off;
    int i;
    int ln = 0; /* current lines */
    
    off = lseek(fd, -BUFSIZE, SEEK_END);
    if( off < 0 )
        off = lseek(fd, 0, SEEK_SET);
    while( (siz = read(fd, buf, BUFSIZE)) != -1 )
    {
        for( i = siz-1; i >= 0; i--)
        {
            if( buf[i] == '\n' )
                ln++;
            if( ln == line )
                return off + i;
        }
        if( off == 0 ) /* already at the beginning of file */
            return off;
        off = lseek(fd, -BUFSIZE, SEEK_CUR);
        if( off < 0 )
            off = lseek(fd, -BUFSIZE, SEEK_SET);
    }
}

void write_lines(int fd, off_t start, int line)
{
    size_t siz;
    int i;
    int ln=0;

    lseek(fd, start, SEEK_SET);
    while( (siz = read(fd, buf, BUFSIZE)) > 0  )
    {
        for( i = 0; i < siz; i++)
        {
            if( buf[i] == '\n' )
                ln++;
            if( ln == line )
                return;

            putchar( buf[i] );
        }
    }
}

