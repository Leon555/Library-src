#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <getopt.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <stdint.h>

enum filetype
{
    unknown,
    fifo,
    chardev,
    directory,
    blockdev,
    normal,
    symbolic_link,
    sock,
    whiteout,
    arg_directory
};
  
struct file_info {
    char            *name;
    char            *linkname;
    struct stat     stat;
    enum filetype   filetype;
    
    bool            link_ok;
    bool            stat_ok;
};

struct file_node {
	struct file_info 	*file;
	struct file_node	*prev;
	struct file_node	*next;
};

/*
 * Name: decode_switches -- translate the command line arguments into local variables
 * Description: 
 * Arguments: argc is the number of command line arguements,
              argv is the command line argument list
 * Return Values: optind as return value, aka, next known option character in optstring
 */
static int decode_switches(int argc, char **argv);

/*
 * Name: list -- list the files and directories for some path
 * Description: 
 * Arguments: path: the path whose contents will be displayed
              recursively: if true, lists the contents of the directories;
                           if false, treats directories same as files.
 * Return Values: void
 */
static void list(char *path, bool recursively);

/*
 * Name: sort_files -- sort the files&directories by some criterion
 * Description: 
 * Arguments: 
 * Return Values: void
 */
static void sort_files(struct file_info **sorted_files);
static void sort_by_time(struct file_info **sorted_files);
static void sort_by_size(struct file_info **sorted_files);

static void add_node(struct file_info *file);
static void add_node_by_size(struct file_node *new_node);
static void add_node_by_time(struct file_node *new_node);

static struct file_node * init_list();
static void reset_list();
static void free_node(struct file_node * node);
static void destroy_list();
static void insert_node(struct file_node *prev, struct file_node *next, struct file_node *node);

/*
 * Name: print_files -- print the files in file_info array
 * Description: 
 * Arguments: 
 * Return Values: void
 */
static void print_files();

struct file_node * node_head;
struct file_node * node_tail;

/*
 * switch list: ls switches likewise
 * supporting both short options and long options
 */
static bool all_except_dot = false;     /* -A */
static bool list_all = false;           /* -a */
static bool sort_by_ctime = false;      /* -c */
static bool with_color = false;         /* --color */
static bool full_time = false;          /* --full-time */
static bool human_readable = false;     /* -h, --human-readble */
static bool with_ino = false;           /* -i */
static bool long_format = false;        /* -l */
static bool dereference_symlinks = false; /* -L, --dereference */
static bool width_with_comma = false;   /* -m */
static bool numeric_uid_gid = false;    /* -n, --numeric-uid-gid */
static bool reverse_order = false;      /* -r */
static bool recursively_listing = false;/* -R */
static bool sort_by_file_size = false;  /* -S */
static bool sort_by_mtime = false;      /* -t */
static bool one_file_per_line = false;  /* -1 */
static bool with_version = false;       /* --version */

char short_switches[] = "AachiI:lLmnrRSt1";

/* For long options that have no equivalent short option, use a
   non-character as a pseudo short option, starting with CHAR_MAX + 1.  */
enum
{
  AUTHOR_OPTION = CHAR_MAX + 1,
  COLOR_OPTION,
  FULL_TIME_OPTION,
  HELP_OPTION,
  VERSION_OPTION
};

static struct option const long_options[] = 
{
    {"color", optional_argument, NULL, COLOR_OPTION},
    {"full-time", no_argument, NULL, FULL_TIME_OPTION},
    {"human-readable", no_argument, NULL, 'h'},
    {"dereference", no_argument, NULL, 'L'},
    {"ignore", required_argument, NULL, 'I'},
    {"numeric-uid-gid", no_argument, NULL, 'n'},
    {"help", no_argument, NULL, HELP_OPTION},
    {"version", no_argument, NULL, VERSION_OPTION},
    {NULL, 0, NULL, 0}
};

int main(int argc, char* argv[])
{
	int optindex;

	optindex = decode_switches(argc, argv);
	
	init_list();

	list( argv[optindex], recursively_listing );

	destroy_list();

	exit(0);
}

