#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

class ppmImage
{
public:
    /*constructors*/
    ppmImage (); //default constructor
    ppmImage (const int, const int); //constructor which creates an object according to the given dimensions
    ppmImage (const string&); //constructor which takes a ppm file name as argument and creates object form file

    /*accesor function (to private member)*/
    int getRow () const;
    int getColumn () const;
    int getMaxColor () const;
    int getPixel (const int, const int, const int) const;

    /*mutator function (to private member)*/
    void setRow (const int);
    void setColumn (const int);
    void setMaxColor (const int);
    void setPixel (const int, const int, const int, const int); //changes the individual pixel

    /*some necessary function*/
    void printDimension () const;
    int savePpm (const string&) const; //We make int for return 0 and 1 in main kontrol
    int readPpm  (const string&);

    /*my function*/
    void resizeVector(const int x)
    {
        if (x < pixel.size())
        {
            cerr << "Cannot shrink vector" << endl;
            exit(1);
        }
        pixel.resize(x);
    }

    /*overloaded operator*/
    ppmImage operator + (const ppmImage& other)
    {
        ppmImage retObject;

        if (other.row != getRow() || other.column != getColumn()) //we assume max color for both object is the same
        {
            cerr << "Objects are different sizes." << endl;
            exit(1);
        }

        else
        {
            retObject.setRow(getRow());
            retObject.setColumn(getColumn());
            retObject.setMaxColor(getMaxColor());
            retObject.pixel.resize(getRow() * getColumn() * 3);

            for (int i = 0; i < getRow() * getColumn() * 3; i += 3) 
            {
                int r = pixel[i] + other.pixel[i];
                int g = pixel[i+1] + other.pixel[i+1];
                int b = pixel[i+2] + other.pixel[i+2];

                if (r > 255) r = 255;
                if (g > 255) g = 255; /*If the values bigger than 255 we set 255*/
                if (b > 255) b = 255;

                retObject.pixel[i] = r;
                retObject.pixel[i+1] = g;
                retObject.pixel[i+2] = b;
            }
        }
        return retObject;
    }

    ppmImage operator - (const ppmImage& other)
    {
        ppmImage retObject;

        if (other.row != getRow() || other.column != getColumn()) //we assume max color for both object is the same
        {
            cerr << "Objects are different sizes." << endl;
            exit(1);
        }

        else
        {
            retObject.setRow(getRow());
            retObject.setColumn(getColumn());
            retObject.setMaxColor(getMaxColor());
            retObject.pixel.resize(getRow() * getColumn() * 3);

            for (int i = 0; i < getRow() * getColumn() * 3; i += 3) 
            {
                int r = pixel[i] - other.pixel[i];
                int g = pixel[i+1] - other.pixel[i+1];
                int b = pixel[i+2] - other.pixel[i+2];

                if (r < 0) r = 0;
                if (g < 0) g = 0; /*If the values smaller than 0 we set 0*/
                if (b < 0) b = 0;

                retObject.pixel[i] = r;
                retObject.pixel[i+1] = g;
                retObject.pixel[i+2] = b;
            }
        }
        return retObject;
    }

    int& operator () (const int r, const int c, const int rgbindex)
    {
        if ((r > getRow() - 1) || (c > getColumn() - 1) || (rgbindex > 3) || (rgbindex < 0) || (r < 0) || (c < 0))
        {
            cerr << "Invalid value (row,column or color channel)" << endl;
            exit(1);
        }
        int index = (r * getColumn() + c) * 3 + rgbindex - 1; /*algorithn which find index */

        return pixel[index];
    } 

    friend ostream& operator << (ostream&, const ppmImage&);

private:
    vector <int> pixel;  //vector where pixel values are kept
    int row;             //pixel's row
    int column;          //pixel's column
    int maxColor;        //maximum color value that pixels can receive
};

