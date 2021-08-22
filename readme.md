# graphcli

graphcli is a command-line tool to build dependency graphs and check what tasks can be run parallelly.

## Build

In the source directory you can run

    cmake -S . -B build
    cmake --build build

Or alternatively if you are on linux, you can simply run

    ./cleanbuild.sh

Binaries will be under 'build'.

## Run

To run graphcli you can do 

    graphcli <options|filename>

where options can be:

    -h  print the help message
    -i  build dependency graph interactively

Whether you choose interactive session or an input file the input should be structured as follows
* first line is the number of nodes in your graph
* following lines should describe the directed edges between the nodes in 'X,Y' format which means X's output is required by Y. Nodes are identified by their number, indexed from zero, that is if the first line was 3, you can work with nodes 0, 1 and 2.
* in interactive mode an empty line terminates the sequence. You don't need an empty line at the end in case you use an input file. 

For example

    /build/graphcli -i
    Starting interactive session
    Number of nodes: 3
    Add edges to the graph in X,Y format one by one where X,Y represents an X-->Y edge 
    meaning X's output is required by Y. Hit enter when done
    0,1
    1,2
    2,0

See *example.txt* for file input example.

Once you finished constructing your dependency graph graphcli will run a check to see if the input graph contains any circular dependencies. If it does, you'll see 

    Graph contains circular dependency.    

If not it will output the batches of nodes that can be run in parallel.

    Batches: 
    Batch 1: 0 1 2 
    Batch 2: 3 9 
    Batch 3: 4 5 
    Batch 4: 6 
    Batch 5: 7 8 