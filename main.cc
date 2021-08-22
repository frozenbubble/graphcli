#include <fstream>
#include <iostream>
#include <set>

#include "graph.hh"
#include "graphbuilder.hh"

void printHelp()
{
    std::cout << "Usage: graphcli <options|filename>" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "-h\tprint this help message" << std::endl;
    std::cout << "-i\tbuild dependency graph interactively" << std::endl;
}

void printParallelBatches(Graph& g)
{
    std::cout << std::endl << "Batches: " << std::endl;
    int batchNumber = 1;
    auto batches = g.getParallelBatches();
    for (auto&& batch : batches)
    {
        std::cout << "Batch " << batchNumber << ": ";
        for (int node : batch)
        {
            std::cout << node << " ";
        }
        std::cout << std::endl;
        
        batchNumber++;
    }
}

int main(int argc, char* argv[])
{
    std::set<std::string> allowedArgs {""};

    try
    {
        if (argc != 2)
        {
            printHelp();
            return 1;
        }

        std::string arg(argv[1]);
        if (arg.compare("-h") == 0)
        {
            printHelp();
            return 0;
        }
        if (arg.compare("-i") == 0)
        {
            std::cout << "Starting interactive session" << std::endl;
            CommandLineGraphBuilder builder;
            Graph* g = builder.build();
            printParallelBatches(*g);

            delete g;
        }
        else
        {
            std::ifstream f(arg);
            if (!f.good())
            {
                std::cout << arg << ": Could not open file. Use 'graphcli -h' for help" << std::endl;
                return 1;
            }

            FileGraphBuilder builder(arg);
            Graph* g = builder.build();
            printParallelBatches(*g);

            delete g;

        }        
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << "Invalid input. See readme for examples." << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}