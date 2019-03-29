1. On Ubuntu, you can use the following commands to install unzip:         
        sudo apt-get install unzip
   To unzip files, use:
        unzip ./FIleName.zip

2. Make a word list:
```sh
grep "^[A-Za-z]*$" /usr/share/dict/words > dict.txt
```
/usr/share/dict/words can be replaced by other text files if they contain words and there is only one word each line





Steps
1. Downloads zip file
2. Unzip files.
3. Make word file.
4. Type "make"
5. Type "valgrind -q ./main" to start game



Game rules:
1. The minimum number of letters in the word you discover should be 4 letters
2. You can enter only the letter adjacent to the last selected letter.
3. The time is set to 3 minutes.
4. For each correct word you discover, you earn "1 point for a four letter text", "2 points for a five letter text".