/*Standalone functions*/
int read_ppm(const string, ppmImage&);
int write_ppm(const string, const ppmImage&);
int test_addition(const string, const string, const string);
int test_subtraction(const string, const string, const string);
int test_print(const string);
int swap_channels(ppmImage&, int);
ppmImage single_color(const ppmImage&, int);

int main(int argc, char const *argv[])
{    
    int choice = atoi(argv[1]);

    string ppm_file_name1 = argv[2];    

    if (choice == 1)
    {
        if (argc == 5)
        {
            string ppm_file_name2 = argv[3];
            string ppm_file_name3 = argv[4];
            test_addition(ppm_file_name1,ppm_file_name2,ppm_file_name3);
        }

        else
        {
            cerr << "Missing argument" << endl;
            exit(1);
        }
    }

    else if (choice == 2)
    {
        if (argc == 5)
        {
            string ppm_file_name2 = argv[3];
            string ppm_file_name3 = argv[4];
            test_subtraction(ppm_file_name1,ppm_file_name2,ppm_file_name3);
        }

        else
        {
            cerr << "Missing argument" << endl;
            exit(1);
        }
    }

    else if (choice == 3)
    {
        if (argc == 4)
        {
            string ppm_file_name2 = argv[3];
            ppmImage object;
            read_ppm(ppm_file_name1,object);
            swap_channels(object,2);
            write_ppm(ppm_file_name2,object);
        }

        else
        {
            cerr << "Missing argument." << endl;
            exit(1);
        }
    }

    else if (choice == 4)
    {
        if (argc == 4)
        {
            string ppm_file_name2 = argv[3];
            ppmImage object;
            read_ppm(ppm_file_name1,object);
            swap_channels(object,3);
            write_ppm(ppm_file_name2,object);
        }

        else
        {
            cerr << "Missing argument." << endl;
            exit(1);
        }
    }

    else if (choice == 5)
    {
        if (argc == 4)
        {
            string ppm_file_name2 = argv[3];
            ppmImage object1, object2;
            read_ppm(ppm_file_name1,object1);
            object2 = single_color(object1,1);
            write_ppm(ppm_file_name2,object2);
        }

        else
        {
            cerr << "Missing argument." << endl;
            exit(1);
        }
    }

    else if (choice == 6)
    {
        if (argc == 4)
        {
            string ppm_file_name2 = argv[3];
            ppmImage object1, object2;
            read_ppm(ppm_file_name1,object1);
            object2 = single_color(object1,2);
            write_ppm(ppm_file_name2,object2);
        }

        else
        {
            cerr << "Missing argument." << endl;
            exit(1);
        }
    }

    else if (choice == 7)
    {
        if (argc == 4)
        {
            string ppm_file_name2 = argv[3];
            ppmImage object1, object2;
            read_ppm(ppm_file_name1,object1);
            object2 = single_color(object1,3);
            write_ppm(ppm_file_name2,object2);
        }

        else
        {
            cerr << "Missing argument." << endl;
            exit(1);
        }
    }

    else
    {
        cerr << "---Invalid choice" << endl;
        exit(1);
    }
    return 0;
}

ostream& operator << (ostream& print, const ppmImage& Obj)
{
    print << "P3" << endl << Obj.row << " " << Obj.column << endl << Obj.maxColor << endl;

    int a = 0;

    for (int i = 0; i < Obj.row; ++i)
    {
        for (int j = 0; j < Obj.column; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                int tempPix = Obj.pixel[a];

                if (tempPix > 255 || tempPix < 0)
                {
                    cerr << "Pixel value is out of standards." << endl;
                    exit(1);
                }
                print << tempPix << " ";
                a++;
            }
            print << "\t";
        }
        print << endl;
    }
    return print;
}

ppmImage :: ppmImage () : row(0), column(0), maxColor(255)
{}

ppmImage :: ppmImage (const string& filename)
{
    int result = readPpm(filename);

    if (result == 0) 
    {
        exit(1);
    }
}

