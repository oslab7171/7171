#include <iostream>
#include <fstream>
using namespace std;

class OS
{
private:
    char M[100][4];
    char IR[4];
    char R[4];
    int IC;
    int SI;
    bool C;
    char buffer[40];
    string ID;

public:
    void init();
    void LOAD();
    void Execute();
    void MOS();

    void saveToFile();

    fstream infile;
    fstream outfile;
};




void OS::saveToFile(){
    fstream memfile;
    string filename= "Mem_"+ID;
    memfile.open("./mem/"+filename+".txt",ios::out);

    for (int i = 0; i < 100; i++)
        {
            if(i<=9)memfile << "[0" << i << "]---\t";
            else memfile << "[" << i << "]---\t";
            for (int j = 0; j < 4; j++)
            {
                if( M[i][j])memfile << M[i][j];
            }
            memfile<<"\n";
        }

}



// initiallise everything to 0
void OS::init()
{

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            M[i][j] = 0;
        }
    }
    // getid
    // char str[4];
    ID="";

    for(int i=0;i<4;i++)ID+=buffer[4+i];
    IR[0] = {0};
    R[0] = {0};
    C = false;
}

void OS::MOS()
{
    if (SI == 1) // Read Mode
    {
        for (int i = 0; i <= 39; i++)
            buffer[i] = '\0';

        infile.getline(buffer, 40);
        int k = 0;
        int i = IR[2] - '0';
        i = i * 10;
        for (int l = 0; l < 10; ++l)
        {
            for (int j = 0; j < 4; ++j)
            {
                M[i][j] = buffer[k];
                k++;
            }
            if (k == 40)
            {
                break;
            }
            i++;
        }

        for (int i = 0; i < 100; i++)
        {
            cout << "M[" << i << "]\t";
            for (int j = 0; j < 4; j++)
            {
                cout << M[i][j];
            }
            cout << endl;
        }
    }
    else if (SI == 2) // Write Mode
    {
        for (int i = 0; i <= 39; i++)
            buffer[i] = '\0';

        int k = 0;
        int i = IR[2] - '0';
        i = i * 10;

        for (int l = 0; l < 10; ++l)
        {
            for (int j = 0; j < 4; ++j)
            {
                buffer[k] = M[i][j];
                if (buffer[k] != '\0')
                    outfile << buffer[k];

                k++;
            }
            if (k == 40)
            {
                break;
            }
            i++;
        }

        for (int i = 0; i < 100; i++)
        {
            cout << "M[" << i << "]\t";
            for (int j = 0; j < 4; j++)
            {
                cout << M[i][j];
            }
            cout << endl;
        }

        outfile << "\n";
    }
    else if (SI == 3)
    {

        outfile << "\n";
        outfile << "\n";
    }
}

void OS::Execute()
{
    while (true)
    {
        for (int i = 0; i < 4; i++)
        {
            IR[i] = M[IC][i];
        }
        IC++;

        if (IR[0] == 'G' && IR[1] == 'D')
        {
            SI = 1;
            MOS();
        }
        else if (IR[0] == 'P' && IR[1] == 'D')
        {
            SI = 2;
            MOS();
        }
        else if (IR[0] == 'H')
        {
            SI = 3;
            MOS();
            break;
        }
        else if (IR[0] == 'L' && IR[1] == 'R')
        {
            int i = IR[2] - '0';
            i = i * 10 + (IR[3] - '0');

            for (int j = 0; j <= 3; j++)
                R[j] = M[i][j];

            cout << endl;
        }
        else if (IR[0] == 'S' && IR[1] == 'R')
        {
            int i = IR[2] - '0';
            i = i * 10 + (IR[3] - '0');
            for (int j = 0; j <= 3; j++)
                M[i][j] = R[j];

            cout << endl;
        }
        else if (IR[0] == 'C' && IR[1] == 'R')
        {
            int i = IR[2] - '0';
            i = i * 10 + (IR[3] - '0');

            int count = 0;

            for (int j = 0; j <= 3; j++)
                if (M[i][j] == R[j])
                    count++;

            if (count == 4)
                C = true;
        }
        else if (IR[0] == 'B' && IR[1] == 'T')
        {
            if (C == true)
            {
                int i = IR[2] - '0';
                i = i * 10 + (IR[3] - '0');

                IC = i;
            }
        }
    }
}

void OS::LOAD()
{
    cout << "Reading Data..." << endl;
    int x = 0;
    do
    {
        for (int i = 0; i <= 39; i++)
            buffer[i] = '\0';

        infile.getline(buffer, 41);

        for (int k = 0; k <= 39; k++)
            cout << buffer[k];

        if (buffer[0] == '$' && buffer[1] == 'A' && buffer[2] == 'M' && buffer[3] == 'J')
        {
            init();
        }
        else if (buffer[0] == '$' && buffer[1] == 'D' && buffer[2] == 'T' && buffer[3] == 'A')
        {
            IC = 00;
            Execute();
        }
        else if (buffer[0] == '$' && buffer[1] == 'E' && buffer[2] == 'N' && buffer[3] == 'D')
        {
            x = 0;
            saveToFile();
            continue;
        }
        else
        {
            int k = 0;

            for (; x < 100; ++x)
            {
                for (int j = 0; j < 4; ++j)
                {

                    M[x][j] = buffer[k];
                    k++;
                }

                if (k == 40 || buffer[k] == ' ' || buffer[k] == '\n')
                {
                    break;
                }
            }
        }

    } while (!infile.eof());
}

int main()
{
    OS os;

    os.infile.open("input.txt", ios::in);
    os.outfile.open("output.txt", ios::out);

    if (!os.infile)
    {
        cout << "Failure" << endl;
    }
    else
    {
        cout << "File Exist" << endl;
    }

    os.LOAD();
    return 0;
}