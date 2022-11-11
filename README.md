## OSTIS-geography
OSTIS-geography is an open-source knowledge base for geographical system for Open Semantic Technology for Intelligent Systems. System includes OpenStreetMap support to display geographical objects. 
## Install

Clone the project
```sh
git clone -c core.longpaths=true -c core.autocrlf=true https://github.com/ostis-apps/ostis-geography
cd ostis-geography
git submodule update --init --recursive
```

### Using Ubuntu 22.04 or 20.04
Linux:
```sh
cd scripts
./install_project.sh
```

## Build knowledge base
If you are using the Docker version, just put your scs files in the "kb" folder and restart.

For Linux:
```sh
cd scripts
./build_kb.sh
```

## Run
### Option 1. Run servers

Run in Docker:
```sh
docker-compose up
```

Run on Linux:
```sh
#Terminal 1
cd scripts
./run_sc_server.sh
#Terminal 2
cd scripts
./run_py_sc_server.sh
#Terminal 3
cd scripts
./run_sc_web.sh
```

Then open localhost:8000 in your browser.
![](https://i.imgur.com/6SehI5s.png)

You can open localhost:8090 in your browser as well to see the new web interface version.

## Pull requests
1. Add understandable title to the Pull Request which covers all changes in this Pull Request;
2. Also, you can write this information inside Pull request;
3. Don't forget about newline at the end of the file;
4. Not necessary, but we will appreciate if you clean your commit history.

## Project Structure

### kb
The place for the knowledge base of your app. Put your **.scs** files here.

### problem-solver
The place for the problem solver of your app. Put your agents here.

#### Agents on C++
Some tips:
- Store your modules with C++ agents in *problem-solver/cxx*;
- After updating your C++ code you need to rebuild problem-solver. Just run:
```
cd scripts
./build_problem_solver.sh
```
For a full rebuild with the deleting of the *bin* and *build* folders run:
```
cd scripts
./build_problem_solver.sh -f
```
and run:
```
cd scripts
./run_sc_server.sh
```

#### Agents on Python
Some tips:
- Store your modules with Python agents in *problem-solver/py*;
- You can see example modules using Python [here](problem-solver/py/modules).
- After updating your C++ code you need to rebuild problem-solver. Just run:
```
cd scripts
./run_py_sc_server.sh
```
