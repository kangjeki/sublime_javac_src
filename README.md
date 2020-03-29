# sublime_javac_src
sublime text java build compiler
optimation class and package


# project structur

    |- ProjectRoot
    |______|- bin
    |______|- dist
    |______|- src


# usage
- add file build system in sublimeText package directory
- edit cmd path in build system to spesific path where you saved javac_src.exe
  
        "cmd": ["D:\\JC\\Dev\\Eclipse\\__javarun\\javac_src"],
	      "working_dir": "${file_path}",

- create folder root project in sublimeText
- create child folder src -> 'default sources directory'
- set build using javac_run
- press CTRL+B or CTRL+SHIFT+B -> optional [compile] | [export jar] 


# Main
- default MainActivity is Main.java | ex: com.test.Main
- or you can set costum MainActivity in <b>setting.jc</b> file

# recomended
- install package javaIME via package controll to autocomplate
- enjoy code
