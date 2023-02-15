//usr/bin/env echo "(write 1)(newline)" | /usr/bin/env guix repl -- /dev/stdin ; exit;

;; Check at `configure` time weather the C compiler is new enough to understand "//" comments. If so, this is a shell script. If not, put the line lower down in the code.

;; making it `chmod +x` without a shebang

/*-
 * iconv.h
 *
 * ... lorem ipsum ...
 *
 */
"
 generate-code-here
 "/*\n"
"--8<---------------cut here---------------start------------->8---\n"
this-file-goes-here
"--8<---------------cut here---------------end--------------->8---\n"
" */\n"
 
