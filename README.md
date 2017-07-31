# ft_p
This project is about implementing a client and a server that allow the transfer of files within a TCP/IP network.

ft_p implements:
 * lpwd | pwd
 * ls | lls
 * put
 * get
 * lecho 
 * cd | lcd
 * lsetenv
 * lunsetenv
 * lenv
 * quit | exit
* lhistory
 * lhistory n
 * lhistory -c
 * ^string^string^
 * !string
 * !n
 * !! and !-1
 * CTRL+R (reverse-i-search)
 * :arrow_up: UP or :arrow_down: DOWN
* Copy and Paste
 * CTRL-W - Copy what is currently in front of the cursor.
 * CTRL-G - Copy the entire line that has being typed.
 * CTRL-K - Cut or delete what is currently in front of the cursor.
 * CTRL-X - Cut or delete the entire line that has being typed.
 * CTRL-V - Paste the last thing you deleted (using CTRL-K, CTRL-W, CTRL-G or CTRL-X ).
* Auto complete
* lunset
* lexport
* line edition
* the “;” command line separator
* pipes “|”
* redirections “<”, “>”, “<<” & “>>”
* file descriptor aggregation (e.g. ``2>&-`` & ``1>&2``)
* Go directly to the beginning or the end of a line by pressing home and end.
* Move directly by word towards the left or the right using ctrl+LEFT and ctrl+RIGHT.
* Simple logical operators (&& and ||)
* CTRL+T for swapping characters.
* CTRL+P get previous history.
* CTRL+H delete character from cmd

# Installation
```
$ git clone https://github.com/julekgwa/ft_p
```

# Usage
```
$ cd ft_p && make
```

start server
```
$ ./server 8000
```

run client
```
$ ./client 127.0.0.1 8000
```
# License
MIT
