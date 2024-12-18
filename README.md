<div align="center">
  <h1><strong>Matrix Calculator</strong></h1>
  <img src = "https://github.com/realhongloan/matrix-calculator/blob/01b66425446652613f58634b6459eb41fd0652e4/img/Screenshot%20From%202024-12-17%2023-15-02.png">
  <img src = "https://github.com/realhongloan/matrix-calculator/blob/fce0681d63a58305e45f863b0c19b03ab6a107be/img/Screenshot%20From%202024-12-17%2023-10-45.png">
  <img src = "https://github.com/realhongloan/matrix-calculator/blob/2d877849769ab566fa558dd34ddae8aa1a48c329/img/Screenshot%20From%202024-12-17%2023-59-42.png">
  
  _<br/><br/>The matrix-calculator is a compact, convenient application designed to handle basic matrix operations property. The program is written based on Qt development framework for graphical user interfaces which allows for non-technical users to interact with the software 
  easily without having to deal with the hassle of command lines.<br/><br/>_

</div>



## Setting Up
### Bash Compilation:
To compile and run the program, follow these steps:
   1. Download all the necessary files for compilation.
      ```
      $ git clone https://github.com/realhongloan/matrix-calculator.git
      ```
   2. Change your directory to the source code file.
      ```
      $ cd matrix-calculator
      $ cd src
      ```
   3. Make sure you've already install all the necessary programs for the compilation.
      ```
      $ sudo apt update
      $ sudo apt install qt5-default qtcreator qmake build-essential
      ```
   4. Compile the codes.
      ```
      $ qmake project.pro
      $ make
      ```
   5. Run the executable file.
      ```
      $ ./project
      ```

<img src = https://github.com/realhongloan/matrix-calculator/blob/d122459246972b410084a2db49be2c445bd0f244/img/Screencast%20From%202024-12-17%2023-27-02.gif align = "center">

### Qt Creator Compilation:
  1. Create a new project.
  2. Choose file "project.pro" then the IDE will set everything up for you.
  3. Build all projects.
  4. Then run the executable file.

