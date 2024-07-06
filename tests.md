<p align="center">
  <img src="https://github.com/jotavare/jotavare/blob/main/42/banners/piscine_and_common_core/github_piscine_and_common_core_banner_minishell.png">
</p>

<p align="center">
	<img src="https://img.shields.io/badge/status-finished-success?color=%2312bab9&style=flat-square"/>
	<img src="https://img.shields.io/badge/evaluated-18%20%2F%2012%20%2F%202022-success?color=%2312bab9&style=flat-square"/>
	<img src="https://img.shields.io/badge/score-100%20%2F%20100-success?color=%2312bab9&style=flat-square"/>
	<img src="https://img.shields.io/github/languages/top/jotavare/minishell?color=%2312bab9&style=flat-square"/>
	<img src="https://img.shields.io/github/last-commit/jotavare/minishell?color=%2312bab9&style=flat-square"/>
	<a href='https://www.linkedin.com/in/joaoptoliveira' target="_blank"><img alt='Linkedin' src='https://img.shields.io/badge/LinkedIn-100000?style=flat-square&logo=Linkedin&logoColor=white&labelColor=0A66C2&color=0A66C2'/></a>
	<a href='https://profile.intra.42.fr/users/jotavare' target="_blank"><img alt='42' src='https://img.shields.io/badge/Porto-100000?style=flat-square&logo=42&logoColor=white&labelColor=000000&color=000000'/></a>
</p>

<p align="center">
	<a href="#about">About</a> •
	<a href="#important-information">Important Information</a> •
	<a href="#utilities">Utilities</a> •
	<a href="#command-examples">Command Examples</a> •
	<a href="#norminette">Norminette</a> •
	<a href="#license">License</a>
</p>

## ABOUT
The existence of shells is linked to the very existence of IT. At the time, all developers agreed that communicating with a computer using aligned 1/0 switches was seriously irritating. It was only logical that they came up with the idea of creating software to communicate with a computer using interactive lines of commands in a language somewhat close to the human language.

Thanks to Minishell, I travelled through time and came back to problems people faced when Windows didn’t exist. This project was about creating a simple shell, my own little bash. I learned a lot about processes and file descriptors.

