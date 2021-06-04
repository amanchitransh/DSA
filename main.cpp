#include <iostream>
#include<list>
using namespace std;
#define MAX INT_MAX

class AdjListNode
{
public:
    int dest;
    int weight;
    AdjListNode *next;
};

class CpeListNode
{
public:
    string name;
    CpeListNode *next;
};
class CpeList
{
public:
    CpeListNode *head;
    CpeList() {}
    CpeList(const CpeList &p1)
    {
        head = new CpeListNode();
        CpeListNode *pcrawl = p1.head;
        while (pcrawl)
        {
            head = pcrawl;
            pcrawl->next;
        }
    }
};
// A structure to represent an adjacency list
class AdjList
{
public:
    AdjListNode *head;
    AdjList() {}
    AdjList(const AdjList &p1)
    {
        head = new AdjListNode();
        AdjListNode *pcrawl = p1.head;
        while (pcrawl)
        {
            head = pcrawl;
            pcrawl->next;
        }
    }
};

// Reference List for Adjacency List
class ReferenceList
{
public:
    string vertices;
    int cost = MAX;
    AdjList adjList;
    CpeList cpelist;
    ReferenceList() {}
    ReferenceList(const ReferenceList &p1)
    {
        vertices = p1.vertices;
        cost = p1.cost;
        adjList = p1.adjList;
        cpelist = p1.cpelist;
    }
};

class Graph
{
public:
    int V;
    ReferenceList *referenceList;
    Graph() {}
    Graph(const Graph &p1)
    {
        V = p1.V;
        referenceList = new ReferenceList[V];
        for (int i = 0; i < V; ++i)
        {
            referenceList = p1.referenceList;
        }
    }
};

// A utility function that creates a graph of V vertices
class Graph createGraph(int V)
{
    Graph graph;
    graph.V = V;

    // Create an array of reference lists. Size of
    // array will be V
    graph.referenceList = new ReferenceList[V];
    // Initialize each reference list as empty by
    // making head as NULL
    int i;
    for (i = 0; i < V; ++i)
    {
        graph.referenceList[i].adjList.head = NULL;
        graph.referenceList[i].cpelist.head = NULL;
    }