ppmImage :: ppmImage (const int rowValue, const int columnValue) : row(rowValue), column(columnValue), maxColor(255)
{
    pixel.resize(getRow() * getColumn() *3); //All pixel must be white (wiht value 255)
}

void ppmImage :: printDimension() const
{
    cout << "Image dimensions : " << getRow() << "x" << getColumn() << endl;
}

int ppmImage :: savePpm (const string& filename) const
{
    ofstream outputFile(filename);

    if (!outputFile.is_open())
    {
        cerr << "Could'nt be open file: " << filename << endl;
        return 0;
    }
    outputFile << "P3" << endl << getRow() << " " << getColumn() << endl << getMaxColor() << endl;

    int a = 0;

    for (int i = 0; i < getRow(); ++i)
    {
        for (int j = 0; j < getColumn(); ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                int tempPix = pixel[a];

                if (tempPix > 255 || tempPix < 0)
                {
                    cerr << "Pixel value is out of standards." << endl;
                    return 0;
                }
                outputFile << tempPix << " ";
                a++;
            }
            outputFile << "\t";
        }
        outputFile << endl;
    }
    outputFile.close();

    return 1;
}

int ppmImage :: readPpm (const string& filename)
{
    ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        cerr << "Could'nt be open file: " << filename << endl;
        return 0;
    }

    string format;  
    inputFile >> format >> row >> column >> maxColor;

    if (format != "P3")
    {
        cerr << "Invalid File Format : " << format << endl;
        return 0;
    }
    pixel.resize(getRow() * getColumn() * 3);

    for (int i = 0; i < getRow() * getColumn() * 3; ++i)
    {
        int tempPix;
        inputFile >> tempPix;

        if (tempPix > 255 || tempPix < 0)
        {
            cerr << "Pixel value is out of standards." << endl;
            return 0;
        }
        pixel[i] = tempPix;
    }
    inputFile.close();

    return 1;
}

int ppmImage :: getRow () const
{
    return row;
}

int ppmImage :: getColumn () const
{
    return column;
}

int ppmImage :: getMaxColor () const
{
    return maxColor;
}

int ppmImage :: getPixel (const int r, const int c, const int rgbindex) const
{
    if ((r > row - 1) || (c > column - 1) || (r < 0) || (c < 0) || (rgbindex > 3) || (rgbindex < 0))
    {
        cerr << "Invalid pixel value or location" << endl;
        exit(1);
    }
    int index = (r * column + c) * 3 + rgbindex;

    return pixel[index];
}

void ppmImage :: setRow(const int rowValue)
{
    row = rowValue;
}

void ppmImage :: setColumn(const int columnValue)
{
    column = columnValue;
}

void ppmImage :: setMaxColor(const int maxColorValue)
{
    if (maxColorValue > 255 || maxColorValue < 0)
    {
        cerr << "Invalid value for maximum color value (" << maxColorValue << ")" << endl;
        exit(1);
    }
    maxColor = maxColorValue;
}

void ppmImage :: setPixel(const int r, const int c, const int rgbindex, const int value) //pixel[r][c][rgbindex] = value
{
    if ((r > row - 1) || (c > column - 1) || (value > maxColor) || (r < 0) || (c < 0) || (value < 0) || (rgbindex > 3) || (rgbindex < 0))
    {
        cerr << "Invalid pixel value or location" << endl;
        exit(1);
    }
    int index = (r * column + c) * 3 + rgbindex;

    pixel[index] = value;
}

int read_ppm(const string source_ppm_file_name, ppmImage& destination_object)
{
    int result = destination_object.readPpm(source_ppm_file_name);

    if (result == 0)
    {
        exit(1);
    }
    return 1;
}

int write_ppm(const string destination_ppm_file_name, const ppmImage& source_object)
{
    source_object.savePpm(destination_ppm_file_name);

    return 1;
}

int test_addition(const string filename_image1, const string filename_image2, const string filename_image3)
{
    ppmImage object1, object2, object3;

    read_ppm(filename_image1,object1);
    read_ppm(filename_image2,object2);

    object3 = object1 + object2;

    write_ppm(filename_image3,object3);

    return 1;
}

