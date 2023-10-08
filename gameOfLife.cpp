#include<iostream>
#include <windows.h>
#include<unistd.h>

using namespace std;

void pageclear()
{
    #if defined(_WIN32)
        // Windows-specific code
        system("cls");
    #elif defined(__linux__)
        // Linux-specific code
        system("clear");
    #else
        // General code or warning
        printf("Running on an unsupported OS.\n");
    #endif
}

class Cell //The cell class which represents each cell irrespective of state.
{
    friend class Grid;
    char next_state, curr_state;

    public:
    Cell()
    {
        curr_state = '*';
        next_state = '*';
    }

    char getNextState() //Accessor function
    {
        curr_state = next_state;
        return next_state;
    }

    char getCurrState() //Accessor function
    {
        return curr_state;
    }

    void setNextState(char st) //Mutator Function
    {
        next_state = st;
    }

    void setDefaultState() //Mutator Function
    {
        next_state = 'O';
    }
};

class Grid //The grid class updates the main display every second and calculates the next generation. 
{
    friend void operator<<(ostream&, Grid&); 
    friend void operator>>(istream&, Grid&); 
    Cell grid[20][20];

    public:

    void setGen(int choice) //Determines the starting (intialising) generation.
    {
        switch(choice)
        {
            case 1: //Block
                grid[3][3].setDefaultState();
                grid[3][4].setDefaultState();
                grid[4][3].setDefaultState();
                grid[4][4].setDefaultState();
                break;
            
            case 2: //Blinker
                grid[15][5].setDefaultState();
                grid[15][6].setDefaultState();
                grid[15][7].setDefaultState();
                break;

            case 3: //Toad
                grid[10][10].setDefaultState();
                grid[10][11].setDefaultState();
                grid[10][12].setDefaultState();
                grid[11][9].setDefaultState();
                grid[11][10].setDefaultState();
                grid[11][11].setDefaultState();
                break;

            case 4: //Glider
                grid[2][2].setDefaultState();
                grid[4][2].setDefaultState();
                grid[3][3].setDefaultState();
                grid[3][4].setDefaultState();
                grid[4][2].setDefaultState();
                grid[4][3].setDefaultState();
                break;

            case 5: //Pentadecathlon
                grid[5][5].setDefaultState();
                grid[6][5].setDefaultState();
                grid[7][4].setDefaultState();
                grid[7][6].setDefaultState();
                grid[8][5].setDefaultState();
                grid[9][5].setDefaultState();
                grid[10][5].setDefaultState();
                grid[11][5].setDefaultState();
                grid[12][4].setDefaultState();
                grid[12][6].setDefaultState();
                grid[13][5].setDefaultState();
                grid[14][5].setDefaultState();
                break;

            case 6: //Light Weight Space Ship
                grid[3][3].setDefaultState();
                grid[3][4].setDefaultState();
                grid[3][5].setDefaultState();
                grid[3][6].setDefaultState();
                grid[3][7].setDefaultState();
                grid[4][7].setDefaultState();
                grid[4][2].setDefaultState();
                grid[5][7].setDefaultState();
                grid[6][6].setDefaultState();
                grid[7][4].setDefaultState();
                break;

            case 7: //Custom generation
                cout<<"Keep entering coordinates for live cells : and to stop enter -1 -1"<<endl;
                while(true)
                {
                    int x,y;
                    cin>>x>>y;
                    if(x==-1 && y==-1)
                        break;
                    grid[x][y].setDefaultState();
                }
                break;
        }
    }

    void nextGen() //Most valuable function which helps generate the next generation.
    {
        int neighbours;
        for(int i=0;i<20;i++)
        {
            for(int j=0;j<20;j++)
            {
                neighbours = 0;
                for(int x = i-1;x<=i+1;x++)
                {
                    for(int y = j-1; y<=j+1;y++)
                    {
                        if(x==i && y==j)
                            continue;
                        if(grid[x][y].getCurrState()== 'O')
                            neighbours++;
                    }
                }
                if(grid[i][j].getCurrState() == 'O')
                {
                    if(neighbours < 2 || neighbours > 3)
                        grid[i][j].setNextState('*');
                    else if(neighbours == 2 || neighbours == 3)
                        grid[i][j].setNextState('O');
                }
                else
                {
                    if(neighbours == 3)
                        grid[i][j].setNextState('O');
                }
            }
        }
    }
};

void operator<<(ostream& print, Grid& obj) //Operator overloading for insertion operator <<.
{
    cout<<"\n\n";
    for(int i=0;i<20;i++) 
    {
        print<<"\t\t\t";
        for(int j=0;j<20;j++)
            print<<obj.grid[i][j].getNextState()<<" ";
        print<<endl;
    }
    obj.nextGen();
    sleep(1);
    pageclear();
        cout<<"\n\n";
}

void operator>>(istream& insert, Grid& obj) //Operator overloading for extraction operator >>
{
    int choice;
    cout<<"Initialise Generator: "<<endl;
    cout<<"1)Block\n2)Blinker\n3)Toad\n4)Glider\n5)Pentadecathlon\n6)Light Weight Space Ship\n7)Custom\nChoice: "<<endl;
    insert>>choice;
    obj.setGen(choice);
    
}

int main()
{
    Grid subject;
    cin>>subject;
    while(true)
        cout<<subject;
    return 0;
}