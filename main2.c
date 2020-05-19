
/* The program does what xxd program does. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* max numbers for -c, -l and -g arguments */
#define MAX_C_NUM 32
#define MAX_G_NUM 32
#define MAX_L_NUM 0x7FFFFFFF
#define MAX_S_NUM 0x7FFFFFFE

#define CURRENT_VERSION "v1.0"

#define ERR_RETURN 1
#define OK_RETURN  0

/* print_and_exit: print an error message and exit */
void print_and_exit(char *str, int out) {
    fprintf(stderr, "%s", str);
    exit(out);
}

int seek_file(FILE *file, long int s_mode, unsigned long int s_num) {
    if (s_mode) {
        if (fseek(file, s_num, SEEK_END)) 
    		return ERR_RETURN;
    } else if (fseek(file, s_num, SEEK_SET))
    	return ERR_RETURN;
    return OK_RETURN;
}

/* print_spaces: print a necessary number of spaces before ascii part */
void print_spaces(int j, unsigned long int c_num, char *out_str_p) {
    for (; j <= c_num; j++) {
	    if (j % 2 == 0)
	        if (j != c_num)
	            sprintf(out_str_p++, " ");  /* XXYY_XXYY_XXYY_ ... */
	    sprintf(out_str_p, "  ");       /* ____ ____ ____  ... */
	    out_str_p += 2;
	}
}

/* for get_number() function */
#define SECOND_ARG      2
#define FIRST_ARG       1
#define NO_ARG          0

/* get_number: get hex-number for -l -g and -c arguments; character '-' minus will
   be ignored */
int get_number(char *argv1, char *argv2, unsigned long int *put_to) {
    int out;
    
    if (*argv1 == '\0') {
        if (*argv2 == '-')
            argv2++;   /* miss */
        if (sscanf(argv2, "%lx", put_to))
            out = SECOND_ARG;
        else
            out = NO_ARG;
    } else {
        if (*argv1 == '-')
            argv1++;   /* miss */
        if (sscanf(argv1, "%lx", put_to))
	        out = FIRST_ARG;
	}
	return out;
}

struct file_vars {
        FILE *fi, *fo;
        char *cif, *cof;
        int inf, outf;
};

struct arg_vars {
    int l_arg, a_arg, r_arg, i_arg, u_arg, p_arg, s_mode;
    unsigned long int s_num, l_num, g_num, c_num;
};

int open_and_seek(struct file_vars *files, struct arg_vars *arg) {
    if (file->outf && strcmp(file->cof, "-")) {  
        if (arg->r_arg) {
            if ((file->fo = fopen(file->cof, "r+")) == NULL  ||
    		    seek_file(file->fo, arg->s_mode, arg->s_num) ||
                (arg->s_num = ftell(file->fo)) == -1L)       ||
                    return ERR_RETURN;
        } else if ((file->fo = fopen(cof, "w")) == NULL)
    		    return ERR_RETURN;
    }
    if (file->inf && strcmp(file->cif, "-")) {
        if ((file->fi = fopen(file->cif, "r+")) == NULL)
    		return ERR_RETURN;
   	    if (arg->r_arg == 0) {
    	    if (seek_file(file->fi, arg->s_mode, arg->s_num) ||
    	        (s_num = ftell(file->fi)) == -1L)
    	            return ERR_RETURN;
        }
    }
    return OK_RETURN; 
}

int treat_r_argument(struct file_vars *file, struct arg_vars *arg) {
    int hex;   /* character we've had */
    unsigned long int c_num = arg->c_num;
	unsigned long int s_num = arg->s_num;
	   
	if (arg->p_arg == 0)
	    while((hex = fgetc(file->fi)) != '|' && hex != EOF)
	        ;
    while (s_num <= MAX_S_NUM) {
	    if (fscanf(file->fi, "%2x", &hex) == 1) {
	        c_num--;
	        if (fputc(hex, file->fo) == EOF)
	            return ERR_RETURN;
	    } else {
	        if (feof(file->fi)   ||
	            ferror(file->fi))
	                return ERR_RETURN;
	    }
	    if (c_num == 0) {
	        while ((hex = fgetc(file->fi)) != '|' && hex != EOF)
	            ;
	        if (arg->p_arg == 0)
	            while((hex = fgetc(file->fi)) != '|' && hex != EOF)
	            ;
	        c_num = arg->c_num;
	    }
	    s_num++;
	}
	return OK_RETURN; 
}


