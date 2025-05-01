Issuing a zero velocity command after entering a nonzero velocity command will still cause the Xarm7 to move.  

To reproduce, compile main.cpp, linking against the Xarm C++ API. Then run the program, which will wait for user input.  

Press enter once to input a small nonzero velocity command. The Xarm7 should move slightly, as expected.  
Then press it again to input a zero velocity command. The Xarm7 will move slightly, which is undesired.  
