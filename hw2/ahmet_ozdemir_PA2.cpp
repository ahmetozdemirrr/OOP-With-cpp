#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class ImageEditor
{
public:
    void mainMenu();
    void openImageMenu();
    void saveImageMenu();
    void scriptsMenu();
    void grayscaleMenu();
    void openImage();
    void saveImage();
    void convert();

private:
    vector <int> pixel;
    int row;
    int column;
    int maxColor;
};

void ImageEditor :: mainMenu()
{
    cout << "Main Menu" << endl;
    int choice = -1;

    do
    {
        cout << "0 - Exit" << endl << "1 - Open An Image (D)" << endl << "2 - Save Image Data (D)" << endl << "3 - Scripts (D)" << endl;
        cin >> choice;

        if (choice == 0)
        {
            cout << "Exiting." << endl;
            exit(1);
        }

        else if (choice == 1)
        {
            openImageMenu();
        }

        else if (choice == 2)
        {
            saveImageMenu();
        }

        else if (choice == 3)
        {
            scriptsMenu();
        }

        else
        {
            cout << "Invalid choice." << endl;
        }
    }
    while (choice != 0);
}

void ImageEditor :: openImageMenu()
{
    cout << "Open An Image Menu" << endl;
    int choice = -1;

    do
    {
        cout << "0 - UP" << endl << "1 - Enter The Name Of The Image File" << endl;
        cin >> choice;

        if (choice == 0)
        {
            mainMenu();
        }

        else if (choice == 1)
        {
            openImage();
            openImageMenu();
        }

        else
        {
            cout << "Invalid choice." << endl;
        }
    }
    while (choice != 0);
}

void ImageEditor :: saveImageMenu()
{
    cout << "Save Image Data Menu" << endl;
    int choice = -1;

    do
    {
        cout << "0 - UP" << endl << "1 - Enter A File Name" << endl;
        cin >> choice;

        if (choice == 0)
        {
            mainMenu();
        }

        else if (choice == 1)
        {
            saveImage();
            saveImageMenu();
        }

        else
        {
            cout << "Invalid choice." << endl;
        }
    }
    while (choice != 0);
}

void ImageEditor :: scriptsMenu()
{
    cout << "Scripts Menu" << endl;
    int choice = -1;

    do
    {
        cout << "0 - Up" << endl << "1 - Convert To Grayscale (D)" << endl;
        cin >> choice;

        if (choice == 0)
        {
            mainMenu();
        }

        else if (choice == 1)
        {
            grayscaleMenu();
        }

        else
        {
            cout << "Invalid choice." << endl;
        }
    }
    while (choice != 0);
}

void ImageEditor :: grayscaleMenu()
{
    cout << "Convert To Grayscale Menu" << endl;
    int choice = -1;

    do
    {
        cout << "0 - Up" << endl << "1 - Enter Coefficients For RED GREEN And BLUE Channels." << endl;
        cin >> choice;

        if (choice == 0)
        {
            mainMenu();
        }

        else if (choice == 1)
        {
            convert();
            mainMenu();
        }

        else
        {
            cout << "Invalid choice." << endl;
        }
    }
    while (choice != 0);
}

void ImageEditor :: openImage()
{
    string filename;
    cin >> filename;
    cout << endl;

    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "File could'nt be opened" << endl;
        exit(1);
    }

    string format;  
    file >> format >> row >> column >> maxColor;

    if (format != "P3")
    {
        cerr << "Invalid Format" << endl;
        exit(1);
    }

    pixel = vector <int>(row * column * 3); //Yeniden boyutlandırma.

    for (int i = 0; i < row * column * 3; ++i) // 3 --> for RED, GREEN and BLUE
    {
        int tempPix;
        file >> tempPix;

        if (tempPix > 255 || tempPix < 0)
        {
            cerr << "Pixel value is out of standards." << endl;
            exit(1);
        }
        pixel[i] = tempPix;
    }
}

void ImageEditor :: saveImage()
{
    string filename;
    cin >> filename;
    cout << endl;

    ofstream file(filename);

    if (!file.is_open())
    {
        cerr << "File could'nt be opened." << endl;
        exit(1);
    }
    file << "P3" << endl << row << " " << column << endl << maxColor << endl;

    int a = 0;

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < column; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                int tempPix = pixel[a];

                if (tempPix > 255 || tempPix < 0)
                {
                    cerr << "Pixel value is out of standards." << endl;
                    exit(1);
                }
                file << tempPix << " ";
                a++;
            }
            file << "\t";
        }
        file << endl;
    }
}

void ImageEditor :: convert()
{
    float value1, value2, value3;
    cin >> value1 >> value2 >> value3;

    if ((value1 >= 0 && value1 < 1) && (value2 >= 0 && value2 < 1) && (value3 >= 0 && value3 < 1))
    {
        for (int i = 0; i < row * column * 3; i += 3)
        {
            int grayScale = (int)(value1 * pixel[i]) + (value2 * pixel[i+1]) + (value3 * pixel[i+2]);

            if (grayScale > 255)
            {
                grayScale = 255;
            }
            pixel[i] = grayScale;
            pixel[i+1] = grayScale;
            pixel[i+2] = grayScale;
        }
    }

    else
    {
        cerr << "Coefficients are must be in the range [0,1)." << endl;
        exit(1);
    }
}

int main() 
{
    ImageEditor object;
    object.mainMenu();
    
    return 0;
}