int decode_switches(int argc, char** argv)
{
	for(;;)
	{
		int oi = -1;
		int c = getopt_long(argc, argv, short_switches, long_options, &oi);
	
		if( c == -1 )
			break;
		
		switch (c)
		{
			case 'A':
				all_except_dot = true; 
				break;
			case 'a':
				list_all = true; 
				break;
			case 'c':
				sort_by_ctime = true;
				break;
			case 'C':
				with_color = true;
				break;
			//case ' full_time
			case 'h':
				human_readable = true;
				break;
			case 'i':
				with_ino = true;
				break;
			case 'l':
				long_format = true;
				break;
			case 'L':
				dereference_symlinks = true;
				break;
			case 'm':
				width_with_comma = true;
				break;
			case 'r':
				reverse_order = true;
				break;
			case 'R':
				recursively_listing = true;
				break;
			case 'S':
				sort_by_file_size = true;
				break;
			case 't':
				sort_by_mtime = true;
				break;
			case '1':
				one_file_per_line = true;
				break;
			//case with_version
			default:
				break;
		}
}

void print_files()
{
	struct file_node *node;

	if( reverse_order )
	{
		node = node_tail->prev;
		while( node != node_head )
		{
			printf("%s\n", node->file->name);
			node = node->prev;
		}
	}
	else
	{
		node = node_head->next;
		while( node != node_tail )
		{
			printf("%s\n", node->file->name);
			node = node->next;
		}
	}
}

void list(char *path, bool recursively)
{
	DIR* dp;
	struct dirent *dirp;
	struct file_info *file;

	if( (dp = opendir(path)) == NULL )
		return ;

	while( (dirp = readdir(dp)) != NULL )
	{
		file = (struct file_info *) malloc( sizeof(struct file_info) );
	
		if( strstr(dirp->d_name, ".") == dirp->d_name )
			continue;
		size_t len = strlen(dirp->d_name);
		file->name = (char *) malloc (len+1);
		strcpy(file->name, dirp->d_name);
		file->name[len] = '\0';

		stat(dirp->d_name, &file->stat);
		
		add_node(file);
	}
	print_files();
	reset_list();

	while(
	if( recursively && S_ISDIR(file->stat.st_mode) )
		list(dirp->d_name, recursively);
}

struct file_node * init_list()
{
	struct file_info *file_head = (struct file_info *) malloc ( sizeof(struct file_info) );
	struct file_info *file_tail = (struct file_info *) malloc ( sizeof(struct file_info) );
	
	if( file_head && file_tail )
	{
		file_head->stat.st_size = -1;
		file_tail->stat.st_size = SIZE_MAX;
	}
	else
		perror("Cannot init file_info");

	node_head = (struct file_node *) malloc ( sizeof(struct file_node) );
	node_tail = (struct file_node *) malloc ( sizeof(struct file_node) );

	if( node_head && node_tail )
	{
		node_head->file = file_head;
		node_head->next = node_tail;
		node_head->prev = NULL;

		node_tail->file = file_tail;
		node_tail->prev = node_head;
		node_tail->next = NULL;
	}
	else
		perror("Cannot init linked list");
	
	return node_head;
}

void add_node(struct file_info *file)
{
	struct file_node *new_node = (struct file_node *) malloc ( sizeof(struct file_node) );
	if ( new_node != NULL )
	{
		new_node->file = file;
		new_node->next = NULL;
		new_node->prev = NULL;
	}
	else
		perror("Can't get new node");

	// empty list
	if( node_head->next == node_tail )
	{
		insert_node(node_head, node_tail, new_node);

		return;
	}

	sort_by_file_size = true;

	if( sort_by_file_size )
		add_node_by_size(new_node);
	else if( sort_by_ctime || sort_by_mtime )
		add_node_by_time(new_node);

}

void add_node_by_size(struct file_node *new_node)
{
	struct file_node *node = node_head;
	off_t prev_size, next_size;
	off_t size;

	off_t new_size = new_node->file->stat.st_size;
	
	while( (node = node->next) != node_tail )
	{
		size = node->file->stat.st_size;
		
		prev_size = node->prev->file->stat.st_size;
		next_size = node->next->file->stat.st_size;

		if( new_size <= size && new_size > prev_size )
		{
			insert_node(node->prev, node, new_node);
			return;
		}
		if( new_size >= size && new_size < next_size )
		{
			insert_node(node, node->next, new_node);
			return;
		}
	}
}

void add_node_by_time(struct file_node *new_node)
{
    
}

void insert_node(struct file_node *prev, struct file_node *next, struct file_node *node)
{
	node->prev = prev;
	node->next = next;
	
	prev->next = node;
	next->prev = node;
}

void reset_list()
{
	struct file_node *node = node_head;
	struct file_node *temp;
	while( node->next != node_tail )
	{
		// the node to be freed
		temp = node->next;
		// next node
		node->next = temp->next;
		free_node(temp);
	}
	node_head->next = node_tail;
	node_tail->prev = node_head;
}

void destroy_list()
{
	free(node_head);
	free(node_tail);
}

void free_node(struct file_node *node)
{
	if( node && node->file )
	{
		free(node->file);
		node->file = NULL;
		free(node);
		node = NULL;
	}
}
