int main(int argc, char **argv) {
 
    /* for input/output setting */
    struct file_vars file = { stdin, stdout, "-", "-", 0, 0 };
    struct arg_vars arg = { 0, 0, 0, 0, 0, 0, 0,
                            0, MAX_L_NUM, 2, 0x10 };
   
    char *progname = *argv;

    char null_str[MAX_C_NUM];
/************************************************* get arguments */
    while (--argc > 0) {
        char *arg = NULL;
        char *p = NULL;
        int out;
        
	    if (file_vars.outf) {   /* output file must be a last argument we can get */
	        fprintf(stderr, "error: incorrect order of arguments\n\n%s", usage);
	        exit(1);
	    }
	    p = *++argv;
	    if (inf) {
	            cof = p;
    		    outf = 1;
    		    continue;
    	}
	    if (*p =='-') {
	        switch(*++p) {
	    	    case '\0':   /* "-" character means a standard input or output stream */
	    	        if (inf) outf = 1; else inf = 1;
	    	        break;
    	    	case  's':
    	    	    /* arg is a (char *) point to a first digit of number(future file position) */
    	    	    if (*++p == '\0') {
    	    	        arg = *++argv;
    	    	        argc--;
    	    	    } else
    	    	        arg = p;
    	    	    
    	    	    /* get the number */    
    	    	    if (*arg == '-') {
    	    	        if (sscanf(arg + 1, "%lx", &s_num))
    	    	           s_mode = 1;
    	    	    } else if (sscanf(arg, "%lx", &s_num)) 
    	    	        s_mode = 0;
    	    	    else 
    	    	        print_and_exit("error: can't take a -s argument(offset)\n", 1);
    	    	        
    	    	    /* check the number */
    	    	    if (s_mode == 0) {
    	    	        if (s_num > MAX_S_NUM)  /* not 0x7FFFFFFF */
    	    	            print_and_exit("error: too big offset in -s argument\n", 1);
    	    	    } else if (s_num > MAX_S_NUM + 1)  /* yes, 0x7FFFFFFF */
    	    	            print_and_exit("error: too big negative offset in -s argument\n", 1);
    	    	    
    	    	    /* get the negavite number for fseek() function;
    	    	       note: 7FFFFFFF go to 80000001, that's right */
    	    	    if (s_mode)
    	    	        s_num = -s_num;
		            break;
        		case  'l':
        		    if ((out = get_number(++p, *(argv + 1), &l_num)) == SECOND_ARG) {
        		        argv++; argc--;   /* because we took two argc's arguments */
        		    }
        		    if (l_num > MAX_L_NUM)  /* 0x7FFFFFFF bytes we can print: from 0 to 7FFFFFFE file position; or - none */
    	    	        print_and_exit("error: too big length in -l argument\n", 1);
    	    	    else if (out == NO_ARG)  /* error with getting a number of argument */
    	    	        print_and_exit("error: can't take a -l argument(length)\n", 1);
    	    	    else if (l_num == 0)
    	    	        print_and_exit("error: -l argument(length) don't have to be 0\n", 1);
                    break;
        		case  'g':
        		    /* the same */
        		    if ((out = get_number(++p, *(argv + 1), &g_num)) == SECOND_ARG) { 
        		        argv++; argc--; 
        		    }
        		    if (g_num > MAX_G_NUM)
        		        print_and_exit("error: too big group in -g argument\n", 1);
        		    else if (out == NO_ARG)
    	    	        print_and_exit("error: can't take a -g argument(group)\n", 1);
    	    	    else if (g_num == 0)
    	    	        print_and_exit("error: -g argument(number) don't have to be 0\n", 1);
        		    break;
        		case  'c':   
        		    /* the same */             
        		    if ((out = get_number(++p, *(argv + 1), &c_num)) == SECOND_ARG) { 
        		        argv++; argc--; 
        		    }
        		    if (c_num > MAX_C_NUM)
        		        print_and_exit("error: too big number of characters in one line\n", 1);
        		    else if (out == NO_ARG)
    	    	        print_and_exit("error: can't take a -c argument(characters)\n", 1);
    	    	    else if (c_num == 0)
    	    	        print_and_exit("error: -c argument(number) don't have to be 0\n", 1);
    	     	    break;
    		    case  'h':    
    	    	    fprintf(stdout, "%s", usage);
    	    	    exit(0);
    	    	    break;
    	    	case  'a': a_arg = 1; break;
    	    	case  'i': i_arg = 1; break;
		        case  'r': r_arg = 1; break;  // no
		        case  'u': u_arg = 1; break;
	        	case  'v': 
	        	    fprintf(stdout, "%s\n", CURRENT_VERSION);
	        	    exit(0);
	        	case  'p': p_arg = 1; break;
	        }  /* switch */
	    } else {
    		cif = p;
    		inf = 1;
    	}
    }  /* while */
  
      fprintf(stderr, "s: %lX == %ld\n", s_num, s_num);
/*   printf("%lX == %ld\n", s_mode, s_mode);
  printf("l: %lX == %ld\n", l_num, l_num);
  printf("c: %lX == %ld\n", c_num, c_num);
  printf("g: %lX == %ld\n", g_num, g_num);
*/
/************************************************************* open files */
    /* the program returns 2 as an error number, if openinig or seeking cause an error */
    if (open_and_seek(&file, &arg))
        exit(2);
/************************************************************* u argument */
	char *address;   /* print 0XXXXXXX: */
	char *hex_case;  /* print 0xXX or XX */
	if (arg->i_arg)
	    if (arg->u_arg) hex_case = "0x%02X"; else hex_case = "0x%02x";
	else
	    if (arg->u_arg) hex_case = "%02X"; else hex_case = "%02x";
	if (arg->u_arg) address = " %08X | "; else address = " %08x| ";

    /************************************************************* r argument */
    if (r_arg) 
        if (treat_r_argument(&file, &arg))
            exit(3);
    /************************************************************* i argument */
    else if (i_arg) {  
        int ch, ch2;
        unsigned long int k;
        
        if (l_num != 0)
            fprintf(fo, "unsigned int %s[] = {\n", cif);
        else
            exit(0);
        
        /* check a FIRST character; maybe array is empty */
        if ((ch = fgetc(fi)) == EOF)
            if (ferror(fi))
                print_and_exit("error: in getting characters from the input stream\n", 3);
            else if (feof(fi)) {
                fprintf(fo, "};");
                fprintf(fo, "\nunsigned int %s_len = 0x%lx;\n", cif, (long) 0);
                exit(0);
            }
                
        fprintf(fo, "\t");
        if (l_num == 1) {
            fprintf(fo, hex_case, ch);
            fprintf(fo, "\n};");
            fprintf(fo, "\nunsigned int %s_len = 0x%lx;\n", cif, (long) 1);
        }
        
        for (k = 2; k <= l_num; k++) {
            ch2 = fgetc(fi);   /* get SECOND character */
            if (k != l_num  && ch2 != EOF) {
                fprintf(fo, hex_case, ch);  /* print FIRST character */
                fprintf(fo, ", ");
            } else {
                fprintf(fo, hex_case, ch);
                if (ch2 == EOF) {
                    if (ferror(fi))
                        print_and_exit("error: in getting characters from the input stream\n", 3);
                }
                if (k == l_num) {
                    if (feof(fi))  /* if k == l_num and eof is occurred, don't print SECOND character */
                        k--;       /* we have k - 1 characters */
                    else {
                        fprintf(fo, ", ");
                        fprintf(fo, hex_case, ch2);
                    }
                } else 
                    k--;   /* if eof is occurred */
                fprintf(fo, "\n};");
                fprintf(fo, "\nunsigned int %s_len = 0x%lx;\n", cif, k);
                break;
            }
            ch = ch2;

            if ((k - 1) % c_num == 0)
                fprintf(fo, "\n\t");
        }
        exit(0);
    }
/**************************************************************** default */
    else {
	    int c, j, i;
	    int ch_zero = 0;  /* number of 0x00 characters in a current line */
	    int star = 0;     /* if star == 1, "*" character was already printed */
	    int up_zero = 0;  /* if up_zero == 1, one NULL-line was already printed */

        if (l_num == 0)
            exit(0);
            
	    /* take a max necessary array for the output ascii string */
	    char *out_ascii, *out_ascii_p;
	    out_ascii = out_ascii_p = (char *) malloc(2 + c_num + 2);

        /* take a max necessary array for the output string */
	    char *out_str, *out_str_p;
	    out_str = out_str_p = (char *) malloc(11 + c_num * 2 + c_num + 3);

	    while (1) {
	        /* either print or don't print the address */
	        if (p_arg == 0) {
	            sprintf(out_str_p, address, s_num);
	            out_str_p += 11;
	        }
	        
	        for (j = 1; j <= c_num; j++, l_num--) {
	            /* we read all characters */
	            if (l_num == 0) {
	                /* fill the space before ascii part(if exist) */
	                print_spaces(j, c_num, out_str_p);
	                fprintf(fo, "%s", out_str);
                    if (p_arg == 0)
	                    fprintf(fo, " | %s", out_ascii);
	                fprintf(fo, "\n");
	                exit(0); 
	            }
	            
	            if ((c = fgetc(fi)) == EOF) {
	                if (feof(fi)) {
	                    /* a necessary to put spaces before the ascii part */
	                    if (j != 1) {
	                        print_spaces(j, c_num, out_str_p);
	                        fprintf(fo, "%s", out_str);
	                        if (p_arg == 0) {    /* if a postscript style */
	                            fprintf(fo, " | %s", out_ascii);
	                        }
	                    }
	                    fprintf(fo, "\n");
	                    exit(0);
	                } else 
	                    print_and_exit("error: in getting characters from the input stream\n", 3);            
	            }
	                    
	            sprintf(out_str_p, hex_case, (unsigned long int) c);
	            out_str_p += 2;
	            
	            if (c == 0)  /* we have 0x00 character */
	                ch_zero++;
	            
	            /* print the character and a separator */
	            if (p_arg == 0) {
	                if ((j % g_num) == 0)
	                    if (j != c_num)
	                        sprintf(out_str_p++, " ");
	                if (isprint(c))
	                    sprintf(out_ascii_p++, "%c", c);
	                else
	                    sprintf(out_ascii_p++, ".");
	            }
	        }  /* for (...) */
	        if (a_arg && l_num != 0) {  /* l_num != 0, because last line always must be printed */
	            if (ch_zero == c_num) {
	                if (up_zero == 0)
    	                up_zero = 1;   /* first NULL-line must be printed */
    	            else {
    	                if (star == 0)
    	                    fprintf(fo, " *\n");   /* it's second NULL-line */
    	                star = 1;
    	                ch_zero = 0;
    	                /* form a new address to the output string */
    	                s_num += c_num;
    	                /* a pointers must point to beginning of strings */
    	                out_ascii_p = out_ascii;
     	                out_str_p = out_str;
    	                continue;
    	            }
    	        } else {  /* let's do cycle again */
    	            up_zero = 0;
    	            star = 0;
    	            ch_zero = 0;
	            }
	        }
	                
	        fprintf(fo, "%s", out_str);
	        /* either print or don't print the ascii part */
	        if (p_arg == 0)
	            fprintf(fo, " | %s", out_ascii);
	        fprintf(fo, "\n");
	        
	        /* in case j == c_num and l_num == 0 */
	        if (l_num == 0)
	            exit(0);

	        /* form a new address to the output string */
	        s_num += c_num;
	        /* a pointers must point to beginning of strings */
	        out_ascii_p = out_ascii;
	        out_str_p = out_str;
	    }  /* while (1) */
	}
}  /* main() */

