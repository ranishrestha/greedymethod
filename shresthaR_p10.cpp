#include<iostream>
#include <fstream>
using namespace std;

class graphColoring
{
    public:
    int numNodes;
    int ** AdjMatrix;
    int * ColorList;
    int* usedColorList;
   // int newColor;
    void initialize(int n)
    {
        ColorList = new int [n+1];
        AdjMatrix = new int* [n+1];
        for(int i = 0; i < n+1; i++)
        {
           AdjMatrix[i] = new int[n+1];
           ColorList [i] = 0;
            for(int j = 0; j < n+1; j++)
            { 
                AdjMatrix[i][j]=0;
            }
        } 
    }
    void loadAdjMatrix(ifstream& inFile)
    {
        int i, j;
        while(inFile >> i >> j)
        {
            AdjMatrix[i][j] = 1;
            AdjMatrix[j][i] = 1;

        }
    }
     bool isOk(int nc, int node)
    {
        int adjNode;
        for(int j = 1; j < numNodes+1; j++)
        {
            if (AdjMatrix[node][j] == 1)
            {
                adjNode = j;
                if(ColorList[j] == nc)
                {
                return false;
                }
            }
        }
        return true;

    }
    bool allcolored()
    {
        for(int i = 1; i < numNodes+1; i++)
        {
            if (ColorList[i] == 0 )
            return false;
        }
        return true;

    }
    void loadColorlist()
    {
        int newColor = 1;
        while(!allcolored())
        {
            for(int i = 1; i < numNodes+1; i++)
            {
            if (ColorList[i] == 0)
            {
                int node = i;
                if(isOk(newColor, node))
                {
                    ColorList[i] = newColor;
                }
            }
            }
        newColor++;
        }
    }
    void printcolors(ofstream &outfile, int method)
    {
        outfile << "using method " << method << endl;
        outfile << numNodes <<endl;
        for (int i = 1; i < numNodes+1; i++)
        {
            outfile <<  i <<" "<< ColorList[i] <<endl;
        }

    }
    void printDS (ofstream &outfile, int method)
    {
        outfile <<"print for method " << method <<endl;
        for(int i = 1; i < numNodes+1 ;i++)
        {
            outfile <<  "node: " <<i <<" color: " << ColorList[i]<<" adjacent nodes: ";
            for(int j = 0; j < numNodes+1; j++)
            {
                if(AdjMatrix [i][j] == 1)
                outfile <<j <<" ";
                
            }
            outfile << endl;

        }

        outfile << "tableview:" << endl;
        for(int i = 1; i < numNodes+1 ;i++)
        {
            for(int j = 0; j < numNodes+1; j++)
            {
                outfile << AdjMatrix[i][j] <<" ";     
            }
            outfile << endl;
        }

    }
    void Method1(ifstream &inFile,ofstream & outfile)
    {
        inFile >> numNodes;
        initialize(numNodes);
        loadAdjMatrix(inFile);
        for (int i = 0; i < numNodes+1; i++)
        {
            for(int j = 0; j < numNodes+1; j++)
            {
            cout << AdjMatrix[i][j];
            }
        cout <<endl; 
       }
       loadColorlist();
       printcolors(outfile, 1);
        
    }
    void Method2(ifstream & infile, ofstream &outfile)
    {
        infile >> numNodes;
        initialize(numNodes);
        loadAdjMatrix(infile);
        usedColorList = new int[numNodes];
        for(int i = 0; i <numNodes+1; i++)
        {
            usedColorList[i] = 0;
        }
        int newcolor = 1;
        int usedColorSize = 0;
        int i = 1;
        while(!allcolored())
        {
           // for(int i = 1; i < numNodes+1; i++)
           // {
               
                if (ColorList[i] == 0)
                {
                    int node = i;
                    int count = 1;
                    
                    int usedColor = usedColorList[count];
                    while (!isOk(usedColor, node) && usedColor != 0)
                    {
                       usedColor = usedColorList[count+1];
                       count = count+1;
                       
                    }
                    if(isOk(usedColor, node) && usedColor!= 0)
                    {
                        ColorList[i] = usedColor;
                    }
                    else
                    {
                        ColorList[i] = newcolor;
                        usedColorList[usedColorSize+1] = newcolor;
                        usedColorSize++;
                        newcolor++;

                    }

                }
                i++;

        

        }
        printcolors(outfile, 2);
    }
};
int main(int argc, char** argv)
{
    ifstream infile;
    infile.open(argv[1]);
    ofstream outfile1, outfile2;
    outfile1.open(argv[3]);
    outfile2.open(argv[4]);
    int whichmethod = atoi(argv[2]);
    graphColoring myGraph; 
    if (whichmethod == 1)
    {
        myGraph.Method1(infile, outfile1);
        myGraph.printDS(outfile2, 1);
    }
    else if (whichmethod == 2)
    {
        myGraph.Method2(infile, outfile1);
        myGraph.printDS(outfile2, 2);
    }
    else
    {
        cout <<"no such method";
    }
    infile.close();
    outfile1.close();
    outfile2.close();

}