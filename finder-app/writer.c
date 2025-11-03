#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

#define CONSLOG 0    // print (1) or not (0) error message to stderr

int main (int argc, char *argv[])
{
    // Configure and opens the log file:
    char const *ident = "UCBOULDER-WRITER";
    int logopt = LOG_PID | LOG_ODELAY | LOG_CONS;
    int facility = LOG_USER;
    openlog(ident, logopt, facility);

    // To errno verifications:
    int errnum = 0;
    
    // Verify number of arguments
    if (argc != 3)
    {
        if (CONSLOG)
            fprintf(stderr, "Usage: %s destfile \"string\"\n", argv[0]);
        syslog(LOG_ERR, "[ERROR] Invalid number of arguments: %d.", argc);
        return EXIT_FAILURE;
    }

    // Syntatic sugar pointers
    char const *destfile = argv[1];
    char const *string = argv[2];

    // Verify if writefile is an absolute path:
    if (destfile[0] != '/')
    {
        if (CONSLOG)
            fprintf(stderr,
                    "[ERROR] %s is not an absolute full path to a file.\n",
                    destfile);
        syslog(LOG_ERR, "[ERROR] %s is not an absolute full path to a file.",
               destfile);
        return EXIT_FAILURE;
    }

    // Opens destfile
    FILE *outfile = fopen(destfile, "w");
    if (!outfile)
    {
        errnum = errno;
        if (CONSLOG)
            fprintf(stderr, "[ERROR] %s could not be open/created (%s).\n",
                    destfile, strerror(errnum));
        syslog(LOG_ERR, "[ERROR] %s could not be open/created (%s).",
               destfile, strerror(errnum));
        return EXIT_FAILURE;
    }

    // Write string to destfile:
    if (fprintf(outfile, "%s\n", string) < 0)
    {
        errnum = errno;
        if (CONSLOG)
            fprintf(stderr, "[ERROR] %s could not be writed in %s (%s).\n",
                    string, destfile, strerror(errnum));
        syslog(LOG_ERR, "[ERROR] %s could not be writed in %s (%s).",
               string, destfile, strerror(errnum));
        fclose(outfile);
        outfile = NULL;
        return EXIT_FAILURE;
    }
    else
    {
        syslog(LOG_DEBUG, "Writing %s to %s", string, destfile);
    }

    // Close destfile
    fclose(outfile);
    outfile = NULL;

    // Close log file:
    closelog();
}
