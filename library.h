#ifndef GLLIB_LIBRARY_H
#define GLLIB_LIBRARY_H

char findfile(const char* dirname, const char* key, int thread_count);
void *findfile_multithread(void *arguments);
void search(char toFind[]);

#endif //GLLIB_LIBRARY_H
