# sublime_javac_src
sublime text java build compiler
optimation class and package


# project structur

    |- ProjectRoot
    |______|- bin
    |______|- dist
    |______|- src


# penggunaan
- buat file build system dan tambahkan di sublimeText package directory
- edit cmd path in build system dan arahkan dimana file javac_src.exe disimmpan
  
        "cmd": ["D:\\JC\\Dev\\Eclipse\\__javarun\\javac_src"],
	      "working_dir": "${file_path}",

- buat folder root project in sublimeText seperti project structur diatas
- set build system menggunakan javac_run pada menu tools 
- dari diroctoy root CTRL+B or CTRL+SHIFT+B -> optional [compile] | [export jar] 


# Main file
- default MainActivity adalah Main.java | ex: com.test.Main
- atau kamu dapat merubahnya pada <b>setting.jc</b> file

# rekomendasi
- install package javaIME via package controll untuk autocomplate
- enjoy code
