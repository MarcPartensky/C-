import os



#name=str(input("Enter program name: "))


#path=os.path.abspath(name)
#print(path)

name="game_of_life_v2.cpp"
directory=os.getcwd()
os.chdir(directory)
os.system("cd "+directory)
os.system("sudo g++ "+name)
os.system("./a.out")