int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3)
{
    ppmImage object1, object2, object3;

    read_ppm(filename_image1,object1);
    read_ppm(filename_image2,object2);

    object3 = object1 - object2;

    write_ppm(filename_image3,object3);

    return 1;
}

int test_print(const string filename_image1)
{
    ppmImage testObject;

    int result = testObject.readPpm(filename_image1);

    if (result == 0)
    {
        exit(1);
    }
    cout << testObject;

    return 1;
}

int swap_channels(ppmImage& image_object_to_be_modified, int swap_choice)
{
    if (swap_choice == 1)
    {
        for (int i = 0; i < image_object_to_be_modified.getRow(); ++i)
        {
            for (int j = 0; j < image_object_to_be_modified.getColumn(); ++j)
            {
                int tempPix1 = image_object_to_be_modified(i,j,0); //red
                int tempPix2 = image_object_to_be_modified(i,j,1); //green

                image_object_to_be_modified.setPixel(i,j,0,tempPix2);
                image_object_to_be_modified.setPixel(i,j,1,tempPix1);

                if ((tempPix1 != image_object_to_be_modified(i,j,1)) || (tempPix2 != image_object_to_be_modified(i,j,0)))
                { 
                    return 0;
                }
            }
        }
    }

    else if (swap_choice == 2)
    {
        for (int i = 0; i < image_object_to_be_modified.getRow(); ++i)
        {
            for (int j = 0; j < image_object_to_be_modified.getColumn(); ++j)
            {
                int tempPix1 = image_object_to_be_modified(i,j,0); //red
                int tempPix2 = image_object_to_be_modified(i,j,2); //blue

                image_object_to_be_modified.setPixel(i,j,0,tempPix2);
                image_object_to_be_modified.setPixel(i,j,2,tempPix1);

                if ((tempPix1 != image_object_to_be_modified(i,j,2)) || (tempPix2 != image_object_to_be_modified(i,j,0)))
                {
                    return 0;
                }
            }
        }
    }

    else if (swap_choice == 3)
    {
        for (int i = 0; i < image_object_to_be_modified.getRow(); ++i)
        {
            for (int j = 0; j < image_object_to_be_modified.getColumn(); ++j)
            {
                int tempPix1 = image_object_to_be_modified(i,j,1); //green
                int tempPix2 = image_object_to_be_modified(i,j,2); //blue

                image_object_to_be_modified.setPixel(i,j,1,tempPix2);
                image_object_to_be_modified.setPixel(i,j,2,tempPix1);

                if ((tempPix1 != image_object_to_be_modified(i,j,2)) || (tempPix2 != image_object_to_be_modified(i,j,1)))
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

ppmImage single_color(const ppmImage& source, int color_choice)
{
    ppmImage copySource(source.getRow(),source.getColumn());
    ppmImage temp = source; //for const

    for (int i = 0; i < copySource.getRow(); ++i)
    {
        for (int j = 0; j < copySource.getColumn(); ++j)
        {
            if (color_choice == 1)
            {
                copySource.setPixel(i,j,0,temp(i,j,0)); //channel 1 preserved
                copySource.setPixel(i,j,1,0);
                copySource.setPixel(i,j,2,0);
            }

            else if (color_choice == 2)
            {
                copySource.setPixel(i,j,0,temp(i,j,1)); //channel 2 preserved
                copySource.setPixel(i,j,1,0);
                copySource.setPixel(i,j,2,0);
            }

            else if (color_choice == 3)
            {
                copySource.setPixel(i,j,0,temp(i,j,2)); //channel 3 preserved
                copySource.setPixel(i,j,1,0);
                copySource.setPixel(i,j,2,0);
            }

            else
            {
                cerr << "Invalid color choice (" << color_choice << ")" << endl;
                exit(1);
            }
        }
    }  
    return copySource;
}