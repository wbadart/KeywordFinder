# OS Project 4
## Web Crawler

This program can be used to verify the success of SEO efforts by scanning target sites for keywords.

## Team

- Badart, Cat *cbadart*
- Badart, Will *wbadart*

Error Handling:
In the config file, if you enter more than the max number of threads (8), an error message is printed but NUM_FETCH and/or NUM_PARSE is set to 8 and the program continues.  Likewise, if the number of threads is less than 1, an error message is printed and the number of threads is set to 1.  

If the specified Sites file and/or Search terms file is unable to opened, an error message is printed and the program exits.