    return graph;
}
// A utility function to create a new adjacency list node
class AdjListNode *newAdjListNode(int dest, int weight)
{
    AdjListNode *newNode = new AdjListNode();
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
//A utility function to create a new CPE
class CpeListNode *newCpeList(string name)
{
    CpeListNode *newCpe = new CpeListNode();
    newCpe->name = name;
    newCpe->next = NULL;
    return newCpe;
}
void applyBellman(Graph graph)
{
    int i = 0, j = 0;
    for (i = 0; i < graph.V - 1; i++)
    {
        for (j = 0; j < graph.V; j++)
        {
            AdjListNode *pCrawl = graph.referenceList[j].adjList.head;
            while (pCrawl)
            {
                if ((graph.referenceList[j].cost + pCrawl->weight) < graph.referenceList[pCrawl->dest].cost)
                {
                    graph.referenceList[pCrawl->dest].cost = graph.referenceList[j].cost + pCrawl->weight;
                }
                pCrawl = pCrawl->next;
            }
        }
    }
}

int findIndex(Graph graph, string name)
{
    for (int i = 0; i < sizeof(graph.referenceList); i++)
    {
        if (!name.compare(graph.referenceList[i].vertices))
        {
            return i;
        }
    }
    return 0;
}

void addCpe(Graph graph, string src, string newCpe)
{
    int srcPos = -1;
    int i, V = graph.V;
    for (i = 0; i < V; i++)
    {
        if (graph.referenceList[i].vertices == src)
        {
            srcPos = i;
        }
    }
    if (srcPos == -1)
    {
        cout << "Source router not found";
    }
    else
    {
        CpeListNode *newNode = newCpeList(newCpe);
        if (graph.referenceList[srcPos].cpelist.head == NULL)
        {
            graph.referenceList[srcPos].cpelist.head = newNode;
        }
        else
        {
            newNode->next = graph.referenceList[srcPos].cpelist.head;
            graph.referenceList[srcPos].cpelist.head = newNode;
            cout << "cpe"
                 << " " << newCpe << " "
                 << "Added to router"
                 << " " << src;
        }
    }
}

void addLink(Graph graph, string src, string dest, int weight)
{
    int srcPos = -1, destPos = -1;
    int i, V = graph.V;
    for (i = 0; i < V; i++)
    {
        if (graph.referenceList[i].vertices == src)
        {
            srcPos = i;
        }
        if (graph.referenceList[i].vertices == dest)
        {
            destPos = i;
        }
    }
    if ((srcPos == -1) || (destPos == -1))
    {
        cout << "Destination or Source not found\n";
    }
    else
    {
        // Add an edge from src to dest. A new node is
        // added to the adjacency list of src. The node
        // is added at the beginning
        AdjListNode *newNode = newAdjListNode(destPos, weight);
        newNode->next = graph.referenceList[srcPos].adjList.head;
        graph.referenceList[srcPos].adjList.head = newNode;
        // Since graph is undirected, add an edge from
        // dest to src also
        // newNode = newAdjListNode(src,weight);
        // newNode->next = graph->array[dest].head;
        // graph->array[dest].head = newNode;
        cout << "\n\n Link added between Source Router"
             << " " << src << " "
             << "and"
             << " Destination Router"
             << " " << dest << " Successfully"
             << " with edge Weight/Cost"
             << " " << weight << " "
             << "!!\n\n";
    }
}

// A utility function to print the adjacency list
// representation of graph
void printGraph(Graph graph)
{
    cout << "\n\nNetwork Topology Representation in Adjacency List : \n\n";
    int v;
    for (v = 0; v < graph.V; ++v)
    {
        AdjListNode *pCrawl = graph.referenceList[v].adjList.head;
        if (graph.referenceList[v].cost == MAX)
            cout << "\n"
                 << "Adjacency list of vertex"
                 << " " << graph.referenceList[v].vertices << " with cost Infinity"
                 << "\n"
                 << "head";
        else
            cout << "\n"
                 << "Adjacency list of vertex"
                 << " " << graph.referenceList[v].vertices << " with cost " << graph.referenceList[v].cost << "\n"
                 << "head";
        while (pCrawl)
        {
            cout << "->" << graph.referenceList[pCrawl->dest].vertices << "(" << pCrawl->weight << ")";
            pCrawl = pCrawl->next;
        }
        cout << "\n";
    }
}
void printCPEs(Graph graph, string router_name)
{
    int srcPos = -1;
    int i, V = graph.V;
    for (i = 0; i < V; i++)
    {
        if (graph.referenceList[i].vertices == router_name)
        {
            srcPos = i;
        }
    }
    if (srcPos == -1)
    {
        cout << "Source router not found";
    }
    else
    {
        CpeListNode *pCrawl = graph.referenceList[srcPos].cpelist.head;
        cout << graph.referenceList[srcPos].vertices << " : ";
        while (pCrawl)
        {
            cout << "->" << pCrawl->name;
            pCrawl = pCrawl->next;
        }
    }
}
void deleteCPEs(Graph graph, string router_name)
{
    int srcPos = -1;
    string cpe;
    int i, V = graph.V;
    for (i = 0; i < V; i++)
    {
        if (graph.referenceList[i].vertices == router_name)
        {
            srcPos = i;
        }
    }
    if (srcPos == -1)
    {
        cout << "Source router not found";
    }
    else
    {
        cout << " Enter CPE you want to delete:\t ";
        cin >> cpe;
        if (graph.referenceList[srcPos].cpelist.head->name == cpe)
        {
            graph.referenceList[srcPos].cpelist.head = graph.referenceList[srcPos].cpelist.head->next;
            cout<<" CPE "<<cpe<<" deleted";
        }
        else
        {
                    CpeListNode *p = graph.referenceList[srcPos].cpelist.head;
        CpeListNode *q = graph.referenceList[srcPos].cpelist.head->next;
        while (q->name != cpe && q->next != NULL)
        {
            p = p->next;
            q = q->next;
        }
        if (q->name == cpe)
        {
            p->next = q->next;
            cout<<" CPE "<<cpe<<" deleted";
        }
        }

    }
}

// Weighted directed Graph Implementation in C++
int main(void)
{
    int choice, V;
    string source, destination, router_name, cpe_name;
    Graph graph;
    while (1)
    {
        //Main Menu
        cout << "\n\n";
        cout << "<---------------------------------------[Design a Network Topology With Routers & CPEs]-------------------------------------->\n\n";
        cout << "1. Press 1 to input the Details required regarding Routers and CPEs that are needed to be Connected with respective Router to design the Topology\n";
        cout << "2. Press 2 to Add a link with Weight/Cost between any two Routers\n";
        cout << "3. Press 3 to Delete the link between any two Routers\n";
        cout << "4. Press 4 to Assign/change weights for links between routers/CPEs\n";
        cout << "5. Press 5 to Find out and print the least cost path between any 2 given nodes(could be routers or CPEs)\n";
        cout << "6. Press 6 to print the Network Topology Modeled\n";
        cout << "7. Press 7 to Add a CPE to a Router\n";
        cout << "8. Press 8 to see the CPEs connected to a Router.\n";
        cout << "9. Press 9 to Delete a CPE connected to a Router\n\n\n";
        cout << "10. Press 10 to Exit the Application\n\n\n";

        input1:
        cout << "Enter your choice :  ";
        cin >> choice;
        
        if (!(choice>0 && choice<=10)){
            cout<<"Invalid Input";
            goto input1 ;
            }

        switch (choice)
        {
        case 1:
            int r, c, w;
            cout << "\n Enter the Necessary Details required regarding Network Nodes(Router) to design the Topology: \n\n\n";
            input_router:
            cout << "Input the  Number of Routers you need in the Topology:  ";
            cin >> r;
             if (!(r>0 && r<=400)){
                 cout<<"Invalid Input";
                 goto input_router ;
                 
             }
            V = r;
            graph = createGraph(V);
            for (int i = 0; i < V; i++)
            {
                cout << "\n Enter The Router"
                     << " " << i + 1 << " "
                     << "Id/Name :";
                cin >> graph.referenceList[i].vertices;
            }
            cout << "\n\nRouters Data Entered Successfully !!\n\n";

            break;

        case 2:
            int weight;
            cout << "\nAdd a link with Weight/Cost between any two Routers: \n\n";
            cout << "\nInput the Source Router Id/Name from the topology: ";
            cin >> source;
            cout << "\nInput the Destination Router Id/Name from the topology: ";
            cin >> destination;

            input_weight:
            
            cout << "\nEnter The Edge Weight/Cost :";
            cin >> weight;

            if (!(weight>0 && weight<=400)){
                 cout<<"Invalid Input";
                 goto input_weight ;
                 }
                 
            addLink(graph, source, destination, weight);

            break;
        case 3:
        {

            cout << "\nEnter the source Router Id/Name from the topology to be deleted : ";
            cin >> source;
            cout << "\nEnter the destination Router Id/Name from the topology to be deleted : ";
            cin >> destination;
            int sourceIndex = findIndex(graph, source);
            int destinationIndex = findIndex(graph, destination);
            AdjListNode *ptr = graph.referenceList[sourceIndex].adjList.head;
            if (ptr->dest == destinationIndex)
            {
                graph.referenceList[sourceIndex].adjList.head = ptr->next;
                cout << "\nLink between Router '" << source << "' and Router '" << destination << "' with weight '" << ptr->weight << "' is deleted";
                delete ptr;
            }
            else
            {
                while (ptr->next->dest != destinationIndex)
                {
                    ptr = ptr->next;
                }
                cout << "\nLink between Router '" << source << "' and Router '" << destination << "' with weight '" << ptr->next->weight << "' is deleted";
                AdjListNode *tmp = ptr->next;
                ptr->next = ptr->next->next;
                delete tmp;
            }

            break;
        }

        case 4:
        {

            int weight,v;
            stringtest:
            cout << "\nEnter the source Router Id/Name from the topology";
            cin >> source;
            cout << "\nEnter the destination Router Id/Name from the topology";
            cin >> destination;

            for (v=0;v<graph.V;v++){
                AdjListNode *pCrawl = graph.referenceList[v].adjList.head;
                if (graph.referenceList[v].vertices != source && graph.referenceList[v].vertices != destination){
                    cout<<"Source or Destination doesn't exist";
                    goto stringtest;
                }

            }

            input_weight1:
            cout << "\nEnter the updated edge weight/cost : ";
            cin >> weight;
            
            if (!(weight>0 && weight<=400)){
                 cout<<"Invalid Input";
                 goto input_weight1 ;
                 }
                 
            int sourceIndex = findIndex(graph, source);
            int destinationIndex = findIndex(graph, destination);
            AdjListNode *ptr = graph.referenceList[sourceIndex].adjList.head;
            while (ptr->dest != destinationIndex)
            {
                ptr = ptr->next;
            }
            ptr->weight = weight;
            cout << "\nUpdated weight of edge between Router '" << source << "' and Router '" << destination << "' is '" << weight << "'";
            break;
        }
        case 5:
        {

            cout << "Enter the source Router Id/Name from the topology: ";
            cin >> source;
            cout << "Enter the destination Router Id/Name from the topology: ";
            cin >> destination;
            int sourceIndex = findIndex(graph, source);
            int destinationIndex = findIndex(graph, destination);
            graph.referenceList[sourceIndex].cost = 0;
            applyBellman(graph);
            cout << "The cost of least cost path between Router '" << source << "' and "
                 << "Router '" << destination << "' is : " << graph.referenceList[destinationIndex].cost;
            for (int i = 0; i < sizeof(graph.referenceList); i++)
            {
                graph.referenceList[i].cost = MAX;
            }
            break;
        }

        case 6:
            printGraph(graph);
            break;
        case 7:
            int n;
            cout << "enter the router you want to add CPE\t";
            cin >> router_name;
            cout << "enter number of CPE you want to add\t";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                cout << "\nEnter name of CPE : " << i + 1 << "\t";
                cin >> cpe_name;
                addCpe(graph, router_name, cpe_name);
            }
            break;
        case 8:
            cout << "Enter the name of the Router: \t";
            cin >> router_name;
            printCPEs(graph, router_name);
            break;
        case 9:
            cout << "Enter the name of Router:\t";
            cin >> router_name;
            deleteCPEs(graph, router_name);
            break;
        case 10:
            printf("\n\n\n\t\tTHANKS FOR USING OUR APPLICATION!\n\n\n");
            exit(0);
            break;
        }
    }
    return 0;
}
