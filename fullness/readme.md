# System fullness

This program is intended to check if a folder's content changed since last time it was checked. This is done by writing in a file MD5 digest for each file in the folder and its sub-folders and then comparing with the previous similarly-written file.

Use *make reference* to set the reference file which will be used as the model to be compared to.  
Use *make check* to generate the file that will be compared to the reference file.

Using *make check* without setting a reference file will generate the same reference and test file, so that no difference will be found.