- [Subject](https://github.com/jotavare/minishell/blob/main/subject/en_subject_minishell.pdf) `PDF`
- [References](https://github.com/jotavare/42-resources#03-minishell) `GitHub`

## IMPORTANT INFORMATION
#### BEFORE EVALUATION
> Check this list before delivering the project.

- [x] Check the norminette for any errors.
- [x] Check for segmentation faults, bus errors, double free, leaks, ...
- [x] Must compile with -Wall, -Wextra and -Werror.
- [x] Makefile must contain $(NAME), all, clean, fclean.
- [x] Check for forbidden functions in your code.
- [x] Check the subject for any other requirements.

#### NICE TO KNOW
> Some nice-to-know commands that will help the evaluatee and the evaluator.

| Important Commands                | Description                                                              |
| :-------------------------------- | :----------------------------------------------------------------------- |
| `make -n`                         | Display the compilation information without actually compiling the code. |
| `echo $?`                         | Display the exit status of the last executed command.                    |
| `nm -g ./minishell \| grep " U "` | Check for forbidden functions.                                           |
| `norminette`                      | Checks the code for compliance with the coding style and guidelines.     |
| `-R CheckForbiddenSourceHeader`   | Check the code in header files.                                          |
| `cc -g -Wall -Wextra -Werror`     | Compile with the mandatory flags.                                        |
| `-fsanitize=address`              | Check for leaks.                                                         |
| `-lreadline`                      | Necessary to use the readline library.                                   |
| `ps -e` or `ps -A`                | See all processes currently running on your computer.                    |
| `ps -a`                           | Check for any dead children.                                             |

#### VALGRIND
> Important valgrind flags that are necessary to know every single leak.

| Valgrind Flags                 | Description                                      |
| :----------------------------- | :----------------------------------------------- |
| `valgrind ./minishell`         | Check for leaks                                  |
| `-leak-check=full`             | Detailed checking for memory leaks.              |
| `--show-leak-kinds=all`        | Display all types of memory leaks.               |
| `--track-origins=yes`          | Tracks the origins of uninitialized values.      |
| `--verbose`                    | Increases the level of verbosity.                |
| `--gen-suppressions=all`       | Ignore specific known issues or false positives. |
| `--suppressions=readline.supp` | Specifies the path to a suppression file.        |
| `--log-file=memleaks.log`      | Sets the name of the file.                       |

> To ignore leaks related to the `readline` and `add_history` functions, create a file called `readline.supp` with the following content:
```
{
    leak readline
    Memcheck:Leak
    ...
    fun:readline
}
{
    leak add_history
    Memcheck:Leak
    ...
    fun:add_history
}
```

`valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell`

## UTILITIES
#### Return Values ($?)
> The values that a function returns when it completes.

* All Linux commands return an error code between `0` and `255`.
* The value 0 represents the value true (command success).
* Values greater than 0 represent false (command failure).
* The error code of the last command used is contained in the variable `$?`.

| $?      | Description                                                                             |
| :------ | :-------------------------------------------------------------------------------------- |
| `1`     | Standard for general errors, such as a division by zero.                                |
| `2`     | Improper use of built-in commands, per Bash documentation.                              |
| `126`   | The command called cannot be executed, rights problem or the command is not executable. |
| `127`   | Command not found, possible problem with $PATH or typing error.                         |
| `128`   | Invalid command argument.                                                               |
| `128+n` | 128 + signal number.                                                                    |
| `130`   | Finished with `Ctrl` + `C` (130 = 128 + 2).                                             |
| `255`   | Exit code out of bounds. Example: `exit -1`.                                            |

#### Command Reminders
> More nice-to-know commands that may be useful in the future.

| Command       | Description                                                                                 |
| :------------ | :------------------------------------------------------------------------------------------ |
| `yes`		| Writes in an infinite loop `yes teste`.                                                     |
| `ln`		| Bind a file or directory.                                                                   |
| `chmod`	| Change file permissions `chmod 777` (all permissions) `chmod 000` (no permissions).         |
| `cd`		| Change directory. `cd -` (last visited directory) `cd` (user directory) `cd /` (root).      |
| `clear`	| Clear the screen.                                                                           |	
| `diff`	| Compare files line by line.                                                                 |
| `cmp`		| Write the first line of difference between 2 files.                                         |
| `pc`		| Copying files.                                                                              |
| `rm`		| Delete file.                                                                                |
| `rm -rf`	| Delete the directory recursively.                                                           |
| `ls -l`	| Show the contents of the directory.                                                         |
| `exit`	| Exit current process.                                                                       |
| `grep`	| Search for strings in files `grep "printf" file`.                                           |
| `mkdir`	| Create a directory.                                                                         |
| `rmdir`	| Delete a directory.                                                                         |
| `more`	| Displays a file page by page as in a man.                                                   |
| `mv`		| Move or rename.                                                                             |
| `$PATH`	| Path to executables.                                                                        |
| `cat`		| Send the file to stdout.                                                                    |

#### CHMOD
> Change the access permissions and the special mode flags of file system objects.

| Rights        | Number |
| :------------ | :----- |
| `r` (read)	| `4`    |
| `w` (write)	| `2`    |
| `x` (execute)	| `1`    |
	
| Rights  | Calculation | Total |
| :------ | :---------- | :---- |
| `---`   | `0+0+0`     | `0`   |
| `r--`   | `4+0+0`     | `4`   |
| `-w-`   | `0+2+0`     | `2`   |
| `--x`   | `0+0+1`     | `1`   |
| `rw-`   | `4+2+0`     | `6`   |
| `-wx`   | `0+2+1`     | `3`   |
| `x-ray` | `4+0+1`     | `5`   |
| `rwx`   | `4+2+1`     | `7`   |

#### DATA TYPES
> All data types, their size in bytes and the INT MIN and INT MAX range.

| Data Types | Qualifiers                        | Size (in byte) | Range                          |
| :--------- | :-------------------------------- | :------------- | :----------------------------- |
| `char`     | `char` or `signed char`		 | `1`            | `-128` to `127`                |
| `char`     | `unsigned char`			 | `1`            | `0` to `255`                   |
| `int`	     | `int` or `signed int`		 | `4`            | `-2147483648` to `2147483647`  |
| `int`	     | `unsigned int`			 | `4`            | `0` to `4294967295`            |
| `int`	     | `short int` or `short signed int` | `2`            | `-32768` to `32767`            |
| `int`	     | `unsigned short int`		 | `2`            | `0` to `65535`                 |
| `int`	     | `long int` or `signed long int`	 | `4`            | `-2147483648` to `2147483647`  |
| `int`	     | `unsigned long int`		 | `4`            | `0` to `4294967295`            |
| `float`    | `float`				 | `4`            | `1.1754e-38` to `3.4028e+38`   |
| `float`    | `double`				 | `8`            | `2.2250e-308` to `1.7976e+308` |
| `float`    | `long double`			 | `10`           | `3.4E-4932` to `3.4E+4932`     |

## COMMAND EXAMPLES
> Some example commands that can be tested on minishell or break it.

| Status  | Definition |
| :------ | :--------- |
| 🟢 | Working.                     |
| 🟡 | Didn't test yet.             |
| 🟣 | Leaks or segmentation fault. |
| ⚪ | Weird behaviour.             |
| 🔴 | Not working.                 |
| 🔵 | Not mandatory.               |

#### BLANK
> Exploring fundamental commands in Minishell, unravelling the core of shell interactions.

| Status  | Command |
| :------ | :------ |
| 🟢 | `<empty>`  |
| 🟢 | `<spaces>` |
| 🟢 | `../../`   | Diff error message
| 🟢 | `$`        | Diff error message	

#### SIGNALS
> Understanding system signals, showcasing the shell's adaptability in various scenarios.

| Status  | Command |
| :------ | :------ |
| 🟢 | `Ctrl` + `C`                                |
| 🟢 | `Ctrl` + `D`                                |
| 🟢 | `Ctrl` + `\`                                |
| 🟢 | `write something then press` + `Ctrl` + `C` |
| 🟢 | `write something then press` + `Ctrl` + `D` |
| 🟢 | `write something then press` + `Ctrl` + `\` |
| 🟢 | `cat` + `Ctrl` + `C`                        |
| 🟢 | `cat` + `Ctrl` + `D`                        |
| 🟢 | `cat` + `Ctrl` + `\`                        |
| 🟢 | `sleep 5` + `Ctrl` + `C`                    |
| 🟢 | `sleep 5` + `Ctrl` + `D`                    |
| 🟢 | `sleep 5` + `Ctrl` + `\`                    |
	
#### PATH
> Managing executable file access by manipulating the system path in Minishell.

| Status  | Command |
| :------ | :------ |
| 🟢 | `/bin/echo`        |
| 🟢 | `/bin/grep`        |
| 🟢 | `/bin/ls`          |
| 🟢 | `/bin/ls -la`      |
| 🟢 | `/bin/cat`         |
| 🟢 | `/bin/pwd`         |
| 🟢 | `/bin/cd`          | OK! Path not found in bash nor in our
| 🟢 | `/bin/export`      | OK! Path not found in bash nor in our
| 🟢 | `/bin/exit`        | OK! Path not found in bash nor in our
| 🟢 | `/bin/env`         | IMPORTANT!

#### PWD
> Locating the present directory through the pwd command in Minishell.

| Status  | Command |
| :------ | :------ |
| 🟢 | `pwd`         |
| 🟢 | `pwd a`       |
| 🟢 | `pwd a b c d` |

#### EXPORT, ENV AND UNSET
> Harnessing environment variables via export, env, and unset commands in Minishell.

| Status  | Command |
| :------ | :------ |
| 🟢 | `ENV`                        	|
| 🟢 | `eNv`                        	|
| 🟢 | `env`                        	|
| 🟢 | ` env`                       	|
| 🟢 | `env `                       	|
| 🟢 | `  env  `                    	|
| 🟢 | `UNSET`                      	|
| 🟢 | `uNsEt`                      	|
| 🟢 | `unset`                      	|
| 🟢 | ` unset`                     	|
| 🟢 | `unset `                     	|
| 🟢 | `  unset  `                  	|
| 🟢 | `unset [variable]`           	|
| 🟢 | `unset [variable] [variable]`	|
| 🟢 | `unset [all variables]`      	|
| 🟢 | `EXPORT`                     	|
| 🟢 | `eXpOrT`                     	|
| 🟢 | `export`                     	|
| 🟢 | ` export`                    	|
| 🟢 | `export `                    	|
| 🟢 | `  export  `                 	|
| 🟢 | `export a=42`                	|
| 🟢 | `export a = 42`              	|
| 🟢 | `export a=" 42 "`            	|
| 🟢 | `export a=' 42 '`            	|
| 🟢 | `export a` 		    	        |
| 🟢 | `export a=''`           	    	|                                         
| 🟢 | `export a='"'`               	|                                   
| 🟢 | `export a='\'`               	|                                
| 🟢 | `export a='$'`               	|                                 
| 🟢 | `export a='\t'`              	|                                    
| 🟢 | `export a='''` 		 	        | 
| 🟢 | `export =` 		             	| not a valid identifier
| 🟢 | `export ==`		            	| not a valid identifier
| 🟢 | `export a=` 		            	| its possbible
| 🟢 | `export a=42=` 		    		| its possbible - nesse caso como o = eh impresso eh preciso altera-lo (*-1)
| 🟢 | `export =a=42` 		  	 	 	| not a valid identifier
| 🟢 | `export a==42` 		  		  	| its possible - nesse caso como o = eh impresso eh preciso altera-lo (*-1)
| 🟢 | `export "a=42"` 		 		   	| its possbile - value nao esta ficando entre "" na lista export
| 🔴 | `export _=42` 		 		   	| O _=aaaaaaa n deve fazer nada. Fazer tratamento especial pra evitar aparecer na lista exp
| 🟢 | `export 42=42`		  		  	|
| 🟢 | `export a b = 42`	  		  	|
| 🟢 | `export a= b= 42`	    	    |
| 🟢 | `export a=42 % b=42 @ c=42`  	|
| 🟢 | `export A=a B=b C=c D=d E=e` 	|
| 🔵 | `export _=a; echo $_a` 		    |

#### EXIT
> Concluding Minishell's operations gracefully using the exit command.

| Status  | Command |
| :------ | :------ |
| 🟢 | `EXIT`                      |
| 🟢 | `eXiT`                      |
| 🟢 | `exit`                      |
| 🟢 | `exit `                     |
| 🟢 | ` exit`                     |
| 🟢 | `  exit  `                  |
| 🟢 | `exit test`                 | inverter a ordem das mensagens do stdout e err (verificar se o err ta no stderr)
| 🟢 | `exit "test"`               | inverter a ordem das mensagens do stdout e err (verificar se o err ta no stderr)
| 🟢 | `"exit test"`               |
| 🟢 | `"exit"`                    |
| 🟢 | `exit1`                     |
| 🟢 | `exita`                     |
| 🟢 | `exit exit`                 | inverter a ordem das mensagens do stdout e err (verificar se o err ta no stderr)
| 🟢 | `exit a`                    | inverter a ordem das mensagens do stdout e err (verificar se o err ta no stderr)
| 🟢 | `exit abc`                  | inverter a ordem das mensagens do stdout e err (verificar se o err ta no stderr)
| 🟢 | `exit a b c`                | inverter a ordem das mensagens do stdout e err (verificar se o err ta no stderr) && ajustar mensagem de erro
| 🟢 | `exit a b c d`              | inverter a ordem das mensagens do stdout e err (verificar se o err ta no stderr) && ajustar mensagem de erro
| 🔵 | `exit #`                    | pensar sobre o parsing do # (not mandatory??)
| 🔵 | `exit *`                    | wildcard not mandatory?
| 🟢 | `exit 0`                    |
| 🟢 | `exit 1`                    |
| 🟢 | `exit 123`                  |
| 🟢 | `exit 1234`                 |
| 🟢 | `exit 1 2 3 4`              | inverter a ordem das mensagens do stdout e err (verificar se o err ta no stderr)
| 🟢 | `exit +`                    | inverter a ordem das mensagens do stdout e err (verificar se o err ta no stderr) && incluir mensagem de erro
| 🟢 | `exit -`                    | inverter a ordem das mensagens do stdout e err (verificar se o err ta no stderr) && incluir mensagem de erro
| 🟢 | `exit +10`                  |
| 🟢 | `exit -10`                  |
| 🟢 | `exit +2000`                |
| 🟢 | `exit -2000`                |
| 🟢 | `exit +-2000`               | inverter a ordem das mensagens do stdout e err (verificar se o err ta no stderr)
| 🟢 | `exit -+2000`               | inverter a ordem das mensagens do stdout e err (verificar se o err ta no stderr)
| 🟢 | `exit ++2000`               | inverter a ordem das mensagens do stdout e err (verificar se o err ta no stderr)
| 🟢 | `exit --2000`               | inverter a ordem das mensagens do stdout e err (verificar se o err ta no stderr)
| 🟢 | `exit -2147483649`          |
| 🟢 | `exit 2147483648`           |
| 🟢 | `exit 00000000000000000000` |
| 🟢 | `exit 11111111111111111111` | inverter a ordem das mensagens do stdout e err (verificar se o err ta no stderr)
| 🟢 | `exit'42'`                  |
| 🟢 | `exit '\t42'`               | inverter a ordem das mensagens do stdout e err (verificar se o err ta no stderr)
| 🟢 | `exit '\t\f\r 42'`          | inverter a ordem das mensagens do stdout e err (verificar se o err ta no stderr)
| 🟢 | `exit '42 '`                |
| 🟢 | `exit '42\t'`               | inverter a ordem das mensagens do stdout e err (verificar se o err ta no stderr)
| 🟢 | `exit '42\r'`               | inverter a ordem das mensagens do stdout e err (verificar se o err ta no stderr)
| 🟢 | `exit '42\t\f\r '`          | inverter a ordem das mensagens do stdout e err (verificar se o err ta no stderr)
| 🟢 | `exit '42     a'`           | inverter a ordem das mensagens do stdout e err (verificar se o err ta no stderr)
| 🟢 | `exit '42\t\t\ta'`          | inverter a ordem das mensagens do stdout e err (verificar se o err ta no stderr)

#### CD
> Traversing directories seamlessly using the cd command in Minishell.

| Status  | Command |
| :------ | :------ |
| 🟢| `CD`                     |
| 🟢 | `cd`                    |
| 🟢 | `cd `                   |
| 🟢 | ` cd`                   |
| 🟢 | `  cd  `                |
| 🟢 | `cd .`                  |
| 🟢 | `cd ~`                  |
| 🟢 | `cd no_file`            |
| 🟢 | `cd1`                   |
| 🟢 | `cd 0`                  |
| 🟢 | `cd 1`                  |
| 🟢 | `cd 123`                |
| 🟢 | `cd 1 2 3 4`            |
| 🟢 | `cd cd`                 |
| 🟢 | `cd a`                  |
| 🟢 | `cd abc`                |
| 🟢 | `cd a b c`              |
| 🟢 | `cd ../../`             |
| 🟢 | `cd ../../../../../../` |
| 🟢 | `cd ../../...`          |
| 🟢 | `cd .../../..`          |
| 🟢 | `cd .../../...`         |
| 🟢 | `cd \`                  |
| 🟢 | `cd /`                  |
| 🟢 | `cd //`                 | OK! TESTAR NO BASH DA ESCOLA>
| 🟢 | `cd ///`                |
| 🟢 | `cd -`                  |
| 🟢 | `cd $[VAR]`             |

#### ECHO
> Rendering text and variables in the terminal with the versatile echo command in Minishell.

| Status  | Command |
| :------ | :------ |
| 🟢 | `ECHO`                                                               |
| 🟢 | `echO`                                                               |
| 🟢 | `ECHo`                                                               |
| 🟢 | `echo`                                                               |
| 🟢 | `echo echo`                                                          |
| 🟢 | `echo `                                                              |
| 🟢 | ` echo`                                                              |
| 🟢 | `  echo  `                                                           |
| 🟢 | `echo .`                                                             |
| 🟢 | `echo ~`                                                             |
| 🟢 | `echo echo ~`                                                        |
| 🟢 | `"echo test"`                                                        |
| 🟢 | `echo "~"`                                                           |
| 🟢 | `echo '~'`                                                           |
| 🟢 | `echo ~123`                                                          |
| 🟢 | `echo 123~`                                                          |
| 🟢 | `echo ~/123`                                                         |
| 🟢 | `echo ~/123/456`                                                     |
| 🟢 | `echo #`                                                             |
| 🟢 | `echofile`                                                           |
| 🟢 | `echo file`                                                          |
| 🟢 | `echo no_file`                                                       |
| 🟢 | `echo file test`                                                     |
| 🟢 | `echo file   test`                                                   |
| 🟢 | `echo file     test file   test`                                     |
| 🟢 | `echo a"b"c`                                                         |
| 🟢 | `echo "a'b'c`                                                        |
| 🟢 | `echo "test"`                                                        |
| 🟢 | `echo test`                                                          |
| 🟢 | `echo 'test'`                                                        |
| 🟢 | `echo -n`                                                            |
| 🟢 | `echo -n -n -n -n`                                                   |
| 🟢 | `echo -nnnnnnnnnnnnnnnnnnnnnnnn`                                     |
| 🟢 | `echo -n test -n`                                                    |
| 🟢 | `"echo" "-n"`                                                        |
| 🟢 | `echo -n test`                                                       |
| 🟢 | `echo -nn test`                                                      |
| 🟢 | `echo -n -n -n test`                                                 |
| 🟢 | `echo "-n" test`                                                     |
| 🟢 | `echo -n"-n" test`                                                   |
| 🟢 | `echo "-nnnn" test`                                                  |
| 🟢 | `echo "-n -n -n"-n test`                                             |
| 🟢 | `echo "-n '-n'" test `                                               |
| 🟢 | `echo -n file test`                                                  |
| 🟢 | `echo -n -n -n file test`                                            |
| 🟢 | `echo $USER`                                                         |
| 🟢 | `echo "$USER"`                                                       |
| 🟢 | `echo "'$USER'"`                                                     | erro aspas simples dentro de duplas
| 🟢 | `echo " '$USER' "`                                                   | erro aspas simples dentro de duplas
| 🟢 | `echo text"$USER"`                                                   |
| 🟢 | `echo text"'$USER'" ' $USER '`                                       | erro aspas simples dentro de duplas
| 🟢 | `echo "text"   "$USER"    "$USER"`                                   |
| 🟢 | `echo '              $USER          '`                               |
| 🟢 | `echo               text "$USER"            "$USER"text`             |
| 🟢 | `echo ''''''''''$USER''''''''''`                                     |
| 🟢 | `echo """"""""$USER""""""""`                                         |
| 🟢 | `echo $USER'$USER'text oui oui     oui  oui $USER oui      $USER ''` |
| 🟢 | `echo $USER '' $USER $USER '' $USER '' $USER -n $USER`               | bug printando apenas 1 vez
| 🟢 | `echo ' \' ' \'`                                                     |
| 🔵 | `echo '\" ' " \"\""`                                                 |
| 🔵 | `echo \\\" \\\" \\\" \\\"\\\"\\\" \\\'\\\'\\\'`                      |
| 🟢 | `echo "$USER""$USER""$USER"`                                         |
| 🟢 | `echo text"$USER"test`                                               |
| 🟢 | `echo '$USER' "$USER" "text \' text"`                                |
| 🟢 | `echo '$USER'`                                                       |
| 🟢 | `echo $USER " "`                                                     |
| 🟢 | `echo "$USER""Users/$USER/file""'$USER'"'$USER'`                     |
| 🟢 | `echo "$USER$USER$USER"`                                             |
| 🟢 | `echo '$USER'"$USER"'$USER'`                                         |
| 🟢 | `echo '"$USER"''$USER'"""$USER"`                                     |
| 🟢 | `echo " $USER  "'$PWD'`                                              |
| 🟢 | `echo " $USER  \$ "'$PWD'`                                           |
| 🟢 | `echo $USER=4`                                                       |
| 🟢 | `echo $USER=thallard`                                                |
| 🟢 | `echo $USER`                                                         |
| 🟢 | `echo $?`                                                            |
| 🟢 | `echo $USER213`                                                      |
| 🟢 | `echo $USER$12USER$USER=4$USER12`                                    |
| 🟢 | `echo $USER $123456789USER $USER123456789`                           |
| 🟢 | `echo $USER $9999USER $8888USER $7777USER`                           |
| 🟢 | `echo $USER $USER9999 $USER8888 $USER7777`                           |
| 🟢 | `echo $USER $USER9999 $USER8888 $USER7777 "$USER"`                   |
| 🟢 | `echo "$USER=12$USER"`                                               |
| 🟢 | `echo "$9USER" "'$USER=12$SOMETHING'"`                               |
| 🟢 | `echo $PWD/file`                                                     |
| 🟢 | `echo "$PWD/file`                                                    | error unmatched quotes
| 🟢 | `echo "text" "text$USER" ... "$USER`                                 |
| 🟢 | `echo $PW`                                                           |
| 🟢 | `echo "'"'ola'"'"`                                                   |
| 🟢 | `echo "'"' ola '"'"`                                                 |

#### PIPES AND REDIRECTS

Redirecionamento Simples de Entrada e Saída:  
| 🟢 | cat < input.txt > output.txt  
| 🟢 | grep 'palavra' < arquivo.txt > resultados.txt  
  
Uso de Pipe Simples:  
| 🟢 | ls | wc -l  
| 🟢 | cat arquivo.txt | grep 'palavra'  
  
Combinação de Pipes:  
| 🟢 | seq 100 | grep "1" | sort -r | uniq | wc -l
| 🟢 | cat arquivo.txt | grep 'palavra' | sort | uniq  
| 🟢 | ls -l | grep '^d' | wc -l  
  
Pipes com Redirecionamento de Entrada:  
| 🟢 | grep 'palavra' < arquivo.txt | sort > resultados_ordenados.txt  
| 🟢 | cat input.txt | wc -l > line_count.txt  
| 🟢 | cat < input.txt | wc -l > line_count.txt  
| 🟢 | grep "bb" < tfile.txt | wc -l

Pipes com Redirecionamento de Saída:  
| 🟢 | ls -l | grep '^d' > diretorios.txt  
| 🟢 | cat arquivo.txt | head -n 5 > primeiras_linhas.txt  
  
Redirecionamento de Erro:  
|    | grep 'palavra' arquivo_inexistente.txt 2> erro.txt  
|    | cat arquivo.txt 2> /dev/null  
  
## NORMINETTE
> At 42 School, it is expected that almost every project is written following the Norm, which is the coding standard of the school.

```
- No for, do...while, switch, case, goto, ternary operators, or variable-length arrays allowed;
- Each function must be a maximum of 25 lines, not counting the function's curly brackets;
- Each line must be at most 80 columns wide, with comments included;
- A function can take 4 named parameters maximum;
- No assigns and declarations in the same line (unless static);
- You can't declare more than 5 variables per function;
- ...
```

* [42 Norms](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf) - Information about 42 code norms. `PDF`
* [Norminette](https://github.com/42School/norminette) - Tool to respect the code norm, made by 42. `GitHub`
* [42 Header](https://github.com/42Paris/42header) - 42 header for Vim. `GitHub`

## LICENSE
<p>
This work is published under the terms of <a href="https://github.com/jotavare/minishell/blob/main/LICENSE">Unlicense</a>.
</p>


USUAL LIST TO TEST:
SHELL WSL2_GUI_APPS_ENABLED WSL_DISTRO_NAME NAME PWD LOGNAME HOME LANG WSL_INTEROP LS_COLORS WAYLAND_DISPLAY LESSCLOSE TERM LESSOPEN USER DISPLAY SHLVL XDG_RUNTIME_DIR WSLENV XDG_DATA_DIRS
PATH DBUS_SESSION_BUS_ADDRESS HOSTTYPE PULSE_SERVER OLDPWD _