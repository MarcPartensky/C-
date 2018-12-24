import os
#import subprocess

#pid = subprocess.Popen(args=["gnome-terminal", "--command=python 'test.py'"]).pid
#print pid

#os.system("gnome-terminal -x python test.py")

#os.system("gnome-terminal  'sudo apt-get update'")


#name=str(input("Enter program name: "))


#path=os.path.abspath(name)
#print(path)

name="game_of_life_v2.cpp"
directory=os.getcwd()
os.chdir(directory)
os.system("cd "+directory)
os.system("g++ "+name)
#os.system("make "+name)
os.system("./a.out")
#os.system("./"+name)
